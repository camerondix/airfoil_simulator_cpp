#ifndef AIRFOILS_AERODYNAMICS_PANELMETHODS_H_
#define AIRFOILS_AERODYNAMICS_PANELMETHODS_H_

#include <vector>

#include "airfoil.h"
#include "vector.h"
#include "point.h"

namespace aerodynamics
{
    /// @brief methods to solve the flow around an airfoil using source and/or vortex flows
    class PanelMethods
    {
    private:
        static double findA(const geometry::Point &point1, const geometry::Point &point2, double phi);
        static double findB(const geometry::Point &point1, const geometry::Point &point2);
        static double findC(double angle1, double angle2, bool reverse);
        static double findD(const geometry::Point &point1, const geometry::Point &point2, double phi, bool reverse);
        static double findE(double a, double b);
        static double findGeometricIntegral(double a, double b, double c, double d, double e, double s);
        static double findIij(const aerodynamics::Panel &i, const aerodynamics::Panel &j);
        static double findJij(const aerodynamics::Panel &i, const aerodynamics::Panel &j);
        static double findLij(const aerodynamics::Panel &i, const aerodynamics::Panel &j);
        static double findMx(const aerodynamics::Panel &panel, const geometry::Point &point);
        static double findNx(const aerodynamics::Panel &panel, const geometry::Point &point);
        static double findMy(const aerodynamics::Panel &panel, const geometry::Point &point);
        static double findNy(const aerodynamics::Panel &panel, const geometry::Point &point);
        static double findCp(double velocity);

    public:
        /// @brief uses a combination of source and vortex flows to solve for the flow around the airfoil
        /// @tparam count panel count
        /// @param airfoil airfoil geometry to solve for
        /// @param angleOfAttackDegrees angle of attack of the airfoil in degrees
        /// @return an airfoil with source strengths, vortex strengths, and pressure coefficients set
        static aerodynamics::Airfoil computeSourceVortex(const aerodynamics::Airfoil &airfoil, double angleOfAttackDegrees);

        /// @brief computes the freestream gradient at a point determined by the airfoil body
        /// @tparam count panel count
        /// @param airfoil solved airfoil geometry
        /// @param point the point of interest
        /// @return a vector where x and y store the direction of the stream and z the pressure coefficient
        static geometry::Vector computeStreamline(const std::vector<aerodynamics::Panel> &panels, const geometry::Point &point);
    };
} // namespace aerodynamics

#endif
