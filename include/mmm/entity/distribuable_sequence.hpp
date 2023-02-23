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

    distribuable_sequence() : storage_{}, root_{0}, status_{false} {}

    distribuable_sequence ( int n, int root = 0 )
                        : storage_{}, root_{root}, status_{false}
    {
      auto sz  = context.size();
      auto pid = context.rank();

      count_.resize(sz);
      int chunk_size = n / sz;
      int remainder = n % sz;
      for(int i = 0; i < sz; i++)
      {
        count_[i] = chunk_size + ( i < remainder ? 1 : 0);
      }

      offset_.resize(sz);
      offset_[0] = 0;
      for(int i = 1; i < sz; i++)
      {
        offset_[i] = offset_[i - 1] + count_[i - 1];
      }

      if(pid == root_)  storage_.resize(n);
      else              storage_.resize(local_size());
    }

    auto root()       const { return root_; }

    auto status()     const { return status_; }

    auto data() const { return storage_.data(); }
    auto data()       { return storage_.data(); }

    auto begin() const { return storage_.begin(); }
    auto begin()       { return storage_.begin(); }

    auto end() const { return storage_.begin() + size(); }
    auto end()       { return storage_.begin() + size(); }

    auto local_size() const { return count_[mmm::context.rank()]; }
    auto size()       const { return status_ ? local_size() : storage_.size(); }

    auto count(int pid)      const { return count_[pid]; }

    auto offset(int pid)     const { return offset_[pid];}


    void scatter()
    {
      auto dt = datatype(type<T>);

      MPI_Scatterv( data(), local_size(), offset_, dt
                  , data(), local_size, dt
                  , root(), MPI_COMM_WORLD);

      status_ = true;
    }

    void gather()
    {
      auto dt = datatype(type<T>);
      
      MPI_Gather( data(), local_size(), dt
                , data(), local_size(), offset_, dt
                , root(), MPI_COMM_WORLD
                );

      status_ = false;
    }

    private:
    std::vector<int>  count_;
    std::vector<int>  offset_;
    std::vector<T,A>  storage_;
    int               root_;
    bool              status_;
  };
}
