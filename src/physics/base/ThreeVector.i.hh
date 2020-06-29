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
: x_(0), y_(0), z_(0), magnitude_(0), theta_(0), phi_(0)
{}

ThreeVector::ThreeVector(double x, double y, double z)
: x_(x), y_(y), z_(z)
{
    this->magnitude_ = std::sqrt(x*x + y*y + z*z);

    this->dirX_ = this->x_ / this->magnitude_;
    this->dirY_ = this->y_ / this->magnitude_;
    this->dirZ_ = this->z_ / this->magnitude_;
    
    this->theta_ = std::asin(this->z_ / this->magnitude_);
    this->phi_ = std::acos(this->x_ / (this->magnitude_*std::cos(this->theta_)));
}



//-------------------------------- Operators --------------------------------//
ThreeVector ThreeVector::operator()(double x, double y, double z)
{
    this->x_ = x;
    this->y_ = y;
    this->z_ = z;
    
    this->magnitude_ = std::sqrt(x*x + y*y + z*z);

    this->dirX_ = this->x_ / this->magnitude_;
    this->dirY_ = this->y_ / this->magnitude_;
    this->dirZ_ = this->z_ / this->magnitude_;
    
    this->theta_ = std::asin(this->z_ / this->magnitude_);
    this->phi_ = std::acos(this->x_ / (this->magnitude_*std::cos(this->theta_)));
    
    return *this;
}

ThreeVector ThreeVector::operator+(ThreeVector A)
{
    ThreeVector C(this->GetX() + A.GetX(),
                  this->GetY() + A.GetY(),
                  this->GetZ() + A.GetZ());
    return C;
}

ThreeVector ThreeVector::operator-(ThreeVector A)
{
    ThreeVector C(this->GetX() - A.GetX(),
                  this->GetY() - A.GetY(),
                  this->GetZ() - A.GetZ());
    return C;
}

ThreeVector ThreeVector::operator*(double A)
{
    ThreeVector C(A * this->GetX(), A * this->GetY(), A * this->GetZ());
    return C;
}


//--------------------------------- Getters ---------------------------------//
double ThreeVector::GetX()
{
    return this->x_;
}

double ThreeVector::GetY()
{
    return this->y_;
}

double ThreeVector::GetZ()
{
    return this->z_;
}

double ThreeVector::GetMagnitude()
{
    return this->magnitude_;
}

double ThreeVector::GetDirX()
{
    return this->dirX_;
}

double ThreeVector::GetDirY()
{
    return this->dirY_;
}

double ThreeVector::GetDirZ()
{
    return this->dirZ_;
}

double ThreeVector::GetTheta()
{
    return this->theta_;
}

double ThreeVector::GetPhi()
{
    return this->phi_;
}

//---------------------------------------------------------------------------//
}  // namespace celeritas
