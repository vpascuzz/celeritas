//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SimTrackView.hh
//---------------------------------------------------------------------------//
#pragma once

#include "SimParamsPointers.hh"
#include "SimStatePointers.hh"
#include "base/Macros.hh"
#include "base/Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Simulation properties for a single track.
 *
 * Manage the simulation state.
 */
class SimTrackView
{
  public:
    //@{
    //! Type aliases
    using Initializer_t = SimStateVars;
    //@}

  public:
    // Construct with view to state and persistent data
    inline SimStateVars(const SimParamsPointers& params,
                        const SimStatePointers&  state,
                        ThreadId                 thread);

    // Initialize the sim state
    inline CELER_FUNCTION SimTrackView& operator=(const Initializer_t& other);

  private:
    const SimParamsPointers& params_;
    SimStateVars&            state_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "SimTrackView.i.hh"
