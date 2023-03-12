#include "panel_methods.h"

#include <cmath>
#include <vector>

#include "airfoil.h"
#include "panel.h"
#include "point.h"
#include "vector.h"
#include "matrix.h"

using aerodynamics::PanelMethods;

using aerodynamics::Airfoil;
using aerodynamics::Panel;
using geometry::Point;
using geometry::Vector;
using linear_algebra::Matrix;

double PanelMethods::findA(const Point &point1, const Point &point2, double phi)
{
    return -(point1.x - point2.x) * std::cos(phi) - (point1.y - point2.y) * std::sin(phi);
}

double PanelMethods::findB(const Point &point1, const Point &point2)
{
    return (point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y);
}

double PanelMethods::findC(double angle1, double angle2, bool reverse)
{
    return reverse ? -std::cos(angle1 - angle2) : std::sin(angle1 - angle2);
}

double PanelMethods::findD(const Point &point1, const Point &point2, double phi, bool reverse)
{
    return reverse ? -(point1.x - point2.x) * std::sin(phi) + (point1.y - point2.y) * std::cos(phi) : (point1.x - point2.x) * std::cos(phi) + (point1.y - point2.y) * std::sin(phi);
}

double PanelMethods::findE(double a, double b)
{
    if (b - a * a > 0)
        return std::sqrt(b - a * a);
    else
        return 0;
}

double PanelMethods::findGeometricIntegral(double a, double b, double c, double d, double e, double s)
{
    return (c / 2.0) * std::log((s * s + 2.0 * a * s + b) / b) + ((d - a * c) / e) * (std::atan((s + a) / e) - std::atan(a / e));
}

/// @brief normal velocity geometric integral of panel i relative to panel j
double PanelMethods::findIij(const Panel &i, const Panel &j)
{
    double a = findA(i.getMid(), j.getStart(), j.getPhiAngle());
    double b = findB(i.getMid(), j.getStart());
    double c = findC(i.getPhiAngle(), j.getPhiAngle(), false);
    double d = findD(i.getMid(), j.getStart(), i.getPhiAngle(), true);
    double e = findE(a, b);
    double i_ij = findGeometricIntegral(a, b, c, d, e, j.getLength());
    return i_ij;
}

/// @brief tangential velocity geometric integral of panel i relative to panel j
double PanelMethods::findJij(const Panel &i, const Panel &j)
{
    double a = findA(i.getMid(), j.getStart(), j.getPhiAngle());
    double b = findB(i.getMid(), j.getStart());
    double c = findC(i.getPhiAngle(), j.getPhiAngle(), true);
    double d = findD(i.getMid(), j.getStart(), i.getPhiAngle(), false);
    double e = findE(a, b);
    double j_ij = findGeometricIntegral(a, b, c, d, e, j.getLength());
    return j_ij;
}

/// @brief tangential velocity geometric integral of panel i relative to panel j
double PanelMethods::findLij(const Panel &i, const Panel &j)
{
    double a = findA(i.getMid(), j.getStart(), j.getPhiAngle());
    double b = findB(i.getMid(), j.getStart());
    double c = findC(j.getPhiAngle(), i.getPhiAngle(), false);
    double d = -findD(i.getMid(), j.getStart(), i.getPhiAngle(), true);
    double e = findE(a, b);
    double l_ij = findGeometricIntegral(a, b, c, d, e, j.getLength());
    return l_ij;
}

double PanelMethods::findMx(const Panel &panel, const Point &point)
{
    double a = findA(point, panel.getMid(), panel.getPhiAngle());
    double b = findB(point, panel.getMid());
    double c = findC(panel.getPhiAngle(), 0, true);
    double d = point.x - panel.getMid().x;
    double e = findE(a, b);
    return findGeometricIntegral(a, b, c, d, e, panel.getLength());
}

double PanelMethods::findNx(const Panel &panel, const Point &point)
{
    double a = findA(point, panel.getMid(), panel.getPhiAngle());
    double b = findB(point, panel.getMid());
    double c = findC(panel.getPhiAngle(), 0, false);
    double d = -(point.y - panel.getMid().y);
    double e = findE(a, b);
    return findGeometricIntegral(a, b, c, d, e, panel.getLength());
}

double PanelMethods::findMy(const Panel &panel, const Point &point)
{
    double a = findA(point, panel.getMid(), panel.getPhiAngle());
    double b = findB(point, panel.getMid());
    double c = -findC(panel.getPhiAngle(), 0, false);
    double d = point.y - panel.getMid().y;
    double e = findE(a, b);
    return findGeometricIntegral(a, b, c, d, e, panel.getLength());
}

