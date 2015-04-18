/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_iterator.cxx - this file is integral part of `tress' project.

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

