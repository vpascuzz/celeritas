//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file KleinNishinaSampleSecondaries.i.hh
//---------------------------------------------------------------------------//

#include <cmath>

#include "base/Assert.hh"
#include "physics/base/ConstantsAndUnits.hh"
#include "physics/base/ThreeVector.hh"
#include "KleinNishinaSampleSecondaries.hh"


namespace celeritas {
//---------------------------------------------------------------------------//
/*!
 * Construct with defaults.
 */
KleinNishinaSampleSecondaries::KleinNishinaSampleSecondaries()
:
{}

class KNProcess
{
  private:
    const ProcessParam& params_;
    ProcessStateVars&   state_;

    VGAccessor geometry_;
    Particle   particle_;
};

struct ProcessParams
{
    ParticleDefId   electron_type;
    const real_type inv_electron_mass_csquared; // calculated on host

    // Data required for all processes?
};

struct ProcessState
{
    //! Allocate space for secondaries being produced
    Secondary* secondaries;
};

void KNProcess::allocate_secondaries()
{
    REQUIRE(!state_.secondaries);
    // Klein-Nishina always emits a single electron
    state_.secondaries = shared.alloc_secondaries(1);
}

Interaction KNProcess::sample_secondaries()
{
    REQUIRE(state_.secondaries);

    using constants::two_pi;
    using units::electron_volt;

    // The scattered gamma energy is sampled according to Klein - Nishina
    // formula.
    // The random number techniques of Butcher & Messel are used
    // (Nuc Phys 20(1960),15).
    // Note: Effects due to binding of atomic electrons are negliged.

    // Placeholder. To be replaced by a particle->GetEnergy() type function
    real_type particle_.kinetic_energy() = 10;

    // Placeholder. Change if needed
    real_type const lowest_secondary_energy = 100 * units::electron_volt;

    // Placeholder. To be replaced by a GetLowEnergy() type function
    real_type low_energy_limit = 10;

    // If below energy limit, stop
    if (gamma_initial_energy <= low_energy_limit)
    {
        return;
    }

    real_type gamma_initial_energy_per_mc2 = gamma_initial_energy
                                             * params_.inv_electron_mass_csq;

    // Original G4 code
    // G4ThreeVector gamma_initial_direction =
    // aDynamicGamma->GetMomentumDirection();

    // Testing with a one axis direction to get a delta
    ThreeVector gamma_initial_direction(1, 0, 0);

    //
    // sample the energy rate of the scattered gamma
    //
    real_type epsilon, epsilon_squared;
    real_type one_minus_cosTheta, sinTheta_squared;
    real_type g_rejection_function;

    real_type epsilon_0 = 1. / (1. + 2. * gamma_initial_energy_per_mc2);
    real_type epsilon_0_squared = epsilon_0 * epsilon_0;
    real_type alpha_1           = -std::log(epsilon_0);
    real_type alpha_2           = alpha_1 + 0.5 * (1. - epsilon_0_squared);

    real_type random_array[3];

    static const int loop_limit = 1000;

    // False interaction if there are too many interations
    for (int loop = 0; loop < loop_limit; loop++)
    {
        // Selecting 3 random numbers to sample scattering
        // Need to use Celeritas' Random, but that is not ready
        // Adding fixed numbers as placeholders
        // Random numbers must be of type random.Uniform(0, 1)

        random_array[3] = {0.2, 0.4, 0.8}; // FIX RANDOM NUMBER

        if (alpha_1 > alpha_2 * random_array[0])
        {
            epsilon = std::exp(-alpha_1 * random_array[1]); // epsilon_0^r
            epsilon_squared = epsilon * epsilon;
        }

        else
        {
            epsilon_squared = epsilon_0_squared
                              + (1. - epsilon_0_squared) * random_array[1];
            epsilon = std::sqrt(epsilon_squared);
        }

        one_minus_cosTheta = (1. - epsilon)
                             / (epsilon * gamma_initial_energy_per_mc2);

        sinTheta_squared = one_minus_cosTheta * (2. - one_minus_cosTheta);

        g_rejection_function
            = 1. - epsilon * sinTheta_squared / (1. + epsilon_squared);

        // Testing the rejection function. Accept epsilon, otherwise repeat
        if (g_rejection_function >= random_array[2])
        {
            break;
        }
    }

    // Scattered gamma angles (z-axis along the parent gamma)
    if (sinTheta_squared < 0.0)
    {
        sinTheta_squared = 0.0;
    }

    // Placeholder for a random.Uniform() number for Phi
    real_type a_random_uniform = 0.5;

    real_type cosTheta = 1. - one_minus_cosTheta;
    real_type sinTheta = std::sqrt(sinTheta_squared);
    real_type Phi = two_pi * a_random_uniform; // FIX RANDOM NUMBER AND TWO_PI

    //------------ Update particle info for the scattered gamma -------------//

    ThreeVector gamma_final_direction(
        sinTheta * std::cos(Phi), sinTheta * std::sin(Phi), cosTheta);

    // Original G4 code
    // gamma_final_direction.rotateUz(gamma_initial_direction);

    real_type gamma_final_energy = epsilon * gamma_initial_energy;
    real_type energy_deposited   = 0.0;

    if (gamma_final_energy > lowest_secondary_energy)
    {
        // fParticleChange->ProposeMomentumDirection(gamma_final_direction);
        // fParticleChange->SetProposedKineticEnergy(gamma_final_energy);
    }

    else
    {
        // fParticleChange->ProposeTrackStatus(fStopAndKill);
        // fParticleChange->SetProposedKineticEnergy(0.0);
        energy_deposited = gamma_final_energy;
    }

    // Kinematics of the scattered electron
    real_type electron_kinetic_energy = gamma_initial_energy
                                        - gamma_final_energy;

    if (electron_kinetic_energy > lowest_secondary_energy)
    {
        // Original G4 code
        // G4ThreeVector eDirection =
        // gamma_initial_energy*gamma_initial_direction -
        // gamma_final_energy*gamma_final_direction;

        ThreeVector electron_final_direction
            = gamma_initial_direction * gamma_initial_energy
              - gamma_final_direction * gamma_final_energy;

        electron_final_direction(electron_final_direction.dirX(),
                                 electron_final_direction.dirY(),
                                 electron_final_direction.dirZ());

        // Original G4 code
        // create G4DynamicParticle object for the electron.
        // G4DynamicParticle* dp = new
        // G4DynamicParticle(theElectron,eDirection,electron_kinetic_energy);
        // fvect->push_back(dp);
    }

    else
    {
        energy_deposited += electron_kinetic_energy;
    }

    // energy balance
    if (energy_deposited > 0.0)
    {
        // fParticleChange->ProposeLocalEnergyDeposit(energy_deposited);
    }
}

//---------------------------------------------------------------------------//
}  // namespace celeritas
