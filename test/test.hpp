//==================================================================================================
/**
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "mmm/system/context.hpp"
#define TTS_MAIN
#define TTS_CUSTOM_DRIVER_FUNCTION mmm_entry_point
#include "tts.hpp"
#include <mmm/mmm.hpp>

int main(int argc, char const **argv)
{
  using mmm::context;

  context.synchronize();
  std::cout << "----------------------------------------------------------------\n";
  std::cout << "[MMM] - Assertions: ";
  #ifdef NDEBUG
  std::cout << "Disabled\n";
  #else
  std::cout << "Enabled\n";
  #endif

  context.synchronize();
  std::cout << ">> Testing on " << context.node_id << " "
            << "(" << context.rank << "/" << context.size << ")"
            << "\n";

  context.synchronize();
  mmm_entry_point(argc, argv);
  auto nb_error = tts::report(0,0);
  std::cout << "\n";

  return nb_error;
}
