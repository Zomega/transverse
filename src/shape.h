// Copyright 2015 Will Oursler

#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>

#include "edge.h"

class Shape {
 private:
  std::vector<std::shared_ptr<Edge>> edges;
 public:
  explicit Shape(std::vector<std::shared_ptr<Edge>> edges);
  // TODO(woursler): verify on construction that these are all good.

  // TODO(woursler): What about shapes with multiple disjoint sections?
  // Maybe those are more like vector<Shape>?
};

#endif  // SHAPE_H_
