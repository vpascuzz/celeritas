//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryAllocator.test.cc
//---------------------------------------------------------------------------//
#include "physics/base/SecondaryAllocatorView.hh"
#include "physics/base/SecondaryAllocatorStore.hh"

#include <cstdint>
#include "gtest/Main.hh"
#include "gtest/Test.hh"
#include "SecondaryAllocator.test.hh"

// using namespace celeritas;
using namespace celeritas_test;

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

    // Get span to the data
    auto all_secondaries = alloc.secondaries();
    EXPECT_EQ(8, all_secondaries.size());
    EXPECT_EQ(static_cast<void*>(storage_.data()),
              static_cast<void*>(all_secondaries.data()));
}

//---------------------------------------------------------------------------//
// DEVICE TESTS
//---------------------------------------------------------------------------//
#if CELERITAS_USE_CUDA

class SecondaryAllocatorDeviceTest : public celeritas::Test
{
  protected:
    void SetUp() override
    {
        // Allocate 1024 secondaries
        storage = SecondaryAllocatorStore(1024);
    }

    // Get the actual number of allocated secondaries
    int actual_allocations(const SATestInput& in, const SATestOutput& out) const
    {
        using std::uintptr_t;

        // Use GPU pointer arithmetic to find the start address of the final
        // secondary allocation; divide by sizeof secondary, add the final
        // allocation
        void* storage_begin_ptr
            = static_cast<void*>(in.sa_view.allocator.storage.data());
        auto prev_alloc = (static_cast<uintptr_t>(out.last_secondary_address)
                           - reinterpret_cast<uintptr_t>(storage_begin_ptr))
                          / sizeof(Secondary);
        return prev_alloc + in.alloc_size;
    }

    SecondaryAllocatorStore storage;
};

TEST_F(SecondaryAllocatorDeviceTest, run)
{
    EXPECT_EQ(1024, storage.capacity());
    int accum_expected_alloc = 0;

    // Allocate a subset of the stack
    SATestInput input;
    input.sa_view     = storage.device_pointers();
    input.num_threads = 64;
    input.num_iters   = 1;
    input.alloc_size  = 2;
    auto result       = sa_test(input);
    EXPECT_EQ(0, result.num_errors);
    EXPECT_EQ(input.num_threads * input.num_iters * input.alloc_size,
              result.num_allocations);
    accum_expected_alloc += result.num_allocations;
    EXPECT_EQ(accum_expected_alloc, actual_allocations(input, result));

    // Run again, two iterations per thread
    input.num_iters  = 2;
    input.alloc_size = 4;
    result           = sa_test(input);
    EXPECT_EQ(0, result.num_errors);
    EXPECT_EQ(input.num_threads * input.num_iters * input.alloc_size,
              result.num_allocations);
    accum_expected_alloc += result.num_allocations;
    EXPECT_EQ(accum_expected_alloc, actual_allocations(input, result));

    // Run again, too many iterations (so storage gets filled up)
    input.num_iters   = 128;
    input.num_threads = 1024;
    input.alloc_size  = 1;
    result            = sa_test(input);
    EXPECT_EQ(0, result.num_errors);
    EXPECT_EQ(1024 - accum_expected_alloc, result.num_allocations);
    EXPECT_EQ(1024, actual_allocations(input, result));

    // Reset secondary storage
    storage.clear();
}

#endif