// Copyright 2015 Will Oursler

#ifndef RSTORE_H_
#define RSTORE_H_

#include <boost/config.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <iostream>
#include <vector>
#include <utility>

#include "bbox.h"

template <typename iter_type>
class range {
 private:
  iter_type begin_iter, end_iter;
 public:
  range(iter_type begin, iter_type end) : begin_iter(begin), end_iter(end) {}
  iter_type begin() { return begin_iter; }
  iter_type end() { return end_iter; }
};

template <typename T>
struct overlapped_predicate {
  BBox r1;
  explicit overlapped_predicate(const BBox rect) { r1 = rect; }
  bool operator()(std::pair<T, BBox> p) { return overlapped(r1, p.second); }
};

template <typename T> using RIterator
  = typename std::vector<std::pair<T, BBox>>::iterator;

template <typename T> using RFilterIter
  = boost::filter_iterator<overlapped_predicate<T>, RIterator<T>>;

template <typename T>
class RStore {
  // virtual range<RFilterIter<T>> overlapping(BBox rect) = 0;
};

#endif  // RSTORE_H_
