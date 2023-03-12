#include "point.h"

#include <cmath>

#include "vector.h"
#include "matrix.h"

using geometry::Point;

using geometry::Vector;
using linear_algebra::Matrix;

bool Point::operator==(const Point &rhs) const
{
    // Compare x, y, and z individually
    return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool Point::operator!=(const Point &rhs) const
{
    return !(*this == rhs);
}

Vector Point::operator-(const Point &rhs) const
{
    return Vector{rhs, *this};
}

Point Point::operator+(const Point &rhs) const
{
    // Add x, y, and z individually
    return Point{this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
}

Point Point::rotate(double radians, const Vector &axis) const
{
    // If no rotating is necessary save on resources
    if (radians == 0)
        return *this;

    // Create the identity matrix
    Matrix identity(Matrix::identity(3));

    // Unitize the axis of rotation
    Vector unit = axis.getUnit();

    // Construct the rotation matrix
    Matrix w(3, 3);
    w.at(0).at(1) = -unit.z;
    w.at(0).at(2) = unit.y;
    w.at(1).at(0) = unit.z;
    w.at(1).at(2) = -unit.x;
    w.at(2).at(0) = -unit.y;
    w.at(2).at(1) = unit.x;

    // Rodrigues' rotation formula
    // R = I + sin * W + (1 - cos) * W^2
    Matrix r = identity + sin(radians) * w + (1.0 - cos(radians)) * (w * w);
    Matrix v(*this);
    // P = R * V
    Matrix p = r * v;

    return p.toPoint();
}

Point Point::zero()
{
    return Point{0, 0, 0};
}