//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <mmm/mmm.hpp>

TTS_CASE("TTS from MPI")
{
  TTS_EXPECT(mmm::context.rank < mmm::context.size);
};
