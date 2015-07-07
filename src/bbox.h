// Copyright 2015 Will Oursler

#ifndef BBOX_H_
#define BBOX_H_

#include <random>
#include <iostream>
#include <vector>

#include "point.h"

/**
* Bounding box class. Allows for infinite bounding boxes.
* Bounding boxes are assumed to be OPEN -- they do include their
* boundaries.
* This insures that the nonzero intersection of two boundary boxes
* has some width and height.
*
* The bool flags indicate that an edge extends out to infinity. If any flag is true, the corresponding float value should be completely ignored (i.e. in no way affect the result of any computation).
*/

struct BBox {
  float left;
  float right;
  float top;
  float bottom;

  bool l_inf = false;
  bool r_inf = false;
  bool t_inf = false;
  bool b_inf = false;
};

bool overlapped(const BBox r1, const BBox r2);

BBox bound(std::vector<Point> points);

BBox bound(std::vector<BBox> boxes);

#endif  // BBOX_H_