double PanelMethods::findNy(const Panel &panel, const Point &point)
{
    double a = findA(point, panel.getMid(), panel.getPhiAngle());
    double b = findB(point, panel.getMid());
    double c = findC(panel.getPhiAngle(), 0, true);
    double d = point.x - panel.getMid().x;
    double e = findE(a, b);
    return findGeometricIntegral(a, b, c, d, e, panel.getLength());
}

double PanelMethods::findCp(double velocity)
{
    return 1 - velocity * velocity;
}

Airfoil PanelMethods::computeSourceVortex(const Airfoil &airfoil, double angleOfAttackDegrees)
{
    Airfoil solved{airfoil};
    solved.setAngleOfAttack(angleOfAttackDegrees * M_PI / 180.0);

    int count = solved.size();
    Matrix a(count + 1, count + 1);
    Matrix b(count + 1, 1);
    for (int i = 0; i < count; ++i)
    {
        double sumK = 0.0;
        for (int j = 0; j < count; j++)
            if (i == j)
                a.at(i).at(j) = M_PI;
            else
            {
                a.at(i).at(j) = findIij(solved.at(i), solved.at(j));
                sumK += findJij(solved.at(i), solved.at(j));
            }
        a.at(i).at(count) = -sumK;
        b.at(i).at(0) = -2.0 * M_PI * std::cos(solved.at(i).getBetaAngle());
    }
    double sumL = 0.0;
    for (int i = 0; i < count; ++i)
    {
        double sum = 0.0;
        if (i != 0)
        {
            sum += findJij(solved.front(), solved.at(i));
            sumL += findLij(solved.front(), solved.at(i));
        }
        if (i != count - 1)
        {
            sum += findJij(solved.back(), solved.at(i));
            sumL += findLij(solved.back(), solved.at(i));
        }
        a.at(count).at(i) = sum;
    }
    a.at(count).at(count) = -sumL + 2.0 * M_PI;
    b.at(count).front() = -2.0 * M_PI * (std::sin(solved.front().getBetaAngle()) + std::sin(solved.back().getBetaAngle()));
    Matrix lambdasAndGamma = Matrix::lowerUpperDecomposition(a, b);
    std::vector<double> lambdas(count);
    std::vector<double> gammas(count);
    for (int i = 0; i < count; ++i)
    {
        lambdas[i] = lambdasAndGamma.at(i).front();
        gammas[i] = lambdasAndGamma.back().front();
    }
    solved.setLambdas(lambdas);
    solved.setGammas(gammas);
    for (int i = 0; i < count; ++i)
    {
        double sumJ = 0.0;
        double sumL = 0.0;
        for (int j = 0; j < count; j++)
        {
            if (i != j)
            {
                sumJ += solved[j].lambda * findJij(solved[i], solved[j]);
                sumL += findLij(solved[i], solved[j]);
            }
            double v = std::sin(solved[i].getBetaAngle()) + (1.0 / (2.0 * M_PI)) * sumJ + solved[i].gamma / 2.0 - (solved[i].gamma / (2.0 * M_PI)) * sumL;
            double cp = findCp(v);
            solved[i].coefficientOfPressure = cp;
        }
    }
    return solved;
}

Vector PanelMethods::computeStreamline(const std::vector<Panel> &panels, const Point &point)
{
    double lambdaMxSum = 0.0;
    double gammaNxSum = 0.0;
    double lambdaMySum = 0.0;
    double gammaNySum = 0.0;
    for (int i = 0; i < panels.size(); ++i)
    {
        lambdaMxSum += panels.at(i).lambda * findMx(panels.at(i), point) / (2.0 * M_PI);
        gammaNxSum += -panels.at(i).gamma * findNx(panels.at(i), point) / (2.0 * M_PI);
        lambdaMySum += panels.at(i).lambda * findMy(panels.at(i), point) / (2.0 * M_PI);
        gammaNySum += -panels.at(i).gamma * findNy(panels.at(i), point) / (2.0 * M_PI);
    }
    double vx = std::cos(panels.front().alphaAngle) + lambdaMxSum + gammaNxSum;
    double vy = std::sin(panels.front().alphaAngle) + lambdaMySum + gammaNySum;
    Vector v{Point::zero(), Point{vx, vy, 0.0}};
    double magnitude = v.getMagnitude();
    double cp = 1 - magnitude * magnitude;
    return Vector{Point::zero(), Point{vx, vy, cp}};
}