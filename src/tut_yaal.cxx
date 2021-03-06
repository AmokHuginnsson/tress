/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal );
TUT_TEST_GROUP( tut_yaal, "yaal" );

TUT_UNIT_TEST( "swap" )
	int a( 7 );
	int b( 13 );
	ENSURE_EQUALS( "init failed", a, 7 );
	ENSURE_EQUALS( "init failed", b, 13 );
	swap( a, b );
	ENSURE_EQUALS( "swap failed", a, 13 );
	ENSURE_EQUALS( "swap failed", b, 7 );
TUT_TEARDOWN()

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

TUT_UNIT_TEST( "copy algorithm" )
	int tab1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int tab2[] = { 0, -1, -2, -3, -4, -5, -6, -7 };
	copy( tab2 + 2, tab2 + 5, tab1 + 2 );
	ENSURE_EQUALS( "copy started too early", tab1[ 1 ], 1 );
	ENSURE_EQUALS( "copy started too late", tab1[ 2 ], -2 );
	ENSURE_EQUALS( "copy finished too early", tab1[ 4 ], -4 );
	ENSURE_EQUALS( "copy finished too late", tab1[ 5 ], 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "meta::max" )
	int long unsigned q = meta::max<sizeof ( int ), sizeof ( char ), sizeof ( double long ), sizeof ( void* ), sizeof ( int long ), sizeof ( int short )>::value;
	ENSURE_EQUALS( "meta::max failed", q, sizeof ( double long ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "back_insert_iterator" )
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 3, 14, 15, 9265, 35, 89, 79, 3 };
	int d4[] = { 1, 2, 4, 2, 3, 5, 7, 3, 14, 15, 9265, 35, 89, 79, 3 };

	int_list_t l1( begin( d1 ), end( d1 ) );
	int_list_t l2( begin( d2 ), end( d2 ) );
	int_list_t l3( begin( d3 ), end( d3 ) );
	int_list_t l4( begin( d4 ), end( d4 ) );
	int_list_t l;
	copy( l1.begin(), l1.end(), back_insert_iterator( l ) );
	copy( l2.begin(), l2.end(), back_insert_iterator( l ) );
	copy( l3.begin(), l3.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "back_insert_iterator failed", l, l4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "equal" )
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int_list_t l1( begin( d1 ), end( d1 ) );
	int_list_t l2( begin( d2 ), end( d2 ) );
	ENSURE( "positive test for equality failed", safe_equal( l1.begin(), l1.end(), begin( d1 ), end( d1 ) ) );
	ENSURE( "positive test for equality failed", equal( l1.begin(), l1.end(), d1 ) );
	ENSURE_NOT( "negative test for equality failed", safe_equal( l1.begin(), l1.end(), l2.begin(), l2.end() ) );
	ENSURE_NOT( "negative test for equality failed", equal( l1.begin(), l1.end(), l2.begin() ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_union uniqe" )
	int d1[] = { 1, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 1, 2, 3, 4, 5, 7 };
	int_list_t l1( begin( d1 ), end( d1 ) );
	int_list_t l2( begin( d2 ), end( d2 ) );
	int_list_t l3( begin( d3 ), end( d3 ) );
	int_list_t l;
	set_union( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l1 + l2", l, l3 );
	l.clear();
	set_union( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l2 + l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_union duplicates" )
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 1, 2, 2, 3, 4, 5, 7 };
	int_list_t l1( begin( d1 ), end( d1 ) );
	int_list_t l2( begin( d2 ), end( d2 ) );
	int_list_t l3( begin( d3 ), end( d3 ) );
	int_list_t l;
	set_union( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l1 + l2", l, l3 );
	l.clear();
	set_union( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_union failed l2 + l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_intersection unique" )
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 3, 5, 7 };
	int d3[] = { 2 };
	int_list_t l1( begin( d1 ), end( d1 ) );
	int_list_t l2( begin( d2 ), end( d2 ) );
	int_list_t l3( begin( d3 ), end( d3 ) );
	int_list_t l;
	set_intersection( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l1 * l2", l, l3 );
	l.clear();
	set_intersection( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l2 * l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_intersection duplicates" )
	int d1[] = { 1, 2, 2, 4 };
	int d2[] = { 2, 2, 3, 5, 7 };
	int d3[] = { 2, 2 };
	int_list_t l1( begin( d1 ), end( d1 ) );
	int_list_t l2( begin( d2 ), end( d2 ) );
	int_list_t l3( begin( d3 ), end( d3 ) );
	int_list_t l;
	set_intersection( l1.begin(), l1.end(), l2.begin(), l2.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l1 * l2", l, l3 );
	l.clear();
	set_intersection( l2.begin(), l2.end(), l1.begin(), l1.end(), back_insert_iterator( l ) );
	ENSURE_EQUALS( "set_intersection failed l2 * l1", l, l3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "remove_if algorithm" )
	int a[] = { 1, -2, 3, -4, 9, -8, 7, -6, 5 };
	int_list_t l( begin( a ), end( a ) );
	copy( l.begin(), l.end(), stream_iterator( clog, " " ) );
	clog << endl;
	int_list_t::iterator end( remove_if( l.begin(), l.end(), bind2nd( less<int>(), 0 ) ) );
	copy( l.begin(), l.end(), stream_iterator( clog, " " ) );
	clog << endl;
	l.erase( end, l.end() );
	copy( l.begin(), l.end(), stream_iterator( clog, " " ) );
	clog << endl;
	int b[] = { 1, 3, 9, 7, 5 };
	ENSURE( "remove_if failed", safe_equal( l.begin(), l.end(), begin( b ), yaal::end( b ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "transform" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	transform( begin( a ), end( a ), back_insert_iterator( l ), compose1( bound_cast<int, double>(), ptr_fun( static_cast<double (*)( double )>( sqrt ) ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "transform failed", ss.string(), "1 2 3 4 5 6 7 8 9 10 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "negate" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	transform( begin( a ), end( a ), back_insert_iterator( l ), negate<int>() );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "negate failed", ss.string(), "-1 -4 -9 -16 -25 -36 -49 -64 -81 -100 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "compose1" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	transform( begin( a ), end( a ), back_insert_iterator( l ), compose1( negate<int>(), bind1st( plus<int>(), 1 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "compose1 failed", ss.string(), "-2 -5 -10 -17 -26 -37 -50 -65 -82 -101 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "remove_copy_if" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	remove_copy_if( begin( a ), end( a ), back_insert_iterator( l ),
				bind1st( less<int>(), 30 ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "remove_copy_if failed", ss.string(), "1 4 9 16 25 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "compose2" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	remove_copy_if( begin( a ), end( a ), back_insert_iterator( l ),
			compose2(
				logical_and<bool>(),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "compose2 failed", ss.string(), "1 4 9 16 25 64 81 100 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "count" )
	int a[] = { 1, 4, 9, 16, 25, 36, 16, 49, 64, 81, 100, 16 };
	ENSURE_EQUALS( "misscounted 16", count( begin( a ), end( a ), 16 ), 3 );
	ENSURE_EQUALS( "misscounted 16", count( begin( a ), end( a ), 17 ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "count_if" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	ENSURE_EQUALS( "misscounted 16", count_if( begin( a ), end( a ), bind2nd( less<int>(), 50 ) ), 7 );
	ENSURE_EQUALS( "misscounted 16", count_if( begin( a ), end( a ), bind2nd( less<int>(), 1 ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "not1" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	ENSURE_EQUALS( "misscounted 16", count_if( begin( a ), end( a ), not1( bind2nd( less<int>(), 50 ) ) ), yaal::size( a ) - 7 );
	ENSURE_EQUALS( "misscounted 16", count_if( begin( a ), end( a ), not1( bind2nd( less<int>(), 1 ) ) ), yaal::size( a ) - 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "not2" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	remove_copy_if( begin( a ), end( a ), back_insert_iterator( l ),
			compose2(
				not2(	logical_and<bool>() ),
				bind1st( less<int>(), 30 ),
				bind1st( greater<int>(), 60 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "not2 failed", ss.string(), "36 49 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "identity" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	remove_copy_if( begin( a ), end( a ), back_insert_iterator( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( bind1st( less<int>(), 30 ), identity<int>() ),
				bind1st( greater<int>(), 60 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "identity failed", ss.string(), "36 49 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "ptr_fun" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	remove_copy_if( begin( a ), end( a ), back_insert_iterator( l ),
			compose2(
				not2(	logical_and<bool>() ),
				compose1( bind1st( less<int>(), 5 ), compose1( compose1( bound_cast<int, double>(), ptr_fun( static_cast<double (*)( double )>( sqrt ) ) ), bound_cast<int, int>() ) ),
				bind1st( greater<int>(), 60 ) ) );
	HStringStream ss;
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "ptr_fun failed", ss.string(), "36 49 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "call as bind1st/bind2nd" )
	bool p = call( less<int>(), 4, _1 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", p );
	bool q = call( less<int>(), 1, _1 )( 3 );
	ENSURE( "greater functor binded incorrectly", q );
	bool r = call( greater<int>(), _1, 4 )( 3 );
	ENSURE_NOT( "greater functor binded incorrectly", r );
	bool s = call( greater<int>(), _1, 1 )( 3 );
	ENSURE( "greater functor binded incorrectly", s );
TUT_TEARDOWN()

TUT_UNIT_TEST( "call in superposition" )
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	int_list_t l;
	remove_copy_if( begin( a ), end( a ), back_insert_iterator( l ),
			compose2(
				logical_and<bool>(),
				call( less<int>(), 30, _1 ),
				call( greater<int>(), 60, _1 ) ) );
	copy( l.begin(), l.end(), stream_iterator( clog, " " ) );
	clog << endl;
TUT_TEARDOWN()

namespace {

class MemFunTest {
	int _base;
public:
	MemFunTest( int base_ ) : _base( base_ ) {}
/* cppcheck-suppress functionConst */
	int value( void )
		{ return ( _base ); }
	int value_const( void ) const
		{ return ( _base ); }
/* cppcheck-suppress functionConst */
	int calc( int arg_ )
		{ return ( _base + arg_ ); }
	int calc_const( int arg_ ) const
		{ return ( _base + arg_ ); }
};

}

TUT_UNIT_TEST( "mem_fun, mem_fun_ref" )
	typedef HPointer<MemFunTest> mem_fun_test_ptr_t;
	typedef HList<mem_fun_test_ptr_t> mem_fun_ptr_list_t;
	typedef HList<MemFunTest*> naked_list_t;
	typedef HList<MemFunTest const*> const_naked_list_t;

	mem_fun_ptr_list_t l;
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 0 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 1 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 3 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 7 ) ) );

	naked_list_t nl;
	const_naked_list_t cnl;
	transform( l.begin(), l.end(), back_insert_iterator( nl ), mem_fun_ref( static_cast<tut::MemFunTest* ( yaal::hcore::HPointer<tut::MemFunTest>::* )( void )>( &mem_fun_test_ptr_t::raw ) ) );
	transform( l.begin(), l.end(), back_insert_iterator( cnl ), mem_fun_ref( static_cast<tut::MemFunTest const* ( yaal::hcore::HPointer<tut::MemFunTest>::* )( void ) const>( &mem_fun_test_ptr_t::raw ) ) );
	HStringStream ss;
	transform( nl.begin(), nl.end(), stream_iterator( ss, " " ), mem_fun( &MemFunTest::value ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "0 1 3 7 " );
	clog << ss.string() << endl;
	ss.reset();
	transform( cnl.begin(), cnl.end(), stream_iterator( ss, " " ), mem_fun( &MemFunTest::value_const ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "0 1 3 7 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "mem_fun1" )
	int a[] = { 1, 4, 9, 16 };
	typedef HPointer<MemFunTest> mem_fun_test_ptr_t;
	typedef HList<mem_fun_test_ptr_t> mem_fun_ptr_list_t;
	typedef HList<MemFunTest*> naked_list_t;
	typedef HList<MemFunTest const*> const_naked_list_t;

	mem_fun_ptr_list_t l;
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 0 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 1 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 3 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 7 ) ) );

	naked_list_t nl;
	const_naked_list_t cnl;
	transform( l.begin(), l.end(), back_insert_iterator( nl ), mem_fun_ref( static_cast<tut::MemFunTest* ( yaal::hcore::HPointer<tut::MemFunTest>::* )( void )>( &mem_fun_test_ptr_t::raw ) ) );
	transform( l.begin(), l.end(), back_insert_iterator( cnl ), mem_fun_ref( static_cast<tut::MemFunTest const* ( yaal::hcore::HPointer<tut::MemFunTest>::* )( void ) const>( &mem_fun_test_ptr_t::raw ) ) );
	HStringStream ss;
	transform( nl.begin(), nl.end(), a, stream_iterator( ss, " " ), mem_fun1( &MemFunTest::calc ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "1 5 12 23 " );
	clog << ss.string() << endl;
	ss.reset();
	transform( cnl.begin(), cnl.end(), a, stream_iterator( ss, " " ), mem_fun1( &MemFunTest::calc_const ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "1 5 12 23 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "mem_fun1_ref" )
	int a[] = { 1, 4, 9, 16 };
	typedef HList<MemFunTest> mem_fun_list_t;

	mem_fun_list_t l;
	l.push_back( MemFunTest( 0 ) );
	l.push_back( MemFunTest( 1 ) );
	l.push_back( MemFunTest( 3 ) );
	l.push_back( MemFunTest( 7 ) );

	HStringStream ss;
	transform( l.begin(), l.end(), a, stream_iterator( ss, " " ), mem_fun1_ref( &MemFunTest::calc ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "1 5 12 23 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "replace" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	replace( begin( a ), end( a ), 36, 7 );
	HStringStream ss;
	copy( begin( a ), end( a ), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "replace failed", ss.string(), "7 1 4 9 16 25 7 49 64 81 100 7 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "for_each of for_each" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int_array_t a0( begin( a ), end( a ) );
	typedef HArray<int_array_t> matrix_t;
	matrix_t m;
	m.push_back( a0 );
	transform( a0.begin(), a0.end(), a0.begin(), a0.begin(), multiplies<int>() );
	m.push_back( a0 );
	transform( a0.begin(), a0.end(), a, a0.begin(), minus<int>() );
	m.push_back( a0 );
	copy( m.begin(), m.end(), stream_iterator( clog, endl ) );
TUT_TEARDOWN()


}

