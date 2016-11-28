/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hbitmap.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hbitmap.hxx>
#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace yaal {

namespace tools {

inline bool operator == ( HBitmap const& bmp_, HString const& pat_ ) {
	HStringStream ss;
	ss << bmp_;
	return ( ss.str() == pat_ );
}

inline std::ostream& operator << ( std::ostream& stream_, HBitmap const& bmp_ ) {
	HStringStream ss;
	ss << bmp_;
	stream_ << ss.string();
	return ( stream_ );
}

}

}

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hbitmap );
TUT_TEST_GROUP( tut_yaal_tools_hbitmap, "yaal::tools::HBitmap" );

TUT_UNIT_TEST( "simple use" )
	static char const BUFF[] = "ala ma kota";
	static int const BUFF_BIT_SIZE( ( static_cast<int>( sizeof ( BUFF ) ) - 1 ) * 8 );
	HBitmap bmp;
	bmp.copy( BUFF, BUFF_BIT_SIZE );
	HBitmap const x( bmp );
	cout << endl;
	yaal::copy( x.begin(), x.end(), stream_iterator( cout ) );
	yaal::fill_n( bmp.begin(), BUFF_BIT_SIZE / 2, true );
	HBitmap const y( bmp );
	cout << endl;
	yaal::copy( y.begin(), y.end(), stream_iterator( cout ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Default constructor" )
	HBitmap bmp;
	ENSURE_EQUALS( "size", bmp.get_size(), 0 );
	ENSURE_EQUALS( "raw", bmp.raw(), static_cast<void*>( NULL ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "constructor from size" )
	static int const SIZE = 7;
	HBitmap bmp( SIZE );
	ENSURE_EQUALS( "constructor from size size", bmp.get_size(), SIZE );
	ENSURE( "default constructor raw", bmp.raw() != static_cast<void*>( NULL ) );
	ENSURE( "default constructor ", bmp.raw() != static_cast<void*>( NULL ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set" )
	HBitmap bmp;
	ENSURE_THROW( "default constructor set", bmp.set( 0, true ), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get" )
	HBitmap bmp;
	ENSURE_THROW( "default constructor set", bmp.get( 0 ), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rotate_left" )
	HBitmap bmp;
	ENSURE_THROW( "default constructor set", bmp.rotate_left( 0, 0, 0 ), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rotate_right" )
	HBitmap bmp;
	ENSURE_THROW( "default constructor set", bmp.rotate_right( 0, 0, 0 ), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse iteration" )
	static char const BUFF[] = "ala ma kota";
	static int const BUFF_BIT_SIZE( ( static_cast<int>( sizeof ( BUFF ) ) - 1 ) * 8 );
	HBitmap bmp;
	bmp.copy( BUFF, BUFF_BIT_SIZE );
	HStringStream ss;
	ss << bmp;
	HString s( ss.string() );
	ss.reset();
	yaal::copy( bmp.rbegin(), bmp.rend(), stream_iterator( ss ) );
	reverse( s.begin(), s.end() );
	ENSURE_EQUALS( "bad reverse iterator", ss.string(), s );
	ss.reset();
	HBitmap const& cbmp( bmp );
	yaal::copy( cbmp.rbegin(), cbmp.rend(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bad reverse iterator", ss.string(), s );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator[]" )
	HBitmap bmp( 7 );
	ENSURE_EQUALS( "bad constructor", bmp, "0000000" );
	bmp[1] = true;
	ENSURE_EQUALS( "bad operator[] or HBit ref", bmp, "0100000" );
	bmp[5] = true;
	ENSURE_EQUALS( "bad operator[] or HBit ref", bmp, "0100010" );
	bmp[0] = bmp[6] = bmp[1] && bmp[5];
	ENSURE_EQUALS( "bad operator[] or HBit ref", bmp, "1100011" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "push_back, size" )
	HBitmap bmp;
	bmp.push_back( true );
	bmp.push_back( false );
	bmp.push_back( true );
	bmp.push_back( true );
	bmp.push_back( false );
	bmp.push_back( true );
	bmp.push_back( false );
	ENSURE_EQUALS( "bad size", bmp.size(), 7 );
	ENSURE_EQUALS( "bad data", bmp, "1011010" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "clear" )
	HBitmap bmp;
	bmp.copy( "abc", 22 );
	ENSURE_EQUALS( "bad size", bmp.size(), 22 );
	HBitmap empty;
	bmp = empty;
	ENSURE_EQUALS( "bad size", bmp.size(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "fill, reserve" )
	HBitmap bmp( 7 );
	ENSURE_EQUALS( "bad size", bmp.size(), 7 );
	ENSURE_EQUALS( "bad ctor", bmp, "0000000" );
	bmp.fill( true );
	ENSURE_EQUALS( "fill true failed", bmp, "1111111" );
	bmp.fill( false );
	ENSURE_EQUALS( "false true failed", bmp, "0000000" );
	bmp.fill( 0, 7, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "1111111" );
	bmp.fill( 1, 5, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "1000001" );
	bmp.fill( 2, 3, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "1011101" );
	bmp.fill( 3, 1, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "1010101" );

	bmp.reserve( 15 );
	ENSURE_EQUALS( "bad size", bmp.size(), 15 );

	bmp.fill( true );
	ENSURE_EQUALS( "fill true failed", bmp, "111111111111111" );
	bmp.fill( false );
	ENSURE_EQUALS( "fill false failed", bmp, "000000000000000" );
	bmp.fill( 0, 15, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "111111111111111" );
	bmp.fill( 1, 13, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "100000000000001" );
	bmp.fill( 2, 11, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "101111111111101" );
	bmp.fill( 3, 9, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "101000000000101" );
	bmp.fill( 4, 7, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "101011111110101" );
	bmp.fill( 5, 5, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "101010000010101" );
	bmp.fill( 6, 3, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "101010111010101" );
	bmp.fill( 7, 1, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "101010101010101" );

	bmp.reserve( 23 );
	ENSURE_EQUALS( "bad size", bmp.size(), 23 );

	bmp.fill( true );
	ENSURE_EQUALS( "fill true failed", bmp, "11111111111111111111111" );
	bmp.fill( false );
	ENSURE_EQUALS( "fill false failed", bmp, "00000000000000000000000" );
	bmp.fill( 0, 23, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "11111111111111111111111" );
	bmp.fill( 1, 21, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10000000000000000000001" );
	bmp.fill( 2, 19, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10111111111111111111101" );
	bmp.fill( 3, 17, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10100000000000000000101" );
	bmp.fill( 4, 15, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10101111111111111110101" );
	bmp.fill( 5, 13, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10101000000000000010101" );
	bmp.fill( 6, 11, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10101011111111111010101" );
	bmp.fill( 7, 9, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10101010000000001010101" );
	bmp.fill( 8, 7, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10101010111111101010101" );
	bmp.fill( 9, 5, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10101010100000101010101" );
	bmp.fill( 10, 3, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10101010101110101010101" );
	bmp.fill( 11, 1, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10101010101010101010101" );

	bmp.reserve( 32 );
	ENSURE_EQUALS( "bad size", bmp.size(), 32 );

	bmp.fill( true );
	ENSURE_EQUALS( "fill true failed", bmp, "11111111111111111111111111111111" );
	bmp.fill( false );
	ENSURE_EQUALS( "fill false failed", bmp, "00000000000000000000000000000000" );
	bmp.fill( 8, 16, true );
	ENSURE_EQUALS( "fill false failed", bmp, "00000000111111111111111100000000" );
	bmp.fill( true );
	bmp.fill( 8, 16, false );
	ENSURE_EQUALS( "fill false failed", bmp, "11111111000000000000000011111111" );
TUT_TEARDOWN()

}

