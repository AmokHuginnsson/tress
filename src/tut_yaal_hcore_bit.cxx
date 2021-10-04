/* Read tress/LICENSE.md file for copyright and licensing information. */

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
	ENSURE_EQUALS( "bit count failed on pattern " M_STRINGIFY( pattern ), bit::count( static_cast<u64_t>( meta::obinary<pattern>::value ) ), cnt );

TUT_UNIT_TEST( "bit count" )
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

TUT_UNIT_TEST( "most_significant_lookup" )
	ENSURE_EQUALS( "most_significant_lookup failed on 0", bit::most_significant_lookup( 0 ), -1 );
	for ( int i( 0 ); i < 63; ++ i ) {
		ENSURE_EQUALS( "most_significant_lookup failed on value 2^" + to_string( i ), bit::most_significant_lookup( 1ull << i ), i );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "most_significant" )
	ENSURE_EQUALS( "most_significant failed on 0", bit::most_significant( 0 ), -1 );
	for ( int i( 0 ); i < 63; ++ i ) {
		ENSURE_EQUALS( "most_significant failed on value 2^" + to_string( i ), bit::most_significant( 1ull << i ), i );
	}
TUT_TEARDOWN()

}

