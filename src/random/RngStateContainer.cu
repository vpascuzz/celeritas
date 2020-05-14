//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file RngStateContainer.cu
//---------------------------------------------------------------------------//
#include "RngStateContainer.cuh"

#include "base/Assert.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with no states.
 */
RngStateContainer::RngStateContainer() = default;

//---------------------------------------------------------------------------//
/*!
 * Construct with an empty state
 */
RngStateContainer::RngStateContainer(size_type count) : rng_(count)
{
    ENSURE(rng_.size() == count);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
