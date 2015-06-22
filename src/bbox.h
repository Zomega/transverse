#ifndef _TRANSVERSE_BBOX_H_
#define _TRANSVERSE_BBOX_H_

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

class bbox_distribution {
 private:
  std::uniform_real_distribution<float> x_dist, y_dist, width_dist, height_dist;

 public:
  bbox_distribution(
    std::uniform_real_distribution<float> x_dist,
    std::uniform_real_distribution<float> y_dist,
    std::uniform_real_distribution<float> width_dist,
    std::uniform_real_distribution<float> height_dist )
    : x_dist(x_dist),
    y_dist(y_dist),
    width_dist(width_dist),
    height_dist(height_dist) {}

  template <class RNG>
  BBox operator()(RNG &gen);
};

#endif // _TRANSVERSE_BBOX_H_
