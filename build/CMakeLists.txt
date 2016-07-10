cmake_minimum_required ( VERSION 3.2.2 )

set( PROJECT web_server )

set ( CMAKE_CXX_STANDARD 14 )

set ( CMAKE_CXX_STANDARD_REQUIRED on )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++" )

#for debug version
SET( CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "postfix applied to debug build of libraries" )

#SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" )

#for release version
#SET( CMAKE_RELEASE_POSTFIX "" CACHE STRING "postfix applied to release build of libraries" )

#путь к исполнеямому файлу
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set( SOURCES ../src/main.cpp )

include_directories ( ../inc )

project( ${PROJECT} )

source_group ( "Header Files" FILES ${HEADERS} )

source_group ( "Source Files" FILES ${SOURCES} )

add_executable( ${PROJECT} ${HEADRES} ${SOURCES} )

