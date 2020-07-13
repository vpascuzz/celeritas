//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file UniformRealDistribution.hh
//---------------------------------------------------------------------------//
#ifndef random_UniformRealDistribution_hh
#define random_UniformRealDistribution_hh

#include "GenerateCanonical.hh"
#include "base/Macros.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Sample from a uniform distribution.
 */
template<class RealType = double>
class UniformRealDistribution
{
  public:
    //@{
    //! Type aliases
    using real_type   = RealType;
    using result_type = real_type;
    //@}

  public:
    // Constructor
    explicit inline CELER_FUNCTION
    UniformRealDistribution(real_type a = 0.0, real_type b = 1.0);

    // Sample a random number according to the distribution
    template<class Generator>
    inline CELER_FUNCTION result_type operator()(Generator& rng);

    // >>> ACCESSORS

    //! Get the lower bound of the distribution
    CELER_FUNCTION real_type a() const { return a_; }

    //! Get the upper bound of the distribution
    CELER_FUNCTION real_type b() const { return delta_ + a_; }

  private:
    RealType a_;
    RealType delta_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "UniformRealDistribution.i.hh"

#endif // random_UniformRealDistribution_cuh
