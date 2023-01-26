//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <mmm/detail/overload.hpp>
#include <mmm/system/context.hpp>
#include <mmm/system/traits.hpp>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace mmm::tags
{
  struct datatype_ : callable<datatype_>
  {
    using callable<datatype_>::operator();

    template<typename T>
    auto operator()(type_t<T> const& x) const noexcept -> decltype(tag_dispatch(*this, x))
    {
      return tag_dispatch(*this, x);
    }
  };
}

namespace mmm
{
  //================================================================================================
  //! @var datatype
  //! @brief datatype object function for MPI_Datatype retrieval
  //!
  //! **Defined in Header**
  //!
  //! @code
  //! #include <mmm/system/datatype.hpp>
  //! @endcode
  //!
  //! @groupheader{Callable Signatures}
  //!
  //! @code
  //! namespace mmm
  //! {
  //!   template<typename T >
  //!   MPI_Datatype datatype(mmm::type_t<T> target) noexcept;
  //! }
  //! @endcode
  //!
  //! **Parameter:**
  //!
  //!   * `target`  : A [type-to-object adapter](@ref mmm::type) instance carrying the
  //!     type for which the `MPI_Datatype` is requested.
  //!
  //! **Return value:**
  //!
  //! The `MPI_Datatype` value associated to `T`.
  //!
  //================================================================================================
  inline constexpr tags::datatype_ datatype = {};
}

//==================================================================================================
// datatype specializations
//==================================================================================================
namespace mmm::tags
{
  // floating-point cases
  template<std::floating_point T>
  auto tag_dispatch(datatype_ const&, type_t<T> ) noexcept
  {
    if      constexpr( std::same_as<T, float>      ) return MPI_FLOAT;
    else if constexpr( std::same_as<T, double>     ) return MPI_DOUBLE;
    else if constexpr( std::same_as<T, long double>) return MPI_LONG_DOUBLE;
  }

  // integral cases
  template<std::integral T>
  auto tag_dispatch(datatype_ const&, type_t<T> ) noexcept
  {
    // signed integers by size
    if      constexpr(  std::is_signed_v<T> && sizeof(T) == 1 ) return MPI_INT8_T;
    else if constexpr(  std::is_signed_v<T> && sizeof(T) == 2 ) return MPI_INT16_T;
    else if constexpr(  std::is_signed_v<T> && sizeof(T) == 4 ) return MPI_INT32_T;
    else if constexpr(  std::is_signed_v<T> && sizeof(T) == 8 ) return MPI_INT64_T;
    // unsigned integers by size
    else if constexpr( !std::is_signed_v<T> && sizeof(T) == 1 ) return MPI_UINT8_T;
    else if constexpr( !std::is_signed_v<T> && sizeof(T) == 2 ) return MPI_UINT16_T;
    else if constexpr( !std::is_signed_v<T> && sizeof(T) == 4 ) return MPI_UINT32_T;
    else if constexpr( !std::is_signed_v<T> && sizeof(T) == 8 ) return MPI_UINT64_T;
  }

  // Specific pair types
  inline auto tag_dispatch(datatype_ const&, type_t<std::pair<float, int>> ) noexcept
  {
    return MPI_FLOAT_INT;
  }

  inline auto tag_dispatch(datatype_ const&, type_t<std::pair<double, int>> ) noexcept
  {
    return MPI_DOUBLE_INT;
  }

  inline auto tag_dispatch(datatype_ const&, type_t<std::pair<long double, int>> ) noexcept
  {
    return MPI_LONG_DOUBLE_INT;
  }

  inline auto tag_dispatch(datatype_ const&, type_t<std::pair<short, int>> ) noexcept
  {
    return MPI_SHORT_INT;
  }

  inline auto tag_dispatch(datatype_ const&, type_t<std::pair<int, int>> ) noexcept
  {
    return MPI_2INT;
  }

  inline auto tag_dispatch(datatype_ const&, type_t<std::pair<long, int>> ) noexcept
  {
    return MPI_LONG_INT;
  }
}
