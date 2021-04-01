/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>
#include <iterator>
#include <TUT/tut.hpp>

#include <yaal/hcore/hstring.hxx>
#include <yaal/hcore/hformat.hxx>
#include <yaal/hcore/random.hxx>
#include <yaal/hcore/unicode.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::random;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

static int const MIN_CAPACITY( static_cast<int>( sizeof ( HString ) ) - 1 );

TUT_SIMPLE_MOCK( tut_yaal_hcore_hstring );
TUT_TEST_GROUP( tut_yaal_hcore_hstring, "yaal::hcore::HString" );

TUT_UNIT_TEST( "trivial constructor" )
	HString str;
	ENSURE_EQUALS( "trivial construction failed", str, "" );
	ENSURE_EQUALS( "trivial construction failed (size)", str.size(), 0 );
	ENSURE_EQUALS( "trivial construction failed (capacity)", str.capacity(), MIN_CAPACITY );
	ENSURE_EQUALS( "trivial construction failed (is_empty)", str.empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "construction from char* [and size]" )
	static char const CORRECT[] = "yaal";
	HString str( CORRECT );
	ENSURE_EQUALS( "construction from c-string does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from char* failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from char* failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from char* failed (is_empty)", str.empty(), false );
	ENSURE_EQUALS( "construction from char* and size failed (rank)", HUTF8String( str ).rank(), 0 );

	static char const SRC7[] = "yaal ó very long string";
	static char const EXP7[] = "yaal ó";
	HString str7( SRC7, 7 );
	ENSURE_EQUALS( "construction from char8-string and size does not work", str7, EXP7 );
	ENSURE_EQUALS( "construction from char* and size failed (size)", str7.size(), 6 );
	ENSURE_EQUALS( "construction from char* and size failed (capacity)", str7.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from char* and size failed (is_empty)", str7.empty(), false );
	ENSURE_EQUALS( "construction from char* and size failed (rank)", HUTF8String( str7 ).rank(), 1 );

	static char const SRC8[] = "yaalyaalyaalyaalyaalyaalyaal@ ó very long string";
	static char const EXP8[] = "yaalyaalyaalyaalyaalyaalyaal@ ó";
	HString str8( SRC8, 32 );
	ENSURE_EQUALS( "construction from char8-string and size does not work", str8, EXP8 );
	ENSURE_EQUALS( "construction from char* and size failed (size)", str8.size(), 31 );
	ENSURE_EQUALS( "construction from char* and size failed (capacity)", str8.capacity(), 32 );
	ENSURE_EQUALS( "construction from char* and size failed (is_empty)", str8.empty(), false );
	ENSURE_EQUALS( "construction from char* and size failed (rank)", HUTF8String( str8 ).rank(), 1 );

	static char16_t const SRC16[] = u"yaal α very long string";
	static char const EXP16[] = "yaal α";
	HString str16( SRC16, 6 );
	ENSURE_EQUALS( "construction from char16-string and size does not work", str16, EXP16 );
	ENSURE_EQUALS( "construction from char16* and size failed (size)", str16.size(), 6 );
	ENSURE_EQUALS( "construction from char16* and size failed (capacity)", str16.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from char16* and size failed (is_empty)", str16.empty(), false );
	ENSURE_EQUALS( "construction from char16* and size failed (rank)", HUTF8String( str16 ).rank(), 2 );

	static char const SRC16_3[] = "yaal ￿ very long string";
	static char const EXP16_3[] = "yaal ￿";
	HString str16_3( SRC16_3, 8 );
	ENSURE_EQUALS( "construction from char16-string and size does not work", str16_3, EXP16_3 );
	ENSURE_EQUALS( "construction from char16* and size failed (size)", str16_3.size(), 6 );
	ENSURE_EQUALS( "construction from char16* and size failed (capacity)", str16_3.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from char16* and size failed (is_empty)", str16_3.empty(), false );
	ENSURE_EQUALS( "construction from char16* and size failed (rank)", HUTF8String( str16_3 ).rank(), 2 );

	static char32_t const SRC32[] = U"yaal 🐍 very long string";
	static char const EXP32[] = "yaal 🐍";
	HString str32( SRC32, 6 );
	ENSURE_EQUALS( "construction from char32-string and size does not work", str32, EXP32 );
	ENSURE_EQUALS( "construction from char32* and size failed (size)", str32.size(), 6 );
	ENSURE_EQUALS( "construction from char32* and size failed (capacity)", str32.capacity(), 32 );
	ENSURE_EQUALS( "construction from char32* and size failed (is_empty)", str32.empty(), false );
	ENSURE_EQUALS( "construction from char32* and size failed (rank)", HUTF8String( str32 ).rank(), 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy construction" )
	static char const CORRECT[] = "1024";
	HString str( CORRECT );
	HString copy( str );
	ENSURE_EQUALS( "copy construction does not work", copy, CORRECT );
	ENSURE_EQUALS( "copy construction failed (size)", copy.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "copy construction failed (capacity)", copy.capacity(), max( 8, MIN_CAPACITY ) );
	ENSURE_EQUALS( "copy construction failed (is_empty)", copy.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "construction from (const) iterator" )
	HString const str( "Ala ma kota, a nie psa" );
	HString s1( str.begin() + 7, str.begin() + 10 );
	ENSURE_EQUALS( "construction form const_iterator failed", s1, "kot" );
	HString src( str );
	HString s2( src.begin() + 7, src.begin() + 10 );
	ENSURE_EQUALS( "construction form iterator failed", s2, "kot" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "construction from integers" )
	/* from int short */ {
		static int short const INIT = 1024;
		static char const CORRECT[] = "1024";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int long does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
		ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
	}

	/* int short unsigned */ {
		static int short unsigned const INIT = 1024;
		static char const CORRECT[] = "1024";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int long does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
		ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
	}
	/* int */ {
		static int const INIT = 1024;
		static char const CORRECT[] = "1024";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int failed (size)",
				str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
		ENSURE_EQUALS( "construction from int failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from int failed (is_empty)", str.empty(), false );
	}
	/* int unsigned */ {
		static int unsigned const INIT = 1024;
		static char const CORRECT[] = "1024";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int unsigned does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int unsigned failed (size)",
				str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
		ENSURE_EQUALS( "construction from int unsigned failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from int unsigned failed (is_empty)", str.empty(), false );
	}
	/* int long */ {
		static int long const INIT = 1024;
		static char const CORRECT[] = "1024";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int long does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
		ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
	}
	/* int long unsigned */ {
		static int long unsigned const INIT = 1024;
		static char const CORRECT[] = "1024";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int long unsigned does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int long unsigned failed (size)",
				str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
		ENSURE_EQUALS( "construction from int long unsigned failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from int long unsigned failed (is_empty)", str.empty(), false );
	}

	/* int long long */ {
		static int long long const INIT = -3141592653589793ll;
		static char const CORRECT[] = "-3141592653589793";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int long long does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int long long failed (size)",
				str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );

		ENSURE_EQUALS( "construction from int long long failed (capacity)", str.capacity(), SIZEOF_INT_LONG == 4 ? 32 : MIN_CAPACITY );
		ENSURE_EQUALS( "construction from int long long failed (is_empty)", str.empty(), false );
	}
	/* int long long unsigned */ {
		static int long long unsigned const INIT = 2718281828459045ll;
		static char const CORRECT[] = "2718281828459045";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int long unsigned does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int long unsigned failed (size)",
				str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );

		ENSURE_EQUALS( "construction from int long long unsigned failed (capacity)", str.capacity(), SIZEOF_INT_LONG == 4 ? 32 : MIN_CAPACITY );
		ENSURE_EQUALS( "construction from int long long unsigned failed (is_empty)", str.empty(), false );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "construction from characters" )
	/* code point */ {
		static code_point_t const CORRECT = unicode::CODE_POINT::SYMBOL_WHITE_SMILING_FACE;
		HString str( CORRECT );
		ENSURE_EQUALS( "construction from code_point_t does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from code_point_t failed (size)", str.size(), 1 );
		ENSURE_EQUALS( "construction from code_point_t failed (capacity)", str.capacity(), max( 1, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from code_point_t failed (is_empty)", str.empty(), false );
		HString nil( code_point_t( 0 ) );
		ENSURE_EQUALS( "construction from nil code_point_t failed (is_empty)", nil.is_empty(), true );
	}
	/* char */ {
		static char const CORRECT = '1';
		HString str( CORRECT );
		ENSURE_EQUALS( "construction from char does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from char failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) ) );
		ENSURE_EQUALS( "construction from char failed (capacity)", str.capacity(), max( 1, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from char failed (is_empty)", str.empty(), false );
		HString nil( '\0' );
		ENSURE_EQUALS( "construction from nil char failed (is_empty)", nil.is_empty(), true );
	}
	/* char unsigned */ {
		static char unsigned const INIT = static_cast<char unsigned>( unicode::CODE_POINT::LATIN_SMALL_LETTER_O_WITH_ACUTE.get() );
		static char const CORRECT[] = "ó";
		HString str( INIT );
		ENSURE_EQUALS( "construction from char unsigned does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from char unsigned failed (size)", str.size(), 1 );
		ENSURE_EQUALS( "construction from char unsigned failed (capacity)", str.capacity(), max( 1, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from char unsigned failed (is_empty)", str.empty(), false );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "construction from floating point" )
	/* float */ {
		static float const INIT = static_cast<float>( 2.718281828459045 );
		static char const CORRECT[] = "2.718282";
		HString str( INIT );
		ENSURE_EQUALS( "construction from int long does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
		ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), MIN_CAPACITY );
		ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
	}
	/* double */ {
		static double INIT = 3.141593;
		static char const* const CORRECT = "3.141593";
		HString str( INIT );
		ENSURE_EQUALS( "construction from double does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from double failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
		ENSURE_EQUALS( "construction from double failed (capacity)", str.capacity(), MIN_CAPACITY );
		ENSURE_EQUALS( "construction from double failed (is_empty)", str.empty(), false );
	}
	/* double long */ {
		static double long INIT = 3.141592653589;
		static char const* const CORRECT = "3.141592653589";
		HString str( INIT );
		ENSURE_EQUALS( "construction from double does not work", str, CORRECT );
		ENSURE_EQUALS( "construction from double failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
		ENSURE_EQUALS( "construction from double failed (capacity)", str.capacity(), max( 16, MIN_CAPACITY ) );
		ENSURE_EQUALS( "construction from double failed (is_empty)", str.empty(), false );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "construction from void*" )
	static size_t const tmp = 0xdeadbeef;
	static void* INIT = reinterpret_cast<void*>( tmp );
	static char const* const CORRECT = "0xdeadbeef";
	HString str( INIT );
	ENSURE_EQUALS( "construction from void* does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from void* failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
	ENSURE_EQUALS( "construction from void* failed (capacity)", str.capacity(), MIN_CAPACITY );
	ENSURE_EQUALS( "construction from void* failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "user defined literal" )
#ifdef __DEBUG__
	/* FIXME TODO */
	ENSURE_EQUALS( "udf failed", "Ala ma kota"_ys, "Ala ma kota" );
	ENSURE_EQUALS( "udf failed", "Ala ma kota"_ys.get_length(), 11 );
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator +=" )
	static char const INIT[] = "1024";
	static char const* const TEST = "0xdeadbeef";
	static char const CORRECT[] = "10240xdeadbeef";
	HString str( INIT );
	ENSURE_EQUALS( "char* constructor does not work", str, INIT );
	ENSURE_EQUALS( "char* constructor failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ENSURE_EQUALS( "char* constructor failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
	ENSURE_EQUALS( "char* constructor failed (is_empty)", str.empty(), false );
	str += TEST;
	ENSURE_EQUALS( "operator+= does not work", str, CORRECT );
	ENSURE_EQUALS( "operator+= failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "operator+= failed (capacity)", str.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "operator+= failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript" )
	/* UCS-1 */ {
		char const data[] = "abecadlo";
		HString s( data );
		for ( int i( 0 ); i < static_cast<int>( sizeof ( data ) - 1 ); ++ i ) {
			ENSURE_EQUALS( "bad value from subscript", s[i], code_point_t( static_cast<yaal::u32_t>( data[i] ) ) );
		}
		ENSURE_THROW( "subscript on bad index succeeded", s[-1], HStringException );
		ENSURE_THROW( "subscript on bad index succeeded", s[static_cast<int>( sizeof ( data ) )], HStringException );
	}
	/* UCS-2 */ {
		char const data[] = "abecadło";
		code_point_t const res[] = { 'a'_ycp, 'b'_ycp, 'e'_ycp, 'c'_ycp, 'a'_ycp, 'd'_ycp, unicode::CODE_POINT::LATIN_SMALL_LETTER_L_WITH_STROKE, 'o'_ycp };
		HString s( data );
		for ( int i( 0 ); i < static_cast<int>( yaal::size( res ) ); ++ i ) {
			ENSURE_EQUALS( "bad value from subscript", s[i], res[i] );
		}
		ENSURE_THROW( "subscript on bad index succeeded", s[-1], HStringException );
		ENSURE_THROW( "subscript on bad index succeeded", s[static_cast<int>( sizeof ( data ) )], HStringException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "front/back" )
	HString s( "abesadlo" );
	ENSURE_EQUALS( "front failed", s.front(), static_cast<code_point_t>( 'a' ) );
	ENSURE_EQUALS( "back failed", s.back(), static_cast<code_point_t>( 'o' ) );
	s.assign( "abesadÅo" );
	ENSURE_EQUALS( "front failed", s.front(), static_cast<code_point_t>( 'a' ) );
	ENSURE_EQUALS( "back failed", s.back(), static_cast<code_point_t>( 'o' ) );
	s.clear();
	ENSURE_THROW( "front on empty succeeded", s.front(), HStringException );
	ENSURE_THROW( "back on empty succeeded", s.back(), HStringException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_at" )
	/* UCS-1 */ {
		char const data[] = "abecadlo";
		char const dataOut[][10] = {
			"abec4dlo",
			"abec4dl0",
			"4bec4dl0",
			"4bec4dł0",
			"4be"
		};
		int repl[][3] = {
			{ 4, '4' },
			{ 7, '0' },
			{ 0, '4' },
			{ 6, static_cast<int>( unicode::CODE_POINT::LATIN_SMALL_LETTER_L_WITH_STROKE.get() ) },
			{ 3, 0 }
		};
		HString s( data );
		for ( int i( 0 ); i < yaal::size( dataOut ); ++ i ) {
			s.set_at( repl[i][0], code_point_t( static_cast<code_point_t::value_type>( repl[i][1] ) ) );
			ENSURE_EQUALS( "set_at failed", s, dataOut[i] );
		}
		ENSURE_THROW( "set_at on bad index succeeded", s.set_at( -1, 0_ycp ), HStringException );
		ENSURE_THROW( "set_at on bad index succeeded", s.set_at( static_cast<int>( sizeof ( data ) - 1 ), 0_ycp ), HStringException );
	}
	/* UCS-2 */ {
		char const data[] = "abecadło";
		char const dataOut[][10] = {
			"abec4dło",
			"abec4dł0",
			"4bec4dł0",
			"4be"
		};
		int repl[][3] = {
			{ 4, '4' },
			{ 7, '0' },
			{ 0, '4' },
			{ 3, 0 }
		};
		HString s( data );
		for ( int i( 0 ); i < yaal::size( dataOut ); ++ i ) {
			s.set_at( repl[i][0], code_point_t( static_cast<code_point_t::value_type>( repl[i][1] ) ) );
			ENSURE_EQUALS( "set_at failed", s, dataOut[i] );
		}
		ENSURE_THROW( "set_at on bad index succeeded", s.set_at( -1, 0_ycp ), HStringException );
		ENSURE_THROW( "set_at on bad index succeeded", s.set_at( static_cast<int>( sizeof ( data ) - 1 ), 0_ycp ), HStringException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "clear" )
	HString str;
	static char const INIT[] = "1024";
	ENSURE_EQUALS( "trivial construction failed", str, "" );
	ENSURE_EQUALS( "trivial construction failed (size)", str.size(), 0 );
	ENSURE_EQUALS( "trivial construction failed (capacity)", str.capacity(), MIN_CAPACITY );
	ENSURE_EQUALS( "trivial construction failed (is_empty)", str.empty(), true );
	str += INIT;
	ENSURE_EQUALS( "operator+= does not work", str, INIT );
	ENSURE_EQUALS( "operator+= failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ENSURE_EQUALS( "operator+= failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
	ENSURE_EQUALS( "operator+= failed (is_empty)", str.empty(), false );
	str.clear();
	ENSURE_EQUALS( "clear does not work", str, "" );
	ENSURE_EQUALS( "clear failed (size)", str.size(), 0 );
	ENSURE_EQUALS( "clear failed (capacity)", str.capacity(), max( 8, MIN_CAPACITY ) );
	ENSURE_EQUALS( "clear failed (is_empty)", str.empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "replace(patter, str)" )
	static char const INIT[] = "aarererererebb";
	static char const PAT1[] = "rere";
	static char const PAT2[] = "OKOK";
	static char const CORRECT12[] = "aaOKOKOKOKrebb";
	static char const PAT3[] = "rok";
	static char const CORRECT23[] = "aarokrokrebb";
	static char const PAT4[] = "I";
	static char const CORRECT34[] = "aaIIrebb";
	static char const PAT5[] = "II";
	static char const PAT6[] = "";
	static char const CORRECT56[] = "aarebb";

	HString str( INIT );
	ENSURE_EQUALS( "char* constructor does not work", str, INIT );
	ENSURE_EQUALS( "char* constructor failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ENSURE_EQUALS( "char* constructor failed (capacity)", str.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "char* constructor failed (is_empty)", str.empty(), false );

	str.replace( PAT1, PAT2 );
	ENSURE_EQUALS( "replace 1->2 does not work", str, CORRECT12 );
	ENSURE_EQUALS( "replace 1->2 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT12 ) - 1 ) );
	ENSURE_EQUALS( "replace 1->2 failed (capacity)", str.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace 1->2 failed (is_empty)", str.empty(), false );

	str.replace( PAT2, PAT3 );
	ENSURE_EQUALS( "replace 2->3 does not work", str, CORRECT23 );
	ENSURE_EQUALS( "replace 2->3 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT23 ) - 1 ) );
	ENSURE_EQUALS( "replace 2->3 failed (capacity)", str.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace 2->3 failed (is_empty)", str.empty(), false );

	str.replace( PAT3, PAT4 );
	ENSURE_EQUALS( "replace 3->4 does not work", str, CORRECT34 );
	ENSURE_EQUALS( "replace 3->4 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT34 ) - 1 ) );
	ENSURE_EQUALS( "replace 3->4 failed (capacity)", str.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace 3->4 failed (is_empty)", str.empty(), false );

	str.replace( PAT5, PAT6 );
	ENSURE_EQUALS( "replace 5->6 does not work", str, CORRECT56 );
	ENSURE_EQUALS( "replace 5->6 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT56 ) - 1 ) );
	ENSURE_EQUALS( "replace 5->6 failed (capacity)", str.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace 5->6 failed (is_empty)", str.empty(), false );

	static char const INIT0[] = "./${NEST}/app/";
	static char const PATA[] = "${NEST}";
	static char const PATB[] = "";
	static char const CORRECT_AB[] = ".//app/";

	str = INIT0;
	str.replace( PATA, PATB );
	ENSURE_EQUALS( "replace A->B does not work", str, CORRECT_AB );
	ENSURE_EQUALS( "replace A->B failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT_AB ) - 1 ) );
	ENSURE_EQUALS( "replace A->B failed (capacity)", str.capacity(), max( 16, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace A->B failed (is_empty)", str.empty(), false );
 {
		static char const INIT1[] = "@c@";
		static char const PAT1A[] = "@";
		static char const PAT1B[] = "UU";
		static char const CORRECT_1AB[] = "UUcUU";
		str = INIT1;
		str.replace( PAT1A, PAT1B );
		ENSURE_EQUALS( "replace A1->B1 does not work", str, CORRECT_1AB );
		ENSURE_EQUALS( "replace A1->B1 failed (size)", str.get_length(), static_cast<int long>( sizeof ( CORRECT_1AB ) - 1 ) );
		ENSURE_EQUALS( "replace A1->B1 failed (capacity)", str.capacity(), MIN_CAPACITY );
		ENSURE_EQUALS( "replace A1->B1 failed (is_empty)", str.empty(), false );
	} {
		static char const INIT1[] = "c@cc@cc@cc@cc@cc@cc";
		static char const PAT1A[] = "@";
		static char const PAT1B[] = "@@";
		static char const CORRECT_1AB[] = "c@@cc@@cc@@cc@@cc@@cc@@cc";
		str = INIT1;
		str.replace( PAT1A, PAT1B );
		ENSURE_EQUALS( "replace A1->B1 does not work", str, CORRECT_1AB );
		ENSURE_EQUALS( "replace A1->B1 failed (size)", str.get_length(), static_cast<int long>( sizeof ( CORRECT_1AB ) - 1 ) );
		ENSURE_EQUALS( "replace A1->B1 failed (capacity)", str.capacity(), max( 32, MIN_CAPACITY ) );
		ENSURE_EQUALS( "replace A1->B1 failed (is_empty)", str.empty(), false );
	}
	/* noop */ {
		static char const INIT1[] = "abecadło";
		str = INIT1;
		str.replace( "", "z pieca" );
		ENSURE_EQUALS( "replace ''->B1 does not work", str, INIT1 );
		ENSURE_EQUALS( "replace ''->B1 failed (size)", str.get_length(), 8 );
		ENSURE_EQUALS( "replace ''->B1 failed (capacity)", str.capacity(), SIZEOF_INT_LONG == 4 ? 16 : MIN_CAPACITY );
		ENSURE_EQUALS( "replace ''->B1 failed (is_empty)", str.empty(), false );
	}
	/* front */
	ENSURE_EQUALS( "front repalce to same length failed", "'main()'"_ys.replace( "'", "#" ), "#main()#" );
	ENSURE_EQUALS( "front repalce to empty failed", "'main()'"_ys.replace( "'", "" ), "main()" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "shift_left" )
	static char const CORRECT[] = "Ala ma kota";
	static int const SHIFT = 4;
	HString str( CORRECT );
	str.shift_left( SHIFT );
	ENSURE_EQUALS( "left_shift failed", str, CORRECT + SHIFT );
	ENSURE_THROW( "no check for negative shift", str.shift_left( -1 ), HStringException);
	str.shift_left( 100000 );
	ENSURE_EQUALS( "left_shift failed", str, "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "shift_right" )
	static char const CORRECT[] = "    Ala ma kota";
	static int const SHIFT = 4;
	HString str( CORRECT + SHIFT );
	str.shift_right( SHIFT );
	ENSURE_EQUALS( "right_shift failed", str, CORRECT );
	ENSURE_THROW( "no check for negative shift", str.shift_right( -1 ), HStringException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mid" )
	char source[] = "abecadlo";
	HString str( source );
	char mid_failed[] = "mid failed";
	ENSURE_EQUALS( mid_failed, str.mid( -10, 100 ), source );
	ENSURE_EQUALS( mid_failed, str.mid( 3, 100 ), "cadlo" );
	ENSURE_EQUALS( mid_failed, str.mid( 3, -2 ), "" );
	ENSURE_EQUALS( mid_failed, str.mid( 35, 5 ), "" );
	ENSURE_EQUALS( mid_failed, str.mid( -15, 3 ), "" );
	ENSURE_EQUALS( mid_failed, str.mid( -15, 18 ), "abe" );
	ENSURE_EQUALS( mid_failed, str.mid( 2, 2 ), "ec" );
	ENSURE_EQUALS( mid_failed, str.mid( 2 ), "ecadlo" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "right" )
	HString str( "ala/." );
	ENSURE_EQUALS( "wrong right part extraction", str.right( 1 ), "." );
	ENSURE_EQUALS( "bad right 0", str.right( 0 ), "" );
	ENSURE_EQUALS( "bad right -1", str.right( -1 ), "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "erase" )
	HString str;
	char s[] = "Ala ma kota";
	char erase_failed[] = "erase failed";
	str = s;ENSURE_EQUALS( erase_failed, str.erase( 0, 4 ), "ma kota" );
	str = s;ENSURE_EQUALS( erase_failed, str.erase( 2, 4 ), "Al kota" );
	str = s;ENSURE_EQUALS( erase_failed, str.erase( -2, 4 ), "a ma kota" );
	str = s;str.erase( 4, 100 );
	ENSURE_EQUALS( "erase 3 failed (size)", str.size(), 4 );
	ENSURE_EQUALS( erase_failed, str, "Ala " );
	str = s;str.erase( 4 );
	ENSURE_EQUALS( "erase 3 failed (size)", str.size(), 4 );
	ENSURE_EQUALS( erase_failed, str, "Ala " );
	str = s;str.erase();
	ENSURE_EQUALS( erase_failed, str.is_empty(), true );
	str = s;ENSURE_EQUALS( erase_failed, str.erase( 0, 100 ), "" );
	HString str2( "|==--|[100%]" );
	ENSURE_EQUALS( erase_failed, str2.erase( 7, 4 ), "|==--|[]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert" )
	HString str;
	char s[] = "abcdef";
	char insert_failed[] = "insert failed";
	char overflow[] = "overflow passed";
	str = s;
	ENSURE_EQUALS( insert_failed, str.insert( 0, "ABCD", 3 ), "ABCabcdef" );
	str = s;
	ENSURE_EQUALS( insert_failed, str.insert( 2, "ABCD", 3 ), "abABCcdef" );
	str = s;
	ENSURE_EQUALS( insert_failed, str.insert( 0, "ABCD", 0 ), "abcdef" );
	str = s;
	ENSURE_EQUALS( insert_failed, str.insert( 0, "CD", 2 ), "CDabcdef" );
	str = s;
	ENSURE_THROW( overflow, str.insert( 0, "ABCD", -1 ), HStringException );
	str = s;
	ENSURE_EQUALS( overflow, str.insert( 3, "ABCD", 10000 ), "abcABCDdef" );
	str = s;
	ENSURE_THROW( insert_failed, str.insert( 20, "ABCD", 3 ), HStringException );
	str = s;
	ENSURE_EQUALS( insert_failed, str.insert( 5, "ABCD", 3 ), "abcdeABCf" );
	str = s;
	ENSURE_EQUALS( insert_failed, str.insert( 6, "ABCD", 3 ), "abcdefABC" );
	str = s;
	ENSURE_THROW( insert_failed, str.insert( 7, "ABCDEFGHIJK", 3 ), HStringException );
	HString str2( "|==--|[]" );
	ENSURE_EQUALS( insert_failed, str2.insert( 7, "done", 4 ), "|==--|[done]" );
	str = s;
	ENSURE_EQUALS( insert_failed, str.insert( 2, "ABCD", 2 ), "abABcdef" );
	str = s;
	ENSURE_EQUALS( insert_failed, str.insert( 3, "ABCD"_ys ), "abcABCDdef" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find" )
	HString str = "abcXYdeYXf";
	char failed[] = "find failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.find( 'A'_ycp ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 1 ), str.find( 'X'_ycp ), 3 );
	ENSURE_EQUALS( format( failed, 2 ), str.find( 'Y'_ycp ), 4 );
	ENSURE_EQUALS( format( failed, 3 ), str.find( 'X'_ycp, -10 ), 3 );
	ENSURE_EQUALS( format( failed, 4 ), str.find( 'Y'_ycp, -10 ), 4 );
	ENSURE_EQUALS( format( failed, 5 ), str.find( 'X'_ycp, 3 ), 3 );
	ENSURE_EQUALS( format( failed, 6 ), str.find( 'Y'_ycp, 3 ), 4 );
	ENSURE_EQUALS( format( failed, 7 ), str.find( 'X'_ycp, 5 ), 8 );
	ENSURE_EQUALS( format( failed, 8 ), str.find( 'Y'_ycp, 5 ), 7 );
	ENSURE_EQUALS( format( failed, 9 ), str.find( 'X'_ycp, 9 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 10 ), str.find( 'Y'_ycp, 9 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 11 ), str.find( 'X'_ycp, 90 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 12 ), str.find( 'Y'_ycp, 90 ), HString::npos + 0 );
	static char const* const PREF = "---> group: ";
	static char const* const SUFF = "yaal, tra la la";
	HString line( PREF );
	line += SUFF;
	ENSURE_EQUALS( format( failed, 13 ), line.find( PREF ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_last" )
	HString str = "abcXYdeYXf012";
	char failed[] = "find_last failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.find_last( 'A'_ycp ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 1 ), str.find_last( 'X'_ycp ), 8 );
	ENSURE_EQUALS( format( failed, 2 ), str.find_last( 'Y'_ycp ), 7 );
	ENSURE_EQUALS( format( failed, 3 ), str.find_last( 'X'_ycp, 100 ), 8 );
	ENSURE_EQUALS( format( failed, 4 ), str.find_last( 'Y'_ycp, 100 ), 7 );
	ENSURE_EQUALS( format( failed, 5 ), str.find_last( 'X'_ycp, 8 ), 8 );
	ENSURE_EQUALS( format( failed, 6 ), str.find_last( 'Y'_ycp, 8 ), 7 );
	ENSURE_EQUALS( format( failed, 7 ), str.find_last( 'X'_ycp, 5 ), 3 );
	ENSURE_EQUALS( format( failed, 8 ), str.find_last( 'Y'_ycp, 5 ), 4 );
	ENSURE_EQUALS( format( failed, 7 ), str.find_last( 'X'_ycp, 3 ), 3 );
	ENSURE_EQUALS( format( failed, 8 ), str.find_last( 'Y'_ycp, 3 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 9 ), str.find_last( 'X'_ycp, 2 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 10 ), str.find_last( 'Y'_ycp, 2 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 11 ), str.find_last( 'X'_ycp, -2 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 12 ), str.find_last( 'Y'_ycp, -2 ), HString::npos + 0 );

	ENSURE_EQUALS( format( failed, 13 ), str.find_last( "A" ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 14 ), str.find_last( "X" ), 8 );
	ENSURE_EQUALS( format( failed, 15 ), str.find_last( "Y" ), 7 );
	ENSURE_EQUALS( format( failed, 16 ), str.find_last( "X", 100 ), 8 );
	ENSURE_EQUALS( format( failed, 17 ), str.find_last( "Y", 100 ), 7 );
	ENSURE_EQUALS( format( failed, 18 ), str.find_last( "X", 8 ), 8 );
	ENSURE_EQUALS( format( failed, 19 ), str.find_last( "Y", 8 ), 7 );
	ENSURE_EQUALS( format( failed, 20 ), str.find_last( "X", 5 ), 3 );
	ENSURE_EQUALS( format( failed, 21 ), str.find_last( "Y", 5 ), 4 );
	ENSURE_EQUALS( format( failed, 22 ), str.find_last( "X", 3 ), 3 );
	ENSURE_EQUALS( format( failed, 23 ), str.find_last( "Y", 3 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 24 ), str.find_last( "X", 2 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 25 ), str.find_last( "Y", 2 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 26 ), str.find_last( "X", -2 ), HString::npos + 0 );
	ENSURE_EQUALS( format( failed, 27 ), str.find_last( "Y", -2 ), HString::npos + 0 );
	static char const* const PREF = "---> group: ";
	static char const* const SUFF = "yaal, tra la la";
	HString line( PREF );
	line += SUFF;
	ENSURE_EQUALS( format( failed, 28 ), line.find_last( PREF ), 0 );
	ENSURE_EQUALS( format( failed, 29 ), line.find_last( SUFF ), 12 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_one_of" )
	HString str = "abcXYdeYXf";
	char failed[] = "find_one_of failed";
	ENSURE_EQUALS( failed, str.find_one_of( "ABCD" ), -1 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB" ), 3 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD" ), 4 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", -10 ), 3 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", -10 ), 4 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", 3 ), 3 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", 3 ), 4 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", 5 ), 7 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", 5 ), 7 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", 9 ), -1 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", 9 ), -1 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", 90 ), -1 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_other_than" )
	HString str = "abcXYdeYXfg";
	char failed[] = "find_other_than failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.find_other_than( "abcXYdeYXfg" ), -1 );
	ENSURE_EQUALS( format( failed, 1 ), str.find_other_than( "abXYdeYXfg" ), 2 );
	ENSURE_EQUALS( format( failed, 2 ), str.find_other_than( "abXYdeYXfg", 2 ), 2 );
	ENSURE_EQUALS( format( failed, 3 ), str.find_other_than( "abXYdeYXfg", 3 ), -1 );
	ENSURE_EQUALS( format( failed, 4 ), str.find_other_than( "abcdefg" ), 3 );
	ENSURE_EQUALS( format( failed, 5 ), str.find_other_than( "abcdefg", 5 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse_find" )
	HString str = "fXYedYXcba";
	char failed[] = "reverse_find failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.reverse_find( 'A'_ycp ), -1 );
	ENSURE_EQUALS( format( failed, 1 ), str.reverse_find( 'X'_ycp ), 3 );
	ENSURE_EQUALS( format( failed, 2 ), str.reverse_find( 'Y'_ycp ), 4 );
	ENSURE_EQUALS( format( failed, 3 ), str.reverse_find( 'X'_ycp, -10 ), 3 );
	ENSURE_EQUALS( format( failed, 4 ), str.reverse_find( 'Y'_ycp, -10 ), 4 );
	ENSURE_EQUALS( format( failed, 5 ), str.reverse_find( 'X'_ycp, 3 ), 3 );
	ENSURE_EQUALS( format( failed, 6 ), str.reverse_find( 'Y'_ycp, 3 ), 4 );
	ENSURE_EQUALS( format( failed, 7 ), str.reverse_find( 'X'_ycp, 5 ), 8 );
	ENSURE_EQUALS( format( failed, 8 ), str.reverse_find( 'Y'_ycp, 5 ), 7 );
	ENSURE_EQUALS( format( failed, 9 ), str.reverse_find( 'X'_ycp, 9 ), -1 );
	ENSURE_EQUALS( format( failed, 10 ), str.reverse_find( 'Y'_ycp, 9 ), -1 );
	ENSURE_EQUALS( format( failed, 11 ), str.reverse_find( 'X'_ycp, 90 ), -1 );
	ENSURE_EQUALS( format( failed, 12 ), str.reverse_find( 'Y'_ycp, 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse_find_one_of" )
	HString str = "fXYedYXcba";
	char failed[] = "reverse_find_one_of failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.reverse_find_one_of( "ABCD" ), -1 );
	ENSURE_EQUALS( format( failed, 1 ), str.reverse_find_one_of( "AXYB" ), 3 );
	ENSURE_EQUALS( format( failed, 2 ), str.reverse_find_one_of( "AYD" ), 4 );
	ENSURE_EQUALS( format( failed, 3 ), str.reverse_find_one_of( "AXYB", -10 ), 3 );
	ENSURE_EQUALS( format( failed, 4 ), str.reverse_find_one_of( "AYD", -10 ), 4 );
	ENSURE_EQUALS( format( failed, 5 ), str.reverse_find_one_of( "AXYB", 3 ), 3 );
	ENSURE_EQUALS( format( failed, 6 ), str.reverse_find_one_of( "AYD", 3 ), 4 );
	ENSURE_EQUALS( format( failed, 7 ), str.reverse_find_one_of( "AXYB", 5 ), 7 );
	ENSURE_EQUALS( format( failed, 8 ), str.reverse_find_one_of( "AYD", 5 ), 7 );
	ENSURE_EQUALS( format( failed, 9 ), str.reverse_find_one_of( "AXYB", 9 ), -1 );
	ENSURE_EQUALS( format( failed, 10 ), str.reverse_find_one_of( "AYD", 9 ), -1 );
	ENSURE_EQUALS( format( failed, 11 ), str.reverse_find_one_of( "AXYB", 90 ), -1 );
	ENSURE_EQUALS( format( failed, 12 ), str.reverse_find_one_of( "AYD", 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse_find_other_than" )
	HString str = "gfXYedYXcba";
	char failed[] = "reverse_find_other_than failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.reverse_find_other_than( "abcXYdeYXfg" ), -1 );
	ENSURE_EQUALS( format( failed, 1 ), str.reverse_find_other_than( "abXYdeYXfg" ), 2 );
	ENSURE_EQUALS( format( failed, 2 ), str.reverse_find_other_than( "abXYdeYXfg", 2 ), 2 );
	ENSURE_EQUALS( format( failed, 3 ), str.reverse_find_other_than( "abXYdeYXfg", 3 ), -1 );
	ENSURE_EQUALS( format( failed, 4 ), str.reverse_find_other_than( "abcdefg" ), 3 );
	ENSURE_EQUALS( format( failed, 5 ), str.reverse_find_other_than( "abcdefg", 5 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_last" )
	HString str = "fXYedYXcba";
	char failed[] = "find_last failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.find_last( 'A'_ycp ), -1 );
	ENSURE_EQUALS( format( failed, 1 ), str.find_last( 'X'_ycp ), 6 );
	ENSURE_EQUALS( format( failed, 2 ), str.find_last( 'Y'_ycp ), 5 );
	ENSURE_EQUALS( format( failed, 3 ), str.find_last( 'X'_ycp, -10 ), -1 );
	ENSURE_EQUALS( format( failed, 4 ), str.find_last( 'Y'_ycp, -10 ), -1 );
	ENSURE_EQUALS( format( failed, 5 ), str.find_last( 'X'_ycp, 3 ), 1 );
	ENSURE_EQUALS( format( failed, 6 ), str.find_last( 'Y'_ycp, 3 ), 2 );
	ENSURE_EQUALS( format( failed, 7 ), str.find_last( 'X'_ycp, 5 ), 1 );
	ENSURE_EQUALS( format( failed, 8 ), str.find_last( 'Y'_ycp, 5 ), 5 );
	ENSURE_EQUALS( format( failed, 9 ), str.find_last( 'X'_ycp, 6 ), 6 );
	ENSURE_EQUALS( format( failed, 9 ), str.find_last( 'X'_ycp, 9 ), 6 );
	ENSURE_EQUALS( format( failed, 10 ), str.find_last( 'Y'_ycp, 9 ), 5 );
	ENSURE_EQUALS( format( failed, 11 ), str.find_last( 'X'_ycp, 90 ), 6 );
	ENSURE_EQUALS( format( failed, 12 ), str.find_last( 'Y'_ycp, 90 ), 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_last_one_of" )
	HString str = "fXYedYXcba";
	char failed[] = "find_last_one_of failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.find_last_one_of( "ABCD" ), -1 );
	ENSURE_EQUALS( format( failed, 1 ), str.find_last_one_of( "AXYB" ), 6 );
	ENSURE_EQUALS( format( failed, 2 ), str.find_last_one_of( "AYD" ), 5 );
	ENSURE_EQUALS( format( failed, 3 ), str.find_last_one_of( "AXYB", -10 ), -1 );
	ENSURE_EQUALS( format( failed, 4 ), str.find_last_one_of( "AYD", -10 ), -1 );
	ENSURE_EQUALS( format( failed, 5 ), str.find_last_one_of( "AXYB", 3 ), 2 );
	ENSURE_EQUALS( format( failed, 6 ), str.find_last_one_of( "AXB", 3 ), 1 );
	ENSURE_EQUALS( format( failed, 7 ), str.find_last_one_of( "AYD", 3 ), 2 );
	ENSURE_EQUALS( format( failed, 8 ), str.find_last_one_of( "AXYB", 5 ), 5 );
	ENSURE_EQUALS( format( failed, 9 ), str.find_last_one_of( "AXB", 5 ), 1 );
	ENSURE_EQUALS( format( failed, 10 ), str.find_last_one_of( "AYD", 5 ), 5 );
	ENSURE_EQUALS( format( failed, 11 ), str.find_last_one_of( "AXYB", 9 ), 6 );
	ENSURE_EQUALS( format( failed, 12 ), str.find_last_one_of( "AYD", 9 ), 5 );
	ENSURE_EQUALS( format( failed, 13 ), str.find_last_one_of( "AXYB", 90 ), 6 );
	ENSURE_EQUALS( format( failed, 14 ), str.find_last_one_of( "AYD", 90 ), 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_last_other_than" )
	HString str = "gfXYedYXcba";
	char failed[] = "find_last_other_than failed[%d]";
	ENSURE_EQUALS( format( failed, 0 ), str.find_last_other_than( "abcXYdeYXfg" ), -1 );
	ENSURE_EQUALS( format( failed, 1 ), str.find_last_other_than( "abXYdeYXfg" ), 8 );
	ENSURE_EQUALS( format( failed, 2 ), str.find_last_other_than( "abXYdeYXfg", 2 ), -1 );
	ENSURE_EQUALS( format( failed, 3 ), str.find_last_other_than( "abXYdeYXfg", 7 ), -1 );
	ENSURE_EQUALS( format( failed, 4 ), str.find_last_other_than( "abXYdeYXfg", 8 ), 8 );
	ENSURE_EQUALS( format( failed, 5 ), str.find_last_other_than( "abXYdeYXfg", 100 ), 8 );
	ENSURE_EQUALS( format( failed, 6 ), str.find_last_other_than( "abcdefg" ), 7 );
	ENSURE_EQUALS( format( failed, 7 ), str.find_last_other_than( "abcdefg", 1 ), -1 );
	ENSURE_EQUALS( format( failed, 8 ), str.find_last_other_than( "abcdefg", 2 ), 2 );
	ENSURE_EQUALS( format( failed, 9 ), str.find_last_other_than( "abcdefg", 3 ), 3 );
	ENSURE_EQUALS( format( failed, 10 ), str.find_last_other_than( "abcdefg", 4 ), 3 );
	ENSURE_EQUALS( format( failed, 11 ), str.find_last_other_than( "abcdefg", 5 ), 3 );
	ENSURE_EQUALS( format( failed, 12 ), str.find_last_other_than( "abcdefg", 6 ), 6 );
	ENSURE_EQUALS( format( failed, 13 ), str.find_last_other_than( "abcdefg", 7 ), 7 );
	ENSURE_EQUALS( format( failed, 14 ), str.find_last_other_than( "abcdefg", 8 ), 7 );
TUT_TEARDOWN()

namespace {

static int const SAMPLE_SIZE = 128;

int find_substr_raw( char const* const str, int size, char const* const pat, int len ) {
	char fastpat[SAMPLE_SIZE + 1];
	len = min( len, SAMPLE_SIZE );
	strncpy( fastpat, pat, static_cast<size_t>( len ) );
	fastpat[len] = 0;
	char const* p = ( len <= size ) ? strstr( str, fastpat ) : nullptr;
	return ( p ? static_cast<int>( p - str ) : -1 );
}

}

struct gen_char {
	distribution::HDiscrete _rnd;
	gen_char( void )
		: _rnd( rng_helper::make_random_number_generator( 1 + 'z' - 'a' ) )
		{ }
	char operator()( void )
		{ return ( static_cast<char>( _rnd() + 'a' ) ); }
};

TUT_UNIT_TEST( "find(\"\")" )
	char sample[ SAMPLE_SIZE + 1 ];
	sample[ SAMPLE_SIZE ] = 0;
	yaal::generate( sample, sample + SAMPLE_SIZE, gen_char() );
	yaal::copy( sample, sample + SAMPLE_SIZE, stream_iterator( clog ) ); clog << endl;
	HString str( sample );
	HString msg;
	for ( int len = 1; len < SAMPLE_SIZE; ++ len ) {
		for ( int offset = 0; offset < SAMPLE_SIZE; ++ offset ) {
			int where = -1;
			do {
				int newWhere = ( ( len + offset ) <= SAMPLE_SIZE ) ? find_substr_raw( sample + where + 1,
						SAMPLE_SIZE - ( where + 1 ), sample + offset, len ) : -1;
				if ( newWhere >= 0 ) {
					newWhere += ( where + 1 );
				}
				msg = format( "find(\"\") failed: %d,%d,%d", len, offset, where );
				ENSURE_EQUALS( msg,
						where = ( offset + len <= SAMPLE_SIZE ) ? static_cast<int>( str.find( HString( sample + offset, len ), where + 1 ) ) : -1,
						newWhere );
			} while ( where >= 0 );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "compare()" )
	ENSURE_EQUALS( "\"abcdefghijklmnopqrstuvwxyz\".compare(0, 3, \"abc\")", "abcdefghijklmnopqrstuvwxyz"_ys.compare( 0, 3, "abc" ), 0 );
	ENSURE_EQUALS( "\"abcdefghijklmnopqrstuvwxyz\".compare(0, 3, \"abd\")", "abcdefghijklmnopqrstuvwxyz"_ys.compare( 0, 3, "abd" ), -1 );
	ENSURE_EQUALS( "\"abcdefghijklmnopqrstuvwxyz\".compare(0, 3, \"abb\")", "abcdefghijklmnopqrstuvwxyz"_ys.compare( 0, 3, "abb" ), 1 );
	ENSURE_EQUALS( "\"abcdefghijklmnopqrstuvwxyz\".compare(0, 3, \"abc\")", "abcdefghijklmnopqrstuvwxyz"_ys.compare( 0, 4, "abc" ), 1 );
	ENSURE_EQUALS( "\"abcdefghijklmnopqrstuvwxyz\".compare(0, 3, \"abc\")", "abcdefghijklmnopqrstuvwxyz"_ys.compare( "abc" ), 1 );
	ENSURE_EQUALS( "\"abc\".compare(\"abcdefghijklmnopqrstuvwxyz\", 0, 3)", "abc"_ys.compare( "abcdefghijklmnopqrstuvwxyz", 0, 3 ), 0 );
	ENSURE_EQUALS( "\"abc\".compare(\"abcdefghijklmnopqrstuvwxyz\", 0, 3)", "abb"_ys.compare( "abcdefghijklmnopqrstuvwxyz", 0, 3 ), -1 );
	ENSURE_EQUALS( "\"abc\".compare(\"abcdefghijklmnopqrstuvwxyz\", 0, 3)", "abd"_ys.compare( "abcdefghijklmnopqrstuvwxyz", 0, 3 ), 1 );
	ENSURE_EQUALS( "\"abc\".compare(\"abcdefghijklmnopqrstuvwxyz\", 0, 3)", "abc"_ys.compare( "abcdefghijklmnopqrstuvwxyz", 0, 4 ), -1 );
	ENSURE_EQUALS( "\"abc\".compare(\"abcdefghijklmnopqrstuvwxyz\", 0, 3)", "abc"_ys.compare( "abcdefghijklmnopqrstuvwxyz" ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "starts_with()" )
	ENSURE( "positive failed", "Ala ma kota"_ys.starts_with( "Ala" ) );
	ENSURE( "positive eq failed", "Ala"_ys.starts_with( "Ala" ) );
	ENSURE_NOT( "negative failed", "Ala ma kota"_ys.starts_with( "Ola" ) );
	ENSURE_NOT( "negative eq len failed", "Ala"_ys.starts_with( "Ola" ) );
	ENSURE_NOT( "negative failed", "Ala"_ys.starts_with( "Ala ma kota" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ends_with()" )
	ENSURE( "positive failed", "Ala ma kota"_ys.ends_with( "kota" ) );
	ENSURE( "positive eq failed", "Ala"_ys.ends_with( "Ala" ) );
	ENSURE_NOT( "negative failed", "Ala ma kota"_ys.ends_with( "psa" ) );
	ENSURE_NOT( "negative eq len failed", "Ala"_ys.ends_with( "Ola" ) );
	ENSURE_NOT( "negative failed", "kota"_ys.ends_with( "Ala ma kota" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "trim_left(\"\")" )
	static char const* const SPACE = "   ";
	static HString const TEXT = "ala ma";
	static char const* const FINE = "1234";
	HString str( SPACE + TEXT );
	ENSURE_EQUALS( "trim failed", str.trim_left(), str );
	HString fine( FINE );
	ENSURE_EQUALS( "trim failed", fine.trim_left(), fine );
	HString space( SPACE );
	ENSURE_EQUALS( "trim failed", space.trim_left(), "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "trim_right(\"\")" )
	static char const* const SPACE = "   ";
	static HString const TEXT = "ala ma";
	static char const* const FINE = "1234";
	HString str( TEXT + SPACE );
	ENSURE_EQUALS( "trim 0 failed", str.trim_right(), str );
	HString fine( FINE );
	ENSURE_EQUALS( "trim 1 failed", fine.trim_right(), fine );
	HString space( SPACE );
	ENSURE_EQUALS( "trim 2 failed", space.trim_right(), "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reserve( size )" )
	HString str;
	ENSURE_EQUALS( "bad capacity on never-used empty string", str.get_capacity(), MIN_CAPACITY );
	str.reserve( 1 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 1, MIN_CAPACITY ) );
	str.reserve( 2 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 2, MIN_CAPACITY ) );
	str.reserve( 3 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 3, MIN_CAPACITY ) );
	str.reserve( 5 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 6, MIN_CAPACITY ) );
	str.reserve( 7 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 8, MIN_CAPACITY ) );
	str.reserve( 10 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), MIN_CAPACITY );
	str.reserve( MIN_CAPACITY - 1 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), MIN_CAPACITY );
	str.reserve( MIN_CAPACITY );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), MIN_CAPACITY );
	str.reserve( MIN_CAPACITY + 1 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), ( MIN_CAPACITY <= 16 ? 16 : 32 ) );
	str.reserve( 100 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), 128 );
	str.reserve( 50 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), 128 );
	ENSURE_THROW( "absurd reallocation size allowed", str.reserve( -1 ), HStringException );
	ENSURE_THROW( "huge (too big) reallocation size allowed", str.reserve( str.get_max_size() + 2 ), HStringException );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_max_size(), str.max_size() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assign( HString ... )" )
	static char const ss[] = "Ala ma kota.";
	HString source( ss );
	HString dest( "dummy" );
	char const err[] = "assign failed";
	dest = source;
	ENSURE_EQUALS( err, dest.assign( source, 0, 0 ), "" );
	dest = source;
	ENSURE_EQUALS( err, dest.assign( source, source.get_length() * 2, source.get_length() ), "" );
	ENSURE_EQUALS( err, dest.assign( source, 0, HString::MAX_STRING_LENGTH ), source );
	ENSURE_EQUALS( err, dest.assign( source, 0, 5 ), "Ala m" );
	ENSURE_EQUALS( err, dest.assign( source, 4, 5 ), "ma ko" );
	ENSURE_EQUALS( err, dest.assign( source, 7, 5 ), "kota." );
	ENSURE_EQUALS( err, dest.assign( source, 8, 5 ), "ota." );
	ENSURE_EQUALS( err, dest.assign( source, static_cast<int>( sizeof ( ss ) ) - 2, 5 ), "." );
	ENSURE_EQUALS( err, dest.assign( source, static_cast<int>( sizeof ( ss ) ) - 1, 5 ), "" );
	ENSURE_EQUALS( err, dest.assign( source, static_cast<int>( sizeof ( ss ) ), 5 ), "" );
	ENSURE_EQUALS( err, dest.assign( source.begin() + 3, source.begin() + static_cast<int>( sizeof ( ss ) ) - 4 ), " ma ko" );
	ENSURE_THROW( "assign with negative offset succeeded", dest.assign( source, -1, 2 ), HStringException );
	ENSURE_THROW( "assign with negative lenght succeeded", dest.assign( source, 0, -2 ), HStringException );
	ENSURE_THROW( "assign with negative lenght succeeded", dest.assign( source, -2 ), HStringException );
	ENSURE_THROW( "assign with null data succeeded", dest.assign( static_cast<char const*>( nullptr), 0l ), HStringException );
	ENSURE_THROW( "assign with negative lenght succeeded", dest.assign( -2, ' '_ycp ), HStringException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "fill()" )
	HString s( 16, 0_ycp );
	s.fill( '0'_ycp, 0, 16 );
	ENSURE_EQUALS( "bad lenght", s.get_length(), 16 );
	ENSURE_EQUALS( "bad content", s, "0000000000000000" );
	s.fill( 'x'_ycp, 4, 8 );
	ENSURE_EQUALS( "bad lenght", s.get_length(), 16 );
	ENSURE_EQUALS( "bad content", s, "0000xxxxxxxx0000" );
	ENSURE_THROW( "bad len succeeded", s.fill( 'x'_ycp, 0, -2 ), HStringException );
	ENSURE_THROW( "bad offset succeeded", s.fill( 'x'_ycp, -1, 1 ), HStringException );
	ENSURE_THROW( "bad offset succeeded", s.fill( 'x'_ycp, 17, 1 ), HStringException );
	s.fill( 'y'_ycp, 16, 4 );
	ENSURE_EQUALS( "bad lenght", s.get_length(), 20 );
	ENSURE_EQUALS( "bad content", s, "0000xxxxxxxx0000yyyy" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "fillz()" )
	HString s( 16, 0_ycp );
	s.fillz( '0'_ycp, 0, 16 );
	ENSURE_EQUALS( "bad lenght", s.get_length(), 16 );
	ENSURE_EQUALS( "bad content", s, "0000000000000000" );
	s.fillz( 'x'_ycp, 4, 8 );
	ENSURE_EQUALS( "bad lenght", s.get_length(), 12 );
	ENSURE_EQUALS( "bad content", s, "0000xxxxxxxx" );
	s.fillz( 'y'_ycp, 8 );
	ENSURE_EQUALS( "bad lenght", s.get_length(), 12 );
	ENSURE_EQUALS( "bad content", s, "0000xxxxyyyy" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "replace(pos, len, str)" )
	HString s( "Ala ma kota." );
	int long origLen( s.get_length() );
	TUT_EVAL( s.replace( 7, 4, "psa" ) );
	ENSURE_EQUALS( "bad lenght", s.get_length(), origLen - 1 );
	ENSURE_EQUALS( "bad content", s, "Ala ma psa." );
	HString uri( "%4f%6b" );
	char c( 'O' );
	uri.replace( 0, 3, &c, 1 );
	c = 'k';
	uri.replace( 1, 3, &c, 1 );
	ENSURE_EQUALS( "replace( pos, len, to, to_len ) failed", uri, "Ok" );
	ENSURE_THROW( "bad size in replace accepted", uri.replace( 0, 3, &c, 1 ), HStringException );
	s.replace( s.begin() + 7, s.begin() + 10, to_string( "kota" ) );
	ENSURE_EQUALS( "bad content", s, "Ala ma kota." );
	ENSURE_THROW( "bad cur size in replace accepted", uri.replace( 0, -1, &c, 1 ), HStringException );
	ENSURE_THROW( "bad new size in replace accepted", uri.replace( 0, 1, &c, -1 ), HStringException );
	ENSURE_THROW( "bad pos in replace accepted", uri.replace( -1, 1, &c, 1 ), HStringException );
	ENSURE_THROW( "bad offset in replace accepted", uri.replace( 0, 1, "aaa"_ys, -1, 1 ), HStringException );
	HString pies( "psXXX" );
	s.replace( 7, 3, pies, 0, 2 );
	ENSURE_EQUALS( "bad content", s, "Ala ma psa." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse" )
	HString s( "aBeCaDlO" );
	s.reverse();
	ENSURE_EQUALS( "reverse failed", s, "AbEcAdLo" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "append( HString ... )" )
	static char const ss[] = "Ala ma kota.";
	HString source( ss );
	HString dest( "dummy" );
	char const err[] = "append failed";
	ENSURE_EQUALS( err, dest.append( source, 0, 0 ), "dummy" );
	ENSURE_THROW( "append with anormous offset succeeded", dest.append( source, source.get_length() * 2, source.get_length() ), HStringException );
	ENSURE_EQUALS( err, dest.append( source, 0, HString::MAX_STRING_LENGTH ), "dummy" + source );
	ENSURE_EQUALS( err, dest.append( source, 0, 5 ), "dummy" + source + "Ala m" );
	ENSURE_EQUALS( err, dest.append( source, 4, 5 ), "dummy" + source + "Ala mma ko" );
	ENSURE_EQUALS( err, dest.append( source, 7, 5 ), "dummy" + source + "Ala mma kokota." );
	ENSURE_EQUALS( err, dest.append( source, 8, 5 ), "dummy" + source + "Ala mma kokota.ota." );
	ENSURE_EQUALS( err, dest.append( source, static_cast<int>( sizeof ( ss ) ) - 2, 5 ), "dummy" + source + "Ala mma kokota.ota.." );
	ENSURE_EQUALS( err, dest.append( source, static_cast<int>( sizeof ( ss ) ) - 1, 5 ), "dummy" + source + "Ala mma kokota.ota.." );
	ENSURE_THROW( "append with off by one offset succeeded", dest.append( source, static_cast<int>( sizeof ( ss ) ), 5 ), HStringException );
	ENSURE_EQUALS( err, dest.append( source.begin() + 3, source.begin() + static_cast<int>( sizeof ( ss ) ) - 4 ), "dummy" + source + "Ala mma kokota.ota.. ma ko" );
	ENSURE_EQUALS( err, dest.append( source, 9 ), "dummy" + source + "Ala mma kokota.ota.. ma kota." );
	ENSURE_THROW( "append with negative offset succeeded", dest.append( source, -1, 2 ), HStringException );
	ENSURE_THROW( "append with negative lenght succeeded", dest.append( source, 0, -2 ), HStringException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap()" )
	/* Short must be shorter than 10 bytes. */
	static int const SHORT_LIMIT( 10 );
	char const ALA[] = "Ala";
	char const PIES[] = "pies";
	HString a( ALA );
	ENSURE( "bad test setup ALA", a.get_length() < SHORT_LIMIT );
	HString b( PIES );
	ENSURE( "bad test setup PIES", b.get_length() < SHORT_LIMIT );
	/* Long must be longer than 24 bytes. */
	static int const LONG_LIMIT( 24 );
	char const YAAL[] = "Yet Another Abstraction Layer";
	char const PI_E[] = "3.141592653589793+2.718281828459045";
	HString c( YAAL );
	ENSURE( "bad test setup YAAL", c.get_length() > LONG_LIMIT );
	HString d( PI_E );
	ENSURE( "bad test setup PI_E", d.get_length() > LONG_LIMIT );

	a.swap( b );
	ENSURE_EQUALS( "swap 1 failed", a, PIES );
	ENSURE_EQUALS( "swap 1 failed", b, ALA );

	c.swap( d );
	ENSURE_EQUALS( "swap 2 failed", c, PI_E );
	ENSURE_EQUALS( "swap 2 failed", d, YAAL );

	a.swap( c );
	ENSURE_EQUALS( "swap 3 failed", a, PI_E );
	ENSURE_EQUALS( "swap 3 failed", c, PIES );
TUT_TEARDOWN()

TUT_UNIT_TEST( "push_back" )
	HString s;
	ENSURE_EQUALS( "bad empty", s, "" );
	s.push_back( 'A'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "A" );
	s.push_back( 'l'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Al" );
	s.push_back( 'a'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala" );
	s.push_back( ' '_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala " );
	s.push_back( 'm'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala m" );
	s.push_back( 'a'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala ma" );
	s.push_back( ' '_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala ma " );
	s.push_back( 'k'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala ma k" );
	s.push_back( 'o'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala ma ko" );
	s.push_back( 't'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala ma kot" );
	s.push_back( 'a'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala ma kota" );
	s.push_back( '.'_ycp );
	ENSURE_EQUALS( "push_back failed", s, "Ala ma kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "pop_back" )
	HString s( "Ala ma kota." );
	ENSURE_EQUALS( "initialization failed", s, "Ala ma kota." );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala ma kota" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala ma kot" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala ma ko" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala ma k" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala ma " );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala ma" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala m" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala " );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Ala" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "Al" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "A" );
	s.pop_back();
	ENSURE_EQUALS( "pop_back failed", s, "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "cmp opers (left literal)" )
	ENSURE( "!= failed", "000" != "001"_ys );
	ENSURE_NOT( "!= failed", "000" != "000"_ys );
	ENSURE( ">= failed", "001" >= "000"_ys );
	ENSURE( ">= failed", "001" >= "001"_ys );
	ENSURE_NOT( ">= failed", "000" >= "001"_ys );
	ENSURE( "<= failed", "000" <= "001"_ys );
	ENSURE( "<= failed", "001" <= "001"_ys );
	ENSURE_NOT( "<= failed", "001" <= "000"_ys );
	ENSURE( "> failed", "001" > "000"_ys );
	ENSURE_NOT( "> failed", "001" > "001"_ys );
	ENSURE( "< failed", "000" < "001"_ys );
	ENSURE_NOT( "< failed", "001" < "001"_ys );
TUT_TEARDOWN()

TUT_UNIT_TEST( "conversions" )
	ENSURE_EQUALS( "to_string void_p failed", to_string( static_cast<void*>( nullptr ) ), "0x0" );
	ENSURE_EQUALS( "to_string double failed", to_string( 3.141592 ), "3.141592" );
	ENSURE_EQUALS( "to_string float failed", to_string( 2.718281f ), "2.718281" );
	ENSURE_EQUALS( "to_string int long long unsigned failed", to_string( 1234567890123456789ULL ), "1234567890123456789" );
	ENSURE_EQUALS( "to_string int long unsigned failed", to_string( 4234567890UL ), "4234567890" );
	ENSURE_EQUALS( "to_string int unsigned failed", to_string( 4234567890U ), "4234567890" );
	ENSURE_EQUALS( "to_string int short failed", to_string( static_cast<int short>( 32145 ) ), "32145" );
	ENSURE_EQUALS( "to_string int short unsigned failed", to_string( static_cast<int short unsigned>( 54321 ) ), "54321" );
	ENSURE_EQUALS( "to_string char unsigned failed", to_string( static_cast<char unsigned>( u'ó' ) ), "ó" );
	ENSURE_EQUALS( "stoi failed", stoi( "-2147483647"_ys ), -2147483647 );
	ENSURE_EQUALS( "stoi failed", stoi( "123_456"_ys ), 123 );
	ENSURE_EQUALS( "stoi failed", stoi( "-7FFFFFFF"_ys, nullptr, 16 ), -2147483647 );
	ENSURE_THROW( "stoi overflow succeeded", stoi( "2147483648" ), HOutOfRangeException );
#if SIZEOF_INT_LONG == 8
	ENSURE_EQUALS( "stol failed", stol( "-9223372036854775807"_ys ), -9223372036854775807L );
	ENSURE_EQUALS( "stol failed", stol( "-7FFFFFFFFFFFFFFF"_ys, nullptr, 16 ), -9223372036854775807L );
	ENSURE_THROW( "stol overflow succeeded", stol( "9223372036854775808"_ys ), HOutOfRangeException );
	/* unsigned */
	ENSURE_EQUALS( "stoul failed", stoul( "18446744073709551615"_ys ), 18446744073709551615UL );
	ENSURE_EQUALS( "stoul failed", stoul( "FFFFFFFFFFFFFFFF"_ys, nullptr, 16 ), 18446744073709551615UL );
	ENSURE_THROW( "stoul overflow succeeded", stoul( "18446744073709551616"_ys ), HOutOfRangeException );
#else
	ENSURE_EQUALS( "stol failed", stol( "-2147483647"_ys ), -2147483647L );
	ENSURE_EQUALS( "stol failed", stol( "-7FFFFFFF"_ys, nullptr, 16 ), -2147483647L );
	ENSURE_THROW( "stol overflow succeeded", stol( "2147483648"_ys ), HOutOfRangeException );
	/* unsigned */
	ENSURE_EQUALS( "stoul failed", stoul( "4294967295"_ys ), 4294967295UL );
	ENSURE_EQUALS( "stoul failed", stoul( "FFFFFFFF"_ys, nullptr, 16 ), 4294967295UL );
	ENSURE_THROW( "stoul overflow succeeded", stoul( "4294967296"_ys ), HOutOfRangeException );
#endif
	ENSURE_EQUALS( "stoll failed", stoll( "-9223372036854775807"_ys ), -9223372036854775807LL );
	ENSURE_EQUALS( "stoll failed", stoll( "-7FFFFFFFFFFFFFFF"_ys, nullptr, 16 ), -9223372036854775807LL );
	ENSURE_THROW( "stoll overflow succeeded", stoll( "9223372036854775808"_ys ), HOutOfRangeException );
	ENSURE_THROW( "stoll on invalid succeeded", stoll( " kotek"_ys ), HInvalidArgumentException );
	int end( 0 );
	ENSURE_EQUALS( "stoll failed", stoll( "-12345678abcdefgh"_ys, &end, 10 ), -12345678LL );
	ENSURE_EQUALS( "stoll end failed", end, 9 );
	ENSURE_EQUALS( "stoll failed", stoll( "-12345678abcdefgh"_ys, &end, 16 ), -0x12345678abcdefLL );
	ENSURE_EQUALS( "stoll end failed", end, 15 );
	/* unsigned */
	ENSURE_EQUALS( "stoull failed", stoull( "18446744073709551615"_ys ), 18446744073709551615ULL );
	ENSURE_EQUALS( "stoull failed", stoull( "FFFFFFFFFFFFFFFF"_ys, nullptr, 16 ), 18446744073709551615ULL );
	ENSURE_EQUALS( "stoull failed", stoull( "12345678abcdefgh"_ys, &end, 10 ), 12345678ULL );
	ENSURE_EQUALS( "stoull end failed", end, 8 );
	ENSURE_EQUALS( "stoull failed", stoull( "12345678abcdefgh"_ys, &end, 16 ), 0x12345678abcdefULL );
	ENSURE_EQUALS( "stoull end failed", end, 14 );
	ENSURE_THROW( "stoull overflow succeeded", stoull( "18446744073709551616"_ys ), HOutOfRangeException );
	ENSURE_THROW( "stoll on invalid succeeded", stoull( " kotek"_ys ), HInvalidArgumentException );
	ENSURE_DISTANCE( "stof failed", stof( "3.141592"_ys ), 3.141592f, static_cast<float>( epsilon ) );
	ENSURE_DISTANCE( "stod failed", stod( "3.1415926535"_ys ), 3.1415926535, static_cast<double>( epsilon ) );
	ENSURE_DISTANCE( "stold failed", stold( "2.718281828459045"_ys ), 2.718281828459045L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "character classes" )
	ENSURE( "is_whitespace failed", is_whitespace( ' '_ycp ) && is_whitespace( '\t'_ycp ) && is_whitespace( '\n'_ycp ) && is_whitespace( '\r'_ycp ) );
	ENSURE_NOT( "is_whitespace failed", is_whitespace( '_'_ycp ) || is_whitespace( '!'_ycp ) || is_whitespace( 'a'_ycp ) );

	ENSURE( "is_digit failed", is_digit( '0'_ycp ) && is_digit( '9'_ycp ) );
	ENSURE_NOT( "is_digit failed", is_digit( '0'_ycp - 1 ) || is_digit( '9'_ycp + 1 ) || is_digit( 'a'_ycp ) );

	ENSURE( "is_dec_digit failed", is_dec_digit( '0'_ycp ) && is_dec_digit( '9'_ycp ) );
	ENSURE_NOT( "is_dec_digit failed", is_dec_digit( '0'_ycp - 1 ) || is_dec_digit( '9'_ycp + 1 ) || is_dec_digit( 'a'_ycp ) );

	ENSURE(
		"is_hex_digit failed",
		is_hex_digit( '0'_ycp ) && is_hex_digit( '9'_ycp )
			&& is_hex_digit( 'a'_ycp ) && is_hex_digit( 'f'_ycp )
			&& is_hex_digit( 'A'_ycp ) && is_hex_digit( 'F'_ycp )
	);
	ENSURE_NOT(
		"is_hex_digit failed",
		is_hex_digit( '0'_ycp - 1 ) || is_hex_digit( '9'_ycp + 1 )
			|| is_hex_digit( 'a'_ycp - 1 ) || is_hex_digit( 'f'_ycp + 1 )
			|| is_hex_digit( 'A'_ycp - 1 ) || is_hex_digit( 'F'_ycp + 1 )
	);

	ENSURE( "is_oct_digit failed", is_oct_digit( '0'_ycp ) && is_oct_digit( '7'_ycp ) );
	ENSURE_NOT( "is_oct_digit failed", is_oct_digit( '0'_ycp - 1 ) || is_oct_digit( '7'_ycp + 1 ) || is_oct_digit( 'a'_ycp ) );

	ENSURE( "is_bin_digit failed", is_bin_digit( '0'_ycp ) && is_bin_digit( '1'_ycp ) );
	ENSURE_NOT( "is_bin_digit failed", is_bin_digit( '0'_ycp - 1 ) || is_bin_digit( '1'_ycp + 1 ) || is_bin_digit( 'a'_ycp ) );

	ENSURE( "is_letter failed", is_letter( 'a'_ycp ) && is_letter( 'z'_ycp ) && is_letter( 'A'_ycp ) && is_letter( 'Z'_ycp ) );
	ENSURE_NOT( "is_letter failed", is_letter( 'a'_ycp - 1 ) || is_letter( 'z'_ycp + 1 ) || is_letter( 'A'_ycp - 1 ) || is_letter( 'Z'_ycp + 1 ) );

	ENSURE( "is_lower failed", is_lower( 'a'_ycp ) && is_lower( 'z'_ycp ) );
	ENSURE_NOT( "is_lower failed", is_lower( 'a'_ycp - 1 ) || is_lower( 'z'_ycp + 1 ) || is_lower( 'A'_ycp ) || is_lower( 'Z'_ycp ) );

	ENSURE( "is_upper failed", is_upper( 'A'_ycp ) && is_upper( 'Z'_ycp ) );
	ENSURE_NOT( "is_upper failed", is_upper( 'a'_ycp ) || is_upper( 'z'_ycp ) || is_upper( 'A'_ycp - 1 ) || is_upper( 'Z'_ycp + 1 ) );

	ENSURE( "is_alpha failed", is_alpha( 'a'_ycp ) && is_alpha( 'z'_ycp ) && is_alpha( 'A'_ycp ) && is_alpha( 'Z'_ycp ) );
	ENSURE_NOT( "is_alpha failed", is_alpha( '\b'_ycp ) || is_alpha( '0'_ycp ) || is_alpha( '9'_ycp ) || is_alpha( '_'_ycp ) );

	ENSURE(
		"is_alnum failed",
		is_alnum( 'a'_ycp ) && is_alnum( 'z'_ycp ) && is_alnum( 'A'_ycp ) && is_alnum( 'Z'_ycp ) && is_alnum( '0'_ycp ) && is_alnum( '9'_ycp )
	);
	ENSURE_NOT(
		"is_alnum failed",
		is_alnum( 'a'_ycp - 1 ) || is_alnum( 'z'_ycp + 1 )
		|| is_alnum( 'A'_ycp - 1 ) || is_alnum( 'Z'_ycp + 1 )
		|| is_alnum( '0'_ycp - 1 ) || is_alnum( '9'_ycp + 1 )
		|| is_alnum( '\b'_ycp ) || is_alnum( '_'_ycp )
	);

	ENSURE(
		"is_ascii failed",
		is_ascii( 'a'_ycp ) && is_ascii( 'z'_ycp ) && is_ascii( 'A'_ycp ) && is_ascii( 'Z'_ycp )
		&& is_ascii( '\b'_ycp ) && is_ascii( '0'_ycp ) && is_ascii( '9'_ycp ) && is_ascii( '_'_ycp )
	);
	ENSURE_NOT( "is_ascii failed", is_ascii( L'ó'_ycp ) );

	ENSURE( "is_lower_greek failed", is_lower_greek( L'α'_ycp ) && is_lower_greek( L'ω'_ycp ) );
	ENSURE_NOT( "is_lower_greek failed", is_lower_greek( L'α'_ycp - 1 ) || is_lower_greek( L'ω'_ycp + 1 ) );

	ENSURE( "is_upper_greek failed", is_upper_greek( L'Α'_ycp ) && is_upper_greek( L'Ω'_ycp ) );
	ENSURE_NOT( "is_upper_greek failed", is_upper_greek( L'Α'_ycp - 1 ) || is_upper_greek( L'Ω'_ycp + 1 ) );

	ENSURE( "is_greek failed", is_greek( L'α'_ycp ) && is_greek( L'ω'_ycp ) && is_greek( L'Α'_ycp ) && is_greek( L'Ω'_ycp ) );
	ENSURE_NOT( "is_greek failed", is_greek( L'Α'_ycp - 1 ) || is_greek( L'ω'_ycp + 1 ) );

	ENSURE( "is_subscript failed", is_subscript( L'ₐ'_ycp ) && is_subscript( L'ₓ'_ycp ) && is_subscript( L'₀'_ycp ) && is_subscript( L'₉'_ycp ) );
	ENSURE_NOT( "is_subscript failed", is_subscript( L'a'_ycp ) || is_subscript( L'z'_ycp ) || is_subscript( '0'_ycp ) );

	ENSURE(
		"is_superscript failed",
		is_superscript( L'ᵃ'_ycp ) && is_superscript( L'ᶻ'_ycp )
		&& is_superscript( L'ᴬ'_ycp ) && is_superscript( L'ᵂ'_ycp )
		&& is_superscript( L'⁰'_ycp ) && is_superscript( L'⁹'_ycp )
	);
	ENSURE_NOT( "is_superscript failed", is_superscript( L'a'_ycp ) || is_superscript( L'z'_ycp ) || is_superscript( 'A'_ycp ) || is_superscript( '0'_ycp ) );
TUT_TEARDOWN()

}

