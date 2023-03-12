#ifndef AIRFOILS_GEOMETRY_POLYGON_H_
#define AIRFOILS_GEOMETRY_POLYGON_H_

#include <vector>

#include "point_cloud.h"
#include "point.h"

namespace geometry
{
    /// @brief a 2D polygon made from a cloud of points
    class Polygon : public geometry::PointCloud
    {
    public:
        /// @brief a polygon from a point cloud
        /// @param points the verticies of the polygon
        Polygon(geometry::PointCloud points) : geometry::PointCloud(points){};

        /// @brief determines if the point lies inside the polygon
        /// @param point the point to check
        /// @return the value indicating if the point is inside the bounds of the polygon
        bool pointIsInside(const geometry::Point &point) const;
    };
} // namespace geometry

#endif