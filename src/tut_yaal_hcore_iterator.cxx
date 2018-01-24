/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/iterator.hxx>
#include <yaal/hcore/hstreaminterface.hxx>
#include <yaal/tools/assign.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_iterator );
TUT_TEST_GROUP( tut_yaal_hcore_iterator, "yaal::hcore::iterators" );
typedef HResource<int> int_res_t;
typedef HArray<int_res_t> int_res_array_t;
auto int_res_cmp = []( int_res_t const& left_, int_res_t const& right_ ){ return ( *left_ < *right_ ); };
typedef decltype( int_res_cmp ) int_res_cmp_t;
typedef HSet<int_res_t, int_res_cmp_t> int_res_set_t;
typedef HDeque<int_res_t> int_res_deque_t;

TUT_UNIT_TEST( "unordered sequence back_insert_iterator, continuous" )
	int_array_t ui;
	HBackInsertIterator<int_array_t> iui( back_insert_iterator<int_array_t>( ui ) );
	ENSURE_EQUALS( "back_insert_iterator constructor failed", ui, int_array_t() );
	*iui = 5;
	*iui = 3;
	*iui = 7;
	*iui = 1;
	*iui = 9;
	ENSURE_EQUALS( "back_insert_iterator failed", ui, array( 5, 3, 7, 1, 9 ) );
	int_res_array_t ir;
	HBackInsertIterator<int_res_array_t> iri( back_insert_iterator<int_res_array_t>( ir ) );
	*iri = make_resource<int>( 7 );
	*iri = make_resource<int>( 3 );
	ENSURE_EQUALS( "bad size after iter back insert", ir.get_size(), 2 );
	ENSURE_EQUALS( "first elem after iter back insert", *ir.front(), 7 );
	ENSURE_EQUALS( "bad last after iter back insert", *ir.back(), 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "unordered sequence front_insert_iterator, continuous" )
	int_deque_t ui;
	HFrontInsertIterator<int_deque_t> iui( front_insert_iterator<int_deque_t>( ui ) );
	ENSURE_EQUALS( "front_insert_iterator constructor failed", ui, int_deque_t() );
	*iui = 5;
	*iui = 3;
	*iui = 7;
	*iui = 1;
	*iui = 9;
	ENSURE_EQUALS( "front_insert_iterator failed", ui, int_deque_t({ 9, 1, 7, 3, 5 }) );
	int_res_deque_t ir;
	HFrontInsertIterator<int_res_deque_t> iri( front_insert_iterator<int_res_deque_t>( ir ) );
	*iri = make_resource<int>( 3 );
	*iri = make_resource<int>( 7 );
	ENSURE_EQUALS( "bad size after iter back insert", ir.get_size(), 2 );
	ENSURE_EQUALS( "first elem after iter back insert", *ir.front(), 7 );
	ENSURE_EQUALS( "bad last after iter back insert", *ir.back(), 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ordered sequence insert_iterator, continuous" )
	int_set_t oi;
	HInsertIterator<int_set_t> ioi( insert_iterator( oi ) );
	ENSURE_EQUALS( "insert_iterator constructor failed", oi, int_set_t() );
	*ioi = 5;
	*ioi = 3;
	*ioi = 7;
	*ioi = 1;
	*ioi = 9;
	ENSURE_EQUALS( "insert_iterator failed", oi, static_cast<int_set_t const&>( sequence( 5 )( 3 )( 7 )( 1 )( 9 ) ) );
	int_res_set_t ir( int_res_cmp );
	HInsertIterator<int_res_set_t> iri( insert_iterator<int_res_set_t>( ir ) );
	*iri = make_resource<int>( 3 );
	*iri = make_resource<int>( 7 );
	ENSURE_EQUALS( "bad size after iter back insert", ir.get_size(), 2 );
	ENSURE_EQUALS( "first elem after iter back insert", **ir.begin(), 3 );
	ENSURE_EQUALS( "bad last after iter back insert", **ir.rbegin(), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "unordered sequence, back_insert_iterator, intermittent" )
	int_array_t ui;
	HBackInsertIterator<int_array_t> iui( back_insert_iterator<int_array_t>( ui ) );
	ENSURE_EQUALS( "back_insert_iterator constructor failed", ui, int_array_t() );
	*iui = 5;
	*iui = 3;
	++ iui;
	++ iui;
	++ iui;
	*iui = 7;
	*iui = 1;
	*iui = 9;
	ENSURE_EQUALS( "back_insert_iterator failed", ui, array( 5, 3, 7, 1, 9 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ordered sequence insert_iterator, intermittent" )
	int_set_t oi;
	HInsertIterator<int_set_t> ioi( insert_iterator( oi ) );
	ENSURE_EQUALS( "insert_iterator constructor failed", oi, int_set_t() );
	*ioi = 5;
	*ioi = 3;
	++ ioi;
	++ ioi;
	++ ioi;
	*ioi = 7;
	*ioi = 1;
	*ioi = 9;
	ENSURE_EQUALS( "insert_iterator failed", oi, static_cast<int_set_t const&>( sequence( 5 )( 3 )( 7 )( 1 )( 9 ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ostream_iterator, continuous" )
	HStringStream ss;
	HStreamIterator<int> oi( ss, " " );
	*oi = 5;
	*oi = 3;
	*oi = 7;
	*oi = 1;
	*oi = 9;
	ENSURE_EQUALS( "ostream_iterator failed", ss.string(), "5 3 7 1 9 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ostream_iterator, intermittent" )
	HStringStream ss;
	HStreamIterator<int> oi( ss, " " );
	*oi = 5;
	*oi = 3;
	++ oi;
	++ oi;
	++ oi;
	*oi = 7;
	*oi = 1;
	*oi = 9;
	ENSURE_EQUALS( "ostream_iterator failed", ss.string(), "5 3 7 1 9 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( "istream_iterator, continuous" )
	HStringStream ss( "5 3 7 1 9" );
	HStreamIterator<int> ii( ss );
	int_array_t arr;
	arr.push_back( *ii );
	arr.push_back( *ii );
	arr.push_back( *ii );
	arr.push_back( *ii );
	arr.push_back( *ii );
	ENSURE_EQUALS( "back_insert_iterator failed", arr, array( 5, 5, 5, 5, 5 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "istream_iterator, intermittent" )
	HStringStream ss( "5 3 7 1 9" );
	HStreamIterator<int> ii( ss );
	int_array_t arr;
	arr.push_back( *ii );
	arr.push_back( *ii );
	++ ii;
	++ ii;
	++ ii;
	arr.push_back( *ii );
	arr.push_back( *ii );
	arr.push_back( *ii );
	ENSURE_EQUALS( "back_insert_iterator failed", arr, array( 5, 5, 1, 1, 1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HMoveIterator" )
	item_t::reset();
	array_t a;
	a.emplace_back( 1 );
	a.emplace_back( 2 );
	a.emplace_back( 3 );
	a.emplace_back( 4 );
	a.emplace_back( 5 );
	a.emplace_back( 6 );
	a.emplace_back( 7 );
	ENSURE_EQUALS( "preparation failed", item_t::get_copy_count(), 0 );
	item_t::reset();
	array_t n( make_move_iterator( a.begin() ), make_move_iterator( a.begin() + 5 ) );
	ENSURE_EQUALS( "preparation failed", item_t::get_copy_count(), 0 );
TUT_TEARDOWN()

}

