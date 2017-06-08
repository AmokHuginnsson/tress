/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hstring_impl.cxx - this file is integral part of `tress' project.

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

#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wkeyword-macro"
#define private public
#define protected public
#pragma GCC diagnostic error "-Wkeyword-macro"
#pragma GCC diagnostic error "-Wpragmas"
#include <yaal/hcore/hstring.hxx>
#undef protected
#undef private

#include <TUT/tut.hpp>

#include <yaal/hcore/unicode.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

static yaal::u8_t const RANK_BIT_MASK =  meta::obinary<001100000>::value;

#undef EXT_GET_RANK
#define EXT_GET_RANK( base ) ( ( ( base._mem[ HString::ALLOC_FLAG_INDEX ] & RANK_BIT_MASK ) >> 5 ) + 1 )

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hstring_impl );
TUT_TEST_GROUP( tut_yaal_hcore_hstring_impl, "yaal::hcore::HString,impl" );

TUT_UNIT_TEST( "default ctor" )
	HString s;
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0 reserve on empty: S(0, 1) -> reserve(0, 1) = S(0, 1)" )
	HString s;
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 1 );
	s.reserve( 0, 1 );
	ENSURE_EQUALS( "bad rank from reserve", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad capacity from reserve", s.get_capacity(), HString::MAX_INPLACE_CAPACITY + 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0 reserve with rank 2 on empty: S(0, 1) -> reserve(0, 2) = S(0, 1)" )
	HString s;
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 1 );
	s.reserve( 0, 2 );
	ENSURE_EQUALS( "bad rank from reserve", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad capacity from reserve", s.get_capacity(), HString::MAX_INPLACE_CAPACITY + 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "non 0 reserve with rank 2 on empty: S(0, 1) -> reserve(1, 2) = S(1, 2)" )
	HString s;
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 1 );
	s.reserve( 1, 2 );
	ENSURE_EQUALS( "bad rank reserve", EXT_GET_RANK( s ), 2 );
	ENSURE_EQUALS( "bad capacity from reserve", s.get_capacity(), HString::MAX_INPLACE_CAPACITY + 0 );
	s.reserve( 1000, 2 );
	ENSURE_EQUALS( "bad rank reserve", EXT_GET_RANK( s ), 2 );
	ENSURE_EQUALS( "bad capacity from reserve", s.get_capacity(), 2048 );
	s.reserve( 1000, 4 );
	ENSURE_EQUALS( "bad rank reserve", EXT_GET_RANK( s ), 4 );
	ENSURE_EQUALS( "bad capacity from reserve", s.get_capacity(), 4096 );
TUT_TEARDOWN()

#ifndef __MSVCXX__
TUT_UNIT_TEST( "resize non 0 to 0 with rank 1 (valid): S(2, 1) -> resize(0, 1) = S(0, 1)" )
	HString s;
	s.push_back( 'a'_ycp );
	s.push_back( 'b'_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 1 );
	s.resize( 0, 1 ); /* resize is private */
	ENSURE_EQUALS( "bad rank resize", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad size from resize", s.get_length(), 0 );
	ENSURE( "bad empty state from resize", s.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "resize non-empty with rank 2 to 0: S(2, 2) -> resize(0, 1) = S(0, 1)" )
	HString s;
	s.push_back( 1000_ycp );
	s.push_back( 1001_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 2 );
	s.resize( 0, 1 );
	ENSURE_EQUALS( "bad rank resize", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad size from resize", s.get_length(), 0 );
	ENSURE( "bad empty state from resize", s.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "resize non-empty with rank 2 to 0: S(2, 2) -> resize(0, 2) = S(0, 1)" )
	HString s;
	s.push_back( 1000_ycp );
	s.push_back( 1001_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 2 );
	s.resize( 0, 2 );
	ENSURE_EQUALS( "bad rank resize", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad size from resize", s.get_length(), 0 );
	ENSURE( "bad empty state from resize", s.is_empty() );
TUT_TEARDOWN()
#endif /* #ifndef __MSVCXX__ */

TUT_UNIT_TEST( "data losing reranking: S(2, 2)[22] -> reserve(2, 1) = ex" )
	HString s;
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 1 );
	s.push_back( 1000_ycp );
	s.push_back( 1001_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 2 );
	ENSURE_THROW( "reserve lost data", s.reserve( 2, 1 ), HOutOfRangeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "data losing reranking: S(2, 2)[22] -> reserve(1, 1) = ex" )
	HString s;
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 1 );
	s.push_back( 1000_ycp );
	s.push_back( 1001_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 2 );
	ENSURE_THROW( "reserve lost data", s.reserve( 1, 1 ), HOutOfRangeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "down-ranking: S(2, 2)[12] -> reserve(1, 1) = S(2, 1)" )
	HString s;
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 1 );
	s.push_back( 'a'_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 1 );
	s.push_back( 1001_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 2 );
	s.pop_back(); // trimming
	s.reserve( 1, 1 );
	ENSURE_EQUALS( "bad rank from reserve", EXT_GET_RANK( s ), 1 );
#ifndef __MSVCXX__
	s.resize( 1, 1 );
	ENSURE_EQUALS( "bad rank from resize", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad size from resize", s.get_length(), 1 );
#endif /* #ifndef __MSVCXX__ */
	/* UCS-4 */
	s.push_back( unicode::CODE_POINT::GREEK_SMALL_LETTER_ALPHA );
	ENSURE_EQUALS( "bad rank from resize", EXT_GET_RANK( s ), 2 );
	s.push_back( unicode::CODE_POINT::EMOJI_PENGUIN );
	ENSURE_EQUALS( "bad rank from resize", EXT_GET_RANK( s ), 4 );
	ENSURE_THROW( "reserve lost data", s.reserve( 2, 2 ), HOutOfRangeException );
	s.pop_back(); // trimming
	s.reserve( 2, 2 );
	ENSURE_EQUALS( "bad rank from reserve", EXT_GET_RANK( s ), 2 );
#ifndef __MSVCXX__
	s.resize( 2, 2 );
	ENSURE_EQUALS( "bad rank from resize", EXT_GET_RANK( s ), 2 );
	ENSURE_EQUALS( "bad size from resize", s.get_length(), 2 );
#endif /* #ifndef __MSVCXX__ */
	s.pop_back(); // trimming
	s.push_back( unicode::CODE_POINT::EMOJI_PENGUIN );
	ENSURE_EQUALS( "bad rank from resize", EXT_GET_RANK( s ), 4 );
	ENSURE_THROW( "reserve lost data", s.reserve( 1, 1 ), HOutOfRangeException );
	s.pop_back(); // trimming
	s.reserve( 1, 1 );
	ENSURE_EQUALS( "bad rank from reserve", EXT_GET_RANK( s ), 1 );
#ifndef __MSVCXX__
	s.resize( 1, 1 );
	ENSURE_EQUALS( "bad rank from resize", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad size from resize", s.get_length(), 1 );
#endif /* #ifndef __MSVCXX__ */
TUT_TEARDOWN()

TUT_UNIT_TEST( "down-ranking: S(2, 2)[11] -> reserve(2, 1) = S(2, 1)" )
	HString s;
	s.reserve( 2, 2 );
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 2 );
	s.push_back( 'a'_ycp );
	s.push_back( 'b'_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 2 );
	s.reserve( 2, 1 );
	ENSURE_EQUALS( "bad rank from reserve", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad size from reserve", s.get_length(), 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "down-ranking: S(2, 2)[11] -> reserve(1, 1) = S(2, 1)" )
	HString s;
	s.reserve( 2, 2 );
	ENSURE_EQUALS( "bad rank from default ctor", EXT_GET_RANK( s ), 2 );
	s.push_back( 'a'_ycp );
	s.push_back( 'b'_ycp );
	ENSURE_EQUALS( "bad rank from push_back", EXT_GET_RANK( s ), 2 );
	s.reserve( 1, 1 );
	ENSURE_EQUALS( "bad rank from reserve", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad size from reserve", s.get_length(), 2 );
#ifndef __MSVCXX__
	s.resize( 1, 1 );
	ENSURE_EQUALS( "bad rank from resize", EXT_GET_RANK( s ), 1 );
	ENSURE_EQUALS( "bad size from resize", s.get_length(), 1 );
#endif /* #ifndef __MSVCXX__ */
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy_n_unpack" )
	HString ucs2( "equation: " );
	ucs2.push_back( unicode::CODE_POINT::GREEK_CAPITAL_LETTER_DELTA );
	ucs2.append( " = b^2 - 4*a*c" );
	HUTF8String utf8( ucs2 );
	HString fromUtf8( utf8 );
	ENSURE_EQUALS( "UCS-2 unpack failed", fromUtf8, ucs2 );
	HString ucs4( "catchphrase: " );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_STOP_SIGN );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_PERSON_WALKING );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_SNAKE );
	utf8 = ucs4;
	fromUtf8 = utf8;
	ENSURE_EQUALS( "UCS-4 unpack failed", fromUtf8, ucs4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_last_impl" )
	HString ucs2( "equation: " );
	ucs2.push_back( unicode::CODE_POINT::GREEK_CAPITAL_LETTER_DELTA );
	ucs2.append( " = b^2 - 4*a*c" );
	ENSURE_EQUALS( "UCS-2 find_last failed", ucs2.find_last( ' '_ycp ), 19 );
	ENSURE_EQUALS( "UCS-2 find_last(pos) failed", ucs2.find_last( ' '_ycp, 18 ), 17 );
	ENSURE_EQUALS( "UCS-2 find_last ?= npos failed", ucs2.find_last( ' '_ycp, 5 ), HString::npos + 0 );

	HString ucs4( "catchphrase: " );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_STOP_SIGN );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_PERSON_WALKING );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_SNAKE );
	ENSURE_EQUALS( "UCS-4 find_last failed", ucs4.find_last( 'a'_ycp ), 8 );
	ENSURE_EQUALS( "UCS-4 find_last(pos) failed", ucs4.find_last( 'a'_ycp, 7 ), 1 );
	ENSURE_EQUALS( "UCS-4 find_last ?= npos failed", ucs4.find_last( 'A'_ycp ), HString::npos + 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "adaptive::set" )
	HString s( "abcdefgh" );
	s.set_at( 0, unicode::CODE_POINT::GREEK_SMALL_LETTER_ALPHA );
	HString expect;
	expect.push_back( unicode::CODE_POINT::GREEK_SMALL_LETTER_ALPHA );
	expect.append( "bcdefgh" );
	ENSURE_EQUALS( "UCS-2 set failed", s, expect );
	s.set_at( 1, unicode::CODE_POINT::EMOJI_PENGUIN );
	expect.clear();
	expect.push_back( unicode::CODE_POINT::GREEK_SMALL_LETTER_ALPHA );
	expect.push_back( unicode::CODE_POINT::EMOJI_PENGUIN );
	expect.append( "cdefgh" );
	ENSURE_EQUALS( "UCS-4 set failed", s, expect );
TUT_TEARDOWN()

TUT_UNIT_TEST( "adapitve::copy" )
	HString ucs4( "catchphrase: " );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_STOP_SIGN );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_PERSON_WALKING );
	ucs4.push_back( unicode::CODE_POINT::EMOJI_SNAKE );
	ucs4.append( ", don't tread on me"_ys );
	HString catchphrase( "catchphrase: 123, don't tread on me" );
	catchphrase.set_at( 13, unicode::CODE_POINT::EMOJI_STOP_SIGN );
	catchphrase.set_at( 14, unicode::CODE_POINT::EMOJI_PERSON_WALKING );
	catchphrase.set_at( 15, unicode::CODE_POINT::EMOJI_SNAKE );
	ENSURE_EQUALS( "copy UCS-1 to UCS-4 failed", ucs4, catchphrase );
	HString ucs2( ", jeżozwierz" );
	ucs4.append( ucs2 );
	catchphrase = "catchphrase: 123, don't tread on me, jezozwierz";
	catchphrase.set_at( 13, unicode::CODE_POINT::EMOJI_STOP_SIGN );
	catchphrase.set_at( 14, unicode::CODE_POINT::EMOJI_PERSON_WALKING );
	catchphrase.set_at( 15, unicode::CODE_POINT::EMOJI_SNAKE );
	catchphrase.set_at( 39, unicode::CODE_POINT::LATIN_SMALL_LETTER_Z_WITH_DOT_ABOVE );
	ENSURE_EQUALS( "copy UCS-2 to UCS-4 failed", ucs4, catchphrase );
TUT_TEARDOWN()

TUT_UNIT_TEST( "adaptive::equal" )
	HString s11a( "abcdefgho" );
	HString s21a( "abcdefgho" );
	s21a.reserve( s21a.get_capacity(), 2 );
	HString s22a( "abcdefgho" );
	s22a.set_at( 8, unicode::CODE_POINT::GREEK_SMALL_LETTER_OMEGA );
	HString s41a( "abcdefgho" );
	s41a.reserve( s41a.get_capacity(), 4 );
	HString s42a( "abcdefgho" );
	s42a.reserve( s42a.get_capacity(), 4 );
	s42a.set_at( 8, unicode::CODE_POINT::GREEK_SMALL_LETTER_OMEGA );
	HString s44a( "abcdefgho" );
	s44a.set_at( 8, unicode::CODE_POINT::EMOJI_PENGUIN );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s11a ), 1 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s21a ), 2 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s22a ), 2 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s41a ), 4 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s42a ), 4 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s44a ), 4 );
	HString s11b( s11a );
	s11b.set_at( 8, 'O'_ycp );
	HString s21b( s21a );
	s21b.set_at( 8, 'O'_ycp );
	HString s22b( s22a );
	s22b.set_at( 8, unicode::CODE_POINT::GREEK_CAPITAL_LETTER_OMEGA );
	HString s41b( s41a );
	s41b.set_at( 8, 'O'_ycp );
	HString s42b( s42a );
	s42b.set_at( 8, unicode::CODE_POINT::GREEK_CAPITAL_LETTER_OMEGA );
	HString s44b( s44a );
	s44b.set_at( 8, unicode::CODE_POINT::EMOJI_SNAKE );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s11b ), 1 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s21b ), 2 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s22b ), 2 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s41b ), 4 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s42b ), 4 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s44b ), 4 );

	HString s11c( s11a );
	HString s21c( s21a );
	HString s22c( s22a );
	HString s41c( s41a );
	HString s42c( s42a );
	HString s44c( s44a );

	ENSURE( "eq 11 11 failed", s11a == s11c );
	ENSURE( "eq 21 21 failed", s21a == s21c );
	ENSURE( "eq 22 22 failed", s22a == s22c );
	ENSURE( "eq 41 41 failed", s41a == s41c );
	ENSURE( "eq 42 42 failed", s42a == s42c );
	ENSURE( "eq 44 44 failed", s44a == s44c );

	ENSURE_NOT( "eq 11 11 failed", s11a == s11b );
	ENSURE_NOT( "eq 21 21 failed", s21a == s21b );
	ENSURE_NOT( "eq 22 22 failed", s22a == s22b );
	ENSURE_NOT( "eq 41 41 failed", s41a == s41b );
	ENSURE_NOT( "eq 42 42 failed", s42a == s42b );
	ENSURE_NOT( "eq 44 44 failed", s44a == s44b );

	ENSURE( "eq 21 11 failed", s21a == s11c );
	ENSURE( "eq 11 21 failed", s11a == s21c );
	ENSURE( "eq 41 11 failed", s41a == s11c );
	ENSURE( "eq 11 41 failed", s11a == s41c );
	ENSURE( "eq 42 22 failed", s42a == s22c );
	ENSURE( "eq 22 42 failed", s22a == s42c );

	ENSURE_NOT( "eq 21 11 failed", s21a == s11b );
	ENSURE_NOT( "eq 11 21 failed", s11a == s21b );
	ENSURE_NOT( "eq 41 11 failed", s41a == s11b );
	ENSURE_NOT( "eq 11 41 failed", s11a == s41b );
	ENSURE_NOT( "eq 42 22 failed", s42a == s22b );
	ENSURE_NOT( "eq 22 42 failed", s22a == s42b );
TUT_TEARDOWN()

TUT_UNIT_TEST( "adaptive::less" )
	HString s11a( "abcdefgho" );
	HString s21a( "abcdefgho" );
	s21a.reserve( s21a.get_capacity(), 2 );
	HString s22a( "abcdefgho" );
	s22a.set_at( 8, unicode::CODE_POINT::GREEK_SMALL_LETTER_OMICRON );
	HString s41a( "abcdefgho" );
	s41a.reserve( s41a.get_capacity(), 4 );
	HString s42a( "abcdefgho" );
	s42a.reserve( s42a.get_capacity(), 4 );
	s42a.set_at( 8, unicode::CODE_POINT::GREEK_SMALL_LETTER_OMICRON );
	HString s44a( "abcdefgho" );
	s44a.set_at( 8, unicode::CODE_POINT::EMOJI_SNAKE );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s11a ), 1 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s21a ), 2 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s22a ), 2 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s41a ), 4 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s42a ), 4 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s44a ), 4 );
	HString s11b( s11a );
	s11b.set_at( 8, 'p'_ycp );
	HString s21b( s21a );
	s21b.set_at( 8, 'p'_ycp );
	HString s22b( s22a );
	s22b.set_at( 8, unicode::CODE_POINT::GREEK_SMALL_LETTER_OMEGA );
	HString s41b( s41a );
	s41b.set_at( 8, 'p'_ycp );
	HString s42b( s42a );
	s42b.set_at( 8, unicode::CODE_POINT::GREEK_SMALL_LETTER_OMEGA );
	HString s44b( s44a );
	s44b.set_at( 8, unicode::CODE_POINT::EMOJI_PENGUIN );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s11b ), 1 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s21b ), 2 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s22b ), 2 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s41b ), 4 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s42b ), 4 );
	ENSURE_EQUALS( "bad rank", EXT_GET_RANK( s44b ), 4 );

	HString s11c( s11a );
	HString s21c( s21a );
	HString s22c( s22a );
	HString s41c( s41a );
	HString s42c( s42a );
	HString s44c( s44a );

	ENSURE_NOT( "less 11 11 failed", s11a < s11c );
	ENSURE_NOT( "less 21 21 failed", s21a < s21c );
	ENSURE_NOT( "less 22 22 failed", s22a < s22c );
	ENSURE_NOT( "less 41 41 failed", s41a < s41c );
	ENSURE_NOT( "less 42 42 failed", s42a < s42c );
	ENSURE_NOT( "less 44 44 failed", s44a < s44c );

	ENSURE( "less 11 11 failed", s11a < s11b );
	ENSURE( "less 21 21 failed", s21a < s21b );
	ENSURE( "less 22 22 failed", s22a < s22b );
	ENSURE( "less 41 41 failed", s41a < s41b );
	ENSURE( "less 42 42 failed", s42a < s42b );
	ENSURE( "less 44 44 failed", s44a < s44b );

	ENSURE_NOT( "less 21 11 failed", s21a < s11c );
	ENSURE_NOT( "less 11 21 failed", s11a < s21c );
	ENSURE_NOT( "less 41 11 failed", s41a < s11c );
	ENSURE_NOT( "less 11 41 failed", s11a < s41c );
	ENSURE_NOT( "less 42 22 failed", s42a < s22c );
	ENSURE_NOT( "less 22 42 failed", s22a < s42c );

	ENSURE( "less 21 11 failed", s21a < s11b );
	ENSURE( "less 11 21 failed", s11a < s21b );
	ENSURE( "less 41 11 failed", s41a < s11b );
	ENSURE( "less 11 41 failed", s11a < s41b );
	ENSURE( "less 42 22 failed", s42a < s22b );
	ENSURE( "less 22 42 failed", s22a < s42b );
TUT_TEARDOWN()

}

