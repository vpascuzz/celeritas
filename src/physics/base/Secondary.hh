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
 * New particle created via an Interaction. It will be converted into a track
 * using the original track information.
 */
struct Secondary
{
    TrackId       parent_track_id; //!< Originating track ID
    ParticleDefId def_id;          //!< New particle type
    Real3         direction;       //!< New direction
    real_type     energy;          //!< New energy

    // Secondary failed to sample
    static inline CELER_FUNCTION Secondary from_failure();

    // Whether the secondary was successfully sampled
    explicit inline CELER_FUNCTION operator bool() const;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "Secondary.i.hh"
