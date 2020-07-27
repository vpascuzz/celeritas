//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryAllocator.test.cu
//---------------------------------------------------------------------------//
#include "SecondaryAllocator.test.hh"

#include <thrust/device_vector.h>
#include "base/KernelParamCalculator.cuda.hh"

using thrust::raw_pointer_cast;

namespace celeritas_test
{
//---------------------------------------------------------------------------//
// KERNELS
//---------------------------------------------------------------------------//

__global__ void sa_test_kernel(SATestInput input)
{
    unsigned int local_thread_id
        = celeritas::KernelParamCalculator::thread_id().get();
    if (local_thread_id >= input.num_threads)
        return;

    num_allocations[local_thread_id] = 0;

    StackAllocator allocate(input.sa_view);
    for (int i = 0; i < input.num_iters; ++i)
    {
        void* new_data = allocate(input.alloc_size);
        if (new_data)
        {
            ++num_allocations[local_thread_id];
        }
    }
}

//---------------------------------------------------------------------------//
// TESTING INTERFACE
//---------------------------------------------------------------------------//
//! Run on device and return results
SATestOutput sa_test(SATestInput input)
{
    celeritas::KernelParamCalculator calc_launch_params;
    auto params = calc_launch_params(input.num_threads);
    sa_test_kernel<<<params.grid_size, params.block_size>>>(input.num_threads);

    SATestOutput result;
    return result;
}

//---------------------------------------------------------------------------//
} // namespace celeritas_test
