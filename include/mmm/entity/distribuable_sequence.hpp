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
#include <cassert>
#include <vector>

namespace mmm
{
  //================================================================================================
  //! @brief Contiguous sequence supporting distribution operations
  //! @tparam T The type of the elements.
  //! @tparam A An allocator that is used to handle memory and the elements in that memory.
  //================================================================================================
  template<typename T, typename A = std::allocator<T>>
  struct distribuable_sequence : private std::vector<T,A>
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

    //! @brief Default constructor rooted on a given PID
    //! @param root PID of the process owning the memory. By default, p = 0
    distribuable_sequence(pid root = {}) noexcept(noexcept(parent()))
    : parent(), count_{}, offset_{}, root_(root)
    {}

    //! @brief Constructs an empty container with a given allocator
    //! @param alloc Allocator to use for all memory allocations of this sequence
    //! @param root PID of the process owning the memory. By default, p = 0
    explicit distribuable_sequence(A const& alloc, pid root = {}) noexcept
    : parent(alloc), count_{}, offset_{}, root_(root)
    {}

    //! @brief Copy the distribuable_sequence with another allocator instance
    //! @param other distribuable_sequence to copy
    //! @param alloc Allocator to use for all memory allocations of this sequence
    distribuable_sequence(distribuable_sequence const& other, A const& alloc)
    : parent(other,alloc), count_{other.count_}, offset_{other.offset_}, root_(other.root_)
    {}

    //! @brief Move the distribuable_sequence with another allocator instance
    //! @param other distribuable_sequence to move
    //! @param alloc Allocator to use for all memory allocations of this sequence
    distribuable_sequence(distribuable_sequence&& other, A const& alloc)
    : parent(std::move(other),alloc)
    {}

    //! @brief Constructs the container with  default-inserted instances of T.
    //! @param count 	The size of the container
    //! @param alloc  Allocator to use for all memory allocations of this sequence
    //! @param root   PID of the process owning the memory. By default, p = 0
    explicit distribuable_sequence(std::integral auto count, A const& alloc, pid root = {})
    : parent(root == context.rank() ? count : 0,alloc)
    , count_{context.size()}, offset_{context.size()}, root_(root)
    {
      map_to_rank(count);
    }

    //! @brief Constructs the container with  default-inserted instances of T.
    //! @param count 	The size of the container
    //! @param root   PID of the process owning the memory. By default, p = 0
    explicit  distribuable_sequence(std::integral auto count, pid root = {} )
            : distribuable_sequence(count,A{},root)
    {}

    //! @brief Constructs the container with  default-inserted instances of T.
    //! @param count 	The size of the container
    //! @param value	The value to initialize elements of the container with
    //! @param alloc  Allocator to use for all memory allocations of this sequence
    //! @param root   PID of the process owning the memory. By default, p = 0
    explicit distribuable_sequence(std::integral auto count, const T& value, A const& alloc, pid root = {})
    : parent(root == context.rank() ? count : 0,value,alloc)
    , count_{context.size()}, offset_{context.size()}, root_(root)
    {
      map_to_rank(count);
    }

    //! @brief Constructs the container with  default-inserted instances of T.
    //! @param count 	The size of the container
    //! @param value	The value to initialize elements of the container with
    //! @param root   PID of the process owning the memory. By default, p = 0
    explicit  distribuable_sequence(std::integral auto count, const T& value, pid root = {})
            : distribuable_sequence(count,value,A{},root)
    {}

    //! @brief Constructs the distribuable_sequence with the contents of the range [first, last).
    //! @param first  Beginning of the range to copy
    //! @param last   End of the range to copy
    //! @param alloc  Allocator to use for all memory allocations of this sequence
    //! @param root   PID of the process owning the memory. By default, p = 0
    template<std::forward_iterator InputIt>
    distribuable_sequence( InputIt first, InputIt last,A const& alloc, pid root = {} )
    : parent(first,root == context.rank() ? last : first,alloc)
    , count_{context.size()}, offset_{context.size()}, root_(root)
    {
      map_to_rank(static_cast<int>(last-first));
    }

