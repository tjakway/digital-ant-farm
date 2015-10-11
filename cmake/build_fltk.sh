#!/usr/bin/env bash

#builds fltk 1.3.3 in the specified dir

USAGE='./build_fltk.sh [PARAM1] [PARAM2]
       PARAM1: the directory to build FLTK version 1.3.3 in
       PARAM2: path to FLTK version 1.3.3 source (probably CMAKE_SOURCE_DIR/lib/fltk-1.3.3)'

if [ -z "$1" ]; then
    echo "PARAM1 empty, number of arguments passed: $#"
    echo "$USAGE"
    exit 1
fi

if [ -z "$2" ]; then
    echo "PARAM2 empty, number of arguments passed: $#"
    echo "$USAGE"
    exit 1
fi

FLTK_OUTPUT_DIR="$1"
#use the absolute path to FLTK source
FLTK_SOURCE_DIR="$(cd $2; pwd)"

mkdir -p "$FLTK_OUTPUT_DIR"
cd "$FLTK_OUTPUT_DIR"

#use FLTK jpeg, zlib and png libraries instead of system built ins
#cmake has problems finding these libraries on Mac OS X
cmake -DOPTION_BUILD_EXAMPLES=OFF -DOPTION_USE_SYSTEM_LIBJPEG=OFF -DOPTION_USE_SYSTEM_ZLIB=OFF -DOPTION_USE_SYSTEM_LIBPNG=OFF "$FLTK_SOURCE_DIR"
make
