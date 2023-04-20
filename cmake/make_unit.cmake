##==================================================================================================
##  MMM - Massively Modernized MPI for C++20
##  Copyright : MMM Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
include(add_target_parent)

##==================================================================================================
## Find MPI and otehr dependencies
##==================================================================================================
find_package(MPI REQUIRED QUIET)

if (MPI_FOUND)
  message( STATUS "[mmm] MPI found")
else (MPI_FOUND)
  message( FATAL_ERROR "[mmm] MPI not found - Check your installation")
endif (MPI_FOUND)

##==================================================================================================
# Unit test Configuration
##==================================================================================================
add_library(mmm_test INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options( mmm_test INTERFACE /W3 /EHsc /bigobj /std:c++20)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options( mmm_test INTERFACE -std=c++20 -Werror -Wall -Wextra -Wunused-variable -Wdocumentation)
else()
  target_compile_options( mmm_test INTERFACE -std=c++20 -Werror -Wall -Wextra -Wunused-variable)
endif()

target_link_libraries(mmm_test INTERFACE MPI::MPI_CXX)

target_include_directories( mmm_test INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                          )

if(MMM_RUN_ON_CI)
  set(MPI_CLI_OPTION "--allow-run-as-root")
else()
  set(MPI_CLI_OPTION "")
endif()

##==================================================================================================
## Turn a filename to a dot-separated target name
##==================================================================================================
function(source_to_target ext filename testname)
  string(REPLACE ".cpp" ".${ext}" base ${filename})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})
  set(${testname} "${base}" PARENT_SCOPE)
endfunction()

function(setup_location test location)
set_property( TARGET ${test}
              PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${location}"
            )
add_test( NAME ${test}
          WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/${location}"
          COMMAND "${MPIEXEC_EXECUTABLE}" ${MPI_CLI_OPTION} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS}  $<TARGET_FILE:${test}>
        )
endfunction()

##==================================================================================================
## Process a list of source files to generate corresponding test target
##==================================================================================================
function(make_unit)
  foreach(file ${ARGN})
    source_to_target( "exe" ${file} test)
    add_executable(${test} ${file})

    add_target_parent(${test})
    add_dependencies(unit ${test})

    setup_location( ${test} "unit")
    target_link_libraries(${test} PUBLIC mmm_test)
  endforeach()
endfunction()

##==================================================================================================
## Generate tests from a GLOB
##==================================================================================================
function(glob_unit relative pattern)
  file(GLOB files CONFIGURE_DEPENDS RELATIVE ${relative} ${pattern})
  make_unit(${files})
endfunction()
