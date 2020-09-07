//----------------------------------*-C++-*-----------------------------------//
/*!
 * \file   experimental/test/tst_mdspan.cc
 * \author Kelly G. Thompson <kgt@lanl.gov>
 * \date   Saturday, Dec 28, 2019, 15:51 pm
 * \brief  Test experimental C++ features (e.g.: mdspan)
 * \sa     https://github.com/kokkos/mdspan/wiki/A-Gentle-Introduction-to-mdspan
 * \note   Copyright (C) 2019-2020 Triad National Security, LLC.
 *         All rights reserved. */
//----------------------------------------------------------------------------//

#include <iostream>
#include "mdspan"

//----------------------------------------------------------------------------//
// Helper Classes.
// See https://github.com/kokkos/mdspan/blob/master/examples/dot_product/dot_product.cpp
//----------------------------------------------------------------------------//

namespace stdex = std::experimental;

//----------------------------------------------------------------------------//
template <class T, class ExtsA, class LayA, class AccA, class ExtsB, class LayB,
          class AccB>
T dot_product(
    stdex::basic_mdspan<T, ExtsA, LayA, AccA> a,
    stdex::basic_mdspan<T, ExtsB, LayB, AccB>
        b) //requires ExtsA::rank() == ExtsB::rank() && ExtsA::rank() == 2
{
  T result = 0;
  for (int i = 0; i < a.extent(0); ++i) {
    for (int j = 0; j < a.extent(1); ++j) {
      result += a(i, j) * b(i, j);
    }
  }
  return result;
}

//----------------------------------------------------------------------------//
template <class T, class ExtsA, class LayA, class AccA>
void fill_in_order(
    stdex::basic_mdspan<T, ExtsA, LayA, AccA> a) // requires ExtsA::rank() == 2
{
  T count = 0;
  for (int i = 0; i < a.extent(0); ++i) {
    for (int j = 0; j < a.extent(1); ++j) {
      a(i, j) = count++;
    }
  }
}

//----------------------------------------------------------------------------//
// TESTS
//----------------------------------------------------------------------------//

int t1() {
  std::cout << "\nStarting t1 test...\n";

  constexpr int rows = 3;
  constexpr int cols = 3;

  using span_2d_dynamic = stdex::basic_mdspan<
      int, stdex::extents<stdex::dynamic_extent, stdex::dynamic_extent>,
      stdex::layout_right>;
  using span_2d_dynamic_left = stdex::basic_mdspan<
      int, stdex::extents<stdex::dynamic_extent, stdex::dynamic_extent>,
      stdex::layout_left>;

  // auto data_a = std::make_unique<int*>(rows * cols);
  // auto data_b = std::make_unique<int*>(rows * cols);

  std::array<int, rows * cols> data_a;
  std::array<int, rows * cols> data_b;

  auto a = span_2d_dynamic(data_a.data(), rows, cols);
  auto b = span_2d_dynamic_left(data_b.data(), rows, cols);
  fill_in_order(a);
  fill_in_order(b);

  if(dot_product(a, b) != 204) {
    std::cout << "dot product failed" << std::endl;
    return 1;
  }
      
  std::cout << "dot product = " << dot_product(a, b) << std::endl;
  std::cout << "done with t1" << std::endl;
  return 0;
}

//----------------------------------------------------------------------------//
int t2() {
  std::cout << "\nStarting t2 test...\n";

  constexpr int rows = 3;
  constexpr int cols = 3;

  using span_2d_10_10 =
      stdex::basic_mdspan<int, stdex::extents<rows, cols>, stdex::layout_right>;
  using span_2d_10_10_left =
      stdex::basic_mdspan<int, stdex::extents<rows, cols>, stdex::layout_right>;

  std::array<int, 100> data_a;
  std::array<int, 100> data_b;

  auto a = span_2d_10_10(data_a.data());
  auto b = span_2d_10_10_left(data_b.data());
  fill_in_order(a);
  fill_in_order(b);

  if(dot_product(a, b) != 204){
      std::cout << "dot product failed" << std::endl;
      return 1;
  }
  std::cout << "dot product = " << dot_product(a, b) << std::endl;
  std::cout << "done with t2" << std::endl;
  return 0;
}

//----------------------------------------------------------------------------//
int main(int argc, char *argv[]) {
  int error(0);  
  error += t1();
  error += t2();
  return error;
}

//----------------------------------------------------------------------------//
// end of tst_mdspan.cc
//----------------------------------------------------------------------------//
