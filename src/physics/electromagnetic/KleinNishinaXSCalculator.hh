//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file KleinNishinaXSCalculator.hh
//---------------------------------------------------------------------------//
#ifndef physics_electromagnetic_KleinNishinaXSCalculator_hh
#define physics_electromagnetic_KleinNishinaXSCalculator_hh

namespace celeritas {
//---------------------------------------------------------------------------//
/*!
 * Brief class description.
 *
 * Optional detailed class description, and possibly example usage:
 * \code
    KleinNishinaXSCalculator ...;
   \endcode
 */
class KleinNishinaXSCalculator
{
  public:
    //@{
    //! Type aliases
    using AtomicNumberType = double;
    //@}

  public:
    // Construct with defaults
    inline KleinNishinaXSCalculator(double energy);

    inline double operator()(AtomicNumberType z) const;

  private:
    //! Energy of the incident photon
    double energy_;
};

//---------------------------------------------------------------------------//
}  // namespace celeritas

#include "KleinNishinaXSCalculator.i.hh"

#endif // physics_electromagnetic_KleinNishinaXSCalculator_hh
