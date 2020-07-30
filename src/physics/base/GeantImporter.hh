//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file GeantImporter.hh
//---------------------------------------------------------------------------//
/*!
 * \brief Loads particleDef and physics table data from ROOT files
 *
 * GeantImporter loads particle data and physics tables previously saved into
 * root files by the external code app/geant-exporter.
 *
 * Usage:
 * \code
 *  GeantImporter importer;
 *  importer.loadParticleDefRootFile("/path/to/particleDefFile.root");
 *  importer.loadPhysicsTableRootFile("/path/to/physicsTables.root");
 * \endcode
 *
 * These methods will load into memory both particles and physics tables as
 * vector<GeantParticleDef> and map<tableName, GeantPhysicsTable>. The data
 * can be retrieved via copy functions:
 * \code
 *  bool copyParticleDef(int pdg, GeantParticleDef &g4Particle);
 *  bool copyPhysicsTable(std::string physTableName,
 *                        GeantPhysicsTable &physTable);
 * \endcode
 *
 * Use \c printPhysicsTableNames() to view the list of physics tables.
 */
//-------------------------------------------------------------------------//

#pragma once

// C++
#include <memory>
#include <string>
#include <vector>
#include <map>

// Project
#include "GeantParticleDef.hh"
#include "GeantPhysicsTable.hh"
#include "ParticleDef.hh"
#include "ParticleMd.hh"

#include "base/Types.hh"
#include "base/Macros.hh"


// ROOT forward declaration
class TFile;

namespace celeritas
{
//-------------------------------------------------------------------------//

class GeantImporter
{
  public:
    GeantImporter();
    ~GeantImporter();

    // Loads the ROOT data into memeory
    void loadParticleDefRootFile(std::string const filename);
    void loadPhysicsTableRootFile(std::string const filename);

    // Copy the data from memory into an object
    bool copyParticleDef(ssize_type pdg, GeantParticleDef& g4Particle);
    bool copyPhysicsTable(std::string        physTableName,
                          GeantPhysicsTable& physTable);

    // Print capabilities
    void printObjectsList();
    void printParticleInfo(ssize_type pdg);
    void printPhysicsTable(std::string physTableName);
    void printPhysicsTableNames();

    // Construct a ParticleDef 
    ParticleDef particleDef(ssize_type pdg);
    ParticleDef particleDef(GeantParticleDef& g4particle);
    std::vector<ParticleDef> particleDefVector();

    // Construct a ParticleMd
    ParticleMd particleMd(ssize_type pdg);
    ParticleMd particleMd(GeantParticleDef& g4particle);

    // Construct a ParticleParams

    // Construct a Particle

  private:
    void buildObjectsList(TFile* rootFile);
    void loadPhysicsTablesIntoMemory();
    void loadParticleDefsIntoMemory();

  private:
    std::vector<std::string>                 objectsList_;
    std::vector<GeantParticleDef>            particleVector_;
    std::map<std::string, GeantPhysicsTable> physTableMap_;

    std::unique_ptr<TFile> rootFile_particleDef_;
    std::unique_ptr<TFile> rootFile_physicsTable_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

