#ifndef AIRFOILS_GEOMETRY_POINTCLOUD_H_
#define AIRFOILS_GEOMETRY_POINTCLOUD_H_

#include <vector>

#include "point.h"

namespace geometry
{
    /// @brief a cloud of points
    class PointCloud : public std::vector<geometry::Point>
    {
    public:
        /// @brief a point cloud with no initial values
        PointCloud(int size) : std::vector<geometry::Point>(size){};

        /// @brief a point cloud with initial values
        /// @param points initial points
        PointCloud(std::vector<geometry::Point> points) : std::vector<geometry::Point>(points){};
    };
} // namespace geometry

#endif