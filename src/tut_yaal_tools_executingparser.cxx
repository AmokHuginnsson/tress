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

TUT_UNIT_TEST( 1, "empty parser" )
	HRule r;
	ENSURE_THROW( "empty parser constructed", HExecutingParser ep( r ), HExecutingParserException );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Named rule name ends with underscore" )
	ENSURE_THROW( "explicit rule name with underscore at the end created", HRule r( "A_" ), HNamedRuleException );
TUT_TEARDOWN()

template<typename T, typename RT = T>
struct setter {
	static void set( T& lval_, RT rval_ ) {
		lval_ = rval_;
	}
	static void set_alt( T& lval_, RT rval_ ) {
		lval_ = -rval_;
	}
};

TUT_UNIT_TEST( 3, "HReal" )
	/* double */ {
		double val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double )>( call( &setter<double>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double).", ep( "3.14" ) );
		ep();
		ENSURE_DISTANCE( "double value not set by ExecutingParser.", static_cast<double long>( val ), 3.14l, epsilon );
	}
	/* double long */ {
		double long val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double long )>( call( &setter<double long>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double long).", ep( "3.14" ) );
		ep();
		ENSURE_DISTANCE( "double long value not set by ExecutingParser.", val, 3.14l, epsilon );
	}
	/* HNumber */ {
		HNumber val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( HNumber const& )>( call( &setter<HNumber, HNumber const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HNumber).", ep( "3.141592653589793" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, "3.141592653589793" );
	}
	/* HString */ {
		hcore::HString val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HString).", ep( "3.141592653589793" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "3.141592653589793" );
	}
	/* bad real */ {
		HExecutingParser ep( real );
		ENSURE_NOT( "Invalid input parsed by HReal", ep( "bad" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "HInteger" )
	/* int */ {
		int val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int )>( call( &setter<int>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int value not set by ExecutingParser.", val, 7 );
	}
	/* int long */ {
		int long val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int long )>( call( &setter<int long>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int long).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int long value not set by ExecutingParser.", val, 7l );
	}
	/* HNumber */ {
		HNumber val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( HNumber const& )>( call( &setter<HNumber, HNumber const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (HNumber).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, 7 );
	}
	/* HString */ {
		hcore::HString val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (HString).", ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "7" );
	}
	/* bad integer */ {
		HExecutingParser ep( integer );
		ENSURE_NOT( "Invalid input parsed by HInteger", ep( "bad" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "HStringLiteral" )
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

TUT_UNIT_TEST( 6, "HCharacterLiteral" )
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

TUT_UNIT_TEST( 7, "HCharacter" )
	/* char (any) */ {
		char val( 0 );
		HExecutingParser ep( character[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", ep( "a" ) );
		ep();
		ENSURE_EQUALS( "char value not set by ExecutingParser.", val, 'a' );
	}
	/* char (specific ok) */ {
		char val( 0 );
		HExecutingParser ep( character( 'a' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", ep( "a" ) );
	}
	/* char (specific, any of ok) */ {
		char val( 0 );
		HExecutingParser ep( character( "ab" )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", ep( "b" ) );
	}
	/* char (specific fail) */ {
		char val( 0 );
		HExecutingParser ep( character( 'X' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HCharacter parsed invalid input.", ep( "a" ) );
	}
	/* char (specific any of fail) */ {
		char val( 0 );
		HExecutingParser ep( character( "ab" )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HCharacter parsed invalid input.", ep( "c" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "HString" )
	/* ok */ {
		hcore::HString val;
		HExecutingParser ep( string( "ala" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HString failed to parse correct input.", ep( "ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
	}
	/* fail */ {
		hcore::HString val;
		HExecutingParser ep( string( "XXX" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HString parsed invalid input.", ep( "ala" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "HRegex" )
	/* ok */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HRegex failed to parse correct input.", ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "12.34" );
	}
	/* fail not fully consumed input */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HExecutingParser accepted parse on partial input.", ep( "12.345" ) );
	}
	/* fail */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HRegex parsed invalid input.", ep( "12.3a" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "HFollows" )
	/* parsed */ {
		char fcData( 0 );
		HRule fc( character( 'a' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( fcData ), _1 ) )] );
		char scData( 0 );
		HRule sc( character( 'b' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( scData ), _1 ) )] );
		bool followsCalled( false );
		HExecutingParser ep( ( fc >> sc )[HBoundCall<void ( void )>( call( &setter<bool>::set, ref( followsCalled ), true ) ) ] );
		ENSURE( "parse on correct failed", ep( "ab" ) );
		ep();
		ENSURE_EQUALS( "predecessor in follows not called", fcData, 'a' );
		ENSURE_EQUALS( "successor in follows not called", scData, 'b' );
		ENSURE( "follows not called", followsCalled );
	}
	/* failed on successor */ {
		char fcData( 0 );
		HRule fc( character( 'a' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( fcData ), _1 ) )] );
		char scData( 0 );
		HRule sc( character( 'b' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( scData ), _1 ) )] );
		bool followsCalled( false );
		HExecutingParser ep( ( fc >> sc )[HBoundCall<void ( void )>( call( &setter<bool>::set, ref( followsCalled ), true ) ) ] );
		ENSURE_NOT( "parse on invalid succeeded", ep( "aa" ) );
	}
TUT_TEARDOWN()

template<typename T>
void sum( T& sum_, T val_ ) {
	sum_ += val_;
}

TUT_UNIT_TEST( 11, "HKleeneStar" )
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

TUT_UNIT_TEST( 12, "HKleenePlus" )
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

TUT_UNIT_TEST( 13, "HOptional" )
	/* not-parsed (empty) configuration test */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &setter<int>::set, ref( val ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> i >> "}" );
		ENSURE_NOT( "parse on invalid (empty) succeeded", ep( "nums{}" ) );
	}
	/* parsed (empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &setter<int>::set, ref( val ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> (-i) >> "}" );
		ENSURE( "parse on valid (but empty) failed", ep( "nums{}" ) );
		ep();
		ENSURE_EQUALS( "execution of optional failed", val, 0 );
	}
	/* parsed (non-empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &setter<int>::set, ref( val ), _1 ) )] );
		HExecutingParser ep( string( "nums{" ) >> (-i) >> "}" );
		ENSURE( "parse on valid failed", ep( "nums{7}" ) );
		ep();
		ENSURE_EQUALS( "execution of optional failed", val, 7 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "canceling execution steps" )
	int val( 0 );
	int val_alt( 0 );
	HRule i( integer[HBoundCall<void ( int )>( call( &setter<int>::set, ref( val ), _1 ) )] );
	HRule ia( integer[HBoundCall<void ( int )>( call( &setter<int>::set_alt, ref( val_alt ), _1 ) )] );
	HExecutingParser ep( string( "nums{" ) >> ( -( i >> ":pos" ) ) >> ( -( ia >> ":neg" ) ) >> "}" );
	ENSURE( "parse on valid failed", ep( "nums{7:neg}" ) );
	ep();
	ENSURE_EQUALS( "execution failed sub-step not removed", val, 0 );
	ENSURE_EQUALS( "execution proper execution sub-step not applied", val_alt, -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "HAlternative" )
	int val( 0 );
	int val_alt( 0 );
	HRule i( integer[HBoundCall<void ( int )>( call( &setter<int>::set, ref( val ), _1 ) )] );
	HRule ia( integer[HBoundCall<void ( int )>( call( &setter<int>::set_alt, ref( val_alt ), _1 ) )] );
	HExecutingParser ep( string( "nums{" ) >> ( ( i >> ":pos" ) | ( ia >> ":neg" ) ) >> "}" );
	ENSURE( "parse on valid failed", ep( "nums{7:neg}" ) );
	ep();
	ENSURE_EQUALS( "execution failed sub-step not removed", val, 0 );
	ENSURE_EQUALS( "execution proper execution sub-step not applied", val_alt, -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "left recursion" )
	/* follows */ {
		HRule S;
		S %= ( S >> '$' >> integer );
		HGrammarDescription gd( S );
		int i( 0 );
		for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
			ENSURE( "bad ruie count", i < 1 );
			ENSURE_EQUALS( "wrong description", *it, "A_ = A_ >> '$' >> integer" );
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
			ENSURE_EQUALS( "wrong description", *it, "A_ = integer | A_" );
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
			ENSURE_EQUALS( "wrong description", *it, "A_ = -( integer ) >> A_" );
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
			ENSURE_EQUALS( "wrong description", *it, "A_ = *( integer ) >> A_" );
			cout << *it << endl;
		}
		ENSURE_THROW( "Grammar with left recursion accepted (kleene star).", HExecutingParser ep( S ), HExecutingParserException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 17, "simple recursive rule" )
	/*
	 * If *::describe() is incorrectly implemented this test will overflow stack.
	 */
	HRule elem;
	HRule mul( elem >> *( '*' >> elem ) );
	HRule sum( mul >> *( '+' >> mul ) );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	HExecutingParser ep( elem );
	static char epDesc[][50] = {
		"A_ = real | '(' >> B_ >> *( '+' >> B_ ) >> ')'",
		"B_ = A_ >> *( '*' >> A_ )"
	};
	cout << "elem:" << endl;
	HGrammarDescription gd( elem );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 18, "non-trivial recursive rule" )
	HRule elem;
	HRule mul( elem >> *( '*' >> elem ) );
	HRule sum( mul >> *( '+' >> mul ) );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	HRule name( regex( "\\<a-z\\>" ) );
	HRule eq( name >> '=' >> elem );
	HExecutingParser ep2( eq );
	char epDesc[][80] = {
		"A_ = regex( \"\\<a-z\\>\" ) >> '=' >> B_",
		"B_ = real | '(' >> C_ >> *( '+' >> C_ ) >> ')'",
		"C_ = B_ >> *( '*' >> B_ )"
	};
	cout << "eq:" << endl;
	HGrammarDescription gd( eq );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 19, "ad-hoc root rule name" )
	HRule elem;
	HRule mul( elem >> *( '*' >> elem ) );
	HRule extra( integer >> '%' >> elem );
	HRule sum( mul >> *( '+' >> mul ) );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	HExecutingParser ep( elem >> extra );
	static char epDesc[][50] = {
		"A_ = B_ >> integer >> '%' >> B_",
		"B_ = real | '(' >> C_ >> *( '+' >> C_ ) >> ')'",
		"C_ = B_ >> *( '*' >> B_ )"
	};
	cout << "ad-hoc:" << endl;
	HGrammarDescription gd( elem >> extra );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "two inter-locking recursion loops" )
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
		"A_ = regex( \"\\<a-z\\>\" ) >> '=' >> B_ >> C_",
		"B_ = real | '(' >> C_ >> *( '+' >> C_ ) >> B_ >> ')'",
		"C_ = integer | '(' >> B_ >> *( '*' >> B_ ) >> C_ >> ')'"
	};
	cout << "eq:" << endl;
	HGrammarDescription gd( eq );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE_EQUALS( "wrong description", *it, epDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 32, "unnamed HHuginn grammar" )
	HRule name( regex( "\\<[a-zA-Z_][a-zA-Z0-9_]*\\>" ) );
	HRule expression;
	HRule absoluteValue( '|' >> expression >> '|' );
	HRule parenthesis( '(' >> expression >> ')' );
	HRule argList( expression >> ( * ( ',' >> expression ) ) );
	HRule functionCall( name >> '(' >> -argList >> ')' );
	HRule atom( absoluteValue | parenthesis | functionCall | real | integer | string_literal | character_literal | name );
	HRule power( atom >> ( * ( '^' >> atom ) ) );
	HRule multiplication( power >> ( * ( '*' >> power ) ) );
	HRule sum( multiplication >> ( * ( '+' >> multiplication ) ) );
	HRule value( sum );
	HRule ref( value >> *( '[' >> value >> ']' ) );
	HRule assignment( *( name >> '=' ) >> ref );
	expression %= assignment;
	HRule booleanExpression;
	HRule booleanValue( executing_parser::constant( "true" ) | executing_parser::constant( "false" ) | executing_parser::constant( '(' ) >> booleanExpression >> ')' );
	HRule booleanEquals( expression >> "==" >> expression );
	HRule booleanNotEquals( expression >> "!=" >> expression );
	HRule booleanLess( expression >> "<" >> expression );
	HRule booleanGreater( expression >> ">" >> expression );
	HRule booleanLessEq( expression >> "<=" >> expression );
	HRule booleanGreaterEq( expression >> ">=" >> expression );
	HRule booleanAnd( booleanValue >> "&&" >> booleanValue );
	HRule booleanOr( booleanValue >> "||" >> booleanValue );
	HRule booleanXor( booleanValue >> "^^" >> booleanValue );
	HRule booleanNot( executing_parser::constant( '!' ) >> booleanValue );
	booleanExpression %= ( booleanEquals | booleanNotEquals | booleanLess | booleanGreater | booleanLessEq | booleanGreaterEq | booleanAnd | booleanOr | booleanXor | booleanNot );
	HRule expressionList( + ( expression >> ';' ) );
	HRule scope;
	HRule loopScope;
	HRule ifStatement( executing_parser::constant( "if" ) >> '(' >> booleanExpression >> ')' >> scope >> -( executing_parser::constant( "else" ) >> scope ) );
	HRule continueStatement( executing_parser::constant( "continue" ) >> ';' );
	HRule breakStatement( executing_parser::constant( "break" ) >> ';' );
	HRule whileStatement( executing_parser::constant( "while" ) >> '(' >> booleanExpression >> ')' >> loopScope );
	HRule foreachStatement( executing_parser::constant( "foreach" ) >> '(' >> name >> ':' >> expression >> ')' >> loopScope );
	HRule caseStatement( executing_parser::constant( "case" ) >> '(' >> integer >> ')' >> ':' >> scope );
	HRule defaultStatement( executing_parser::constant( "default" ) >> ':' >> scope );
	HRule switchStatement( executing_parser::constant( "switch" ) >> '(' >> expression >> ')' >> '{' >> +caseStatement >> '}' );
	HRule returnStatement( executing_parser::constant( "return" ) >> '(' >> expression >> ')' >> ';' );
	HRule statement( ifStatement | whileStatement | foreachStatement | switchStatement | returnStatement | expressionList );
	HRule loopStatement( ifStatement | whileStatement | foreachStatement | switchStatement | breakStatement | continueStatement | returnStatement | expressionList );
	scope %= ( '{' >> *statement >> '}' );
	loopScope %= ( '{' >> *loopStatement >> '}' );
	HRule nameList( name >> ( * ( ',' >> name ) ) );
	HRule functionDefinition( name >> '(' >> -nameList >> ')' >> scope );
	HRule hg( + functionDefinition );
	char const huginnDesc[][320] = {
		"A_ = +( B_ >> '(' >> -( B_ >> *( ',' >> B_ ) ) >> ')' >> C_ )",
		"B_ = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"C_ = '{' >> *( D_ | E_ | F_ | G_ | H_ | I_ ) >> '}'",
		"D_ = \"if\" >> '(' >> J_ >> ')' >> C_ >> -( \"else\" >> C_ )",
		"E_ = \"while\" >> '(' >> J_ >> ')' >> K_",
		"J_ = L_ >> \"==\" >> L_ | L_ >> \"!=\" >> L_ | L_ >> \"<\" >> L_ | L_ >> \">\" >> L_ | L_ >> \"<=\" >> L_ | L_ >> \">=\" >> L_ | M_ >> \"&&\" >> M_ | M_ >> \"||\" >> M_ | M_ >> \"^^\" >> M_ | '!' >> M_",
		"K_ = '{' >> *( D_ | E_ | F_ | G_ | \"break\" >> ';' | \"continue\" >> ';' | H_ | I_ ) >> '}'",
		"L_ = *( B_ >> '=' ) >> N_ >> *( '[' >> N_ >> ']' )",
		"M_ = \"true\" | \"false\" | '(' >> J_ >> ')'",
		"F_ = \"foreach\" >> '(' >> B_ >> ':' >> L_ >> ')' >> K_",
		"G_ = \"switch\" >> '(' >> L_ >> ')' >> '{' >> +( \"case\" >> '(' >> integer >> ')' >> ':' >> C_ ) >> '}'",
		"H_ = \"return\" >> '(' >> L_ >> ')' >> ';'",
		"I_ = +( L_ >> ';' )",
		"N_ = O_ >> *( '+' >> O_ )",
		"O_ = P_ >> *( '*' >> P_ )",
		"P_ = Q_ >> *( '^' >> Q_ )",
		"Q_ = '|' >> L_ >> '|' | '(' >> L_ >> ')' | B_ >> '(' >> -( L_ >> *( ',' >> L_ ) ) >> ')' | real | integer | string_literal | character_literal | B_"
	};
	cout << "hg:" << endl;
	HGrammarDescription gd( hg );
	static int const COUNT( static_cast<int>( end( huginnDesc ) - begin( huginnDesc ) ) );
	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		if ( i < COUNT )
			ENSURE_EQUALS( "wrong grammar description", *it, huginnDesc[i] );
		cout << *it << endl;
	}
TUT_TEARDOWN()

struct calc {
	typedef enum {
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		NONE
	} oper_t;
	typedef HStack<double long> vars_t;
	typedef HStack<oper_t> opers_t;
	vars_t _vars;
	opers_t _opers;
	calc( void )
		: _vars(), _opers()
		{}
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
	void oper( char op_ ) {
		clog << __PRETTY_FUNCTION__ << endl;
		oper_t o( NONE );
		switch ( op_ ) {
			case ( '+' ): o = PLUS; break;
			case ( '-' ): o = MINUS; break;
			case ( '*' ): o = MULTIPLY; break;
			case ( '/' ): o = DIVIDE; break;
			default: M_ASSERT( !"bad oper"[0] );
		}
		_opers.push( o );
	}
	void val( double long v_ ) {
		clog << __PRETTY_FUNCTION__ << endl;
		_vars.push( v_ );
	}
};

TUT_UNIT_TEST( 40, "calc (sum)" )
	calc c;
	HRule realVal( real[HBoundCall<void ( double long )>( call( &calc::val, &c, _1 ) )] );
	HRule r( realVal >> *( ( '+' >> realVal )[HBoundCall<void ( void )>( call( &calc::sum, &c ) )] ) );
	HExecutingParser ep( r );
	ep( "1.7+2.4+-7" );
	ep();
	ENSURE_DISTANCE( "bad value calculated from +", c._vars.top(), -2.9l, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 41, "calc (sum, mul)" )
	calc c;
	HRule realVal( real[HBoundCall<void ( double long )>( call( &calc::val, &c, _1 ) )] );
	HRule multiply( realVal >> *( ( '*' >> realVal )[HBoundCall<void ( void )>( call( &calc::mul, &c ) )] ) );
	HRule r( multiply >> *( ( '+' >> multiply )[HBoundCall<void ( void )>( call( &calc::sum, &c ) )] ) );
	HExecutingParser ep( r );

	ep( "1.7*2+2.4+-7" );
	ep();
	ENSURE_DISTANCE( "bad value calculated from +*", c._vars.top(), -1.2l, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 42, "calc, (sum, mul, recursion)" )
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

TUT_UNIT_TEST( 43, "calc, (plus, minus, mul, div, recursion)" )
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

