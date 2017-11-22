/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hllexecutingparser.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>
#include <cstring>

#include <yaal/hcore/hstack.hxx>
#include <yaal/tools/executingparser.hxx>
#include <yaal/tools/hhuginn.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::executing_parser;
using namespace tress::tut_helpers;
namespace e_p = executing_parser;

namespace ll {

template<typename container_t, typename value_type>
void pushbacker( container_t* container, value_type value ) {
	container->push_back( value );
}

template<typename container_t>
void pushbacker( container_t* container, yaal::hcore::HString const& value ) {
	container->push_back( lexical_cast<typename trait::strip_reference<typename container_t::value_type>::type >( value ) );
}

template<typename value_type, typename container_t>
HBoundCall<void ( value_type )> push_back( container_t& container ) {
	M_PROLOG
	return ( call( &pushbacker<container_t, value_type>, &container, _1 ) );
	M_EPILOG
}

template<typename container_t>
HBoundCall<void ( typename container_t::value_type const& )> push_back( container_t& container ) {
	M_PROLOG
	return ( call( &pushbacker<container_t, typename container_t::value_type const&>, &container, _1 ) );
	M_EPILOG
}

namespace {
void noop( void ) {
	return;
}
}

void match_position( executing_parser::position_t&, executing_parser::position_t );
void match_position( executing_parser::position_t& out_, executing_parser::position_t in_ ) {
	out_ = in_;
}

template<typename T>
void match_value_position_ref( T&, T const&, executing_parser::position_t&, executing_parser::position_t );
template<typename T>
void match_value_position_ref( T& valueOut_, T const& valueIn_, executing_parser::position_t& positionOut_, executing_parser::position_t positionIn_ ) {
	valueOut_ = valueIn_;
	positionOut_ = positionIn_;
	return;
}

template<typename T>
void match_value_position_val( T&, T, executing_parser::position_t&, executing_parser::position_t );
template<typename T>
void match_value_position_val( T& valueOut_, T valueIn_, executing_parser::position_t& positionOut_, executing_parser::position_t positionIn_ ) {
	valueOut_ = valueIn_;
	positionOut_ = positionIn_;
	return;
}

}

using namespace ll;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hllexecutingparser );
TUT_TEST_GROUP( tut_yaal_tools_hllexecutingparser, "yaal::tools::executing_parser" );

