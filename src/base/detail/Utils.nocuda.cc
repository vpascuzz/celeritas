//---------------------------------*-C++-*-----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file Utils.cc
//---------------------------------------------------------------------------//
#include "Utils.hh"

namespace celeritas
{
namespace detail
{
//---------------------------------------------------------------------------//
void device_memset(void*, int, size_type)
{
    REQUIRE(0);
}

//---------------------------------------------------------------------------//
} // namespace detail
} // namespace celeritas
