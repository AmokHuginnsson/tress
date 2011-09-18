/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_lexical_cast.cxx - this file is integral part of `tress' project.

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
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_lexical_cast );
TUT_TEST_GROUP( tut_yaal_lexical_cast, "yaal::lexical_cast" );

TUT_UNIT_TEST( 1, "0" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "-0" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "-0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "0xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "-0xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "9xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "-9xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "9xOlab" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "-9xOlab" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "axOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	try {
		lexical_cast<int>( get_test_name().c_str() );
		FAIL( "lexical_cast to an int from a garbage succeeded" );
	} catch ( HLexicalCastException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "-axOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	try {
		lexical_cast<int>( get_test_name().c_str() );
		FAIL( "lexical_cast to an int from a garbage succeeded" );
	} catch ( HLexicalCastException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "0xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), 10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "-0xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), -10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "0x" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "-0x" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 17, "0x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), 267 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 18, "-0x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), -267 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 19, "x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), 267 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "-x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), -267 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 21, "xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	try {
		lexical_cast<int>( get_test_name().c_str() );
		FAIL( "lexical_cast to an int from a garbage succeeded" );
	} catch ( HLexicalCastException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "-xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	try {
		lexical_cast<int>( get_test_name().c_str() );
		FAIL( "lexical_cast to an int from a garbage succeeded" );
	} catch ( HLexicalCastException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 23, "xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), 10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "-xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), -10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 25, "0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 26, "-0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 27, "01Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 28, "-01Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 29, "07Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 30, "-07Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 31, "08Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 32, "-08Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 33, "078Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 34, "-078Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 35, "01" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 36, "-01" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 37, "0110b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), 6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 38, "-0110b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), -6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 39, "0110c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 72 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 40, "-0110c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -72 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 41, "1010c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 1010 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 42, "-1010c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -1010 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 43, "1010b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), 10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 44, "-1010b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), -10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 45, "string to bool" )
	ENSURE_EQUALS( "yes to bool failed", lexical_cast<bool>( static_cast<char const*>( "yes" ) ), true );
	ENSURE_EQUALS( "no to bool failed", lexical_cast<bool>( static_cast<char const*>( "no" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "true" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "false" ) ), false );
	try {
		lexical_cast<bool>( static_cast<char const*>( "invalid" ) );
		FAIL( "casting garbage to bool did not throw" );
	} catch ( HLexicalCastException const& e ) {
		// ok
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

}

