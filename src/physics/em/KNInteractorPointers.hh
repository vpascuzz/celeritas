//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file KNInteractorPointers.hh
//---------------------------------------------------------------------------//
#pragma once

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Device data for creating a KNInteractor.
 */
struct KNInteractorPointers
{
    real_type inv_electron_mass_csq;
};

//---------------------------------------------------------------------------//
} // namespace celeritas
