#!/usr/bin/env bash

mkdir -p build
cd build
cmake ..
cmake --build . --config Release -- -j $(nproc)
