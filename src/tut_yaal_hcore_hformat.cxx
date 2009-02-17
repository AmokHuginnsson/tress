/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hformat.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hformat
	{
	static double long D_PI;
	static char const* const D_STR;
	};

double long tut_yaal_hcore_hformat::D_PI = 3.141592653589793;
char const* const tut_yaal_hcore_hformat::D_STR = "ala";


TUT_TEST_GROUP_N( tut_yaal_hcore_hformat, "yaal::hcore::HFormat" );

TUT_UNIT_TEST_N( 1, "empty format" )
	HFormat f;
	ensure_equals( "bad empty format output", f.string(), HString() );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "empty format and param" )
	HFormat f;
	try
		{
		int i = 0;
		f % i;
		fail( "parameter for empty format swallowed" );
		}
	catch ( HFormatException& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 22, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%Lf]" ) % D_PI ).string(), "[3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 23, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%.3Lf]" ) % D_PI ).string(), "[3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 24, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%.8Lf]" ) % D_PI ).string(), "[3.14159265]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 25, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%.20Lf]" ) % D_PI ).string(), "[3.14159265350000005412]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 26, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%15Lf]" ) % D_PI ).string(), "[       3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 27, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%+Lf]" ) % D_PI ).string(), "[+3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 28, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%+Lf]" ) % -D_PI ).string(), "[-3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 29, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%Lf]" ) % D_PI ).string(), "[3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 30, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%Lf]" ) % D_PI ).string(), "[3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 31, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%*Lf]" ) % 20 % D_PI ).string(), "[            3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 32, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%1$*2$Lf]" ) % D_PI % 20 ).string(), "[            3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 33, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$*1$Lf]" ) % 20 % D_PI ).string(), "[            3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 34, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%.*Lf]" ) % 3 % D_PI ).string(), "[3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 35, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%1$.*2$Lf]" ) % D_PI % 3 ).string(), "[3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 36, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$.*1$Lf]" ) % 3 % D_PI ).string(), "[3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 37, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%1$*2$.*3$Lf]" ) % D_PI % 8% 3 ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 38, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%1$*3$.*2$Lf]" ) % D_PI % 3% 8 ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 39, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$*3$.*1$Lf]" ) % 3 % D_PI % 8 ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 40, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$*1$.*3$Lf]" ) % 8 % D_PI % 3 ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 41, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%3$*2$.*1$Lf]" ) % 3 % 8 % D_PI ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 42, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%3$*1$.*2$Lf]" ) % 8 % 3 % D_PI ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 43, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$+*1$.*3$Lf]" ) % 8 % D_PI % 3 ).string(), "[  +3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 44, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$+-*1$.*3$Lf]" ) % 8 % D_PI % 3 ).string(), "[+3.142  ]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 45, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$-*1$.*3$s]" ) % 8 % D_STR % 2 ).string(), "[al      ]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 46, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$-*1$.*3$s]" ) % 8 % D_STR % 30 ).string(), "[ala     ]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 47, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$*1$.*3$s]" ) % 8 % D_STR % 2 ).string(), "[      al]" );
TUT_TEARDOWN()
TUT_UNIT_TEST_N( 48, "well-formed format tests" )
	ensure_equals( "bad format output", ( HFormat( "[%2$*1$.*3$s]" ) % 8 % D_STR % 30 ).string(), "[     ala]" );
TUT_TEARDOWN()

}

