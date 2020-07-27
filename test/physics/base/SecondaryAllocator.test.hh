//----------------------------------*-C++-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file SecondaryAllocator.test.hh
//---------------------------------------------------------------------------//

namespace celeritas_test
{
using namespace celeritas;
//---------------------------------------------------------------------------//
// TESTING INTERFACE
//---------------------------------------------------------------------------//
//! Input data
struct SATestInput
{
    int                        num_threads;
    int                        num_iters;
    int                        alloc_size;
    SecondaryAllocatorPointers sa_view;
};

//---------------------------------------------------------------------------//
//! Output results
struct SATestOutput
{
    std::vector<int>    parent_track;
    std::vector<int>    def_id;
    std::vector<double> energy;
};

//---------------------------------------------------------------------------//
//! Run on device and return results
SATestOutput sa_test(SATestInput);

//---------------------------------------------------------------------------//
} // namespace celeritas_test
