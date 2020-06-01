//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file DummyProcess.test.cc
//---------------------------------------------------------------------------//
#include "physics/DummyProcess.hh"

#include "gtest/Main.hh"
#include "gtest/Test.hh"

using celeritas::DummyProcess;

//---------------------------------------------------------------------------//
// TEST HARNESS
//---------------------------------------------------------------------------//

class DummyProcessTest : public celeritas::Test
{
  protected:
    void SetUp() override {}
};

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST_F(DummyProcessTest, all)
{
    double e_gamma = 0;
    double z = 1;
    double returned_xs = 0;
    
    DummyProcess process(e_gamma);
    
    ASSERT_EQ(returned_xs, process.ComputeAtomicCrossSection(z));
}
