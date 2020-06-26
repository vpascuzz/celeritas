//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file ThreeVector.test.cc
//---------------------------------------------------------------------------//
#include "physics/base/ThreeVector.hh"

#include "gtest/Main.hh"
#include "gtest/Test.hh"

using celeritas::ThreeVector;

//---------------------------------------------------------------------------//
// TEST HARNESS
//---------------------------------------------------------------------------//

class ThreeVectorTest : public celeritas::Test
{
  protected:
    void SetUp() override {}
};

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST_F(ThreeVectorTest, all)
{
    ThreeVector vector;
    
    ASSERT_EQ(0, vector.GetDirX());
    ASSERT_EQ(0, vector.GetDirY());
    ASSERT_EQ(0, vector.GetDirZ());

    vector(0.5, 0.3, 0.1);
    
    ASSERT_EQ(0.5, vector.GetDirX());
    ASSERT_EQ(0.3, vector.GetDirY());
    ASSERT_EQ(0.1, vector.GetDirZ());    
}
