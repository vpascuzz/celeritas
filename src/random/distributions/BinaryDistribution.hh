//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file BinaryDistribution.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/Macros.hh"
#include "base/Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Select one of two options with a given probability.
 *
 * The constructor argument is the chance of returning `true`, with an optional
 * second argument for normalizing with a fraction of `false` values.
 * \code
    BinaryDistribution snake_eyes(1, 35);
    if (snake_eyes(rng))
    {
        // ...
    }
    BinaryDistribution also_snake_eyes(1.0 / 36.0);
   \endcode
 *
 * \note Since `true` is 1 and `false` is 0, the constructor argument is the
 * _opposite_ order of std::discrete_distribution.
 */
class BinaryDistribution
{
  public:
    //@{
    //! Type aliases
    using result_type = bool;
    //@}

  public:
    // Construct with the probability of returning true
    explicit inline CELER_FUNCTION BinaryDistribution(real_type p_true);

    // Construct with the UNnormalized probability of returning true or false
    inline CELER_FUNCTION
    BinaryDistribution(real_type scaled_true, real_type scaled_false);

    // Sample true or false based on the probability
    template<class Generator>
    inline CELER_FUNCTION result_type operator()(Generator& rng);

    // Probability of returning `true` from operator()
    real_type p_true() const { return p_true_; }

  private:
    real_type p_true_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "BinaryDistribution.i.hh"
//---------------------------------------------------------------------------//
