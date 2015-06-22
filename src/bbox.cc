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

template <class RNG>
BBox bbox_distribution::operator()(RNG &gen) {
  float x_center = x_dist(gen);
  float y_center = y_dist(gen);
  float width = width_dist(gen);
  float height = height_dist(gen);

  BBox rect;

  rect.left = x_center - (width / 2);
  rect.right  = x_center + (width / 2);
  rect.bottom = x_center - (height / 2);
  rect.top  = x_center + (height / 2);

  return rect;
}
