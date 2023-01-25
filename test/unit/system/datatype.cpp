//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <mmm/mmm.hpp>

TTS_CASE("Check datatype for floating point types")
{
  TTS_EQUAL(mmm::datatype(mmm::type<float>)       , MPI_FLOAT       );
  TTS_EQUAL(mmm::datatype(mmm::type<double>)      , MPI_DOUBLE      );
  TTS_EQUAL(mmm::datatype(mmm::type<long double>) , MPI_LONG_DOUBLE );
};

TTS_CASE("Check datatype for integral types")
{
  TTS_EQUAL(mmm::datatype(mmm::type<std::int8_t> ), MPI_INT8_T);
  TTS_EQUAL(mmm::datatype(mmm::type<std::int16_t>), MPI_INT16_T);
  TTS_EQUAL(mmm::datatype(mmm::type<std::int32_t>), MPI_INT32_T);
  TTS_EQUAL(mmm::datatype(mmm::type<std::int64_t>), MPI_INT64_T);

  TTS_EQUAL(mmm::datatype(mmm::type<std::uint8_t> ), MPI_UINT8_T);
  TTS_EQUAL(mmm::datatype(mmm::type<std::uint16_t>), MPI_UINT16_T);
  TTS_EQUAL(mmm::datatype(mmm::type<std::uint32_t>), MPI_UINT32_T);
  TTS_EQUAL(mmm::datatype(mmm::type<std::uint64_t>), MPI_UINT64_T);

  // Slight trick here
  TTS_EQUAL(mmm::datatype(mmm::type<bool>), MPI_UINT8_T);
};

TTS_CASE("Check datatype for specific pair types")
{
  TTS_EQUAL(mmm::datatype(mmm::type<std::pair<float, int>>)       , MPI_FLOAT_INT       );
  TTS_EQUAL(mmm::datatype(mmm::type<std::pair<double, int>>)      , MPI_DOUBLE_INT      );
  TTS_EQUAL(mmm::datatype(mmm::type<std::pair<long double, int>>) , MPI_LONG_DOUBLE_INT );

  TTS_EQUAL(mmm::datatype(mmm::type<std::pair<short, int>>)       , MPI_SHORT_INT       );
  TTS_EQUAL(mmm::datatype(mmm::type<std::pair<int, int>>)         , MPI_2INT            );
  TTS_EQUAL(mmm::datatype(mmm::type<std::pair<long, int>>)        , MPI_LONG_INT        );
};
