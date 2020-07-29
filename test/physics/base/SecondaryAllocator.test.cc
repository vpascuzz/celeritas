//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryAllocator.test.cc
//---------------------------------------------------------------------------//
#include "physics/base/SecondaryAllocatorView.hh"
#include "physics/base/SecondaryAllocatorPointers.hh"
#include "physics/base/SecondaryAllocatorStore.hh"

#include "gtest/Main.hh"
#include "gtest/Test.hh"
#include "SecondaryAllocator.test.hh"

using namespace celeritas;

//---------------------------------------------------------------------------//
// HOST TESTS
//---------------------------------------------------------------------------//

class SecondaryAllocatorHostTest : public celeritas::Test
{
  protected:
    using size_type = StackAllocatorPointers::size_type;

    void SetUp() override { this->resize(0); }

    void resize(size_type capacity)
    {
        capacity *= sizeof(Secondary);
        storage_.assign(capacity, static_cast<celeritas::byte>(0x0f));
        requested_bytes_            = 0;
        pointers_.allocator.storage = celeritas::make_span(storage_);
        pointers_.allocator.reqsize = &requested_bytes_;
    }

    std::vector<celeritas::byte>      storage_;
    StackAllocatorPointers::size_type requested_bytes_;
    SecondaryAllocatorPointers        pointers_;
};

TEST_F(SecondaryAllocatorHostTest, allocation)
{
    SecondaryAllocatorView alloc(pointers_);

    Secondary* ptr = alloc(1);
    EXPECT_EQ(nullptr, ptr);
    EXPECT_EQ(sizeof(Secondary), requested_bytes_);

    // Reserve space for 16 secondaries
    this->resize(16);
    ptr = alloc(8);
    EXPECT_EQ(8 * sizeof(Secondary), requested_bytes_);
    ASSERT_NE(nullptr, ptr);
    for (const Secondary& p : celeritas::span<Secondary>(ptr, 8))
    {
        // Check that secondary was initialized properly
        EXPECT_EQ(TrackId{}, p.parent_track_id);
        EXPECT_EQ(ParticleDefId{}, p.def_id);
    }

    // Ask for one more than we have room
    ptr = alloc(9);
    EXPECT_EQ(nullptr, ptr);
}
