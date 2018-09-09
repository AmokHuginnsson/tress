/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hash.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;
using namespace tress;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hash_sha512 );
TUT_TEST_GROUP( tut_yaal_tools_hash_sha512, "yaal::tools::tools::hash::sha512" );

TUT_UNIT_TEST( "original suite <0> (empty)" )
	static char const INPUT[] = "";
	static char const HASH[] = "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <1>" )
	static char const INPUT[] = "a";
	static char const HASH[] = "1f40fc92da241694750979ee6cf582f2d5d7d28e18335de05abc54d0560e0f5302860c652bf08d560252aa5e74210546f369fbbbce8c12cfc7957b2652fe9a75";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <2>" )
	static char const INPUT[] = "abc";
	static char const HASH[] = "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <3>" )
	static char const INPUT[] = "message digest";
	static char const HASH[] = "107dbf389d9e9f71a3a95f6c055b9251bc5268c2be16d6c13492ea45b0199f3309e16455ab1e96118e8a905d5597b72038ddb372a89826046de66687bb420e7c";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <4>" )
	static char const INPUT[] = "abcdefghijklmnopqrstuvwxyz";
	static char const HASH[] = "4dbff86cc2ca1bae1e16468a05cb9881c97f1753bce3619034898faa1aabe429955a1bf8ec483d7421fe3c1646613a59ed5441fb0f321389f77f48a879c7b1f1";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <5>" )
	static char const INPUT[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	static char const HASH[] = "1e07be23c26a86ea37ea810c8ec7809352515a970e9253c26f536cfc7a9996c45c8370583e0a78fa4a90041d71a4ceab7423f19c71b9d5a3e01249f0bebd5894";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <6>" )
	static char const INPUT[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
	static char const HASH[] = "72ec1ef1124a45b047e8b7c75a932195135bb61de24ec0d1914042246e0aec3a2354e093d76f3048b456764346900cb130d2a4fd5dd16abb5e30bcb850dee843";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "special A for o.s.<6>" )
	static char const INPUT[] = "1234567890123456789012345678901234567890123456789012345678901234";
	static char const HASH[] = "c96798c0781b89bbf01de99f1aba950ce83884ef54517120d1586a596bf004f42aaaf259da15f5b1332564609ca270273cc3271467f981deed4495b78cded93c";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "special B for o.s.<6>" )
	static char const INPUT[] = "123456789012345678901234567890123456789012345678901234567890123";
	static char const HASH[] = "27f923d5f0d3685dd22e6e30d75cde0e1fa6863211f8ad34f968398acdec5409ba312cae56f2c17068222a5d84a719ebe68a6e6dec821f43fdc1e1043acc4ba4";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "special C for o.s.<6>" )
	static char const INPUT[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678";
	static char const HASH[] = "222b2f64c285e66996769b5a03ef863cfd3b63ddb0727788291695e8fb84572e4bfe5a80674a41fd72eeb48592c9c79f44ae992c76ed1b0d55a670a83fc99ec6";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "special D for o.s.<6>" )
	static char const INPUT[] = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567";
	static char const HASH[] = "f43adab99283e7dbd971eb8c7c137def0825e165c677e99d3c60fe20afae356dc2e301d2a63cec8cfc76beb560a7837cd28c029f025f702e4a328e83f4537b78";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from string" )
	static char const INPUT[] = "Ala ma kota";
	static char const HASH[] = "ea6177922cf84bd32af98e6b497face3f76024bc827404676c8f37db547a74910308858248dd7bb4a0900d3a11d0b98f0f84c5c03dff7290c1da448c4d8a5d62";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from string (small alternation)" )
	static char const INPUT[] = "Ala ma koty";
	static char const HASH[] = "d62fea3edd8adc485ea6220baf1e3d560842b15c3fdb0aac531d3f2011371147a725a16d4bd9a2d0175a3c22996415ba367e2781d28c66f8f3d0fd41a3e8edcc";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from file" )
	static char const* const INPUT = ( setup._argc > 1 ) ? setup._argv[ 1 ] : "./data/karatsuba.bc";
	static char const HASH[] = "747973bd4972356b4d08e4855ee7617f12c97b4f4cf4892f6925b4ea961654fd6072890a1ba6ab5169852f06594886d4b548758f77e5d30ec6b1c130e2998829";
	HFile f( INPUT, HFile::OPEN::READING );
	if ( setup._argc > 1 ) {
		cout << tools::hash::string( tools::hash::FUNCTION::SHA512, f ) << endl;
	} else {
		ENSURE_EQUALS( "bad tools::hash", tools::hash::string( tools::hash::FUNCTION::SHA512, f ), HASH );
	}
TUT_TEARDOWN()

}

