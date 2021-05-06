#!/usr/bin/env bash

set -euo pipefail

# Install the library
mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/usr/local \
        -DBUILD_TESTS=OFF -DTOOLCHAIN_PATH=/opt/cross-pi-gcc-9.3.0-0/bin \
        -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/rpi-zero.cmake
cmake --build . --config Release --target install -- -j $(nproc)
