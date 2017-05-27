/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_money_verify_iban.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/money.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::money;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_money_verify_iban );
TUT_TEST_GROUP( tut_yaal_tools_money_verify_iban, "yaal::tools::money::verify_IBAN" );

TUT_UNIT_TEST( "verifing good IBANs" )
	ENSURE_EQUALS ( "failed to verify IBAN: PL 12 1470 0002 2201 0010 7060 0001",
			verify_IBAN ( "PL 12 1470 0002 2201 0010 7060 0001" ), true );
	ENSURE_EQUALS ( "failed to verify IBAN: PL 12 1140 2004 0000 3402 3659 1487",
			verify_IBAN ( "PL 12 1140 2004 0000 3402 3659 1487" ), true );
	ENSURE_EQUALS ( "failed to verify IBAN: PL 65 1060 0076 0000 3200 0005 7153",
			verify_IBAN ( "PL 65 1060 0076 0000 3200 0005 7153" ), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "verifing bad IBANs" )
	ENSURE_EQUALS ( "failed to verify IBAN: PL 76 1140 2004 0080 3602 3659 1498",
			verify_IBAN ( "PL 76 1140 2004 0080 3602 3659 1498" ), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "verifing ad-hoc IBANs" )
	if ( setup._verbose && ( setup._argc > 1 ) ) {
		HString string( setup._argv[ 1 ] );
		int unknown = static_cast<int>( string.find( '?'_ycp ) );
		if ( unknown < 0 )
			FAIL( "No unknown characters." );
		for ( int i = 0; i < 10; ++ i ) {
			string.set_at( unknown, code_point_t( static_cast<code_point_t::value_type>( i + '0' ) ) );
			cout << string << ": " << ( ! verify_IBAN( string ) ? "OK" : "WRONG" ) << endl;
		}
	}
TUT_TEARDOWN()

}

