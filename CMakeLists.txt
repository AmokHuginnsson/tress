cmake_minimum_required( VERSION 3.13 )
file( TO_CMAKE_PATH "$ENV{YAAL_SOURCE_PATH}" YAAL_SOURCE_PATH )
if ( "${YAAL_SOURCE_PATH}" STREQUAL "" )
	set( YAAL_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../yaal" )
endif()
set( CMAKE_MODULE_PATH "${YAAL_SOURCE_PATH}/_aux/cmake" ${CMAKE_MODULE_PATH} )
project( tress CXX )
include( lib )
include( common )

if ( NOT ( "$ENV{BOOST_INSTALL_PATH}" STREQUAL "" ) )
	set( BOOST_ROOT "$ENV{BOOST_INSTALL_PATH}" )
elseif ( NOT ( "${BOOST_INSTALL_PATH}" STREQUAL "" ) )
	set( BOOST_ROOT "${BOOST_INSTALL_PATH}" )
endif()

if ( CMAKE_HOST_WIN32 )
	add_definitions( /D_ALLOW_KEYWORD_MACROS=1 )
	include_directories( ${BOOST_ROOT}/include )
	link_directories( ${BOOST_ROOT}/lib )
else()
	use_cxx_compiler_flag( -Wno-missing-noreturn )
	use_cxx_compiler_flag( -Wl,--export-dynamic )
	use_cxx_compiler_flag( -rdynamic )
endif()

find_package( Boost COMPONENTS filesystem date_time system )
find_package( Yaal COMPONENTS hcore tools dbwrapper hconsole hdata REQUIRED )

check_cxx_source_compiles( "
#ifdef __GNUC__
#include <ext/functional>
using namespace __gnu_cxx;
#else
#define _HAS_TRADITIONAL_STL 1
#include <functional>
#endif

using namespace std;

int main( int, char** ) {
	compose1( negate<int>(), negate<int>() )( 7 );
	return ( 0 );
}
" HAVE_SGI_STL_EXTENSIONS )

check_cxx_source_compiles( "
#include <functional>

using namespace std;

int main( int, char** ) {
	std::bind2nd( std::less<int>(), 0 );
	return ( 0 );
}
" HAVE_PRE_CXX17_STL )

check_symbol_exists( RTLD_NEXT dlfcn.h HAVE_DECL_RTLD_NEXT )
set( CMAKE_EXTRA_INCLUDE_FILES_ORIG "${CMAKE_EXTRA_INCLUDE_FILES}" )
if ( CMAKE_HOST_WIN32 )
	set( CMAKE_EXTRA_INCLUDE_FILES "curses.h" )
	set( CMAKE_REQUIRED_INCLUDES "${CMAKE_INCLUDE_PATH}" )
else()
	set( CMAKE_EXTRA_INCLUDE_FILES "ncurses.h" )
endif()
check_type_size( "chtype" CHTYPE )
check_type_size( "mmask_t" MMASK_T )
set( CMAKE_EXTRA_INCLUDE_FILES "${CMAKE_EXTRA_INCLUDE_FILES_ORIG}" )
if ( HAVE_CHTYPE )
	set( SIZEOF_CHTYPE ${CHTYPE} )
endif()
if ( HAVE_MMASK_T )
	set( SIZEOF_MMASK_T ${MMASK_T} )
endif()

if ( NOT ( "$ENV{CONTINUOUS_INTEGRATION_SYSTEM}" STREQUAL "" ) )
	string( TOUPPER $ENV{CONTINUOUS_INTEGRATION_SYSTEM} CONTINUOUS_INTEGRATION_SYSTEM )
	string( REPLACE "-" "_" CONTINUOUS_INTEGRATION_SYSTEM "${CONTINUOUS_INTEGRATION_SYSTEM}" )
endif()

include_directories( . )
set( HAVE_LOCAL_HXX 1 )
configure_file( "${YAAL_SOURCE_PATH}/_aux/cmake/client-config.hxx" ${TARGET_PATH}/config.hxx )
configure_file( ./src/local.hxx ${TARGET_PATH}/local.hxx )

file( GLOB SRCS ./src/*.cxx )
file( GLOB HDRS ./src/*.hxx )
file( GLOB CHILD_SRCS ./child/*.cxx )
file( GLOB CHILD_HDRS ./child/*.hxx )
file( GLOB TUT ./TUT/*.hpp )
add_executable( ${PROJECT_NAME} ${SRCS} ${HDRS} "${YAAL_SOURCE_PATH}/_aux/cmake/client-config.hxx" )
add_executable( child ${CHILD_SRCS} ${CHILD_HDRS} )
add_library( tressplugin MODULE data/plugin.cxx )
add_library( huginn_greeter MODULE data/huginn_greeter.cxx )
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
set_target_properties( huginn_greeter PROPERTIES LINKER_LANGUAGE CXX )

target_link_libraries( huginn_greeter ${Yaal_LIBRARIES} )
if ( CMAKE_HOST_WIN32 )
	set_property( DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT tress )
	set_target_properties(
		tress PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${CMAKE_INSTALL_PREFIX}/bin\nYAAL_AUTO_SANITY=1"
		VS_DEBUGGER_COMMAND_ARGUMENTS "-E"
	)
	add_executable( child-simple ${CMAKE_HOME_DIRECTORY}/data/child.cxx )
	set_target_properties( child-simple PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME child RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/data )
	set_target_properties( tressplugin PROPERTIES OUTPUT_NAME tressplugin${LIB_INFIX} LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/data )
	set_target_properties( huginn_greeter PROPERTIES OUTPUT_NAME huginn_greeter${LIB_INFIX} LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/data )
	set_target_properties( child PROPERTIES COMPILE_DEFINITIONS "_SIGNAL_H=1" )
	set_source_files_properties( ${CHILD_SRCS} PROPERTIES COMPILE_FLAGS "/FI${YAAL_SOURCE_PATH}/_aux/msvcxx/csignal /FIyaal/fix.hxx" )
	target_link_libraries( ${PROJECT_NAME} ${Yaal_LIBRARIES} libintl )
	target_link_libraries( child ${Yaal_LIBRARIES} libintl )

	file( GLOB makedef_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/makedef.vc*proj" )
	include_external_msproject( makedef ${makedef_PROJ} )

	file( GLOB msvcxx_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/msvcxx.vc*proj" )
	include_external_msproject( msvcxx ${msvcxx_PROJ} )

	file( GLOB hcore_static_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hcore-static.vc*proj" )
	include_external_msproject( hcore-static ${hcore_static_PROJ} msvcxx )
	file( GLOB hcore_def_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hcore-def.vc*proj" )
	include_external_msproject( hcore-def ${hcore_def_PROJ} makedef )
	file( GLOB hcore_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hcore.vc*proj" )
	include_external_msproject( hcore ${hcore_PROJ} hcore-def  )

	file( GLOB tools_static_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/tools-static.vc*proj" )
	include_external_msproject( tools-static ${tools_static_PROJ} )
	file( GLOB tools_def_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/tools-def.vc*proj" )
	include_external_msproject( tools-def ${tools_def_PROJ} hcore )
	file( GLOB tools_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/tools.vc*proj" )
	include_external_msproject( tools ${tools_PROJ} )

	file( GLOB dbwrapper_static_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/dbwrapper-static.vc*proj" )
	include_external_msproject( dbwrapper-static ${dbwrapper_static_PROJ} )
	file( GLOB dbwrapper_def_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/dbwrapper-def.vc*proj" )
	include_external_msproject( dbwrapper-def ${dbwrapper_def_PROJ} tools )
	file( GLOB dbwrapper_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/dbwrapper.vc*proj" )
	include_external_msproject( dbwrapper ${dbwrapper_PROJ} )

	file( GLOB hconsole_static_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hconsole-static.vc*proj" )
	include_external_msproject( hconsole-static ${hconsole_static_PROJ} )
	file( GLOB hconsole_def_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hconsole-def.vc*proj" )
	include_external_msproject( hconsole-def ${hconsole_def_PROJ} dbwrapper tools )
	file( GLOB hconsole_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hconsole.vc*proj" )
	include_external_msproject( hconsole ${hconsole_PROJ} )

	file( GLOB hdata_static_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hdata-static.vc*proj" )
	include_external_msproject( hdata-static ${hdata_static_PROJ} )
	file( GLOB hdata_def_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hdata-def.vc*proj" )
	include_external_msproject( hdata-def ${hdata_def_PROJ} hconsole )
	file( GLOB hdata_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/hdata.vc*proj" )
	include_external_msproject( hdata ${hdata_PROJ} )

	file( GLOB sqlite3_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/sqlite3.vc*proj" )
	include_external_msproject( sqlite3 ${sqlite3_PROJ} )

	file( GLOB headers_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/headers.vc*proj" )
	include_external_msproject( headers ${headers_PROJ} )

	file( GLOB mkheaders_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/mkheaders.vc*proj" )
	include_external_msproject( mkheaders ${mkheaders_PROJ} )

	file( GLOB update_commit_id_PROJ "${YAAL_SOURCE_PATH}/build/${CMAKE_BUILD_TYPE}/update-commit-id.vc*proj" )
	include_external_msproject( update-commit-id ${update_commit_id_PROJ} )

	file( RELATIVE_PATH TARGET_PATH_RELATIVE ${CMAKE_HOME_DIRECTORY} ${TARGET_PATH} )
	set( INSTALLED_HEADER "${CMAKE_INSTALL_PREFIX}/include/yaal/yaal.hxx" )
	set( YAAL_TARGET_PATH "${YAAL_SOURCE_PATH}/${TARGET_PATH_RELATIVE}" )
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
	add_dependencies( huginn_greeter install_yaal )
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
	set_target_properties(
		huginn_greeter PROPERTIES
		OUTPUT_NAME 1exec
		PREFIX ""
		SUFFIX ""
		LIBRARY_OUTPUT_DIRECTORY ${TARGET_PATH}/huginn_greeter
		LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_PATH}/huginn_greeter
		LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_PATH}/huginn_greeter
		LIBRARY_OUTPUT_DIRECTORY_COV ${TARGET_PATH}/huginn_greeter
		LIBRARY_OUTPUT_DIRECTORY_PROF ${TARGET_PATH}/huginn_greeter
	)
	add_dependencies( ${PROJECT_NAME} commit_id )
	target_link_libraries( ${PROJECT_NAME} ${Yaal_LIBRARIES} ${Boost_LIBRARIES} dl )
	target_link_libraries( child ${Yaal_LIBRARIES} )
endif()

