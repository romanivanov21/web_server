#!/bin/bash

#get current directory
DIR=$(cd $(dirname $0) && pwd);

#build directory
BUILD_DIR="$DIR/build";

#if build directory not found
if ! [[ -d "$BUILD_DIR" ]]; then
	echo "ERROR: directory $BUILD_DIR not found"
	exit
else
	cd "$BUILD_DIR/"
	#execute command clean
	make clean
	cd "$DIR/"
fi

case "$1" in
     "-all"     )
     cd "$BUILD_DIR/"
     if [[ -d "$BUILD_DIR/CMakeFiles" ]]; then
        rm -R CMakeFiles
     fi

     if [[ -f "$BUILD_DIR/CMakeCache.txt" ]]; then
        rm CMakeCache.txt
     fi

     if [[ -f "$BUILD_DIR/Makefile" ]]; then
        rm Makefile
     fi

     if [[ -f "$BUILD_DIR/cmake_install.cmake" ]]; then
        rm cmake_install.cmake
     fi

     if [[ -f "$BUILD_DIR/CTestTestfile.cmake" ]]; then
        rm CTestTestfile.cmake
     fi

     cd "$DIR";

     ;;
esac

