#----------------------------------*-CMake-*----------------------------------#
# Copyright 2020 UT-Battelle, LLC and other Celeritas Developers.
# See the top-level COPYRIGHT file for details.
# SPDX-License-Identifier: (Apache-2.0 OR MIT)
#-----------------------------------------------------------------------------#
# TEST LIBRARY
#-----------------------------------------------------------------------------#

add_library(celeritas_test
  Test.cc
  detail/NonMasterResultPrinter.cc
  detail/ParallelHandler.cc
  detail/TestMain.cc
  detail/Utils.cc
)
target_link_libraries(celeritas_test celeritas GTest::GTest)
target_include_directories(celeritas_test
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

#-----------------------------------------------------------------------------#
# TESTS
#-----------------------------------------------------------------------------#

#-----------------------------------------------------------------------------#
