//---------------------------------*-CUDA-*----------------------------------//
// Copyright 2020 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file StackAllocatorView.hh
//---------------------------------------------------------------------------//
#pragma once

#include "Macros.hh"
#include "StackAllocatorPointers.hh"
#include "Types.hh"

namespace celeritas
{
//---------------------------------------------------------------------------//
/*!
 * Low-level functor for allocating memory on a stack.
 *
 * This class acts like \c malloc but with no alignment. The calling class
 * should make sure each allocation is sufficient for \c alignof(T) or 16. It
 * performs no initialization on the data.
 *
 * \code
    StackAllocatorView alloc(view);
    double* temp_dbl = alloc(4 * sizeof(double));
   \endcode
 */
class StackAllocatorView
{
  public:
    //@{
    //! Type aliases
    using result_type = void*;
    using size_type   = StackAllocatorPointers::size_type;
    //@}

  public:
    // Construct with a reference to the storage pointers
    explicit inline CELER_FUNCTION
    StackAllocatorView(const StackAllocatorPointers&);

    // Allocate like malloc
    inline CELER_FUNCTION result_type operator()(size_type size);

    //! Get a pointer to the stored data
    CELER_FUNCTION byte* data() { return shared_.storage.data(); }

    //! Get a pointer to the stored data
    CELER_FUNCTION const byte* data() const { return shared_.storage.data(); }

    // Get the current (NON THREAD SAFE) storage size in bytes
    inline CELER_FUNCTION size_type size() const;

  private:
    const StackAllocatorPointers& shared_;
};

//---------------------------------------------------------------------------//
} // namespace celeritas

#include "StackAllocatorView.i.hh"

//---------------------------------------------------------------------------//
