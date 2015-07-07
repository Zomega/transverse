// Copyright 2015 Will Oursler

#ifndef REGION_GRAPH_H_
#define REGION_GRAPH_H_

#include <vector>

#include "point.h"
#include "edge.h"

typedef int RegionPrimative;
// TODO(woursler): Singleton RegionPrimative granter?
// shared pointers to empty objects?
// boost::any?

// Forward Declarations
struct AnnotatedEdge;
class Edge;

struct Region {
  std::vector<RegionPrimative> blah;
  // TODO(woursler): Unique IDs
  // TODO(woursler): set is a better idea...
  // TODO(woursler): Constructors, etc...
};

struct AnnotatedPoint {
  std::shared_ptr<Point> point;
  // TODO(woursler): Better, purpose made datastructre.
  // Ability to find next left edge, etc. Orientation smart storage.
  std::vector<std::shared_ptr<AnnotatedEdge>> edges;
};

// Note: AnnotatedEdges only own their edge. They do not own their points
// and regions.
// TODO(woursler): Make mostly immutable?
struct AnnotatedEdge {
  std::shared_ptr<Edge> edge;

  // May be nullptr if there is no associated region.
  std::shared_ptr<Region> left, right;
};

// Note: RegionGraphs own everything attached to them. Regions will be copied.
class RegionGraph {
 private:
  std::vector<std::shared_ptr<Region>> regions;
  std::vector<std::shared_ptr<AnnotatedEdge>> edges;
  std::vector<std::shared_ptr<AnnotatedPoint>> points;
 public:
  // Empty constructor -- provide only a Region.
  // Provide a shape and a name for the interior / exterior regions
  // Provide a bunch of shapes with names for their interiors
  // and a single exterior name.
  // Copy constructor.
};

#endif  // REGION_GRAPH_H_