TUT_UNIT_TEST( "empty parser" )
	HRule r;
	ENSURE_THROW( "empty parser constructed", HExecutingParser ep( r ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Named rule name ends with underscore" )
	ENSURE_THROW( "explicit rule name with underscore at the end created", HRule r( "A_" ), HNamedRuleException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HReal" )
	/* action_t */ {
		bool actionCalled( false );
		HExecutingParser ep( real[HReal::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) )] );
		ENSURE( "HReal failed to parse correct input (double).", ep( "3.14" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* action_position_t */ {
		executing_parser::position_t pos( -1 );
		HExecutingParser ep( real[HReal::action_position_t( call( &match_position, ref( pos ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double).", ep( "3.14" ) );
		ep();
		ENSURE_EQUALS( "bad position from real's action", pos.get(), 0 );
	}
	/* double */ {
		double val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double )>( call( &defer<double>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double).", ep( "3.14" ) );
		ep();
		ENSURE_DISTANCE( "double value not set by ExecutingParser.", static_cast<double long>( val ), 3.14l, epsilon );
	}
	/* double_position_t */ {
		double val( 0 );
		executing_parser::position_t pos( -1 );
		HExecutingParser ep( real[HReal::action_double_position_t( call( &match_value_position_val<double>, ref( val ), _1, ref( pos ), _2 ) )] );
		ENSURE( "HReal failed to parse correct input (double).", ep( "3.14" ) );
		ep();
		ENSURE_DISTANCE( "double value not set by ExecutingParser.", static_cast<double long>( val ), 3.14l, epsilon );
		ENSURE_EQUALS( "bad position from real's action", pos.get(), 0 );
	}
	/* double long */ {
		double long val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double long )>( call( &defer<double long>::set, ref( val ), _1 ) )] );
		hcore::HString input( "3.14" );
		ENSURE( "HReal failed to parse correct input (double long).", ep( input.begin(), input.end() ) );
		ep();
		ENSURE_DISTANCE( "double long value not set by ExecutingParser.", val, 3.14l, epsilon );
	}
	/* double long short front */ {
		double long val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double long )>( call( &defer<double long>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double long).", ep( ".14" ) );
		ep();
		ENSURE_DISTANCE( "double long value not set by ExecutingParser.", val, .14l, epsilon );
	}
	/* double long short back */ {
		double long val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double long )>( call( &defer<double long>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double long).", ep( "3." ) );
		ep();
		ENSURE_DISTANCE( "double long value not set by ExecutingParser.", val, 3.l, epsilon );
	}
	/* HNumber */ {
		HNumber val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( HNumber const& )>( call( &defer<HNumber, HNumber const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HNumber).", ep( "3.141592653589793" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, "3.141592653589793" );
	}
	/* HNumber position */ {
		HNumber val( 0 );
		executing_parser::position_t pos( -1 );
		HExecutingParser ep( real[HReal::action_number_position_t( call( &match_value_position_ref<HNumber>, ref( val ), _1, ref( pos ), _2 ) )] );
		ENSURE( "HReal failed to parse correct input (HNumber).", ep( "3.141592653589793" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, "3.141592653589793" );
		ENSURE_EQUALS( "bad position from real's action", pos.get(), 0 );
	}
	/* HString */ {
		hcore::HString val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HString).", ep( "3.141592653589793" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "3.141592653589793" );
	}
	/* bad real */ {
		HExecutingParser ep( real );
		ENSURE_NOT( "Invalid input parsed by HReal", ep( "bad" ) );
		ENSURE_NOT( "Invalid input parsed by HReal", ep( "3.14bad" ) );
		ENSURE_NOT( "whitespace only input parsed by HReal", ep( " " ) );
		ENSURE_NOT( "empty input parsed by HReal", ep( "" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HInteger" )
	/* int */ {
		int val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int value not set by ExecutingParser.", val, 7 );
	}
	/* int too big */ {
		int val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HInteger failed to parse correct input (int).", ep( to_string( static_cast<int long long>( meta::max_signed<int>::value ) + 1LL ) ) );
	}
	/* int position */ {
		int val( 0 );
		executing_parser::position_t pos( -1 );
		HExecutingParser ep( integer[HInteger::action_int_position_t( call( &match_value_position_val<int>, ref( val ), _1, ref( pos ), _2 ) )] );
		ENSURE( "HInteger failed to parse correct input (int).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int value not set by ExecutingParser.", val, 7 );
		ENSURE_EQUALS( "bad position from int's action", pos.get(), 0 );
	}
	/* action_t */ {
		bool actionCalled( false );
		HExecutingParser ep( integer[HInteger::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) )] );
		ENSURE( "HReal failed to parse correct input (int).", ep( "7" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* action_position_t */ {
		executing_parser::position_t pos( -1 );
		HExecutingParser ep( integer[HInteger::action_position_t( call( &match_position, ref( pos ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "bad position from int's action", pos.get(), 0 );
	}
	/* int long */ {
		int long val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int long )>( call( &defer<int long>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int long).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int long value not set by ExecutingParser.", val, 7l );
	}
	/* int long position */ {
		int long val( 0 );
		executing_parser::position_t pos( -1 );
		HExecutingParser ep( integer[HInteger::action_int_long_position_t( call( &match_value_position_val<int long>, ref( val ), _1, ref( pos ), _2 ) )] );
		ENSURE( "HInteger failed to parse correct input (int long).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int long value not set by ExecutingParser.", val, 7l );
		ENSURE_EQUALS( "bad position from int's action", pos.get(), 0 );
	}
	/* int long long */ {
		int long long val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int long long )>( call( &defer<int long long>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int long).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int long value not set by ExecutingParser.", val, 7ll );
	}
	/* HNumber */ {
		HNumber val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( HNumber const& )>( call( &defer<HNumber, HNumber const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (HNumber).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, 7 );
	}
	/* HNumber position */ {
		HNumber val( 0 );
		executing_parser::position_t pos( -1 );
		HExecutingParser ep( integer[HInteger::action_number_position_t( call( &match_value_position_ref<HNumber>, ref( val ), _1, ref( pos ), _2 ) )] );
		ENSURE( "HInteger failed to parse correct input (HNumber).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, 7 );
		ENSURE_EQUALS( "bad position from int's action", pos.get(), 0 );
	}
	/* HString */ {
		hcore::HString val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (HString).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "7" );
	}
	/* HString position */ {
		hcore::HString val( 0 );
		executing_parser::position_t pos( -1 );
		HExecutingParser ep( integer[HInteger::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) )] );
		ENSURE( "HInteger failed to parse correct input (HString).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "7" );
		ENSURE_EQUALS( "bad position from int's action", pos.get(), 0 );
	}
	/* hex */ {
		int val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int).", ep( "0x77" ) );
		ep();
		ENSURE_EQUALS( "int value not set by ExecutingParser.", val, 119 );
	}
	/* oct */ {
		int val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int).", ep( "0o77" ) );
		ep();
		ENSURE_EQUALS( "int value not set by ExecutingParser.", val, 63 );
	}
	/* bin */ {
		int val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int).", ep( "0b110011" ) );
		ep();
		ENSURE_EQUALS( "int value not set by ExecutingParser.", val, 51 );
	}
	/* bad integer */ {
		int long long val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int long long )>( call( &defer<int long long>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "Invalid input parsed by HInteger", ep( "bad" ) );
		ENSURE_NOT( "Invalid input parsed by HInteger", ep( "7bad" ) );
		ENSURE_NOT( "whitespace only input parsed by HInteger", ep( " " ) );
		ENSURE_NOT( "empty input parsed by HInteger", ep( "" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HStringLiteral" )
	typedef HArray<hcore::HString> strings_t;
	strings_t s;
	HRule sl( string_literal[push_back( s )] );
	HRule r( sl >> *( ',' >> sl ) );
	HExecutingParser ep( r );
	/* simple */ {
		ENSURE( "HStringLiteral failed to parse correct input", ep( "\"Ala\",\"ma\",\"kota.\"" ) );
		ep();
		char const expected[][6] = {
			"Ala",
			"ma",
			"kota."
		};
		int i( 0 );
		for ( strings_t::const_iterator it( s.begin() ), end( s.end() ); it != end; ++ it, ++ i ) {
			ENSURE( "too many elements acquired", i < countof ( expected ) );
			ENSURE_EQUALS( "Failed to acquire string from string literal", *it, expected[i] );
		}
		ENSURE_EQUALS( "not all elemets acquired", i, countof ( expected ) );
	}
	/* special */ {
		ENSURE( "HStringLiteral failed to parse correct input", ep(
					"\"Ola\\n\","
					"\"m\\ra\","
					"\"\\ekota.\","
					"\"\\\"\","
					"\"\\\\\","
					"\"\","
					"\"x\\\"\","
					"\"\\\"x\","
					"\"\\\"x\\\"\"" ) );
		s.clear();
		ep();
		char const expected[][8] = {
			"Ola\n",
			"m\ra",
			"\033kota.",
			"\"",
			"\\",
			"",
			"x\"",
			"\"x",
			"\"x\""
		};
		int i( 0 );
		for ( strings_t::const_iterator it( s.begin() ), end( s.end() ); it != end; ++ it, ++ i ) {
			ENSURE( "too many elements acquired", i < countof ( expected ) );
			ENSURE_EQUALS( "Failed to acquire string from string literal", *it, expected[i] );
		}
		ENSURE_EQUALS( "not all elemets acquired", i, countof ( expected ) );
	}
	ENSURE_NOT( "non-string literal parsed", ep( "Ala" ) );
	ENSURE_NOT( "unfinished string literal parsed", ep( "\"Ala" ) );
	ENSURE_NOT( "unfinished escape sequence string literal parsed", ep( "\"Ala\\" ) );
	ENSURE_NOT( "string literal with invalid character parsed", ep( "\"Al\ba\"" ) );
	ENSURE_NOT( "whitespace only input parsed", ep( " " ) );
	ENSURE_NOT( "empty input parsed", ep( "" ) );
	/* action_t */ {
		bool actionCalled( false );
		HExecutingParser epa( string_literal[HStringLiteral::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) )] );
		ENSURE( "HReal failed to parse correct input (string_literal).", epa( "\"aaa\"" ) );
		epa();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* action_position_t */ {
		executing_parser::position_t pos( -1 );
		HExecutingParser epa( string_literal[HStringLiteral::action_position_t( call( &match_position, ref( pos ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (string_literal).", epa( "\"aaa\"" ) );
		epa();
		ENSURE_EQUALS( "bad position from string_literal's action", pos.get(), 0 );
	}
	/* hex and octal codes */ {
		s.clear();
		ep( "\"a\\x20b\\\\x20c\\x0\",\"a\\x\",\"\\u1234\",\"\\U00102345\", \"\\1234\"" );
		ep();
		char const expected[][16] = {
			"a b\\x20cx0",
			"ax",
			"ሴ",
			"􂍅",
			"S4"
		};
		int i( 0 );
		for ( strings_t::const_iterator it( s.begin() ), end( s.end() ); it != end; ++ it, ++ i ) {
			ENSURE( "too many elements acquired", i < countof ( expected ) );
			ENSURE_EQUALS( "Failed to acquire string from string literal", *it, expected[i] );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HCharacterLiteral" )
	typedef HArray<code_point_t> characters_t;
	characters_t c;
	HRule cl( character_literal[push_back<code_point_t>( c )] );
	HRule r( cl >> *( ',' >> cl ) );
	HExecutingParser ep( r );
	/* simple */ {
		ENSURE( "HCharacterLiteral failed to parse correct input", ep( "'A','\\t'" ) );
		ep();
		char unsigned const expected[] = {
			'A',
			'\t'
		};
		int i( 0 );
		for ( characters_t::const_iterator it( c.begin() ), end( c.end() ); it != end; ++ it, ++ i ) {
			ENSURE( "too many elements acquired", i < countof ( expected ) );
			ENSURE_EQUALS( "Failed to acquire character from character literal", *it, expected[i] );
		}
		ENSURE_EQUALS( "not all elemets acquired", i, countof ( expected ) );
	}
	/* special */ {
		ENSURE( "HCharacterLiteral failed to parse correct input", ep(
					"'\\n',' ','	','\\t','\\b','\\e','\\\\','\\'','x'" ) );
		c.clear();
		ep();
		char unsigned const expected[] = "\n \t\t\b\033\\'x";
		int i( 0 );
		for ( characters_t::const_iterator it( c.begin() ), end( c.end() ); it != end; ++ it, ++ i ) {
			ENSURE( "too many elements acquired", i < ( countof ( expected ) - 1 ) );
			ENSURE_EQUALS( "Failed to acquire character from character literal", *it, expected[i] );
		}
		ENSURE_EQUALS( "not all elemets acquired", i, countof ( expected ) - 1 );
	}
	ENSURE_NOT( "non-character literal parsed", ep( "Ala" ) );
	ENSURE_NOT( "unfinished character literal parsed", ep( "'A" ) );
	ENSURE_NOT( "too long character literal parsed", ep( "'ab'" ) );
	ENSURE_NOT( "empty character literal parsed", ep( "''" ) );
	ENSURE_NOT( "unfinished escape sequence character literal parsed", ep( "'\\" ) );
	ENSURE_NOT( "character literal with invalid character parsed", ep( "'\b'" ) );
	ENSURE_NOT( "whitespace only input parsed", ep( " " ) );
	/* action_t */ {
		bool actionCalled( false );
		HExecutingParser epa( character_literal[HCharacterLiteral::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) )] );
		ENSURE( "HReal failed to parse correct input (character_literal).", epa( "'a'" ) );
		epa();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* action_position_t */ {
		executing_parser::position_t pos( -1 );
		HExecutingParser epa( character_literal[HCharacterLiteral::action_position_t( call( &match_position, ref( pos ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (character_literal).", epa( "'a'" ) );
		epa();
		ENSURE_EQUALS( "bad position from character_literal's action", pos.get(), 0 );
	}
	/* hex codes */ {
		c.clear();
		ep( "'\\x20','\\x','\\u1234','\\U00102345'" );
		ep();
		code_point_t const expected[] = {
			' '_ycp,
			'x'_ycp,
#ifndef __MSVCXX__
			U'ሴ'_ycp,
			U'􂍅'_ycp
#else
			4660_ycp,
			1057605_ycp
#endif
		};
		int i( 0 );
		for ( characters_t::const_iterator it( c.begin() ), end( c.end() ); it != end; ++ it, ++ i ) {
			ENSURE( "too many elements acquired", i < countof ( expected ) );
			ENSURE_EQUALS( "Failed to acquire string from string literal", *it, expected[i] );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HCharacter" )
	/* char (any) */ {
		code_point_t val( 0 );
		HExecutingParser ep( character[HCharacter::action_character_t( call( &defer<code_point_t>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", ep( "a" ) );
		ep();
		ENSURE_EQUALS( "char value not set by ExecutingParser.", val, code_point_t( 'a' ) );
	}
	/* char (specific ok) */ {
		code_point_t val( 0 );
		HExecutingParser ep( e_p::constant( 'a', HCharacter::action_character_t( call( &defer<code_point_t>::set, ref( val ), _1 ) ) ) );
		ENSURE( "HCharacter failed to parse correct input.", ep( "a" ) );
		ep();
		ENSURE_EQUALS( "char not captured", val, code_point_t( 'a' ) );
	}
	/* char (specific ok) action_t */ {
		bool actionCalled( false );
		HExecutingParser ep( e_p::constant( 'a', HCharacter::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ) ) );
		ENSURE( "HCharacter failed to parse correct input.", ep( "a" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* char (specific, any of ok) */ {
		code_point_t val( 0 );
		HExecutingParser ep( characters( "ab", HCharacter::action_character_t( call( &defer<code_point_t>::set, ref( val ), _1 ) ) ) );
		ENSURE( "HCharacter failed to parse correct input.", ep( "b" ) );
		ep();
		ENSURE_EQUALS( "char not captured", val, code_point_t( 'b' ) );
	}
	/* char (specific, any of ok) action_position_t */ {
		e_p::position_t pos( -1 );
		HExecutingParser ep( characters( "ab", e_p::HString::action_position_t( call( &match_position, ref( pos ), _1 ) ) ) );
		ENSURE( "HCharacter failed to parse correct input.", ep( "b" ) );
		ep();
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* char (specific, any of ok) action_t */ {
		bool actionCalled( false );
		HExecutingParser ep( characters( "ab", HCharacter::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ) ) );
		ENSURE( "HCharacter failed to parse correct input.", ep( "b" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* char (specific, any of ok) no action */ {
		HExecutingParser ep( characters( "ab" ) );
		ENSURE( "HCharacter failed to parse correct input.", ep( "b" ) );
	}
	/* char (specific fail) */ {
		code_point_t val( 0 );
		HExecutingParser ep( character( 'X' )[HCharacter::action_character_t( call( &defer<code_point_t>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HCharacter parsed invalid input.", ep( "a" ) );
	}
	/* char (specific any of fail) */ {
		code_point_t val( 0 );
		HExecutingParser ep( character( "ab" )[HCharacter::action_character_t( call( &defer<code_point_t>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HCharacter parsed invalid input.", ep( "c" ) );
	}
	/* char WS */ {
		code_point_t val( 0 );
		HExecutingParser ep( character( "ab " )[HCharacter::action_character_t( call( &defer<code_point_t>::set, ref( val ), _1 ) )]( HCharacter::WHITE_SPACE::AUTO ) );
		ENSURE_NOT( "HCharacter parsed invalid input.", ep( "c" ) );
		ENSURE( "HCharacter parsed invalid input.", ep( " " ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HString" )
	/* action_string_t */ {
		hcore::HString val;
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_string_t( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ) ) );
		ENSURE_NOT( "HString parsed input with trailing garbage.", ep( "  alaX" ) );
		ENSURE( "HString failed to parse correct input.", ep( "  ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
	}
	/* string() action_string_t */ {
		hcore::HString val;
		HExecutingParser ep( e_p::string( "ala", e_p::HString::action_string_t( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ) ) );
		ENSURE_NOT( "HString parsed input with trailing garbage.", ep( "  alaX" ) );
		ENSURE( "HString failed to parse correct input.", ep( "  ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
	}
	/* action_string_t no skip WS */ {
		hcore::HString val;
		HExecutingParser ep( e_p::constant( "ala",e_p::HString::action_string_t( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ), e_p::HString::WHITE_SPACE::KEEP ) );
		ENSURE_NOT( "HString parsed whitespace leading input (skip WS disabled).", ep( "  ala" ) );
		ENSURE( "HString failed to parse correct input.", ep( "ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
	}
	/* action_string_t WB */ {
		hcore::HString val;
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_string_t( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ), e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
	}
	/* string() action_string_t WB */ {
		hcore::HString val;
		HExecutingParser ep( e_p::string( "ala", e_p::HString::action_string_t( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ), e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
	}
	/* action_string_position */ {
		hcore::HString val;
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) ) ) );
		ENSURE_NOT( "HString parsed input with trailing garbage.", ep( "  alaX" ) );
		ENSURE( "HString failed to parse correct input.", ep( "  ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 2 );
	}
	/* string() action_string_position */ {
		hcore::HString val;
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::string( "ala", e_p::HString::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) ) ) );
		ENSURE_NOT( "HString parsed input with trailing garbage.", ep( "  alaX" ) );
		ENSURE( "HString failed to parse correct input.", ep( "  ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 2 );
	}
	/* action_string_position no skip ws */ {
		hcore::HString val;
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) ), e_p::HString::WHITE_SPACE::KEEP ) );
		ENSURE_NOT( "HString parsed whitespace leading input (skip WS disabled).", ep( "  ala" ) );
		ENSURE( "HString failed to parse correct input.", ep( "ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* action_string_position WB */ {
		hcore::HString val;
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) ), e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 2 );
	}
	/* string() action_string_position WB */ {
		hcore::HString val;
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::string( "ala", e_p::HString::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) ), e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 2 );
	}
	/* action_position */ {
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_position_t( call( &match_position, ref( pos ), _1 ) ) ) );
		ENSURE( "HString failed to parse correct input.", ep( "ala" ) );
		ep();
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* string() action_position */ {
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::string( "ala", e_p::HString::action_position_t( call( &match_position, ref( pos ), _1 ) ) ) );
		ENSURE( "HString failed to parse correct input.", ep( "ala" ) );
		ep();
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* action_position WB */ {
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_position_t( call( &match_position, ref( pos ), _1 ) ), e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
		ep();
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 2 );
	}
	/* string() action_position WB */ {
		e_p::position_t pos( -1 );
		HExecutingParser ep( e_p::string( "ala", e_p::HString::action_position_t( call( &match_position, ref( pos ), _1 ) ), e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
		ep();
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 2 );
	}
	/* action */ {
		bool actionCalled( false );
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ) ) );
		ENSURE( "HString failed to parse correct input.", ep( "  ala" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* string() action */ {
		bool actionCalled( false );
		HExecutingParser ep( e_p::string( "ala", e_p::HString::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ) ) );
		ENSURE( "HString failed to parse correct input.", ep( "  ala" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* action WB */ {
		bool actionCalled( false );
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ), e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* string() action WB */ {
		bool actionCalled( false );
		HExecutingParser ep( e_p::string( "ala", e_p::HString::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ), e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* action no skip WS */ {
		bool actionCalled( false );
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ), e_p::HString::WHITE_SPACE::KEEP ) );
		ENSURE_NOT( "HString parsed whitespace leading input (skip WS disabled).", ep( "  ala" ) );
		ENSURE( "HString failed to parse correct input.", ep( "ala" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* no action */ {
		HExecutingParser ep( e_p::constant( "ala" ) );
		ENSURE( "HString failed to parse correct input.", ep( "ala" ) );
	}
	/* no action WB */ {
		HExecutingParser ep( e_p::constant( "ala", e_p::HString::WORD_BOUNDARY::OPTIONAL ) >> *character );
		ENSURE( "HString failed to parse correct input.", ep( "  alaX" ) );
	}
	/* fail */ {
		hcore::HString val;
		HExecutingParser ep( string( "XXX" )[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HString parsed invalid input.", ep( "ala" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HString(multi)" )
	/* multi ok */ {
		hcore::HString val;
		hcore::HString nick;
		HRule animal( ( string( "pies", executing_parser::HString::WORD_BOUNDARY::OPTIONAL ) | "kot" | "lis" )[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ) ] );
		HRule name( regex( ".*", HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( nick ), _1 ) ) ) );
		HExecutingParser ep( animal >> name );
		ENSURE( "HString failed to parse correct input.", ep( "kotFilemon" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "kot" );
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", nick, "Filemon" );
		ENSURE( "HString failed to parse correct input.", ep( "piesReksio" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "pies" );
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", nick, "Reksio" );
		ENSURE( "HString failed to parse correct input.", ep( "lisChytrusek" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "lis" );
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", nick, "Chytrusek" );
	}
	/* multi fail */ {
		hcore::HString val;
		hcore::HString nick;
		HRule animal( ( string( "pies", executing_parser::HString::WORD_BOUNDARY::OPTIONAL ) | "kot" | "lis" )[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ) ] );
		HRule name( regex( ".*", HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ) ) );
		HExecutingParser ep( animal >> name );
		ENSURE_NOT( "HString parsed invalid input.", ep( "losDobry" ) );
	}
	ENSURE_THROW( "broken multi|string accepted", string( "pies" ) | "kot" | "piesek", executing_parser::HStringException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HRegex" )
	/* ok */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[e_p::HRegex::action_string_t( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "12.34" );
	}
	/* action_string_position_t attached */ {
		hcore::HString val;
		e_p::position_t pos( -1 );
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[e_p::HRegex::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) )] );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "12.34" );
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* action_position_t attached */ {
		e_p::position_t pos( -1 );
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[e_p::HRegex::action_position_t( call( &match_position, ref( pos ), _1 ) )] );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* action_t attached */ {
		bool actionCalled( false );
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[e_p::HRegex::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) )] );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* name, action_string */ {
		hcore::HString val;
		HExecutingParser ep( regex( "num", "[0-9]{2}\\.[0-9]{2}", e_p::HRegex::action_string_t( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) ) ) );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "12.34" );
	}
	/* name, action_string_position */ {
		hcore::HString val;
		e_p::position_t pos( -1 );
		HExecutingParser ep( regex( "num", "[0-9]{2}\\.[0-9]{2}", e_p::HRegex::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) ) ) );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "12.34" );
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* action_string_position */ {
		hcore::HString val;
		e_p::position_t pos( -1 );
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}", e_p::HRegex::action_string_position_t( call( &match_value_position_ref<hcore::HString>, ref( val ), _1, ref( pos ), _2 ) ) ) );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "12.34" );
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* name, action_position */ {
		e_p::position_t pos( -1 );
		HExecutingParser ep( regex( "num", "[0-9]{2}\\.[0-9]{2}", e_p::HRegex::action_position_t( call( &match_position, ref( pos ), _1 ) ) ) );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* action_position */ {
		e_p::position_t pos( -1 );
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}", e_p::HRegex::action_position_t( call( &match_position, ref( pos ), _1 ) ) ) );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "bad position from regex's action", pos.get(), 0 );
	}
	/* name, action */ {
		bool actionCalled( false );
		HExecutingParser ep( regex( "num", "[0-9]{2}\\.[0-9]{2}", e_p::HRegex::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ) ) );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* action */ {
		bool actionCalled( false );
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}", e_p::HRegex::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) ) ) );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE( "action was not called by ExecutingParser.", actionCalled );
	}
	/* name, no action */ {
		HExecutingParser ep( regex( "num", "[0-9]{2}\\.[0-9]{2}"_ys ) );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ENSURE_NOT( "HRegex parsed invalid input.", ep( "ala" ) );
	}
	/* fail not fully consumed input */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" ) );
		ENSURE_NOT( "HExecutingParser accepted parse on partial input.", ep( "12.345" ) );
	}
	/* fail */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" ) );
		ENSURE_NOT( "HRegex parsed invalid input.", ep( "12.3a" ) );
		ENSURE_NOT( "whitespace only input parsed", ep( " " ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFollows" )
	/* parsed */ {
		code_point_t fcData( 0 );
		HRule fc( character( 'a' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( fcData ), _1 ) )] );
		code_point_t scData( 0 );
		HRule sc( character( 'b' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( scData ), _1 ) )] );
		bool followsCalled( false );
		HExecutingParser ep( ( fc >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( followsCalled ), true ) ) ] );
		ENSURE( "parse on correct failed", ep( "ab" ) );
		ep();
		ENSURE_EQUALS( "predecessor in follows not called", fcData, static_cast<code_point_t>( 'a' ) );
		ENSURE_EQUALS( "successor in follows not called", scData, static_cast<code_point_t>( 'b' ) );
		ENSURE( "follows not called", followsCalled );
	}
	/* From string. */ {
		HExecutingParser ep( integer >> "num"_ys >> "val"_ys );
		ENSURE( "parse on correct failed", ep( "123 num val" ) );
		HExecutingParser ep2( "num"_ys >> integer );
		ENSURE( "parse on correct failed", ep2( "num 123" ) );
	}
	/* failed on successor */ {
		code_point_t fcData( 0 );
		HRule fc( character( 'a' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( fcData ), _1 ) )] );
		code_point_t scData( 0 );
		HRule sc( character( 'b' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( scData ), _1 ) )] );
		bool followsCalled( false );
		HExecutingParser ep( ( fc >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( followsCalled ), true ) ) ] );
		ENSURE_NOT( "parse on invalid succeeded", ep( "aa" ) );
	}
	/* only optionals and empty input */ {
		HExecutingParser ep( *integer >> -character( '!' ) );
		ENSURE( "parse on empty input with optionals grammar failed", ep( "" ) );
	}
	/* follows concat */ {
		bool followsCalled( false );
		HExecutingParser ep(
			( e_p::constant( '@' ) >> -( e_p::constant( '[' ) ) )[
				HBoundCall<void ( void )>( call( &defer<bool>::set, ref( followsCalled ), true ) )
			] >> '{'
		);
		ep( "@{" );
		ep();
		ENSURE( "follows not called", followsCalled );
	}
TUT_TEARDOWN()

struct Kleene {
	int _count;
	Kleene( void )
		: _count( 0 ) {
	}
	template<typename T>
	void sum( T& sum_, T val_ ) {
		sum_ += val_;
		++ _count;
	}
	void count( int& out_ ) {
		out_ = _count;
	}
	void count_p( int& out_, executing_parser::position_t ) {
		count( out_ );
		out_ = -out_;
	}
};

TUT_UNIT_TEST( "HKleeneStar" )
	/* parsed (non empty) */ {
		int val( 0 );
		int count( 0 );
		Kleene k;
		HRule i( integer[HBoundCall<void ( int )>( call( &Kleene::sum<int>, &k, ref( val ), _1 ) )] );
		HRule nums( ( *( ',' >> i ) )[e_p::HRule::action_t( call( &Kleene::count, &k, ref( count ) ) )] );
		HExecutingParser ep( nums );
		ENSURE( "parse on valid failed", ep( ", 1, 2, 3" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 6 );
		ENSURE_EQUALS( "execution of KleeneStar failed (sem_act)", count, 3 );
	}
	/* parsed (empty) */ {
		int val( 0 );
		int count( 0 );
		Kleene k;
		HRule i( integer[HBoundCall<void ( int )>( call( &Kleene::sum<int>, &k, ref( val ), _1 ) )] );
		HRule nums( ( *( ',' >> i ) )[e_p::HRule::action_position_t( call( &Kleene::count_p, &k, ref( count ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> nums >> "}" );
		ENSURE( "parse on valid (but empty) failed", ep( "nums{}" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 0 );
		ENSURE_EQUALS( "execution of KleeneStar failed (sem_act)", count, 0 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HKleenePlus" )
	namespace e_p = executing_parser;
	/* parsed (non empty) */ {
		int val( 0 );
		int count( 0 );
		Kleene k;
		HRule i( integer[HBoundCall<void ( int )>( call( &Kleene::sum<int>, &k, ref( val ), _1 ) )] );
		HRule nums( ( +( ',' >> i ) )[e_p::HRule::action_t( call( &Kleene::count, &k, ref( count ) ) )] );
		HExecutingParser ep( nums );
		ENSURE( "parse on valid failed", ep( ", 1, 2, 3" ) );
		ep();
		ENSURE_EQUALS( "execution of KleenePlus failed", val, 6 );
		ENSURE_EQUALS( "execution of KleenePlus failed (sem_act)", count, 3 );
	}
	/* parsed (exactly) */ {
		int val( 0 );
		int count( 0 );
		Kleene k;
		HRule i( integer[HBoundCall<void ( int )>( call( &Kleene::sum<int>, &k, ref( val ), _1 ) )] );
		HRule nums( ( +( ',' >> i ) )[e_p::HRule::action_position_t( call( &Kleene::count_p, &k, ref( count ), _1 ) )] );
		HExecutingParser ep( nums );
		ENSURE( "parse on valid failed", ep( ", 1" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 1 );
		ENSURE_EQUALS( "execution of KleeneStar failed (sem_act)", count, -1 );
	}
	/* not-parsed (empty) */ {
		int val( 0 );
		Kleene k;
		HRule i( integer[HBoundCall<void ( int )>( call( &Kleene::sum<int>, &k, ref( val ), _1 ) )] );
		HRule nums( +( ',' >> i ) );
		HExecutingParser ep( string( "nums{" ) >> nums >> "}" );
		ENSURE_NOT( "parse on invalid (empty) succeeded", ep( "nums{}" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HAlternative" )
	/* alternative */ {
		int val( 0 );
		int val_alt( 0 );
		bool actionCalled( false );
		HRule i( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		HRule ia( integer[HBoundCall<void ( int )>( call( &defer<int>::set_alt, ref( val_alt ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> ( ( i >> ":pos" ) | ( ia >> ":neg" ) )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( actionCalled ), true ) )] >> "}" );
		ENSURE( "parse on valid failed", ep( "nums{7:neg}" ) );
		ep();
		ENSURE_EQUALS( "execution failed sub-step not removed", val, 0 );
		ENSURE_EQUALS( "execution proper execution sub-step not applied", val_alt, -7 );
		ENSURE( "action on alternative was not called", actionCalled );
	}
	/* one optional and empty input */ {
		HExecutingParser ep( integer | -real | character( '!' ) );
		ENSURE( "parse on empty input with optionals grammar failed", ep( "" ) );
	}
	/* alternative concat */ {
		bool alternativeCalled( false );
		HExecutingParser ep(
			( e_p::constant( '@' ) | -( e_p::constant( '[' ) ) )[
				HBoundCall<void ( void )>( call( &defer<bool>::set, ref( alternativeCalled ), true ) )
			] | e_p::constant( '{' )
		);
		ep( "@" );
		ep();
		ENSURE( "alternative not called", alternativeCalled );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HOptional" )
	/* not-parsed (empty) configuration test */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> i >> "}" );
		ENSURE_NOT( "parse on invalid (empty) succeeded", ep( "nums{}" ) );
	}
	/* parsed (empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> (-i) >> "}" );
		ENSURE( "parse on valid (but empty) failed", ep( "nums{}" ) );
		ep();
		ENSURE_EQUALS( "execution of optional failed", val, 0 );
	}
	/* parsed (non-empty) action_t */ {
		int val( 0 );
		bool actionCalled( false );
		HRule i( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> (-i)[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( actionCalled ), true ) )] >> "}" );
		ENSURE( "parse on valid failed", ep( "nums{7}" ) );
		ep();
		ENSURE_EQUALS( "execution of optional failed", val, 7 );
		ENSURE( "action on optional was not called", actionCalled );
	}
	/* parsed (non-empty) action_position_t */ {
		int val( 0 );
		executing_parser::position_t pos( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> (-i)[HAlternative::action_position_t( call( &match_position, ref( pos ), _1 ) )] >> "}" );
		ENSURE( "parse on valid failed", ep( "nums{7}" ) );
		ep();
		ENSURE_EQUALS( "execution of optional failed", val, 7 );
		ENSURE_EQUALS( "bad position from optional's action", pos.get(), 5 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HAnd" )
	/* parsed */ {
		bool actionCalled( false );
		executing_parser::position_t pos( -1 );
		code_point_t fcData( '_' );
		HRule fc( character( 'a' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( fcData ), _1 ) )] );
		code_point_t scData( '_' );
		code_point_t data( '_' );
		char trailerChar[] = "b";
		HRule trailer( character( trailerChar )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( scData ), _1 ) )] );
		HRule sc( character( trailerChar )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( data ), _1 ) )] );
		bool andCalled( false );
		HExecutingParser ep( ( ( fc & trailer )[HAnd::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) )] >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( andCalled ), true ) ) ] );
		HExecutingParser epp( ( ( fc & trailerChar )[HAnd::action_position_t( call( &match_position, ref( pos ), _1 ) )] >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( andCalled ), true ) ) ] );
		HExecutingParser epS( ( ( fc & to_string( trailerChar ) )[HAnd::action_position_t( call( &match_position, ref( pos ), _1 ) )] >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( andCalled ), true ) ) ] );
		ENSURE( "parse on correct failed", ep( "ab" ) );
		ENSURE( "parse on correct failed pos", epp( "ab" ) );
		ENSURE( "parse on correct failed pos", epS( "ab" ) );
		ep();
		ENSURE_EQUALS( "predecessor in AND not called", fcData, static_cast<code_point_t>( 'a' ) );
		ENSURE_EQUALS( "successor in AND called", scData, static_cast<code_point_t>( '_' ) );
		ENSURE_EQUALS( "following rule of AND not called", data, static_cast<code_point_t>( 'b' ) );
		ENSURE( "action on AND was not called", actionCalled );
		epp();
		ENSURE_EQUALS( "bad position from and's action", pos.get(), 0 );
		ENSURE( "follows not called", andCalled );
		pos = executing_parser::position_t( -1 );
		epS();
		ENSURE_EQUALS( "bad position from and's action", pos.get(), 0 );
		HExecutingParser ep2( fc & sc );
		ENSURE_NOT( "parse on dangling succeeded", ep2( " ab" ) );
		ENSURE_EQUALS( "bad error position", ep2.error_position(), 2 );
	}
	/* failed on successor */ {
		HRule fc( character( 'a' ) );
		HRule sc( character( 'b' ) );
		HExecutingParser ep( ( fc & sc ) >> character );
		ENSURE_NOT( "parse on invalid succeeded", ep( " aa" ) );
		ENSURE_EQUALS( "bad error position", ep.error_position(), 2 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HNot" )
	/* parsed */ {
		bool actionCalled( false );
		executing_parser::position_t pos( -1 );
		code_point_t fcData( '_' );
		HRule fc( character( 'a' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( fcData ), _1 ) )] );
		code_point_t scData( '_' );
		code_point_t data( '_' );
		char trailerChar[] = "b";
		HRule trailer( character( trailerChar )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( scData ), _1 ) )] );
		HRule sc( character( 'c' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( data ), _1 ) )] );
		bool notCalled( false );
		HExecutingParser ep( ( ( fc ^ trailer )[HNot::action_t( call( &defer<bool>::set, ref( actionCalled ), true ) )] >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( notCalled ), true ) ) ] );
		HExecutingParser epp( ( ( fc ^ trailerChar )[HNot::action_position_t( call( &match_position, ref( pos ), _1 ) )] >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( notCalled ), true ) ) ] );
		HExecutingParser epS( ( ( fc ^ to_string( trailerChar ) )[HNot::action_position_t( call( &match_position, ref( pos ), _1 ) )] >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( notCalled ), true ) ) ] );
		ENSURE( "parse on correct failed", ep( "ac" ) );
		ENSURE( "parse on correct failed pos", epp( "ac" ) );
		ENSURE( "parse on correct failed pos", epS( "ac" ) );
		ep();
		ENSURE_EQUALS( "predecessor in NOT not called", fcData, static_cast<code_point_t>( 'a' ) );
		ENSURE_EQUALS( "successor in NOT called", scData, static_cast<code_point_t>( '_' ) );
		ENSURE_EQUALS( "following rule of NOT not called", data, static_cast<code_point_t>( 'c' ) );
		epp();
		ENSURE_EQUALS( "bad position from NOT's action", pos.get(), 0 );
		ENSURE( "follows not called", notCalled );
		ENSURE( "action on NOT was not called", actionCalled );
		pos = executing_parser::position_t( -1 );
		epS();
		ENSURE_EQUALS( "bad position from NOT's action", pos.get(), 0 );
		HExecutingParser ep2( fc ^ sc );
		ENSURE_NOT( "parse on dangling succeeded", ep2( " ac" ) );
		ENSURE_EQUALS( "bad error position", ep2.error_position(), 2 );
		ENSURE_EQUALS( "bad error position", ep2.error_position(), 2 );
	}
	/* failed on successor */ {
		HRule fc( character( 'a' ) );
		HRule sc( character( 'b' ) );
		HExecutingParser ep( ( fc ^ sc ) >> character );
		ENSURE_NOT( "parse on invalid succeeded", ep( " ab" ) );
		ENSURE_EQUALS( "bad error position", ep.error_position(), 2 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HAction" )
	/* parsed */ {
		bool prefixAction( false );
		code_point_t fcData( 0 );
		HRule fc( character( 'a' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( fcData ), _1 ) )] );
		code_point_t scData( 0 );
		HRule sc( character( 'b' )[HBoundCall<void ( code_point_t )>( call( &defer<code_point_t>::set, ref( scData ), _1 ) )] );
		bool followsCalled( false );
		executing_parser::position_t pos( -1 );
		HExecutingParser ep(
		 	HRuleBase::action_t( call( &defer<bool>::set, ref( prefixAction ), true ) )
		 	>> fc >> sc >>
		 	HRuleBase::action_position_t( call( &match_value_position_val<bool>, ref( followsCalled ), true, ref( pos ), _1 ) )
	 	);
		ENSURE( "parse on correct failed", ep( "ab" ) );
		ep();
		ENSURE_EQUALS( "predecessor in follows not called", fcData, static_cast<code_point_t>( 'a' ) );
		ENSURE_EQUALS( "successor in follows not called", scData, static_cast<code_point_t>( 'b' ) );
		ENSURE( "prefixAction not called", prefixAction );
		ENSURE( "suffixAction not called", followsCalled );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "canceling execution steps" )
	int val( 0 );
	int val_alt( 0 );
	HRule i( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
	HRule ia( integer[HBoundCall<void ( int )>( call( &defer<int>::set_alt, ref( val_alt ), _1 ) )] );
	HExecutingParser ep( string( "nums{" ) >> ( -( i >> ":pos" ) ) >> ( -( ia >> ":neg" ) ) >> "}" );
	ENSURE( "parse on valid failed", ep( "nums{7:neg}" ) );
	ep();
	ENSURE_EQUALS( "execution failed sub-step not removed", val, 0 );
	ENSURE_EQUALS( "execution proper execution sub-step not applied", val_alt, -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "left recursion (follows)" )
	HRule S;
	S %= ( S >> '$' >> integer );
	HGrammarDescription gd( S );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "bad ruie count", i < 1 );
		ENSURE_EQUALS( "wrong description", *it, "A_ = ( A_ >> '$' >> integer )" );
		cout << *it << endl;
	}
	ENSURE_THROW( "Grammar with left recursion accepted (follows).", HExecutingParser ep( S ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "left recursion (alternative)" )
	HRule S;
	S %= ( integer | S );
	HGrammarDescription gd( S );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "bad ruie count", i < 1 );
		ENSURE_EQUALS( "wrong description", *it, "A_ = ( integer | A_ )" );
		cout << *it << endl;
	}
	ENSURE_THROW( "Grammar with left recursion accepted (alternative).", HExecutingParser ep( S ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "left recursion (optional)" )
	HRule S;
	S %= ( -integer >> S );
	HGrammarDescription gd( S );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "bad ruie count", i < 1 );
		ENSURE_EQUALS( "wrong description", *it, "A_ = ( -integer >> A_ )" );
		cout << *it << endl;
	}
	ENSURE_THROW( "Grammar with left recursion accepted (optional).", HExecutingParser ep( S ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "left recursion (kleene star)" )
	HRule S;
	S %= ( *integer >> S );
	HGrammarDescription gd( S );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "bad ruie count", i < 1 );
		ENSURE_EQUALS( "wrong description", *it, "A_ = ( *integer >> A_ )" );
		cout << *it << endl;
	}
	ENSURE_THROW( "Grammar with left recursion accepted (kleene star).", HExecutingParser ep( S ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "left recursion (kleene plus)" )
	HRule S;
	S %= (  +S >> integer );
	HGrammarDescription gd( S );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "bad ruie count", i < 1 );
		ENSURE_EQUALS( "wrong description", *it, "A_ = ( +A_ >> integer )" );
		cout << *it << endl;
	}
	ENSURE_THROW( "Grammar with left recursion accepted (kleene plus).", HExecutingParser ep( S ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "left recursion (and)" )
	HRule S;
	S %= ( ( S & '$' ) >> integer );
	HGrammarDescription gd( S );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "bad ruie count", i < 1 );
		ENSURE_EQUALS( "wrong description", *it, "A_ = ( ( A_ & '$' ) >> integer )" );
		cout << *it << endl;
	}
	ENSURE_THROW( "Grammar with left recursion accepted (and).", HExecutingParser ep( S ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "left recursion (not)" )
	HRule S;
	S %= ( ( S ^ '$' ) >> integer );
	HGrammarDescription gd( S );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "bad ruie count", i < 1 );
		ENSURE_EQUALS( "wrong description", *it, "A_ = ( ( A_ ^ '$' ) >> integer )" );
		cout << *it << endl;
	}
	ENSURE_THROW( "Grammar with left recursion accepted (not).", HExecutingParser ep( S ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "simple recursive rule" )
	/*
	 * If *::describe() is incorrectly implemented this test will overflow stack.
	 */
	HRule elem;
	HRule mul( elem >> *( '*' >> elem ) );
	HRule sum( mul >> *( '+' >> mul ) );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	HExecutingParser ep( elem );
	static char epDesc[][60] = {
		"A_ = ( real | ( '(' >> ( B_ >> *( '+' >> B_ ) ) >> ')' ) )",
		"B_ = ( A_ >> *( '*' >> A_ ) )"
	};
	cout << "elem:" << endl;
	HGrammarDescription gd( elem );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "non-trivial recursive rule" )
	HRule elem;
	HRule mul( elem >> *( '*' >> elem ) );
	HRule sum( mul >> *( '+' >> mul ) );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	HRule name( regex( "\\<a-z\\>" ) );
	HRule eq( name >> '=' >> elem );
	HExecutingParser ep( eq );
	char epDesc[][80] = {
		"A_ = ( regex( \"\\<a-z\\>\" ) >> '=' >> B_ )",
		"B_ = ( real | ( '(' >> ( C_ >> *( '+' >> C_ ) ) >> ')' ) )",
		"C_ = ( B_ >> *( '*' >> B_ ) )"
	};
	cout << "eq:" << endl;
	HGrammarDescription gd( eq );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "ad-hoc root rule name" )
	HRule elem;
	HRule mul( elem >> *( '*' >> elem ) );
	HRule extra( integer >> '%' >> elem );
	HRule sum( mul >> *( '+' >> mul ) );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	HExecutingParser ep( elem >> extra );
	static char epDesc[][60] = {
		"A_ = ( B_ >> ( integer >> '%' >> B_ ) )",
		"B_ = ( real | ( '(' >> ( C_ >> *( '+' >> C_ ) ) >> ')' ) )",
		"C_ = ( B_ >> *( '*' >> B_ ) )"
	};
	cout << "ad-hoc:" << endl;
	HGrammarDescription gd( elem >> extra );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "ad-hoc root rule name with action" )
	HRule elem;
	HRule mul( elem >> *( '*' >> elem ) );
	HRule extra( integer >> '%' >> elem );
	HRule sum( mul >> *( '+' >> mul ) );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	HExecutingParser ep( (elem >> extra)[HRuleBase::action_t( call( &noop ) )] );
	static char epDesc[][60] = {
		"A_ = ( B_ >> ( integer >> '%' >> B_ ) )",
		"B_ = ( real | ( '(' >> ( C_ >> *( '+' >> C_ ) ) >> ')' ) )",
		"C_ = ( B_ >> *( '*' >> B_ ) )"
	};
	cout << "ad-hoc:" << endl;
	HGrammarDescription gd( elem >> extra );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "two inter-locking recursion loops" )
	HRule elem;
	HRule other;
	HRule mul( elem >> *( '*' >> elem ) >> other );
	HRule sum( other >> *( '+' >> other ) >> elem );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	other %= ( integer | ( character( '(' ) >> mul >> ')' ) );
	HRule name( regex( "\\<a-z\\>" ) );
	HRule eq( name >> '=' >> elem >> other );
	HExecutingParser ep2( eq );
	char epDesc[][80] = {
		"A_ = ( regex( \"\\<a-z\\>\" ) >> '=' >> B_ >> C_ )",
		"B_ = ( real | ( '(' >> ( C_ >> *( '+' >> C_ ) >> B_ ) >> ')' ) )",
		"C_ = ( integer | ( '(' >> ( B_ >> *( '*' >> B_ ) >> C_ ) >> ')' ) )"
	};
	cout << "eq:" << endl;
	HGrammarDescription gd( eq );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "trivial infinite recursion bug (follows)" )
	/* left recursion */ {
		HRule A;
		HRule B( A >> integer );
		A %= ( B >> integer );
		try {
			HExecutingParser ep( A );
			FAIL( "Failed to detect infinite recursion in grammar." );
		} catch ( HExecutingParserException const& e ) {
			ENSURE_EQUALS( "bad message", e.what(), "Infinite recursion detected: A_ = ( ( A_ >> integer ) >> integer )"_ys );
		}
	}
	/* non recursion */ {
		HRule A;
		HRule B( integer >> A );
		A %= ( integer >> B );
		HExecutingParser ep( A ); /* <--- Must not throw! */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "trivial infinite recursion bug (alternative)" )
	/* left */ {
		HRule A;
		HRule B( A | integer );
		A %= ( B | integer );
		try {
			HExecutingParser ep( A );
			FAIL( "Failed to detect infinite recursion in grammar." );
		} catch ( HExecutingParserException const& e ) {
			ENSURE_EQUALS( "bad message", e.what(), "Infinite recursion detected: A_ = ( ( A_ | integer ) | integer )"_ys );
		}
	}
	/* right */ {
		HRule A;
		HRule B( integer | A );
		A %= ( integer | B );
		try {
			HExecutingParser ep( A );
			FAIL( "Failed to detect infinite recursion in grammar." );
		} catch ( HExecutingParserException const& e ) {
			ENSURE_EQUALS( "bad message", e.what(), "Infinite recursion detected: A_ = ( integer | ( integer | A_ ) )"_ys );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "trivial infinite recursion in terminal delimited follows" )
	HRule A;
	HRule B( A >> integer );
	A %= ( B >> integer );
	try {
		HExecutingParser ep( character( '"' ) >> A >> '"' );
		FAIL( "Failed to detect infinite recursion in grammar." );
	} catch ( HExecutingParserException const& e ) {
		ENSURE_EQUALS( "bad message", e.what(), "Infinite recursion detected: A_ = ( ( A_ >> integer ) >> integer )"_ys );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "infinite recursion bug (terminal is optional)" )
	/* true left recursion */ {
		HRule A;
		HRule B( A | integer );
		HRule C( real >> B );
		A %= ( -C >> B );
		try {
			HExecutingParser ep( A );
			FAIL( "Failed to detect infinite recursion in grammar." );
		} catch ( HExecutingParserException const& e ) {
			ENSURE_EQUALS( "bad message", e.what(), "Infinite recursion detected: B_ = ( -( real >> A_ ) >> A_ )"_ys );
		}
	}
	/* non recursion */ {
		HRule A;
		HRule B( A | integer );
		HRule C( real >> B );
		A %= ( C >> B );
		HExecutingParser ep( A ); /* <--- Must not throw! */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "follows with recursion bug" )
	HRule A;
	HRule C( real >> A >> '@' );
	HRule B( integer >> C );
	A %= HRule( B >> "=" >> C >> C );
	HExecutingParser ep( A ); /* <--- Must not throw! */
TUT_TEARDOWN()

TUT_UNIT_TEST( "repeated follows invoking alternative recursion bug" )
	HRule B;
	HRule A( ( '(' >> B >> ')' ) | integer );
	B %= ( A >> A );
	HExecutingParser ep( A ); /* <--- Must not throw! */
TUT_TEARDOWN()

TUT_UNIT_TEST( "unnamed HHuginn grammar" )
	HRule name( regex( "\\b[a-zA-Z_][a-zA-Z0-9_]*\\b" ) );
	HRule expression;
	HRule absoluteValue( '|' >> expression >> '|' );
	HRule parenthesis( '(' >> expression >> ')' );
	HRule functionArgument( expression ^ ':' );
	HRule argList( functionArgument >> ( * ( ',' >> functionArgument ) ) );
	HRule namedParameter( name >> ':' >> expression );
	HRule namedParameters( namedParameter >> *( ',' >> namedParameter ) );
	HRule functionCallOperator( ( '(' >> -( argList >> -( ',' >> namedParameters ) ) >> ')' ) | ( '(' >> -namedParameters >> ')' ) );
	HRule listLiteral( '[' >> -argList >> ']' );
	HRule tupleLiteral( '(' >> -argList >> -e_p::constant( ',' ) >> ')' );
	HRule setLiteral( '{' >> expression >> *( ',' >> expression ) >> '}' );
	HRule dictLiteralElement( expression >> ':' >> expression );
	HRule dictLiteral( '{' >> -( dictLiteralElement >> *( ',' >> dictLiteralElement ) ) >> '}' );
	HRule lookupLiteral( '[' >> -( dictLiteralElement >> *( ',' >> dictLiteralElement ) ) >> ']' );
	HRule parameter( ( name ^ "..." ) >> -( '=' >> expression ) );
	HRule variadicParameter( name >> "..." );
	HRule nameList( parameter >> ( * ( ',' >> parameter ) ) );
	HRule statement;
	HRule callable( e_p::constant( '(' ) >> -( ( nameList >> -( ',' >> variadicParameter ) ) | variadicParameter ) >> ')' >> '{' >> *statement >> '}' );
	HRule lambda( e_p::constant( '@' ) >> -( '[' >> name >> *( ',' >> name ) >> ']' ) >> callable );
	HRule subscriptOperator( '[' >> ( ( ( ':' >> -expression ) | ( expression >> -( ':' >> -expression ) ) ) >> -( ':' >> -expression ) ) >> ']' );
	HRule literalNone( e_p::constant( "none" ) );
	HRule booleanLiteralTrue( e_p::constant( "true" ) );
	HRule booleanLiteralFalse( e_p::constant( "false" ) );
	HRule number( '$' >> real );
	HRule memberAccess( '.' >> name );
	HRule dereference( *( subscriptOperator | functionCallOperator | memberAccess ) );
	HRule atom(
	 	absoluteValue
	 	| ( parenthesis >> -( memberAccess >> dereference ) )
	 	| real
	 	| integer
	 	| ( ( number | character_literal ) >> -( memberAccess >> functionCallOperator ) )
	 	| ( ( tupleLiteral | listLiteral | dictLiteral | lookupLiteral | string_literal ) >> -( ( subscriptOperator | memberAccess ) >> dereference ) )
		| ( setLiteral >> -( memberAccess >> dereference ) )
	 	| literalNone
	 	| booleanLiteralTrue
	 	| booleanLiteralFalse
	 	| ( name >> dereference )
	 	| ( lambda >> -( functionCallOperator >> dereference ) )
	);
	HRule factorial( atom >> -( ( character( '!' ) & "==" ) | ( character( '!' ) ^ '=' ) ) );
	HRule booleanNot( ( '-' >> factorial ) | factorial );
	HRule negation;
	HRule power( booleanNot >> ( * ( '^' >> negation ) ) );
	negation %= ( ( '-' >> negation ) | power );
	HRule multiplication( negation >> ( * ( '*' >> negation ) ) );
	HRule sum( multiplication >> ( * ( '+' >> multiplication ) ) );
	HRule compare( sum >> -( ( string( "<=" ) | ">=" | "<" | ">" ) >> sum ) );
	HRule equals( compare >> -( ( string( "==" ) | "!=" ) >> compare ) );
	HRule booleanAnd( equals >> *( "&&" >> equals ) );
	HRule booleanOr( booleanAnd >> *( string( "||" ) >> booleanAnd ) );
	HRule booleanXor( booleanOr >> -( string( "^^" ) >> booleanOr ) );
	HRule ternary( booleanXor >> -( '?' >> expression >> ':' >> expression ) );
	HRule value( ternary );
	HRule subscript( name >> +( subscriptOperator | functionCallOperator | memberAccess ) );
	HRule assignable( subscript | name );
	expression %= ( *( ( assignable >> ( string( "=" ) | "+=" | "-=" | "*=" | "/=" | "%=" | "^=" ) ) ^ '=' ) >> value );
	HRule expressionStatement( expression >> ';' );
	HRule loopScope;
	HRule scope( '{' >> *statement >> '}' );
	HRule catchStatement( e_p::constant( "catch" ) >> '(' >> name >> assignable >> ')' >> scope );
	HRule tryCatchStatement( e_p::constant( "try" ) >> scope >> +catchStatement );
	HRule ifClause( e_p::constant( "if" ) >> '(' >> expression >> ')' >> scope );
	HRule ifStatement(
		ifClause >>
		*( e_p::constant( "else" ) >> ifClause ) >>
		-( e_p::constant( "else" ) >> scope )
	);
	HRule continueStatement( e_p::constant( "continue" ) >> ';' );
	HRule throwStatement( e_p::constant( "throw" ) >> expression >> ';' );
	HRule breakStatement( e_p::constant( "break" ) >> ';' );
	HRule whileStatement( e_p::constant( "while" ) >> '(' >> expression >> ')' >> loopScope );
	HRule forStatement( e_p::constant( "for" ) >> '(' >> assignable >> ':' >> expression >> ')' >> loopScope );
	HRule caseStatement( e_p::constant( "case" ) >> '(' >> integer >> ')' >> ':' >> scope );
	HRule defaultStatement( e_p::constant( "default" ) >> ':' >> scope );
	HRule switchStatement( e_p::constant( "switch" ) >> '(' >> expression >> ')' >> '{' >> +caseStatement >> '}' );
	HRule returnStatement( e_p::constant( "return" ) >> '(' >> expression >> ')' >> ';' );
	statement %= ( ifStatement | whileStatement | forStatement | switchStatement | tryCatchStatement | throwStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope );
	HRule loopStatement( ifStatement | whileStatement | forStatement | switchStatement | tryCatchStatement | throwStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope );
	loopScope %= ( '{' >> *loopStatement >> '}' );
	HRule functionDefinition( name >> callable );
	HRule field( name >> '=' >> ( expression ) >> ';' );
	HRule classDefinition( e_p::constant( "class" ) >> name >> -( ':' >> name ) >> '{' >> +( field | functionDefinition ) >> '}' );
	HRule importStatement( e_p::constant( "import" ) >> name >> "as" >> name >> ';' );
	HRule hg( + ( classDefinition | functionDefinition | importStatement ) );
	HExecutingParser ep( hg ); /* test for infinite recursion */
	char const huginnDesc[][640] = {
		"A_ = +( ( \"class\" >> B_ >> -( ':' >> B_ ) >> '{' >> +( ( B_ >> '=' >> C_ >> ';' ) | D_ ) >> '}' ) | D_ | ( \"import\" >> B_ >> \"as\" >> B_ >> ';' ) )",
		"B_ = regex( \"\\b[a-zA-Z_][a-zA-Z0-9_]*\\b\" )",
		"C_ = ( *( ( E_ >> ( \"=\" | \"+=\" | \"-=\" | \"*=\" | \"/=\" | \"%=\" | \"^=\" ) ) ^ '=' ) >> ( ( F_ >> -( \"^^\" >> F_ ) ) >> -( '?' >> C_ >> ':' >> C_ ) ) )",
		"D_ = ( B_ >> G_ )",
		"E_ = ( ( B_ >> +( H_ | I_ | J_ ) ) | B_ )",
		"F_ = ( K_ >> *( \"||\" >> K_ ) )",
		"G_ = ( '(' >> -( ( ( L_ >> *( ',' >> L_ ) ) >> -( ',' >> M_ ) ) | M_ ) >> ')' >> '{' >> *N_ >> '}' )",
		"H_ = ( '[' >> ( ( ( ':' >> -C_ ) | ( C_ >> -( ':' >> -C_ ) ) ) >> -( ':' >> -C_ ) ) >> ']' )",
		"I_ = ( ( '(' >> -( O_ >> -( ',' >> P_ ) ) >> ')' ) | ( '(' >> -P_ >> ')' ) )",
		"J_ = ( '.' >> B_ )",
		"K_ = ( Q_ >> *( \"&&\" >> Q_ ) )",
		"L_ = ( ( B_ ^ \"...\" ) >> -( '=' >> C_ ) )",
		"M_ = ( B_ >> \"...\" )",
		"N_ = ( R_ | S_ | T_ | U_ | V_ | W_ | X_ | Y_ | Z_ | AA_ | AB_ )",
		"O_ = ( AC_ >> *( ',' >> AC_ ) )",
		"P_ = ( AD_ >> *( ',' >> AD_ ) )",
		"Q_ = ( AE_ >> -( ( \"==\" | \"!=\" ) >> AE_ ) )",
		"R_ = ( AF_ >> *( \"else\" >> AF_ ) >> -( \"else\" >> AB_ ) )",
		"S_ = ( \"while\" >> '(' >> C_ >> ')' >> AG_ )",
		"T_ = ( \"for\" >> '(' >> E_ >> ':' >> C_ >> ')' >> AG_ )",
		"U_ = ( \"switch\" >> '(' >> C_ >> ')' >> '{' >> +( \"case\" >> '(' >> integer >> ')' >> ':' >> AB_ ) >> '}' )",
		"V_ = ( \"try\" >> AB_ >> +( \"catch\" >> '(' >> B_ >> E_ >> ')' >> AB_ ) )",
		"W_ = ( \"throw\" >> C_ >> ';' )",
		"X_ = ( \"break\" >> ';' )",
		"Y_ = ( \"continue\" >> ';' )",
		"Z_ = ( \"return\" >> '(' >> C_ >> ')' >> ';' )",
		"AA_ = ( C_ >> ';' )",
		"AB_ = ( '{' >> *N_ >> '}' )",
		"AC_ = ( C_ ^ ':' )",
		"AD_ = ( B_ >> ':' >> C_ )",
		"AE_ = ( AH_ >> -( ( \"<=\" | \">=\" | \"<\" | \">\" ) >> AH_ ) )",
		"AF_ = ( \"if\" >> '(' >> C_ >> ')' >> AB_ )",
		"AG_ = ( '{' >> *( R_ | S_ | T_ | U_ | V_ | W_ | X_ | Y_ | Z_ | AA_ | AB_ ) >> '}' )",
		"AH_ = ( AI_ >> *( '+' >> AI_ ) )",
		"AI_ = ( AJ_ >> *( '*' >> AJ_ ) )",
		"AJ_ = ( ( '-' >> AJ_ ) | ( ( ( '-' >> AK_ ) | AK_ ) >> *( '^' >> AJ_ ) ) )",
		"AK_ = ( ( ( '|' >> C_ >> '|' ) | ( ( '(' >> C_ >> ')' ) >> -( J_ >> AL_ ) ) | real | integer"
			" | ( ( ( '$' >> real ) | character_literal ) >> -( J_ >> I_ ) ) | ( ( ( '(' >> -O_ >> -',' >> ')' )"
			" | ( '[' >> -O_ >> ']' ) | ( '{' >> -( AM_ >> *( ',' >> AM_ ) ) >> '}' )"
			" | ( '[' >> -( AM_ >> *( ',' >> AM_ ) ) >> ']' ) | string_literal ) >> -( ( H_ | J_ ) >> AL_ ) )"
			" | ( ( '{' >> C_ >> *( ',' >> C_ ) >> '}' ) >> -( J_ >> AL_ ) ) | \"none\" | \"true\" | \"false\""
			" | ( B_ >> AL_ ) | ( ( '@' >> -( '[' >> B_ >> *( ',' >> B_ ) >> ']' ) >> G_ ) >> -( I_ >> AL_ ) ) ) >> -( ( '!' & \"==\" )"
			" | ( '!' ^ '=' ) ) )",
		"AL_ = *( H_ | I_ | J_ )",
		"AM_ = ( C_ >> ':' >> C_ )"
	};
	cout << "hg:" << endl;
	HGrammarDescription gd( hg );
	static int const COUNT( static_cast<int>( end( huginnDesc ) - begin( huginnDesc ) ) );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		cout << *it << endl;
		if ( i < COUNT ) {
			ENSURE_EQUALS( "wrong grammar description", *it, huginnDesc[i] );
		}
	}
	ENSURE_EQUALS( "wrong grammar description", i, COUNT );
