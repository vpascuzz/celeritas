//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file GenerateCanonical.i.hh
//---------------------------------------------------------------------------//

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Generate random numbers in [0, 1).
 */
template<class Generator, class RealType>
CELER_FUNCTION auto
GenerateCanonical<Generator, RealType>::operator()(Generator& rng)
    -> result_type
{
    using limits_t = std::numeric_limits<result_type>;
    return std::generate_canonical<result_type, limits_t::digits>(rng);
}

//---------------------------------------------------------------------------//
/*!
 * Helper function to generate a random real number in [0, 1).
 */
template<class RealType, class Generator>
CELER_FUNCTION RealType sample_uniform(Generator& g)
{
    return GenerateCanonical<Generator, RealType>()();
}

//---------------------------------------------------------------------------//
/*!
 * Helper function to generate a random real number in [0, 1).
 */
template<class Generator>
CELER_FUNCTION real_type sample_uniform(Generator& g)
{
    return GenerateCanonical<Generator, real_type>()();
}

//---------------------------------------------------------------------------//
} // namespace celeritas
