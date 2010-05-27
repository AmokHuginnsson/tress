/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <set>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <boost/bind.hpp>

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace boost;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace yaal
{

template<typename iter_in1_t, typename iter_in2_t, typename iter_out_t>
iter_out_t set_( iter_in1_t it1, iter_in1_t end1, iter_in2_t it2, iter_in2_t end2, iter_out_t out )
	{
	return ( out );
	}

}

namespace tut
{

template<typename tType>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HList<tType> const& l )
	{
	out << "list(";yaal::copy( l.begin(), l.end(), stream_iterator( out, " " ) ); out << "\b)" << std::flush;
	return ( out );
	}

template<typename tType>
bool operator != ( yaal::hcore::HList<tType> const& l1, yaal::hcore::HList<tType> const& l2 )
	{
	return ( ! equal( l1.begin(), l1.end(), l2.begin(), l2.end() ) );
	}

TUT_SIMPLE_MOCK( tut_yaal );
TUT_TEST_GROUP_N( tut_yaal, "yaal" );

TUT_UNIT_TEST_N( 1, "swap" )
	int a( 7 );
	int b( 13 );
	ENSURE_EQUALS( "init failed", a, 7 );
	ENSURE_EQUALS( "init failed", b, 13 );
	yaal::swap( a, b );
	ENSURE_EQUALS( "swap failed", a, 13 );
	ENSURE_EQUALS( "swap failed", b, 7 );
TUT_TEARDOWN()

bool greater( int long a, int long b )
	{
	return ( a > b );
	}

TUT_UNIT_TEST_N( 2, "bind2nd" )
	bool p = yaal::bind2nd( &greater, 4 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", p );
	bool q = yaal::bind2nd( &greater, 1 )( 3 );
	ENSURE( "greater functor binded incorrectly", q );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "copy algorithm" )
	int tab1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int tab2[] = { 0, -1, -2, -3, -4, -5, -6, -7 };
	yaal::copy( tab2 + 2, tab2 + 5, tab1 + 2 );
	ENSURE_EQUALS( "copy started too early", tab1[ 1 ], 1 );
	ENSURE_EQUALS( "copy started too late", tab1[ 2 ], -2 );
	ENSURE_EQUALS( "copy finished too early", tab1[ 4 ], -4 );
	ENSURE_EQUALS( "copy finished too late", tab1[ 5 ], 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "meta::max" )
	int long unsigned q = meta::max<sizeof ( int ), sizeof ( char ), sizeof ( double long ), sizeof ( void* ), sizeof ( int long ), sizeof ( int short )>::value;
	ENSURE_EQUALS( "meta::max failed", q, sizeof ( double long ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "back_insert_iterator" )
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 3, 14, 15, 9265, 35, 89, 79, 3 };
	int d4[] = { 1, 2, 4, 2, 3, 5, 7, 3, 14, 15, 9265, 35, 89, 79, 3 };
	typedef HList<int> list_t;

	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l4( d4, d4 + sizeof ( d4 ) / sizeof ( int ) );
	list_t l;
	yaal::copy( l1.begin(), l1.end(), yaal::hcore::back_insert_iterator( l ) );
	yaal::copy( l2.begin(), l2.end(), yaal::hcore::back_insert_iterator( l ) );
	yaal::copy( l3.begin(), l3.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "back_insert_iterator failed", l, l4 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "equal" )
	typedef HList<int> list_t;
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	ENSURE( "positive test for equality failed", yaal::equal( l1.begin(), l1.end(), d1, d1 + sizeof ( d1 ) / sizeof ( int ) ) );
	ENSURE_NOT( "negative test for equality failed", yaal::equal( l1.begin(), l1.end(), l2.begin(), l2.end() ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "set_union uniqe" )
	typedef HList<int> list_t;
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 1, 2, 3, 4, 5, 7 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l;
	yaal::set_union( l1.begin(), l1.end(), l2.begin(), l2.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l1 + l2", l, l3 );
	l.clear();
	yaal::set_union( l2.begin(), l2.end(), l1.begin(), l1.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l2 + l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "set_union duplicates" )
	typedef HList<int> list_t;
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 1, 2, 2, 3, 4, 5, 7 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l;
	yaal::set_union( l1.begin(), l1.end(), l2.begin(), l2.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l1 + l2", l, l3 );
	l.clear();
	yaal::set_union( l2.begin(), l2.end(), l1.begin(), l1.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l2 + l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "set_intersection unique" )
	typedef HList<int> list_t;
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 2 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l;
	yaal::set_intersection( l1.begin(), l1.end(), l2.begin(), l2.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l1 * l2", l, l3 );
	l.clear();
	yaal::set_intersection( l2.begin(), l2.end(), l1.begin(), l1.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l2 * l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "set_intersection duplicates" )
	typedef HList<int> list_t;
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 2, 3, 5, 7 };
	int d3[] = { 2, 2 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l;
	yaal::set_intersection( l1.begin(), l1.end(), l2.begin(), l2.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l1 * l2", l, l3 );
	l.clear();
	yaal::set_intersection( l2.begin(), l2.end(), l1.begin(), l1.end(), yaal::hcore::back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l2 * l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "remove_if algorithm" )
	typedef HList<int> list_t;
	int a[] = { 1, -2, 3, -4, 9, -8, 7, -6, 5 };
	list_t l( a, a + sizeof ( a ) / sizeof ( a[ 0 ] ) );
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
	list_t::iterator end( remove_if( l.begin(), l.end(), bind2nd( &less<int>, 0 ) ) ); 
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
	l.erase( end, l.end() );
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
	int b[] = { 1, 3, 9, 7, 5 };
	ENSURE( "remove_if failed", equal( l.begin(), l.end(), b, b + sizeof ( b ) / sizeof ( b[0] ) ) );
TUT_TEARDOWN()

}

