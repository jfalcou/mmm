//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <mpi.h>
#include <mmm/detail/overload.hpp>
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
    // Basic integral types
    if      constexpr(std::same_as<T,std::byte>         ) return MPI_BYTE;
    else if constexpr(std::same_as<T,char>              ) return MPI_CHAR;
    else if constexpr(std::same_as<T,short>             ) return MPI_SHORT;
    else if constexpr(std::same_as<T,int>               ) return MPI_INT;
    else if constexpr(std::same_as<T,long>              ) return MPI_LONG;
    else if constexpr(std::same_as<T,unsigned char>     ) return MPI_UNSIGNED_CHAR;
    else if constexpr(std::same_as<T,unsigned short>    ) return MPI_UNSIGNED_SHORT;
    else if constexpr(std::same_as<T,unsigned int>      ) return MPI_UNSIGNED;
    else if constexpr(std::same_as<T,unsigned long>     ) return MPI_UNSIGNED_LONG;

    // MPI version specific
    #if defined(MPI_WCHAR)
    else if constexpr(std::same_as<T,wchar_t>           ) return MPI_WCHAR;
    #endif

    #if defined(MPI_SIGNED_CHAR)
    else if constexpr(std::same_as<T,signed char>       ) return MPI_SIGNED_CHAR;
    #endif

    #if defined(MPI_LONG_LONG_INT)
    else if constexpr(std::same_as<T,long long>         ) return MPI_LONG_LONG_INT;
    #endif

    #if defined(MPI_UNSIGNED_LONG_LONG)
    else if constexpr(std::same_as<T,unsigned long long>) return MPI_UNSIGNED_LONG_LONG;
    #endif

    #if defined(MPI_WCHAR)
    else if constexpr(std::same_as<T,unsigned long long>) return MPI_UNSIGNED_LONG_LONG;
    #endif
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
