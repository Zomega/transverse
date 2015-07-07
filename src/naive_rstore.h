// Copyright 2015 Will Oursler

#ifndef NAIVE_RSTORE_H_
#define NAIVE_RSTORE_H_

#include <iostream>
#include <vector>
#include <utility>

#include "bbox.h"
#include "rstore.h"

template <typename T>
class NaiveRStore : public RStore<T> {
 private:
  std::vector<std::pair<T, BBox>> entries;
 public:
  explicit NaiveRStore(std::vector<std::pair<T, BBox>> entries)
    : entries(entries) {}

  range<RFilterIter<T>> overlapping(BBox rect) {
    overlapped_predicate<T> predicate(rect);

    RFilterIter<T> first(predicate, entries.begin(), entries.end());
    RFilterIter<T> last(predicate, entries.end(), entries.end());

    range<RFilterIter<T>> range(first, last);
    return range;
  }
};

#endif  // NAIVE_RSTORE_H_
