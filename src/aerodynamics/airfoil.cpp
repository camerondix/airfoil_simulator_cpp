#include "airfoil.h"

#include <cmath>
#include <vector>

#include "panel.h"
#include "point.h"
#include "vector.h"

using aerodynamics::Airfoil;

using aerodynamics::Panel;
using geometry::Point;
using geometry::Vector;

void Airfoil::setAngleOfAttack(double radians)
{
    for (int i = 0; i < size(); ++i)
        this->at(i).alphaAngle = radians;
}

void Airfoil::setGammas(std::vector<double> gammas)
{
    if (gammas.size() != size())
        throw std::invalid_argument("Invalid gamma array size");
    for (int i = 0; i < size(); ++i)
        this->at(i).gamma = gammas.at(i);
}

void Airfoil::setLambdas(std::vector<double> lambdas)
{
    if (lambdas.size() != size())
        throw std::invalid_argument("Invalid gamma array size");
    for (int i = 0; i < size(); ++i)
        this->at(i).lambda = lambdas.at(i);
}

double Airfoil::getCoefficientOfLift() const
{
    double normal = 0;
    double axial = 0;
    for (int i = 0; i < size(); ++i)
    {
        Panel panel = this->at(i);
        normal += panel.getCoefficientOfNormalForce() * std::cos(panel.alphaAngle);
        axial += panel.getCoefficientOfAxialForce() * std::sin(panel.alphaAngle);
    }
    return normal - axial;
}

double Airfoil::getCoefficientOfDrag() const
{
    double normal = 0;
    double axial = 0;
    for (int i = 0; i < size(); ++i)
    {
        Panel panel = this->at(i);
        normal += panel.getCoefficientOfNormalForce() * std::sin(panel.alphaAngle);
        axial += panel.getCoefficientOfAxialForce() * std::cos(panel.alphaAngle);
    }
    return normal - axial;
}

double Airfoil::getCoefficientOfMoment() const
{
    double moment = 0;
    for (int i = 0; i < size(); ++i)
    {
        Panel panel = this->at(i);
        moment += panel.coefficientOfPressure * (panel.getMid().x - 0.25) * panel.getLength() * std::cos(panel.getPhiAngle());
    }
    return moment;
}

std::vector<Panel> Airfoil::getRotatedPanels() const
{
    std::vector<Panel> panels(size());
    for (int i = 0; i < size(); ++i)
    {
        panels[i] = this->at(i).getRotatedPanel();
    }
    return panels;
}

Point Airfoil::getAerodynamicCenter() const
{
    // Calculate the x value
    double x = -getCoefficientOfMoment() / (2.0 * M_PI) + 0.25;

    // Find the closest points to the x center on the upper and lower surfaces
    Point lessTop, moreTop, lessBottom, moreBottom;
    bool foundTop = false, foundBottom = false;
    // Start at 1/5 chord
    int i = size() / 2 + size() / 10;
    int j = size() / 2 - size() / 10;
    for (; i < size(); ++i, j--)
    {
        if (foundTop && foundBottom)
            break;
        if (!foundTop && at(i).getStart().x <= x && at(i).getEnd().x >= x)
        {
            foundTop = true;
            lessTop = at(i).getStart();
            moreTop = at(i).getEnd();
        }
        if (!foundBottom && at(j).getEnd().x <= x && at(j).getStart().x >= x)
        {
            foundBottom = true;
            lessBottom = at(j).getEnd();
            moreBottom = at(j).getStart();
        }
    }

    // Linear interpolate to find the top and bottom y values at x
    double yTop = lessTop.y + (x - lessTop.x) * (moreTop.y - lessTop.y) / (moreTop.x - lessTop.x);
    double yBottom = lessBottom.y + (x - lessBottom.x) * (moreBottom.y - lessBottom.y) / (moreBottom.x - lessBottom.x);

    // The average of the top and bottom y is the camber line
    double y = (yTop + yBottom) / 2.0;
    return Point(x, y, 0);
}

Point Airfoil::getRotatedAerodynamicCenter() const
{
    return getAerodynamicCenter().rotate(-front().alphaAngle, Vector::zUnit());
}

Airfoil Airfoil::getNACA4Airfoil(int pointCount, double maxCamberPercent, double maxCamberPositionPercent, double thicknessPercent, bool closedTrailingEdge, double angleOfAttackRadians)
{
    // Validate arguments
    if (maxCamberPercent < 0 || maxCamberPercent > 9.5)
        throw std::invalid_argument("Max Camber Percentage must be at least 0 and at most 9.5.");
    if (maxCamberPositionPercent < 0 || maxCamberPositionPercent > 90)
        throw std::invalid_argument("Max Camber Position Percentage must be at least 0 and at most 90.");
    if (thicknessPercent < 1 || thicknessPercent > 40)
        throw std::invalid_argument("Thickness Percentage must be at least 0 and at most 40.");
    if (pointCount < 20 || pointCount > 200)
        throw std::invalid_argument("Point Count must be at least 20 and at most 200.");
    if (pointCount % 2 != 0)
        throw std::invalid_argument("Point Count must be an even number.");

    // Create upper and lower airfoil points
    double a_4 = closedTrailingEdge ? -0.1036 : -0.1015;
    double m = maxCamberPercent / 100.0;
    double p = maxCamberPositionPercent / 100.0;
    double t = thicknessPercent / 100.0;
    std::vector<Point> upper((pointCount + 2) / 2);
    std::vector<Point> lower((pointCount + 2) / 2);
    for (int i = 0; i <= (pointCount + 2) / 2; ++i)
    {
        double x = (1 - std::cos(i * (M_PI / (pointCount / 2)))) / 2.0;
        double y_C = x < p ? (m / (p * p)) * (2 * p * x - x * x) : (m / ((1 - p) * (1 - p))) * (1 - 2 * p + 2 * p * x - x * x);
        double gradient = x < p ? (2 * m / (p * p)) * (p - x) : (2 * m / ((1 - p) * (1 - p))) * (p - x);
        double y_T = t / 0.2 * (0.2969 * std::sqrt(x) + -0.126 * x + -0.3516 * x * x + 0.2843 * x * x * x + a_4 * x * x * x * x);
        double theta = std::atan(gradient);
        double x_u = x - y_T * std::sin(theta);
        double y_u = y_C + y_T * std::cos(theta);
        upper[i] = Point{x_u, y_u, 0};
        double x_l = x + y_T * std::sin(theta);
        double y_l = y_C - y_T * std::cos(theta);
        lower[i] = Point{x_l, y_l, 0};
    }

    // Combine upper and lower points in order
    std::reverse(lower.begin(), lower.end());
    std::vector<Point> points(pointCount + 1);
    for (int i = 0; i <= points.size() + 1; ++i)
        if (i < lower.size())
            points[i] = lower[i];
        else
            points[i] = upper[i - lower.size() + 1];

    // Create the panels from the points
    Airfoil airfoil(pointCount);
    for (int i = 1; i < points.size(); ++i)
        airfoil[i - 1] = Panel{points[i - 1], points[i]};

    // Set the angle of attacks
    airfoil.setAngleOfAttack(angleOfAttackRadians);

    return airfoil;
}