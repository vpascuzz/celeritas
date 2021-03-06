//----------------------------------*-C++-*----------------------------------//
// Copyright 2021 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file LDemoParams.cc
//---------------------------------------------------------------------------//
#include "LDemoParams.hh"

#include "comm/Logger.hh"
#include "io/RootImporter.hh"
#include "physics/base/ImportedProcessAdapter.hh"
#include "physics/em/ComptonProcess.hh"
#include "physics/em/EIonizationProcess.hh"
#include "physics/em/EPlusAnnihilationProcess.hh"
#include "physics/em/GammaConversionProcess.hh"
#include "physics/em/PhotoelectricProcess.hh"
#include "LDemoIO.hh"

using namespace celeritas;

namespace demo_loop
{
//---------------------------------------------------------------------------//
LDemoParams load_params(const LDemoArgs& args)
{
    CELER_LOG(status) << "Loading input files";
    LDemoParams result;

    // Load ROOT file
    auto loaded = RootImporter(args.physics_filename.c_str())();

    // Load geometry
    {
        result.geometry
            = std::make_shared<GeoParams>(args.geometry_filename.c_str());
    }

    // Load materials
    {
        result.materials = std::move(loaded.material_params);
    }

    // Create geometry/material coupling
    {
        GeoMaterialParams::Input input;
        input.geometry  = result.geometry;
        input.materials = result.materials;

        input.volume_to_mat
            = std::vector<MaterialId>(input.geometry->num_volumes());
        for (const auto& kv : loaded.geometry->volid_to_matid_map())
        {
            CELER_ASSERT(kv.first < input.volume_to_mat.size());
            CELER_ASSERT(kv.second < result.materials->num_materials());
            input.volume_to_mat[kv.first] = MaterialId{kv.second};
        }
        result.geo_mat = std::make_shared<GeoMaterialParams>(std::move(input));
    }

    // Construct particle params
    {
        result.particles = std::move(loaded.particle_params);
    }

    // Construct cutoffs
    {
        CutoffParams::Input input;
        result.cutoffs = std::make_shared<CutoffParams>(std::move(input));
    }

    // Load physics: create individual processes with make_shared
    {
        PhysicsParams::Input input;
        input.particles = result.particles;
        input.materials = result.materials;

        auto process_data
            = std::make_shared<ImportedProcesses>(std::move(loaded.processes));
        input.processes.push_back(
            std::make_shared<ComptonProcess>(result.particles, process_data));
        CELER_NOT_IMPLEMENTED("TODO: add remaining processes");

        result.physics = std::make_shared<PhysicsParams>(std::move(input));
    }

    CELER_ENSURE(result);
    return result;
}

//---------------------------------------------------------------------------//
} // namespace demo_loop
