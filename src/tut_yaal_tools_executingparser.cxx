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

template<typename T, typename RT = T>
struct setter {
	static void set( T& lval_, RT rval_ ) {
		lval_ = rval_;
	}
};

TUT_UNIT_TEST( 2, "HReal" )
	/* double */ {
		double val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double )>( call( &setter<double>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double).", !ep( "7" ) );
		ep();
		ENSURE_DISTANCE( "double value not ser by ExecutingParser.", static_cast<double long>( val ), 7.l, epsilon );
	}
	/* double long */ {
		double long val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( double long )>( call( &setter<double long>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (double long).", !ep( "7" ) );
		ep();
		ENSURE_DISTANCE( "double long value not ser by ExecutingParser.", val, 7.l, epsilon );
	}
	/* HNumber */ {
		HNumber val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( HNumber const& )>( call( &setter<HNumber, HNumber const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HNumber).", !ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HNumber value not ser by ExecutingParser.", val, 7 );
	}
	/* HString */ {
		hcore::HString val( 0 );
		HExecutingParser ep( real[HBoundCall<void ( hcore::HString const& )>( call( &setter<hcore::HString, hcore::HString const&>::set, ref( val ), _1 ) )] );
		ENSURE( "HReal failed to parse correct input (HString).", !ep( "7" ) );
		ep();
		ENSURE_EQUALS( "HString value not ser by ExecutingParser.", val, "7" );
	}
	/* bad real */ {
		HExecutingParser ep( real );
		ENSURE_NOT( "Invalid input parsed by HReal", !ep( "bad" ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 30, "cycle on unnamed rules" )
	/* simple grammars */ {
		/*
		 * If *::describe() is incorrectly implemented this test will overflow stack.
		 */
		HRule elem;
		HRule mul( elem >> *( '*' >> elem ) );
		HRule sum( mul >> *( '+' >> mul ) );
		elem %= ( real | ( character( '(' ) >> sum >> ')' ) );
		HExecutingParser ep1( elem );
		HRule name( regex( "\\<a-z\\>" ) );
		HRule eq( name >> '=' >> elem );
		HExecutingParser ep2( eq );
		cout << "elem:" << endl;
		HGrammarDescription gd1( elem );
		for ( HGrammarDescription::const_iterator it( gd1.begin() ), end( gd1.end() ); it != end; ++ it )
			cout << *it << endl;
		cout << "eq:" << endl;
		HGrammarDescription gd2( eq );
		for ( HGrammarDescription::const_iterator it( gd2.begin() ), end( gd2.end() ); it != end; ++ it )
			cout << *it << endl;
	}
	/* complicated grammar */ {
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
		HRule hg( * functionDefinition );
		cout << "hg:" << endl;
		HGrammarDescription gd( hg );
		for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it )
			cout << *it << endl;
	}
TUT_TEARDOWN()

struct calc {
	typedef HStack<double long> vars_t;
	vars_t _vars;
	calc( void )
		: _vars()
		{}
	void sum( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
		double long v1( _vars.top() );
		_vars.pop();
		double long v2( _vars.top() );
		_vars.pop();
		_vars.push( v1 + v2 );
	}
	void mul( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
		double long v1( _vars.top() );
		_vars.pop();
		double long v2( _vars.top() );
		_vars.pop();
		_vars.push( v1 * v2 );
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

