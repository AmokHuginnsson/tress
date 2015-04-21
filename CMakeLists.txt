cmake_minimum_required( VERSION 2.8 )
project( tress CXX )
include( ../yaal/_aux/cmake/common.cmake )

if ( NOT ( "$ENV{BOOST_INSTALL_PATH}" STREQUAL "" ) )
	set( BOOST_ROOT "$ENV{BOOST_INSTALL_PATH}" )
elseif ( NOT ( "${BOOST_INSTALL_PATH}" STREQUAL "" ) )
	set( BOOST_ROOT "${BOOST_INSTALL_PATH}" )
endif()

if ( CMAKE_HOST_WIN32 )
	add_definitions( /D_ALLOW_KEYWORD_MACROS=1 )
	include_directories( ${BOOST_ROOT}/include )
	link_directories( ${BOOST_ROOT}/lib )
endif()

use_cxx_compiler_flag( -Wno-missing-noreturn )
find_package( Boost COMPONENTS filesystem date_time system REQUIRED )
find_package( Yaal COMPONENTS hcore tools dbwrapper hconsole REQUIRED )

check_cxx_source_compiles( "
#ifdef __GNUC__
#include <ext/functional>
using namespace __gnu_cxx;
#else
#define _HAS_TRADITIONAL_STL 1
#include <functional>
#endif

using namespace std;

int main( int, char** )
	{
	compose1( negate<int>(), negate<int>() )( 7 );
	return ( 0 );
	}
" HAVE_SGI_STL_EXTENSIONS )

check_symbol_exists( RTLD_NEXT dlfcn.h HAVE_DECL_RTLD_NEXT )

include_directories( . )
configure_file( ../yaal/_aux/cmake/client-config.hxx ${TARGET_PATH}/config.hxx )

file( GLOB SRCS ./src/*.cxx )
file( GLOB HDRS ./src/*.hxx )
file( GLOB CHILD_SRCS ./child/*.cxx )
file( GLOB CHILD_HDRS ./child/*.hxx )
file( GLOB TUT ./TUT/*.hpp )
add_executable( ${PROJECT_NAME} ${SRCS} ${HDRS} ../yaal/_aux/cmake/client-config.hxx )
add_executable( child ${CHILD_SRCS} ${CHILD_HDRS} )
add_library( tressplugin MODULE data/plugin.cxx )
add_library( TUT ${TUT} )
set_target_properties(
	${PROJECT_NAME} PROPERTIES
	LINKER_LANGUAGE CXX
	OUTPUT_NAME 1exec
	RUNTIME_OUTPUT_DIRECTORY ${TARGET_PATH}/tress
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_PATH}/tress
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_PATH}/tress
	RUNTIME_OUTPUT_DIRECTORY_COV ${TARGET_PATH}/tress
	RUNTIME_OUTPUT_DIRECTORY_PROF ${TARGET_PATH}/tress
)
set_target_properties(
	child PROPERTIES
	LINKER_LANGUAGE CXX
	OUTPUT_NAME 1exec
	RUNTIME_OUTPUT_DIRECTORY ${TARGET_PATH}/child
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_PATH}/child
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_PATH}/child
	RUNTIME_OUTPUT_DIRECTORY_COV ${TARGET_PATH}/child
	RUNTIME_OUTPUT_DIRECTORY_PROF ${TARGET_PATH}/child
)
set_target_properties( TUT PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( tressplugin PROPERTIES LINKER_LANGUAGE CXX )
if ( CMAKE_HOST_WIN32 )
	add_executable( child-simple ${CMAKE_HOME_DIRECTORY}/data/child.cxx )
	set_target_properties( child-simple PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME child RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/data )
	set_target_properties( tressplugin PROPERTIES OUTPUT_NAME tressplugin${LIB_INFIX} LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/data )
	set_target_properties( child PROPERTIES COMPILE_DEFINITIONS "_SIGNAL_H=1" )
	set_source_files_properties( ${CHILD_SRCS} PROPERTIES COMPILE_FLAGS "/FIglibc/bits/signum.h /FIyaal/fix.hxx" )
	target_link_libraries( ${PROJECT_NAME} ${Yaal_LIBRARIES} libintl )
	target_link_libraries( child ${Yaal_LIBRARIES} libintl )

	file( GLOB makedef_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/makedef.vc*proj )
	include_external_msproject( makedef ${makedef_PROJ} )

	file( GLOB msvcxx_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/msvcxx.vc*proj )
	include_external_msproject( msvcxx ${msvcxx_PROJ} )

	file( GLOB hcore_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/hcore.vc*proj )
	include_external_msproject( hcore ${hcore_PROJ} )
	file( GLOB hcore_static_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/hcore-static.vc*proj )
	include_external_msproject( hcore-static ${hcore_static_PROJ} msvcxx makedef )

	file( GLOB tools_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/tools.vc*proj )
	include_external_msproject( tools ${tools_PROJ} )
	file( GLOB tools_static_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/tools-static.vc*proj )
	include_external_msproject( tools-static ${tools_static_PROJ} )

	file( GLOB dbwrapper_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/dbwrapper.vc*proj )
	include_external_msproject( dbwrapper ${dbwrapper_PROJ} )
	file( GLOB dbwrapper_static_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/dbwrapper-static.vc*proj )
	include_external_msproject( dbwrapper-static ${dbwrapper_static_PROJ} )

	file( GLOB hconsole_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/hconsole.vc*proj )
	include_external_msproject( hconsole ${hconsole_PROJ} )
	file( GLOB hconsole_static_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/hconsole-static.vc*proj )
	include_external_msproject( hconsole-static ${hconsole_static_PROJ} )

	file( GLOB hdata_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/hdata.vc*proj )
	include_external_msproject( hdata ${hdata_PROJ} )
	file( GLOB hdata_static_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/hdata-static.vc*proj )
	include_external_msproject( hdata-static ${hdata_static_PROJ} )

	file( GLOB sqlite3_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/sqlite3.vc*proj )
	include_external_msproject( sqlite3 ${sqlite3_PROJ} )

	file( GLOB headers_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/headers.vc*proj )
	include_external_msproject( headers ${headers_PROJ} )

	file( GLOB mkheaders_PROJ RELATIVE ${CMAKE_HOME_DIRECTORY} ../yaal/mkheaders.vc*proj )
	include_external_msproject( mkheaders ${mkheaders_PROJ} )

	file( RELATIVE_PATH TARGET_PATH_RELATIVE ${CMAKE_HOME_DIRECTORY} ${TARGET_PATH} )
	set( INSTALLED_HEADER "${CMAKE_INSTALL_PREFIX}/include/yaal/yaal.hxx" )
	set( YAAL_TARGET_PATH "${CMAKE_HOME_DIRECTORY}/../yaal/${TARGET_PATH_RELATIVE}" )
	set( GENERATED_HEADERS "${YAAL_TARGET_PATH}/include/yaal" )
#	message( "Info:\n"
#		"\tCMAKE_HOME_DIRECTORY=${CMAKE_HOME_DIRECTORY}\n"
#		"\tCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}\n"
#		"\tTARGET_PATH=${TARGET_PATH}\n"
#		"\tTARGET_PATH_RELATIVE=${TARGET_PATH_RELATIVE}\n"
#		"\tINSTALLED_HEADER=${INSTALLED_HEADER}\n"
#		"\tYAAL_TARGET_PATH=${YAAL_TARGET_PATH}\n"
#		"\tGENERATED_HEADERS=${GENERATED_HEADERS}" )

	add_custom_command( OUTPUT ${INSTALLED_HEADER}
		COMMAND cmd /c "( robocopy /e /np /njh /ndl /njs ${GENERATED_HEADERS} ${CMAKE_INSTALL_PREFIX}/include/yaal ) ^& IF %ERRORLEVEL% LEQ 1 exit /b 0"
		COMMAND cmd /c "( robocopy /xx /np /njh /ndl /njs ${YAAL_TARGET_PATH} ${CMAKE_INSTALL_PREFIX}/lib *.lib ) ^& IF %ERRORLEVEL% LEQ 1 exit /b 0"
		COMMAND cmd /c "( robocopy /xx /np /njh /ndl /njs ${YAAL_TARGET_PATH} ${CMAKE_INSTALL_PREFIX}/bin *.dll ) ^& IF %ERRORLEVEL% LEQ 1 exit /b 0"
		DEPENDS ${GENERATED_HEADERS}/yaal.hxx headers hdata hdata-static hconsole hconsole-static dbwrapper dbwrapper-static tools tools-static hcore hcore-static msvcxx
		VERBATIM )
	add_custom_target( install_yaal DEPENDS ${INSTALLED_HEADER} )

	add_dependencies( tress install_yaal )
	add_dependencies( tressplugin install_yaal )

else()
	set_target_properties( ${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -Wno-variadic-macros )
	set_target_properties(
		tressplugin PROPERTIES
		OUTPUT_NAME 1exec
		PREFIX ""
		SUFFIX ""
		LIBRARY_OUTPUT_DIRECTORY ${TARGET_PATH}/tressplugin
		LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_PATH}/tressplugin
		LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_PATH}/tressplugin
		LIBRARY_OUTPUT_DIRECTORY_COV ${TARGET_PATH}/tressplugin
		LIBRARY_OUTPUT_DIRECTORY_PROF ${TARGET_PATH}/tressplugin
	)
	target_link_libraries( ${PROJECT_NAME} ${Yaal_LIBRARIES} ${Boost_LIBRARIES} dl )
	target_link_libraries( child ${Yaal_LIBRARIES} )
endif()

