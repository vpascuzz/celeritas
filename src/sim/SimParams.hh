//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SimParams.hh
//---------------------------------------------------------------------------//
#pragma once

#include "SimParamsPointers.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Persistent simulation data.
 *
 * TODO: not sure exactly what goes here: maybe manage the various action
 * classes?
 */
class SimParams
{
  public:
    //@{
    //!
    //@}

  public:
    // Construct with a vector of particle definitions
    SimParams();

    // >>> DEVICE ACCESSORS

    // Get a view to the managed data
    SimParamsPointers device_pointers() const;

  private:
};

//---------------------------------------------------------------------------//
} // namespace celeritas
