// Copyright 2015 Will Oursler

#ifndef INTERSECT_H_
#define INTERSECT_H_

#include <vector>

#include "region_graph.h"

class EdgeIntersectionResult {
 private:
  std::vector<std::shared_ptr<Point>> terminals;
  std::vector<std::shared_ptr<AnnotatedPoint>> points;
  std::vector<std::shared_ptr<AnnotatedEdge>> edges;
 public:
  void InsertTerminal(std::shared_ptr<Point> terminal);
  void InsertPoint(std::shared_ptr<Point> point);
  void InsertEdge(std::shared_ptr<Edge> edge,
    std::shared_ptr<Region> left,
    std::shared_ptr<Region> right);
};

// TODO(woursler): Validate function to check that all nonterminals
// are valid intersections etc?

// Breaks a given Edge into two edges.
EdgeIntersectionResult BreakApart(const AnnotatedEdge edge, float t);

EdgeIntersectionResult Intersect(const AnnotatedEdge a, const AnnotatedEdge b);
// TODO(woursler): recursive calls to intersect breaking both curves
// in half each time. Combine the results.
// If both curves might have non-point intersections (i.e. are of same type
// or are LINEAR and RAY, etc...) special methods are needed.
// In other cases, more efficient methods may be desirable.

#endif  // INTERSECT_H_
