#ifndef AIRFOILS_AERODYNAMICS_AIRFOIL_H_
#define AIRFOILS_AERODYNAMICS_AIRFOIL_H_

#include <vector>

#include "panel.h"
#include "point.h"

namespace aerodynamics
{
    /// @brief a 2D cross-section of an airfoil
    class Airfoil : public std::vector<aerodynamics::Panel>
    {
    public:
        /// @brief an airfoil with no intial panels
        Airfoil(int panelCount) : std::vector<aerodynamics::Panel>(panelCount){};

        /// @brief an airfoil with initial panels
        /// @param panels panels of airfoil in clock-wise order
        Airfoil(std::vector<aerodynamics::Panel> panels) : std::vector<aerodynamics::Panel>(panels){};

        /// @brief sets the angle of attack of the airfoil
        /// @param radians angle in radians
        void setAngleOfAttack(double radians);

        /// @brief sets the vortex strength of the panels
        /// @param gammas the vortex strengths of the panels that match by index
        void setGammas(std::vector<double> gammas);

        /// @brief sets the source strength of the panels
        /// @param lambdas the source strengths of the panels that match by index
        void setLambdas(std::vector<double> lambdas);

        /// @brief gets the lift coefficient of the airfoil after coefficients of pressure have been set
        /// @return non-dimensional lift coefficient
        double getCoefficientOfLift() const;

        /// @brief gets the drag coefficient of the airfoil after coefficients of pressure have been set
        /// @return non-dimensional drag coefficient
        double getCoefficientOfDrag() const;

        /// @brief gets the moment coefficient of the airfoil after coefficients of pressure have been set
        /// @return non-dimensional moment coefficient
        double getCoefficientOfMoment() const;

        /// @brief gets the panels rotated where the angle of attack is seen by the airfoil rather than the flow
        /// @return rotated panels
        std::vector<Panel> getRotatedPanels() const;

        /// @brief gets the aerodynamic center of the airfoil (the quarter-chord)
        /// @return the aerodynamic center
        geometry::Point getAerodynamicCenter() const;

        /// @brief gets the aerodynamic center where the angle of attack is seen by the airfoil rather than the flow
        /// @return the aerodynamic center
        geometry::Point getRotatedAerodynamicCenter() const;

        /// @brief gets a NACA 4-digit airfoil and sets the angle of attack
        /// @param maxCamberPercent maximum camber as a percentage of the chord
        /// @param maxCamberPositionPercent the distance of maximum camber from the airfoil leading edge in tenths of the chord
        /// @param thicknessPercent maximum thickness of the airfoil as percent of the chord
        /// @param closedTrailingEdge indicates if the trailing edge should be closed or open
        /// @param angleOfAttackRadians the angle of attack in radians
        /// @return the constructed airfoil
        static Airfoil getNACA4Airfoil(int pointCount, double maxCamberPercent, double maxCamberPositionPercent, double thicknessPercent, bool closedTrailingEdge, double angleOfAttackRadians);
    };
} // namespace aerodynamics

#endif