#include "airfoil.h"

#include <cmath>

#include <gtest/gtest.h>

#include "panel.h"
#include "point.h"

using aerodynamics::Airfoil;
using aerodynamics::Panel;
using geometry::Point;

namespace
{
    TEST(Airfoil, Panel)
    {
        Point pt1{2.0, 2.0, 0.0};
        Point pt2{-2.0, 2.0, 0};
        Point pt3{-2.0, -2.0, 0.0};
        Point pt4{2.0, -2.0, 0};
        Panel p1{pt1, pt2};
        Panel p2{pt2, pt3};
        Panel p3{pt3, pt4};
        Panel p4{pt4, pt1};
        Airfoil a({p1, p2, p3, p4});
        ASSERT_EQ(a.size(), 4);
    }

    TEST(Airfoil, setAngleOfAttack)
    {
        Point pt1{2.0, 2.0, 0.0};
        Point pt2{-2.0, 2.0, 0};
        Point pt3{-2.0, -2.0, 0.0};
        Point pt4{2.0, -2.0, 0};
        Panel p1{pt1, pt2};
        Panel p2{pt2, pt3};
        Panel p3{pt3, pt4};
        Panel p4{pt4, pt1};
        Airfoil a({p1, p2, p3, p4});
        a.setAngleOfAttack(10);
        for (Panel panel : a)
            ASSERT_FLOAT_EQ(panel.alphaAngle, 10);
    }

    TEST(Airfoil, setGammas)
    {
        Point pt1{2.0, 2.0, 0.0};
        Point pt2{-2.0, 2.0, 0};
        Point pt3{-2.0, -2.0, 0.0};
        Point pt4{2.0, -2.0, 0};
        Panel p1{pt1, pt2};
        Panel p2{pt2, pt3};
        Panel p3{pt3, pt4};
        Panel p4{pt4, pt1};
        Airfoil a({p1, p2, p3, p4});
        std::vector<double> gammas({1, 2, 3, 4});
        a.setGammas(gammas);
        for (int i = 0; i < a.size(); i++)
            ASSERT_FLOAT_EQ(a[i].gamma, gammas[i]);
    }

    TEST(Airfoil, setLambdas)
    {
        Point pt1{2.0, 2.0, 0.0};
        Point pt2{-2.0, 2.0, 0};
        Point pt3{-2.0, -2.0, 0.0};
        Point pt4{2.0, -2.0, 0};
        Panel p1{pt1, pt2};
        Panel p2{pt2, pt3};
        Panel p3{pt3, pt4};
        Panel p4{pt4, pt1};
        Airfoil a({p1, p2, p3, p4});
        std::vector<double> lambdas{1, 2, 3, 4};
        a.setLambdas(lambdas);
        for (int i = 0; i < a.size(); i++)
            ASSERT_FLOAT_EQ(a[i].lambda, lambdas[i]);
    }

    TEST(Airfoil, getCoefficientOfLift)
    {
        Point pt1{2.0, 2.0, 0.0};
        Point pt2{-2.0, 2.0, 0};
        Point pt3{-2.0, -2.0, 0.0};
        Point pt4{2.0, -2.0, 0};
        Panel p1{pt1, pt2};
        p1.coefficientOfPressure = 1;
        Panel p2{pt2, pt3};
        p2.coefficientOfPressure = 2;
        Panel p3{pt3, pt4};
        p3.coefficientOfPressure = 3;
        Panel p4{pt4, pt1};
        p4.coefficientOfPressure = 4;
        Airfoil a({p1, p2, p3, p4});
        a.setAngleOfAttack(M_PI_4);
        ASSERT_FLOAT_EQ(a.getCoefficientOfLift(), -8);
    }

    TEST(Airfoil, getCoefficientOfDrag)
    {
        Point pt1{2.0, 2.0, 0.0};
        Point pt2{-2.0, 2.0, 0};
        Point pt3{-2.0, -2.0, 0.0};
        Point pt4{2.0, -2.0, 0};
        Panel p1{pt1, pt2};
        p1.coefficientOfPressure = 1;
        Panel p2{pt2, pt3};
        p2.coefficientOfPressure = 2;
        Panel p3{pt3, pt4};
        p3.coefficientOfPressure = 3;
        Panel p4{pt4, pt1};
        p4.coefficientOfPressure = 4;
        Airfoil a({p1, p2, p3, p4});
        a.setAngleOfAttack(M_PI_4);
        ASSERT_FLOAT_EQ(a.getCoefficientOfDrag(), -8);
    }

    TEST(Airfoil, getCoefficientOfMoment)
    {
        Point pt1{2.0, 2.0, 0.0};
        Point pt2{-2.0, 2.0, 0};
        Point pt3{-2.0, -2.0, 0.0};
        Point pt4{2.0, -2.0, 0};
        Panel p1{pt1, pt2};
        p1.coefficientOfPressure = 1;
        Panel p2{pt2, pt3};
        p2.coefficientOfPressure = 2;
        Panel p3{pt3, pt4};
        p3.coefficientOfPressure = 3;
        Panel p4{pt4, pt1};
        p4.coefficientOfPressure = 4;
        Airfoil a({p1, p2, p3, p4});
        a.setAngleOfAttack(M_PI_4);
        ASSERT_FLOAT_EQ(a.getCoefficientOfMoment(), -2);
    }

