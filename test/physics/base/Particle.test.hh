//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Particle.test.hh
//---------------------------------------------------------------------------//

namespace celeritas_test
{
using namespace celeritas;

//---------------------------------------------------------------------------//
// TESTING INTERFACE
//---------------------------------------------------------------------------//
//! Input data
struct PTestInput
{
    ParticleParamsView             params;
    ParticleStateView              states;
    std::vector<ParticleStateVars> init;
};

//---------------------------------------------------------------------------//
//! Output results
struct PTestOutput
{
    std::vector<double> props;

    static CELER_CONSTEXPR_FUNCTION int props_per_thread() { return 8; }
};

//---------------------------------------------------------------------------//
//! Run on device and return results
PTestOutput p_test(PTestInput);

//---------------------------------------------------------------------------//
} // namespace celeritas_test
