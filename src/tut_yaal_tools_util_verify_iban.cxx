/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_util_verify_iban.cxx - this file is integral part of `tress' project.

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

#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_tools_util_verify_iban );
TUT_TEST_GROUP( tut_yaal_tools_util_verify_iban, "yaal::tools::util::verify_IBAN" );

TUT_UNIT_TEST( 1, "verifing good IBANs" )
	ENSURE_EQUALS ( "failed to verify IBAN: PL 12 1470 0002 2201 0010 7060 0001",
			verify_IBAN ( "PL 12 1470 0002 2201 0010 7060 0001" ), false );
	ENSURE_EQUALS ( "failed to verify IBAN: PL 12 1140 2004 0000 3402 3659 1487",
			verify_IBAN ( "PL 12 1140 2004 0000 3402 3659 1487" ), false );
	ENSURE_EQUALS ( "failed to verify IBAN: PL 65 1060 0076 0000 3200 0005 7153",
			verify_IBAN ( "PL 65 1060 0076 0000 3200 0005 7153" ), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "verifing bad IBANs" )
	ENSURE_EQUALS ( "failed to verify IBAN: PL 76 1140 2004 0080 3602 3659 1498",
			verify_IBAN ( "PL 76 1140 2004 0080 3602 3659 1498" ), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "verifing ad-hoc IBANs" )
	if ( setup._verbose && ( setup._argc > 1 ) )
		{
		HString string( setup._argv[ 1 ] );
		int unknown = static_cast<int>( string.find( '?' ) );
		if ( unknown < 0 )
			FAIL( "No unknown characters." );
		for ( int i = 0; i < 10; ++ i )
			{
			string.set_at( unknown, static_cast<char>( i + '0' ) );
			cout << string << ": " << ( ! verify_IBAN( string ) ? "OK" : "WRONG" ) << endl;
			}
		}
TUT_TEARDOWN()

}

