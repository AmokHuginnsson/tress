/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_bit.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/bit.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_bit );
TUT_TEST_GROUP( tut_yaal_hcore_bit, "yaal::hcore::bit" );

#define BIT_COUNT_TEST( pattern, cnt ) \
	ENSURE_EQUALS( "bit count failed on pattern " M_STRINGIFY( pattern ), bit::count( meta::obinary<pattern>::value ), cnt );

TUT_UNIT_TEST( 1, "bit count" )
	BIT_COUNT_TEST( 0, 0 );
	BIT_COUNT_TEST( 01, 1 );
	BIT_COUNT_TEST( 0101, 2 );
	BIT_COUNT_TEST( 0111, 3 );
	BIT_COUNT_TEST( 010101, 3 );
	BIT_COUNT_TEST( 011101, 4 );
	BIT_COUNT_TEST( 01010101, 4 );
	BIT_COUNT_TEST( 01110101, 5 );
	BIT_COUNT_TEST( 0101010101, 5 );
	BIT_COUNT_TEST( 0111011101, 7 );
	BIT_COUNT_TEST( 010101010101, 6 );
	BIT_COUNT_TEST( 011101010101, 7 );
	BIT_COUNT_TEST( 01010101010101, 7 );
	BIT_COUNT_TEST( 01110111010101, 9 );
	BIT_COUNT_TEST( 0101010101010101, 8 );
	BIT_COUNT_TEST( 0111010111010101, 10 );
	BIT_COUNT_TEST( 010101010101010101, 9 );
	BIT_COUNT_TEST( 011101011101110101, 12 );
TUT_TEARDOWN()

#undef BIT_COUNT_TEST

TUT_UNIT_TEST( 2, "least_significant" )
	ENSURE_EQUALS( "least_significant failed on 0", bit::least_significant( 0 ), -1 );
	for ( int i( 0 ); i < 63; ++ i ) {
		ENSURE_EQUALS( "least_significant failed on value 2^" + to_string( i ), bit::least_significant( 1ull << i ), i );
	}
TUT_TEARDOWN()

}