TUT_TEARDOWN()

TUT_UNIT_TEST( "forwarding rules: A = B, C = B, C = regex() >> '=' >> real" )
	/* no names, no actions */ {
		char const desc[][64] = {
			"A_ = ( regex( \"[a-z]*\" ) >> '=' >> real )"
		};

		HRule C( regex( "[a-z]*" ) >> '=' >> real );
		HRule B( C );
		HRule A( B );

		HGrammarDescription gd( A );
		static int const COUNT( static_cast<int>( end( desc ) - begin( desc ) ) );
		int i( 0 );
		for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
			if ( i < COUNT ) {
				ENSURE_EQUALS( "wrong grammar description", *it, desc[i] );
			}
			cout << *it << endl;
		}
		ENSURE_EQUALS( "wrong grammar description", i, COUNT );
	}
	/* all names, no actions */ {
		char const desc[][64] = {
			"AA = ( regex( \"[a-z]*\" ) >> '=' >> real )"
		};

		HRule C( "CC", regex( "[a-z]*" ) >> '=' >> real );
		HRule B( "BB", C );
		HRule A( "AA", B );

		HGrammarDescription gd( A );
		static int const COUNT( static_cast<int>( end( desc ) - begin( desc ) ) );
		int i( 0 );
		for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
			if ( i < COUNT ) {
				ENSURE_EQUALS( "wrong grammar description", *it, desc[i] );
			}
			cout << *it << endl;
		}
		ENSURE_EQUALS( "wrong grammar description", i, COUNT );
	}
	/* no names, all actions */ {
		char const desc[][64] = {
			"A_ = ( regex( \"[a-z]*\" ) >> '=' >> real )"
		};

		HRule C( regex( "[a-z]*" ) >> '=' >> real, HRuleBase::action_t( call( &noop ) ) );
		HRule B( C, HRuleBase::action_t( call( &noop ) ) );
		HRule A( B, HRuleBase::action_t( call( &noop ) ) );

		HGrammarDescription gd( A );
		static int const COUNT( static_cast<int>( end( desc ) - begin( desc ) ) );
		int i( 0 );
		for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
			if ( i < COUNT ) {
				ENSURE_EQUALS( "wrong grammar description", *it, desc[i] );
			}
			cout << *it << endl;
		}
		ENSURE_EQUALS( "wrong grammar description", i, COUNT );
	}
	/* all names, all actions */ {
		char const desc[][64] = {
			"AA = BB",
			"BB = CC",
			"CC = ( regex( \"[a-z]*\" ) >> '=' >> real )"
		};

		HRule C( "CC", regex( "[a-z]*" ) >> '=' >> real, HRuleBase::action_t( call( &noop ) ) );
		HRule B( "BB", C, HRuleBase::action_t( call( &noop ) ) );
		HRule A( "AA", B, HRuleBase::action_t( call( &noop ) ) );

		HGrammarDescription gd( A );
		static int const COUNT( static_cast<int>( end( desc ) - begin( desc ) ) );
		int i( 0 );
		for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
			if ( i < COUNT ) {
				ENSURE_EQUALS( "wrong grammar description", *it, desc[i] );
			}
			cout << *it << endl;
		}
		ENSURE_EQUALS( "wrong grammar description", i, COUNT );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "two names for one rule" )
	char const desc[][64] = {
		"AA = ( ( '[' >> CC >> ']' ) | BB )",
		"CC = ( regex( \"[a-z]*\" ) >> '=' >> real )",
		"BB = CC"
	};
	HRule C( "CC", regex( "[a-z]*" ) >> '=' >> real, HRuleBase::action_t( call( &noop ) ) );
	HRule B( "BB", C );
	HRule A( "AA", ( '[' >> C >> ']' ) | B );
	HGrammarDescription gd( A );
	static int const COUNT( static_cast<int>( end( desc ) - begin( desc ) ) );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		if ( i < COUNT ) {
			ENSURE_EQUALS( "wrong grammar description", *it, desc[i] );
		}
		cout << *it << endl;
	}
	ENSURE_EQUALS( "wrong grammar description", i, COUNT );
