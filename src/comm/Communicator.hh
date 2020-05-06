//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Communicator.hh
//---------------------------------------------------------------------------//
#ifndef comm_Communicator_hh
#define comm_Communicator_hh

#include "Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Abstraction of an MPI communicator.
 */
class Communicator
{
  public:
    // Construct with a native MPI communicator
    explicit Communicator(MpiComm comm);

    //! Construct with world comm
    Communicator() : Communicator(MPI_COMM_WORLD) {}

    // Prevent copying until we add comm_dup
    Communicator(const Communicator&) = delete;
    Communicator& operator=(const Communicator&) = delete;

    // >>> ACCESSORS

    //! Get the MPI communicator for low-level MPI calls
    MpiComm mpi_comm() const { return comm_; }

    //! Get the local process ID
    int rank() const { return rank_; }

    //! Get the number of total processors
    int size() const { return size_; };

    // >>> FUNCTIONS

    // Wait for all processes in this communicator to reach the barrier
    void barrier() const;

    // TODO: Nemesis HDF5-like interface for send/recv/reduce/etc.

  private:
    MpiComm comm_;
    int     rank_;
    int     size_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#endif // comm_Communicator_hh
