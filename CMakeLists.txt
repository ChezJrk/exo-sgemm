cmake_minimum_required(VERSION 3.22)
project(exo-sgemm VERSION 0.0.1)

if (PROJECT_IS_TOP_LEVEL)
  include(CTest)
endif ()

# ---------------------------------------------------------------------------- #
# Sources

add_subdirectory(src)

# ---------------------------------------------------------------------------- #
# Tests

if (BUILD_TESTING)
  add_subdirectory(test)
endif ()