TUT_TEARDOWN()

TUT_UNIT_TEST( "two names for one rule with recursion" )
	char const desc[][80] = {
		"AA = ( ( '[' >> CC >> ']' ) | BB )",
		"CC = ( regex( \"[a-z]*\" ) >> '=' >> real >> -( '(' >> AA >> ')' ) )",
		"BB = CC"
	};
	HRule A( "AA" );
	HRule C( "CC", regex( "[a-z]*" ) >> '=' >> real >> - ( '(' >> A >> ')' ), HRuleBase::action_t( call( &noop ) ) );
	HRule B( "BB", C );
	A %= ( ( '[' >> C >> ']' ) | B );
	HGrammarDescription gd( A );
	static int const COUNT( static_cast<int>( end( desc ) - begin( desc ) ) );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		if ( i < COUNT ) {
			ENSURE_EQUALS( "wrong grammar description", *it, desc[i] );
		}
		cout << *it << endl;
	}
	ENSURE_EQUALS( "wrong grammar description", i, COUNT );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find by name" )
	HHuginn h;
	HRule hg( h.make_engine() );
	HRuleBase const* fun( hg.find( "functionDefinition" ) );
	ENSURE( "find by name failed", fun != nullptr );
	HExecutingParser ep( *fun );
	ENSURE( "invalid rule from find", ep( "foo( arg0, arg1 = 0 ) { return ( arg0 + arg1 ); }" ) );
	ENSURE_NOT( "invalid rule from find", ep( "class A { foo( arg0, arg1 = 0 ) { return ( arg0 + arg1 ); } }" ) );
