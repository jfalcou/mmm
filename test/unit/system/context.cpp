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
  mmm::context mpi_context(argc, argv, mmm::thread_support::multiple);

  std::cout << "Process     : " << mpi_context.rank << "/" << mpi_context.size << "\n";
  std::cout << "Host        : " << mpi_context.node_id << "\n";
  std::cout << "Thread level: " << mpi_context.thread_level << "\n";
}
