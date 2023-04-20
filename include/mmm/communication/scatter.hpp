//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <mmm/detail/overload.hpp>
#include <mmm/entity/distribuable_sequence.hpp>
#include <mmm/entity/distributed_sequence.hpp>

namespace mmm::tags
{
  struct scatter_ : callable<scatter_>
  {
    using callable<scatter_>::operator();

    template<typename Seq>
    auto operator()(Seq const& s) const noexcept -> decltype(tag_dispatch(*this, s))
    {
      return tag_dispatch(*this, s);
    }
  };
}

namespace mmm
{
  //================================================================================================
  //! @var scatter
  //! @brief Object function for scatter communications
  //!
  //! **Defined in Header**
  //!
  //! @code
  //! #include <mmm/communication/scatter.hpp>
  //! @endcode
  //!
  //! @groupheader{Callable Signatures}
  //!
  //! @code
  //! namespace mmm
  //! {
  //!   template<typename Seq>
  //!   MPI_Datatype scatter(Seq const& data) noexcept;
  //! }
  //! @endcode
  //!
  //! **Parameter:**
  //!
  //!   * `data`  : A distribuable sequence to scatter
  //!
  //! **Return value:**
  //!
  //! A distributed sequence containing the scattered data across PID
  //!
  //================================================================================================
  inline constexpr tags::scatter_ scatter = {};
}

//==================================================================================================
// Communications specializations
//==================================================================================================
namespace mmm::tags
{
  template<typename T, typename A>
  auto tag_dispatch(scatter_ const&, distribuable_sequence<T,A> const& seq) noexcept
  {
    auto dt     = datatype(type<T>);
    auto sz     = seq.local_size(context.rank());

    distributed_sequence<T,A> that(sz);

    MPI_Scatterv( seq.data(), seq.counts().data(), seq.offsets().data(), dt
                , that.data(), sz, dt
                , static_cast<int>(seq.root())
                , MPI_COMM_WORLD
                );

    return that;
  }
}