TUT_TEARDOWN()

struct calc {
	typedef enum {
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		POWER,
		PAREN,
		NONE
	} oper_t;
	typedef HStack<double long> vars_t;
	typedef HStack<oper_t> opers_t;
	typedef HBoundCall<> execution_step_t;
	typedef void ( calc::*action_t )( void );
	typedef HList<execution_step_t> execution_steps_t;
	execution_steps_t _deferred;
	vars_t _vars;
	opers_t _opers;
	calc( void )
		: _deferred(), _vars(), _opers() {
	}
	void sum( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
		double long v1( _vars.top() );
		_vars.pop();
		double long v2( _vars.top() );
		_vars.pop();
		_vars.push( v1 + v2 );
	}
	void plus_minus( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
		double long v1( _vars.top() );
		_vars.pop();
		double long v2( _vars.top() );
		_vars.pop();
		oper_t o( _opers.top() );
		_opers.pop();
		clog << v1 << ( o == PLUS ? '+' : '-' ) << v2 << '=' << ( v1 + v2 ) << endl;
		_vars.push( o == PLUS ? v1 + v2 : v2 - v1 );
	}
	void mul( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
		double long v1( _vars.top() );
		_vars.pop();
		double long v2( _vars.top() );
		_vars.pop();
		_vars.push( v1 * v2 );
	}
	void mul_div( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
		double long v1( _vars.top() );
		_vars.pop();
		double long v2( _vars.top() );
		_vars.pop();
		oper_t o( _opers.top() );
		_opers.pop();
		_vars.push( o == MULTIPLY ? v1 * v2 : v2 / v1 );
	}
	void mul_div_p( executing_parser::position_t ) {
		mul_div();
	}
	void power( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
		while ( ! _opers.is_empty() && ( _opers.top() == POWER ) ) {
			double long v1( _vars.top() );
			_vars.pop();
			double long v2( _vars.top() );
			_vars.pop();
			_vars.push( pow( static_cast<double>( v2 ), static_cast<double>( v1 ) ) );
			_opers.pop();
		}
	}
	void deferred_action( action_t action_ ) {
		_deferred.push_back( call( action_, this ) );
	}
	void oper( code_point_t op_ ) {
		clog << __PRETTY_FUNCTION__ << ": " << op_ << endl;
		oper_t o( NONE );
		switch ( op_.get() ) {
			case ( '+' ): o = PLUS; break;
			case ( '-' ): o = MINUS; break;
			case ( '*' ): o = MULTIPLY; break;
			case ( '/' ): o = DIVIDE; break;
			case ( '^' ): o = POWER; break;
			case ( '(' ): o = PAREN; break;
			default: M_ASSERT( !"bad oper"[0] );
		}
		_opers.push( o );
	}
	void close_paren( void ) {
		M_ENSURE( _opers.top() == PAREN );
		_opers.pop();
	}
	void deferred_oper( code_point_t op_ ) {
		_deferred.push_back( call( &calc::oper, this, op_ ) );
	}
	void val( double long v_ ) {
		clog << __PRETTY_FUNCTION__ << endl;
		_vars.push( v_ );
	}
	void deferred_val( double long v_ ) {
		_deferred.push_back( call( &calc::val, this, v_ ) );
	}
	void execute( void ) {
		for ( execution_step_t& e : _deferred ) {
			e();
		}
		return;
	}
	void reset( void ) {
		_deferred.clear();
	}
};

