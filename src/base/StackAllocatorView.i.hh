//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file StackAllocatorView.i.hh
//---------------------------------------------------------------------------//

#include "base/Algorithms.hh"
#include "base/Atomics.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with a reference to the storage pointers
 */
CELER_FUNCTION
StackAllocatorView::StackAllocatorView(const StackAllocatorPointers& view)
    : shared_(view)
{
}

//---------------------------------------------------------------------------//
/*!
 * Allocate like malloc.
 *
 * Be aware that this increments the requested size *no matter what*: if the
 * buffer is full, reqsize >= capacity.
 */
CELER_FUNCTION auto StackAllocatorView::operator()(size_type size)
    -> result_type
{
    size_type start = atomic_add(shared_.reqsize, size);
    if (start + size > shared_.storage.size())
        return nullptr;
    return shared_.storage.data() + start;
}

//---------------------------------------------------------------------------//
/*!
 * Get the current allocated size in bytes.
 */
CELER_FUNCTION auto StackAllocatorView::size() const -> size_type
{
    return celeritas::min<size_type>(shared_.storage.size(), *shared_.reqsize);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
