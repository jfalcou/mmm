//==================================================================================================
/**
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

namespace mmm
{
  //! Type-to-object adapter helper
  template<typename T> struct type_t
  {
    //! Type stored in the type-to-object adapter
    using type = T;
  };

  //! Type-to-object adapter
  template<typename T> inline constexpr type_t<T> type = {};

  //! Type-to-object adapter generator
  template<typename T> constexpr type_t<T> as(T) noexcept { return type<T>; }
}
