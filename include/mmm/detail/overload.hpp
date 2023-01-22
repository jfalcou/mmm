//==================================================================================================
/**
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <mmm/detail/abi.hpp>
#include <mmm/detail/raberu.hpp>
#include <type_traits>
#include <utility>

namespace mmm
{
  //================================================================================================
  // Externally overloadable tag dispatch inspired from P1895
  //================================================================================================
  namespace func_ns
  {
    struct dispatcher
    {
      template<typename Tag, typename... Ps>
      requires requires (Tag&& t, Ps&&... ps) { tag_dispatch(MMM_FWD(t),MMM_FWD(ps)...); }
      MMM_FORCEINLINE
      constexpr auto operator()(Tag&& t, Ps&&... ps) const
      noexcept(noexcept(tag_dispatch(MMM_FWD(t),MMM_FWD(ps)...)))
            ->  decltype(tag_dispatch(MMM_FWD(t),MMM_FWD(ps)...))
      {
        return tag_dispatch(MMM_FWD(t),MMM_FWD(ps)...);
      }
    };
  }

  inline namespace callable_ns { inline constexpr func_ns::dispatcher tag_dispatch = {}; }

  template<typename Tag, typename... Ps>
  concept tag_invocable = requires(Tag&& t, Ps&&... ps)
  {
    mmm::tag_dispatch(MMM_FWD(t),MMM_FWD(ps)...);
  };

  template<typename Tag, typename... Ps>
  using tag_dispatch_result = std::invoke_result<decltype(mmm::tag_dispatch), Tag, Ps...>;

  template<typename Tag, typename... Ps>
  using tag_dispatch_result_t = std::invoke_result_t<decltype(mmm::tag_dispatch), Tag, Ps...>;

  template<auto& Tag> using tag = std::decay_t<decltype(Tag)>;
}

//-------------------------------------------------------------------------------------------------
// Tools for overload
//-------------------------------------------------------------------------------------------------
namespace mmm
{
  namespace tags
  {
    // Exposition-only struct to carry around wrong tag/types
    template<typename Tag,typename... T> struct unsupported_call {};
  }

  // ADL postponing structure
  namespace detail { struct delay {}; }

  //-----------------------------------------------------------------------------------------------
  //  Base class for masking support (no more macro)
  //-----------------------------------------------------------------------------------------------
  template<typename Tag> struct support_options
  {
    template<typename Settings> struct custom_fn
    {
      template<typename Options>
      MMM_FORCEINLINE auto operator[](Options&& o) const
      {
        auto new_opts = rbr::merge(rbr::settings{o}, opts);
        return custom_fn<decltype(new_opts)>{new_opts};
      }

      template<typename... Ps>
      MMM_FORCEINLINE auto operator()(Ps const&... x) const
      -> mmm::tag_dispatch_result_t<Tag, Settings const&, Ps const&...>
      {
        return tag_dispatch(Tag{}, opts, x...);
      }

      Settings opts;
    };

    template<rbr::concepts::option Options>
    MMM_FORCEINLINE auto operator[](Options&& o) const
    {
      auto n = rbr::settings{o};
      return custom_fn<decltype(n)>{n};
    }

    template<rbr::concepts::settings Settings>
    MMM_FORCEINLINE auto operator[](Settings const& s) const
    {
      return custom_fn<Settings>{s};
    }
  };

  //-----------------------------------------------------------------------------------------------
  // Type & Concepts for function family
  //-----------------------------------------------------------------------------------------------
  template<typename Tag> struct callable
  {
    using callable_tag_type = Tag;

    // Local poison pill to ensure error message are not kilometer long
    template<typename... T>
    mmm::tags::unsupported_call<Tag, T...> operator()(T const&... x) const noexcept
    requires(!requires(Tag const& t){ tag_dispatch(t, x...); }) = delete;
  };

  template<typename T>
  concept callable_object   = requires(T) { typename T::callable_tag_type; };
}

//-------------------------------------------------------------------------------------------------
// Complete the CPO interface by:
//  -> tie-ing it to a function_ to limit rewriting effort
//  -> limit compile-time with CPO solving tag_dispatch over too many overloads
//  -> provide the stream insertion operator
//-------------------------------------------------------------------------------------------------
#define MMM_MAKE_CALLABLE_OBJECT(TYPE,NAME)                                     \
static auto deferred_call(auto&&... ps) noexcept                                \
-> decltype(NAME ## _(detail::delay, MMM_FWD(ps)...))                           \
{                                                                               \
  return NAME ## _(detail::delay, arch,MMM_FWD(ps)...);                         \
}                                                                               \
template<typename Stream>                                                       \
requires requires(Stream& os) { os << #NAME; }                                  \
friend Stream& operator<<(Stream& os, TYPE const& tag) { return os << #NAME; }  \
/**/
