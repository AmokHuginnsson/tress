/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_base64.cxx - this file is integral part of `tress' project.

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

TUT_SIMPLE_MOCK( tut_yaal_tools_base64 );
TUT_TEST_GROUP_N( tut_yaal_tools_base64, "yaal::tools::base64" );

TUT_UNIT_TEST_N( 1, "original suite <0> (empty)" )
	static char const INPUT[] = "";
	static char const BASE64ENC[] = "";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "original suite <1>" )
	static char const INPUT[] = "a";
	static char const BASE64ENC[] = "YQ==";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "original suite <2>" )
	static char const INPUT[] = "abc";
	static char const BASE64ENC[] = "YWJj";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "original suite <3>" )
	static char const INPUT[] = "message digest";
	static char const BASE64ENC[] = "bWVzc2FnZSBkaWdlc3Q=";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "original suite <4>" )
	static char const INPUT[] = "abcdefghijklmnopqrstuvwxyz";
	static char const BASE64ENC[] = "YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXo=";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "original suite <5>" )
	static char const INPUT[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	static char const BASE64ENC[] = "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ejAxMjM0NTY3ODk=";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "original suite <6>" )
	static char const INPUT[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
	static char const BASE64ENC[] = "MTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNDU2Nzg5MDEyMzQ1Njc4OTA=";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "special A for o.s.<6>" )
	static char const INPUT[] = "1234567890123456789012345678901234567890123456789012345678901234";
	static char const BASE64ENC[] = "MTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNA==";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "special B for o.s.<6>" )
	static char const INPUT[] = "123456789012345678901234567890123456789012345678901234567890123";
	static char const BASE64ENC[] = "MTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIz";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "from string" )
	static char const INPUT[] = "Ala ma kota";
	static char const BASE64ENC[] = "QWxhIG1hIGtvdGE=";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "from string (small alternation)" )
	static char const INPUT[] = "Ala ma koty";
	static char const BASE64ENC[] = "QWxhIG1hIGtvdHk=";
	ensure_equals( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ensure_equals( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

}

