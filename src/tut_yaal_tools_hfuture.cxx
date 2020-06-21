/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "yaal/tools/hfuture.hxx"
#include "yaal/tools/sleep.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tool_hfuture : public simple_mock<tut_yaal_tool_hfuture> {
	int _data;
	tut_yaal_tool_hfuture( void )
		: _data( 0 )
		{}
	virtual ~tut_yaal_tool_hfuture( void ) {}
	int long long power_of_three( int power_ ) {
		int long long val( 1 );
		for ( int i = 0; i  < power_; ++ i ) {
			sleep_for( duration( 50, time::UNIT::MILLISECOND ) );
			val *= 3;
		}
		return ( val );
	}
	int& give_val( void ) {
		return ( _data );
	}
	int const& give_val_const( void ) {
		return ( _data );
	}
};

TUT_TEST_GROUP( tut_yaal_tool_hfuture, "yaal::tools::HFuture" );

TUT_UNIT_TEST( "slow operation" )
	HFuture<int long long> f( call( &tut_yaal_tool_hfuture::power_of_three, this, 7 ) );
	ENSURE_EQUALS( "slow operation (3 ^ 7) failed", f.get(), 2187 );
	ENSURE( "is_ready (3 ^ 7) failed", f.is_ready() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_ready" )
	HFuture<int long long> f( call( &tut_yaal_tool_hfuture::power_of_three, this, 7 ) );
	ENSURE_NOT( "is_ready (3 ^ 7) failed", f.is_ready() );
#if defined( __HOST_OS_TYPE_CYGWIN__ ) || defined( __HOST_OS_TYPE_WINDOWS__ )
	static int const delay( 2800 );
#else
	static int const delay( 700 );
#endif
	sleep_for( duration( delay, time::UNIT::MILLISECOND ) );
	ENSURE( "is_ready (3 ^ 7) failed", f.is_ready() );
	ENSURE_EQUALS( "slow operation (3 ^ 7) failed", f.get(), 2187 );
	ENSURE( "is_ready (3 ^ 7) failed", f.is_ready() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reference returned" )
	HFuture<int&> f( call( &tut_yaal_tool_hfuture::give_val, this ) );
	int& rval( f.get() );
	ENSURE_EQUALS( "returning reference failed", &rval, &_data );
TUT_TEARDOWN()

TUT_UNIT_TEST( "const reference returned" )
	HFuture<int const&> f( call( &tut_yaal_tool_hfuture::give_val_const, this ) );
	int const& rcVal( f.get() );
	ENSURE_EQUALS( "returning const reference failed", &rcVal, &_data );
TUT_TEARDOWN()

}

