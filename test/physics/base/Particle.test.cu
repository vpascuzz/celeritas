//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Particle.test.cu
//---------------------------------------------------------------------------//
#include "physics/base/Particle.hh"
#include "Particle.test.hh"

#include <thrust/device_vector.h>
#include "base/KernelParamCalculator.cuda.hh"

using thrust::raw_pointer_cast;

namespace celeritas_test
{
//---------------------------------------------------------------------------//
// KERNELS
//---------------------------------------------------------------------------//

__global__ void p_test_kernel(unsigned int             size,
                              ParticleParamsView       params,
                              ParticleStateView        states,
                              const ParticleStateVars* init,
                              double*                  result)
{
    auto local_thread_id = celeritas::KernelParamCalculator::thread_id();
    if (!(local_thread_id < size))
        return;

    // Initialize particle
    Particle p(params, states, local_thread_id);
    p = init[local_thread_id.get()];

    // Skip result to the start for this thread
    result += local_thread_id.get() * PTestOutput::props_per_thread();

    // Calculate/write values from Particle
    CHECK(p.particle_type() == init[local_thread_id.get()].particle_type);
    *result++ = p.kinetic_energy();
    *result++ = p.mass();
    *result++ = p.elem_charge();
    *result++ = p.decay_constant();
    *result++ = p.speed();
    *result++ = (p.mass() > 0 ? p.lorentz_factor() : -1);
    *result++ = p.momentum();
    *result++ = p.momentum_sq();
}

//---------------------------------------------------------------------------//
// TESTING INTERFACE
//---------------------------------------------------------------------------//
//! Run on device and return results
PTestOutput p_test(PTestInput input)
{
    thrust::device_vector<ParticleStateVars> init = input.init;
    thrust::device_vector<double>    result(init.size()
                                         * PTestOutput::props_per_thread());

    celeritas::KernelParamCalculator calc_launch_params;
    auto                             params = calc_launch_params(init.size());
    p_test_kernel<<<params.grid_size, params.block_size>>>(
        init.size(),
        input.params,
        input.states,
        raw_pointer_cast(init.data()),
        raw_pointer_cast(result.data()));

    PTestOutput output;
    output.props.resize(result.size());
    thrust::copy(result.begin(), result.end(), output.props.begin());
    return output;
}

//---------------------------------------------------------------------------//
} // namespace celeritas_test
