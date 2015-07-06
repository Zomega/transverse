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
