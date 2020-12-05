/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>

#include <TUT/tut.hpp>

#include <yaal/tools/http.hxx>
#include <yaal/tools/hjson.hxx>
#include <yaal/hcore/hcore.hxx>
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
	http::HResponse response( http::call( http::HRequest( http::HTTP::GET, substitute_environment( "http://${TRESS_HTTP_TEST_HOST:-codestation.org}/test/logo.png" ) ) ) );
	HChunk rempte( response.content_length() );
	ENSURE_EQUALS( "content_length failed", response.stream().read( rempte.raw(), response.content_length() ), response.content_length() );
	HFile img( "./data/http/logo.png", HFile::OPEN::READING );
	int const BUF_SIZE( 32000 );
	HChunk local( BUF_SIZE );
	ENSURE_EQUALS( "content_length failed", img.read( local.raw(), BUF_SIZE ), response.content_length() );
	ENSURE_EQUALS( "http::call failed", memcmp( rempte.raw(), local.raw(), static_cast<size_t>( response.content_length() ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "basic authentication" )
	ENSURE_THROW(
		"invalid environment for basic auth test",
		http::call( http::HRequest( http::HTTP::GET, substitute_environment( "http://${TRESS_HTTP_TEST_HOST:-codestation.org}/test/private/secret.txt" ) ) ),
		http::HHTTPException
	);
	http::HResponse response(
		http::call(
			http::HRequest( http::HTTP::GET, substitute_environment( "http://${TRESS_HTTP_TEST_HOST:-codestation.org}/test/private/secret.txt" ) )
				.login( "test" )
				.password( "t3st" )
		)
	);
	HString content;
	HString line;
	while ( getline( response.stream(), line ).good() ) {
		content.append( line );
	}
	ENSURE_EQUALS( "basic authentication failed", content, "Secret Data" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "transfer-encoding: chunked" )
	http::HResponse response( http::call( http::HRequest( http::HTTP::GET, substitute_environment( "http://${TRESS_HTTP_TEST_HOST:-codestation.org}/test/cgi/cgi" ) ) ) );
	HChunk rempte( response.content_length() );
	HString content;
	HString line;
	int ignore( 2 );
	while ( getline( response.stream(), line ).good() ) {
		if ( ignore == 0 ) {
			content.append( line );
		} else {
			-- ignore;
		}
	}
	HFile src( "./data/http/cgi.cxx", HFile::OPEN::READING );
	HString code;
	while ( getline( src, line ).good() ) {
		code.append( line );
	}
	ENSURE_EQUALS( "http::call failed", content, code );
TUT_TEARDOWN()

TUT_UNIT_TEST( "post" )
	char const testData[] = "yaal-post\r\ntest-data\r\n0\r\n-working";
	HStringStream ss( testData );
	http::HRequest request( http::HTTP::POST, substitute_environment( "http://httpbin.org/post" ), &ss );
	http::HResponse response( http::call( request ) );
	HJSON json;
	json.load( response.stream() );
	ENSURE_EQUALS( "post failed", json.element()["data"].get_string(), testData );
TUT_TEARDOWN()

}

