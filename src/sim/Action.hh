//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Action.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/Macros.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Broad categories of events applied to a particle in a track.
 */
enum class ActionCategory
{
    birth,   //!< Primary particle from an event or creation of a secondary
    cell,    //!< Enter a new cell
    scatter, //!< Undergo a scattering event
    // KILLING ACTIONS BELOW
    begin_kill_,
    absorb = begin_kill_, //!< Absorbed (killed)
    energy_cutoff,        //!< Below energy cutoff (killed)
    escape,               //!< Exited geometry (killed)
    end_kill_
};

//---------------------------------------------------------------------------//

//! Whether the given action should kill the active track
inline CELER_FUNCTION bool action_kills(Action);

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "Action.i.hh"
