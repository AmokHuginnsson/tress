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

char const cases[][5] = {
"AA==", "AQ==", "Ag==", "Aw==", "BA==", "BQ==", "Bg==", "Bw==", "CA==", "CQ==",
"Cg==", "Cw==", "DA==", "DQ==", "Dg==", "Dw==", "EA==", "EQ==", "Eg==", "Ew==",
"FA==", "FQ==", "Fg==", "Fw==", "GA==", "GQ==", "Gg==", "Gw==", "HA==", "HQ==",
"Hg==", "Hw==", "IA==", "IQ==", "Ig==", "Iw==", "JA==", "JQ==", "Jg==", "Jw==",
"KA==", "KQ==", "Kg==", "Kw==", "LA==", "LQ==", "Lg==", "Lw==", "MA==", "MQ==",
"Mg==", "Mw==", "NA==", "NQ==", "Ng==", "Nw==", "OA==", "OQ==", "Og==", "Ow==",
"PA==", "PQ==", "Pg==", "Pw==", "QA==", "QQ==", "Qg==", "Qw==", "RA==", "RQ==",
"Rg==", "Rw==", "SA==", "SQ==", "Sg==", "Sw==", "TA==", "TQ==", "Tg==", "Tw==",
"UA==", "UQ==", "Ug==", "Uw==", "VA==", "VQ==", "Vg==", "Vw==", "WA==", "WQ==",
"Wg==", "Ww==", "XA==", "XQ==", "Xg==", "Xw==", "YA==", "YQ==", "Yg==", "Yw==",
"ZA==", "ZQ==", "Zg==", "Zw==", "aA==", "aQ==", "ag==", "aw==", "bA==", "bQ==",
"bg==", "bw==", "cA==", "cQ==", "cg==", "cw==", "dA==", "dQ==", "dg==", "dw==",
"eA==", "eQ==", "eg==", "ew==", "fA==", "fQ==", "fg==", "fw==", "gA==", "gQ==",
"gg==", "gw==", "hA==", "hQ==", "hg==", "hw==", "iA==", "iQ==", "ig==", "iw==",
"jA==", "jQ==", "jg==", "jw==", "kA==", "kQ==", "kg==", "kw==", "lA==", "lQ==",
"lg==", "lw==", "mA==", "mQ==", "mg==", "mw==", "nA==", "nQ==", "ng==", "nw==",
"oA==", "oQ==", "og==", "ow==", "pA==", "pQ==", "pg==", "pw==", "qA==", "qQ==",
"qg==", "qw==", "rA==", "rQ==", "rg==", "rw==", "sA==", "sQ==", "sg==", "sw==",
"tA==", "tQ==", "tg==", "tw==", "uA==", "uQ==", "ug==", "uw==", "vA==", "vQ==",
"vg==", "vw==", "wA==", "wQ==", "wg==", "ww==", "xA==", "xQ==", "xg==", "xw==",
"yA==", "yQ==", "yg==", "yw==", "zA==", "zQ==", "zg==", "zw==", "0A==", "0Q==",
"0g==", "0w==", "1A==", "1Q==", "1g==", "1w==", "2A==", "2Q==", "2g==", "2w==",
"3A==", "3Q==", "3g==", "3w==", "4A==", "4Q==", "4g==", "4w==", "5A==", "5Q==",
"5g==", "5w==", "6A==", "6Q==", "6g==", "6w==", "7A==", "7Q==", "7g==", "7w==",
"8A==", "8Q==", "8g==", "8w==", "9A==", "9Q==", "9g==", "9w==", "+A==", "+Q==",
"+g==", "+w==", "/A==", "/Q==", "/g==", "/w==", "AAA=", "AQE=", "AgI=", "AwM=",
"BAQ=", "BQU=", "BgY=", "Bwc=", "CAg=", "CQk=", "Cgo=", "Cws=", "DAw=", "DQ0=",
"Dg4=", "Dw8=", "EBA=", "ERE=", "EhI=", "ExM=", "FBQ=", "FRU=", "FhY=", "Fxc=",
"GBg=", "GRk=", "Gho=", "Gxs=", "HBw=", "HR0=", "Hh4=", "Hx8=", "ICA=", "ISE=",
"IiI=", "IyM=", "JCQ=", "JSU=", "JiY=", "Jyc=", "KCg=", "KSk=", "Kio=", "Kys=",
"LCw=", "LS0=", "Li4=", "Ly8=", "MDA=", "MTE=", "MjI=", "MzM=", "NDQ=", "NTU=",
"NjY=", "Nzc=", "ODg=", "OTk=", "Ojo=", "Ozs=", "PDw=", "PT0=", "Pj4=", "Pz8=",
"QEA=", "QUE=", "QkI=", "Q0M=", "REQ=", "RUU=", "RkY=", "R0c=", "SEg=", "SUk=",
"Sko=", "S0s=", "TEw=", "TU0=", "Tk4=", "T08=", "UFA=", "UVE=", "UlI=", "U1M=",
"VFQ=", "VVU=", "VlY=", "V1c=", "WFg=", "WVk=", "Wlo=", "W1s=", "XFw=", "XV0=",
"Xl4=", "X18=", "YGA=", "YWE=", "YmI=", "Y2M=", "ZGQ=", "ZWU=", "ZmY=", "Z2c=",
"aGg=", "aWk=", "amo=", "a2s=", "bGw=", "bW0=", "bm4=", "b28=", "cHA=", "cXE=",
"cnI=", "c3M=", "dHQ=", "dXU=", "dnY=", "d3c=", "eHg=", "eXk=", "eno=", "e3s=",
"fHw=", "fX0=", "fn4=", "f38=", "gIA=", "gYE=", "goI=", "g4M=", "hIQ=", "hYU=",
"hoY=", "h4c=", "iIg=", "iYk=", "ioo=", "i4s=", "jIw=", "jY0=", "jo4=", "j48=",
"kJA=", "kZE=", "kpI=", "k5M=", "lJQ=", "lZU=", "lpY=", "l5c=", "mJg=", "mZk=",
"mpo=", "m5s=", "nJw=", "nZ0=", "np4=", "n58=", "oKA=", "oaE=", "oqI=", "o6M=",
"pKQ=", "paU=", "pqY=", "p6c=", "qKg=", "qak=", "qqo=", "q6s=", "rKw=", "ra0=",
"rq4=", "r68=", "sLA=", "sbE=", "srI=", "s7M=", "tLQ=", "tbU=", "trY=", "t7c=",
"uLg=", "ubk=", "uro=", "u7s=", "vLw=", "vb0=", "vr4=", "v78=", "wMA=", "wcE=",
"wsI=", "w8M=", "xMQ=", "xcU=", "xsY=", "x8c=", "yMg=", "yck=", "yso=", "y8s=",
"zMw=", "zc0=", "zs4=", "z88=", "0NA=", "0dE=", "0tI=", "09M=", "1NQ=", "1dU=",
"1tY=", "19c=", "2Ng=", "2dk=", "2to=", "29s=", "3Nw=", "3d0=", "3t4=", "398=",
"4OA=", "4eE=", "4uI=", "4+M=", "5OQ=", "5eU=", "5uY=", "5+c=", "6Og=", "6ek=",
"6uo=", "6+s=", "7Ow=", "7e0=", "7u4=", "7+8=", "8PA=", "8fE=", "8vI=", "8/M=",
"9PQ=", "9fU=", "9vY=", "9/c=", "+Pg=", "+fk=", "+vo=", "+/s=", "/Pw=", "/f0=",
"/v4=", "//8=", "AAAA", "AQEB", "AgIC", "AwMD", "BAQE", "BQUF", "BgYG", "BwcH",
"CAgI", "CQkJ", "CgoK", "CwsL", "DAwM", "DQ0N", "Dg4O", "Dw8P", "EBAQ", "ERER",
"EhIS", "ExMT", "FBQU", "FRUV", "FhYW", "FxcX", "GBgY", "GRkZ", "Ghoa", "Gxsb",
"HBwc", "HR0d", "Hh4e", "Hx8f", "ICAg", "ISEh", "IiIi", "IyMj", "JCQk", "JSUl",
"JiYm", "Jycn", "KCgo", "KSkp", "Kioq", "Kysr", "LCws", "LS0t", "Li4u", "Ly8v",
"MDAw", "MTEx", "MjIy", "MzMz", "NDQ0", "NTU1", "NjY2", "Nzc3", "ODg4", "OTk5",
"Ojo6", "Ozs7", "PDw8", "PT09", "Pj4+", "Pz8/", "QEBA", "QUFB", "QkJC", "Q0ND",
"RERE", "RUVF", "RkZG", "R0dH", "SEhI", "SUlJ", "SkpK", "S0tL", "TExM", "TU1N",
"Tk5O", "T09P", "UFBQ", "UVFR", "UlJS", "U1NT", "VFRU", "VVVV", "VlZW", "V1dX",
"WFhY", "WVlZ", "Wlpa", "W1tb", "XFxc", "XV1d", "Xl5e", "X19f", "YGBg", "YWFh",
"YmJi", "Y2Nj", "ZGRk", "ZWVl", "ZmZm", "Z2dn", "aGho", "aWlp", "ampq", "a2tr",
"bGxs", "bW1t", "bm5u", "b29v", "cHBw", "cXFx", "cnJy", "c3Nz", "dHR0", "dXV1",
"dnZ2", "d3d3", "eHh4", "eXl5", "enp6", "e3t7", "fHx8", "fX19", "fn5+", "f39/",
"gICA", "gYGB", "goKC", "g4OD", "hISE", "hYWF", "hoaG", "h4eH", "iIiI", "iYmJ",
"ioqK", "i4uL", "jIyM", "jY2N", "jo6O", "j4+P", "kJCQ", "kZGR", "kpKS", "k5OT",
"lJSU", "lZWV", "lpaW", "l5eX", "mJiY", "mZmZ", "mpqa", "m5ub", "nJyc", "nZ2d",
"np6e", "n5+f", "oKCg", "oaGh", "oqKi", "o6Oj", "pKSk", "paWl", "pqam", "p6en",
"qKio", "qamp", "qqqq", "q6ur", "rKys", "ra2t", "rq6u", "r6+v", "sLCw", "sbGx",
"srKy", "s7Oz", "tLS0", "tbW1", "tra2", "t7e3", "uLi4", "ubm5", "urq6", "u7u7",
"vLy8", "vb29", "vr6+", "v7+/", "wMDA", "wcHB", "wsLC", "w8PD", "xMTE", "xcXF",
"xsbG", "x8fH", "yMjI", "ycnJ", "ysrK", "y8vL", "zMzM", "zc3N", "zs7O", "z8/P",
"0NDQ", "0dHR", "0tLS", "09PT", "1NTU", "1dXV", "1tbW", "19fX", "2NjY", "2dnZ",
"2tra", "29vb", "3Nzc", "3d3d", "3t7e", "39/f", "4ODg", "4eHh", "4uLi", "4+Pj",
"5OTk", "5eXl", "5ubm", "5+fn", "6Ojo", "6enp", "6urq", "6+vr", "7Ozs", "7e3t",
"7u7u", "7+/v", "8PDw", "8fHx", "8vLy", "8/Pz", "9PT0", "9fX1", "9vb2", "9/f3",
"+Pj4", "+fn5", "+vr6", "+/v7", "/Pz8", "/f39", "/v7+", "////" };

TUT_UNIT_TEST_N( 14, "000" )
	static int const MAX_TEST_LEN = 4;
	char input[ MAX_TEST_LEN ];
	HStringStream ss;
	for ( int len = 1; len < MAX_TEST_LEN; ++ len )
		{
		for ( int val = 0; val < 256; ++ val )
			{
			fill_n( input, MAX_TEST_LEN, val );
			HMemory m( input, len );
			base64::encode( m, ss, true );
			ENSURE_EQUALS( "bad encode", ss.string(), cases[ ( len - 1 ) * 256 + val ] );
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

