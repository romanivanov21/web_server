#!/bin/bash

#The project name
PROJECT="web_server"

#get current directory
DIR=$(cd $(dirname $0) && pwd);

#build directory ({PROJECT}/build/)
BUILD_DIR="$DIR/build";



#if folder build ton found 
if ! [[ -d "$BUILD_DIR/" ]]; then
	echo "ERROR: directory $BUILD_DIR not found"
	exit
#if file CMakeLists.txt not found
else if ! [[ -f "$BUILD_DIR/CMakeLists.txt" ]]; then
	echo "ERROR: file CMakeLists.txt from '$BUILD_DIR' not found"
	exit
else
    if ! [[ -f "/usr/lib/libgtest.a" ]]; then
        echo "You need to install the library GTest"
        if ! [[ -d "/usr/src/gtest" ]]; then
            echo "Can not found the library GTest. You need to install libgtest-dev"
            exit 25
        else
            cd /usr/src/gtest
            sudo cmake CMakeLists.txt
            sudo make
            # copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
            sudo cp *.a /usr/lib
            echo "GTest was installed"
        fi
    fi

    case "$1" in
        "-d"    )
	    #run command cmake for debug
	    cmake "$BUILD_DIR/CMakeLists.txt" -DCMAKE_BUILD_TYPE=Debug
	    ;;
	    "-r"    )
	    #run command cmake for release
	    cmake "$BUILD_DIR/CMakeLists.txt" -DCMAKE_BUILD_TYPE=Release
	    ;;
	    *)
	    echo "Options:"
        echo "  -d       Build debug version"
	    echo "  -r       Build release version"
	    exit 25
	esac
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
