#!/usr/bin/env bash

set -euo pipefail

# Build the automated test suite
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/tmp/guitar_fx_lib -DBUILD_TESTS=ON ..
cmake --build . -j $(nproc) --config Release --

# Run the test
export GTEST_COLOR=1
cmake --build . --config Release -j $(nproc) --target run_tests --

# Test install target
cmake --build . --config Release -j $(nproc) --target install --
