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
    this->reallocate_secondaries(128);
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
    particle_state_.kinetic_energy = energy;
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
/*!
 * Clear and reserve a new amount of secondary tracks.
 */
void InteractorHostTestBase::reallocate_secondaries(size_type capacity)
{
    REQUIRE(capacity > 0);
    this->clear_secondaries();
    secondary_storage_.resize(capacity * sizeof(Secondary));
    secondary_size_             = 0;
    secondary_pointers_.storage = make_span(secondary_storage_);
    secondary_pointers_.size    = &secondary_size_;

    ENSURE(secondary_pointers_);
}

//---------------------------------------------------------------------------//
/*!
 * Reset the number of stored secondaries.
 */
void InteractorHostTestBase::clear_secondaries()
{
    secondary_size_ = 0;
}

//---------------------------------------------------------------------------//
/*!
 * Return a view to (host-owned) secondary allocator.
 */
SecondaryAllocatorView InteractorHostTestBase::secondary_allocator()
{
    REQUIRE(secondary_pointers_);
    SecondaryAllocatorPointers ptrs;
    ptrs.allocator = secondary_pointers_;
    return SecondaryAllocatorView(ptrs);
}

//---------------------------------------------------------------------------//
/*!
 * Access secondaries that have been created.
 */
auto InteractorHostTestBase::secondaries() const -> constSpanSecondaries
{
    // XXX need c++17 "launder" for this to not be UB
    return {reinterpret_cast<const Secondary*>(secondary_storage_.data()),
            secondary_size_ / sizeof(Secondary)};
}

//---------------------------------------------------------------------------//
} // namespace celeritas_test
