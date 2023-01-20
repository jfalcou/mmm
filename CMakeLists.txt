##==================================================================================================
##  MMM - Massively Modernized MPI for C++20
##  Copyright : MMM Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
cmake_minimum_required(VERSION 3.2)
enable_testing()

##==================================================================================================
## Setup project
##==================================================================================================
project(mmm LANGUAGES CXX)

set(MMM_MAJOR_VERSION 0)
set(MMM_MINOR_VERSION 1)
set(MMM_PATCH_VERSION 0)
set(MMM_VERSION ${MMM_MAJOR_VERSION}.${MMM_MINOR_VERSION}.${MMM_PATCH_VERSION})

set(PROJECT_VERSION   ${MMM_VERSION})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )

##==================================================================================================
## No in-source build
##==================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[mmm]: In-source build is not recommend")
endif()

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mmm TYPE INCLUDE)
include(mmm-install)

##==================================================================================================
## Options
##==================================================================================================
option( MMM_BUILD_TEST          "Build tests for mmm" ON )
option( MMM_BUILD_DOCUMENTATION "Build docs for mmm" OFF )
#option( MMM_BUILD_INTEGRATION   "Build integration tests for mmm" OFF )

##==================================================================================================
## Test targets
##==================================================================================================
# if( MMM_BUILD_TEST )
#   include(CTest)
#   add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
# endif()

# if( MMM_BUILD_INTEGRATION )
#   include(CTest)
#   add_subdirectory(${PROJECT_SOURCE_DIR}/test/integration)
# endif()

##==================================================================================================
## Add Doxygen building target
##==================================================================================================
if( MMM_BUILD_DOCUMENTATION )
  include(cmake/mmm-doxygen.cmake)
endif()
