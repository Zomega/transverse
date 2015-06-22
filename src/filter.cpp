//  (C) Copyright Jeremy Siek 1999-2004.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/cstdlib.hpp>  // for exit_success
#include <algorithm>
#include <functional>
#include <iostream>

struct is_positive_number {
  bool operator()(int x) { return 0 < x; }
};

struct is_even_number {
  bool operator()(int x) { return !(x % 2); }
};

struct is_gt_n {
  int n;
  explicit is_gt_n(int n) : n(n) {}
  bool operator()(int x) { return x > n; }
};

int main() {
  int numbers_[] = { 0, -1, 4, -3, 5, 8, -2, 1, 2, 3, 4, 5, 6 };
  const int N = sizeof(numbers_)/sizeof(int);

  typedef int* base_iterator;
  base_iterator numbers(numbers_);

  // Example using make_filter_iterator()
  std::copy(
    boost::make_filter_iterator<is_positive_number>(numbers, numbers + N),
    boost::make_filter_iterator<is_positive_number>(numbers + N, numbers + N),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  // Example using filter_iterator
  typedef boost::filter_iterator<is_positive_number, base_iterator>
    FilterIter;

  is_positive_number predicate;
  FilterIter filter_iter_first(predicate, numbers, numbers + N);
  FilterIter filter_iter_last(predicate, numbers + N, numbers + N);

  std::copy(
    filter_iter_first,
    filter_iter_last,
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

// Example using filter_iterator
  typedef boost::filter_iterator<is_gt_n, base_iterator>
    FilterIter2;

  is_gt_n pred(3);
  FilterIter2 filter_iter_first2(pred, numbers, numbers + N);
  FilterIter2 filter_iter_last2(pred, numbers + N, numbers + N);

  std::copy(
    filter_iter_first2,
    filter_iter_last2,
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  // Example using make_filter_iterator()
  std::copy(
    boost::make_filter_iterator<is_even_number>(numbers, numbers + N),
    boost::make_filter_iterator<is_even_number>(numbers + N, numbers + N),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  // Another example using make_filter_iterator()
  std::copy(
      boost::make_filter_iterator(
          std::bind2nd(std::greater<int>(), -2)
        , numbers, numbers + N)

    , boost::make_filter_iterator(
          std::bind2nd(std::greater<int>(), -2)
        , numbers + N, numbers + N)

    , std::ostream_iterator<int>(std::cout, " "));

  std::cout << std::endl;

  return boost::exit_success;
}
