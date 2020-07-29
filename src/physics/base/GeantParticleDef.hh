//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file GeantParticleDef.hh
//---------------------------------------------------------------------------//
#pragma once

#include <string>

#include "base/Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * /brief Stores particle information for the GeantImporter class
 *
 * This class provides the same structure seen in the particleDef.root file
 * created by the app/geant-exporter external code and it is used to load
 * said ROOT data into memory by the GeantImporter class.
 */

class GeantParticleDef
{
  protected:
    std::string name_;
    ssize_type  pdg_;
    real_type   mass_;
    real_type   charge_;
    real_type   spin_;
    real_type   lifetime_;
    bool        isStable_;

  public:
    GeantParticleDef();
    GeantParticleDef(std::string name,
                     ssize_type  pdg,
                     real_type   mass,
                     real_type   charge,
                     real_type   spin,
                     real_type   lifetime,
                     bool        isStable);
    
    ~GeantParticleDef();
    
    GeantParticleDef operator()(std::string name,
                                ssize_type  pdg,
                                real_type   mass,
                                real_type   charge,
                                real_type   spin,
                                real_type   lifetime,
                                bool        isStable);

    std::string name();
    ssize_type  pdg();
    real_type   mass();
    real_type   charge();
    real_type   spin();
    real_type   lifetime();
    bool        isStable();
    
    void print();
};

//---------------------------------------------------------------------------//
} // namespace celeritas
