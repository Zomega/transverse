// Copyright 2015 Will Oursler

#ifndef REGION_UTILS_H_
#define REGION_UTILS_H_

#include <iostream>
#include <vector>

#include "edge.h"
#include "region_graph.h"
#include "shape.h"
#include "predicate.h"

class RegionPrimativeMatchPredicate : public Predicate<Region> {
 private:
  RegionPrimative label;
 public:
  bool matches(const Region region);
  // TODO(woursler): check if label is part of region...
};

// TODO(woursler)
RegionGraph CombineRegions(const RegionGraph a, const RegionGraph b);

// TODO(woursler): Use ray
std::shared_ptr<Region> Locate(const RegionGraph regions, const Point p);

// TODO(woursler): Use Green's theorem.
float area(const RegionGraph regions, const std::shared_ptr<Region> r);
float area(const Shape shape);

// TODO(woursler):
// Remove all regions that are sufficiently small by joining them with the region along
// their longest edge.
// Should this be a RegionRedicate instead?
RegionGraph DeburrRegions(RegionGraph regions, float minimumArea);

// TODO(woursler): implement.
Shape FilterRegions(const RegionGraph regions, std::shared_ptr<Predicate<Region>> predicate);
std::vector<Shape> BreakApartRegions(const RegionGraph regions);

#endif  // REGION_UTILS_H_
