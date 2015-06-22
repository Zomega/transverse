#include "rstore.h"

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
class NaiveRStore : public RStore<T> {
 private:
  std::vector<std::pair<T, BBox>> entries;
 public:
  explicit NaiveRStore(std::vector<std::pair<T, BBox>> entries) : entries( entries ) {}

  range<RFilterIter<T>> overlapping(BBox rect) {
    overlapped_predicate<T> predicate(rect);

    RFilterIter<T> first(predicate, entries.begin(), entries.end());
    RFilterIter<T> last(predicate, entries.end(), entries.end());

    range<RFilterIter<T>> range(first, last);
    return range;
  }
};
