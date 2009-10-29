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
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;
using namespace tress;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_tools_base64 );
TUT_TEST_GROUP_N( tut_yaal_tools_base64, "yaal::tools::base64" );

TUT_UNIT_TEST_N( 14, "000" )
	static int const MAX_TEST_LEN = 4;
	char input[ MAX_TEST_LEN ];
	for ( int len = 0; len < MAX_TEST_LEN; ++ len )
		{
		for ( int val = 0; val < 256; ++ val )
			{
			fill_n( input, MAX_TEST_LEN, val );
			HMemory m( input, len );
			}
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 1, "original suite <0> (empty)" )
	static char const INPUT[] = "";
	static char const BASE64ENC[] = "";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "original suite <1>" )
	static char const INPUT[] = "a";
	static char const BASE64ENC[] = "YQ==";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "original suite <2>" )
	static char const INPUT[] = "abc";
	static char const BASE64ENC[] = "YWJj";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "original suite <3>" )
	static char const INPUT[] = "message digest";
	static char const BASE64ENC[] = "bWVzc2FnZSBkaWdlc3Q=";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "original suite <4>" )
	static char const INPUT[] = "abcdefghijklmnopqrstuvwxyz";
	static char const BASE64ENC[] = "YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXo=";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "original suite <5>" )
	static char const INPUT[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	static char const BASE64ENC[] = "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ejAxMjM0NTY3ODk=";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "original suite <6>" )
	static char const INPUT[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
	static char const BASE64ENC[] = "MTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNDU2Nzg5MDEyMzQ1Njc4OTA=";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "special A for o.s.<6>" )
	static char const INPUT[] = "1234567890123456789012345678901234567890123456789012345678901234";
	static char const BASE64ENC[] = "MTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNA==";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "special B for o.s.<6>" )
	static char const INPUT[] = "123456789012345678901234567890123456789012345678901234567890123";
	static char const BASE64ENC[] = "MTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIzNDU2Nzg5MDEyMzQ1Njc4OTAxMjM0NTY3ODkwMTIz";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "from string" )
	static char const INPUT[] = "Ala ma kota";
	static char const BASE64ENC[] = "QWxhIG1hIGtvdGE=";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "from string (small alternation)" )
	static char const INPUT[] = "Ala ma koty";
	static char const BASE64ENC[] = "QWxhIG1hIGtvdHk=";
	ENSURE_EQUALS( "bad encode", base64::encode( INPUT ), BASE64ENC );
	ENSURE_EQUALS( "bad decode", base64::decode( BASE64ENC ), INPUT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "from file" )
	static char const* const INPUT = ( setup.f_iArgc > 1 ) ? setup.f_ppcArgv[ 1 ] : "./data/karatsuba.bc";
	static char const BASE64ENC[] =
