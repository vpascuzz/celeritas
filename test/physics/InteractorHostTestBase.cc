//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file InteractorHostTestBase.cc
//---------------------------------------------------------------------------//
#include "InteractorHostTestBase.hh"

#include "base/ArrayUtils.hh"
#include "physics/base/SecondaryAllocatorView.hh"
#include "physics/base/ParticleTrackView.hh"

namespace celeritas_test
{
//---------------------------------------------------------------------------//
/*!
 * Initialize secondary allocation on construction.
 */
InteractorHostTestBase::InteractorHostTestBase()
{
    secondaries_.resize(128);
}

//---------------------------------------------------------------------------//
/*!
 * Default destructor.
 */
InteractorHostTestBase::~InteractorHostTestBase() = default;

//---------------------------------------------------------------------------//
/*!
 * Set particle parameters.
 */
void InteractorHostTestBase::set_particle_params(
    const ParticleParams::VecAnnotatedDefs& defs)
{
    REQUIRE(!defs.empty());
    particle_params_ = std::make_shared<ParticleParams>(defs);
}

//---------------------------------------------------------------------------//
/*!
 * Access particle parameters.
 */
const ParticleParams& InteractorHostTestBase::particle_params() const
{
    REQUIRE(particle_params_);
    return *particle_params_;
}

//---------------------------------------------------------------------------//
/*!
 * Initialize the incident particle data.
 */
void InteractorHostTestBase::set_inc_particle(PDGNumber pdg, real_type energy)
{
    REQUIRE(particle_params_);
    REQUIRE(pdg);
    REQUIRE(energy > 0);

    particle_state_.particle_type  = particle_params_->find(pdg);
    particle_state_.energy         = energy;
}

//---------------------------------------------------------------------------//
/*!
 * Set an incident direction (and normalize it).
 */
void InteractorHostTestBase::set_inc_direction(const Real3& dir)
{
    REQUIRE(celeritas::norm(dir) > 0);

    inc_direction_ = dir;
    normalize_direction(&inc_direction_);
}

//---------------------------------------------------------------------------//
/*!
 * Get the particle track view corresponding to the set particle.
 */
ParticleTrackView InteractorHostTestBase::particle_track()
{
    REQUIRE(particle_params_);
    REQUIRE(particle_state_.particle_type);

    ParticleStatePointers state;
    state.vars = {&particle_state_, 1};

    return ParticleTrackView(
        particle_params_->host_pointers(), state, ThreadId{0});
}

//---------------------------------------------------------------------------//
} // namespace celeritas_test
