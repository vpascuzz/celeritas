//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file ThreeVector.hh
//---------------------------------------------------------------------------//
#ifndef physics_base_ThreeVector_hh
#define physics_base_ThreeVector_hh

#include "base/Assert.hh"

namespace celeritas {
//---------------------------------------------------------------------------//
/*!
 * Brief class description.
 */

class ThreeVector
{
  protected:
      double dirX_;
      double dirY_;
      double dirZ_;
    
  public:
    // Construct with defaults
    inline ThreeVector();
    
    // Operator ()
    inline ThreeVector operator()(double dirX, double dirY, double dirZ);
    
    // Getters
    inline double GetDirX();
    inline double GetDirY();
    inline double GetDirZ();
        
    // Setters
    inline void SetDirection(ThreeVector &threeVector);
    inline void SetDirection(double dirX, double dirY, double dirZ);

    inline void SetDirX(double dirX);
    inline void SetDirY(double dirY);
    inline void SetDirZ(double dirZ);
};

//---------------------------------------------------------------------------//
}  // namespace celeritas

#include "ThreeVector.i.hh"

#endif // physics_base_ThreeVector_hh
