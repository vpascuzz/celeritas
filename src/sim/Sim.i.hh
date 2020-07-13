//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Sim.i.hh
//---------------------------------------------------------------------------//

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct from persistent and local data.
 */
CELER_FUNCTION
Sim::Sim(const SimParamsView& params, const SimStateView& states, ThreadId id)
    : params_(params), state_(states.vars[id.get()])
{
    REQUIRE(id < states.vars.size());
}

//---------------------------------------------------------------------------//
/*!
 * \brief Initialize the particle
 */
CELER_FUNCTION Sim& Sim::operator=(const Initializer_t& other)
{
    REQUIRE(other.particle_type < params_.defs.size());
    REQUIRE(other.kinetic_energy > 0);
    state_ = other;
    return *this;
}

//---------------------------------------------------------------------------//
} // namespace celeritas
