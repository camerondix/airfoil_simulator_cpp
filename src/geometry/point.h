#ifndef AIRFOILS_GEOMETRY_POINT_H_
#define AIRFOILS_GEOMETRY_POINT_H_

namespace geometry
{
    class Vector;

    /// @brief a position in 3D space
    class Point
    {
    public:
        double x, y, z;
        /// @brief initializes a 3D point located at (0 ,0 ,0)
        Point() : x(0), y(0), z(0){};

        /// @brief initialize a 3D point located at (x, y, z)
        /// @param x x position
        /// @param y y position
        /// @param z z position
        Point(double x, double y, double z) : x(x), y(y), z(z){};

        /// @brief compares the x, y, and z position in 3D space to determine if they are equal
        /// @param rhs comparison point
        /// @return the value indicating if the positions in space are equal
        bool operator==(const Point &rhs) const;

        /// @brief compares the x, y, and z position in 3D space to determine if they are equal
        /// @param rhs comparison point
        /// @return the value indicating if the positions in space are not equal
        bool operator!=(const Point &rhs) const;

        /// @brief gets the vector from the starting to ending point
        /// @param rhs ending point
        /// @return the vector from lhs point to rhs point
        Vector operator-(const Point &rhs) const;

        /// @brief adds x, y, and z positions individualy and returns that point
        /// @param rhs addition point
        /// @return sum of lhs point and rhs point
        Point operator+(const Point &rhs) const;

        /// @brief performs an axis-angle rotation
        /// @param radians the angle to rotate in radians
        /// @param axis the axis to rotate around
        /// @return rotated point
        Point rotate(double radians, const Vector &axis) const;

        /// @brief gets the origin point at 0,0,0
        /// @return a point at the origin 0,0,0
        static Point zero();
    };
} // namespace geometry

#endif