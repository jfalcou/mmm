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

namespace mmm
{
  template<typename T, typename A = std::allocator<T>>
  struct distribuable_sequence
  {
    distribuable_sequence() : storage_{}, status_{false}, root_{0} {}

    distribuable_sequence ( std::size_t n, int root = 0 )
                        : storage_{}, status_{false}, root_{root}
    {
      std::size_t sz  = static_cast<std::size_t>(context.size());
      std::size_t pid = static_cast<std::size_t>(context.rank());

      local_size_ = n/sz + (pid < (n%sz) ? 1 : 0);
      if(pid == root_)  storage_.resize(n);
      else              storage_.resize(local_size_);
    }

    auto root()       const { return root_; }

    auto data() const { return storage_.data(); }
    auto data()       { return storage_.data(); }

    auto begin() const { return storage_.begin(); }
    auto begin()       { return storage_.begin(); }

    auto end() const { return storage_.begin() + size(); }
    auto end()       { return storage_.begin() + size(); }

    auto local_size() const { return local_size_; }
    auto size()       const { return status_ ? local_size_ : storage_.size(); }

    void scatter()
    {
      auto dt = datatype(type<T>);

      MPI_Scatter ( data(), local_size(), dt
                  , data(), local_size(), dt
                  , root(), MPI_COMM_WORLD
                  );

      status_ = true;
    }

    void gather()
    {
      auto dt = datatype(type<T>);

      MPI_Gather( data(), local_size(), dt
                , data(), local_size(), dt
                , root(), MPI_COMM_WORLD
                );

      status_ = false;
    }

    private:
    std::vector<T,A>  storage_;
    std::size_t       local_size_;
    int               root_;
    bool              status_;
  };
}
