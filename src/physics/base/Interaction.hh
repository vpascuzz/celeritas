//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Interaction.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/Array.hh"
#include "base/Types.hh"
#include "sim/Action.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Change in state to a particle during an interaction.
 */
struct Interaction
{
    Real3     direction; //!< Post-interaction direction
    real_type energy;    //!< Post-interaction energy
    Action    action;    //!< Scatter, absorption, ...
};

//---------------------------------------------------------------------------//
} // namespace celeritas
