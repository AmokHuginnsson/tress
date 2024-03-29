/* Read tress/LICENSE.md file for copyright and licensing information. */

#ifndef __GNUC__
#define _HAS_TRADITIONAL_STL 1
#endif /* not __GNUC__ */

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include "config.hxx"
#ifdef __GNUC__
#ifdef HAVE_SGI_STL_EXTENSIONS
#include <ext/functional>
#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */
#endif /* __GNUC__ */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace tut;
using namespace std;
#ifdef HAVE_SGI_STL_EXTENSIONS
using namespace stdext;
#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */
using namespace tress::tut_helpers;

namespace tut {

struct tut_stl {
	virtual ~tut_stl( void ) {}
};

TUT_TEST_GROUP( tut_stl, yaal::hcore::_debugLevel_ <= yaal::hcore::DEBUG_LEVEL::ABORT_ON_ASSERT ? "stl" : "yaal" );

TUT_UNIT_TEST( "swap" )
	int a( 7 );
	int b( 13 );
	ENSURE_EQUALS( "init failed", a, 7 );
	ENSURE_EQUALS( "init failed", b, 13 );
	swap( a, b );
	ENSURE_EQUALS( "swap failed", a, 13 );
	ENSURE_EQUALS( "swap failed", b, 7 );
TUT_TEARDOWN()


#ifdef HAVE_PRE_CXX17_STL
TUT_UNIT_TEST( "bind1st" )
	bool p = bind1st( less<int>(), 4 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", p );
	bool q = bind1st( less<int>(), 1 )( 3 );
	ENSURE( "greater functor binded incorrectly", q );
TUT_TEARDOWN()

TUT_UNIT_TEST( "bind2nd" )
	bool p = bind2nd( greater<int>(), 4 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", p );
	bool q = bind2nd( greater<int>(), 1 )( 3 );
	ENSURE( "greater functor binded incorrectly", q );
TUT_TEARDOWN()
#endif

TUT_UNIT_TEST( "copy algorithm" )
	int tab1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int tab2[] = { 0, -1, -2, -3, -4, -5, -6, -7 };
	copy( tab2 + 2, tab2 + 5, tab1 + 2 );
	ENSURE_EQUALS( "copy started too early", tab1[ 1 ], 1 );
	ENSURE_EQUALS( "copy started too late", tab1[ 2 ], -2 );
	ENSURE_EQUALS( "copy finished too early", tab1[ 4 ], -4 );
	ENSURE_EQUALS( "copy finished too late", tab1[ 5 ], 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "back_insert_iterator" )
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

TUT_UNIT_TEST( "equal" )
	typedef list<int> list_t;
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	list_t l1( d1, d1 + sizeof ( d1 ) / sizeof ( int ) );
	list_t l2( d2, d2 + sizeof ( d2 ) / sizeof ( int ) );
	ENSURE( "positive test for equality failed", equal( l1.begin(), l1.end(), d1 ) );
	ENSURE_NOT( "negative test for equality failed", equal( l1.begin(), l1.end(), l2.begin() ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_union uniqe" )
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

TUT_UNIT_TEST( "set_union duplicates" )
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

TUT_UNIT_TEST( "set_intersection unique" )
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

TUT_UNIT_TEST( "set_intersection duplicates" )
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

TUT_UNIT_TEST( "remove_if algorithm" )
	typedef list<int> list_t;
	int a[] = { 1, -2, 3, -4, 9, -8, 7, -6, 5 };
	list_t l( a, a + yaal::size( a ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog, " " ) );
	clog << endl;
#ifdef HAVE_PRE_CXX17_STL
	list_t::iterator end( remove_if( l.begin(), l.end(), bind2nd( less<int>(), 0 ) ) );
#else
	list_t::iterator end( std::remove_if( l.begin(), l.end(), yaal::bind2nd( less<int>(), 0 ) ) );
#endif
	copy( l.begin(), l.end(), ostream_iterator<int>( clog, " " ) );
	clog << endl;
	l.erase( end, l.end() );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog, " " ) );
	clog << endl;
	int b[] = { 1, 3, 9, 7, 5 };
	ENSURE( "remove_if failed", equal( l.begin(), l.end(), b ) );
TUT_TEARDOWN()

#pragma GCC diagnostic ignored "-Weffc++"
template<typename to_t, typename from_t>
struct cast : public std::unary_function<from_t, to_t> {
	to_t operator()( from_t from_ ) const {
		return ( static_cast<to_t>( from_ ) );
	}
};

#ifdef HAVE_SGI_STL_EXTENSIONS

TUT_UNIT_TEST( "transform" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( static_cast<int*>( a ), a + yaal::size( a ), back_insert_iterator<list_t>( l ), compose1( cast<int, double>(), ptr_fun( static_cast<double (*)( double )>( sqrt ) ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "transform failed", ss.str(), "1 2 3 4 5 6 7 8 9 10 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */

TUT_UNIT_TEST( "negate" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ), negate<int>() );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "negate failed", ss.str(), "-1 -4 -9 -16 -25 -36 -49 -64 -81 -100 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

#ifdef HAVE_SGI_STL_EXTENSIONS

TUT_UNIT_TEST( "compose1" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	transform( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ), compose1( negate<int>(), bind1st( plus<int>(), 1 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "compose1 failed", ss.str(), "-2 -5 -10 -17 -26 -37 -50 -65 -82 -101 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */

TUT_UNIT_TEST( "remove_copy_if" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
#ifdef HAVE_PRE_CXX17_STL
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ), bind1st( less<int>(), 30 ) );
#else
	std::remove_copy_if( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ), yaal::bind1st( less<int>(), 30 ) );
#endif
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "remove_copy_if failed", ss.str(), "1 4 9 16 25 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

#ifdef HAVE_SGI_STL_EXTENSIONS

TUT_UNIT_TEST( "compose2" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ),
			compose2(
				logical_and<bool>(),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "compose2 failed", ss.str(), "1 4 9 16 25 64 81 100 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */

TUT_UNIT_TEST( "count" )
	int a[] = { 1, 4, 9, 16, 25, 36, 16, 49, 64, 81, 100, 16 };
	ENSURE_EQUALS( "misscounted 16", count( a, a + yaal::size( a ), 16 ), 3 );
	ENSURE_EQUALS( "misscounted 16", count( a, a + yaal::size( a ), 17 ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "count_if" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
#ifdef HAVE_PRE_CXX17_STL
	ENSURE_EQUALS( "misscounted 16", count_if( a, a + yaal::size( a ), bind2nd( less<int>(), 50 ) ), 7 );
	ENSURE_EQUALS( "misscounted 16", count_if( a, a + yaal::size( a ), bind2nd( less<int>(), 1 ) ), 0 );
#else
	ENSURE_EQUALS( "misscounted 16", std::count_if( a, a + yaal::size( a ), yaal::bind2nd( less<int>(), 50 ) ), 7 );
	ENSURE_EQUALS( "misscounted 16", std::count_if( a, a + yaal::size( a ), yaal::bind2nd( less<int>(), 1 ) ), 0 );
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "not1" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
#ifdef HAVE_PRE_CXX17_STL
	ENSURE_EQUALS( "misscounted 16", count_if( a, a + yaal::size( a ), not1( bind2nd( less<int>(), 50 ) ) ), yaal::size( a ) - 7 );
	ENSURE_EQUALS( "misscounted 16", count_if( a, a + yaal::size( a ), not1( bind2nd( less<int>(), 1 ) ) ), yaal::size( a ) - 0 );
#else
	ENSURE_EQUALS( "misscounted 16", std::count_if( a, a + yaal::size( a ), std::not1( yaal::bind2nd( less<int>(), 50 ) ) ), yaal::size( a ) - 7 );
	ENSURE_EQUALS( "misscounted 16", std::count_if( a, a + yaal::size( a ), std::not1( yaal::bind2nd( less<int>(), 1 ) ) ), yaal::size( a ) - 0 );
#endif
TUT_TEARDOWN()

#ifdef HAVE_SGI_STL_EXTENSIONS

TUT_UNIT_TEST( "not2" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "not2 failed", ss.str(), "36 49 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "identity" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( bind1st( less<int>(), 30 ), identity<int>() ),
				bind1st( greater<int>(), 60 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "identity failed", ss.str(), "36 49 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "ptr_fun" )
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( compose1( bind1st( less<int>(), 5 ), compose1( cast<int, double>(), ptr_fun( static_cast<double (*)( double )>( sqrt ) ) ) ), cast<int, int>() ),
				bind1st( greater<int>(), 60 ) ) );
	stringstream ss;
	copy( l.begin(), l.end(), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "ptr_fun failed", ss.str(), "36 49 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */

class MemFunTest {
	int _base;
public:
	MemFunTest( int base_ ) : _base( base_ ) {}
/* cppcheck-suppress functionConst */
	int value( void )
		{ return ( _base ); }
/* cppcheck-suppress functionConst */
	int calc( int arg_ )
		{ return ( _base + arg_ ); }

};

template<typename T>
T* get_pointer( T& x )
	{ return ( &x ); }

TUT_UNIT_TEST( "mem_fun, mem_fun_ref" )
	typedef list<MemFunTest> list_t;
	typedef list<MemFunTest*> naked_list_t;

	list_t l;
	l.push_back( MemFunTest( 0 ) );
	l.push_back( MemFunTest( 1 ) );
	l.push_back( MemFunTest( 3 ) );
	l.push_back( MemFunTest( 7 ) );

	naked_list_t nl;
	std::transform( l.begin(), l.end(), back_insert_iterator<naked_list_t>( nl ), get_pointer<MemFunTest> );
	stringstream ss;
#ifdef HAVE_PRE_CXX17_STL
	transform( nl.begin(), nl.end(), ostream_iterator<int>( ss, " " ), mem_fun( &MemFunTest::value ) );
#else
	std::transform( nl.begin(), nl.end(), ostream_iterator<int>( ss, " " ), yaal::mem_fun( &MemFunTest::value ) );
#endif
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.str(), "0 1 3 7 " );
	ss.flush();
#ifdef HAVE_PRE_CXX17_STL
	transform( l.begin(), l.end(), ostream_iterator<int>( ss, " " ), mem_fun_ref( &MemFunTest::value ) );
#else
	std::transform( l.begin(), l.end(), ostream_iterator<int>( ss, " " ), yaal::mem_fun_ref( &MemFunTest::value ) );
#endif
	clog << ss.str() << endl;
TUT_TEARDOWN()

#ifdef HAVE_SGI_STL_EXTENSIONS
TUT_UNIT_TEST( "mem_fun1" )
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
	clog << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "mem_fun1_ref" )
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
	clog << ss.str() << endl;
TUT_TEARDOWN()
#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */

TUT_UNIT_TEST( "replace" )
	typedef list<int> list_t;
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	list_t l;
	replace( a, a + yaal::size( a ), 36, 7 );
	stringstream ss;
	copy( a, a + yaal::size( a ), ostream_iterator<int>( ss, " " ) );
	ENSURE_EQUALS( "replace failed", ss.str(), "7 1 4 9 16 25 7 49 64 81 100 7 " );
	clog << ss.str() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "transform (negate) container content automatically" )
	clog << "negate container content ..." << endl;
	clog << "{" << endl;
	typedef list<int> T;
	T l;
	generate_n( std::back_insert_iterator<T>( l ), 20, inc( 1 ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog ) ); clog << endl;
#ifdef HAVE_PRE_CXX17_STL
	replace_if( l.begin(), l.end(), bind2nd( less<int>(), 10 ), 10 );
#else
	std::replace_if( l.begin(), l.end(), yaal::bind2nd( less<int>(), 10 ), 10 );
#endif
	copy( l.begin(), l.end(), ostream_iterator<int>( clog ) ); clog << endl;
	transform( l.begin(), l.end(), l.begin(), negate<int>() );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog ) ); clog << endl;
#ifdef HAVE_PRE_CXX17_STL
	transform( l.begin(), l.end(), l.begin(), bind2nd( plus<int>(), 7 ) );
#else
	std::transform( l.begin(), l.end(), l.begin(), yaal::bind2nd( plus<int>(), 7 ) );
#endif
	copy( l.begin(), l.end(), ostream_iterator<int>( clog ) ); clog << endl;
	clog << "}" << endl;
	vector<string> vs;
TUT_TEARDOWN()

TUT_UNIT_TEST( "max_size of string" )
	string str;
	clog << str.max_size() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "map insert of already existing key")
	typedef map<int, int> i2i_t;
	i2i_t m;
	m.insert( std::make_pair( 1, 2 ) );
	ENSURE( "element not inserted", m.find( 1 ) != m.end() );
	typedef pair<i2i_t::iterator, bool> insert_result_t;
	insert_result_t ir = m.insert( std::make_pair( 1, 3 ) );
	ENSURE_EQUALS( "element with already existing key inserted", ir.second, false );
	clog << (*ir.first).second << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "manipulators" )
	string str;
	int i( 7 );
	clog << "[O] i = '" << i << "'" << endl;
	clog << "[M] i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	clog << "[O] i = '" << i << "'" << endl;
	clog << "[M] i = '" << setfill( '0' ) << i << "'" << " \tsetfill( '0' )" << endl;
	clog << "[O] i = '" << i << "'" << endl;
	clog << "[M] i = '" << setfill( '0' ) << setw( 5 ) << i << "'" << " \tsetfill( '0' ), setw( 5 )" << endl;
	clog << "[O] i = '" << i << "'" << endl;
	clog << "[M] i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	clog << "[O] i = '" << i << "'" << endl;
	clog << "[M] i = '" << setfill( '0' ) << i << "'" << " \tsetfill( '0' )" << endl;
	clog << "[O] i = '" << i << "'" << endl;
	int k( 103 );
	clog << "[O] k = '" << k << "'" << endl;
	clog << "[M] k = '" << hex << k << "' \thex" << endl;
	clog << "[O] k = '" << k << "'" << endl;
	clog << dec << flush;
TUT_TEARDOWN()

TUT_UNIT_TEST( "display automatically" )
	clog << "display container contents automatically ..." << endl;
	clog << "{" << endl;
	typedef set<int> T;
	T s;
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 3 );
	copy( s.begin(), s.end(), ostream_iterator<int>( clog ) );
	clog << endl;
	clog << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "create contents automatically" )
	clog << "create container contents automatically ..." << endl;
	clog << "{" << endl;
	typedef set<int> T;
	T s;
	generate_n( std::insert_iterator<T>( s, s.begin() ), 3, inc( 1 ) );
	copy( s.begin(), s.end(), ostream_iterator<int>( clog ) );
	clog << endl;
	clog << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse container content automatically" )
	clog << "reverse container content ..." << endl;
	clog << "{" << endl;
	typedef list<int> T;
	T l;
	generate_n( std::back_insert_iterator<T>( l ), 3, inc( 1 ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog ) ); clog << endl;
	reverse( l.begin(), l.end() );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog ) ); clog << endl;
	T lc;
	reverse_copy( l.begin(), l.end(), std::back_insert_iterator<T>( lc ) );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog ) ); clog << endl;
	copy( lc.begin(), lc.end(), ostream_iterator<int>( clog ) ); clog << endl;
	clog << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "create by_hand" )
	clog << "lets do everything by hand ..." << endl;
	clog << "{" << endl;
	typedef set<int> T;
	T s;
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 3 );

	for ( T::const_iterator it = s.begin(); it != s.end(); ++ it )
		clog << *it;
	clog << endl;

	clog << "}" << endl;
TUT_TEARDOWN()

}

#pragma GCC diagnostic pop

