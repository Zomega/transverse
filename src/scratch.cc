// Copyright 2015 Will Oursler

#include <boost/config.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/cstdlib.hpp>  // for exit_success

#include <stdio.h>
#include <random>

#include "region_utils.h"
#include "shape.h"

void pprint(const BBox rect) {
  std::cout << "LEFT: ";
  if (!rect.l_inf) std::cout << rect.left << std::endl;
  else
    std::cout << "NegInf" << std::endl;

  std::cout << "RIGHT: ";
  if (!rect.r_inf) std::cout << rect.right << std::endl;
  else
    std::cout << "Inf" << std::endl;

  std::cout << "TOP: ";
  if (!rect.t_inf) std::cout << rect.top << std::endl;
  else
    std::cout << "Inf" << std::endl;

  std::cout << "BOTTOM: ";
  if (!rect.b_inf) std::cout << rect.bottom << std::endl;
  else
    std::cout << "NegInf" << std::endl;
}

int main() {
  std::shared_ptr<Point> p1 = std::make_shared<Point>(Point(0, 0));
  std::shared_ptr<Point> p2 = std::make_shared<Point>(Point(1, 2));
  std::shared_ptr<Point> p3 = std::make_shared<Point>(Point(0, -2));

  std::shared_ptr<Edge> e1 = std::make_shared<LinearEdge>(LinearEdge(p1, p2));
  std::shared_ptr<Edge> e2 = std::make_shared<LinearEdge>(LinearEdge(p2, p3));
  std::shared_ptr<Edge> e3 = std::make_shared<LinearEdge>(LinearEdge(p3, p1));

  std::vector<std::shared_ptr<Edge>> edges;
  edges.push_back(e1);
  edges.push_back(e2);
  edges.push_back(e3);

  Shape triangle(edges);

  std::cout << e3->getPosition(0.212).x
    << " " << e3->getPosition(0.212).y << std::endl;

  pprint(e2->getBBox());

  std::shared_ptr<int> sp = std::make_shared<int>(12);
  std::cout << *sp << std::endl;
  return boost::exit_success;
}
