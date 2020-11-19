/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/hcore/hcache.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

class HDataSource {
	typedef HArray<int> requested_keys_t;
	requested_keys_t _requestedKeys;
public:
	HDataSource( void )
		: _requestedKeys() {
	}
	HString generate( int const& key_ ) {
		_requestedKeys.push_back( key_ );
		return ( "["_ys.append( key_ ).append( "]" ) );
	}
	requested_keys_t const& requested_keys( void ) const {
		return ( _requestedKeys );
	}
};

typedef HCache<int, HString> cache_t;

TUT_SIMPLE_MOCK( tut_yaal_hcore_hcache );
TUT_TEST_GROUP( tut_yaal_hcore_hcache, "yaal::hcore::HCache" );

TUT_UNIT_TEST( "get new values" )
	HDataSource ds;
	cache_t cache( call( &HDataSource::generate, &ds, _1 ), 10 );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting new value failed", ds.requested_keys(), int_array_t{ 0, 2, 3, 5 } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get cached values" )
	HDataSource ds;
	cache_t cache( call( &HDataSource::generate, &ds, _1 ), 10 );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 7 ), "[7]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 11 ), "[11]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 7 ), "[7]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting cached value failed", cache.obtain( 11 ), "[11]" );
	ENSURE_EQUALS( "getting cached value failed", ds.requested_keys(), int_array_t{ 0, 2, 3, 5, 7, 11 } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "retire entries" )
	HDataSource ds;
	cache_t cache( call( &HDataSource::generate, &ds, _1 ), 4 );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 1 ), "[1]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 1 ), "[1]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 1 ), "[1]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 1 ), "[1]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 1 ), "[1]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 1 ), "[1]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 1 ), "[1]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 1 ), "[1]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 4 ), "[4]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting, new, value, failed", ds.requested_keys(), int_array_t{ 0, 1, 2, 3, 4, 0, 1, 2, 3, 5, 0, 1, 2, 3, 5, 0, 1, 2, 3, 5, 0, 1, 2, 3, 5 } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "clear" )
	HDataSource ds;
	cache_t cache( call( &HDataSource::generate, &ds, _1 ), 10 );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting new value failed", ds.requested_keys(), int_array_t{ 0, 2, 3, 5 } );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting new value failed", ds.requested_keys(), int_array_t{ 0, 2, 3, 5 } );
	cache.clear();
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 0 ), "[0]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 2 ), "[2]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 3 ), "[3]" );
	ENSURE_EQUALS( "getting new value failed", cache.obtain( 5 ), "[5]" );
	ENSURE_EQUALS( "getting new value failed", ds.requested_keys(), int_array_t{ 0, 2, 3, 5, 0, 2, 3, 5 } );
TUT_TEARDOWN()

}

