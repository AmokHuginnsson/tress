cmake_minimum_required( VERSION 2.8 )
project( tress CXX )
include( ../yaal/_aux/cmakelib.cmake )

use_cxx_compiler_flag( -Wno-missing-noreturn )

include_directories( . )
configure_file( ../yaal/_aux/cmake-client-config.hxx build/${CMAKE_BUILD_TYPE}/config.hxx )

file( GLOB SRCS ./src/*.cxx )
add_executable( ${PROJECT_NAME} ${SRCS} )
add_library( tressplugin MODULE data/plugin.cxx )
set_target_properties( ${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME 1exec RUNTIME_OUTPUT_DIRECTORY build/${CMAKE_BUILD_TYPE}/tress )
set_target_properties( tressplugin PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME 1exec PREFIX "" SUFFIX "" LIBRARY_OUTPUT_DIRECTORY build/${CMAKE_BUILD_TYPE}/tressplugin )
target_link_libraries( ${PROJECT_NAME} hdata${LIB_INFIX} hconsole${LIB_INFIX} dbwrapper${LIB_INFIX} tools${LIB_INFIX} hcore${LIB_INFIX} boost_regex-mt boost_filesystem-mt boost_program_options-mt boost_date_time-mt )

