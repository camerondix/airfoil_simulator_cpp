#ifndef AIRFOILS_AERODYNAMICS_PANEL_H_
#define AIRFOILS_AERODYNAMICS_PANEL_H_

#include "line_segment.h"
#include "point.h"
#include "vector.h"

namespace aerodynamics
{
    /// @brief a 2D line segment specialized to represent a linear segment of an airfoil
    class Panel : public geometry::LineSegment
    {
    private:
        bool mIsRotated;
        Panel(geometry::Point start, geometry::Point end, double alphaAngle, double coefficientOfPressure, double gamma, double lambda, bool isRotated = false) : geometry::LineSegment(start, end), alphaAngle(alphaAngle), coefficientOfPressure(coefficientOfPressure), gamma(gamma), lambda(lambda), mIsRotated(isRotated){};

    public:
        double alphaAngle, coefficientOfPressure, gamma, lambda;

        /// @brief a default zero length panel at the origin
        Panel() : geometry::LineSegment(geometry::Point::zero(), geometry::Point::zero()), mIsRotated(false){};

        /// @brief a panel from start to end
        /// @param start the starting point
        /// @param end the ending point
        Panel(geometry::Point start, geometry::Point end) : geometry::LineSegment(start, end), mIsRotated(false){};

        /// @brief gets the angle from the x axis to the panel
        /// @return angle in radians
        double getPhiAngle() const;

        /// @brief gets the angle from the x axis to the panel normal
        /// @return angle in radians
        double getDeltaAngle() const;

        /// @brief gets the angle from the angle of attack to the panel normal
        /// @return angle in radians
        double getBetaAngle() const;

        /// @brief gets the normal force coefficient of the panel after coefficients of pressure have been set
        /// @return non-dimensional normal force coefficient
        double getCoefficientOfNormalForce() const;

        /// @brief gets the axial force coefficient of the panel after coefficients of pressure have been set
        /// @return non-dimensional axial force coefficient
        double getCoefficientOfAxialForce() const;

        /// @brief gets the panel rotated so the angle of attack is seen by the panel rather than the flow
        /// @return rotated panel
        Panel getRotatedPanel() const;

        /// @brief performs an axis-angle rotation
        /// @param radians the angle to rotate in radians
        /// @param axis the axis to rotate around
        /// @return rotated panel
        Panel rotate(double radians, const geometry::Vector &axis) const;
    };
} // namespace aerodynamics

#endif