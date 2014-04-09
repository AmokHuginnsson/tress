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


template<typename container_t>
void pushbacker( container_t* container, yaal::hcore::HString const& value ) {
	container->push_back( lexical_cast<typename container_t::value_type>( value ) );
}

template<typename container_t>
HBoundCall<void ( yaal::hcore::HString const& )> push_back( container_t& container ) {
	M_PROLOG
	return ( call( &pushbacker<container_t>, &container, _1 ) );
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
	try {
		HExecutingParser ep( r );
		FAIL( "empty parser constructed" );
	} catch ( HExecutingParserException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Named rule name ends with underscore" )
	try {
		HRule r( "A_" );
		FAIL( "explicit rule name with underscore at the end created" );
	} catch ( HNamedRuleException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

template<typename T, typename RT = T>
struct setter {
	static void set( T& lval_, RT rval_ ) {
		lval_ = rval_;
	}
};

TUT_UNIT_TEST( 3, "HReal" )
	/* double */ {
		double val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double )>( call( &setter<double>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double).", !ep( "3.14" ) );
		ep();
		ENSURE_DISTANCE( "double value not set by ExecutingParser.", static_cast<double long>( val ), 3.14l, epsilon );
	}
	/* double long */ {
		double long val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double long )>( call( &setter<double long>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double long).", !ep( "3.14" ) );
		ep();
		ENSURE_DISTANCE( "double long value not set by ExecutingParser.", val, 3.14l, epsilon );
	}
	/* HNumber */ {
		HNumber val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( HNumber const& )>( call( &setter<HNumber, HNumber const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HNumber).", !ep( "3.141592653589793" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, "3.141592653589793" );
	}
	/* HString */ {
		hcore::HString val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HString).", !ep( "3.141592653589793" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "3.141592653589793" );
	}
	/* bad real */ {
		HExecutingParser ep( real );
		ENSURE_NOT( "Invalid input parsed by HReal", !ep( "bad" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "HInteger" )
	/* int */ {
		int val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int )>( call( &setter<int>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int).", !ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int value not set by ExecutingParser.", val, 7 );
	}
	/* int long */ {
		int long val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( int long )>( call( &setter<int long>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (int long).", !ep( "7" ) );
		ep();
		ENSURE_EQUALS( "int long value not set by ExecutingParser.", val, 7l );
	}
	/* HNumber */ {
		HNumber val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( HNumber const& )>( call( &setter<HNumber, HNumber const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (HNumber).", !ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not set by ExecutingParser.", val, 7 );
	}
	/* HString */ {
		hcore::HString val( 0 );
		HExecutingParser ep( integer[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HInteger failed to parse correct input (HString).", !ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "7" );
	}
	/* bad integer */ {
		HExecutingParser ep( integer );
		ENSURE_NOT( "Invalid input parsed by HInteger", !ep( "bad" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "HCharacter" )
	/* char (any) */ {
		char val( 0 );
		HExecutingParser ep( character[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", !ep( "a" ) );
		ep();
		ENSURE_EQUALS( "char value not set by ExecutingParser.", val, 'a' );
	}
	/* char (specific ok) */ {
		char val( 0 );
		HExecutingParser ep( character( 'a' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", !ep( "a" ) );
	}
	/* char (specific, any of ok) */ {
		char val( 0 );
		HExecutingParser ep( character( "ab" )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE( "HCharacter failed to parse correct input.", !ep( "b" ) );
	}
	/* char (specific fail) */ {
		char val( 0 );
		HExecutingParser ep( character( 'X' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HCharacter parsed invalid input.", !ep( "a" ) );
	}
	/* char (specific any of fail) */ {
		char val( 0 );
		HExecutingParser ep( character( "ab" )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HCharacter parsed invalid input.", !ep( "c" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "HString" )
	/* ok */ {
		hcore::HString val;
		HExecutingParser ep( string( "ala" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HString failed to parse correct input.", !ep( "ala" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "ala" );
	}
	/* fail */ {
		hcore::HString val;
		HExecutingParser ep( string( "XXX" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HString parsed invalid input.", !ep( "ala" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "HRegex" )
	/* ok */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HRegex failed to parse correct input.", !ep( "12.34" ) );
		ep();
		ENSURE_EQUALS( "HString value not set by ExecutingParser.", val, "12.34" );
	}
	/* fail not fully consumed input */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HExecutingParser accepted parse on partial input.", !ep( "12.345" ) );
	}
	/* fail */ {
		hcore::HString val;
		HExecutingParser ep( regex( "[0-9]{2}\\.[0-9]{2}" )[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE_NOT( "HRegex parsed invalid input.", !ep( "12.3a" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "HFollows" )
	/* parsed */ {
		char fcData( 0 );
		HRule fc( character( 'a' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( fcData ), _1 ) )] );
		char scData( 0 );
		HRule sc( character( 'b' )[HBoundCall<void ( char )>( call( &setter<char>::set, ref( scData ), _1 ) )] );
		bool followsCalled( false );
		HExecutingParser ep( ( fc >> sc )[HBoundCall<void ( void )>( call( &setter<bool>::set, ref( followsCalled ), true ) ) ] );
		ENSURE( "parse on correct failed", !ep( "ab" ) );
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
		ENSURE_NOT( "parse on invalid succeeded", !ep( "aa" ) );
	}
TUT_TEARDOWN()

template<typename T>
void sum( T& sum_, T val_ ) {
	sum_ += val_;
}

TUT_UNIT_TEST( 9, "HKleeneStar" )
	/* parsed (non empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &sum<int>, ref( val ), _1 ) )] );
		HRule nums( *( ',' >> i ) );
		HExecutingParser ep( nums );
		ENSURE( "parse on valid failed", !ep( ", 1, 2, 3" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 6 );
	}
	/* parsed (empty) */ {
		int val( 0 );
		HRule i( integer[HBoundCall<void ( int )>( call( &sum<int>, ref( val ), _1 ) )] );
		HRule nums( *( ',' >> i ) );
		HExecutingParser ep( string( "nums{" ) >> nums >> "}" );
		ENSURE( "parse on valid (but empty) failed", !ep( "nums{}" ) );
		ep();
		ENSURE_EQUALS( "execution of KleeneStar failed", val, 0 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "HKleenePlus" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "HOptional" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "HAlternative" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 30, "simple recursive rule" )
	/*
	 * If *::describe() is incorrectly implemented this test will overflow stack.
	 */
	HRule elem;
	HRule mul( elem >> *( '*' >> elem ) );
	HRule sum( mul >> *( '+' >> mul ) );
	elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
	HExecutingParser ep1( elem );
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

TUT_UNIT_TEST( 31, "non-trivial recursive rule" )
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

TUT_UNIT_TEST( 32, "unnamed HHuginn grammar" )
	HRule name( regex( "\\<[a-zA-Z_][a-zA-Z0-9_]*\\>" ) );
	HRule expression;
	HRule absoluteValue( '|' >> expression >> '|' );
	HRule parenthesis( '(' >> expression >> ')' );
	HRule argList( expression >> ( * ( ',' >> expression ) ) );
	HRule functionCall( name >> '(' >> -argList >> ')' );
	HRule atom( absoluteValue | parenthesis | functionCall | real | name );
	HRule power( atom >> ( * ( '^' >> atom ) ) );
	HRule multiplication( power >> ( * ( '*' >> power ) ) );
	HRule sum( multiplication >> ( * ( '+' >> multiplication ) ) );
	HRule value( sum );
	HRule assignment( *( name >> '=' ) >> value );
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
	HRule ifStatement( executing_parser::constant( "if" ) >> '(' >> booleanExpression >> ')' >> scope >> -( executing_parser::constant( "else" ) >> scope ) );
	HRule whileStatement( executing_parser::constant( "while" ) >> '(' >> booleanExpression >> ')' >> scope );
	HRule caseStatement( executing_parser::constant( "case" ) >> '(' >> integer >> ')' >> ':' >> scope );
	HRule switchStatement( executing_parser::constant( "switch" ) >> '(' >> expression >> ')' >> '{' >> +caseStatement >> '}' );
	HRule returnStatement( executing_parser::constant( "return" ) >> '(' >> expression >> ')' );
	HRule statement( ifStatement | whileStatement | switchStatement | returnStatement | expressionList );
	scope %= ( '{' >> *statement >> '}' );
	HRule nameList( name >> ( * ( ',' >> name ) ) );
	HRule functionDefinition( name >> '(' >> -nameList >> ')' >> scope );
	HRule hg( + functionDefinition );
	char const huginnDesc[][320] = {
		"A_ = +( B_ >> '(' >> -( B_ >> *( ',' >> B_ ) ) >> ')' >> C_ )",
		"B_ = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"C_ = '{' >> *( \"if\" >> '(' >> D_ >> ')' >> C_ >> -( \"else\" >> C_ ) | \"while\" >> '(' >> D_ >> ')' >> C_ | \"switch\" >> '(' >> E_ >> ')' >> '{' >> +( \"case\" >> '(' >> integer >> ')' >> ':' >> C_ ) >> '}' | \"return\" >> '(' >> E_ >> ')' | +( E_ >> ';' ) ) >> '}'",
		"D_ = E_ >> \"==\" >> E_ | E_ >> \"!=\" >> E_ | E_ >> \"<\" >> E_ | E_ >> \">\" >> E_ | E_ >> \"<=\" >> E_ | E_ >> \">=\" >> E_ | F_ >> \"&&\" >> F_ | F_ >> \"||\" >> F_ | F_ >> \"^^\" >> F_ | '!' >> F_",
		"E_ = *( B_ >> '=' ) >> G_ >> *( '+' >> G_ )",
		"F_ = \"true\" | \"false\" | '(' >> D_ >> ')'",
		"G_ = H_ >> *( '*' >> H_ )",
		"H_ = I_ >> *( '^' >> I_ )",
		"I_ = '|' >> E_ >> '|' | '(' >> E_ >> ')' | B_ >> '(' >> -( E_ >> *( ',' >> E_ ) ) >> ')' | real | B_"
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
			default: M_ASSERT( !"bad oper" );
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
	ENSURE( "parsing correct input (single real) failed", !HExecutingParser( real[push_back(v)] )( "3.141592653589793" ) );
	HRule r( real[push_back(v)] >> *( ',' >> real[push_back(v)] ) );
	HExecutingParser ep( r );
	ENSURE( "parsing correct input (coma separated set of reals) failed", !ep( "3.141592653589793, -2.718281828459045, 17" ) );
	ep();
	if ( ep( "3.141592653589793, -2.718281828459045, 17, kupa" ) )
		cout << "2: failed to consume input" << endl;
	copy( v.begin(), v.end(), stream_iterator( cout, endl ) );
TUT_TEARDOWN()

}

