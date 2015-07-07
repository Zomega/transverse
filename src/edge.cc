// Copyright 2015 Will Oursler

#include "edge.h"

#include <vector>

EdgeType LinearEdge::type() {
  return LINEAR;
}

std::shared_ptr<Point> LinearEdge::getStart() {
  return start;
}

std::shared_ptr<Point> LinearEdge::getEnd() {
  return end;
}

UnitVector LinearEdge::getStartTangent() {
  return PointsTowards(*start, *end);
}

UnitVector LinearEdge::getEndTangent() {
  return PointsTowards(*end, *start);
}

Point LinearEdge::getPosition(float t) {
  return interpolate(*start, *end, t);
}

// Identify the bounding box by bounding all the extreme points.
// In this case, the ends are the only relevant extrema.
BBox LinearEdge::getBBox() {
  std::vector<Point> extrema;
  extrema.push_back(*start);
  extrema.push_back(*end);
  return bound(extrema);
}

std::shared_ptr<Edge> LinearEdge::applyTransform(RigidTransform transform) {
  // TODO(woursler) : implement
}

std::shared_ptr<Edge> LinearEdge::subEdge(float t_s, float t_e) {
  // TODO(woursler) : implement
}

bool LinearEdge::hasSelfIntersection() {
  return false;  // No linear edge can self intersect.
}

EdgeIntersectionResult LinearEdge::selfIntersection() {
  EdgeIntersectionResult result;
  result.InsertTerminal(start);
  result.InsertTerminal(end);
  result.InsertEdge(shared_from_this(), nullptr, nullptr);

  return result;
}
