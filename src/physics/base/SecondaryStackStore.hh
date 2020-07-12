//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryStackStore.hh
//---------------------------------------------------------------------------//
#ifndef physics_base_SecondaryStackStore_hh
#define physics_base_SecondaryStackStore_hh

#include "base/StackAllocatorStore.hh"
#include "SecondaryStackView.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Manage device data for an allocation of secondaries.
 */
class SecondaryStackStore
{
  public:
    //@{
    //! Type aliases
    using size_type = StackAllocatorStore::size_type;
    //@}

  public:
    // Construct with no storage
    SecondaryStackStore() = default;

    // Construct with the number of secondaries to allocate on device
    explicit SecondaryStackStore(size_type capacity);

    // >>> HOST ACCESSORS

    //! Size of the allocation
    size_type capacity() const { return capacity_; }

    // Clear allocated data
    void clear();

    // Swap with another stack allocator
    void swap(SecondaryStackStore& other);

    // >>> DEVICE ACCESSORS

    // Get a view to the managed data
    SecondaryStackView device_view();

  private:
    size_type           capacity_ = 0;
    StackAllocatorStore allocator_store_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#endif // physics_base_SecondaryStackStore_hh
