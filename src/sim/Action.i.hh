//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Action.i.hh
//---------------------------------------------------------------------------//

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Whether the function returning an action succeeded.
 *
 * This should be 'false' for (e.g.) failing to allocate memory for sampling
 * secondaries, allowing a recoverable failure (next kernel launch retries with
 */
CELER_FUNCTION bool action_completed(Action a)
{
    return a != Action::failure;
}

//---------------------------------------------------------------------------//
/*!
 * Whether the given action should kill the active track.
 */
CELER_FUNCTION bool action_kills(Action a)
{
    return int(a) >= int(Action::begin_kill_)
           && int(a) < int(Action::end_kill_);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
