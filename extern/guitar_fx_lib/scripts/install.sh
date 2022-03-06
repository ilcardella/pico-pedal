#!/usr/bin/env bash

set -euo pipefail

if [[ -d build ]]; then
    rm -rf build
fi

# Build the automated test suite
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr/local -DBUILD_TESTS=OFF ..
cmake --build . -j $(nproc) --config Release --target install --
