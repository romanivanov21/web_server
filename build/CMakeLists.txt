cmake_minimum_required ( VERSION 3.2.2 )

set( PROJECT web_server )

set ( CMAKE_CXX_STANDARD 14 )

set ( CMAKE_CXX_STANDARD_REQUIRED on )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++" )

#for debug
SET( CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "postfix applied to debug build of libraries" )

#SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" )

#for release
#SET( CMAKE_RELEASE_POSTFIX "" CACHE STRING "postfix applied to release build of libraries" )

#путь к исполнеямому файлу
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set( SOURCES ../src/main.cpp
             ../src/config/server_config.cpp
             ../src/common/server_loader.cpp
             ../src/logs/error_log.cpp
             ../src/logs/access_log.cpp
             ../src/connection/tcp_connection_creator.cpp
             ../src/connection/tcp_connection.cpp
             ../src/config/server_config_exception.cpp
             ../src/workers/worker_process_creator.cpp
             ../src/workers/worker_process.cpp
             ../src/common/current_system_info.cpp
   )

include_directories ( ../inc
                      ../inc/common
                      ../inc/config
                      ../inc/logs
                      ../inc/connection
                      ../inc/workers
                    )

project( ${PROJECT} )

source_group ( "Header Files" FILES ${HEADERS} )

source_group ( "Source Files" FILES ${SOURCES} )

add_executable( ${PROJECT} ${HEADRES} ${SOURCES} )

