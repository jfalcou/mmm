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
  mmm::context mpi_context;

  std::cout << "Hello world from processor " << mpi_context.node_id;
  std::cout << " [" << mpi_context.rank << "/" << mpi_context.size << "]\n";
}
