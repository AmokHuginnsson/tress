/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_stl.cxx - this file is integral part of `tress' project.

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

#ifndef __GNUC__
#define _HAS_TRADITIONAL_STL 1
#endif /* not __GNUC__ */

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#ifdef __GNUC__
#include <ext/functional>
#endif /* __GNUC__ */

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace stdext;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_stl
	{
	virtual ~tut_stl( void ) {}
	};

TUT_TEST_GROUP_N( tut_stl, yaal::hcore::_debugLevel_ > yaal::hcore::DEBUG_LEVEL::ABORT_ON_ASSERT ? "yaal" : "stl" );

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

TUT_UNIT_TEST_N( 6, "back_insert_iterator" )
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 3, 14, 15, 9265, 35, 89, 79, 3 };
	int d4[] = { 1, 2, 4, 2, 3, 5, 7, 3, 14, 15, 9265, 35, 89, 79, 3 };
	typedef list<int> list_t;

	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l4( d4, d4 + sizeof ( d4 ) / sizeof ( int ) );
	list_t l;
	copy( l1.begin(), l1.end(), back_insert_iterator<list_t>( l ) );
	copy( l2.begin(), l2.end(), back_insert_iterator<list_t>( l ) );
	copy( l3.begin(), l3.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "back_insert_iterator<list_t> failed", l, l4 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "equal" )
	typedef list<int> list_t;
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	ENSURE( "positive test for equality failed", equal( l1.begin(), l1.end(), d1 ) );
	ENSURE_NOT( "negative test for equality failed", equal( l1.begin(), l1.end(), l2.begin() ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "set_union uniqe" )
	typedef list<int> list_t;
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 1, 2, 3, 4, 5, 7 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l;
	set_union( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "set_union failed l1 + l2", l, l3 );
	l.clear();
	set_union( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "set_union failed l2 + l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "set_union duplicates" )
	typedef list<int> list_t;
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 1, 2, 2, 3, 4, 5, 7 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l;
	set_union( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "set_union failed l1 + l2", l, l3 );
	l.clear();
	set_union( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "set_union failed l2 + l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "set_intersection unique" )
	typedef list<int> list_t;
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 2 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l;
	set_intersection( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "set_intersection failed l1 * l2", l, l3 );
	l.clear();
	set_intersection( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "set_intersection failed l2 * l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "set_intersection duplicates" )
	typedef list<int> list_t;
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 2, 3, 5, 7 };
	int d3[] = { 2, 2 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	list_t l3( d3, d3 + sizeof ( d3 ) / sizeof ( int ) );
	list_t l;
	set_intersection( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "set_intersection failed l1 * l2", l, l3 );
	l.clear();
	set_intersection( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator<list_t>( l ) );
	ENSURE_EQUALS( "set_intersection failed l2 * l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "remove_if algorithm" )
	typedef list<int> list_t;
	int a[] = { 1, -2, 3, -4, 9, -8, 7, -6, 5 };
	list_t l( a, a + countof( a ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
	list_t::iterator end( remove_if( l.begin(), l.end(), bind2nd( less<int>(), 0 ) ) ); 
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
	l.erase( end, l.end() );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
	int b[] = { 1, 3, 9, 7, 5 };
	ENSURE( "remove_if failed", equal( l.begin(), l.end(), b ) );
TUT_TEARDOWN()

template<typename to_t, typename from_t>
struct cast : public std::unary_function<from_t, to_t>
	{
	to_t operator()( from_t from_ ) const
		{
		return ( static_cast<to_t>( from_ ) );
		}
	};

#pragma GCC diagnostic ignored "-Weffc++"
TUT_UNIT_TEST_N( 13, "transform" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( static_cast<int*>( a ), a + countof( a ), back_insert_iterator<list_t>( l ), compose1( cast<int, double>(), ptr_fun( static_cast<double (*)( double )>( sqrt ) ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "transform failed", ss.str(), "1 2 3 4 5 6 7 8 9 10 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()
#pragma GCC diagnostic warning "-Weffc++"

TUT_UNIT_TEST_N( 14, "negate" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( a, a + countof( a ), back_insert_iterator<list_t>( l ), negate<int>() );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "negate failed", ss.str(), "-1 -4 -9 -16 -25 -36 -49 -64 -81 -100 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 15, "compose1" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( a, a + countof( a ), back_insert_iterator<list_t>( l ), compose1( negate<int>(), bind1st( plus<int>(), 1 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "compose1 failed", ss.str(), "-2 -5 -10 -17 -26 -37 -50 -65 -82 -101 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 16, "remove_copy_if" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
				bind1st( less<int>(), 30 ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "remove_copy_if failed", ss.str(), "1 4 9 16 25 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 17, "compose2" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
			compose2(
				logical_and<bool>(),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "compose2 failed", ss.str(), "1 4 9 16 25 64 81 100 " );
	cout << ss.str() << endl;
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
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "not2 failed", ss.str(), "36 49 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 22, "identity" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( bind1st( less<int>(), 30 ), identity<int>() ),
				bind1st( greater<int>(), 60 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "identity failed", ss.str(), "36 49 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 23, "ptr_fun" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( compose1( bind1st( less<int>(), 5 ), compose1( cast<int, double>(), ptr_fun( static_cast<double (*)( double )>( sqrt ) ) ) ), cast<int, int>() ),
				bind1st( greater<int>(), 60 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "ptr_fun failed", ss.str(), "36 49 " );
	cout << ss.str() << endl;
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

template<typename T>
T* get_pointer( T& x )
	{ return ( &x ); }

TUT_UNIT_TEST_N( 26, "mem_fun, mem_fun_ref" )
	typedef list<MemFunTest> list_t;
	typedef list<MemFunTest*> naked_list_t;

	list_t l;
	l.push_back( MemFunTest( 0 ) );
	l.push_back( MemFunTest( 1 ) );
	l.push_back( MemFunTest( 3 ) );
	l.push_back( MemFunTest( 7 ) );

	naked_list_t nl;
	transform( l.begin(), l.end(), back_insert_iterator<naked_list_t>( nl ), get_pointer<MemFunTest> );
	stringstream ss;
	transform( nl.begin(), nl.end(), ostream_iterator<int>( ss, " " ), mem_fun( &MemFunTest::value ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.str(), "0 1 3 7 " );
	ss.flush();
	transform( l.begin(), l.end(), ostream_iterator<int>( ss, " " ), mem_fun_ref( &MemFunTest::value ) );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 27, "mem_fun1" )
	int a[] = { 1, 4, 9, 16 };
	typedef list<MemFunTest> list_t;
	typedef list<MemFunTest*> naked_list_t;

	list_t l;
	l.push_back( MemFunTest( 0 ) );
	l.push_back( MemFunTest( 1 ) );
	l.push_back( MemFunTest( 3 ) );
	l.push_back( MemFunTest( 7 ) );

	naked_list_t nl;
	transform( l.begin(), l.end(), back_insert_iterator<naked_list_t>( nl ), get_pointer<MemFunTest> );
	stringstream ss;
	transform( nl.begin(), nl.end(), a, ostream_iterator<int>( ss, " " ), mem_fun1( &MemFunTest::calc ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.str(), "1 5 12 23 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 28, "mem_fun1_ref" )
	int a[] = { 1, 4, 9, 16 };
	typedef list<MemFunTest> list_t;

	list_t l;
	l.push_back( MemFunTest( 0 ) );
	l.push_back( MemFunTest( 1 ) );
	l.push_back( MemFunTest( 3 ) );
	l.push_back( MemFunTest( 7 ) );

	stringstream ss;
	transform( l.begin(), l.end(), a, ostream_iterator<int>( ss, " " ), mem_fun1_ref( &MemFunTest::calc ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.str(), "1 5 12 23 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 29, "replace" )
	typedef list<int> list_t;
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	list_t l;
	replace( a, a + countof ( a ), 36, 7 );
	stringstream ss;
	copy( a, a + countof ( a ), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "replace failed", ss.str(), "7 1 4 9 16 25 7 49 64 81 100 7 " );
	cout << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 42, "transform (negate) container content automatically" )
	cout << "negate container content ..." << endl;
	cout << "{" << endl;
	typedef list<int> T;
	T l;
	generate_n( std::back_insert_iterator<T>( l ), 20, inc( 1 ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	replace_if(l.begin(), l.end(), std::bind2nd( less<int>(), 10 ), 10);
	copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	transform( l.begin(), l.end(), l.begin(), negate<int>() );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	transform( l.begin(), l.end(), l.begin(), bind2nd( plus<int>(), 7 ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	cout << "}" << endl;
	vector<string> vs;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 43, "max_size of string" )
	string str;
	cout << str.max_size() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 44, "map insert of already existing key")
	typedef map<int, int> i2i_t;
	i2i_t m;
	m.insert( std::make_pair( 1, 2 ) );
	ENSURE( "element not inserted", m.find( 1 ) != m.end() );
	typedef pair<i2i_t::iterator, bool> insert_result_t;
	insert_result_t ir = m.insert( std::make_pair( 1, 3 ) );
	ENSURE_EQUALS( "element with already existing key inserted", ir.second, false );
	cout << (*ir.first).second << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 45, "manipulators" )
	string str;
	int i( 7 );
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setfill( '0' ) << i << "'" << " \tsetfill( '0' )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setfill( '0' ) << setw( 5 ) << i << "'" << " \tsetfill( '0' ), setw( 5 )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setfill( '0' ) << i << "'" << " \tsetfill( '0' )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	int k( 103 );
	cout << "[O] k = '" << k << "'" << endl;
	cout << "[M] k = '" << hex << k << "' \thex" << endl;
	cout << "[O] k = '" << k << "'" << endl;
	cout << dec << flush;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 46, "display automatically" )
	cout << "display container contents automatically ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 3 );
	copy( s.begin(), s.end(), ostream_iterator<int>( cout ) );
	cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 47, "create contents automatically" )
	cout << "create container contents automatically ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	generate_n( std::insert_iterator<T>( s, s.begin() ), 3, inc( 1 ) );
	copy( s.begin(), s.end(), ostream_iterator<int>( cout ) );
	cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 48, "reverse container content automatically" )
	cout << "reverse container content ..." << endl;
	cout << "{" << endl;
	typedef list<int> T;
	T l;
	generate_n( std::back_insert_iterator<T>( l ), 3, inc( 1 ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	reverse( l.begin(), l.end() );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	T lc;
	reverse_copy( l.begin(), l.end(), std::back_insert_iterator<T>( lc ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	copy( lc.begin(), lc.end(), ostream_iterator<int>( cout ) ); cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 49, "create by_hand" )
	cout << "lets do everything by hand ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 3 );

	for ( T::const_iterator it = s.begin(); it != s.end(); ++ it )
		cout << *it;
	cout << endl;

	cout << "}" << endl;
TUT_TEARDOWN()

}

