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
M_VCSID( "$Id: "__ID__" $" )
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
	hcore::HString text( "1+2" );
	ENSURE( "empty parser consumed input", r.parse( text.begin(), text.end() ) == text.begin() );
	ENSURE( "empty parser succeeded on non empty input", r( text ) );
	try {
		r();
		FAIL( "execution of empty parser succeeded" );
	} catch ( HRuleException const& ) {
		// ok
	}
TUT_TEARDOWN()

struct calc {
	typedef HStack<double long> vars_t;
	vars_t _vars;
	calc( void )
		: _vars()
		{}
	void sum( void ) {
		double long v1( _vars.top() );
		_vars.pop();
		double long v2( _vars.top() );
		_vars.pop();
		_vars.push( v1 + v2 );
	}
	void val( double long v_ ) {
		_vars.push( v_ );
	}
};

TUT_UNIT_TEST( 2, "calc" )
	calc c;
	HRule r( real[HBoundCall<void ( double long )>( call( &calc::val, &c, _1 ) )] >> '+' >> real[HBoundCall<void ( double long )>( call( &calc::val, &c, _1 ) )] );
	r[HBoundCall<void ( void )>( call( &calc::sum, &c ) )];
	r( "1.7+2.4" );
	r();
	cout << c._vars.top() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "the test" )
	HArray<double> v;
	if ( real[push_back(v)]( "3.141592653589793" ) )
		cout << "1: failed to consume input" << endl;
	HRule r( real[push_back(v)] >> *( ',' >> real[push_back(v)] ) );
	r( "3.141592653589793, -2.718281828459045, 17" );
	r();
	if ( r( "3.141592653589793, -2.718281828459045, 17, kupa" ) )
		cout << "2: failed to consume input" << endl;
	copy( v.begin(), v.end(), stream_iterator( cout, endl ) );
TUT_TEARDOWN()

}
