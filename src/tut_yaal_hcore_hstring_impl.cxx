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

}

