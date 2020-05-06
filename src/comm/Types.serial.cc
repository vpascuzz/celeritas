//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Types.serial.cc
//---------------------------------------------------------------------------//
#include "Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
//! Const global data
const MpiComm MPI_COMM_WORLD{-2};
const MpiComm MPI_COMM_SELF{-1};
const MpiComm MPI_COMM_NULL{0};

//---------------------------------------------------------------------------//
} // namespace celeritas
