/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hutf8string.cxx - this file is integral part of `tress' project.

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

#include <cstring>

#include <TUT/tut.hpp>
#include <yaal/hcore/unicode.hxx>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hutf8string );
TUT_TEST_GROUP( tut_yaal_hcore_hutf8string, "yaal::hcore::HUTF8String" );

TUT_UNIT_TEST( "default (trivial) ctor" )
	HUTF8String s;
	ENSURE( "non-empty empty", s.is_empty() && s.empty() );
	ENSURE_EQUALS( "bad byte count", s.byte_count(), 0 );
	ENSURE_EQUALS( "bad character count", s.character_count(), 0 );
	ENSURE_EQUALS( "bad x_str", strcmp( s.x_str(), "" ), 0 );
	ENSURE_EQUALS( "bad rank", s.rank(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "pure ascii data" )
	HUTF8String s( "HUTF8String" );
	ENSURE_NOT( "non-empty empty", s.is_empty() || s.empty() );
	ENSURE_EQUALS( "bad byte count", s.byte_count(), 11 );
	ENSURE_EQUALS( "bad character count", s.character_count(), 11 );
	ENSURE_EQUALS( "bad x_str", s.x_str(), "HUTF8String"_ys );
	ENSURE_EQUALS( "bad rank", s.rank(), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ctor from HString" )
	char d[] = "Ala ma kota";
	HString s( d );
	HUTF8String u( s );
	ENSURE_EQUALS( "bad HString ctor", ::strncmp(	u.x_str(), d, sizeof ( d ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ctor from iterators" )
	char const data[] = "Mężny bądź, chroń pułk twój i sześć flag!";
	HUTF8String s( data );
	HUTF8String::const_iterator beg( s.begin() );
	HUTF8String::const_iterator end( s.end() );
	HUTF8String sub( beg + 12, end - 14 );
	ENSURE_EQUALS( "bad iter ctor", sub, HUTF8String( "chroń pułk twój" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "utf8 data" )
	char const data[] = "Mężny bądź, chroń pułk twój i sześć flag!";
	HUTF8String s( data );
	ENSURE_NOT( "non-empty empty", s.is_empty() || s.empty() );
	ENSURE_EQUALS( "bad byte count", s.byte_count(), 50 );
	ENSURE_EQUALS( "bad character count", s.character_count(), 41 );
	ENSURE_EQUALS( "bad x_str", s.x_str(), to_string( data ) );
	ENSURE_EQUALS( "bad rank", s.rank(), 2 );
	ENSURE_EQUALS( "bad raw", s.raw(), to_string( data ) );
	ENSURE_THROW( "bad utf-8 accepted (head)", HUTF8String( "\xff" ), HUTF8StringException );
	ENSURE_THROW( "bad utf-8 accepted (tail)", HUTF8String( "�a" ), HUTF8StringException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy ctor" )
	char const data[] = "Mężny bądź, chroń pułk twój i sześć flag!";
	HUTF8String s( data );
	ENSURE_NOT( "non-empty empty", s.is_empty() || s.empty() );
	ENSURE_EQUALS( "bad byte count", s.byte_count(), 50 );
	ENSURE_EQUALS( "bad character count", s.character_count(), 41 );
	ENSURE_EQUALS( "bad x_str", s.x_str(), to_string( data ) );
	/* scope */ {
		HUTF8String x( s );
		ENSURE_NOT( "non-empty empty", x.is_empty() || x.empty() );
		ENSURE_EQUALS( "bad byte count", x.byte_count(), 50 );
		ENSURE_EQUALS( "bad character count", x.character_count(), 41 );
		ENSURE_EQUALS( "bad x_str", x.x_str(), to_string( data ) );
	}
	ENSURE_NOT( "non-empty empty", s.is_empty() || s.empty() );
	ENSURE_EQUALS( "bad byte count", s.byte_count(), 50 );
	ENSURE_EQUALS( "bad character count", s.character_count(), 41 );
	ENSURE_EQUALS( "bad x_str", s.x_str(), to_string( data ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "move ctor" )
	char const data[] = "Mężny bądź, chroń pułk twój i sześć flag!";
	HUTF8String s( data );
	ENSURE_NOT( "non-empty empty", s.is_empty() || s.empty() );
	ENSURE_EQUALS( "bad byte count", s.byte_count(), 50 );
	ENSURE_EQUALS( "bad character count", s.character_count(), 41 );
	ENSURE_EQUALS( "bad x_str", s.x_str(), to_string( data ) );
	/* scope */ {
		HUTF8String x( yaal::move( s ) );
		ENSURE_NOT( "non-empty empty", x.is_empty() || x.empty() );
		ENSURE_EQUALS( "bad byte count", x.byte_count(), 50 );
		ENSURE_EQUALS( "bad character count", x.character_count(), 41 );
		ENSURE_EQUALS( "bad x_str", x.x_str(), to_string( data ) );
	}
	ENSURE( "non-empty empty", s.is_empty() && s.empty() );
	ENSURE_EQUALS( "bad byte count", s.byte_count(), 0 );
	ENSURE_EQUALS( "bad character count", s.character_count(), 0 );
	ENSURE_EQUALS( "bad x_str", strcmp( s.x_str(), "" ), 0  );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy assignment" )
	char const data[] = "Mężny bądź, chroń pułk twój i sześć flag!";
	HUTF8String x;
	/* scope */ {
		HUTF8String s( data );
		ENSURE_NOT( "non-empty empty", s.is_empty() || s.empty() );
		ENSURE_EQUALS( "bad byte count", s.byte_count(), 50 );
		ENSURE_EQUALS( "bad character count", s.character_count(), 41 );
		ENSURE_EQUALS( "bad x_str", s.x_str(), to_string( data ) );
		x = s;
		ENSURE_NOT( "non-empty empty", s.is_empty() || s.empty() );
		ENSURE_EQUALS( "bad byte count", s.byte_count(), 50 );
		ENSURE_EQUALS( "bad character count", s.character_count(), 41 );
		ENSURE_EQUALS( "bad x_str", s.x_str(), to_string( data ) );
	}
	ENSURE_NOT( "non-empty empty", x.is_empty() || x.empty() );
	ENSURE_EQUALS( "bad byte count", x.byte_count(), 50 );
	ENSURE_EQUALS( "bad character count", x.character_count(), 41 );
	ENSURE_EQUALS( "bad x_str", x.x_str(), to_string( data ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "move assignment" )
	char const data[] = "Mężny bądź, chroń pułk twój i sześć flag!";
	HUTF8String x;
	/* scope */ {
		HUTF8String s( data );
		ENSURE_NOT( "non-empty empty", s.is_empty() || s.empty() );
		ENSURE_EQUALS( "bad byte count", s.byte_count(), 50 );
		ENSURE_EQUALS( "bad character count", s.character_count(), 41 );
		ENSURE_EQUALS( "bad x_str", s.x_str(), to_string( data ) );
		x = yaal::move( s );
		ENSURE( "non-empty empty", s.is_empty() && s.empty() );
		ENSURE_EQUALS( "bad byte count", s.byte_count(), 0 );
		ENSURE_EQUALS( "bad character count", s.character_count(), 0 );
		ENSURE_EQUALS( "bad x_str", strcmp( s.x_str(), "" ), 0 );
	}
	ENSURE_NOT( "non-empty empty", x.is_empty() || x.empty() );
	ENSURE_EQUALS( "bad byte count", x.byte_count(), 50 );
	ENSURE_EQUALS( "bad character count", x.character_count(), 41 );
	ENSURE_EQUALS( "bad x_str", x.x_str(), to_string( data ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "eq ==, neq !=" )
	char const u[] = "Żółw";
	HUTF8String u1( u );
	HUTF8String u2( u );
	char const a[] = "Zolw";
	HUTF8String a1( a );
	HUTF8String a2( a );
	ENSURE( "== failed", u1 == u2 );
	ENSURE( "== failed", u1 == u );
	ENSURE( "== failed", u == u2 );

	ENSURE( "!= failed", u1 != a1 );
	ENSURE( "!= failed", u1 != a );
	ENSURE( "!= failed", u != a2 );

	ENSURE( "== failed", a1 == a2 );
	ENSURE( "== failed", a1 == a );
	ENSURE( "== failed", a == a2 );

	ENSURE( "!= failed", a1 != u1 );
	ENSURE( "!= failed", a1 != u );
	ENSURE( "!= failed", a != u2 );

	ENSURE_NOT( "== failed", a1 == HUTF8String() );
	ENSURE( "!= failed", a1 != HUTF8String() );
	ENSURE_NOT( "== failed", a == HUTF8String() );
	ENSURE( "!= failed", a != HUTF8String() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "iterator" )
	char const data[] = "Mężny bądź, chroń pułk twój i sześć flag!";
	HUTF8String s( data );
	int_array_t a( s.begin(), s.end() );
	ENSURE_EQUALS( "bad character count", a.get_size(), 41 );
	int_array_t r( s.rbegin(), s.rend() );
	reverse( r.begin(), r.end() );
	ENSURE_EQUALS( "iter/riter failed", r, a );
	char const c[] = "M�ny b�d�, chro� pu�k tw�j i sze�� flag!";
	int_array_t d( begin( c ), end( c ) - 1 );
	d[1]  = unicode::CODE_POINTS::LATIN_SMALL_LETTER_E_WITH_OGONEK;
	d[2]  = unicode::CODE_POINTS::LATIN_SMALL_LETTER_Z_WITH_DOT_ABOVE;
	d[7]  = unicode::CODE_POINTS::LATIN_SMALL_LETTER_A_WITH_OGONEK;
	d[9]  = unicode::CODE_POINTS::LATIN_SMALL_LETTER_Z_WITH_ACUTE;
	d[16] = unicode::CODE_POINTS::LATIN_SMALL_LETTER_N_WITH_ACUTE;
	d[20] = unicode::CODE_POINTS::LATIN_SMALL_LETTER_L_WITH_STROKE;
	d[25] = unicode::CODE_POINTS::LATIN_SMALL_LETTER_O_WITH_ACUTE;
	d[33] = unicode::CODE_POINTS::LATIN_SMALL_LETTER_S_WITH_ACUTE;
	d[34] = unicode::CODE_POINTS::LATIN_SMALL_LETTER_C_WITH_ACUTE;
	ENSURE_EQUALS( "decode failed", a, d );
	HUTF8String x( "aąࠀ𐀀" );
	HUTF8String::HIterator it;
	it = x.cbegin();
	int_array_t q( it, x.cend() );
	int_array_t v( x.crbegin(), x.crend() );
	reverse( v.begin(), v.end() );
	int_array_t u( { 0x61, 0x105, 0x800, 0x10000 } );
	ENSURE_EQUALS( "decode all range failed", q, u );
	ENSURE_EQUALS( "decode all range failed", v, u );
TUT_TEARDOWN()

TUT_UNIT_TEST( "substr" )
	char const data[] = "Mężny bądź, chroń pułk twój i sześć flag!";
	HUTF8String s( data );
	HUTF8String ss( s.substr( 6, 4 ) );
	char const res[] = "bądź";
	ENSURE_EQUALS( "decode failed", ss, res );
	s = "Ala i pies"_ys;
	ss = s.substr( 6 );
	ENSURE_EQUALS( "decode failed", ss, "pies" );
TUT_TEARDOWN()

}


