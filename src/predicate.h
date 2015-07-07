// Copyright 2015 Will Oursler

#ifndef PREDICATE_H_
#define PREDICATE_H_

// TODO(woursler): This is more general than  just for regions. Use templates...
// TODO(woursler): Does boost have stuff for this? Use if so.
// TODO(woursler): Replace all pointers with shared_ptrs
template <typename T>
class Predicate {
 public:
  virtual bool matches(const T x) = 0;
};

template <typename T>
class NotPredicate : public Predicate<T> {
 private:
  std::shared_ptr<Predicate<T>> pred;
 public:
  explicit NotPredicate(std::shared_ptr<Predicate<T>> pred)
    : pred(pred) {}
  bool matches(const T x) {
    return !pred->matches(x);
  }
};

template <typename T>
class AndPredicate : public Predicate<T> {
 private:
  std::shared_ptr<Predicate<T>> predA;
  std::shared_ptr<Predicate<T>> predB;
 public:
  AndPredicate(std::shared_ptr<Predicate<T>> predA, std::shared_ptr<Predicate<T>> predB)
    : predA(predA), predB(predB) {}  // TODO(woursler): copy and destroy?
  bool matches(const T x) {
    return predA->matches(x) && predB->matches(x);
  }
};

template <typename T>
class OrPredicate : public Predicate<T> {
 private:
  std::shared_ptr<Predicate<T>> predA;
  std::shared_ptr<Predicate<T>> predB;
 public:
  OrPredicate(std::shared_ptr<Predicate<T>> predA, std::shared_ptr<Predicate<T>> predB)
    : predA(predA), predB(predB) {}  // TODO(woursler): copy and destroy?
  bool matches(const T x) {
    return predA->matches(x) && predB->matches(x);
  }
};

#endif  // PREDICATE_H_
