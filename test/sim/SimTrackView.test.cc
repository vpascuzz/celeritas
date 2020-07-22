//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SimTrackView.test.cc
//---------------------------------------------------------------------------//
#include "../test/sim/SimTrackView.hh"

#include "gtest/Main.hh"
#include "gtest/Test.hh"
#include "gmock/gmock.h"
#include "SimTrackView.test.hh"

using celeritas::SimTrackView;
using namespace celeritas_test;

//---------------------------------------------------------------------------//
// TEST HARNESS
//---------------------------------------------------------------------------//

class SimTrackViewTest : public celeritas::Test
{
  protected:
    void SetUp() override {}
};

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST_F(SimTrackViewTest, all)
{
    // STVTestInput input;
    // input.num_threads = 0;
    // auto result = stv_test(input);
    // using testing::ElementsAreArray;
    // EXPECT_THAT(result.foo, ElementsAreArray(expected_foo));
}
