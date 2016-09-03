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


SET( FLAG_DEBUG "Debug" )
if( "${CMAKE_BUILD_TYPE}" STREQUAL "${FLAG_DEBUG}" )
    add_definitions( -D_DEBUG )
endif()

#путь к исполнеямому файлу
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )

set( SOURCES ../src/main.cpp
        ../src/config/server_config.cpp
        ../src/logs/error_log.cpp
        ../src/logs/access_log.cpp
        ../src/logs/server_log.cpp
        ../src/connection/tcp_connection_creator.cpp
        ../src/connection/tcp_connection.cpp
        ../src/config/server_config_exception.cpp
        ../src/process/daemon_process/daemon_process.cpp
        ../src/process/daemon_process/daemon_process_creator.cpp
        ../src/process/worker_process/worker_process_creator.cpp
        ../src/process/worker_process/worker_process.cpp
        ../src/common/current_system_info.cpp
        ../src/common/event_dispatcher.cpp
        ../src/process/master_process/master_process.cpp
        ../src/process/master_process/master_process_creator.cpp
        ../src/process/master_process/master_process_manager.cpp
        ../src/daemon/daemon.cpp
        ../src/config/embedding_python_api.cpp
        ../src/common/user_msg/user_msg_parser.cpp
        ../src/common/user_msg/en/en_user_msg_parser.cpp
       )

include_directories ( ../inc
        ../inc/common
        ../inc/common/user_msg/en
        ../inc/common/user_msg
        ../inc/config
        ../inc/logs
        ../inc/connection
        ../inc/process/daemon_process
        ../inc/process/master_process
        ../inc/process/worker_process
        ../inc/process
        ../inc/daemon
        )

project( ${PROJECT} )

source_group ( "Header Files" FILES ${HEADERS} )

source_group ( "Source Files" FILES ${SOURCES} )

add_executable( ${PROJECT} ${HEADRES} ${SOURCES} )

target_link_libraries( ${PROJECT} python2.7 )
