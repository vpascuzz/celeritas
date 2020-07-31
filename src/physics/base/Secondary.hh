//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Secondary.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/Array.hh"
#include "base/Types.hh"
#include "sim/Types.hh"
#include "ParticleDef.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * New particle created via an Interaction.
 *
 * It will be converted into a track using the original track information.
 */
struct Secondary
{
    TrackId       parent_track_id; //!< Originating track ID
    ParticleDefId def_id;          //!< New particle type
    Real3         direction;       //!< New direction
    real_type     energy;          //!< New kinetic energy

    // Secondary failed to sample
    static inline CELER_FUNCTION Secondary from_failure();

    // Whether the secondary was successfully sampled
    explicit inline CELER_FUNCTION operator bool() const;
};

//---------------------------------------------------------------------------//
// INLINE FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * Construct with defaults.
 */
CELER_FUNCTION Secondary Secondary::from_failure()
{
    Secondary result;
    result.parent_track_id = {};
    return result;
}

//---------------------------------------------------------------------------//
/*!
 * Whether the Secondary succeeded
 */
CELER_FUNCTION Secondary::operator bool() const
{
    return static_cast<bool>(this->parent_track_id);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
