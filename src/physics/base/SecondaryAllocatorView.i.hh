//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryAllocatorView.i.hh
//---------------------------------------------------------------------------//

#include "base/Atomics.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with defaults.
 */
CELER_FUNCTION SecondaryAllocatorView::SecondaryAllocatorView(
    const SecondaryAllocatorPointers& shared)
    : shared_(shared)
{
    REQUIRE(shared);
}

//---------------------------------------------------------------------------//
/*!
 * Allocate space for this many secondaries.
 *
 * Returns NULL if allocation failed due to out-of-memory. Ensures that the
 * shared size reflects the amount of data allocated
 */
CELER_FUNCTION auto SecondaryAllocatorView::operator()(size_type count)
    -> result_type
{
    // Atomic add 'count' to the shared size
    size_type start = atomic_add(shared_.size, count);
    if (CELER_UNLIKELY(start + count > shared_.storage.size()))
    {
        // Out of memory: restore the old value so that another thread can
        // potentially use it. Other threads might have given up in the
        // meantime and incremented the "size" beyond the value we have, but we
        // can be sure that none has allocated successfully. With this logic we
        // can ensure that `shared_.size` is always accurate.
        *shared_.size = start;

        // TODO It might be useful to set an "out of memory" flag to make it
        // easier for host code to detect whether a failure occurred, rather
        // than looping through primaries and testing for failure.

        // Return null pointer, indicating failure to allocate.
        return nullptr;
    }

    // Initialize the data at the newly "allocated" address
    return new (shared_.storage.data() + start) Secondary[count];
}

//---------------------------------------------------------------------------//
/*!
 * View all allocated secondaries.
 *
 * This cannot be called while any running kernel could be modifiying the size.
 */
CELER_FUNCTION auto SecondaryAllocatorView::secondaries() -> SpanSecondary
{
    REQUIRE(*shared_.size <= shared_.storage.size());
    return {shared_.storage.data(), *shared_.size};
}

//---------------------------------------------------------------------------//
/*!
 * View all allocated secondaries (immutable).
 *
 * This cannot be called while any running kernel could be modifiying the size.
 */
CELER_FUNCTION auto SecondaryAllocatorView::secondaries() const
    -> constSpanSecondary
{
    REQUIRE(*shared_.size < shared_.storage.size());
    return {shared_.storage.data(), *shared_.size};
}
//---------------------------------------------------------------------------//
} // namespace celeritas
