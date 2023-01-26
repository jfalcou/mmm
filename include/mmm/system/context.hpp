//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <mpi.h>
#include <string>
#include <ostream>

namespace mmm
{
  //! Class enumeration for MPI thread support options
  enum thread_support
  {
    //! Only one thread will execute.
    single     = MPI_THREAD_SINGLE,
    //! Only main thread can use MPI-like operations
    funneled   = MPI_THREAD_FUNNELED,
    //! Only one thread at a time can use MPI-like operations
    serialized = MPI_THREAD_SERIALIZED,
    //! MPI-like operations can be called from any thread at any time
    multiple   = MPI_THREAD_MULTIPLE
  };

  inline std::ostream& operator<<(std::ostream& os, thread_support t)
  {
    if      (t == single    ) return os << "Single";
    else  if(t == funneled  ) return os << "Funneled";
    else  if(t == serialized) return os << "Serialized";
    else  if(t == multiple  ) return os << "Multiple";
    else                      return os << "Unsupported";
  }

  //================================================================================================
  //! @struct context
  //! @brief RAII-enabled MPI setup object
  //!
  //! mmm::context encapsulates all the MPI setup and teardown process in a RAII enabled
  //! type. It also provides access to persistent informations about the MPI environment like
  //! size, rank and node ID.
  //================================================================================================
  struct context
  {
    //! @brief Default constructor
    //! Initialize the MPI environment =and gather informations
    context() : context(thread_support::single)
    {}

    //! @brief Constructor from argc/argv
    //! Initialize the MPI environment and gather informations
    //! @param argc `argc` Number of command line argument
    //! @param argv `argv` array of command line argument's strings
    context(int& argc, char**& argv) : context(argc,argv,thread_support::single)
    {}

    //! @brief Constructor with thread support
    //! Initialize the MPI environment at a given thread support level and gather informations
    //! @param ts   Expected [thread support level](@ref thread_support)
    context(thread_support ts)
    {
      init_thread(nullptr, nullptr, ts);
      prepare();
    }

    //! @brief Constructor from argc/argv with thread support
    //! Initialize the MPI environment at a given thread support level and gather informations
    //! @param argc `argc` Number of command line argument
    //! @param argv `argv` array of command line argument's strings
    //! @param ts   Expected [thread support level](@ref thread_support)
    context(int& argc, char**& argv, thread_support ts)
    {
      init_thread(&argc, &argv, ts);
      prepare();
    }

    //! @brief Destructor
    //! Teardown the MPI environment by calling `MPI_Finalize()`.
    ~context() { MPI_Finalize(); }

    // mmm::context is non-copyable
    context(context const&)             =delete;
    context& operator=(context const&)  =delete;

    //! Size of current MPI environment
    int         size() const noexcept { return size_; }

    //! Rank of current process in the current MPI environment
    int         rank() const noexcept { return rank_; }

    //! Node ID for current process
    std::string node_id() const noexcept { return id_; }

    //! Provided thread support
    thread_support thread_level;

    // Internal helpers
    private:

    int         size_;
    int         rank_;
    std::string id_;

    void init_thread(int* argc, char*** argv, thread_support ts)
    {
      int provided_level;
      MPI_Init_thread(argc, argv, static_cast<int>(ts), &provided_level);
      thread_level = static_cast<thread_support>(provided_level);
    }

    void prepare()
    {
      MPI_Comm_size(MPI_COMM_WORLD, &size_);
      MPI_Comm_rank(MPI_COMM_WORLD, &rank_);

      int length;
      char buffer[MPI_MAX_PROCESSOR_NAME];
      MPI_Get_processor_name(buffer, &length);
      id_ = std::string(&buffer[0], static_cast<std::string::size_type>(length));
    }
  };
}
