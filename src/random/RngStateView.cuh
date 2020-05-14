//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file RngStateView.cuh
//---------------------------------------------------------------------------//
#ifndef random_RngStateView_cuh
#define random_RngStateView_cuh

#include "base/Assert.hh"
#include "RngStateRef.cuh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Device view to a vector of CUDA random number generator states.
 *
 * This "view" is expected to be an argument to a geometry-related kernel
 * launch.
 */
class RngStateView
{
  public:
    //@{
    //! Type aliases
    using value_type  = Rng;
    using CuRandState = Rng::CuRandState;
    //@}

    //! Construction parameters
    struct Params
    {
        size_type    size = 0;
        CuRandState* rng  = nullptr;
    };

  public:
    //! Construct on host with invariant parameters
    explicit RngStateView(const Params& params) : data_(params)
    {
        REQUIRE(data_.size > 0);
        REQUIRE(data_.vgnext);
        assert(data_.pos);
        assert(data_.dir);
        assert(data_.next_step);
    }

    //! Number of states
    __device__ size_type size() const { return data_.size; }

    //! Get a reference to the local state for a thread
    __device__ curandState_t* operator[](size_type idx) const
    {
        REQUIRE(idx < this->size());
        RngStateRef::Params params;
        params.rng = data_.rng + idx;
        return value_type(params);
    }

  private:
    Params data_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#endif // random_RngStateView_cuh
