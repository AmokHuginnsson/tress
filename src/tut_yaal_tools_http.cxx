/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>

#include <TUT/tut.hpp>

#include <yaal/tools/http.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_http );
TUT_TEST_GROUP( tut_yaal_tools_http, "yaal::tools::http" );

TUT_UNIT_TEST( "get binary file (with redirection)" )
	http::HResponse response( http::get( http::HRequest( "http://codestation.org/img/logo.png" ) ) );
	HChunk rempte( response.content_length() );
	ENSURE_EQUALS( "content_length failed", response.stream().read( rempte.raw(), response.content_length() ), response.content_length() );
	HFile img( "./data/logo.png", HFile::OPEN::READING );
	int const BUF_SIZE( 32000 );
	HChunk local( BUF_SIZE );
	ENSURE_EQUALS( "content_length failed", img.read( local.raw(), BUF_SIZE ), response.content_length() );
	ENSURE_EQUALS( "http::get failed", memcmp( rempte.raw(), local.raw(), static_cast<size_t>( response.content_length() ) ), 0 );
TUT_TEARDOWN()

}

