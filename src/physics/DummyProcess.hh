//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file DummyProcess.hh
//---------------------------------------------------------------------------//
#ifndef physics_DummyProcess_hh
#define physics_DummyProcess_hh

namespace celeritas {
//---------------------------------------------------------------------------//
/*!
 * Brief class description.
 *
 * Optional detailed class description, and possibly example usage:
 * \code
    DummyProcess ...;
   \endcode
 */
class DummyProcess
{
  public:
    //@{
    //! Type aliases
    //@}
    double e_gamma;
    double ComputeAtomicCrossSection(double &z);

  public:
    // Construct with defaults
    inline DummyProcess();
    inline DummyProcess(double &e_gamma);
    
    ~DummyProcess();
};

//---------------------------------------------------------------------------//
}  // namespace celeritas

#include "DummyProcess.cc"

#endif // physics_DummyProcess_hh
