/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/numeric.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::meta;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_meta );
TUT_TEST_GROUP( tut_yaal_meta, "yaal::meta" );

TUT_UNIT_TEST( "is_signed" )
	ENSURE_EQUALS( "signedness detection false negative", is_signed<int>::value, true );
	ENSURE_EQUALS( "signedness detection false positive", is_signed<int unsigned>::value, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "max_signed" )
	ENSURE_EQUALS( "bad max signed value", max_signed<char signed>::value, 127 );
	ENSURE_EQUALS( "bad max signed value", max_signed<short>::value, 32767 );
	clog << "char = " << hex << static_cast<int>( max_signed<char signed>::value ) << endl;
	clog << "short = " << hex << max_signed<short>::value << endl;
	clog << "int = " << hex << max_signed<int>::value << endl;
	clog << "long = " << hex << max_signed<long>::value << endl;
	clog << dec;
TUT_TEARDOWN()

TUT_UNIT_TEST( "max" )
	ENSURE_EQUALS( "bad max", meta::max<4, 5, -1, 9, 0, 2>::value, 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "min" )
	ENSURE_EQUALS( "bad min", meta::min<4, 5, -1, 9, 0, 2>::value, -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "integer_cast<>" )
	clog << integer_cast<int, 4>::value << endl;
	clog << integer_cast<char signed, 127>::value << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "unsigned_integer_cast<>" )
	clog << unsigned_integer_cast<int unsigned, static_cast<int unsigned>( 4 )>::value << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "xor" )
	ENSURE_NOT( "xor failed", meta::logical_xor<false, false>::value );
	ENSURE( "xor failed", meta::logical_xor<false, true>::value );
	ENSURE( "xor failed", meta::logical_xor<true, false>::value );
	ENSURE_NOT( "xor failed", meta::logical_xor<true, true>::value );
TUT_TEARDOWN()

}

