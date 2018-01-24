/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hash.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::hash;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hash_hmac );
TUT_TEST_GROUP( tut_yaal_tools_hash_hmac, "yaal::tools::hash::hmac" );

TUT_UNIT_TEST( "hmac md5" )
	ENSURE_EQUALS( "empty failed", hmac( FUNCTION::MD5, "", "" ), "74e6f7298a9c2d168935f58c001bad88" );
	ENSURE_EQUALS( "empty failed", hmac( FUNCTION::MD5, "key", "The quick brown fox jumps over the lazy dog" ), "80070713463e7749b90c2dc24911e275" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "hmac sha1" )
	ENSURE_EQUALS( "empty failed", hmac( FUNCTION::SHA1, "", "" ), "fbdb1d1b18aa6c08324b7d64b71fb76370690e1d" );
	ENSURE_EQUALS( "empty failed", hmac( FUNCTION::SHA1, "key", "The quick brown fox jumps over the lazy dog" ), "de7c9b85b8b78aa6bc8a7a36f70a90701c9db4d9" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "hmac sha512" )
	ENSURE_EQUALS( "empty failed", hmac( FUNCTION::SHA512, "", "" ), "b936cee86c9f87aa5d3c6f2e84cb5a4239a5fe50480a6ec66b70ab5b1f4ac6730c6c515421b327ec1d69402e53dfb49ad7381eb067b338fd7b0cb22247225d47" );
	ENSURE_EQUALS( "empty failed", hmac( FUNCTION::SHA512, "key", "The quick brown fox jumps over the lazy dog" ), "b42af09057bac1e2d41708e48a902e09b5ff7f12ab428a4fe86653c73dd248fb82f948a549f7b791a5b41915ee4d1ec3935357e4e2317250d0372afa2ebeeb3a" );
TUT_TEARDOWN()

}

