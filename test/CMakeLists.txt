# ---------------------------------------------------------------------------- #
# Dependencies

## oneAPI MKL
set(MKL_ARCH "intel64"
    CACHE STRING "MKL architecture. Options: intel64, ia32")
set(MKL_LINK "static"
    CACHE STRING "MKL link type. Options: dynamic, static, sdl")
set(MKL_THREADING "sequential"
    CACHE STRING "MKL threading model. Options: sequential, intel_thread, gnu_thread, pgi_thread, tbb_thread")
set(MKL_INTERFACE "lp64"
    CACHE STRING "MKL interface type. Options: lp64, ilp64")
set(MKL_MPI "openmpi"
    CACHE STRING "Which MPI interface to use. Options: intelmpi, mpich, openmpi, msmpi, mshpc")

find_package(MKL REQUIRED)

## Google Benchmark
find_package(benchmark REQUIRED)

## Google Test
find_package(GTest REQUIRED)

# ---------------------------------------------------------------------------- #
# Tests

add_executable(correctness correctness.cpp)
target_link_libraries(correctness PRIVATE GTest::gtest_main exo-sgemm::sgemm MKL::MKL)
target_compile_features(correctness PRIVATE cxx_std_17)

gtest_discover_tests(correctness)

# ---------------------------------------------------------------------------- #
# Benchmarks

add_executable(benchmark benchmark.cpp)
target_link_libraries(
    benchmark PRIVATE benchmark::benchmark_main exo-sgemm::sgemm MKL::MKL)
target_compile_features(benchmark PRIVATE cxx_std_17)
