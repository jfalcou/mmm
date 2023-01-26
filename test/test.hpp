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

int main(int argc, const char** argv)
{
  //mmm::context.synchronize();
  std::cout << "----------------------------------------------------------------\n";
  std::cout << "[MMM] - Assertions: ";
  #ifdef NDEBUG
  std::cout << "Disabled\n";
  #else
  std::cout << "Enabled\n";
  #endif

 // mmm::context.synchronize();
  std::cout << ">> Testing on " << mmm::context.node_id() << " "
            << "(" << mmm::context.rank() << "/" << mmm::context.size() << ")"
            << "\n";

 // mmm::context.synchronize();
  mmm_entry_point(argc, argv);
  auto nb_error = tts::report(0,0);
  std::cout << "\n";

  return nb_error;
}
