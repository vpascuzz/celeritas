//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file ParticleParamsView.hh
//---------------------------------------------------------------------------//
#ifndef physics_base_ParticleParamsView_hh
#define physics_base_ParticleParamsView_hh

#include "base/Macros.hh"
#include "base/Span.hh"
#include "ParticleDef.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Access particle definitions on the device.
 *
 * This view is created from \c ParticleParams.
 */
struct ParticleParamsView
{
    span<const ParticleDef> defs;

    //! Check whether the view is assigned
    explicit inline CELER_FUNCTION operator bool() const
    {
        return !defs.empty();
    }
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#endif // physics_base_ParticleParamsView_hh
