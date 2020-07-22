//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryStack.hh
//---------------------------------------------------------------------------//
#pragma once

#include "base/StackAllocator.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Stack of secondary particles added by a physics process.
 */
class SecondaryStackAllocator
{
  public:
    //@{
    //! Type aliases
    using result_type = Secondary*;
    //@}

  public:
    // Construct with defaults
    explicit inline CELER_FUNCTION
    SecondaryStackAllocator(const SecondaryStackPointers& shared);

    // Allocate space for this many secondaries
    inline CELER_FUNCTION result_type operator()(size_type count);

  private:
    StackAllocator allocate_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "SecondaryStack.i.hh"