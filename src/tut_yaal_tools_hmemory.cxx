/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hmemory.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hmemory.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hmemory {
	static int const SIZE = 256;
	char _buf[SIZE];
	tut_yaal_tools_hmemory( void );
	virtual ~tut_yaal_tools_hmemory( void ) {}
};

tut_yaal_tools_hmemory::tut_yaal_tools_hmemory( void ) : _buf() {
	fill_n( _buf, SIZE, 0 );
}

TUT_TEST_GROUP( tut_yaal_tools_hmemory, "yaal::tools::HMemory" );

TUT_UNIT_TEST( 1, "constructor" )
	try {
		HMemory m( NULL, 10 );
		FAIL( "construction of null block succeeded" );
	} catch ( HFailedAssertion const& ) {
		// ok
	}
	try {
		char b[10];
		HMemory m( b, 0 );
		FAIL( "zero length block construction succeeded" );
	} catch ( HFailedAssertion const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "simple write" )
	char const pattern[] = "Ala ma kota.";
	::memset( _buf, 0, SIZE );
	HMemory m( _buf, SIZE );
	m << pattern;
	ENSURE_EQUALS( "simple write failed", memcmp( _buf, pattern, sizeof ( pattern ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "stacked writes" )
	char const pattern[] = "Ala ma kota.";
	char const pattern_hi[] = "Ala ma";
	char const pattern_lo[] = " kota.";
	::memset( _buf, 0, SIZE );
	HMemory m( _buf, SIZE );
	m << pattern_hi << pattern_lo;
	ENSURE_EQUALS( "simple write failed", memcmp( _buf, pattern, sizeof ( pattern ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "read from empty" )
	HMemory m( _buf, SIZE, HMemory::INITIAL_STATE::INVALID );
	HString line;
	ENSURE_EQUALS( "read byte count from empty", m.read_until( line ), 0 );
TUT_TEARDOWN()

}

