#include "panel_methods.h"

#include <gtest/gtest.h>

#include "airfoil.h"
#include "point.h"
#include "vector.h"

using aerodynamics::Airfoil;
using aerodynamics::PanelMethods;
using geometry::Point;
using geometry::Vector;

namespace
{
    TEST(PanelMethods, computeSourceVortex)
    {
        Airfoil a = Airfoil::getNACA4Airfoil(200, 2, 40, 12, false, 0);
        Airfoil b = PanelMethods::computeSourceVortex(a, 2);
        ASSERT_FLOAT_EQ(b.getCoefficientOfLift(), 0.49225303229453155);
        ASSERT_FLOAT_EQ(b.getCoefficientOfDrag(), 0.01698688438654304);
        ASSERT_FLOAT_EQ(b.getCoefficientOfMoment(), -0.05526644272468364);
    }

    TEST(PanelMethods, computeStreamline)
    {
        Airfoil a = Airfoil::getNACA4Airfoil(200, 2, 40, 12, false, 0);
        Airfoil b = PanelMethods::computeSourceVortex(a, 2);
        Vector v = PanelMethods::computeStreamline(b, Point{1, 1, 1});
        ASSERT_FLOAT_EQ(v.x, 1.0336661);
        ASSERT_FLOAT_EQ(v.y, 0.0094638597);
        ASSERT_FLOAT_EQ(v.z, -0.06855532416961796);
    }
} // namespace