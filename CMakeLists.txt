cmake_minimum_required(VERSION 3.22)
project(exo-sgemm VERSION 0.1.0)

if (PROJECT_IS_TOP_LEVEL)
  include(CTest)
endif ()

# ---------------------------------------------------------------------------- #
# Project-wide options

option(EXO_SGEMM_ENABLE_PACKAGING "Enable exo's install rules" "${PROJECT_IS_TOP_LEVEL}")

# ---------------------------------------------------------------------------- #
# Sources

add_subdirectory(src)

# ---------------------------------------------------------------------------- #
# Tests

if (BUILD_TESTING)
  add_subdirectory(test)
endif ()

# ---------------------------------------------------------------------------- #
# Packaging

if (EXO_SGEMM_ENABLE_PACKAGING)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)

  set(EXO_SGEMM_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/cmake/exo-sgemm"
      CACHE STRING "Path to exo-sgemm's CMake files")

  install(
    TARGETS sgemm EXPORT exo-sgemm-config
    RUNTIME COMPONENT exo-sgemm-runtime
    LIBRARY COMPONENT exo-sgemm-runtime
    NAMELINK_COMPONENT exo-sgemm-development
    ARCHIVE COMPONENT exo-sgemm-development
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  )

  install(
    EXPORT exo-sgemm-config
    NAMESPACE exo-sgemm::
    DESTINATION "${EXO_SGEMM_INSTALL_CMAKEDIR}"
  )

  write_basic_package_version_file(
    exo-sgemm-config-version.cmake
    COMPATIBILITY SameMinorVersion
  )

  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/exo-sgemm-config-version.cmake"
    DESTINATION "${EXO_SGEMM_INSTALL_CMAKEDIR}"
    COMPONENT exo-sgemm-development
  )
endif ()
