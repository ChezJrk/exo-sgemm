# ---------------------------------------------------------------------------- #
# Dependencies

## Exo
find_package(Python3 REQUIRED)
find_package(Exo REQUIRED HINTS "${Python3_SITELIB}")

# ---------------------------------------------------------------------------- #
# Libraries

add_exo_library(sgemm sgemm.py)