TUT_UNIT_TEST( "calc (sum)" )
	calc c;
	HRule realVal( real[HBoundCall<void ( double long )>( call( &calc::val, &c, _1 ) )] );
	HRule r( realVal >> *( ( '+' >> realVal )[HBoundCall<void ( void )>( call( &calc::sum, &c ) )] ) );
	HExecutingParser ep( r );
	ep( "1.7+2.4+-7" );
	ep();
	ENSURE_DISTANCE( "bad value calculated from +", c._vars.top(), -2.9l, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "calc (sum, mul)" )
	calc c;
	HRule realVal( real[HBoundCall<void ( double long )>( call( &calc::val, &c, _1 ) )] );
	HRule multiply( realVal >> *( ( '*' >> realVal )[HBoundCall<void ( void )>( call( &calc::mul, &c ) )] ) );
	HRule r( multiply >> *( ( '+' >> multiply )[HBoundCall<void ( void )>( call( &calc::sum, &c ) )] ) );
	HExecutingParser ep( r );

	ep( "1.7*2+2.4+-7" );
	ep();
	ENSURE_DISTANCE( "bad value calculated from +*", c._vars.top(), -1.2l, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "calc, (sum, mul, recursion)" )
	calc c;
	HRule expr;
	HRule paren( '(' >> expr >> ')' );
	HRule realVal( real[HBoundCall<void ( double long )>( call( &calc::val, &c, _1 ) )] );
	HRule atom( realVal | paren );
	HRule mulExec( '*' >> atom );
	HRule multiply( atom >> *( mulExec[HBoundCall<void ( void )>( call( &calc::mul, &c ) )] ) );
	HRule addExec( "sum", HBoundCall<void ( void )>( call( &calc::sum, &c ) ) );
	addExec %= ( '+' >> multiply );
	HRule r( multiply >> *( addExec ) );
	expr %= r;
	HExecutingParser ep( r );

	ep( "1.7*(2+2.4)+-7+2*3" );
	ep();
	ENSURE_DISTANCE( "bad value calculated from +*()", c._vars.top(), 6.48l, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "calc, (plus, minus, mul, div, recursion)" )
	calc c;
	HRule expr;
	HRule paren( '(' >> expr >> ')' );
	HRule realVal( real[HBoundCall<void ( double long )>( call( &calc::val, &c, _1 ) )] );
	HRule atom( realVal | paren );
	HRule mulExec( HBoundCall<void ( executing_parser::position_t )>( call( &calc::mul_div_p, &c, _1 ) ) );
	mulExec %= ( character( "*/" )[HBoundCall<void ( code_point_t )>( call( &calc::oper, &c, _1 ) )] >> atom );
	HRule multiply( atom >> *( mulExec ) );
	HRule addExec( HBoundCall<void ( void )>( call( &calc::plus_minus, &c ) ) );
	addExec %= ( character( "+-" )[HBoundCall<void ( code_point_t )>( call( &calc::oper, &c, _1 ) )] >> multiply );
	HRule r( multiply >> *( addExec ) );
	expr %= r;
	HExecutingParser ep( r );

	ep( "(1.7*(2+2.4)+-7+2*3-5)/2" );
	ep();
	ENSURE_DISTANCE( "bad value calculated from +*()", c._vars.top(), 0.74l, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "calc(deferred), (plus, minus, mul, div, recursion)" )
	calc c;
	HRule expr;
	HRule paren( '(' >> expr >> ')' );
	HRule realVal( real[HBoundCall<void ( double long )>( call( &calc::deferred_val, &c, _1 ) )] );
	HRule atom( realVal | paren );
	HRule multiply( atom >> *( ( character( "*/" )[HBoundCall<void ( code_point_t )>( call( &calc::deferred_oper, &c, _1 ) )] >> atom )[HBoundCall<void ( void )>( call( &calc::deferred_action, &c, &calc::mul_div ) )] ) );
	HRule r( multiply >> *( ( character( "+-" )[HBoundCall<void ( code_point_t )>( call( &calc::deferred_oper, &c, _1 ) )] >> multiply )[HBoundCall<void ( void )>( call( &calc::deferred_action,  &c, &calc::plus_minus ) )] ) );
	expr %= r;
	HExecutingParser ep( r );

	ep( "(1.7*(2+2.4)+-7+2*3-5)/2" );
	ep();
	ENSURE( "non empty stack on deferred executor", c._vars.is_empty() );
	c.execute();
	ENSURE_DISTANCE( "bad value calculated from +*()", c._vars.top(), 0.74l, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "associativity: calc(deferred), (plus, minus, mul, div, power, recursion)" )
	calc c;
	HRule expr;
	HRule paren( character( '(' )[HCharacterLiteral::action_character_t( call( &calc::deferred_oper, &c, _1 ) )] >> expr >> character( ')' )[HRuleBase::action_t( call( &calc::deferred_action, &c, &calc::close_paren ) )] );
	HRule realVal( real[HReal::action_double_long_t( call( &calc::deferred_val, &c, _1 ) )] );
	HRule atom( realVal | paren );
	HRule power( atom >> *( ( character( "^" )[HCharacterLiteral::action_character_t( call( &calc::deferred_oper, &c, _1 ) )] >> atom ) ), HBoundCall<void ( void )>( call( &calc::deferred_action, &c, &calc::power ) ) );
	HRule multiply( power >> *( ( character( "*/" )[HBoundCall<void ( code_point_t )>( call( &calc::deferred_oper, &c, _1 ) )] >> power )[HBoundCall<void ( void )>( call( &calc::deferred_action, &c, &calc::mul_div ) )] ) );
	HRule r( multiply >> *( ( character( "+-" )[HBoundCall<void ( code_point_t )>( call( &calc::deferred_oper, &c, _1 ) )] >> multiply )[HBoundCall<void ( void )>( call( &calc::deferred_action,  &c, &calc::plus_minus ) )] ) );
	expr %= r;
	HExecutingParser ep( r );
	ep( "(1.7*(2+2.4)+-7+2*3-5)/2" );
	ep();
	ENSURE( "non empty stack on deferred executor", c._vars.is_empty() );
	c.execute();
	ENSURE_DISTANCE( "bad value calculated from +*()", c._vars.top(), 0.74L, epsilon );
	c._vars.pop();
	c.reset();
	ep( "4^3^2" );
	ep();
	ENSURE( "non empty stack on deferred executor", c._vars.is_empty() );
	c.execute();
	clog << "res = " << c._vars.top() << endl;
	ENSURE_DISTANCE( "bad value calculated from +*()", c._vars.top(), 262144.L, epsilon );
	c._vars.pop();
	c.reset();
	ep( "(1+1+1+1)^(1+1+1)^(1+1)" );
	ep();
	ENSURE( "non empty stack on deferred executor", c._vars.is_empty() );
	c.execute();
	clog << "res = " << c._vars.top() << endl;
	ENSURE_DISTANCE( "bad value calculated from +*()", c._vars.top(), 262144.L, epsilon );
	c._vars.pop();
	c.reset();
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "the test" )
	HArray<double> v;
	HRule realNo( real[push_back<double>( v )] );
	ENSURE( "parsing correct input (single real) failed", HExecutingParser( realNo )( "3.141592653589793" ) );
	HRule r( realNo >> *( ',' >> realNo ) );
	HExecutingParser ep( r );
	ENSURE( "parsing correct input (coma separated set of reals) failed", ep( "3.141592653589793, -2.718281828459045, 17" ) );
	ep();
	char const data[] = "3.141592653589793, -2.718281828459045, 17, kupa";
	int long bad( strstr( data, "kupa" ) - data );
	ENSURE_NOT( "parsing incorrect input (coma separated set of reals plus trash) succeeded", ep( data ) );
	ENSURE_EQUALS( "error position given incorrectly", ep.error_position(), bad );
	ENSURE_EQUALS( "bad error message", ep.error_messages()[0], "expected real number" );
	copy( v.begin(), v.end(), stream_iterator( cout, endl ) );
TUT_TEARDOWN()

}

