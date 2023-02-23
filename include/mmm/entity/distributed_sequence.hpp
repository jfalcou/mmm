//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <mmm/system/context.hpp>
#include <mmm/system/datatype.hpp>
#include <vector>
#include <cassert>

namespace mmm
{
  //================================================================================================
  //! @brief Contiguous sequence distributed across PID
  //! @tparam T The type of the elements.
  //! @tparam A An allocator that is used to handle memory and the elements in that memory.
  //================================================================================================
  template<typename T, typename A = std::allocator<T>>
  struct distributed_sequence : private std::vector<T,A>
  {
    using parent                  = std::vector<T,A>;
    using value_type              = typename parent::value_type;
    using allocator_type          = typename parent::allocator_type;
    using size_type               = typename parent::size_type;
    using difference_type         = typename parent::difference_type;
    using reference               = typename parent::reference;
    using const_reference         = typename parent::const_reference;
    using pointer                 = typename parent::pointer;
    using const_pointer           = typename parent::const_pointer;
    using iterator                = typename parent::iterator;
    using const_iterator          = typename parent::const_iterator;
    using reverse_iterator        = typename parent::reverse_iterator;
    using const_reverse_iterator  = typename parent::const_reverse_iterator;

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================
    //! @brief Default cConstructs the container
    distributed_sequence() : parent() {}

    //! @brief Constructs the container with  default-inserted instances of T.
    //! @param count 	The size of the container
    //! @param alloc  Allocator to use for all memory allocations of this sequence
    explicit  distributed_sequence(size_type count, A const& alloc)
            : parent(count,alloc)
    {}

    //! @brief Constructs the container with  default-inserted instances of T.
    //! @param count 	The size of the container
    explicit  distributed_sequence(size_type count)
            : distributed_sequence(count,A{})
    {}

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Iterators
    //! @{
    //==============================================================================================

    //! Returns an iterator to the beginning
    auto begin()  const   { return parent::begin();  }
    //! Returns an iterator to the beginning
    auto begin()          { return parent::begin();  }
    //! Returns an iterator to the beginning
    auto cbegin() const   { return parent::cbegin(); }

    //! Returns an iterator to the end
    auto end() const      { return parent::end();  }
    //! Returns an iterator to the end
    auto end()            { return parent::end();  }
    //! Returns an iterator to the end
    auto cend() const     { return parent::cend(); }

    //! Returns a reverse iterator to the beginning
    auto rbegin() const   { return parent::rbegin();  }
    //! Returns a reverse iterator to the beginning
    auto rbegin()         { return parent::rbegin();  }
    //! Returns a reverse iterator to the beginning
    auto crbegin() const  { return parent::crbegin(); }

    //! Returns a reverse iterator to the end
    auto rend() const     { return parent::rend();  }
    //! Returns a reverse iterator to the end
    auto rend()           { return parent::rend();  }
    //! Returns a reverse iterator to the end
    auto crend() const    { return parent::crend(); }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Element access
    //! @{
    //==============================================================================================

    //! Direct access to the underlying array
    auto data() const { return parent::data(); }

    //! Direct access to the underlying array
    auto data()       { return parent::data(); }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Capacity
    //! @{
    //==============================================================================================

    //! Returns the number of elements
    auto size() const{ return parent::size(); }

    //! Returns if the sequence si empty
    auto empty() const{ return parent::empty(); }

    //==============================================================================================
    //! @}
    //==============================================================================================

    // void gather()
    // {
    //   auto dt = datatype(type<T>);

    //   MPI_Gather( data(), local_size(), dt
    //             , data(), local_size(), offset_, dt
    //             , root(), MPI_COMM_WORLD
    //             );

    //   status_ = false;
    // }
  };
}
