//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <mmm/mmm.hpp>
#include <iostream>

int main()
{
  std::cout << "Process     : " << mmm::context.rank() << "/" << mmm::context.size() << "\n";
  std::cout << "Host        : " << mmm::context.node_id() << "\n";
  std::cout << "Thread level: " << mmm::context.threading() << "\n";
}
