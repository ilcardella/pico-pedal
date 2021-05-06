#!/usr/bin/env bash

mkdir -p build
cd build
cmake .. -DTOOLCHAIN_PATH=/opt/cross-pi-gcc-9.3.0-0/bin \
         -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/rpi-zero.cmake
cmake --build . --config Release -- -j $(nproc)
