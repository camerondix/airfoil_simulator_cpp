#include "polygon.h"

#include <gtest/gtest.h>

#include "point_cloud.h"
#include "point.h"

using geometry::Point;
using geometry::PointCloud;
using geometry::Polygon;

namespace
{
    TEST(Polygon, PolygonPoints)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{3.25, 2.5, 1.75};
        Point p3{2.25, 1.5, 3.75};
        Polygon p{{{p1, p2, p3}}};
        ASSERT_EQ(p[0], p1);
        ASSERT_EQ(p[1], p2);
        ASSERT_EQ(p[2], p3);
        ASSERT_EQ(p.size(), 3);
    }

    TEST(Polygon, pointIsInsideTrue)
    {
        Point p1{2.0, 2.0, 0.0};
        Point p2{-2.0, 2.0, 0};
        Point p3{-2.0, -2.0, 0.0};
        Point p4{2.0, -2.0, 0};
        Polygon p{{{p1, p2, p3, p4}}};
        Point point = Point::zero();
        ASSERT_TRUE(p.pointIsInside(point));
    }

    TEST(Polygon, pointIsInsideFalse)
    {
        Point p1{2.0, 2.0, 0.0};
        Point p2{-2.0, 2.0, 0};
        Point p3{-2.0, -2.0, 0.0};
        Point p4{2.0, -2.0, 0};
        Polygon p{{{p1, p2, p3, p4}}};
        Point point{0.0, 2.1, 0.0};
        ASSERT_FALSE(p.pointIsInside(point));
    }
} // namespace