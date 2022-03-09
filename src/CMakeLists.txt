# ---------------------------------------------------------------------------- #
# Dependencies

## Exo
find_package(Python3 REQUIRED)
find_package(Exo REQUIRED HINTS "${Python3_SITELIB}")

# ---------------------------------------------------------------------------- #
# Libraries

add_exo_library(sgemm sgemm.py)

# TODO: move this into upstream Exo
set_target_properties(
    sgemm
    PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_BINARY_DIR}/sgemm.exo/sgemm.h"
)
