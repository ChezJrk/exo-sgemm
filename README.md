# exo-sgemm

Example application for Exo: AVX-512 SGEMM

## Building

To build this project, you will need:

* Python 3.9+
* CMake 3.22+

Assuming you have these dependencies installed, run:

```
$ python -m venv $HOME/.venv/exo-sgemm
$ source $HOME/.venv/exo-sgemm/bin/activate
(exo-sgemm) $ python -m pip install -U pip setuptools wheel
(exo-sgemm) $ python -m pip install -r requirements.txt
(exo-sgemm) $ cmake --preset vcpkg-gcc
...
(exo-sgemm) $ cmake --build build
...
(exo-sgemm) $ ctest --test-dir build
```

We strongly recommend setting the `CC` and `CXX` environment variables to point to Clang
13 for maximum performance. However, you may use any compatible compiler you wish. To
ease building with MSVC, use the `vcpkg-msvc` preset instead of `vcpkg-gcc`. If you do
not wish to use the presets, be sure to set `CMAKE_{C,CXX}_FLAGS` (either at the command
line or in a toolchain file) such that AVX-512 code will compile.
