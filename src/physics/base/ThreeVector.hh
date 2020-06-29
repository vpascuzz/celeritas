//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file ThreeVector.hh
//---------------------------------------------------------------------------//
#ifndef physics_base_ThreeVector_hh
#define physics_base_ThreeVector_hh

#include <cmath>
#include "base/Assert.hh"

namespace celeritas {
//---------------------------------------------------------------------------//
/*!
 * Brief class description.
 */

class ThreeVector
{
  protected:
    double x_;
    double y_;
    double z_;
    double magnitude_;
    double dirX_;
    double dirY_;
    double dirZ_;
    double theta_;
    double phi_;
    
  public:
    // Construct with defaults
    inline ThreeVector();
    inline ThreeVector(double x, double y, double z);

    
    // Operators
    inline ThreeVector operator()(double x, double y, double z);
    inline ThreeVector operator+(ThreeVector A);
    inline ThreeVector operator-(ThreeVector A);
    inline ThreeVector operator*(double A);
    
    // Dot and cross products not included

    // Getters
    inline double GetX();
    inline double GetY();
    inline double GetZ();

    inline double GetMagnitude();
    
    inline double GetDirX();
    inline double GetDirY();
    inline double GetDirZ();
    
    inline double GetTheta();
    inline double GetPhi();
};

//---------------------------------------------------------------------------//
}  // namespace celeritas

#include "ThreeVector.i.hh"

#endif // physics_base_ThreeVector_hh
