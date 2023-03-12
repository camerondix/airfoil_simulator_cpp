#include "point_cloud.h"

#include <gtest/gtest.h>

#include "point.h"

using geometry::Point;
using geometry::PointCloud;

namespace
{
    TEST(PointCloud, PointCloudDefault)
    {
        PointCloud c(3);
        ASSERT_EQ(c[0], Point::zero());
        ASSERT_EQ(c[1], Point::zero());
        ASSERT_EQ(c[2], Point::zero());
        ASSERT_EQ(c.size(), 3);
    }

    TEST(PointCloud, PointCloudPoints)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{3.25, 2.5, 1.75};
        Point p3{2.25, 1.5, 3.75};
        PointCloud c{{p1, p2, p3}};
        ASSERT_EQ(c[0], p1);
        ASSERT_EQ(c[1], p2);
        ASSERT_EQ(c[2], p3);
        ASSERT_EQ(c.size(), 3);
    }
} // namespace