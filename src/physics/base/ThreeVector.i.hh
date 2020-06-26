//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file ThreeVector.i.hh
//---------------------------------------------------------------------------//

#include "ThreeVector.hh"

namespace celeritas {
//---------------------------------------------------------------------------//
/*!
 * Construct with defaults.
 */
ThreeVector::ThreeVector()
: dirX_(0), dirY_(0), dirZ_(0)
{}

//------------------------------- Operator () -------------------------------//
ThreeVector ThreeVector::operator()(double dirX, double dirY, double dirZ)
{
    REQUIRE(dirX >= -1.0 && dirX <= 1.0);
    REQUIRE(dirY >= -1.0 && dirY <= 1.0);
    REQUIRE(dirZ >= -1.0 && dirZ <= 1.0);
            
    this->dirX_ = dirX;
    this->dirY_ = dirY;
    this->dirZ_ = dirZ;
    
    return *this;
}

//--------------------------------- Getters ---------------------------------//
double ThreeVector::GetDirX()
{
    return (this->dirX_);
}

double ThreeVector::GetDirY()
{
    return (this->dirY_);
}

double ThreeVector::GetDirZ()
{
    return (this->dirZ_);
}

//--------------------------------- Setters ---------------------------------//
void ThreeVector::SetDirection(ThreeVector &threeVector)
{
    this->dirX_ = threeVector.GetDirX();
    this->dirY_ = threeVector.GetDirY();
    this->dirZ_ = threeVector.GetDirZ();
}

void ThreeVector::SetDirection(double dirX, double dirY, double dirZ)
{
    REQUIRE(dirX >= -1.0 && dirX <= 1.0);
    REQUIRE(dirY >= -1.0 && dirY <= 1.0);
    REQUIRE(dirZ >= -1.0 && dirZ <= 1.0);
    
    this->dirX_ = dirX;
    this->dirY_ = dirY;
    this->dirZ_ = dirZ;
}

void ThreeVector::SetDirX(double dirX)
{
    REQUIRE(dirX >= -1.0 && dirX <= 1.0);
    this->dirX_ = dirX;
}

void ThreeVector::SetDirY(double dirY)
{
    REQUIRE(dirY >= -1.0 && dirY <= 1.0);
    this->dirY_ = dirY;
}

void ThreeVector::SetDirZ(double dirZ)
{
    REQUIRE(dirZ >= -1.0 && dirZ <= 1.0);
    this->dirZ_ = dirZ;
}


//---------------------------------------------------------------------------//
}  // namespace celeritas
