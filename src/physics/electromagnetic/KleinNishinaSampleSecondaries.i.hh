//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file KleinNishinaSampleSecondaries.i.hh
//---------------------------------------------------------------------------//

#include "base/Assert.hh"
#include "KleinNishinaSampleSecondaries.hh"

namespace celeritas {
//---------------------------------------------------------------------------//
/*!
 * Construct with defaults.
 */
KleinNishinaSampleSecondaries::KleinNishinaSampleSecondaries()
{
    /*
  int numSecondaries = 0;
  const double kinetic_energy  = track.GetKinE();
  // check if kinetic energy is below fLowEnergyUsageLimit and do nothing if yes;
  // check if kinetic energy is above fHighEnergyUsageLimit andd o nothing if yes
  if (kinetic_energy < GetLowEnergyUsageLimit() || kinetic_energy > GetHighEnergyUsageLimit()) {
    return numSecondaries;
  }
  // sample post interaction gamma energy
  // here we need 3 random number + later one more for sampling phi
  double *rndArray = td->fDblArray;
  td->fRndm->uniform_array(4, rndArray);
  double eps, oneMinusCost, sint2;
  if (GetUseSamplingTables()) {
    eps                = SampleReducedPhotonEnergy(kinetic_energy, rndArray[0], rndArray[1], rndArray[2]);
    const double kappa = kinetic_energy / geant::units::kElectronMassC2;
    oneMinusCost       = (1. / eps - 1.) / kappa;
    sint2              = oneMinusCost * (2. - oneMinusCost);
  } else {
    eps = SampleReducedPhotonEnergy(kinetic_energy, oneMinusCost, sint2, td);
  }
  // compute gamma scattering angle (realtive to the origininal dir i.e. Z)
  sint2             = std::max(0., sint2);
  const double cost = 1.0 - oneMinusCost;
  const double sint = std::sqrt(sint2);
  const double phi  = geant::units::kTwoPi * (rndArray[3]);
  // direction of the scattered gamma in the scattering frame
  double dirX = sint * Math::Cos(phi);
  double dirY = sint * Math::Sin(phi);
  double dirZ = cost;
  // rotate back to lab frame
  Math::RotateToLabFrame(dirX, dirY, dirZ, track.GetDirX(), track.GetDirY(), track.GetDirZ());
  //
  // keep org. gamma dir in lab frame: will be updated but will be needed later
  const double orgGamDirX = track.GetDirX();
  const double orgGamDirY = track.GetDirY();
  const double orgGamDirZ = track.GetDirZ();
  // Update primary gamma track properties i.e. the scattered gamma
  double eDeposit         = 0.0;
  const double postGammaE = kinetic_energy * eps;
  if (postGammaE > GetLowestSecondaryEnergy()) {
    // update primary track kinetic energy
    track.SetKinE(postGammaE);
    // update primary track direction
    track.SetDirX(dirX);
    track.SetDirY(dirY);
    track.SetDirZ(dirZ);
  } else {
    eDeposit += postGammaE;
    track.SetKinE(0.0);
    track.SetTrackStatus(LTrackStatus::kKill);
  }
  //
  // Compute secondary e- properties: first the enrgy to check
  const double elEnergy = kinetic_energy - postGammaE; // E_el = E_0-E_1
  if (elEnergy > GetLowestSecondaryEnergy()) {
    // compute the secondary e- direction: from momentum vector conservation
    // final momentum of the secondary e- in the lab frame: = P_1-P_0 (binary col.)
    double elDirX = kinetic_energy * orgGamDirX - postGammaE * dirX;
    double elDirY = kinetic_energy * orgGamDirY - postGammaE * dirY;
    double elDirZ = kinetic_energy * orgGamDirZ - postGammaE * dirZ;
    // normalisation factor
    const double norm = 1.0 / std::sqrt(elDirX * elDirX + elDirY * elDirY + elDirZ * elDirZ);
    elDirX *= norm;
    elDirY *= norm;
    elDirZ *= norm;
    // create the secondary partcile i.e. the e-
    numSecondaries      = 1;
    LightTrack &emTrack = td->fPhysicsData->InsertSecondary();
    emTrack.SetDirX(elDirX);
    emTrack.SetDirY(elDirY);
    emTrack.SetDirZ(elDirZ);
    emTrack.SetKinE(elEnergy);
    emTrack.SetGVcode(fSecondaryInternalCode); // e- GV code
    emTrack.SetMass(geant::units::kElectronMassC2);
    emTrack.SetTrackIndex(track.GetTrackIndex()); // parent Track index
  } else {
    eDeposit += elEnergy;
  }
  //
  // set (possible) energy deposit
  track.SetEnergyDeposit(eDeposit);
  //
  // return with number of secondaries i.e. 1 or 0
  return numSecondaries;
     */
    
}


//---------------------------------------------------------------------------//
}  // namespace celeritas
