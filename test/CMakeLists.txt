##==================================================================================================
##  MMM - Massively Modernized MPI for C++20
##  Copyright : MMM Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
include(make_unit)
set(unit_root "${CMAKE_SOURCE_DIR}/test")

glob_unit(${unit_root} "unit/system/*.cpp")
