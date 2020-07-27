//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Secondary.i.hh
//---------------------------------------------------------------------------//

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Construct with defaults.
 */
CELER_FUNCTION Secondary Secondary::from_failure()
{
    Secondary result;
    result.parent_track_id = {};
    return result;
}

//---------------------------------------------------------------------------//
/*!
 * Whether the Secondary succeeded
 */
CELER_FUNCTION Secondary::operator bool() const
{
    return static_cast<bool>(this->parent_track_id);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
