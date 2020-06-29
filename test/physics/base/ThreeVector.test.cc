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

    ASSERT_EQ(0, A.GetX());
    ASSERT_EQ(0, A.GetY());
    ASSERT_EQ(0, A.GetZ());
    ASSERT_EQ(0, A.GetMagnitude());
    ASSERT_EQ(0, A.GetTheta());
    ASSERT_EQ(0, A.GetPhi());
}

TEST(ThreeVectorTest, magnitudeAndAngleCalcs)
{
    ThreeVector A(30, 20, 10);

    double mag = std::sqrt(30*30 + 20*20 + 10*10);
    double theta = std::asin(10 / mag);
    double phi = std::acos(30 / (mag*std::cos(theta)));
    
    ASSERT_EQ(30, A.GetX());
    ASSERT_EQ(20, A.GetY());
    ASSERT_EQ(10, A.GetZ());
    ASSERT_EQ(mag, A.GetMagnitude());
    ASSERT_EQ(theta, A.GetTheta());
    ASSERT_EQ(phi, A.GetPhi());
}

TEST(ThreeVectorTest, operators)
{
    ThreeVector A, B, C;
    
    A(10, 0, 0);
    B(0, 10, 0);
    C = A + B;
    
    ASSERT_EQ(10, C.GetX());
    ASSERT_EQ(10, C.GetY());
    ASSERT_EQ( 0, C.GetZ());

    C = A - B;
    ASSERT_EQ( 10, C.GetX());
    ASSERT_EQ(-10, C.GetY());
    ASSERT_EQ(  0, C.GetZ());
    
    C = A * 2.;
    ASSERT_EQ(20, C.GetX());
    ASSERT_EQ( 0, C.GetY());
    ASSERT_EQ( 0, C.GetZ());
}
