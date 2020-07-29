//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file InteractorHostTestBase.hh
//---------------------------------------------------------------------------//
#pragma once

#include <memory>
#include <random>
#include <vector>
#include "gtest/Test.hh"
#include "base/Array.hh"
#include "base/Span.hh"
#include "base/StackAllocatorPointers.hh"
#include "base/Types.hh"
#include "physics/base/ParticleParams.hh"
#include "physics/base/ParticleStatePointers.hh"

namespace celeritas
{
class SecondaryAllocatorView;
class ParticleParams;
class ParticleTrackView;
struct Secondary;
} // namespace celeritas

namespace celeritas_test
{
using namespace celeritas;
//---------------------------------------------------------------------------//
/*!
 * Test harness base class for a host-side Interactor.
 *
 * This class initializes host versions of some of the common inputs to an
 * Interactor. It \b cannot be used for testing device instantiations.
 */
class InteractorHostTestBase : public celeritas::Test
{
  public:
    //@{
    //! Type aliases
    using RandomEngine         = std::mt19937;
    using constSpanSecondaries = span<const Secondary>;
    //@}

  public:
    //@{
    //! Initialize and destroy
    InteractorHostTestBase();
    ~InteractorHostTestBase();
    //@}

    //@{
    //! Set and get particle params
    void set_particle_params(const ParticleParams::VecAnnotatedDefs& defs);
    const ParticleParams& particle_params() const;
    //@}

    //@{
    //! Incident particle properties and access
    void              set_inc_particle(PDGNumber n, real_type energy);
    void              set_inc_direction(const Real3& dir);
    ParticleTrackView particle_track();
    const Real3&      direction() const { return inc_direction_; }
    //@}

    //@{
    //! Secondary stack storage and access
    void                   reallocate_secondaries(size_type capacity);
    void                   clear_secondaries();
    SecondaryAllocatorView secondary_allocator();
    constSpanSecondaries   secondaries() const;
    //@}

    //@{
    //! Random number generator
    RandomEngine& rng() { return rng_; }
    //@}

  private:
    std::shared_ptr<ParticleParams> particle_params_;
    ParticleTrackState              particle_state_;
    Real3                           inc_direction_ = {0, 0, 1};

    std::vector<celeritas::byte>      secondary_storage_;
    StackAllocatorPointers::size_type secondary_size_;
    StackAllocatorPointers            secondary_pointers_;

    RandomEngine rng_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas_test
