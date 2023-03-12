#ifndef AIRFOILS_GEOMETRY_LINESEGMENT_H_
#define AIRFOILS_GEOMETRY_LINESEGMENT_H_

#include "point.h"
#include "vector.h"

namespace geometry
{
    /// @brief a finite line with a start and end point in 3D space
    class LineSegment
    {
    protected:
        geometry::Point mStart;
        geometry::Point mEnd;

    public:
        /// @brief a line segment from start to end point
        /// @param start starting point
        /// @param end ending point
        LineSegment(geometry::Point start, geometry::Point end) : mStart(start), mEnd(end){};

        /// @brief gets the starting point of the line segment
        /// @return starting point
        geometry::Point getStart() const;

        /// @brief gets the ending point of the line segment
        /// @return ending point
        geometry::Point getEnd() const;

        /// @brief gets the mid point of the line segment
        /// @return mid point
        geometry::Point getMid() const;

        /// @brief gets the delta vector of the line segment
        /// @return delta vector
        geometry::Vector getDelta() const;

        /// @brief gets the length of the line segment
        /// @return segment length
        double getLength() const;

        /// @brief performs an axis-angle rotation
        /// @param radians the angle to rotate in radians
        /// @param axis the axis to rotate around
        /// @return rotated line segment
        LineSegment rotate(double radians, const geometry::Vector &axis) const;
    };
} // namespace geometry

#endif