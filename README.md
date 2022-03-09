# exo-sgemm

Example application for Exo: AVX-512 SGEMM

This repository contains submodules. Please be sure to clone with them:

```console
$ git clone --recursive https://github.com/ChezJrk/exo-sgemm.git
```

If you forgot to do this, or if you have recently pulled the repository, run:

```console
$ git submodule update --init --recursive
```

## Building

To build this project, you will need to manually install:

* [Python] 3.9+
* [CMake] 3.22+
* [Intel oneAPI] HPC Toolkit (for MKL)

The remaining dependencies can be acquired via [vcpkg], which is included as a
submodule. These will be downloaded and installed in an isolated location during the
build (more below).

* [Google Benchmark] 1.6.0+
* [Google Test] 1.11.0+

These may also be built on your own, with [Conan], or some other mechanism, as long as
you configure the project such that [CMake can find them][config-search].

Assuming you have the first set of dependencies installed, run:

```console
dev@host:exo-sgemm$ python -m venv $HOME/.venv/exo-sgemm
dev@host:exo-sgemm$ source $HOME/.venv/exo-sgemm/bin/activate
(exo-sgemm) dev@host:exo-sgemm$ python -m pip install -U pip setuptools wheel
(exo-sgemm) dev@host:exo-sgemm$ python -m pip install -r requirements.txt
(exo-sgemm) dev@host:exo-sgemm$ cmake --preset vcpkg-gcc
...
(exo-sgemm) dev@host:exo-sgemm$ cmake --build build
...
(exo-sgemm) dev@host:exo-sgemm$ ctest --test-dir build
```

When using this preset, vcpkg will install its dependencies into a subdirectory of
the `build` folder. It will also store caches of the dependencies in a platform-specific
location. To completely remove everything created by the build command, you will need to
remove these folders as well. If you wish to disable this caching behavior, set the
environment variable `VCPKG_BINARY_SOURCES=clear`. For more information, see the vcpkg
documentation here: https://vcpkg.io/en/docs/users/binarycaching.html

We strongly recommend setting the `CC` and `CXX` environment variables to point to Clang
13 for maximum performance. However, you may use any compatible compiler you wish. To
ease building with MSVC, use the `vcpkg-msvc` preset instead of `vcpkg-gcc`. If you do
not wish to use the presets, be sure to set `CMAKE_{C,CXX}_FLAGS` (either at the command
line or in a toolchain file) such that AVX-512 code will compile.

[CMake]: https://cmake.org/download/

[Google Benchmark]: https://github.com/google/benchmark

[Google Test]: https://github.com/google/googletest

[Intel oneAPI]: https://www.intel.com/content/www/us/en/developer/tools/oneapi/hpc-toolkit-download.html

[Python]: https://www.python.org/downloads/

[config-search]: https://cmake.org/cmake/help/latest/command/find_package.html#config-mode-search-procedure

[vcpkg]: https://vcpkg.io
