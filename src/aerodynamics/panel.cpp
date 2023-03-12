#include "panel.h"

#include <cmath>

#include "point.h"
#include "vector.h"

using aerodynamics::Panel;

using geometry::Point;
using geometry::Vector;

double Panel::getPhiAngle() const
{
    // Find the angle of the panel from the x axis but keep the angle greater than 0 if it goes under
    Vector delta = this->getDelta();
    double angle = std::atan2(delta.y, delta.x);
    if (angle < 0)
        angle += 2.0 * M_PI;
    return angle;
}

double Panel::getDeltaAngle() const
{
    // Add 90 degrees to phi but keep the angle less than 360 if it goes over
    double phi = getPhiAngle();
    return fmod((phi + M_PI_2), (2.0 * M_PI));
}

double Panel::getBetaAngle() const
{
    return getDeltaAngle() - alphaAngle;
}

double Panel::getCoefficientOfNormalForce() const
{
    return -coefficientOfPressure * getLength() * std::sin(getBetaAngle());
}

double Panel::getCoefficientOfAxialForce() const
{
    return -coefficientOfPressure * getLength() * std::cos(getBetaAngle());
}

Panel Panel::getRotatedPanel() const
{
    // Only rotate if it is not already rotated
    return !mIsRotated ? rotate(-alphaAngle, Vector::zUnit()) : *this;
}

Panel Panel::rotate(double radians, const Vector &axis) const
{
    // Rotate start and end points and copy properties
    Point start = mStart.rotate(radians, axis);
    Point end = mEnd.rotate(radians, axis);
    return Panel(start, end, 0, coefficientOfPressure, gamma, lambda, true);
}