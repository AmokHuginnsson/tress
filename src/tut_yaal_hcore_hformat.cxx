/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hformat.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hformat.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hformat : public simple_mock<tut_yaal_hcore_hformat> {
	typedef simple_mock<tut_yaal_hcore_hformat> base_type;
	static double long PI;
	static double long E;
	static char const* const STR;
	virtual ~tut_yaal_hcore_hformat( void )
		{}
};

double long tut_yaal_hcore_hformat::PI = 3.141592653589793;
double long tut_yaal_hcore_hformat::E = 2.718281828459045;
char const* const tut_yaal_hcore_hformat::STR = "ala";


TUT_TEST_GROUP( tut_yaal_hcore_hformat, "yaal::hcore::HFormat" );

TUT_UNIT_TEST( "empty format" )
	HFormat f;
	ENSURE_EQUALS( "bad empty format output", f.string(), HString() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "param given for an empty format" )
	HFormat f;
	int i = 0;
	ENSURE_THROW( "parameter for empty format swallowed", f % i, HFormatException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "no params for non empty format" )
	HFormat f( "%d" );
	ENSURE_THROW( "non empty format generated string based on zero args", f.string(), HFormatException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "bad order of params" )
	HFormat f( "[%1$*2$.*3$Lf]" );
	ENSURE_THROW( "incorrect arg type accepted", f % 8 % PI % 3, HFormatException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reuse of format" )
	HFormat f( "[%.15Lf]" );
	f % PI;
	ENSURE_EQUALS( "bad format output", f.string(), "[3.141592653589793]" );
	f % E;
	ENSURE_EQUALS( "bad format output", f.string(), "[2.718281828459045]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "format and streams interaction" )
	typedef HFormat format;
	cout << "PI: " << format( "[%2$*1$.*3$Lf]" ) % 30 % PI % 15 << endl;
	HStringStream ss;
	ss << format( "[%2$*1$.*3$Lf]" ) % 30 % PI % 15 << flush;
	ENSURE_EQUALS( "format feeded stream with garbage", ss.string(), "[             3.141592653589793]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "well-formed format tests [%Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%Lf]" ) % PI ).string(), "[3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%.3Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%.3Lf]" ) % PI ).string(), "[3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%.8Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%.8Lf]" ) % PI ).string(), "[3.14159265]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%.20Lf]" )
#ifdef __MSVCXX__
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%.20Lf]" ) % PI ).string(), "[3.14159265358979310000]" );
#else
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%.20Lf]" ) % PI ).string(), "[3.14159265358979311600]" );
#endif
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%15Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%15Lf]" ) % PI ).string(), "[       3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%+Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%+Lf]" ) % PI ).string(), "[+3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%+Lf] (-)" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%+Lf]" ) % -PI ).string(), "[-3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%Lf]" ) % PI ).string(), "[3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%Lf] (-)" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%Lf]" ) % -PI ).string(), "[-3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%*Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%*Lf]" ) % 20 % PI ).string(), "[            3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%1$*2$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%1$*2$Lf]" ) % PI % 20 ).string(), "[            3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$*1$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$*1$Lf]" ) % 20 % PI ).string(), "[            3.141593]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%.*Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%.*Lf]" ) % 3 % PI ).string(), "[3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%1$.*2$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%1$.*2$Lf]" ) % PI % 3 ).string(), "[3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$.*1$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$.*1$Lf]" ) % 3 % PI ).string(), "[3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%1$*2$.*3$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%1$*2$.*3$Lf]" ) % PI % 8 % 3 ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%1$*3$.*2$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%1$*3$.*2$Lf]" ) % PI % 3 % 8 ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$*3$.*1$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$*3$.*1$Lf]" ) % 3 % PI % 8 ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$*1$.*3$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$*1$.*3$Lf]" ) % 8 % PI % 3 ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%3$*2$.*1$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%3$*2$.*1$Lf]" ) % 3 % 8 % PI ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%3$*1$.*2$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%3$*1$.*2$Lf]" ) % 8 % 3 % PI ).string(), "[   3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$+*1$.*3$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$+*1$.*3$Lf]" ) % 8 % PI % 3 ).string(), "[  +3.142]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$+-*1$.*3$Lf]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$+-*1$.*3$Lf]" ) % 8 % PI % 3 ).string(), "[+3.142  ]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$-*1$.*3$s]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$-*1$.*3$s]" ) % 8 % STR % 2 ).string(), "[al      ]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$-*1$.*3$s]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$-*1$.*3$s]" ) % 8 % STR % 30 ).string(), "[ala     ]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$*1$.*3$s]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$*1$.*3$s]" ) % 8 % STR % 2 ).string(), "[      al]" );
TUT_TEARDOWN()
TUT_UNIT_TEST( "well-formed format tests [%2$*1$.*3$s]" )
	ENSURE_EQUALS( "bad format output", ( HFormat( "[%2$*1$.*3$s]" ) % 8 % STR % 30 ).string(), "[     ala]" );
TUT_TEARDOWN()

}

