// Copyright 2015 Will Oursler

// "edge.h"
//
// This class defines an abstract edge concept and several implementations.
//
// The code in "intersect.h" and to an extent "region_graph.h" is closely
// related and should be read alongside this file to gain a full understanding.
//
// An Edge is defined by a continuous curve between two Points. There must not
// be any discontinuities; therefore Edge subclasses need to be numerically
// stable.
//
// From an external perspective, Edges are first and foremost defined by their
// endpoints and their (one-sided) tangents at those endpoints. While it is
// possible to gain a detailed picture of edge behavior either by casting or by
// repeated use of Edge::getPosition(t), wherever possible code should deal
// with edges topologically by finding their intersections against each other.
//
// This subtly influences the implementation of Edges. In particular, edges
// have pointers to their endpoints so they can be compared by reference; if
// the endpoint values change, the edge should update seamlessly when next
// referenced. That said, it is *highly* discouraged to modify points on the
// fly, since this might alter the topology of drawings attached to them.
//
// TODO(woursler): Modify this doc once Points are immutable / singletons.
//
// Utilities for efficient and uniform intersection between edges can be found
// in the header "intersect.h". See that file for details on how to perform
// intersections and deal uniformly with the results.
//
// While it is not encouraged, edges may intersect with themselves through
// happenstance. The Edge class contains two methods for this case. One
// detects if a self-intersection has occurred (Edge::hasSelfIntersection), the
// other (Edge::selfIntersection) can produce an EdgeIntersectionResult that
// details how to remove the self intersection by breaking the edge into
// smaller components. Many objects (i.e. Shape) have utilities to detect and
// remove self intersections built in.
//
// Making a new Edge type is not advisable -- if you must, make sure to
// properly update EdgeType, intersect, and other functions related to I/O on
// edges.
//
// See the comments below for more details.

#ifndef EDGE_H_
#define EDGE_H_

#include "bbox.h"
#include "point.h"
#include "unit_vector.h"
#include "intersect.h"
#include "rigid_transform.h"

// This forward declaration is necessary for the Edge class to include
// self-intersection utilities.
struct EdgeIntersectionResult;

// Use sparingly! This type is mostly used internally in "intersect.h" and for
// SVG export. If it is being used for anything else there is likely a better
// way.
//
// Check the bottom of the file for the classes corresponding to these values.
//
// TODO(woursler): Protected part of Edge?
enum EdgeType {
  LINEAR,
  RAY,
  ELLIPSOID_ARC,
  CIRCULAR_ARC,
  QUAD_BEZIER,
  CUBIC_BEZIER
};

// Pure abstract class defining edges. For almost everything involving edges,
// this should be all you need. As stated in the file comments, an Edge is
// defined by its endpoint behavior and the way it intersects with other edges.
//
// Edges are implicitly oriented -- they have a "start" and an "end". This is
// mainly for convenience, but is used to orient and categorize intersections.
class Edge {
 public:
  // Use sparingly: see the note on EdgeType;
  virtual EdgeType type() = 0;

  // Returns a reference to the starting point.
  virtual std::shared_ptr<Point> getStart() = 0;

  // Returns a reference to the ending point.
  virtual std::shared_ptr<Point> getEnd() = 0;

  // The normalized tangent to the curve when leaving the start point.
  virtual UnitVector getStartTangent() = 0;

  // The normalized tangent to the curve when leaving the end point.
  // Note that this is reversed from the tangent moving forward in time, since
  // to leave the end point, t starts at 1 and goes towards 0.
  virtual UnitVector getEndTangent() = 0;

  // The point on the curve when 0 < t < 1. Undefined behavior will occur
  // outside this range.
  //
  // Use sparingly; this function is mostly intended to produce subedges.
  virtual Point getPosition(float t) = 0;

  // Returns a axis aligned bounding box for the Edge. While it is not required
  // that this box be tight to the curve, that is highly encouraged, as it
  // prevents potential undefined behavior in intersect.
  //
  // A common method to do this is to identify all extrema on the edge; points
  // which locally maximize either the x or y coordinate. The ends of the curve
  // are always extrema, but there may also be arbitrarily many internal sites
  // that qualify. The tight axis-aligned bounding box that bounds the extrema
  // should then bound the edge tightly.
  virtual BBox getBBox() = 0;

  // TODO(woursler): would a unique pointer be more appropriate here?
  virtual std::shared_ptr<Edge> applyTransform(RigidTransform transform) = 0;
  virtual std::shared_ptr<Edge> subEdge(float t_s, float t_e) = 0;

  virtual bool hasSelfIntersection() = 0;
  virtual EdgeIntersectionResult selfIntersection() = 0;
};

// Everything below this line is headers for implementations of Edge.

// Linear Edges are pretty simple -- they describe a straight line segment
// between the given points.
class LinearEdge : public Edge,
  public std::enable_shared_from_this<LinearEdge> {
 private:
  std::shared_ptr<Point> start, end;

 public:
  // Creates an edge from start to end.
  LinearEdge(std::shared_ptr<Point> start, std::shared_ptr<Point> end)
    : start(start), end(end) {}

  // Everything below here is documented in the Edge Class.
  EdgeType type();
  std::shared_ptr<Point> getStart();
  std::shared_ptr<Point> getEnd();
  UnitVector getStartTangent();
  UnitVector getEndTangent();
  Point getPosition(float t);
  BBox getBBox();
  std::shared_ptr<Edge> applyTransform(RigidTransform transform);
  std::shared_ptr<Edge> subEdge(float t_s, float t_e);
  bool hasSelfIntersection();
  EdgeIntersectionResult selfIntersection();
};

class RayEdge : public Edge {
 private:
  Point start;
  UnitVector tangent;
};  // TODO(woursler): other members

class EllipsoidArc : public Edge {
 private:
  Point center;
  UnitVector rotation;
  float semimajorAxis, semiminorAxis;
  UnitVector startAngle, endAngle;
};  // TODO(woursler)

class CircularArc : public Edge {
 private:
  Point center;
  float radius;
  UnitVector startAngle, endAngle;
};  // TODO(woursler)

class QuadraticBezierArc : public Edge {
 private:
  Point P0, P1, P2;
};  // TODO(woursler)

class CubicBezierArc : public Edge {
 private:
  Point P0, P1, P2, P3;
};  // TODO(woursler)

#endif  // EDGE_H_
