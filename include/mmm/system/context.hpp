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

namespace mmm
{
  //================================================================================================
  //! @struct context_handle
  //! @brief RAII-enabled MPI setup object
  //!
  //! mmm::context_handle encapsulates all the MPI setup and teardown process in a RAII enabled
  //! type. It also provides access to persistent informations about the MPI environment like
  //! size, rank and node ID.
  //================================================================================================
  struct context_handle
  {
    //! @brief Default constructor
    //! Initialize the MPI environment via `MPI_Init` and gather persistent informations
    context_handle()
    {
      MPI_Init(nullptr,nullptr);
      MPI_Comm_size(MPI_COMM_WORLD, &size);
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      int length;
      char buffer[MPI_MAX_PROCESSOR_NAME];
      MPI_Get_processor_name(buffer, &length);
      node_id = std::string(&buffer[0], static_cast<std::string::size_type>(length));
    }

    //! @brief Destructor
    //! Teardown the MPI environment by calling `MPI_Finalize()`.
    ~context_handle() { MPI_Finalize(); }

    // mmm::context_handle is non-copyable
    context_handle(context_handle const&) =delete;
    context_handle& operator=(context_handle const&) =delete;

    void synchronize() const
    {
      MPI_Barrier(MPI_COMM_WORLD);
    }

    //! Size of current MPI environment
    int         size;
    //! Rank of current process in the current MPI environment
    int         rank;
    //! Node ID for current process
    std::string node_id;
  };

  //! @var context
  //! @brief Global MPI environment [handle](@ref mmm::context_handle)
  inline context_handle const context = {};
}
