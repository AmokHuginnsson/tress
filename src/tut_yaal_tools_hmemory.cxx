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
	HMemory m( make_resource<HMemoryObserver>( _buf, SIZE + 0 ) );
	m << pattern;
	ENSURE_EQUALS( "simple write failed", memcmp( _buf, pattern, sizeof ( pattern ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stacked writes" )
	char const pattern[] = "Ala ma kota.";
	char const pattern_hi[] = "Ala ma";
	char const pattern_lo[] = " kota.";
	::memset( _buf, 0, SIZE );
	HMemory m( make_resource<HMemoryObserver>( _buf, SIZE + 0 ) );
	m << pattern_hi << pattern_lo;
	ENSURE_EQUALS( "simple write failed", memcmp( _buf, pattern, sizeof ( pattern ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read from empty" )
	HMemory m( make_resource<HMemoryObserver>( _buf, SIZE + 0 ), HMemory::INITIAL_STATE::INVALID );
	HString line;
	ENSURE_EQUALS( "read byte count from empty", m.read_until( line ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "equality operator" )
	static char buf1[] = "abcde";
	static char buf2[] = "abcdf";
	HMemory m1( make_resource<HMemoryObserver>( buf1, 4 ) );
	HMemory m2( make_resource<HMemoryObserver>( buf2, 4 ) );
	HMemory m3( make_resource<HMemoryObserver>( buf1, 5 ) );
	HMemory m4( make_resource<HMemoryObserver>( buf2, 5 ) );
	ENSURE( "equality failed on equal", m1 == m2 );
	ENSURE_NOT( "equality failed on equal", m1 == m3 );
	ENSURE_NOT( "equality failed on equal", m3 == m4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "cycle" )
	char buf[] = "abcdefghijk";
	int const dataSize( 4 );
	char data[dataSize + 1];
	::memset( data, 0, dataSize + 1 );
	HMemory m( make_resource<HMemoryObserver>( buf, static_cast<int>( sizeof ( buf ) - 1 ) ) );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "abcd"_ys );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "efgh"_ys );
	m.write( "012345", 6 );
	ENSURE_EQUALS( "write failed", buf, "012345ghijk"_ys );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "ijk0"_ys );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "1234"_ys );
	m.write( "678901", 6 );
	ENSURE_EQUALS( "write failed", buf, "11234567890"_ys );
TUT_TEARDOWN()

TUT_UNIT_TEST( "seek" )
	char buf[] = "abcdefghijk";
	int const dataSize( 4 );
	char data[dataSize + 1];
	::memset( data, 0, dataSize + 1 );
	HMemory m( make_resource<HMemoryObserver>( buf, static_cast<int>( sizeof ( buf ) - 1 ) ) );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "abcd"_ys );
	m.read( data, dataSize );
	ENSURE_EQUALS( "read failed", data, "efgh"_ys );
	m.seek( 0, HStreamInterface::SEEK::BEGIN );
	m.read( data, dataSize );
	ENSURE_EQUALS( "seek failed", data, "abcd"_ys );
	m.read( data, dataSize );
	ENSURE_EQUALS( "seek failed", data, "efgh"_ys );
	m.seek( -4, HStreamInterface::SEEK::CURRENT );
	m.read( data, dataSize );
	ENSURE_EQUALS( "seek failed", data, "efgh"_ys );
	m.seek( -4, HStreamInterface::SEEK::END );
	m.read( data, dataSize );
	ENSURE_EQUALS( "seek failed", data, "hijk"_ys );
	m.seek( 0, HStreamInterface::SEEK::BEGIN );
	ENSURE_THROW( "memory overwrite", m.write( "AB", 2 ), HMemoryException );
	m.read( data, 2 );
	m.write( "AB", 2 );
	m.seek( 2, HStreamInterface::SEEK::CURRENT );
	m.read( data, 4 );
	ENSURE_EQUALS( "seek failed", data, "efgh"_ys );
	ENSURE_THROW( "negative pos after seek", m.seek( -10, HStreamInterface::SEEK::CURRENT ), HMemoryException );
	ENSURE_THROW( "pos behind end", m.seek( 10, HStreamInterface::SEEK::CURRENT ), HMemoryException );
	ENSURE_EQUALS( "seek failed", buf, "ABcdefghijk"_ys );
TUT_TEARDOWN()

}

