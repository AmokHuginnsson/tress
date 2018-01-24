/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/base.hxx>
#include <yaal/hcore/unicode.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_lexical_cast );
TUT_TEST_GROUP( tut_yaal_lexical_cast, "yaal::lexical_cast", 60 );

TUT_UNIT_TEST( "0" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
	ENSURE_EQUALS( "overlong string with short int", lexical_cast<int>( "0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"_ys ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "9xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-9xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "9xOlab" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-9xOlab" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "axOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-axOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), 10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), -10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0x" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0x" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), 267 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), -267 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "01Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-01Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "07Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0o7Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 7 );
	ENSURE_THROW( "too many oct digits ok", lexical_cast<int long long unsigned>( "0o12345671234567123456712345671234567123456712345"_ys ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-07Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0o7Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0o8Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "08Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-08Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "078Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-078Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "01" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-01" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0b110b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), 6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0b110b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), -6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0b110c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), 6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0b11001001010011101010101" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), -6596437 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0110c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 72 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0110c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -72 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "1010c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 1010 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-101010c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -101010 );
	ENSURE_THROW( "casting with overflow succeeded", lexical_cast<int short>( get_test_name().c_str() ), HOutOfRangeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "1b010" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-1b010" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), -1 );
	ENSURE_THROW( "too many bin digits ok", lexical_cast<int long long unsigned>( "0b10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"_ys ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "string to bool" )
	ENSURE_EQUALS( "yes to bool failed", lexical_cast<bool>( static_cast<char const*>( "yes" ) ), true );
	ENSURE_EQUALS( "no to bool failed", lexical_cast<bool>( static_cast<char const*>( "no" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "true" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "false" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "on" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "off" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "enable" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "disable" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "enabled" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "disabled" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "1" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "0" ) ), false );
	ENSURE_THROW( "casting garbage to bool did not throw", lexical_cast<bool>( static_cast<char const*>( "invalid" ) ), HLexicalCastException );
	ENSURE_THROW( "casting garbage to bool did not throw", lexical_cast<bool>( static_cast<char const*>( "2" ) ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "conversions" )
	ENSURE_EQUALS( "lexical_cast<HString> void_p failed", lexical_cast<HString>( static_cast<void*>( nullptr ) ), "0x0" );
	ENSURE_EQUALS( "lexical_cast<HString> double failed", lexical_cast<HString>( 3.141592 ), "3.141592" );
	ENSURE_EQUALS( "lexical_cast<HString> float failed", lexical_cast<HString>( 2.718281f ), "2.718281" );
	ENSURE_EQUALS( "lexical_cast<HString> int long long unsigned failed", lexical_cast<HString>( 1234567890123456789ULL ), "1234567890123456789" );
	ENSURE_EQUALS( "lexical_cast<HString> int long unsigned failed", lexical_cast<HString>( 4234567890UL ), "4234567890" );
	ENSURE_EQUALS( "lexical_cast<HString> int unsigned failed", lexical_cast<HString>( 4234567890U ), "4234567890" );
	ENSURE_EQUALS( "lexical_cast<HString> int short failed", lexical_cast<HString>( static_cast<int short>( 32145 ) ), "32145" );
	ENSURE_EQUALS( "lexical_cast<HString> int short unsigned failed", lexical_cast<HString>( static_cast<int short unsigned>( 54321 ) ), "54321" );
	static char unsigned const UC_INIT = static_cast<char unsigned>( unicode::CODE_POINT::LATIN_SMALL_LETTER_O_WITH_ACUTE.get() );
	static char const UC_OK[] = "ó";
	ENSURE_EQUALS( "lexical_cast<HString> char unsigned failed", lexical_cast<HString>( static_cast<char unsigned>( UC_INIT ) ), UC_OK );
	ENSURE_EQUALS( "lexical_cast<int> failed", lexical_cast<int>( static_cast<char const*>( "-2147483647" ) ), -2147483647 );
	ENSURE_EQUALS( "lexical_cast<int> failed", lexical_cast<int>( static_cast<char const*>( "-0x7FFFFFFF" ) ), -2147483647 );
	ENSURE_THROW( "lexical_cast<int> overflow succeeded", lexical_cast<int>( static_cast<char const*>( "2147483648" ) ), HOutOfRangeException );
#if SIZEOF_INT_LONG == 8
	ENSURE_EQUALS( "lexical_cast<int long> failed", lexical_cast<int long>( static_cast<char const*>( "-9223372036854775807" ) ), -9223372036854775807L );
	ENSURE_EQUALS( "lexical_cast<int long> failed", lexical_cast<int long>( static_cast<char const*>( "-0x7FFFFFFFFFFFFFFF" ) ), -9223372036854775807L );
	ENSURE_THROW( "lexical_cast<int long> overflow succeeded", lexical_cast<int long>( static_cast<char const*>( "9223372036854775808" ) ), HOutOfRangeException );
	/* unsigned */
	ENSURE_EQUALS( "lexical_cast<int long unsigned failed", lexical_cast<int long unsigned>( static_cast<char const*>( "18446744073709551615" ) ), 18446744073709551615UL );
	ENSURE_EQUALS( "lexical_cast<int long unsigned failed", lexical_cast<int long unsigned>( static_cast<char const*>( "0xFFFFFFFFFFFFFFFF" ) ), 18446744073709551615UL );
	ENSURE_THROW( "lexical_cast<int long unsigned overflow succeeded", lexical_cast<int long unsigned>( static_cast<char const*>( "18446744073709551616" ) ), HOutOfRangeException );
#else
	ENSURE_EQUALS( "lexical_cast<int long> failed", lexical_cast<int long>( static_cast<char const*>( "-2147483647" ) ), -2147483647L );
	ENSURE_EQUALS( "lexical_cast<int long> failed", lexical_cast<int long>( static_cast<char const*>( "-0x7FFFFFFF" ) ), -2147483647L );
	ENSURE_THROW( "lexical_cast<int long> overflow succeeded", lexical_cast<int long>( static_cast<char const*>( "2147483648" ) ), HOutOfRangeException );
	/* unsigned */
	ENSURE_EQUALS( "lexical_cast<int long unsigned failed", lexical_cast<int long unsigned>( static_cast<char const*>( "4294967295" ) ), 4294967295UL );
	ENSURE_EQUALS( "lexical_cast<int long unsigned failed", lexical_cast<int long unsigned>( static_cast<char const*>( "0xFFFFFFFF" ) ), 4294967295UL );
	ENSURE_THROW( "lexical_cast<int long unsigned overflow succeeded", lexical_cast<int long unsigned>( static_cast<char const*>( "4294967296" ) ), HOutOfRangeException );
#endif
	ENSURE_EQUALS( "lexical_cast<int long long> failed", lexical_cast<int long long>( static_cast<char const*>( "-9223372036854775807" ) ), -9223372036854775807LL );
	ENSURE_EQUALS( "lexical_cast<int long long> failed", lexical_cast<int long long>( static_cast<char const*>( "-0x7FFFFFFFFFFFFFFF" ) ), -9223372036854775807LL );
	ENSURE_THROW( "lexical_cast<int long long> overflow succeeded", lexical_cast<int long long>( static_cast<char const*>( "9223372036854775808" ) ), HOutOfRangeException );
	ENSURE_THROW( "lexical_cast<int long long> on invalid succeeded", lexical_cast<int long long>( static_cast<char const*>( " kotek" ) ), HLexicalCastException );
	ENSURE_EQUALS( "lexical_cast<int long long> failed", lexical_cast<int long long>( static_cast<char const*>( "-12345678abcdefgh" ) ), -12345678LL );
	ENSURE_EQUALS( "lexical_cast<int long long> failed", lexical_cast<int long long>( static_cast<char const*>( "-0x12345678abcdefgh" ) ), -0x12345678abcdefLL );
	/* unsigned */
	ENSURE_EQUALS( "lexical_cast<int long long unsigned> failed", lexical_cast<int long long unsigned>( static_cast<char const*>( "18446744073709551615" ) ), 18446744073709551615ULL );
	ENSURE_EQUALS( "lexical_cast<int long long unsigned> failed", lexical_cast<int long long unsigned>( static_cast<char const*>( "0xFFFFFFFFFFFFFFFF" ) ), 18446744073709551615ULL );
	ENSURE_EQUALS( "lexical_cast<int long long unsigned> failed", lexical_cast<int long long unsigned>( static_cast<char const*>( "12345678abcdefgh" ) ), 12345678ULL );
	ENSURE_EQUALS( "lexical_cast<int long long unsigned> failed", lexical_cast<int long long unsigned>( static_cast<char const*>( "0x12345678abcdefgh" ) ), 0x12345678abcdefULL );
	ENSURE_THROW( "lexical_cast<int long long unsigned> overflow succeeded", lexical_cast<int long long unsigned>( static_cast<char const*>( "18446744073709551616" ) ), HOutOfRangeException );
	ENSURE_THROW( "lexical_cast<int long long> on invalid succeeded", lexical_cast<int long long unsigned>( static_cast<char const*>( " kotek" ) ), HLexicalCastException );
	ENSURE_DISTANCE( "lexical_cast<float> failed", lexical_cast<float>( static_cast<char const*>( "3.141592" ) ), 3.141592f, static_cast<float>( epsilon ) );
	ENSURE_DISTANCE( "lexical_cast<double> failed", lexical_cast<double>( static_cast<char const*>( "3.1415926535" ) ), 3.1415926535, static_cast<double>( epsilon ) );
	ENSURE_DISTANCE( "lexical_cast<double long> failed", lexical_cast<double long>( static_cast<char const*>( "2.718281828459045" ) ), 2.718281828459045L, epsilon );
	ENSURE( "is_hexadecimal failed", is_hexadecimal( static_cast<char const*>( "0x123fb" ) ) );
	ENSURE_NOT( "is_hexadecimal failed", is_hexadecimal( static_cast<char const*>( "0y123fb" ) ) );
	ENSURE_NOT( "is_hexadecimal failed", is_hexadecimal( static_cast<char const*>( "0xghi" ) ) );
	ENSURE( "is_octal failed", is_octal( static_cast<char const*>( "0o12356" ) ) );
	ENSURE_NOT( "is_octal failed", is_octal( static_cast<char const*>( "0x123fb" ) ) );
	ENSURE_NOT( "is_octal failed", is_octal( static_cast<char const*>( "0o8989" ) ) );
	ENSURE( "is_binary failed", is_binary( static_cast<char const*>( "0b11010101" ) ) );
	ENSURE_NOT( "is_binary failed", is_binary( static_cast<char const*>( "0o12345" ) ) );
	ENSURE_NOT( "is_binary failed", is_binary( static_cast<char const*>( "0b234" ) ) );
TUT_TEARDOWN()

}

