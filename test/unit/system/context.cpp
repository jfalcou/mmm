//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <iostream>
#include <mmm/mmm.hpp>

int main()
{
  std::cout << "Hello world from processor " << mmm::context.node_id;
  std::cout << " [" << mmm::context.rank << "/" << mmm::context.size << "]\n";
}
