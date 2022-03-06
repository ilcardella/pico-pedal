#!/usr/bin/env bash

set -euo pipefail

if [[ -d build ]]; then
    rm -rf build
fi

mkdir -p build
cd build
cmake ..
cmake --build . -j $(nproc) --config Release --
