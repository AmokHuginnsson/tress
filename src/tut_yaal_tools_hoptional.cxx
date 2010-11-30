/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hoptional.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_tools_hoptional );
TUT_TEST_GROUP_N( tut_yaal_tools_hoptional, "yaal::tools::HOptional" );

TUT_UNIT_TEST_N( 1, "default constructor" )
	HOptional<int> opt;
	ENSURE_EQUALS( "bad initialization status", opt ? true : false, false );
	try
		{
		int i( *opt );
		FAIL( "dereferencing unititialized optional" );
		++ i;
		}
	catch ( HFailedAssertion const& )
		{
		/* ok */
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "initialized optional" )
	HOptional<int> opt( 7 );
	ENSURE_EQUALS( "bad initialization status", opt ? true : false, true );
	ENSURE_EQUALS( "bad value stored/retrieved", *opt, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "copy constructor" )
	HOptional<HString> opt( "Ala" );
	HOptional<HString> str( opt );
	ENSURE_EQUALS( "bad value", *opt, "Ala" );
	ENSURE_EQUALS( "bad copy", *str, "Ala" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "const reference" )
	HString const ala( "ala" );
	HOptional<HString const&> opt( ala );
	ENSURE_EQUALS( "bad value", &*opt, &ala );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "swap on const reference" )
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

TUT_UNIT_TEST_N( 6, "non-const reference to const reference" )
	HString ala( "ala" );
	HString const kot( "kot" );
	HOptional<HString&> optAla( ala );
	HOptional<HString const&> optKot( kot );
	optKot = optAla;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "non-const to const" )
	HOptional<HString> const optAla( "ala" );
	HOptional<HString> optKot( "kot" );
	optKot = optAla;
TUT_TEARDOWN()

}

