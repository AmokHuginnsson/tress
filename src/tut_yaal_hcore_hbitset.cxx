/* Read tress/LICENSE.md file for copyright and licensing information. */

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

namespace std {
template<int const SIZE>
inline std::ostream& operator << ( std::ostream& stream, HBitset<SIZE> const& bs_ ) {
	stream << bs_.to_string();
	return stream;
}
}

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hbitset );
TUT_TEST_GROUP( tut_yaal_hcore_hbitset, "yaal::hcore::HBitset" );

TUT_UNIT_TEST( "empty" )
	HBitset<3> bs;
	ENSURE_EQUALS( "bs not empty", bs.to_integer(), 0u );
TUT_TEARDOWN()

TUT_UNIT_TEST( "count" )
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

TUT_UNIT_TEST( "or" )
	HBitset<5> bs1;
	HBitset<5> bs2;
	bs1.set( 1 );
	bs2.set( 3 );
	ENSURE_EQUALS( "bs or failed", bs1 | bs2, HBitset<5>( obinary<01010>::value ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "op[]" )
	HBitset<5> bs1;
	HBitset<5> bs2;
	bs1[ 1 ] = true;
	bs2[ 3 ] = true;
	ENSURE_EQUALS( "bs or failed", bs1 | bs2, HBitset<5>( obinary<01010>::value ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "size" )
	HBitset<5> bs1;
	ENSURE_EQUALS( "size failed", bs1.size(), 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy constructor" )
	typedef HBitset<128> bs128_t;
	bs128_t bs1;
	bs1.set( 50 );
	bs1.set( 100 );
	bs128_t bs1copy( bs1 );
	ENSURE_EQUALS( "copy construction failed", bs1, bs1copy );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	typedef HBitset<128> bs128_t;
	bs128_t bs1;
	bs128_t bs2;
	bs1.set( 50 );
	bs1.set( 100 );
	bs2.set( 55 );
	bs2.set( 105 );
	ENSURE_NOT( "construction failed", bs1 == bs2 );
	bs128_t bs1copy( bs1 );
	bs128_t bs2copy( bs2 );
	ENSURE_EQUALS( "copy construction failed", bs1, bs1copy );
	ENSURE_EQUALS( "copy construction failed", bs2, bs2copy );
	bs1.swap( bs2 );
	ENSURE_EQUALS( "swap failed", bs1, bs2copy );
	ENSURE_EQUALS( "swap failed", bs2, bs1copy );
TUT_TEARDOWN()

}