"eD1yZWFkKCk7Cnk9cmVhZCgpOwoKc2NhbGUgPSAwCgpkZWZpbmUgZGlnaXRfY291bnQoIG4gKSB7\n"
"CglrID0gMDsKCXdoaWxlICggbiA+IDAgKSB7CgkJayA9IGsgKyAxOwoJCW4gPSBuIC8gMTA7Cgl9\n"
"CglyZXR1cm4gKCBrICk7Cn0KCmRlZmluZSBtYXgoIGEsIGIgKSB7CglyID0gMDsKCWlmICggYSA+\n"
"IGIgKSB7CgkJciA9IGE7Cgl9IGVsc2UgewoJCXIgPSBiOwoJfQoJcmV0dXJuICggciApOwp9Cgp4\n"
"bCA9IGRpZ2l0X2NvdW50KCB4ICk7CnlsID0gZGlnaXRfY291bnQoIHkgKTsKCnByaW50ICI8PDwg\n"
"S2FyYXRzdWJhID4+PlxuIgoKcHJpbnQgImZpcnN0IGZhY3RvciAiLCB4LCAiIGhhcyAiLCB4bCwg\n"
"IiBkaWdpdHNcbiIKcHJpbnQgInNlY29uZCBmYWN0b3IgIiwgeSwgIiBoYXMgIiwgeWwsICIgZGln\n"
"aXRzXG4iCgppZiAoIHhsID4geWwgKSB7Cgl0ID0geDsKCXggPSB5OwoJeSA9IHQ7Cgl0ID0geGw7\n"
"Cgl4bCA9IHlsOwoJeWwgPSB0Owp9CgptbCA9IG1heCggeGwsIHlsICk7CgptID0gbWwgLyAyOwpp\n"
"ZiAoIG1sICUgMiApIHsKCW0gPSBtICsgMQp9Cgp4MSA9IHgvMTBebQp4MiA9IHglMTBebQp5MSA9\n"
"IHkvMTBebQp5MiA9IHklMTBebQoKI3ByaW50ICJ1cHBlciBwYXJ0IG9mIHggaXMgIiwgeDEsICIg\n"
"bG93ZXIgcGFydCBvZiB4IGlzICIsIHgyLCAiXG4iCiNwcmludCAidXBwZXIgcGFydCBvZiB5IGlz\n"
"ICIsIHkxLCAiIGxvd2VyIHBhcnQgb2YgeSBpcyAiLCB5MiwgIlxuIgoKcjJtID0geDEqeTEKciA9\n"
"IHgyKnkyCgpwcmludCAicjJtIGlzICIsIHIybSwgIlxuIgpwcmludCAiciBpcyAiLCByLCAiXG4i\n"
"CgpoeCA9IHgxICsgeDIKaHkgPSB5MSArIHkyCgpwcmludCAiaHggaXMgIiwgaHgsICJcbiIKcHJp\n"
"bnQgImh5IGlzICIsIGh5LCAiXG4iCgp6MSA9IGh4ICogaHkKCnoyID0gejEqMTBebStyCgpyZXMw\n"
"ID0gejIrcjJtKjEwXigyKm0pCgpyZXMxID0gcmVzMC1yMm0qMTBebQoKcmVzdWx0ID0gcmVzMS1y\n"
"KjEwXm0KCnByaW50ICJaIGlzICIsIHoxLCAiXG4iCnByaW50ICJaKjEwXm0rciBpcyAiLCB6Miwg\n"
"IlxuIgpwcmludCAiWioxMF5tK3IrcjJtKjEwXjJtIGlzICIsIHJlczAsICJcbiIKcHJpbnQgIloq\n"
"MTBebStyLXIybSoxMF5tIGlzICIsIHJlczEsICJcbiIKCnJlc3VsdAp4KnkgLSByZXN1bHQK\n";

	if ( setup.f_iArgc > 1 )
		{
		if ( HString( "-" ) == INPUT )
			base64::encode( cin, cout );
		else
			{
			HFile f( INPUT );
			base64::encode( f, cout );
			}
		cout << endl;
		}
	else
		{
		HFile f( INPUT );
		HStringStream ss;
		base64::encode( f, ss, true );
		ENSURE_EQUALS( "badly encoded", ss.string(), BASE64ENC );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "from file" )
	static char const* const OUTPUT = "./out/decoded.txt";
	static char const BASE64ENC[] =
