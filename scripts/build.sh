#!/usr/bin/env bash

mkdir -p build
cd build
cmake ..
cmake --build . -j $(nproc) --config Release --
