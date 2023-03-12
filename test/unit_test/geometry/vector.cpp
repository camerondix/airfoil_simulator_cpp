#include "vector.h"

#include <gtest/gtest.h>

#include "point.h"

using geometry::Point;
using geometry::Vector;

namespace
{
    TEST(Vector, VectorDefault)
    {
        Point p1{2.5, 3.5, 1.5};
        Point p2{8.25, -2, 4.75};
        Vector v{p1, p2};
        ASSERT_FLOAT_EQ(v.x, 5.75);
        ASSERT_FLOAT_EQ(v.y, -5.5);
        ASSERT_FLOAT_EQ(v.z, 3.25);
    }

    TEST(Vector, multiplicationScalar)
    {
        Vector v{Point::zero(), Point{1, 2, 3}};
        v = 3.5 * v;
        ASSERT_FLOAT_EQ(v.x, 3.5);
        ASSERT_FLOAT_EQ(v.y, 7.0);
        ASSERT_FLOAT_EQ(v.z, 10.5);
    }

    TEST(Vector, getMagnitude)
    {
        Vector v{Point::zero(), Point{1, 2, 3}};
        double m = v.getMagnitude();
        ASSERT_FLOAT_EQ(m, 3.741657);
    }

    TEST(Vector, getUnit)
    {
        Vector v{Point::zero(), Point{1, 2, 3}};
        v = v.getUnit();
        ASSERT_FLOAT_EQ(v.x, 0.26726124);
        ASSERT_FLOAT_EQ(v.y, 0.53452247);
        ASSERT_FLOAT_EQ(v.z, 0.80178374);
        ASSERT_FLOAT_EQ(v.getMagnitude(), 1.0);
    }

    TEST(Vector, xUnit)
    {
        Vector v = Vector::xUnit();
        ASSERT_FLOAT_EQ(v.x, 1.0);
        ASSERT_FLOAT_EQ(v.y, 0.0);
        ASSERT_FLOAT_EQ(v.z, 0.0);
        ASSERT_FLOAT_EQ(v.getMagnitude(), 1.0);
    }

    TEST(Vector, yUnit)
    {
        Vector v = Vector::yUnit();
        ASSERT_FLOAT_EQ(v.x, 0.0);
        ASSERT_FLOAT_EQ(v.y, 1.0);
        ASSERT_FLOAT_EQ(v.z, 0.0);
        ASSERT_FLOAT_EQ(v.getMagnitude(), 1.0);
    }

    TEST(Vector, zUnit)
    {
        Vector v = Vector::zUnit();
        ASSERT_FLOAT_EQ(v.x, 0.0);
        ASSERT_FLOAT_EQ(v.y, 0.0);
        ASSERT_FLOAT_EQ(v.z, 1.0);
        ASSERT_FLOAT_EQ(v.getMagnitude(), 1.0);
    }
} // namespace