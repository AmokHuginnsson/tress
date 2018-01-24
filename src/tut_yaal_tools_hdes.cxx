/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstdio>
#include <cstring>
#include <TUT/tut.hpp>

#include <yaal/tools/hdes.hxx>
#include <yaal/tools/crypto.hxx>
#include <yaal/tools/hmemory.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::crypto;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hdes : public simple_mock<tut_yaal_tools_hdes> {
	virtual ~tut_yaal_tools_hdes( void ) {}
	void do_des( HString, HString, HDes::action_t const& );
	void crypt_decrypt_test( int );
};

TUT_TEST_GROUP( tut_yaal_tools_hdes, "yaal::tools::HDes" );

void tut_yaal_tools_hdes::do_des( HString src_, HString dst_, HDes::action_t const& action_ ) {
	HFile in;
	HFile out;
	HString passwd;
	cin >> passwd;
	if ( src_ == "-" )
		in.open( stdin, HFile::OWNERSHIP::EXTERNAL );
	else
		in.open( src_, HFile::OPEN::READING );
	if ( dst_ == "-" )
		out.open( stdout, HFile::OWNERSHIP::EXTERNAL );
	else
		out.open( dst_, HFile::OPEN::WRITING );
	if ( action_ == HDes::CRYPT )
		crypto::crypt_3des( in, out, passwd );
	else
		crypto::decrypt_3des( in, out, passwd );
}

void tut_yaal_tools_hdes::crypt_decrypt_test( int onSize_ ) {
	HChunk m( onSize_ + 1 );
	clog << "+" << endl;
	for ( int i( 0 ); i < onSize_; ++ i )
		m.get<char>()[ i ] = static_cast<char>( ( i % 26 ) + 'a' );
	HStringStream ss;
 {
		HFile out( "./out/crypted", HFile::OPEN::WRITING );
		if ( onSize_ > 0 ) {
			HMemoryObserver mo( m.raw(), onSize_ );
			HMemory protype( mo, HMemory::INITIAL_STATE::VALID );
			crypto::crypt_3des( protype, out, "kalafior" );
		} else
			crypto::crypt_3des( ss, out, "kalafior" );
	}
 {
		HFile in( "./out/crypted", HFile::OPEN::READING );
		crypto::decrypt_3des( in, ss, "kalafior" );
	}
	HString check( ss.string() );
	ENSURE_EQUALS( "decrypted lenght is incorrect", check.get_length(), onSize_ );
	ENSURE_EQUALS( "decrypted data is incorrect", check, m.get<char>() );
}

TUT_UNIT_TEST( "crypt file" )
	if ( setup._argc > 2 )
		do_des( setup._argv[ 1 ], setup._argv[ 2 ], HDes::CRYPT );
	else {
		HDes d( "kotek" );
		char const prototype[] = "test1234";
		char buf[ sizeof ( prototype ) ];
		strncpy( buf, prototype, sizeof ( prototype ) );
		d.crypt( reinterpret_cast<u8_t*>( buf ), 8, HDes::CRYPT );
		for ( int i( 0 ); i < ( static_cast<int>( sizeof ( prototype ) ) - 1 ); ++ i )
			ENSURE_NOT( "crypto failed", buf[i] == prototype[i] );
		d.crypt( reinterpret_cast<u8_t*>( buf ), 8, HDes::DECRYPT );
		ENSURE( "crypto or decrypt failed", equal( buf, buf + sizeof ( prototype ) - 1, prototype ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "decrypt file" )
	if ( setup._argc > 2 )
		do_des( setup._argv[ 1 ], setup._argv[ 2 ], HDes::DECRYPT );
	else {
		char prototype[] = "test1234";
		char buf[ sizeof ( prototype ) ];
		char buf2[ sizeof ( prototype ) ];
		HMemoryObserver srcMo( prototype, static_cast<int>( sizeof ( prototype ) ) - 1 );
		HMemory src( srcMo, HMemory::INITIAL_STATE::VALID );
		HMemoryObserver dstMo( buf, sizeof ( buf ) );
		HMemory dst( dstMo );
		strncpy( buf, prototype, sizeof ( prototype ) );
		strncpy( buf2, prototype, sizeof ( prototype ) );
		crypto::crypt_3des( src, dst, "kotek" );
		HDes d( "kotek" );
		d.crypt( reinterpret_cast<u8_t*>( buf2 ), 8, HDes::CRYPT );
		ENSURE( "crypto through streams failed", equal( buf, buf + sizeof ( prototype ) - 1, buf2 ) );
		for ( int i( 0 ); i < ( static_cast<int>( sizeof ( prototype ) ) - 1 ); ++ i )
			ENSURE_NOT( "crypto failed", buf[i] == prototype[i] );
		d.crypt( reinterpret_cast<u8_t*>( buf ), 8, HDes::DECRYPT );
		ENSURE( "crypto or decrypt failed", equal( buf, buf + sizeof ( prototype ) - 1, prototype ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "en/de cryption of various lengths" )
	TIME_CONSTRAINT_EXEMPT();
	for ( int i( 0 ); i < 300; ++ i )
		crypt_decrypt_test( i );
TUT_TEARDOWN()

}

