//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <mmm/mmm.hpp>
#include <iostream>

int main(int argc, char** argv)
{
  mmm::context mpi_context(argc, argv);

  std::cout << "Hello world from processor " << mpi_context.node_id;
  std::cout << " [" << mpi_context.rank << "/" << mpi_context.size << "]\n";
}
