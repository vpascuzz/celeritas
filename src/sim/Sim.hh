//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Sim.hh
//---------------------------------------------------------------------------//
#ifndef sim_Sim_hh
#define sim_Sim_hh

#include "SimParamsView.hh"
#include "SimStateView.hh"
#include "base/Macros.hh"
#include "base/Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Simulation properties.
 *
 * Manage the simulation state.
 */
class Sim
{
  public:
    //@{
    //! Type aliases
    using Initializer_t = SimStateVars;
    //@}

  public:
    // Construct with view to state and persistent data
    inline SimStateVars(const SimParamsView& params,
                        const SimStateView&  state,
                        ThreadId             thread);

    // Initialize the sim state
    inline CELER_FUNCTION Sim& operator=(const Initializer_t& other);

  private:
    const SimParamsView& params_;
    SimStateVars&        state_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "Sim.i.hh"

#endif // sim_Sim_hh
