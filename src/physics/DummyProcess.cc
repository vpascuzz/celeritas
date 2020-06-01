//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file DummyProcess.cc
//---------------------------------------------------------------------------//
#include <iostream>
#include <cmath>

#include "DummyProcess.hh"
#include "ConstantsAndUnits.hh"

using namespace celeritas;

namespace celeritas {
//---------------------------------------------------------------------------//
DummyProcess::DummyProcess() : e_gamma(0)
{}

DummyProcess::DummyProcess(double &e_gamma) : e_gamma(e_gamma)
{}

DummyProcess::~DummyProcess()
{}

double DummyProcess::ComputeAtomicCrossSection(double &z)
{
    double xsec = 0.0;
    
    constexpr double a = 20.0;
    constexpr double b = 230.0;
    constexpr double c = 440.0;
    
    constexpr double d1 = 2.7965e-1 * units::barn;
    constexpr double d2 = -1.8300e-1 * units::barn;
    constexpr double d3 = 6.7527 * units::barn;
    constexpr double d4 = -1.9798e+1 * units::barn;
    
    constexpr double e1 = 1.9756e-5 * units::barn;
    constexpr double e2 = -1.0205e-2 * units::barn;
    constexpr double e3 = -7.3913e-2 * units::barn;
    constexpr double e4 = 2.7079e-2 * units::barn;
    
    constexpr double f1 = -3.9178e-7 * units::barn;
    constexpr double f2 = 6.8241e-5 * units::barn;
    constexpr double f3 = 6.0480e-5 * units::barn;
    constexpr double f4 = 3.0274e-4 * units::barn;
    
    const double z2  = z * z;
    const double p1Z = z * (d1 + e1 * z + f1 * z2);
    const double p2Z = z * (d2 + e2 * z + f2 * z2);
    const double p3Z = z * (d3 + e3 * z + f3 * z2);
    const double p4Z = z * (d4 + e4 * z + f4 * z2);
    
    double t0 = 15.0 * units::kilo_electron_volt;
    
    if (z < 1.5)
    {
        t0 = 40.0 * units::kilo_electron_volt;
    }
    
    double kappa  = std::max(this->e_gamma, t0) / constants::electron_mass_c2;
    double kappa2 = kappa * kappa;
    double kappa3 = kappa2 * kappa;
    
    xsec = p1Z * log(1. + 2. * kappa) / kappa +
    (p2Z + p3Z * kappa + p4Z * kappa2) / (1. + a * kappa + b * kappa2 + c * kappa3);
    
    // low energy correction
    if (this->e_gamma < t0)
    {
        constexpr double dt0 = 1. * units::kilo_electron_volt;
        kappa                = (t0 + dt0) / constants::electron_mass_c2;
        kappa2               = kappa * kappa;
        kappa3               = kappa2 * kappa;
        const double sigma   = p1Z * log(1. + 2 * kappa) / kappa +
        (p2Z + p3Z * kappa + p4Z * kappa2) / (1. + a * kappa + b * kappa2 +
                                              c * kappa3);
        
        const double c1 = -t0 * (sigma - xsec) / (xsec * dt0);
        double c2       = 0.15;
        
        if (z > 1.5)
        {
            c2 = 0.375 - 0.0556 * log(z);
        }
        
        const double y = log(this->e_gamma / t0);
        xsec *= exp(-y * (c1 + c2 * y));
    }
    
    return xsec;
}


//---------------------------------------------------------------------------//
}  // namespace celeritas
