#include "line_segment.h"

#include "point.h"
#include "vector.h"

using geometry::LineSegment;

using geometry::Point;
using geometry::Vector;

Point LineSegment::getStart() const
{
    return mStart;
}

Point LineSegment::getEnd() const
{
    return mEnd;
}

Point LineSegment::getMid() const
{
    return mStart + 0.5 * (mEnd - mStart);
}

Vector LineSegment::getDelta() const
{
    return Vector{mStart, mEnd};
}

double LineSegment::getLength() const
{
    return getDelta().getMagnitude();
}

LineSegment LineSegment::rotate(double radians, const Vector &axis) const
{
    // Rotate start and end points
    return LineSegment{mStart.rotate(radians, axis), mEnd.rotate(radians, axis)};
}