/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>

#include <TUT/tut.hpp>

#include <yaal/tools/hmemory.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hmemory : public simple_mock<tut_yaal_tools_hmemory> {
	typedef simple_mock<tut_yaal_tools_hmemory> base_type;
	static int const SIZE = 256;
	char _buf[SIZE];
	tut_yaal_tools_hmemory( void );
	virtual ~tut_yaal_tools_hmemory( void ) {}
};

tut_yaal_tools_hmemory::tut_yaal_tools_hmemory( void )
	: base_type(), _buf() {
	fill_n( _buf, SIZE, 0 );
}

TUT_TEST_GROUP( tut_yaal_tools_hmemory, "yaal::tools::HMemory" );

TUT_UNIT_TEST( "constructor" )
	ENSURE_THROW( "construction of null block succeeded", HMemoryObserver m( NULL, 10 ), HFailedAssertion );
	char b[10];
	ENSURE_THROW( "zero length block construction succeeded", HMemoryObserver m( b, 0 ), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "simple write" )
	char const pattern[] = "Ala ma kota.";
	::memset( _buf, 0, SIZE );
	HMemoryObserver mo( _buf, SIZE );
	HMemory m( mo );
	m << pattern;
	ENSURE_EQUALS( "simple write failed", memcmp( _buf, pattern, sizeof ( pattern ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stacked writes" )
	char const pattern[] = "Ala ma kota.";
	char const pattern_hi[] = "Ala ma";
	char const pattern_lo[] = " kota.";
	::memset( _buf, 0, SIZE );
	HMemoryObserver mo( _buf, SIZE );
	HMemory m( mo );
	m << pattern_hi << pattern_lo;
	ENSURE_EQUALS( "simple write failed", memcmp( _buf, pattern, sizeof ( pattern ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read from empty" )
	HMemoryObserver mo( _buf, SIZE );
	HMemory m( mo, HMemory::INITIAL_STATE::INVALID );
	HString line;
	ENSURE_EQUALS( "read byte count from empty", m.read_until( line ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "equality operator" )
	static char buf1[] = "abcde";
	static char buf2[] = "abcdf";
	HMemoryObserver mo1( buf1, 4 );
	HMemoryObserver mo2( buf2, 4 );
	HMemoryObserver mo3( buf1, 5 );
	HMemoryObserver mo4( buf2, 5 );
	HMemory m1( mo1 );
	HMemory m2( mo2 );
	HMemory m3( mo3 );
	HMemory m4( mo4 );
	ENSURE( "equality failed on equal", m1 == m2 );
	ENSURE_NOT( "equality failed on equal", m1 == m3 );
	ENSURE_NOT( "equality failed on equal", m3 == m4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "cycle" )
	char buf[] = "abcdefghijk";
	int const dataSize( 4 );
	char data[dataSize + 1];
	::memset( data, 0, dataSize + 1 );
	HMemoryObserver mo( buf, static_cast<int>( sizeof ( buf ) - 1 ) );
	HMemory m( mo );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "abcd"_ys );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "efgh"_ys );
	m.write( "012345", 6 );
	ENSURE_EQUALS( "read failed", buf, "012345ghijk"_ys );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "ijk0"_ys );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "1234"_ys );
	m.write( "678901", 6 );
	ENSURE_EQUALS( "read failed", buf, "11234567890"_ys );
TUT_TEARDOWN()

}

