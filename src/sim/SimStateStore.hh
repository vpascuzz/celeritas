//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SimStateStore.hh
//---------------------------------------------------------------------------//
#ifndef sim_SimState_hh
#define sim_SimState_hh

#include "base/DeviceVector.hh"
#include "base/Types.hh"
#include "SimStateView.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Manage on-device particle physics states.
 */
class SimStateStore
{
  public:
    // Construct from number of track states
    explicit SimStateStore(size_type size);

    // >>> ACCESSORS

    // Number of states
    size_type size() const;

    // View on-device states
    SimStateView device_view();

  private:
    DeviceVector<SimStateVars> vars_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#endif // sim_SimState_hh
