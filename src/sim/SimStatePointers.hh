//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SimStatePointers.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/Span.hh"
#include "Types.hh"
#include "AccumPathLength.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Simulation state of a track.
 *
 * This contains quantities for managing the flow of the simulation.
 *
 * TODO: preliminary sketch; not sure which of these all should be here, or
 * what else should be here.
 */
struct SimStateVars
{
    real_type       clock = 0;       // "Real-world" from event start [s]
    AccumPathLength path;            // Accumulated path length [cm]
    TrackId         track_id;        // Unique ID for this track
    TrackId         parent_track_id; // ID of parent that created it
    EventId         event_id;        // ID of originating event
    ActionId        next_action;     // Next step-limiting action
};

//---------------------------------------------------------------------------//
/*!
 * View to the simulation states of multiple tracks.
 */
struct SimStatePointers
{
    span<SimStateVars> vars;

    //! Check whether the view is assigned
    explicit inline CELER_FUNCTION operator bool() const
    {
        return !vars.empty();
    }
};

//---------------------------------------------------------------------------//
} // namespace celeritas
