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

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

template<typename tType>
std::ostream& operator << ( std::ostream& out, HList<tType> const& l )
	{
	out << "list(";
	yaal::copy( l.begin(), l.end(), stream_iterator( out, " " ) );
	out << "\b)" << std::flush;
	return ( out );
	}

TUT_SIMPLE_MOCK( tut_yaal );
TUT_TEST_GROUP_N( tut_yaal, "yaal" );

TUT_UNIT_TEST_N( 1, "swap" )
	int a( 7 );
	int b( 13 );
	ENSURE_EQUALS( "init failed", a, 7 );
	ENSURE_EQUALS( "init failed", b, 13 );
	swap( a, b );
	ENSURE_EQUALS( "swap failed", a, 13 );
	ENSURE_EQUALS( "swap failed", b, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "bind1st" )
	bool p = bind1st( less<int>(), 4 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", p );
	bool q = bind1st( less<int>(), 1 )( 3 );
	ENSURE( "greater functor binded incorrectly", q );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "bind2nd" )
	bool p = bind2nd( greater<int>(), 4 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", p );
	bool q = bind2nd( greater<int>(), 1 )( 3 );
	ENSURE( "greater functor binded incorrectly", q );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "copy algorithm" )
	int tab1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int tab2[] = { 0, -1, -2, -3, -4, -5, -6, -7 };
	copy( tab2 + 2, tab2 + 5, tab1 + 2 );
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
	copy( l1.begin(), l1.end(), back_insert_iterator( l ) );
	copy( l2.begin(), l2.end(), back_insert_iterator( l ) );
	copy( l3.begin(), l3.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "back_insert_iterator failed", l, l4 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "equal" )
	typedef HList<int> list_t;
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	ENSURE( "positive test for equality failed", safe_equal( l1.begin(), l1.end(), d1, d1 + sizeof ( d1 ) / sizeof ( int ) ) );
	ENSURE( "positive test for equality failed", equal( l1.begin(), l1.end(), d1 ) );
	ENSURE_NOT( "negative test for equality failed", safe_equal( l1.begin(), l1.end(), l2.begin(), l2.end() ) );
	ENSURE_NOT( "negative test for equality failed", equal( l1.begin(), l1.end(), l2.begin() ) );
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
	set_union( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l1 + l2", l, l3 );
	l.clear();
	set_union( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator( l ) );
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
	set_union( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l1 + l2", l, l3 );
	l.clear();
	set_union( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator( l ) );
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
	set_intersection( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l1 * l2", l, l3 );
	l.clear();
	set_intersection( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator( l ) );
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
	set_intersection( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l1 * l2", l, l3 );
	l.clear();
	set_intersection( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l2 * l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "remove_if algorithm" )
	typedef HList<int> list_t;
	int a[] = { 1, -2, 3, -4, 9, -8, 7, -6, 5 };
	list_t l( a, a + countof( a ) );
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
	list_t::iterator end( remove_if( l.begin(), l.end(), bind2nd( less<int>(), 0 ) ) ); 
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
	l.erase( end, l.end() );
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
	int b[] = { 1, 3, 9, 7, 5 };
	ENSURE( "remove_if failed", safe_equal( l.begin(), l.end(), b, b + countof( b ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "transform" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( a, a + countof( a ), back_insert_iterator( l ), static_cast<double (*)( double )>( sqrt ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "transform failed", ss.string(), "1 2 3 4 5 6 7 8 9 10 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "negate" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( a, a + countof( a ), back_insert_iterator( l ), negate<int>() );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "negate failed", ss.string(), "-1 -4 -9 -16 -25 -36 -49 -64 -81 -100 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 15, "compose1" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( a, a + countof( a ), back_insert_iterator( l ), compose1( negate<int>(), bind1st( plus<int>(), 1 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "compose1 failed", ss.string(), "-2 -5 -10 -17 -26 -37 -50 -65 -82 -101 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 16, "remove_copy_if" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ),
				bind1st( less<int>(), 30 ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "remove_copy_if failed", ss.string(), "1 4 9 16 25 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 17, "compose2" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ),
			compose2(
				logical_and<bool>(),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "compose2 failed", ss.string(), "1 4 9 16 25 64 81 100 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 18, "count" )
	int a[] = { 1, 4, 9, 16, 25, 36, 16, 49, 64, 81, 100, 16 };
	ENSURE_EQUALS( "misscounted 16", count( a, a + countof( a ), 16 ), 3 );
	ENSURE_EQUALS( "misscounted 16", count( a, a + countof( a ), 17 ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 19, "count_if" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	ENSURE_EQUALS( "misscounted 16", count_if( a, a + countof( a ), bind2nd( less<int>(), 50 ) ), 7 );
	ENSURE_EQUALS( "misscounted 16", count_if( a, a + countof( a ), bind2nd( less<int>(), 1 ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 20, "not1" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	ENSURE_EQUALS( "misscounted 16", count_if( a, a + countof( a ), not1( bind2nd( less<int>(), 50 ) ) ), countof( a ) - 7 );
	ENSURE_EQUALS( "misscounted 16", count_if( a, a + countof( a ), not1( bind2nd( less<int>(), 1 ) ) ), countof( a ) - 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 21, "not2" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ),
			compose2(
				not2(	logical_and<bool>() ),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "not2 failed", ss.string(), "36 49 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 22, "identity" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( bind1st( less<int>(), 30 ), identity<int>() ),
				bind1st( greater<int>(), 60 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "identity failed", ss.string(), "36 49 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 23, "ptr_fun" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( bind1st( less<int>(), 5 ), ptr_fun( static_cast<double (*)( double )>( sqrt ) ) ),
				bind1st( greater<int>(), 60 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "ptr_fun failed", ss.string(), "36 49 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 24, "call as bind1st/bind2nd" )
	bool p = call( less<int>(), 4, _1 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", p );
	bool q = call( less<int>(), 1, _1 )( 3 );
	ENSURE( "greater functor binded incorrectly", q );
	bool r = call( greater<int>(), _1, 4 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", r );
	bool s = call( greater<int>(), _1, 1 )( 3 );
	ENSURE( "greater functor binded incorrectly", s );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 25, "call in superposition" )
	typedef HList<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ),
			compose2(
				logical_and<bool>(),
				call( less<int>(), 30, _1 ),
				call( greater<int>(), 60, _1 ) ) );
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

class MemFunTest
	{
	int _base;
public:
	MemFunTest( int base_ ) : _base( base_ ) {}
	int value( void )
		{ return ( _base ); }
	int calc( int arg_ )
		{ return ( _base + arg_ ); }

	};

TUT_UNIT_TEST_N( 26, "mem_fun, mem_fun_ref" )
	typedef HPointer<MemFunTest> mem_fun_test_ptr_t;
	typedef HList<mem_fun_test_ptr_t> list_t;
	typedef HList<MemFunTest*> naked_list_t;

	list_t l;
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 0 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 1 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 3 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 7 ) ) );

	naked_list_t nl;
	transform( l.begin(), l.end(), back_insert_iterator( nl ), mem_fun_ref( &mem_fun_test_ptr_t::raw ) );
	HStringStream ss;
	transform( nl.begin(), nl.end(), stream_iterator( ss, " " ), mem_fun( &MemFunTest::value ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "0 1 3 7 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 27, "mem_fun1" )
	int a[] = { 1, 4, 9, 16 };
	typedef HPointer<MemFunTest> mem_fun_test_ptr_t;
	typedef HList<mem_fun_test_ptr_t> list_t;
	typedef HList<MemFunTest*> naked_list_t;

	list_t l;
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 0 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 1 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 3 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 7 ) ) );

	naked_list_t nl;
	transform( l.begin(), l.end(), back_insert_iterator( nl ), mem_fun_ref( &mem_fun_test_ptr_t::raw ) );
	HStringStream ss;
	transform( nl.begin(), nl.end(), a, stream_iterator( ss, " " ), mem_fun1( &MemFunTest::calc ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "1 5 12 23 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 28, "mem_fun1_ref" )
	int a[] = { 1, 4, 9, 16 };
	typedef HList<MemFunTest> list_t;

	list_t l;
	l.push_back( MemFunTest( 0 ) );
	l.push_back( MemFunTest( 1 ) );
	l.push_back( MemFunTest( 3 ) );
	l.push_back( MemFunTest( 7 ) );

	HStringStream ss;
	transform( l.begin(), l.end(), a, stream_iterator( ss, " " ), mem_fun1_ref( &MemFunTest::calc ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "1 5 12 23 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 29, "replace" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	replace( a, a + countof ( a ), 36, 7 );
	HStringStream ss;
	copy( a, a + countof ( a ), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "replace failed", ss.string(), "7 1 4 9 16 25 7 49 64 81 100 7 " );
	cout << ss.string() << endl;
TUT_TEARDOWN()

}

