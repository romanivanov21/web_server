#!/bin/bash

#The project name
PROJECT="web_server"

#get current directory
DIR=$(cd $(dirname $0) && pwd);

#build directory ({PROJECT}/build/)
BUILD_DIR="$DIR/build";

#if folder build ton found 
if ! [[ -d $BUILD_DIR ]]; then
	echo "ERROR: directory $BUILD_DIR not found"
	exit
#if file CMakeLists.txt not found
else if ! [[ -f "$BUILD_DIR/CMakeLists.txt" ]]; then
	echo "ERROR: file CMakeLists.txt from '$BUILD_DIR' not found"
	exit
else
	#run command cmake
	cmake "$BUILD_DIR/CMakeLists.txt"
	#if Makefile not found 
	if ! [[ -f "$BUILD_DIR/Makefile" ]]; then
		echo "ERROR: make file from $BUILD_DIR not found"
		exit
	else
		cd "$BUILD_DIR/"
		#execute Makefile
		make
		cd "$DIR/"
	fi
fi
fi

#if output file not found
if ! [[ -f "$BUILD_DIR/$PROJECT" ]]; then
	echo "ERROR: execute file '$PROJECT' not found"
	exit
#if foldef 'bin' and output file found 
else if [[ -d "$BUILD_DIR/bin" ]] && ! [[ -f "$BUILD_DIR/bin/$PROJECT" ]]; then
	mv "$BUILD_DIR/$PROJECT" "$BUILD_DIR/bin" && echo "-- Move new executable file '$PROJECT' from $BUILD_DIR/ to $BUILD_DIR/bin/"
#if folder 'bin' found and output file not found
else if [[ -d "$BUILD_DIR/bin" ]] && [[ -f "$BUILD_DIR/bin/$PROJECT" ]]; then
	rm -R "$BUILD_DIR/bin/$PROJECT"
	mv "$BUILD_DIR/$PROJECT" "$BUILD_DIR/bin" && echo "-- Move new executable file '$PROJECT' from $BUILD_DIR/ to $BUILD_DIR/bin/"
else
#if folder 'bin' nit found
	mkdir "$BUILD_DIR/bin" && echo "-- Create folder 'bin' for the executable files"
	mv "$BUILD_DIR/$PROJECT" "$BUILD_DIR/bin" && echo "-- Move executable file '$PROJECT' from $BUILD_DIR/ to $BUILD_DIR/bin/"
fi
fi
fi

