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

#if !defined(MMM_THREAD_SUPPORT)
#define MMM_THREAD_SUPPORT ::mmm::thread_support::single
#endif

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
  //! @struct mpi_context
  //! @brief RAII-enabled MPI setup object
  //!
  //! mmm::mpi_context encapsulates all the MPI setup and teardown process in a RAII enabled
  //! type. It also provides access to persistent informations about the MPI environment like
  //! size, rank and node ID.
  //================================================================================================
  struct mpi_context
  {
    //! @brief Default constructor
    //! Initialize the MPI environment and gather informations
    mpi_context()
    {
      init_thread(nullptr, nullptr, MMM_THREAD_SUPPORT);
      prepare();
    }

    //! @brief Destructor
    //! Teardown the MPI environment by calling `MPI_Finalize()`.
    ~mpi_context() { MPI_Finalize(); }

    // mmm::mpi_context is non-copyable
    mpi_context(mpi_context const&)             =delete;
    mpi_context& operator=(mpi_context const&)  =delete;

    //! Size of current MPI environment
    int         size() const noexcept { return size_; }

    //! Rank of current process in the current MPI environment
    int         rank() const noexcept { return rank_; }

    //! Node ID for current process
    std::string node_id() const noexcept { return id_; }

    //! Provided thread support
    thread_support threading() const noexcept { return threading_; }

    // Internal helpers
    private:

    std::string     id_;
    thread_support  threading_;
    int             size_;
    int             rank_;

    void init_thread(int* argc, char*** argv, thread_support ts)
    {
      int provided_level;
      MPI_Init_thread(argc, argv, static_cast<int>(ts), &provided_level);
      threading_ = static_cast<thread_support>(provided_level);
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


  inline const mpi_context context = {};
}
