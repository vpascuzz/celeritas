//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Particle.hh
//---------------------------------------------------------------------------//
#ifndef physics_base_Particle_hh
#define physics_base_Particle_hh

#include "ParticleStateView.hh"
#include "ParticleParamsView.hh"
#include "base/Macros.hh"
#include "base/Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Access and modify physical properties of a particle track.
 */
class Particle
{
  public:
    //@{
    //! Type aliases
    using Initializer_t = ParticleStateVars;
    //@}

  public:
    // Construct from "dynamic" state and "static" particle definitions
    inline CELER_FUNCTION Particle(const ParticleParamsView& params,
                                   const ParticleStateView&  states,
                                   ThreadId                  id);

    // Initialize the particle
    inline CELER_FUNCTION Particle& operator=(const Initializer_t& other);

    // >>> DYNAMIC PROPERTIES

    // Unique particle type identifier
    inline CELER_FUNCTION ParticleDefId particle_type() const;

    // Kinetic energy [MeV]
    inline CELER_FUNCTION real_type kinetic_energy() const;

    // >>> STATIC PROPERTIES

    // Rest mass [MeV / c^2]
    inline CELER_FUNCTION real_type mass() const;

    // Charge
    inline CELER_FUNCTION real_type charge() const;

    // Decay constant
    inline CELER_FUNCTION real_type decay_constant() const;

    // >>> DERIVED PROPERTIES

    // Speed [1/c]
    inline CELER_FUNCTION real_type speed() const;

    // Lorentz factor [unitless]
    inline CELER_FUNCTION real_type lorentz_factor() const;

    // Relativistic momentum [MeV / c]
    inline CELER_FUNCTION real_type momentum() const;

    // Relativistic momentum squared [MeV^2 / c^2]
    inline CELER_FUNCTION real_type momentum_sq() const;

  private:
    const ParticleParamsView& params_;
    ParticleStateVars&        state_;

    inline CELER_FUNCTION const ParticleDef& particle_def() const;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "Particle.i.hh"

#endif // physics_base_Particle_hh
