//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Secondary.hh
//---------------------------------------------------------------------------//
#ifndef physics_base_Secondary_hh
#define physics_base_Secondary_hh

#include "base/Array.hh"
#include "base/Types.hh"
#include "sim/Types.hh"
#include "ParticleDef.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * New particle created via a Process interaction.
 */
struct Secondary
{
    TrackId       parent_track_id; //!< Originating track ID
    ParticleDefId def_id;          //!< New particle type
    Real3         direction;       //!< New particle direction
    real_type     energy;          //!< New energy
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#endif // physics_base_Secondary_hh
