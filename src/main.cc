// Copyright 2015 Will Oursler

#include <boost/config.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/cstdlib.hpp>  // for exit_success
#include <stdio.h>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iterator>
#include <utility>

#include "bbox.h"
#include "rstore.h"
#include "naive_rstore.h"

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

void pprint(const BBox rect) {
  std::cout << "LEFT: ";
  if (!rect.l_inf) std::cout << rect.left << std::endl;
  else
    std::cout << "NegInf" << std::endl;

  std::cout << "RIGHT: ";
  if (!rect.r_inf) std::cout << rect.right << std::endl;
  else
    std::cout << "Inf" << std::endl;

  std::cout << "TOP: ";
  if (!rect.t_inf) std::cout << rect.top << std::endl;
  else
    std::cout << "Inf" << std::endl;

  std::cout << "BOTTOM: ";
  if (!rect.b_inf) std::cout << rect.bottom << std::endl;
  else
    std::cout << "NegInf" << std::endl;
}

int main() {
  std::random_device rd;
  std::mt19937 mt(rd());

  std::uniform_real_distribution<float> x_dist(-100, 100);
  std::uniform_real_distribution<float> y_dist(-100, 100);
  std::uniform_real_distribution<float> width_dist(0.1, 50);
  std::uniform_real_distribution<float> height_dist(0.1, 50);

  bbox_distribution rect_dist(x_dist, y_dist, width_dist, height_dist);

  std::vector<std::pair<int, BBox>> entries;

  for (int i=0; i < 100; ++i) {
    entries.push_back(std::make_pair(i, rect_dist(mt)));
  }

  NaiveRStore<int> rstore(entries);

  BBox reference;

  reference.l_inf = true;
  reference.right  = 0;
  reference.bottom = -1;
  reference.top  = 1;
  pprint(reference);

  for (auto rect : rstore.overlapping(reference)) {
    pprint(rect.second);
    std::cout << std::endl;
  }

  return boost::exit_success;
}
