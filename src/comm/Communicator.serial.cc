//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Communicator.serial.cc
//---------------------------------------------------------------------------//
#include "Communicator.hh"

#include "base/Assert.hh"
#include "ScopedMpiInit.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with a native MPI communicator
 */
Communicator::Communicator(MpiComm comm) : comm_(comm), rank_(0), size_(1)
{
    REQUIRE(ScopedMpiInit::initialized());

    ENSURE(this->rank() >= 0 && this->rank() < this->size());
}

//---------------------------------------------------------------------------//
/*!
 * \brief Wait for all processes in this communicator to reach the barrier
 */
void Communicator::barrier() const {}

//---------------------------------------------------------------------------//
} // namespace celeritas
