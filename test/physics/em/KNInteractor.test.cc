//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file KNInteractor.test.cc
//---------------------------------------------------------------------------//
#include "physics/em/KNInteractor.hh"

#include "gtest/Main.hh"
#include "../InteractorHostTestBase.hh"

using celeritas::KNInteractor;

//---------------------------------------------------------------------------//
// TEST HARNESS
//---------------------------------------------------------------------------//

class KNInteractorTest : public celeritas_test::InteractorHostTestBase
{
    using Base = celeritas_test::InteractorHostTestBase;

  protected:
    void SetUp() override
    {
        namespace pdg = celeritas::pdg;
        using celeritas::ParticleDef;
        Base::set_particle_params(
            {{{"electron", pdg::electron()},
              {0.5109989461, -1, ParticleDef::stable_decay_constant()}},
             {{"gamma", pdg::gamma()},
              {0, 0, ParticleDef::stable_decay_constant()}}});
    }
};

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST_F(KNInteractorTest, all) {}
