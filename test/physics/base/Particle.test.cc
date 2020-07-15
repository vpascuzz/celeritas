//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Particle.test.cc
//---------------------------------------------------------------------------//
#include "physics/base/Particle.hh"

#include "celeritas_config.h"
#include "gtest/Main.hh"
#include "gtest/Test.hh"
#include "gmock/gmock.h"
#include "base/Array.hh"
#include "physics/base/ParticleParams.hh"
#include "physics/base/ParticleStateStore.hh"
#include "physics/base/ParticleStateView.hh"
#include "physics/base/Units.hh"
#include "Particle.test.hh"

using celeritas::Particle;
using celeritas::ParticleDef;
using celeritas::ParticleDefId;
using celeritas::ParticleParams;
using celeritas::ParticleParamsView;
using celeritas::ParticleStateStore;
using celeritas::ParticleStateView;

using celeritas::real_type;
using celeritas::ThreadId;
using testing::ElementsAreArray;

namespace units = celeritas::units;
using namespace celeritas_test;

//---------------------------------------------------------------------------//
// TEST HARNESS BASE
//---------------------------------------------------------------------------//

class ParticleTest : public celeritas::Test
{
  protected:
    void SetUp() override
    {
        namespace pdg = celeritas::pdg;
        using celeritas::ParticleDef;

        // Create particle defs, initialize on device
        ParticleParams::VecAnnotatedDefs defs;
        defs.push_back(
            {{"electron", pdg::electron()},
             {0.5109989461, -1, ParticleDef::stable_decay_constant()}});
        defs.push_back({{"gamma", pdg::gamma()},
                        {0, 0, ParticleDef::stable_decay_constant()}});
        defs.push_back(
            {{"neutron", pdg::neutron()}, {939.565413, 0, 1.0 / 879.4}});

        particle_params = std::make_shared<ParticleParams>(std::move(defs));
    }

    std::shared_ptr<ParticleParams> particle_params;
};

TEST_F(ParticleTest, params_accessors)
{
    using celeritas::PDGNumber;
    const ParticleParams& defs = *this->particle_params;

    EXPECT_EQ(ParticleDefId(0), defs.find(PDGNumber(11)));
    EXPECT_EQ(ParticleDefId(1), defs.find(PDGNumber(22)));
    EXPECT_EQ(ParticleDefId(2), defs.find(PDGNumber(2112)));

    EXPECT_EQ(ParticleDefId(0), defs.find("electron"));
    EXPECT_EQ(ParticleDefId(1), defs.find("gamma"));
    EXPECT_EQ(ParticleDefId(2), defs.find("neutron"));
}

//---------------------------------------------------------------------------//
// HOST TESTS
//---------------------------------------------------------------------------//

class ParticleTestHost : public ParticleTest
{
    using Base = ParticleTest;

  protected:
    void SetUp() override
    {
        Base::SetUp();
        CHECK(particle_params);

        // Construct views
        params_view     = particle_params->host_view();
        state_view.vars = celeritas::make_span(state_storage);
    }

    celeritas::array<celeritas::ParticleStateVars, 1> state_storage;

    ParticleParamsView params_view;
    ParticleStateView  state_view;
};

TEST_F(ParticleTestHost, electron)
{
    Particle particle(params_view, state_view, ThreadId(0));
    particle = {ParticleDefId{0}, 500 * units::kilo_electron_volt};

    EXPECT_DOUBLE_EQ(0.5, particle.kinetic_energy());
    EXPECT_DOUBLE_EQ(0.5109989461, particle.mass());
    EXPECT_DOUBLE_EQ(-1., particle.charge());
    EXPECT_DOUBLE_EQ(0.0, particle.decay_constant());
    EXPECT_SOFT_EQ(0.86286196322132447, particle.speed()); // fraction of c
    EXPECT_SOFT_EQ(1.9784755992474248, particle.lorentz_factor());
    EXPECT_SOFT_EQ(0.87235253544653601, particle.momentum());
}

TEST_F(ParticleTestHost, gamma)
{
    Particle particle(params_view, state_view, ThreadId(0));
    particle = {ParticleDefId{1}, 10 * units::mega_electron_volt};

    EXPECT_DOUBLE_EQ(0, particle.mass());
    EXPECT_DOUBLE_EQ(10, particle.kinetic_energy());
    EXPECT_DOUBLE_EQ(1.0, particle.speed());
    EXPECT_DOUBLE_EQ(10, particle.momentum()); // [1 / c]
}

TEST_F(ParticleTestHost, neutron)
{
    Particle particle(params_view, state_view, ThreadId(0));
    particle = {ParticleDefId{2}, 20 * units::mega_electron_volt};

    EXPECT_DOUBLE_EQ(20, particle.kinetic_energy());
    EXPECT_DOUBLE_EQ(1.0 / 879.4, particle.decay_constant());
}

#if CELERITAS_USE_CUDA
//---------------------------------------------------------------------------//
// DEVICE TESTS
//---------------------------------------------------------------------------//

class ParticleTestDevice : public ParticleTest
{
    using Base = ParticleTest;
};

TEST_F(ParticleTestDevice, calc_props)
{
    PTestInput input;
    input.init = {{ParticleDefId{0}, 500 * units::kilo_electron_volt},
                  {ParticleDefId{1}, 10 * units::mega_electron_volt},
                  {ParticleDefId{2}, 20 * units::mega_electron_volt}};

    ParticleStateStore pstates(input.init.size());
    input.params = particle_params->device_view();
    input.states = pstates.device_view();

    // Run GPU test
    auto result = p_test(input);

    // Check results
    static const double expected_props[] = {
        0.5, 0.510999, -1, 0,          0.862862, 1.97848, 0.872353, 0.760999,
        10,  0,        0,  0,          1,        -1,      10,       100,
        20,  939.565,  0,  0.00113714, 0.203104, 1.02129, 194.891,  37982.6};
    EXPECT_THAT(result.props, ElementsAreArray(expected_props));
}
#endif
