//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryAllocatorStore.cc
//---------------------------------------------------------------------------//
#include "SecondaryAllocatorStore.hh"

#include "base/Assert.hh"
#include "Secondary.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with the number of bytes to allocate on device.
 */
SecondaryAllocatorStore::SecondaryAllocatorStore(size_type capacity)
    : capacity_(capacity), allocator_store_(capacity * sizeof(Secondary))
{
}

//---------------------------------------------------------------------------//
/*!
 * Get a view to the managed data.
 */
SecondaryAllocatorPointers SecondaryAllocatorStore::device_pointers()
{
    SecondaryAllocatorPointers view;
    view.allocator = allocator_store_.device_pointers();
    return view;
}

//---------------------------------------------------------------------------//
/*!
 * Clear allocated data.
 */
void SecondaryAllocatorStore::clear()
{
    allocator_store_.clear();
}

//---------------------------------------------------------------------------//
/*!
 * Swap with another stack allocator.
 */
void SecondaryAllocatorStore::swap(SecondaryAllocatorStore& other)
{
    using std::swap;
    swap(capacity_, other.capacity_);
    swap(allocator_store_, other.allocator_store_);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
