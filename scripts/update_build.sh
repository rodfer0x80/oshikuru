#!/bin/sh
set -e
cd ./build
./premake5 gmake2
cd ..
make
