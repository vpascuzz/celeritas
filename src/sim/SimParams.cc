//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SimParams.cc
//---------------------------------------------------------------------------//
#include "SimParams.hh"

#include "base/Macros.hh"
#include "celeritas_config.h"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * \brief Construct with a vector of particle definitions
 */
SimParams::SimParams()
{
}

//---------------------------------------------------------------------------//
/*!
 * Get a view to the managed data.
 */
SimParamsView SimParams::device_view() const
{
    SimParamsView result;
    return result;
}

//---------------------------------------------------------------------------//
} // namespace celeritas
