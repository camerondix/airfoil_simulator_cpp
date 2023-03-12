#include "panel.h"

#include <math.h>

#include <gtest/gtest.h>

#include "line_segment.h"
#include "point.h"
#include "vector.h"

using aerodynamics::Panel;
using geometry::LineSegment;
using geometry::Point;
using geometry::Vector;

namespace
{
    TEST(Panel, Point)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        ASSERT_EQ(l.getStart(), p1);
        ASSERT_EQ(l.getEnd(), p2);
        ASSERT_FLOAT_EQ(l.alphaAngle, 0.0);
        ASSERT_FLOAT_EQ(l.coefficientOfPressure, 0.0);
        ASSERT_FLOAT_EQ(l.gamma, 0.0);
        ASSERT_FLOAT_EQ(l.lambda, 0.0);
    }

    TEST(Panel, getPhiAngle)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        ASSERT_FLOAT_EQ(l.getPhiAngle(), 5.724585991836024);
    }

    TEST(Panel, getDeltaAngle)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        ASSERT_FLOAT_EQ(l.getDeltaAngle(), 1.0121970114513346);
    }

    TEST(Panel, getBetaAngle0Alpha)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        ASSERT_FLOAT_EQ(l.getBetaAngle(), 1.0121970114513346);
    }

    TEST(Panel, getBetaAngle45Alpha)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        l.alphaAngle = M_PI_4;
        ASSERT_FLOAT_EQ(l.getBetaAngle(), 0.22679884805388628);
    }

    TEST(Panel, getCoefficientOfNormalForce0Alpha)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        l.coefficientOfPressure = 10;
        ASSERT_FLOAT_EQ(l.getCoefficientOfNormalForce(), -20);
    }

    TEST(Panel, getCoefficientOfNormalForce45Alpha)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        l.alphaAngle = M_PI_4;
        l.coefficientOfPressure = 10;
        ASSERT_FLOAT_EQ(l.getCoefficientOfNormalForce(), -5.3033008588991155);
    }

    TEST(Panel, getCoefficientOfAxialForce0Alpha)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        l.coefficientOfPressure = 10;
        ASSERT_FLOAT_EQ(l.getCoefficientOfAxialForce(), -12.5);
    }

    TEST(Panel, getCoefficientOfAxialForce45Alpha)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        l.alphaAngle = M_PI_4;
        l.coefficientOfPressure = 10;
        ASSERT_FLOAT_EQ(l.getCoefficientOfAxialForce(), -22.98097038856279);
    }

    TEST(Panel, getRotatedPanel)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        l.alphaAngle = M_PI_4;
        l.gamma = 1;
        l.lambda = 2;
        l.coefficientOfPressure = 10;
        Panel r = l.getRotatedPanel();
        Point s = r.getStart();
        Point e = r.getEnd();
        ASSERT_FLOAT_EQ(s.x, 3.5355339059327373);
        ASSERT_FLOAT_EQ(s.y, 1.7677669529663689);
        ASSERT_FLOAT_EQ(s.z, 0);
        ASSERT_FLOAT_EQ(e.x, 4.065863991822648);
        ASSERT_FLOAT_EQ(e.y, -0.5303300858899105);
        ASSERT_FLOAT_EQ(e.z, 0);
        ASSERT_FLOAT_EQ(r.alphaAngle, 0);
        ASSERT_FLOAT_EQ(r.coefficientOfPressure, 10);
        ASSERT_FLOAT_EQ(r.gamma, 1);
        ASSERT_FLOAT_EQ(r.lambda, 2);
    }

    TEST(Panel, rotate)
    {
        Point p1{1.25, 3.75, 0};
        Point p2{3.25, 2.5, 0};
        Panel l{p1, p2};
        l.alphaAngle = M_PI_4;
        l.gamma = 1;
        l.lambda = 2;
        l.coefficientOfPressure = 10;
        Panel r = l.rotate(10, Vector::zUnit());
        Point s = r.getStart();
        Point e = r.getEnd();
        ASSERT_FLOAT_EQ(s.x, 0.9912397544895715);
        ASSERT_FLOAT_EQ(s.y, -3.8265446226484094);
        ASSERT_FLOAT_EQ(s.z, 0);
        ASSERT_FLOAT_EQ(e.x, -1.366929692275046);
        ASSERT_FLOAT_EQ(e.y, -3.8657474330815838);
        ASSERT_FLOAT_EQ(e.z, 0);
        ASSERT_FLOAT_EQ(r.alphaAngle, 0);
        ASSERT_FLOAT_EQ(r.coefficientOfPressure, 10);
        ASSERT_FLOAT_EQ(r.gamma, 1);
        ASSERT_FLOAT_EQ(r.lambda, 2);
    }
} // namespace