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
  struct gather_ : callable<gather_>
  {
    using callable<gather_>::operator();

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
  //! @var gather
  //! @brief Object function for gather communications
  //!
  //! **Defined in Header**
  //!
  //! @code
  //! #include <mmm/communication/gather.hpp>
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
  inline constexpr tags::gather_ gather = {};
}

//==================================================================================================
// Communications specializations
//==================================================================================================
namespace mmm::tags
{
  template<typename T, typename A>
  auto tag_dispatch(gather_ const&, distributed_sequence<T,A> const& seq) noexcept
  {
    auto        dt          = datatype(type<T>);
    auto local_size  = static_cast<int>(seq.size());
    int   size       = 0;

    MPI_Reduce(&local_size,&size,1,datatype(size),MPI_SUM,0,MPI_COMM_WORLD);

    distribuable_sequence<T,A> dist(size);

    MPI_Gatherv(  seq.data() , local_size, dt
                , dist.data(), dist.counts().data(), dist.offsets().data(), dt
                , static_cast<int>(dist.root())
                , MPI_COMM_WORLD
                );

    return dist;
  }
}
