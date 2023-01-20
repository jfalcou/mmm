##==================================================================================================
##  MMM - Massively Modernized MPI for C++20
##  Copyright : MMM Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
include(GNUInstallDirs)
set(MAIN_DEST     "${CMAKE_INSTALL_LIBDIR}/mmm-${PROJECT_VERSION}")
set(INSTALL_DEST  "${CMAKE_INSTALL_INCLUDEDIR}/mmm-${PROJECT_VERSION}")
set(DOC_DEST      "${CMAKE_INSTALL_DOCDIR}-${PROJECT_VERSION}")

## =================================================================================================
## Exporting target for external use
## =================================================================================================
add_library(mmm_lib INTERFACE)
target_include_directories( mmm_lib INTERFACE
                            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:${INSTALL_DEST}>
                          )
target_compile_features(mmm_lib INTERFACE cxx_std_20)
set_target_properties(mmm_lib PROPERTIES EXPORT_NAME mmm)
add_library(mmm::mmm ALIAS mmm_lib)

## =================================================================================================
## Install target with versioned folder
## =================================================================================================
install(TARGETS   mmm_lib EXPORT mmm-targets DESTINATION "${MAIN_DEST}")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mmm               DESTINATION "${INSTALL_DEST}" )
install(FILES     ${PROJECT_SOURCE_DIR}/cmake/mmm-config.cmake    DESTINATION "${MAIN_DEST}"    )
install(FILES     ${PROJECT_SOURCE_DIR}/LICENSE.md                DESTINATION "${DOC_DEST}"     )
install(EXPORT    mmm-targets NAMESPACE "mmm::" DESTINATION "${MAIN_DEST}")
