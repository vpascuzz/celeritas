//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file DummyProcess.test.cc
//---------------------------------------------------------------------------//
#include "physics/electromagnetic/KleinNishinaXSCalculator.hh"

#include "gtest/Main.hh"
#include "gtest/Test.hh"

using celeritas::KleinNishinaXSCalculator;

//---------------------------------------------------------------------------//
// TEST HARNESS
//---------------------------------------------------------------------------//

class KleinNishinaXSCalculatorTest : public celeritas::Test
{
  protected:
    void SetUp() override {}
};

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST_F(KleinNishinaXSCalculatorTest, all)
{
    double e_gamma = 0;
    double z = 1;
    double returned_xs = 0;
    
    KleinNishinaXSCalculator processTest(e_gamma);
    
    ASSERT_EQ(returned_xs, processTest(z));
}
