/* Read tress/LICENSE.md file for copyright and licensing information. */

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
		if ( unknown < 0 ) {
			FAIL( "No unknown characters." );
		}
		for ( int i = 0; i < 10; ++ i ) {
			string.set_at( unknown, code_point_t( static_cast<code_point_t::value_type>( i + '0' ) ) );
			cout << string << ": " << ( ! verify_IBAN( string ) ? "OK" : "WRONG" ) << endl;
		}
	}
TUT_TEARDOWN()

}

