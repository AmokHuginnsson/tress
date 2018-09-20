/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_cryptography : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_cryptography( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_cryptography, "yaal::tools::HHuginn.Cryptography" );

TUT_UNIT_TEST( "md5" )
	ENSURE_EQUALS(
		"Cryptography.md5 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.md5(\"\"));\n"
			"}"
		),
		"\"d41d8cd98f00b204e9800998ecf8427e\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "sha1" )
	ENSURE_EQUALS(
		"Cryptography.sha1 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.sha1(\"\"));\n"
			"}"
		),
		"\"da39a3ee5e6b4b0d3255bfef95601890afd80709\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "sha512" )
	ENSURE_EQUALS(
		"Cryptography.sha512 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.sha512(\"\"));\n"
			"}"
		),
		"\"cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "hmac_md5" )
	ENSURE_EQUALS(
		"Cryptography.hmac_md5 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.hmac_md5(\"\",\"\"));\n"
			"}"
		),
		"\"74e6f7298a9c2d168935f58c001bad88\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "hmac_sha1" )
	ENSURE_EQUALS(
		"Cryptography.hmac_sha1 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.hmac_sha1(\"\",\"\"));\n"
			"}"
		),
		"\"fbdb1d1b18aa6c08324b7d64b71fb76370690e1d\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "hmac_sha512" )
	ENSURE_EQUALS(
		"Cryptography.hmac_sha512 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.hmac_sha512(\"\",\"\"));\n"
			"}"
		),
		"\"b936cee86c9f87aa5d3c6f2e84cb5a4239a5fe50480a6ec66b70ab5b1f4ac6730c6c515421b327ec1d69402e53dfb49ad7381eb067b338fd7b0cb22247225d47\""
	);
TUT_TEARDOWN()

}

