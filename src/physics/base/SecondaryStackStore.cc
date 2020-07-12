//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryStackStore.cc
//---------------------------------------------------------------------------//
#include "SecondaryStackStore.hh"

#include "base/Assert.hh"
#include "Secondary.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with the number of bytes to allocate on device.
 */
SecondaryStackStore::SecondaryStackStore(size_type capacity)
    : capacity_(capacity), allocator_store_(capacity * sizeof(Secondary))
{
}

//---------------------------------------------------------------------------//
/*!
 * Get a view to the managed data.
 */
SecondaryStackView SecondaryStackStore::device_view()
{
    SecondaryStackView view;
    view.allocator_view = allocator_store_.device_view();
    return view;
}

//---------------------------------------------------------------------------//
/*!
 * Clear allocated data.
 */
void SecondaryStackStore::clear()
{
    allocator_store_.clear();
}

//---------------------------------------------------------------------------//
/*!
 * Swap with another stack allocator.
 */
void SecondaryStackStore::swap(SecondaryStackStore& other)
{
    using std::swap;
    swap(capacity_, other.capacity_);
    swap(allocator_store_, other.allocator_store_);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