    TEST(Airfoil, getRotatedPanels)
    {
        Point pt1{2.0, 2.0, 0.0};
        Point pt2{-2.0, 2.0, 0};
        Point pt3{-2.0, -2.0, 0.0};
        Point pt4{2.0, -2.0, 0};
        Panel p1{pt1, pt2};
        p1.coefficientOfPressure = 1;
        Panel p2{pt2, pt3};
        p2.coefficientOfPressure = 2;
        Panel p3{pt3, pt4};
        p3.coefficientOfPressure = 3;
        Panel p4{pt4, pt1};
        p4.coefficientOfPressure = 4;
        Airfoil a({p1, p2, p3, p4});
        a.setAngleOfAttack(M_PI_4);
        std::vector<Panel> r = a.getRotatedPanels();
        ASSERT_FLOAT_EQ(r[0].getStart().x, 2.82842712474619);
        ASSERT_FLOAT_EQ(r[0].getStart().y, 2.220446049250313E-16);
        ASSERT_FLOAT_EQ(r[0].getStart().z, 0);
        ASSERT_FLOAT_EQ(r[1].getStart().x, -2.220446049250313E-16);
        ASSERT_FLOAT_EQ(r[1].getStart().y, 2.82842712474619);
        ASSERT_FLOAT_EQ(r[1].getStart().z, 0);
        ASSERT_FLOAT_EQ(r[2].getStart().x, -2.82842712474619);
        ASSERT_FLOAT_EQ(r[2].getStart().y, -2.220446049250313E-16);
        ASSERT_FLOAT_EQ(r[2].getStart().z, 0);
        ASSERT_FLOAT_EQ(r[3].getStart().x, 2.220446049250313E-16);
        ASSERT_FLOAT_EQ(r[3].getStart().y, -2.82842712474619);
        ASSERT_FLOAT_EQ(r[3].getStart().z, 0);
    }

    TEST(Airfoil, getAerodynamicCenter)
    {
        Airfoil a = Airfoil::getNACA4Airfoil(200, 0, 0, 12, false, 0);
        Point point = a.getAerodynamicCenter();
        ASSERT_FLOAT_EQ(point.x, 0.25);
        ASSERT_FLOAT_EQ(point.y, 0.0);
        ASSERT_FLOAT_EQ(point.z, 0.0);
    }

    TEST(Airfoil, getRotatedAerodynamicCenter)
    {
        Airfoil a = Airfoil::getNACA4Airfoil(200, 0, 0, 12, false, 0);
        a.setAngleOfAttack(M_PI_4);
        Point point = a.getRotatedAerodynamicCenter();
        ASSERT_FLOAT_EQ(point.x, 0.17677669529663689);
        ASSERT_FLOAT_EQ(point.y, -0.17677669529663687);
        ASSERT_FLOAT_EQ(point.z, 0.0);
    }

    TEST(Airfoil, getNACA4Airfoil)
    {
        Airfoil a = Airfoil::getNACA4Airfoil(200, 2, 40, 12, false, 0);
        ASSERT_FLOAT_EQ(a[0].getStart().x, 0.99991618604);
        ASSERT_FLOAT_EQ(a[0].getStart().y, -0.0012572093);
        ASSERT_FLOAT_EQ(a[0].getStart().z, 0);
        ASSERT_FLOAT_EQ(a[100].getStart().x, 0);
        ASSERT_FLOAT_EQ(a[100].getStart().y, 0);
        ASSERT_FLOAT_EQ(a[100].getStart().z, 0);
        ASSERT_FLOAT_EQ(a[199].getEnd().x, 1.0000838140);
        ASSERT_FLOAT_EQ(a[199].getEnd().y, 0.0012572093);
        ASSERT_FLOAT_EQ(a[199].getEnd().z, 0);
    }

    TEST(Airfoil, getNACA4AirfoilInvalidArguments)
    {
        ASSERT_THROW(Airfoil::getNACA4Airfoil(200, -1, 40, 12, false, 0), std::invalid_argument);
        ASSERT_THROW(Airfoil::getNACA4Airfoil(200, 10, 40, 12, false, 0), std::invalid_argument);
        ASSERT_THROW(Airfoil::getNACA4Airfoil(200, 2, -1, 12, false, 0), std::invalid_argument);
        ASSERT_THROW(Airfoil::getNACA4Airfoil(200, 2, 91, 12, false, 0), std::invalid_argument);
        ASSERT_THROW(Airfoil::getNACA4Airfoil(200, 2, 40, 0, false, 0), std::invalid_argument);
        ASSERT_THROW(Airfoil::getNACA4Airfoil(200, 2, 40, 41, false, 0), std::invalid_argument);
        ASSERT_THROW(Airfoil::getNACA4Airfoil(19, 2, 40, 12, false, 0), std::invalid_argument);
        ASSERT_THROW(Airfoil::getNACA4Airfoil(201, 2, 40, 12, false, 0), std::invalid_argument);
        ASSERT_THROW(Airfoil::getNACA4Airfoil(101, 2, 40, 12, false, 0), std::invalid_argument);
    }
} // namespace