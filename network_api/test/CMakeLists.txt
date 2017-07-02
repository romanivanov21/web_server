cmake_minimum_required ( VERSION 3.2.2 )

set( PROJECT NETWORK_API_TEST )

set ( CMAKE_CXX_STANDARD 14 )

set ( CMAKE_CXX_STANDARD_REQUIRED on )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++" )

set ( CMAKE_INCLUDE_CURRENT_DIR ON )

set ( CMAKE_AUTOMOC ON )

set ( FLAG_DEBUG "Debug" )

if( "${CMAKE_BUILD_TYPE}" STREQUAL "${FLAG_DEBUG}" )
    SET( CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "postfix applied to debug build of libraries" )
    SET( CMAKE_CXX_FLAGS_DEBUG "-O0 -g" )
    add_definitions( -D_DEBUG )
else()
    SET( CMAKE_RELEASE_POSTFIX "" CACHE STRING "postfix applied to release build of libraries" )
    SET( CMAKE_CXX_FLAGS_RELEASE "-O3 -g" )
endif()

file(GLOB_RECURSE NETWORK_API_TEST_HEADERS "/include/*.h")
file(GLOB_RECURSE NETWORK_API_TEST_SOURCES "/source/*.h")
file(GLOB_RECURSE NETWORK_API_TEST_SOURCES "/source/*.cpp")

#путь к исполнеямым файлам
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
#путь к динамическим библиотекам
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
#путь к статическим библиотекам
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )

project( ${PROJECT} )

#исполняемый файл network_api
add_executable( ${PROJECT} ${NETWORK_API_TEST_HEADERS} ${NETWORK_API_TEST_SOURCES} )