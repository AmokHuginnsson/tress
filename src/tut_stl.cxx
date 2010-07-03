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

TUT_SIMPLE_MOCK( tut_stl );
TUT_TEST_GROUP_N( tut_stl, yaal::hcore::_debugLevel_ > yaal::hcore::DEBUG_LEVEL::ABORT_ON_ASSERT ? "yaal" : "stl" );

TUT_UNIT_TEST_N( 1, "create by_hand" )
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

TUT_UNIT_TEST_N( 2, "display automatically" )
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

TUT_UNIT_TEST_N( 3, "create contents automatically" )
	cout << "create container contents automatically ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	generate_n( std::insert_iterator<T>( s, s.begin() ), 3, inc( 1 ) );
	copy( s.begin(), s.end(), ostream_iterator<int>( cout ) );
	cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "reverse container content automatically" )
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

TUT_UNIT_TEST_N( 5, "transform (negate) container content automatically" )
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

TUT_UNIT_TEST_N( 6, "max_size of string" )
	string str;
	cout << str.max_size() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "map insert of already existing key")
	typedef map<int, int> i2i_t;
	i2i_t m;
	m.insert( std::make_pair( 1, 2 ) );
	ENSURE( "element not inserted", m.find( 1 ) != m.end() );
	typedef pair<i2i_t::iterator, bool> insert_result_t;
	insert_result_t ir = m.insert( std::make_pair( 1, 3 ) );
	ENSURE_EQUALS( "element with already existing key inserted", ir.second, false );
	cout << (*ir.first).second << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "manipulators" )
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

TUT_UNIT_TEST_N( 9, "transform" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( static_cast<int*>( a ), a + countof( a ), back_insert_iterator<list_t>( l ), static_cast<double (*)( double )>( sqrt ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "compose1" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( a, a + countof( a ), back_insert_iterator<list_t>( l ), compose1( negate<int>(), bind1st( plus<int>(), 1 ) ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "remove_copy_if" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
				bind1st( less<int>(), 30 ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "compose2" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
			compose2(
				logical_and<bool>(),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "not2" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "identity" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( bind1st( less<int>(), 30 ), identity<int>() ),
				bind1st( greater<int>(), 60 ) ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 15, "ptr_fun" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( bind1st( less<int>(), 5 ), ptr_fun( static_cast<double (*)( double )>( sqrt ) ) ),
				bind1st( greater<int>(), 60 ) ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

}

