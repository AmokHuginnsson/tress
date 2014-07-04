/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hbitset.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hbitset.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/tools/streamtools.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::meta;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

template<int const SIZE>
inline std::ostream& operator << ( std::ostream& stream, HBitset<SIZE> const& bs_ ) {
	stream << bs_.to_string();
	return ( stream );
}


namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hbitset );
TUT_TEST_GROUP( tut_yaal_hcore_hbitset, "yaal::hcore::HBitset" );

TUT_UNIT_TEST( 1, "empty" )
	HBitset<3> bs;
	ENSURE_EQUALS( "bs not empty", bs.to_integer(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "count" )
	typedef HBitset<64> bs64;
	ENSURE_EQUALS( "count failed", bs64().count(), 0 );
	ENSURE_EQUALS( "count failed", bs64( 1 ).count(), 1 );
	ENSURE_EQUALS( "count failed", bs64( 2 ).count(), 1 );
	ENSURE_EQUALS( "count failed", bs64( 3 ).count(), 2 );
	ENSURE_EQUALS( "count failed", bs64( 4 ).count(), 1 );
	ENSURE_EQUALS( "count failed", bs64( 5 ).count(), 2 );
	ENSURE_EQUALS( "count failed", bs64( 6 ).count(), 2 );
	ENSURE_EQUALS( "count failed", bs64( 7 ).count(), 3 );
	ENSURE_EQUALS( "count failed", bs64( 8 ).count(), 1 );
	ENSURE_EQUALS( "count failed", bs64( obinary<0110110110>::value ).count(), 6 );
	ENSURE_EQUALS( "count failed", bs64( obinary<0101010101010>::value ).count(), 6 );
	ENSURE_EQUALS( "count failed", bs64( obinary<0110101101011010>::value ).count(), 9 );
	ENSURE_EQUALS( "count failed", bs64( obinary<01101011010101010>::value ).count(), 9 );
	ENSURE_EQUALS( "count failed", bs64( obinary<011010110101010010>::value ).count(), 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "or" )
	HBitset<5> bs1;
	HBitset<5> bs2;
	bs1.set( 1 );
	bs2.set( 3 );
	ENSURE_EQUALS( "bs or failed", bs1 | bs2, HBitset<5>( obinary<01010>::value ) );
TUT_TEARDOWN()

}

