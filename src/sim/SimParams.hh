//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SimParams.hh
//---------------------------------------------------------------------------//
#ifndef sim_base_SimParams_hh
#define sim_base_SimParams_hh

#include "SimParamsView.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Persistent simulation data.
 *
 * TODO: not sure exactly what goes here: maybe manage the various action
 * classes?
 */
class SimParams
{
  public:
    //@{
    //!
    //@}

  public:
    // Construct with a vector of particle definitions
    SimParams();

    // >>> DEVICE ACCESSORS

    // Get a view to the managed data
    SimParamsView device_view() const;

  private:
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#endif // sim_base_SimParams_hh
