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
 * Whether the given action should kill the active track.
 */
CELER_INLINE_FUNCTION bool action_kills(Action a)
{
    using enum_int = int;
    return int(a) >= int(Action::begin_kill) && int(a) < int(Action::end_kill);
}

//---------------------------------------------------------------------------//
} // namespace celeritas
