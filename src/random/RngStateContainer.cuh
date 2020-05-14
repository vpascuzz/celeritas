//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file RngStateContainer.cuh
//---------------------------------------------------------------------------//
#ifndef random_RngStateContainer_cuh
#define random_RngStateContainer_cuh

#include <thrust/device_vector.h>

#include "base/Types.hh"
#include "RngStateView.cuh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Manage ownership of on-device random number generator.
 */
class RngStateContainer
{
  public:
    //@{
    //! Type aliases
    using size_type   = celeritas::size_type;
    using CuRandState = RngStateView::CuRandState;
    //@}

  public:
    // Default constructor
    RngStateContainer();

    // Construct with the number of RNG states
    RngStateContainer(size_type count);

    // Emit a view to on-device memory
    inline RngStateView device_view();

    //! Number of states
    size_type size() const { return rng_.size(); }

  private:
    thrust::device_vector<CuRandState> rng_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "RngStateContainer.i.cuh"

#endif // random_RngStateContainer_cuh
