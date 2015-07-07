// Copyright 2015 Will Oursler

#ifndef RTREE_H_
#define RTREE_H_

#include "bbox.h"
#include "rstore.h"

template <typename T, class NodeT>
class RTree : public RStore<T> {
 private:
  NodeT root;
 public:
  range<RFilterIter<T>> overlapping(BBox rect);
};

template <typename T>
class RNode {
 public:
  virtual BBox limit() = 0;
};

#endif  // RTREE_H_
