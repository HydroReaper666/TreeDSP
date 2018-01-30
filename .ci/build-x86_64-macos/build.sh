#!/bin/sh

set -e
set -x

export PATH="/usr/local/opt/llvm/bin:$PATH"
export CC=clang
export CXX=clang++
export LDFLAGS="-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib"

mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4

./tests/tdsp-tests --durations yes
