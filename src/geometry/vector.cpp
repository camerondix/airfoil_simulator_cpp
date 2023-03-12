#include "vector.h"

#include <cmath>

#include "point.h"

using geometry::Vector;

using geometry::Point;

Vector::Vector(const Point &start, const Point &end)
{
    this->x = end.x - start.x;
    this->y = end.y - start.y;
    this->z = end.z - start.z;
}

/// @brief scalar vector multiplication
/// @param lhs scalar
/// @param rhs vector
/// @return vector magnified by scalar
Vector geometry::operator*(double lhs, const Vector &rhs)
{
    return Vector{Point::zero(), Point{lhs * rhs.x, lhs * rhs.y, lhs * rhs.z}};
}

double Vector::getMagnitude() const
{
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector Vector::getUnit() const
{
    return 1.0 / getMagnitude() * Vector{*this};
}

Vector Vector::xUnit()
{
    return Vector{Point::zero(), Point{1, 0, 0}};
}

Vector Vector::yUnit()
{
    return Vector{Point::zero(), Point{0, 1, 0}};
}

Vector Vector::zUnit()
{
    return Vector{Point::zero(), Point{0, 0, 1}};
}