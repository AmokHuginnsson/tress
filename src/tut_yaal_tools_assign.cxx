/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/assign.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/tools/streamtools.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_assign );
TUT_TEST_GROUP( tut_yaal_tools_assign, "yaal::tools::assign" );

namespace {

HString foo( tut_yaal_tools_assign::int_array_t const& arr_ ) {
	HStringStream ss;
	ss << arr_;
	return ( ss.string() );
}

typedef HMap<int, int> int2int_t;

HString bar( int2int_t const& arr_ ) {
	HStringStream ss;
	ss << arr_;
	return ( ss.string() );
}

}

TUT_UNIT_TEST( "build HArray<>" )
	int_array_t a = sequence( 1 )( 2 )( 3 );
	int_array_t expected;
	expected.push_back( 1 );
	expected.push_back( 2 );
	expected.push_back( 3 );
	ENSURE_EQUALS( "assign to HArray failed", a, expected );
	ENSURE_EQUALS( "construction to HArray failed", foo( sequence( -1 )( 3 )( -5 ) ), "array(-1 3 -5)" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "build HMap<>" )
	int2int_t m = sequence( 1, 2 )( 3, 4 )( 5, -6 )( -7, 8 );
	int2int_t expected;
	expected.insert( make_pair( 1, 2 ) );
	expected.insert( make_pair( 3, 4 ) );
	expected.insert( make_pair( 5, -6 ) );
	expected.insert( make_pair( -7, 8 ) );
	ENSURE_EQUALS( "assign to HMap failed", m, expected );
	ENSURE_EQUALS( "construction to HMap failed", bar( sequence( 1, 2 )( 3, -4 )( -5, 6 ) ), "map(pair<-5,6> pair<1,2> pair<3,-4>)" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "fast build HArray<>" )
	int_array_t expected;
	expected.push_back( 1 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1 ), expected );
	expected.push_back( 2 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2 ), expected );
	expected.push_back( 3 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2, 3 ), expected );
	expected.push_back( 4 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2, 3, 4 ), expected );
	expected.push_back( 5 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2, 3, 4, 5 ), expected );
	expected.push_back( 6 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2, 3, 4, 5, 6 ), expected );
	expected.push_back( 7 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2, 3, 4, 5, 6, 7 ), expected );
	expected.push_back( 8 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2, 3, 4, 5, 6, 7, 8 ), expected );
	expected.push_back( 9 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2, 3, 4, 5, 6, 7, 8, 9 ), expected );
	expected.push_back( 10 );
	ENSURE_EQUALS( "assign to HArray failed", array( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ), expected );
TUT_TEARDOWN()

}