"eD1yZWFkKCk7Cnk9cmVhZCgpOwoKc2NhbGUgPSAwCgpkZWZpbmUgZGlnaXRfY291bnQoIG4gKSB7\n"
"CglrID0gMDsKCXdoaWxlICggbiA+IDAgKSB7CgkJayA9IGsgKyAxOwoJCW4gPSBuIC8gMTA7Cgl9\n"
"CglyZXR1cm4gKCBrICk7Cn0KCmRlZmluZSBtYXgoIGEsIGIgKSB7CglyID0gMDsKCWlmICggYSA+\n"
"IGIgKSB7CgkJciA9IGE7Cgl9IGVsc2UgewoJCXIgPSBiOwoJfQoJcmV0dXJuICggciApOwp9Cgp4\n"
"bCA9IGRpZ2l0X2NvdW50KCB4ICk7CnlsID0gZGlnaXRfY291bnQoIHkgKTsKCnByaW50ICI8PDwg\n"
"S2FyYXRzdWJhID4+PlxuIgoKcHJpbnQgImZpcnN0IGZhY3RvciAiLCB4LCAiIGhhcyAiLCB4bCwg\n"
"IiBkaWdpdHNcbiIKcHJpbnQgInNlY29uZCBmYWN0b3IgIiwgeSwgIiBoYXMgIiwgeWwsICIgZGln\n"
"aXRzXG4iCgppZiAoIHhsID4geWwgKSB7Cgl0ID0geDsKCXggPSB5OwoJeSA9IHQ7Cgl0ID0geGw7\n"
"Cgl4bCA9IHlsOwoJeWwgPSB0Owp9CgptbCA9IG1heCggeGwsIHlsICk7CgptID0gbWwgLyAyOwpp\n"
"ZiAoIG1sICUgMiApIHsKCW0gPSBtICsgMQp9Cgp4MSA9IHgvMTBebQp4MiA9IHglMTBebQp5MSA9\n"
"IHkvMTBebQp5MiA9IHklMTBebQoKI3ByaW50ICJ1cHBlciBwYXJ0IG9mIHggaXMgIiwgeDEsICIg\n"
"bG93ZXIgcGFydCBvZiB4IGlzICIsIHgyLCAiXG4iCiNwcmludCAidXBwZXIgcGFydCBvZiB5IGlz\n"
"ICIsIHkxLCAiIGxvd2VyIHBhcnQgb2YgeSBpcyAiLCB5MiwgIlxuIgoKcjJtID0geDEqeTEKciA9\n"
"IHgyKnkyCgpwcmludCAicjJtIGlzICIsIHIybSwgIlxuIgpwcmludCAiciBpcyAiLCByLCAiXG4i\n"
"CgpoeCA9IHgxICsgeDIKaHkgPSB5MSArIHkyCgpwcmludCAiaHggaXMgIiwgaHgsICJcbiIKcHJp\n"
"bnQgImh5IGlzICIsIGh5LCAiXG4iCgp6MSA9IGh4ICogaHkKCnoyID0gejEqMTBebStyCgpyZXMw\n"
"ID0gejIrcjJtKjEwXigyKm0pCgpyZXMxID0gcmVzMC1yMm0qMTBebQoKcmVzdWx0ID0gcmVzMS1y\n"
"KjEwXm0KCnByaW50ICJaIGlzICIsIHoxLCAiXG4iCnByaW50ICJaKjEwXm0rciBpcyAiLCB6Miwg\n"
"IlxuIgpwcmludCAiWioxMF5tK3IrcjJtKjEwXjJtIGlzICIsIHJlczAsICJcbiIKcHJpbnQgIloq\n"
"MTBebStyLXIybSoxMF5tIGlzICIsIHJlczEsICJcbiIKCnJlc3VsdAp4KnkgLSByZXN1bHQK\n";

	if ( setup.f_iArgc > 1 )
		{
		if ( HString( "-" ) == setup.f_ppcArgv[ 1 ] )
			base64::decode( cin, cout );
		else
			{
			HFile f( setup.f_ppcArgv[ 1 ] );
			base64::decode( f, cout );
			}
		cout << endl;
		}
	else
		{
		HStringStream ss;
		ss << BASE64ENC;
		HFile o( OUTPUT, HFile::OPEN::WRITING );
		base64::decode( ss, o, true );
//		ENSURE_EQUALS( "badly encoded", ss.string(), BASE64ENC );
		}
TUT_TEARDOWN()

}

