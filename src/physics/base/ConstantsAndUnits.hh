//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file ConstantsAndUnits.hh
//---------------------------------------------------------------------------//
#ifndef physics_ConstantsAndUnits_hh
#define physics_ConstantsAndUnits_hh

namespace celeritas {
//---------------------------------------------------------------------------//
/*! \note Celeritas decided to use a CGS-based system with MeV as the base
 *        energy unit for particles.
 */

namespace units {

// Lenght
constexpr double centimeter = 1.;
constexpr double millimeter = centimeter / 10.;
constexpr double      meter = 100. * centimeter;

// Mass
constexpr double gram = 1.;
constexpr double milligram = 1e-3 * gram;
constexpr double  kilogram = 1e3 * gram;

// Time
constexpr double      second = 1.;
constexpr double millisecond = 1.e-3 * second;
constexpr double microsecond = 1.e-6 * second;
constexpr double  nanosecond = 1.e-9 * second;

// Energy
constexpr double mega_electron_volt = 1.;
constexpr double      electron_volt = 1.e-6 * mega_electron_volt;
constexpr double kilo_electron_volt = 1.e-3 * mega_electron_volt;
constexpr double giga_electron_volt = 1.e+3 * mega_electron_volt;
constexpr double tera_electron_volt = 1.e+6 * mega_electron_volt;
constexpr double peta_electron_volt = 1.e+9 * mega_electron_volt;

// Area
constexpr double      barn = 1.e-28 * meter * meter;
constexpr double millibarn = 1.e-3 * barn;

} // namespace units


namespace constants {

// Universal constants
constexpr double pi = 3.14159265358979323846;
constexpr double two_pi  = 2 * pi;
constexpr double speed_of_light = 299792458; // m/s PS: SHOULD WE MOVE TO CM?
constexpr double speed_of_light_squared = speed_of_light * speed_of_light;

// Electric charge
constexpr double electric_charge_unit = 1.;
constexpr double electron_charge_SI = -1.602176487e-19; // Coulombs
constexpr double coulomb = electric_charge_unit / electron_charge_SI;

// Electron mass
constexpr double electron_mass = 0.51099891 * units::mega_electron_volt;
constexpr double electron_mass_c2 = electron_mass * speed_of_light_squared;

} // namespace constants


//---------------------------------------------------------------------------//
}  // namespace celeritas

#endif // physics_ConstantsAndUnits_hh
