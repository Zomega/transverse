// Copyright 2015 Will Oursler

#include "bbox.h"

bool _overlapped_helper(float left1, bool l_inf1, float right1, bool r_inf1,
             float left2, bool l_inf2, float right2, bool r_inf2) {
  // Handle cases where the infinite flags alone decide the result.
  if ((l_inf1 && l_inf2)
    || (r_inf1 && r_inf2)
    || (l_inf1 && r_inf1)
    || (l_inf2 && r_inf2)) return true;

  // Handle the remaining cases with an infinite flag...
  if (l_inf1 || r_inf2) return left2 < right1;
  if (l_inf2 || r_inf1) return left1 < right2;

  // At this point, none of the infinite flags are marked.
  if (left1 < left2) return left2 < right1;
  return left1 < right2;
}

bool overlapped(const BBox r1, const BBox r2) {
  bool overlapped_x = _overlapped_helper(r1.left, r1.l_inf, r1.right, r1.r_inf,
                      r2.left, r2.l_inf, r2.right, r2.r_inf);
  bool overlapped_y = _overlapped_helper(r1.bottom, r1.b_inf, r1.top, r1.t_inf,
                      r2.bottom, r2.b_inf, r2.top, r2.t_inf);
  return overlapped_x && overlapped_y;
}

BBox bound(std::vector<Point> points) {
  bool first_pass = true;
  float min_x, min_y, max_x, max_y = 0;

  for (Point p : points) {
    if (first_pass) {
      min_x = max_x = p.x;
      min_y = max_y = p.y;
      first_pass = false;
      continue;
    }
    if (p.x < min_x)
      min_x = p.x;
    if (p.y < min_y)
      min_y = p.y;
    if (p.x > max_x)
      max_x = p.x;
    if (p.y > max_y)
      max_y = p.y;
  }

  BBox result;
  result.left = min_x;
  result.right = max_x;
  result.bottom = min_y;
  result.top = max_y;
  return result;
}

// TODO(woursler): Generalize with Boundable* / abstract class?
BBox bound(std::vector<BBox> boxes) {
  bool first_pass = true;
  float min_x, min_y, max_x, max_y = 0;
  bool l_inf, r_inf, t_inf, b_inf = false;

  for (BBox b : boxes) {
    if (first_pass) {
      min_x = b.left;
      max_x = b.right;
      min_y = b.bottom;
      max_y = b.top;

      l_inf = b.l_inf;
      r_inf = b.r_inf;
      t_inf = b.t_inf;
      b_inf = b.b_inf;

      first_pass = false;
      continue;
    }

    if (b.left < min_x)
      min_x = b.left;
    if (b.bottom < min_y)
      min_y = b.bottom;
    if (b.right > max_x)
      max_x = b.right;
    if (b.top > max_y)
      max_y = b.top;

    if (b.l_inf)
      l_inf = true;
    if (b.r_inf)
      r_inf = true;
    if (b.t_inf)
      t_inf = true;
    if (b.b_inf)
      b_inf = true;
  }

  BBox result;
  result.left = min_x;
  result.right = max_x;
  result.bottom = min_y;
  result.top = max_y;
  result.l_inf = l_inf;
  result.r_inf = r_inf;
  result.t_inf = t_inf;
  result.b_inf = b_inf;
  return result;
}
