//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file KleinNishinaInteractorPointers.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Device data for creating a KleinNishinaInteractor.
 */
struct KleinNishinaInteractorPointers
{
    //! Gamma energy divided by electron mass * csquared
    real_type inv_electron_mass_csq;
    //! ID of an electron
    ParticleDefId electron_id;
    //! ID of a gamma
    ParticleDefId gamma_id;
};

//---------------------------------------------------------------------------//
} // namespace celeritas