//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryStackView.hh
//---------------------------------------------------------------------------//
#ifndef physics_base_SecondaryStackView_hh
#define physics_base_SecondaryStackView_hh

#include "base/StackAllocatorView.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * View to data for allocating secondaries.
 */
struct SecondaryStackView
{
    StackAllocatorView allocator_view;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#endif // physics_base_SecondaryStackView_hh
