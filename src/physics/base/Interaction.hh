//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Interaction.hh
//---------------------------------------------------------------------------//
#ifndef physics_base_Interaction_hh
#define physics_base_Interaction_hh

#include "base/Types.hh"
#include "Action.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Change in state to a particle during an interaction.
 */
struct Interaction
{
    real_type delta_phi;
    real_type energy; //!< Post-interaction energy
    Action    action; //!< Scatter, absorption, ...
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "Interaction.i.hh"

#endif // physics_base_Interaction_hh
