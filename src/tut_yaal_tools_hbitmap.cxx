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
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator[]" )
	HBitmap bmp( 7 );
	HStringStream ss;
	ss << bmp;
	ENSURE_EQUALS( "bad constructor", ss.string(), "0000000" );
	bmp[1] = true;
	ss.reset();
	ss << bmp;
	ENSURE_EQUALS( "bad operator[] or HBit ref", ss.string(), "0100000" );
	bmp[5] = true;
	ss.reset();
	ss << bmp;
	ENSURE_EQUALS( "bad operator[] or HBit ref", ss.string(), "0100010" );
	bmp[0] = bmp[6] = bmp[1] && bmp[5];
	ss.reset();
	ss << bmp;
	ENSURE_EQUALS( "bad operator[] or HBit ref", ss.string(), "1100011" );
TUT_TEARDOWN()

}

