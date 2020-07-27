//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryAllocatorStore.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/StackAllocatorStore.hh"
#include "SecondaryAllocatorPointers.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Manage device data for an allocation of secondaries.
 */
class SecondaryAllocatorStore
{
  public:
    //@{
    //! Type aliases
    using size_type = StackAllocatorStore::size_type;
    //@}

  public:
    // Construct with no storage
    SecondaryAllocatorStore() = default;

    // Construct with the number of secondaries to allocate on device
    explicit SecondaryAllocatorStore(size_type capacity);

    // >>> HOST ACCESSORS

    //! Size of the allocation
    size_type capacity() const { return capacity_; }

    // Clear allocated data
    void clear();

    // Swap with another stack allocator
    void swap(SecondaryAllocatorStore& other);

    // >>> DEVICE ACCESSORS

    // Get a view to the managed data
    SecondaryAllocatorPointers device_pointers();

  private:
    size_type           capacity_ = 0;
    StackAllocatorStore allocator_store_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas
