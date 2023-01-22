//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <mmm/mmm.hpp>
#include <mpi.h>

TTS_CASE("Check datatype for floating point types")
{
  TTS_EQUAL(mmm::datatype(mmm::type<float>)       , MPI_FLOAT       );
  TTS_EQUAL(mmm::datatype(mmm::type<double>)      , MPI_DOUBLE      );
  TTS_EQUAL(mmm::datatype(mmm::type<long double>) , MPI_LONG_DOUBLE );
};

TTS_CASE("Check datatype for integral types")
{
  TTS_EQUAL(mmm::datatype(mmm::type<char>             ) , MPI_CHAR     );
  TTS_EQUAL(mmm::datatype(mmm::type<signed short>     ) , MPI_SHORT    );
  TTS_EQUAL(mmm::datatype(mmm::type<signed int>       ) , MPI_INT      );
  TTS_EQUAL(mmm::datatype(mmm::type<signed long long> ) , MPI_LONG_LONG);

  TTS_EQUAL(mmm::datatype(mmm::type<unsigned char>      ) , MPI_UNSIGNED_CHAR     );
  TTS_EQUAL(mmm::datatype(mmm::type<unsigned short>     ) , MPI_UNSIGNED_SHORT    );
  TTS_EQUAL(mmm::datatype(mmm::type<unsigned int>       ) , MPI_UNSIGNED          );
  TTS_EQUAL(mmm::datatype(mmm::type<unsigned long long> ) , MPI_UNSIGNED_LONG_LONG);

  // Slight trick here
  TTS_EQUAL(mmm::datatype(mmm::type<bool> ), mmm::context::mpi_bool() );
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
