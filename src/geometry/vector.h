#ifndef AIRFOILS_GEOMETRY_VECTOR_H_
#define AIRFOILS_GEOMETRY_VECTOR_H_

#include "point.h"

namespace geometry
{
    /// @brief a vector in 3D space
    class Vector : public Point
    {
    public:
        Vector() : Point(){};

        /// @brief a vector from start to end point
        /// @param start starting point
        /// @param end ending point
        Vector(const Point &start, const Point &end);

        /// @brief computes the magnitude of the vector
        /// @return vector magnitude
        double getMagnitude() const;

        /// @brief computes the unit vector
        /// @return unitized vector
        Vector getUnit() const;

        /// @brief unit vector along the x axis
        /// @return x axis unit vector
        static Vector xUnit();

        /// @brief unit vector along the y axis
        /// @return y axis unit vector
        static Vector yUnit();

        /// @brief unit vector along the z axis
        /// @return z axis unit vector
        static Vector zUnit();
    };

    Vector operator*(double lhs, const Vector &rhs);
} // namespace geometry

#endif