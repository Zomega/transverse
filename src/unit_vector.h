// Copyright 2015 Will Oursler

#ifndef UNIT_VECTOR_H_
#define UNIT_VECTOR_H_

#import "point.h"

struct UnitVector {
  float angle;  // in radians.
  // TODO(woursler): This class should be fancier,
  // allow for sorting somehow.
  explict UnitVector(float angle) : angle(angle) {}
};

inline UnitVector PointsTowards(const Point p1, const Point p2) {
  return atan2(p2.y - p1.y, p2.x - p1.x);
}

#endif  // UNIT_VECTOR_H_
