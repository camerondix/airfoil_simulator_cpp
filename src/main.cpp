#include <cmath>
#include <map>
#include <iomanip>
#include <sstream>
#include <vector>

#include "../matplotlibcpp.h"

#include "airfoil.h"
#include "panel.h"
#include "panel_methods.h"
#include "point.h"
#include "polygon.h"
#include "vector.h"

using std::map;
using std::string;
using std::to_string;
using std::vector;

namespace plt = matplotlibcpp;

using aerodynamics::Airfoil;
using aerodynamics::Panel;
using aerodynamics::PanelMethods;
using geometry::Point;
using geometry::Polygon;
using geometry::Vector;

/// @brief Plots a free-body diagram, velocity vector field, and contour plot
int main()
{
    int pointCount = 100;                 // [20 200] even number
    double maxCamberPercent = 2;          // [0 9.5]
    double maxCamberPositionPercent = 40; // [0 90]
    double thicknessPercent = 12;         // [1 40]
    double angleOfAttack = 7;             // Degrees
    int vectorGridLength = 25;
    int vectorGridHeight = 20;

    // Build Airfoil
    Airfoil nacaAirfoil = Airfoil::getNACA4Airfoil(pointCount, maxCamberPercent, maxCamberPositionPercent, thicknessPercent, false, angleOfAttack * M_PI / 180.0);

    // Simulate Airfoil
    nacaAirfoil = PanelMethods::computeSourceVortex(nacaAirfoil, angleOfAttack);
    double lift = nacaAirfoil.getCoefficientOfLift();
    double drag = nacaAirfoil.getCoefficientOfDrag();

    // Rotate the Airfoil
    vector<Panel> rotatedPanels = nacaAirfoil.getRotatedPanels();

    // Find Aerodynamic Center
    Point aerodynamicCenter = nacaAirfoil.getRotatedAerodynamicCenter();

    // Extract Airfoil Points
    vector<double> bodyX(pointCount), bodyY(pointCount);
    vector<Point> point_cloud(pointCount);
    for (int i = 0; i < pointCount; ++i)
    {
        Point start = rotatedPanels[i].getStart();
        bodyX.at(i) = start.x;
        bodyY.at(i) = start.y;
        point_cloud.at(i) = Point(start.x, start.y, 0.0);
    }

    // Create Polygon From Airfoil Points
    Polygon airfoilPolygon(point_cloud);

    // Build Velocity Grid
    int vectorGridSize = vectorGridLength * vectorGridHeight;
    double gridDX = 2.0 / vectorGridLength;
    double gridDY = 1.0 / vectorGridHeight;
    vector<double> gridX(vectorGridSize), gridY(vectorGridSize), gridU(vectorGridSize), gridW(vectorGridSize);
    vector<float> gridZ(vectorGridSize);
    for (int i = vectorGridHeight - 1; i >= 0; i--)
    {
        double y = i * gridDY - 0.5;
        for (int j = 0; j < vectorGridLength; j++)
        {
            int index = i * vectorGridLength + j;
            double x = j * gridDX - 0.5;
            // Ignore the point if it is inside of the airfoil
            if (airfoilPolygon.pointIsInside(Point(x, y, 0.0)))
            {
                gridZ.at(index) = 0;
                continue;
            }
            Vector streamLine = PanelMethods::computeStreamline(rotatedPanels, Point(x, y, 0.0));
            gridX.at(index) = x;
            gridY.at(index) = y;
            gridZ.at(index) = streamLine.z;
            gridU.at(index) = streamLine.x;
            gridW.at(index) = streamLine.y;
        }
    }

    // Generate Plots
    plt::suptitle("NACA " + to_string((int)maxCamberPercent) + to_string((int)maxCamberPositionPercent)[0] + to_string((int)thicknessPercent));

    // Free Body Diagram
    plt::subplot2grid(2, 2, 0, 0);
    plt::axis("off");
    plt::margins(0.0, 0.0);
    plt::set_aspect_equal();
    plt::fill(bodyX, bodyY, map<string, string>({{"color", "#8e8e93"}}));
    plt::plot(vector<double>({aerodynamicCenter.x}), vector<double>({aerodynamicCenter.y}), map<string, string>({{"color", "#30d158"}, {"markersize", "3"}, {"marker", "o"}}));
    double arrowStartOffset = 0.01;
    double maxArrowLength = 0.15;
    double arrowWidth = 0.02;
    plt::arrow(aerodynamicCenter.x, aerodynamicCenter.y + arrowStartOffset, 0.0, maxArrowLength, "r", "r", arrowWidth, arrowWidth);
    std::stringstream liftStream;
    liftStream << std::fixed << std::setprecision(2) << lift;
    plt::text(aerodynamicCenter.x + arrowStartOffset, aerodynamicCenter.y + maxArrowLength, liftStream.str());
    plt::arrow(aerodynamicCenter.x + arrowStartOffset, aerodynamicCenter.y, maxArrowLength * drag / lift, 0.0, "r", "r", arrowWidth, arrowWidth);
    std::stringstream dragStream;
    dragStream << std::fixed << std::setprecision(2) << drag;
    plt::text(aerodynamicCenter.x + arrowWidth * 2 + maxArrowLength * drag / lift, aerodynamicCenter.y + arrowStartOffset, dragStream.str());

    // Surface Pressure Arrows
    plt::subplot2grid(2, 2, 0, 1);
    plt::axis("off");
    plt::margins(0.0, 0.0);
    plt::set_aspect_equal();
    plt::fill(bodyX, bodyY, map<string, string>({{"color", "#000000"}}));
    for (int i = 0; i < rotatedPanels.size(); ++i)
    {
        Panel panel = rotatedPanels.at(i);
        Point mid = panel.getMid();
        Vector normalUnit = Vector(Point::zero(), panel.getDelta().rotate(M_PI_2, Vector::zUnit())).getUnit();
        double x, y, dX, dY;
        if (panel.coefficientOfPressure > 0)
        {
            Point nearToSurface = mid + arrowStartOffset * 3 * normalUnit;
            Point awayFromSurface = nearToSurface + (abs(panel.coefficientOfPressure) / 10.0) * normalUnit;
            Vector delta = nearToSurface - awayFromSurface;
            plt::arrow(awayFromSurface.x, awayFromSurface.y, delta.x, delta.y, "b", "b", arrowWidth, arrowWidth);
        }
        else
        {
            Point nearToSurface = mid + arrowStartOffset * normalUnit;
            Point awayFromSurface = nearToSurface + (abs(panel.coefficientOfPressure) / 10.0) * normalUnit;
            Vector delta = awayFromSurface - nearToSurface;
            plt::arrow(nearToSurface.x, nearToSurface.y, delta.x, delta.y, "r", "r", arrowWidth, arrowWidth);
        }
    }

    // Velocity Vectors
    plt::subplot2grid(2, 2, 1, 0);
    plt::axis("off");
    plt::margins(0.0, 0.0);
    plt::set_aspect_equal();
    plt::fill(bodyX, bodyY, map<string, string>({{"color", "#000000"}}));
    plt::quiver(gridX, gridY, gridU, gridW, map<string, string>({{"color", "#32ade6"}}));

    // Pressure Contour
    plt::subplot2grid(2, 2, 1, 1);
    plt::axis("off");
    plt::margins(0.0, 0.0);
    plt::set_aspect_equal();
    vector<double> imageBodyX(bodyX.size()), imageBodyY(bodyY.size());
    for (int i = 0; i < bodyX.size(); ++i)
        imageBodyX.at(i) = vectorGridLength / 2.0 * (bodyX.at(i) + 0.5);
    for (int i = 0; i < bodyY.size(); ++i)
        imageBodyY.at(i) = vectorGridHeight * (bodyY.at(i) + 0.5);
    plt::fill(imageBodyX, imageBodyY, map<string, string>({{"color", "#000000"}}));
    const float *ptr = &(gridZ[0]);
    PyObject *mat;
    plt::imshow(ptr, vectorGridHeight, vectorGridLength, 1, map<string, string>({{"cmap", "Spectral"}, {"origin", "lower"}, {"aspect", to_string(0.5)}}), &mat);
    plt::colorbar(mat);

    // Show Plots
    plt::show();

    return 0;
}