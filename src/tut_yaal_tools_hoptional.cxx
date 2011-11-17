/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hoptional.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hoptional.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hoptional );
TUT_TEST_GROUP( tut_yaal_tools_hoptional, "yaal::tools::HOptional" );

TUT_UNIT_TEST( 1, "default constructor" )
	HOptional<int> opt;
	ENSURE_EQUALS( "bad initialization status", opt ? true : false, false );
	try {
		int i( *opt );
		FAIL( "dereferencing unititialized optional" );
		++ i;
	} catch ( HFailedAssertion const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "initialized optional" )
	HOptional<int> opt( 7 );
	ENSURE_EQUALS( "bad initialization status", opt ? true : false, true );
	ENSURE_EQUALS( "bad value stored/retrieved", *opt, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "copy constructor" )
	HOptional<HString> opt( "Ala" );
	HOptional<HString> str( opt );
	ENSURE_EQUALS( "bad value", *opt, "Ala" );
	ENSURE_EQUALS( "bad copy", *str, "Ala" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "const reference" )
	HString const ala( "ala" );
	HOptional<HString const&> opt( ala );
	ENSURE_EQUALS( "bad value", &*opt, &ala );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "swap on const reference" )
	HString const ala( "ala" );
	HString const kot( "kot" );
	HOptional<HString const&> optAla( ala );
	HOptional<HString const&> optKot( kot );
	ENSURE_EQUALS( "bad value", &*optAla, &ala );
	ENSURE_EQUALS( "bad value", &*optKot, &kot );
	swap( optAla, optKot );
	ENSURE_EQUALS( "bad value", &*optAla, &kot );
	ENSURE_EQUALS( "bad value", &*optKot, &ala );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "non-const reference to const reference" )
	HString ala( "ala" );
	HString const kot( "kot" );
	HOptional<HString&> optAla( ala );
	HOptional<HString const&> optKot( kot );
	optKot = optAla;
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "non-const to const" )
	HOptional<HString> const optAla( "ala" );
	HOptional<HString> optKot( "kot" );
	optKot = optAla;
TUT_TEARDOWN()

}

