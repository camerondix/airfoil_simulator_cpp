#include "polygon.h"

#include <complex>

#include "point.h"

using geometry::Polygon;

using geometry::Point;

bool Polygon::pointIsInside(const Point &point) const
{
    std::complex<double> sum{0.0, 0.0};
    for (int i = 0; i < size(); ++i)
    {
        Point p1 = i == 0 ? this->at(size() - 1) : this->at(i - 1);
        Point p2 = this->at(i);
        std::complex<double> complexPoint = std::complex<double>{point.x, point.y};
        std::complex<double> p1ToPoint = std::complex<double>{p1.x, p1.y} - complexPoint;
        std::complex<double> p2ToPoint = std::complex<double>{p2.x, p2.y} - complexPoint;
        sum += std::log(p2ToPoint / p1ToPoint);
    }
    return std::abs(sum) > 1;
}