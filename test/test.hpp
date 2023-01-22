//==================================================================================================
/**
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#define TTS_MAIN
#define TTS_CUSTOM_DRIVER_FUNCTION mmm_entry_point
#include "tts.hpp"
#include <mmm/system/context.hpp>

int main(int argc, char const **argv)
{
  mmm::context mpi_context;

  mpi_context.synchronize();
  std::cout << "----------------------------------------------------------------\n";
  std::cout << "[MMM] - Assertions: ";
  #ifdef NDEBUG
  std::cout << "Disabled\n";
  #else
  std::cout << "Enabled\n";
  #endif

  mpi_context.synchronize();
  std::cout << ">> Testing on " << mpi_context.node_id << " "
            << "(" << mpi_context.rank << "/" << mpi_context.size << ")"
            << "\n";

  mpi_context.synchronize();
  mmm_entry_point(argc, argv);
  auto nb_error = tts::report(0,0);
  std::cout << "\n";

  return nb_error;
}
