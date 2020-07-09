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
 * Class for dealing with 3D vectors
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
    // Constructors
    inline ThreeVector();
    inline ThreeVector(double x, double y, double z);

    // Operators
    inline ThreeVector operator()(double x, double y, double z);
    inline ThreeVector operator+(ThreeVector A);
    inline ThreeVector operator-(ThreeVector A);
    inline ThreeVector operator*(double A);
    inline ThreeVector operator*(int A);
    inline ThreeVector operator=(ThreeVector A);
        
    // Should we add dot and cross products?

    // Getters
    inline double x();
    inline double y();
    inline double z();

    inline double magnitude();
    
    inline double dirX();
    inline double dirY();
    inline double dirZ();
    
    inline double theta();
    inline double phi();
};

//---------------------------------------------------------------------------//
}  // namespace celeritas

#include "ThreeVector.i.hh"

#endif // physics_base_ThreeVector_hh
