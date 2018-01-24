/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/resolver.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/hcore/htokenizer.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace tress::tut_helpers;

inline std::ostream& operator << ( std::ostream& stream, ip_t const& ip_ ) {
	stream << resolver::ip_to_string( ip_ );
	return ( stream );
}

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_resolver );
TUT_TEST_GROUP( tut_yaal_hcore_resolver, "yaal::hcore::resolver" );

TUT_UNIT_TEST( "ip_to_string" )
	ENSURE_EQUALS( "ip_to_string failure", resolver::ip_to_string( HIP( 127, 0, 0, 1 ) ), "127.0.0.1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_ip" )
	HIP ipA( 127, 0, 0, 1 );
	HIP ipB( 0, 0, 0, 0 );
	HIP ip( resolver::get_ip( "localhost" ) );
	ENSURE( "get_ip filed", ( ip == ipA ) || ( ip == ipB ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_ip on invalid" )
	ENSURE_THROW( "invalid resolved", resolver::get_ip( "nonexisting.invalid" ), HResolverException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_name" )
	HTokenizer t( hcore::system::get_host_name(), "." );
	std::vector<HString> expected(
		{ "localhost", "ip6-localhost", t[0] }
	);
	char const* HOSTNAME( getenv( "HOSTNAME" ) );
	if ( HOSTNAME ) {
		expected.push_back( HOSTNAME );
		t = HTokenizer( HOSTNAME, "." );
		expected.push_back( t[0] );
	}
	HString resolved( resolver::get_name( HIP( 127, 0, 0, 1 ) ) );
	ENSURE_IN( "get_name failure", resolved, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_name on invalid" )
	HString resolved( resolver::get_name( HIP( 192, 0, 2, 0 ) ) );
	ENSURE_EQUALS( "get_name failure", resolved, "192.0.2.0" );
TUT_TEARDOWN()

}

