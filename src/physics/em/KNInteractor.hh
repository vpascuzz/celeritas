//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file KNInteractor.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/Macros.hh"
#include "base/Types.hh"
#include "physics/base/Interaction.hh"
#include "physics/base/ParticleTrackView.hh"
#include "physics/base/SecondaryAllocatorView.hh"
#include "physics/base/Secondary.hh"
#include "physics/base/Units.hh"
#include "KNInteractorPointers.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Interact
 *
 * Example
 * \code
  __global__ physics_do_it(...)
  {
      ParticleTrackView particle(particle_params, particle_state, tid);
      GeoTrackView geo(geom_params, geo_state, tid);
      RngTrackView rng(rng_state);
      SecondaryStackAllocatorView allocate_secondaries(secondary_store_params);

      // Apply cutoffs to incident particles

      Interaction result;
      if (sim.process_id == Processes::kn_interactor)
      {
          KNInteractor interact(kndata, particle, sim_state, geo.direction(),
          allocate_secondaries);
          result = interact(rng);
      }
      else if (...)
      {
          ... some other physics process
      }

      // Apply cutoffs to exiting secondaries
      // Copy parent track IDs to emitted secondaries
  }
  \endcode
 */
class KNInteractor
{
  public:
    // Construct sampler from shared and state data
    inline CELER_FUNCTION KNInteractor(const KNInteractorPointers& shared,
                                       const ParticleTrackView&    particle,
                                       const Real3&            inc_direction,
                                       SecondaryAllocatorView& allocate);

    // Sample an interaction with the given RNG
    template<class Engine>
    inline CELER_FUNCTION Interaction operator()(Engine& rng);

    // >>> COMMON PROPERTIES

    // Minimum incident energy for this model to be valid
    static CELER_CONSTEXPR_FUNCTION real_type min_incident_energy()
    {
        return 10 * units::kilo_electron_volt;
    }

    // Maximum loops to allow over the rejection function
    static CELER_CONSTEXPR_FUNCTION int max_rejection_loops() { return 1024; }

  private:
    // Gamma energy divided by electron mass * csquared
    const real_type inv_electron_mass_csq_;
    // Incident gamma energy
    const real_type inc_energy_;
    // Incident direction
    const Real3& inc_direction_;
    // Allocate space for a secondary particle
    SecondaryAllocatorView& allocate_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "KNInteractor.i.hh"
