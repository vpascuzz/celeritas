//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryStackAllocator.i.hh
//---------------------------------------------------------------------------//

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with defaults.
 */
CELER_FUNCTION SecondaryStackAllocator::SecondaryStackAllocator(
    const SecondaryStackView& shared)
    : allocate_(shared.allocator_view)
{
}

//---------------------------------------------------------------------------//
/*!
 * Allocate space for this many secondaries.
 *
 * Returns NULL if allocation failed due to out-of-memory.
 */
CELER_FUNCTION result_type operator()(size_type count)
{
    void* alloc = this->allocate_(count * sizeof(Secondary));
    return static_cast<result_type>(alloc);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
