//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file HostDebugSecondaryStorage.hh
//---------------------------------------------------------------------------//
#pragma once

#include <vector>
#include "physics/base/SecondaryAllocatorPointers.hh"
#include "base/Span.hh"

namespace celeritas_test
{
//---------------------------------------------------------------------------//
/*!
 * Debug helper class for storing secondary particles on the host.
 */
class HostDebugSecondaryStorage
{
    //@{
    //! Type aliases
    using Secondary                  = celeritas::Secondary;
    using SecondaryAllocatorPointers = celeritas::SecondaryAllocatorPointers;
    using size_type                  = SecondaryAllocatorPointers::size_type;
    using constSpanSecondary         = celeritas::span<const Secondary>;
    //@}

  public:
    HostDebugSecondaryStorage() { this->resize(0); }

    void resize(size_type capacity)
    {
        Secondary unallocated_secondary;
        unallocated_secondary.parent_track_id = celeritas::TrackId{0xdeadbeef};
        unallocated_secondary.def_id    = celeritas::ParticleDefId{0xdeadbeef};
        unallocated_secondary.direction = {-10, -20, -30};
        unallocated_secondary.energy    = -1;
        storage_.assign(capacity, unallocated_secondary);
        size_             = 0;
        pointers_.storage = celeritas::make_span(storage_);
        pointers_.size    = &size_;
    }

    //! Access active (allocated) secondaries
    constSpanSecondary secondaries() const { return {storage_.data(), size_}; }

    //! Access host pointers
    const SecondaryAllocatorPointers& host_pointers() const
    {
        return pointers_;
    }

  private:
    std::vector<Secondary>                storage_;
    SecondaryAllocatorPointers::size_type size_;
    SecondaryAllocatorPointers            pointers_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas_test

//---------------------------------------------------------------------------//
