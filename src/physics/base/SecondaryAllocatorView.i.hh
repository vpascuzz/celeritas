//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryAllocatorView.i.hh
//---------------------------------------------------------------------------//

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with defaults.
 */
CELER_FUNCTION SecondaryAllocatorView::SecondaryAllocatorView(
    const SecondaryAllocatorPointers& shared)
    : allocate_(shared.allocator)
{
}

//---------------------------------------------------------------------------//
/*!
 * Allocate space for this many secondaries.
 *
 * Returns NULL if allocation failed due to out-of-memory.
 */
CELER_FUNCTION auto SecondaryAllocatorView::operator()(size_type count)
    -> result_type
{
    void* alloc = this->allocate_(count * sizeof(Secondary));
    if (CELER_UNLIKELY(!alloc))
    {
        // Out of memory
        return nullptr;
    }
    return new (alloc) Secondary[count];
}

//---------------------------------------------------------------------------//
/*!
 * View all allocated secondaries (NOT THREAD SAFE).
 */
CELER_FUNCTION auto SecondaryAllocatorView::secondaries() -> SpanSecondary
{
    // Transform size and data from bytes to secondary
    auto size = this->allocate_.size() / sizeof(Secondary);
    return {reinterpret_cast<Secondary*>(this->allocate_.data()), size};
}

//---------------------------------------------------------------------------//
} // namespace celeritas
