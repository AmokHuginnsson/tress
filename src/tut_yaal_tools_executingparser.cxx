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

#include <yaal/hcore/hstack.hxx>
#include <yaal/tools/executingparser.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace yaal;
using namespace yaal::hcore;

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

}

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::executing_parser;
using namespace tress::tut_helpers;

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
	/* double */ {
		double val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double )>( call( &defer<double>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double).", ep( "3.14" ) );
		ep();
		ENSURE_DISTANCE( "double value not set by ExecutingParser.", static_cast<double long>( val ), 3.14l, epsilon );
	}
	/* double long */ {
		double long val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double long )>( call( &defer<double long>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double long).", ep( "3.14" ) );
		ep();
		ENSURE_DISTANCE( "double long value not set by ExecutingParser.", val, 3.14l, epsilon );
	}
	/* HNumber */ {
		HNumber val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( HNumber const& )>( call( &defer<HNumber, HNumber const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HNumber).", ep( "3.141592653589793" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, "3.141592653589793" );
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
	/* int long */ {
		int long val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int long )>( call( &defer<int long>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int long).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int long value not set by ExecutingParser.", val, 7l );
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
	/* HString */ {
		hcore::HString val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (HString).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "7" );
	}
	/* bad integer */ {
		HExecutingParser ep( integer );
		ENSURE_NOT( "Invalid input parsed by HInteger", ep( "bad" ) );
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
	ENSURE_NOT( "string literal with invalid character parsed", ep( "\"Al\ba\"" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HCharacterLiteral" )
	typedef HArray<char> characters_t;
	characters_t c;
	HRule cl( character_literal[push_back<char>( c )] );
	HRule r( cl >> *( ',' >> cl ) );
	HExecutingParser ep( r );
	/* simple */ {
		ENSURE( "HCharacterLiteral failed to parse correct input", ep( "'A','\\t'" ) );
		ep();
		char const expected[] = {
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
		char const expected[] = "\n \t\t\b\033\\'x";
		int i( 0 );
		for ( characters_t::const_iterator it( c.begin() ), end( c.end() ); it != end; ++ it, ++ i ) {
			ENSURE( "too many elements acquired", i < ( countof ( expected ) - 1 ) );
			ENSURE_EQUALS( "Failed to acquire character from character literal", *it, expected[i] );
		}
		ENSURE_EQUALS( "not all elemets acquired", i, countof ( expected ) - 1 );
	}
	ENSURE_NOT( "non-character literal parsed", ep( "Ala" ) );
	ENSURE_NOT( "unfinished character literal parsed", ep( "'A" ) );
	ENSURE_NOT( "character literal with invalid character parsed", ep( "'\b'" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HCharacter" )
	/* char (any) */ {
		char val( 0 );
		HExecutingParser ep( character[HBoundCall<void ( char )>( call( &defer<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", ep( "a" ) );
		ep();
		ENSURE_EQUALS( "char value not set by ExecutingParser.", val, 'a' );
	}
	/* char (specific ok) */ {
		char val( 0 );
		HExecutingParser ep( character( 'a' )[HBoundCall<void ( char )>( call( &defer<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", ep( "a" ) );
	}
	/* char (specific, any of ok) */ {
		char val( 0 );
		HExecutingParser ep( character( "ab" )[HBoundCall<void ( char )>( call( &defer<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", ep( "b" ) );
	}
	/* char (specific fail) */ {
		char val( 0 );
		HExecutingParser ep( character( 'X' )[HBoundCall<void ( char )>( call( &defer<char>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HCharacter parsed invalid input.", ep( "a" ) );
	}
	/* char (specific any of fail) */ {
		char val( 0 );
		HExecutingParser ep( character( "ab" )[HBoundCall<void ( char )>( call( &defer<char>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HCharacter parsed invalid input.", ep( "c" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HString" )
	/* ok */ {
		hcore::HString val;
		HExecutingParser ep( string( "ala" )[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HString failed to parse correct input.", ep( "ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
	}
	/* fail */ {
		hcore::HString val;
		HExecutingParser ep( string( "XXX" )[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HString parsed invalid input.", ep( "ala" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HRegex" )
	/* ok */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "12.34" );
	}
	/* fail not fully consumed input */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HExecutingParser accepted parse on partial input.", ep( "12.345" ) );
	}
	/* fail */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &defer<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HRegex parsed invalid input.", ep( "12.3a" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFollows" )
	/* parsed */ {
		char fcData( 0 );
		HRule fc( character( 'a' )[HBoundCall<void ( char )>( call( &defer<char>::set, ref( fcData ), _1 ) )] );
		char scData( 0 );
		HRule sc( character( 'b' )[HBoundCall<void ( char )>( call( &defer<char>::set, ref( scData ), _1 ) )] );
		bool followsCalled( false );
		HExecutingParser ep( ( fc >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( followsCalled ), true ) ) ] );
		ENSURE( "parse on correct failed", ep( "ab" ) );
		ep();
		ENSURE_EQUALS( "predecessor in follows not called", fcData, 'a' );
		ENSURE_EQUALS( "successor in follows not called", scData, 'b' );
		ENSURE( "follows not called", followsCalled );
	}
	/* failed on successor */ {
		char fcData( 0 );
		HRule fc( character( 'a' )[HBoundCall<void ( char )>( call( &defer<char>::set, ref( fcData ), _1 ) )] );
		char scData( 0 );
		HRule sc( character( 'b' )[HBoundCall<void ( char )>( call( &defer<char>::set, ref( scData ), _1 ) )] );
		bool followsCalled( false );
		HExecutingParser ep( ( fc >> sc )[HBoundCall<void ( void )>( call( &defer<bool>::set, ref( followsCalled ), true ) ) ] );
		ENSURE_NOT( "parse on invalid succeeded", ep( "aa" ) );
	}
TUT_TEARDOWN()

template<typename T>
void sum( T& sum_, T val_ ) {
	sum_ += val_;
}

TUT_UNIT_TEST( "HKleeneStar" )
	/* parsed (non empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &sum<int>, ref( val ), _1 ) )] );
		HRule nums( *( ',' >> i ) );
		HExecutingParser ep( nums );
		ENSURE( "parse on valid failed", ep( ", 1, 2, 3" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 6 );
	}
	/* parsed (empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &sum<int>, ref( val ), _1 ) )] );
		HRule nums( *( ',' >> i ) );
		HExecutingParser ep( string( "nums{" ) >> nums >> "}" );
		ENSURE( "parse on valid (but empty) failed", ep( "nums{}" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 0 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HKleenePlus" )
	/* parsed (non empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &sum<int>, ref( val ), _1 ) )] );
		HRule nums( +( ',' >> i ) );
		HExecutingParser ep( nums );
		ENSURE( "parse on valid failed", ep( ", 1, 2, 3" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 6 );
	}
	/* parsed (exactly) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &sum<int>, ref( val ), _1 ) )] );
		HRule nums( +( ',' >> i ) );
		HExecutingParser ep( nums );
		ENSURE( "parse on valid failed", ep( ", 1" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 1 );
	}
	/* not-parsed (empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &sum<int>, ref( val ), _1 ) )] );
		HRule nums( +( ',' >> i ) );
		HExecutingParser ep( string( "nums{" ) >> nums >> "}" );
		ENSURE_NOT( "parse on invalid (empty) succeeded", ep( "nums{}" ) );
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
	/* parsed (non-empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> (-i) >> "}" );
		ENSURE( "parse on valid failed", ep( "nums{7}" ) );
		ep();
		ENSURE_EQUALS( "execution of optional failed", val, 7 );
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

TUT_UNIT_TEST( "HAlternative" )
	int val( 0 );
	int val_alt( 0 );
	HRule i( integer[HBoundCall<void ( int )>( call( &defer<int>::set, ref( val ), _1 ) )] );
	HRule ia( integer[HBoundCall<void ( int )>( call( &defer<int>::set_alt, ref( val_alt ), _1 ) )] );
	HExecutingParser ep( string( "nums{" ) >> ( ( i >> ":pos" ) | ( ia >> ":neg" ) ) >> "}" );
	ENSURE( "parse on valid failed", ep( "nums{7:neg}" ) );
	ep();
	ENSURE_EQUALS( "execution failed sub-step not removed", val, 0 );
	ENSURE_EQUALS( "execution proper execution sub-step not applied", val_alt, -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "left recursion" )
	/* follows */ {
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
	}
	/* alternative */ {
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
	}
	/* optional */ {
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
	}
	/* kleene star */ {
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
	}
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
	HExecutingParser ep2( eq );
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

TUT_UNIT_TEST( "infinite recursion bug" )
	HRule A;
	HRule B( A | integer );
	HRule C;
	C %= ( real >> B );
	A %= ( -C >> B );
	try {
		HExecutingParser ep( A );
		ep( "m(){return(0);}" );
		FAIL( "Failed to detect ifinite recursion in grammar." );
	} catch ( HExecutingParserException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "unnamed HHuginn grammar" )
	namespace e_p = executing_parser;
	HRule name( regex( "\\<[a-zA-Z_][a-zA-Z0-9_]*\\>" ) );
	HRule expression;
	HRule absoluteValue( '|' >> expression >> '|' );
	HRule parenthesis( '(' >> expression >> ')' );
	HRule argList( expression >> ( * ( ',' >> expression ) ) );
	HRule functionCall( name >> '(' >> -argList >> ')' );
	HRule subscript;
	HRule atom( absoluteValue | parenthesis | real | integer | character_literal | subscript | functionCall | string_literal | name );
	HRule negation( ( '-' >> atom ) | atom );
	HRule power( negation >> ( * ( '^' >> negation ) ) );
	HRule multiplication( power >> ( * ( '*' >> power ) ) );
	HRule sum( multiplication >> ( * ( '+' >> multiplication ) ) );
	HRule value( sum );
	subscript %= ( ( functionCall | name | string_literal ) >> +( '[' >> ( subscript | value ) >> ']' ) );
	HRule assignment( *( ( subscript | name ) >> '=' ) >> value );
	expression %= assignment;
	HRule booleanExpression;
	HRule booleanValue( e_p::constant( "true" ) | e_p::constant( "false" ) | e_p::constant( '(' ) >> booleanExpression >> ')' );
	HRule booleanEquals( expression >> "==" >> expression );
	HRule booleanNotEquals( expression >> "!=" >> expression );
	HRule booleanLess( expression >> '<' >> expression );
	HRule booleanGreater( expression >> '>' >> expression );
	HRule booleanLessEq( expression >> "<=" >> expression );
	HRule booleanGreaterEq( expression >> ">=" >> expression );
	HRule booleanAnd( booleanValue >> "&&" >> booleanValue );
	HRule booleanOr( booleanValue >> "||" >> booleanValue );
	HRule booleanXor( booleanValue >> "^^" >> booleanValue );
	HRule booleanNot( e_p::constant( '!' ) >> booleanValue );
	booleanExpression %= ( booleanEquals | booleanNotEquals | booleanLess | booleanGreater | booleanLessEq | booleanGreaterEq | booleanAnd | booleanOr | booleanXor | booleanNot );
	HRule expressionStatement( expression >> ';' );
	HRule scope;
	HRule loopScope;
	HRule ifStatement(
		e_p::constant( "if" ) >> '(' >> booleanExpression >> ')' >> scope >>
		*( e_p::constant( "else" )>> e_p::constant( "if" ) >> '(' >> booleanExpression >> ')' >> scope ) >>
		-( e_p::constant( "else" ) >> scope )
	);
	HRule continueStatement( e_p::constant( "continue" ) >> ';' );
	HRule breakStatement( e_p::constant( "break" ) >> ';' );
	HRule whileStatement( e_p::constant( "while" ) >> '(' >> booleanExpression >> ')' >> loopScope );
	HRule forStatement( e_p::constant( "for" ) >> '(' >> name >> ':' >> expression >> ')' >> loopScope );
	HRule caseStatement( e_p::constant( "case" ) >> '(' >> integer >> ')' >> ':' >> scope );
	HRule defaultStatement( e_p::constant( "default" ) >> ':' >> scope );
	HRule switchStatement( e_p::constant( "switch" ) >> '(' >> expression >> ')' >> '{' >> +caseStatement >> '}' );
	HRule returnStatement( e_p::constant( "return" ) >> '(' >> expression >> ')' >> ';' );
	HRule statement( ifStatement | whileStatement | forStatement | switchStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope );
	HRule loopStatement( ifStatement | whileStatement | forStatement | switchStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope );
	scope %= ( '{' >> *statement >> '}' );
	loopScope %= ( '{' >> *loopStatement >> '}' );
	HRule nameList( name >> ( * ( ',' >> name ) ) );
	HRule functionDefinition( name >> '(' >> -nameList >> ')' >> scope );
	HRule hg( + functionDefinition );
	char const huginnDesc[][320] = {
		"A_ = +( B_ >> '(' >> -( B_ >> *( ',' >> B_ ) ) >> ')' >> C_ )",
		"B_ = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"C_ = ( '{' >> *( D_ | E_ | F_ | G_ | H_ | I_ | J_ | K_ | C_ ) >> '}' )",
		"D_ = ( \"if\" >> '(' >> L_ >> ')' >> C_ >> *( \"else\" >> \"if\" >> '(' >> L_ >> ')' >> C_ ) >> -( \"else\" >> C_ ) )",
		"E_ = ( \"while\" >> '(' >> L_ >> ')' >> M_ )",
		"F_ = ( \"for\" >> '(' >> B_ >> ':' >> N_ >> ')' >> M_ )",
		"G_ = ( \"switch\" >> '(' >> N_ >> ')' >> '{' >> +( \"case\" >> '(' >> integer >> ')' >> ':' >> C_ ) >> '}' )",
		"H_ = ( \"break\" >> ';' )",
		"I_ = ( \"continue\" >> ';' )",
		"J_ = ( \"return\" >> '(' >> N_ >> ')' >> ';' )",
		"K_ = ( N_ >> ';' )",
		"L_ = ( ( N_ >> \"==\" >> N_ ) | ( N_ >> \"!=\" >> N_ ) | ( N_ >> '<' >> N_ ) | ( N_ >> '>' >> N_ ) | ( N_ >> \"<=\" >> N_ ) | ( N_ >> \">=\" >> N_ ) | ( O_ >> \"&&\" >> O_ ) | ( O_ >> \"||\" >> O_ ) | ( O_ >> \"^^\" >> O_ ) | ( '!' >> O_ ) )",
		"M_ = ( '{' >> *( D_ | E_ | F_ | G_ | H_ | I_ | J_ | K_ | C_ ) >> '}' )",
		"N_ = ( *( ( P_ | B_ ) >> '=' ) >> Q_ )",
		"O_ = ( \"true\" | \"false\" | ( '(' >> L_ >> ')' ) )",
		"P_ = ( ( R_ | B_ | string_literal ) >> +( '[' >> ( P_ | Q_ ) >> ']' ) )",
		"Q_ = ( S_ >> *( '+' >> S_ ) )",
		"R_ = ( B_ >> '(' >> -( N_ >> *( ',' >> N_ ) ) >> ')' )",
		"S_ = ( T_ >> *( '*' >> T_ ) )",
		"T_ = ( U_ >> *( '^' >> U_ ) )",
		"U_ = ( ( '-' >> V_ ) | V_ )",
		"V_ = ( ( '|' >> N_ >> '|' ) | ( '(' >> N_ >> ')' ) | real | integer | character_literal | P_ | R_ | string_literal | B_ )"
	};
	cout << "hg:" << endl;
	HGrammarDescription gd( hg );
	static int const COUNT( static_cast<int>( end( huginnDesc ) - begin( huginnDesc ) ) );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		if ( i < COUNT ) {
			ENSURE_EQUALS( "wrong grammar description", *it, huginnDesc[i] );
		}
		cout << *it << endl;
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
	void oper( char op_ ) {
		clog << __PRETTY_FUNCTION__ << ": " << op_ << endl;
		oper_t o( NONE );
		switch ( op_ ) {
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
	void deferred_oper( char op_ ) {
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
	HRule multiply( atom >> *( ( '*' >> atom )[HBoundCall<void ( void )>( call( &calc::mul, &c ) )] ) );
	HRule r( multiply >> *( ( '+' >> multiply )[HBoundCall<void ( void )>( call( &calc::sum, &c ) )] ) );
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
	HRule multiply( atom >> *( ( character( "*/" )[HBoundCall<void ( char )>( call( &calc::oper, &c, _1 ) )] >> atom )[HBoundCall<void ( void )>( call( &calc::mul_div, &c ) )] ) );
	HRule r( multiply >> *( ( character( "+-" )[HBoundCall<void ( char )>( call( &calc::oper, &c, _1 ) )] >> multiply )[HBoundCall<void ( void )>( call( &calc::plus_minus, &c ) )] ) );
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
	HRule multiply( atom >> *( ( character( "*/" )[HBoundCall<void ( char )>( call( &calc::deferred_oper, &c, _1 ) )] >> atom )[HBoundCall<void ( void )>( call( &calc::deferred_action, &c, &calc::mul_div ) )] ) );
	HRule r( multiply >> *( ( character( "+-" )[HBoundCall<void ( char )>( call( &calc::deferred_oper, &c, _1 ) )] >> multiply )[HBoundCall<void ( void )>( call( &calc::deferred_action,  &c, &calc::plus_minus ) )] ) );
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
	HRule multiply( power >> *( ( character( "*/" )[HBoundCall<void ( char )>( call( &calc::deferred_oper, &c, _1 ) )] >> power )[HBoundCall<void ( void )>( call( &calc::deferred_action, &c, &calc::mul_div ) )] ) );
	HRule r( multiply >> *( ( character( "+-" )[HBoundCall<void ( char )>( call( &calc::deferred_oper, &c, _1 ) )] >> multiply )[HBoundCall<void ( void )>( call( &calc::deferred_action,  &c, &calc::plus_minus ) )] ) );
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