    //! @brief Constructs the distribuable_sequence with the contents of the range [first, last).
    //! @param first  Beginning of the range to copy
    //! @param last   End of the range to copy
    //! @param root   PID of the process owning the memory. By default, p = 0
    template<typename InputIt>
    distribuable_sequence (InputIt first, InputIt last, pid root = {})
                          : distribuable_sequence(first,last,A{},root)
    {}

    //! @brief Constructs the container with the contents of an initializer list.
    //! @param init	Initializer list to initialize the elements of the container with
    //! @param alloc  Allocator to use for all memory allocations of this sequence
    //! @param root PID of the process owning the memory. By default, p = 0
    distribuable_sequence( std::initializer_list<T> init,A const& alloc, pid root = {})
    : parent(alloc), count_{context.size()}, offset_{context.size()}, root_(root)
    {
      if(root_ == context.rank())
      {
        parent::insert(parent::end(),init);
      }

      map_to_rank(init.size());
    }

    //! @brief Constructs the container with the contents of an initializer list.
    //! @param init	Initializer list to initialize the elements of the container with
    //! @param root PID of the process owning the memory. By default, p = 0
    distribuable_sequence (std::initializer_list<T> init, pid root = {})
                          : distribuable_sequence(init,A{},root)
    {}

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Iterators
    //! @{
    //==============================================================================================

    //! Returns an iterator to the beginning
    auto begin()  const   { assert(root_ == context.rank()); return parent::begin();  }
    //! Returns an iterator to the beginning
    auto begin()          { assert(root_ == context.rank()); return parent::begin();  }
    //! Returns an iterator to the beginning
    auto cbegin() const   { assert(root_ == context.rank()); return parent::cbegin(); }

    //! Returns an iterator to the end
    auto end() const      { assert(root_ == context.rank()); return parent::end();  }
    //! Returns an iterator to the end
    auto end()            { assert(root_ == context.rank()); return parent::end();  }
    //! Returns an iterator to the end
    auto cend() const     { assert(root_ == context.rank()); return parent::cend(); }

    //! Returns a reverse iterator to the beginning
    auto rbegin() const   { assert(root_ == context.rank()); return parent::rbegin();  }
    //! Returns a reverse iterator to the beginning
    auto rbegin()         { assert(root_ == context.rank()); return parent::rbegin();  }
    //! Returns a reverse iterator to the beginning
    auto crbegin() const  { assert(root_ == context.rank()); return parent::crbegin(); }

    //! Returns a reverse iterator to the end
    auto rend() const     { assert(root_ == context.rank()); return parent::rend();  }
    //! Returns a reverse iterator to the end
    auto rend()           { assert(root_ == context.rank()); return parent::rend();  }
    //! Returns a reverse iterator to the end
    auto crend() const    { assert(root_ == context.rank()); return parent::crend(); }

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

    //! Returns the root of the sequence
    auto root()       const { return root_; }

    auto local_size(pid p)     const { return count_[static_cast<std::size_t>(p)]; }

    auto const& counts()  const { return count_; }
    auto const& offsets() const { return offset_; }

    private:
    std::vector<int>  count_;
    std::vector<int>  offset_;
    pid               root_;

    public:
    int get_offset(pid rk)
    {
      return offset_[static_cast<int>(rk)];
    }

    void map_to_rank(std::size_t n)
    {
      auto sz          = static_cast<std::size_t>(context.size());
      auto chunk_size  = n / sz;
      auto remainder   = n % sz;

      for(std::size_t i = 0; i < sz; i++)
      {
        count_[i] = chunk_size + ( i < remainder ? 1 : 0);
      }

      offset_[0] = 0;
      for(std::size_t i = 1; i < sz; i++)
      {
        offset_[i] = offset_[i - 1] + count_[i - 1];
      }
    }
  };
}
