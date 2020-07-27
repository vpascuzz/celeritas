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

using celeritas::SecondaryAllocator;
using namespace celeritas_test;

//---------------------------------------------------------------------------//
// TEST HARNESS
//---------------------------------------------------------------------------//

class SecondaryAllocatorTest : public celeritas::Test
{
  protected:
    void SetUp() override {}
};

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST_F(SecondaryAllocatorTest, all)
{
    // SATestInput input;
    // input.num_threads = 0;
    // auto result = sa_test(input);
    // using testing::ElementsAreArray;
    // EXPECT_THAT(result.foo, ElementsAreArray(expected_foo));
}
