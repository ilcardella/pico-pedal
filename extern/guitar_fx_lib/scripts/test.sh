#!/usr/bin/env bash

set -euo pipefail

# Build the automated test suite
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/tmp/guitar_fx_lib -DBUILD_TESTS=ON ..
cmake --build . --config Release -- -j $(nproc)

# Run the test
export GTEST_COLOR=1
cmake --build . --config Release --target run_tests -- -j $(nproc)

# Test install target
cmake --build . --config Release --target install -- -j $(nproc)
