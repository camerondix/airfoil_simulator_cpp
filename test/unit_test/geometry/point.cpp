#include "point.h"

#include <gtest/gtest.h>

#include "vector.h"

using geometry::Point;
using geometry::Vector;

namespace
{
    TEST(Point, PointDefault)
    {
        Point p;
        ASSERT_FLOAT_EQ(p.x, 0.0);
        ASSERT_FLOAT_EQ(p.y, 0.0);
        ASSERT_FLOAT_EQ(p.z, 0.0);
    }

    TEST(Point, PointXYZ)
    {
        double x = 1.1;
        double y = 2.2;
        double z = 3.3;
        Point p{x, y, z};
        ASSERT_FLOAT_EQ(p.x, x);
        ASSERT_FLOAT_EQ(p.y, y);
        ASSERT_FLOAT_EQ(p.z, z);
    }

    TEST(Point, equalTrue)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{1.25, 2.5, 3.75};
        ASSERT_TRUE(p1 == p2);
    }

    TEST(Point, equalFalseX)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{1.24, 2.5, 3.75};
        ASSERT_FALSE(p1 == p2);
    }

    TEST(Point, equalFalseY)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{1.24, 2.49, 3.75};
        ASSERT_FALSE(p1 == p2);
    }

    TEST(Point, equalFalseZ)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{1.24, 2.49, 3.74};
        ASSERT_FALSE(p1 == p2);
    }

    TEST(Point, notEqualFalse)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{1.25, 2.5, 3.75};
        ASSERT_FALSE(p1 != p2);
    }

    TEST(Point, notEqualTrueX)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{1.24, 2.5, 3.75};
        ASSERT_TRUE(p1 != p2);
    }

    TEST(Point, notEqualTrueY)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{1.24, 2.49, 3.75};
        ASSERT_TRUE(p1 != p2);
    }

    TEST(Point, notEqualTrueZ)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{1.24, 2.49, 3.74};
        ASSERT_TRUE(p1 != p2);
    }

    TEST(Point, subtraction)
    {
        Point p1{2.5, 3.5, 1.5};
        Point p2{8.25, -2, 4.75};
        Vector v = p2 - p1;
        ASSERT_FLOAT_EQ(v.x, 5.75);
        ASSERT_FLOAT_EQ(v.y, -5.5);
        ASSERT_FLOAT_EQ(v.z, 3.25);
    }

    TEST(Point, addition)
    {
        Point p1{2.5, 3.5, 1.5};
        Point p2{8.25, -2, 4.75};
        Point p = p1 + p2;
        ASSERT_FLOAT_EQ(p.x, 10.75);
        ASSERT_FLOAT_EQ(p.y, 1.5);
        ASSERT_FLOAT_EQ(p.z, 6.25);
    }

    TEST(Point, rotate)
    {
        Point p{1.0, 2.0, 3.0};
        Vector v{Point::zero(), Point{3.0, 2.0, 1.0}};
        Point r = p.rotate(10.0, v);
        ASSERT_FLOAT_EQ(r.x, 2.5202130023387523);
        ASSERT_FLOAT_EQ(r.y, 2.1122680451678422);
        ASSERT_FLOAT_EQ(r.z, -1.7851750973519422);
    }

    TEST(Point, zero)
    {
        Point p = Point::zero();
        ASSERT_FLOAT_EQ(p.x, 0.0);
        ASSERT_FLOAT_EQ(p.y, 0.0);
        ASSERT_FLOAT_EQ(p.z, 0.0);
    }
} // namespace