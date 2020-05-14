//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Rng.cuh
//---------------------------------------------------------------------------//
#ifndef random_Rng_cuh
#define random_Rng_cuh

#include <cstddef>

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Sample random numbers on device.
 */
class CurngEngine
{
  public:
    //@{
    //! Type aliases
    using result_type = unsigned int;
    using size_type   = std::size_t;
    //@}

    struct State
    {
        CuRandState* rng = nullptr;
    };

  public:
    // Construct from state
    inline CurngEngine(State state);

    // Sample a random number
    inline __device__ result_type operator()();

    // Sample multiple random numbers
    inline __device__ void operator()(result_type* out, size_type count);

  private:
    State state_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "CurngEngine.i.cuh"

#endif // random_Rng_cuh
