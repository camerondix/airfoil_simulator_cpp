#include "line_segment.h"

#include <gtest/gtest.h>

#include "point.h"
#include "vector.h"

using geometry::LineSegment;
using geometry::Point;
using geometry::Vector;

namespace
{
    TEST(LineSegment, Point)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{3.25, 2.5, 1.75};
        LineSegment l{p1, p2};
        ASSERT_EQ(l.getStart(), p1);
        ASSERT_EQ(l.getEnd(), p2);
    }

    TEST(LineSegment, getStart)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{3.25, 2.5, 1.75};
        LineSegment l{p1, p2};
        ASSERT_EQ(l.getStart(), p1);
    }

    TEST(LineSegment, getEnd)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{3.25, 2.5, 1.75};
        LineSegment l{p1, p2};
        ASSERT_EQ(l.getEnd(), p2);
    }

    TEST(LineSegment, getMid)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{3.25, 2.5, 1.75};
        LineSegment l{p1, p2};
        Point m = l.getMid();
        ASSERT_FLOAT_EQ(m.x, 2.25);
        ASSERT_FLOAT_EQ(m.y, 2.5);
        ASSERT_FLOAT_EQ(m.z, 2.75);
    }

    TEST(LineSegment, getDelta)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{3.25, 2.5, 1.75};
        LineSegment l{p1, p2};
        Point m = l.getMid();
        ASSERT_FLOAT_EQ(m.x, 2.25);
        ASSERT_FLOAT_EQ(m.y, 2.5);
        ASSERT_FLOAT_EQ(m.z, 2.75);
    }

    TEST(LineSegment, rotate)
    {
        Point p1{1.25, 2.5, 3.75};
        Point p2{3.25, 2.5, 1.75};
        LineSegment l{p1, p2};
        Vector v{Point::zero(), Point{-1.0, 2.0, 3.0}};
        LineSegment r = l.rotate(10, v);
        Point s = r.getStart();
        Point e = r.getEnd();
        ASSERT_FLOAT_EQ(s.x, -3.0192731924989085);
        ASSERT_FLOAT_EQ(s.y, 0.7527205566940294);
        ASSERT_FLOAT_EQ(s.z, 3.491761898037677);
        ASSERT_FLOAT_EQ(e.x, -3.064935203145218);
        ASSERT_FLOAT_EQ(e.y, -1.930658507427681);
        ASSERT_FLOAT_EQ(e.z, 2.5987939372367146);
    }
} // namespace