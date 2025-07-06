#!/bin/bash
set -e

[ -d ./build ] && rm -rf ./build

mkdir build
cd build && cmake .. && make -j32
