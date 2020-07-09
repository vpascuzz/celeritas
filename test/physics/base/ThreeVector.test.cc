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

TEST(ThreeVectorTest, getters)
{
    ThreeVector A;

    ASSERT_EQ(0, A.x());
    ASSERT_EQ(0, A.y());
    ASSERT_EQ(0, A.z());
    ASSERT_EQ(0, A.magnitude());
    ASSERT_EQ(0, A.theta());
    ASSERT_EQ(0, A.phi());
}

TEST(ThreeVectorTest, magnitudeAndAngleCalcs)
{
    ThreeVector A(30, 20, 10);

    ASSERT_EQ(30, A.x());
    ASSERT_EQ(20, A.y());
    ASSERT_EQ(10, A.z());
    EXPECT_SOFT_EQ(37.416573867739416, A.magnitude());
    EXPECT_SOFT_EQ(0.2705497629785729, A.theta());
    EXPECT_SOFT_EQ(0.5880026035475675, A.phi());
}

TEST(ThreeVectorTest, operators)
{
    ThreeVector A, B, C;
    
    A(10, 0, 0);
    B(0, 10, 0);
    
    C = A;
    ASSERT_EQ(10, C.x());
    ASSERT_EQ( 0, C.y());
    ASSERT_EQ( 0, C.z());
  
    C = A + B;
    ASSERT_EQ(10, C.x());
    ASSERT_EQ(10, C.y());
    ASSERT_EQ( 0, C.z());

    C = A - B;
    ASSERT_EQ( 10, C.x());
    ASSERT_EQ(-10, C.y());
    ASSERT_EQ(  0, C.z());
   
    C = A * 2;
    ASSERT_EQ(20, C.x());
    ASSERT_EQ( 0, C.y());
    ASSERT_EQ( 0, C.z());
    
    C = A * 2.5;
    ASSERT_EQ(25, C.x());
    ASSERT_EQ( 0, C.y());
    ASSERT_EQ( 0, C.z());
}
