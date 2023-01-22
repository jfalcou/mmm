//==================================================================================================
/**
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

// Faster than std::forward
#define MMM_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

// Force a function to be inline
#if defined(MMM_NO_FORCEINLINE)
#  define MMM_FORCEINLINE inline
#else
#  if defined(_MSC_VER)
#    define MMM_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
#    define MMM_FORCEINLINE inline __attribute__((__always_inline__))
#  else
#    define MMM_FORCEINLINE inline
#  endif
#endif

// CONST attribute
#if defined(_MSC_VER)
#  define MMM_CONST
#else
#  define MMM_CONST [[gnu::const]]
#endif

// PURE attribute
#if defined(_MSC_VER)
#  define MMM_PURE
#else
#  define MMM_PURE [[gnu::pure]]
#endif
