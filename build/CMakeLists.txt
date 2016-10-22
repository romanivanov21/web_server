cmake_minimum_required ( VERSION 3.2.2 )

set( PROJECT web_server )

set ( CMAKE_CXX_STANDARD 14 )

set ( CMAKE_CXX_STANDARD_REQUIRED on )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++" )

SET( FLAG_DEBUG "Debug" )

if( "${CMAKE_BUILD_TYPE}" STREQUAL "${FLAG_DEBUG}" )
    SET( CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "postfix applied to debug build of libraries" )
    SET( CMAKE_CXX_FLAGS_DEBUG "-O0 -g" )
    add_definitions( -D_DEBUG )
else()
    SET( CMAKE_RELEASE_POSTFIX "" CACHE STRING "postfix applied to release build of libraries" )
    SET( CMAKE_CXX_FLAGS_RELEASE "-O3 -g" )
endif()

#путь к исполнеямым файлам
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
#путь к динамическим библиотекам
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
#путь к статическим библиотекам
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )

project( ${PROJECT} )

#заголовочные файлы библиотеки http_lib
include_directories( ../http_lib/inc/lib )
#файлы реализации библиоткеи http_lib
aux_source_directory( ../http_lib/src/lisb HTTP_LIB_SRC )
#статическая библиотека http_lib
add_library( httpparser STATIC ${HTTP_LIB_SRC} )


#заголовочные файлы программы http_test
enable_testing()
include_directories( ../http_lib/inc/test )
find_package( GTest )
find_package( Threads )
#файлы реализации программы http_test
aux_source_directory( ../http_lib/src/test HTTP_LIB_TEST_SRC )
#исполняемый файл программы http_test
add_executable( http_test ${HTTP_LIB_TEST_SRC} )
#линковка исполняемого файл http_test c статической библиотекой (libhttpparse и libgtest.a)
target_link_libraries( http_test httpparser libgtest.a pthread )

#заголовочные файлы программы web_test
include_directories (
        ../inc
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
#файлы реализации программы web_server
aux_source_directory( ../src WEB_SERVER_SRC )
aux_source_directory( ../src/config WEB_SERVER_SRC )
aux_source_directory( ../src/logs WEB_SERVER_SRC )
aux_source_directory( ../src/connection WEB_SERVER_SRC )
aux_source_directory( ../src/process WEB_SERVER_SRC )
aux_source_directory( ../src/process/daemon_process WEB_SERVER_SRC )
aux_source_directory( ../src/process/worker_process WEB_SERVER_SRC )
aux_source_directory( ../src/process/master_process WEB_SERVER_SRC )
aux_source_directory( ../src/common WEB_SERVER_SRC )
aux_source_directory( ../src/daemon WEB_SERVER_SRC )
aux_source_directory( ../src/common/user_msg WEB_SERVER_SRC )
aux_source_directory( ../src/common/user_msg/en WEB_SERVER_SRC )
#исполняемый файл web_server
add_executable( web_server ${WEB_SERVER_SRC} )
#линковка исполняемого файла web_server с статическими библиотеками ( python2.7 libhttpparser )
target_link_libraries( web_server python2.7 httpparser )
