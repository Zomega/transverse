// Copyright 2015 Will Oursler

#ifndef POINT_H_
#define POINT_H_

#include <cmath>

// TODO(woursler): Points should be immutable...
struct Point {
// TODO(woursler): Allow for points at infinty. May need to make
// Point an abstract class to do so.
  float x, y;
  Point(float x, float y) : x(x), y(y) {}
  // TODO(woursler): RigidTransform applications?
};

/*class InfinitePoint : public Point {
private:
  UnitVector direction;
};*/

inline float distance2(const Point a, const Point b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

inline float distance(const Point a, const Point b) {
  return sqrt(distance2(a, b));
}

inline float interpolate(const float x1, const float x2, const float t) {
  return (1 - t) * x1 + t * x2;
}

inline Point interpolate(const Point p1, const Point p2, const float t) {
  return Point(interpolate(p1.x, p2.x, t), interpolate(p1.y, p2.y, t));
}

inline Point quadratic_interpolate(
  const Point p1,
  const Point p2,
  const Point p3,
  float t ) {
  return interpolate(interpolate(p1, p2, t), interpolate(p2, p3, t), t);
}

inline Point cubic_interpolate(
  const Point p1,
  const Point p2,
  const Point p3,
  const Point p4,
  float t ) {
  return interpolate(
    quadratic_interpolate(p1, p2, p3, t),
    quadratic_interpolate(p2, p3, p4, t),
    t);
}

#endif  // POINT_H_
