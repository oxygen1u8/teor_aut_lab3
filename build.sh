#!/usr/bin/env bash

root_dir=`dirname $0`
cd $root_dir
root_dir=$(pwd)

build_dir="$root_dir/build"

rm -rf "${build_dir}"
mkdir -p "${build_dir}"
cd "${build_dir}"

cmake -G "Unix Makefiles" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_BUILD_TYPE=Debug \
    ../
make
