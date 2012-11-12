/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hplugin.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/hcore/hlog.hxx>
#include <yaal/tools/hplugin.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

#define RESOLE_MACRO_FOR_MAKE_C_STRING( x ) ( #x )
#define MAKE_C_STRING( x ) RESOLE_MACRO_FOR_MAKE_C_STRING( x )

#define SELF_SUMATOR self_sumator
extern "C"
M_EXPORT_SYMBOL int SELF_SUMATOR( int, int );
extern "C"
M_EXPORT_SYMBOL int SELF_SUMATOR( int a, int b ) {
	return ( a + b );
}

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hplugin );
TUT_TEST_GROUP( tut_yaal_tools_hplugin, "yaal::tools::HPlugin" );

typedef int ( * sumator_t )( int, int );
static char const* const TRESS_PLUGIN = "./data/"LIB_PREFIX"tressplugin"LIB_INFIX"."LIB_EXT;

TUT_UNIT_TEST( 1, "load external library and resolve symbol" )
	int const T1 = 7;
	int const T2 = 13;
	HPlugin p;
	p.load( TRESS_PLUGIN );
	ENSURE( "failed to load plugin", p.is_loaded() );
	sumator_t my_sum( NULL );
	p.resolve( "tut_yaal_tools_hplugin_sum", my_sum );
	ENSURE( "failed to resolve symbol", my_sum != NULL );
	ENSURE_EQUALS( "cound not utilize plugin", my_sum( T1, T2 ), T1 + T2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "resolve symbol from self" )
	int const T1 = 7;
	int const T2 = 13;
	HPlugin p;
	p.load( HString() );
	sumator_t my_sum;
	p.resolve( MAKE_C_STRING( SELF_SUMATOR ), my_sum );
	ENSURE_EQUALS( "cound not utilise self-contained symbols", my_sum( T1, T2 ), T1 + T2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "load non-existing plugin" )
	try {
		HPlugin p;
		p.load( "/non/existing/plugin" );
		FAIL( "non-existing plugin loaded" );
	} catch ( HPluginException const& e ) {
		hcore::log << "expected: " << e.what() << endl;
	} catch ( HException const& e ) {
		FAIL( std::string( "unexpected: " ) + e.what() );
	} catch ( ... ) {
		FAIL( "unexpected unknown exception!" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "resolve non-existing symbol" )
	bool loaded( false );
	try {
		HPlugin p;
		p.load( TRESS_PLUGIN );
		loaded = p.is_loaded();
		void (*sym)(void) = NULL;
		p.resolve( "non_existing_symbol", sym );
		FAIL( "non-existing plugin loaded" );
	} catch ( HPluginException const& e ) {
		ENSURE( "failed to load plugin", loaded );
		hcore::log << "expected: " << e.what() << endl;
	}
TUT_TEARDOWN()

}

