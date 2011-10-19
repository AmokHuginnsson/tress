/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hring.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hring.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hring );
TUT_TEST_GROUP( tut_yaal_tools_hring, "yaal::tools::HRing" );

TUT_UNIT_TEST( 2, "equals (==)" )
	ring_t r1;
	ring_t r2;
	ENSURE_EQUALS( "empty rings not equal", r1, r2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 47, "data test" )
	HRing<int> ring( ring::capacity( 3 ) );

	// Insert some elements into the buffer.
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 0 );
	ring.push_back( 1 );
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 1 );
	ring.push_back( 2 );
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 2 );
	ring.push_back( 3 );
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 3 );

	ENSURE_EQUALS( "push_back failed", ring[0], 1 );
	ENSURE_EQUALS( "push_back failed", ring[1], 2 );
	ENSURE_EQUALS( "push_back failed", ring[2], 3 );

	// The buffer is full now, pushing subsequent
	// elements will throw.

	try {
		ring.push_back( 4 );  // Overwrite 1 with 4.
		FAIL( "pushing into full ring succeeded" );
	} catch ( HException const& ) {
		/* ok */
	}

	ring.pop_front();
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 2 );
	ring.pop_front();
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 1 );

	ring.push_back( 4 ); // Overwrite 1 with 4
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 2 );
	ring.push_back( 5 ); // Overwrite 2 with 5.
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 3 );

	// The buffer now contains 3, 4 and 5.

	ENSURE_EQUALS( "push_back failed", ring[0], 3 );
	ENSURE_EQUALS( "push_back failed", ring[1], 4 );
	ENSURE_EQUALS( "push_back failed", ring[2], 5 );

	// Elements can be popped from either the front or the back.

	ring.pop_back();  // 5 is removed.
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 2 );
	ring.pop_front(); // 3 is removed.
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 1 );

	ENSURE_EQUALS( "pop_back and/or pop_front failed", ring[0], 4 );

	ring.clear();
	ENSURE_EQUALS( "inconsistent size", ring.get_size(), 0 );
	ENSURE_EQUALS( "clear failed", ring.is_empty(), true );

TUT_TEARDOWN()

TUT_UNIT_TEST( 48, "iterator" )
	HRing<int> ring( ring::capacity( 3 ) );
	ring.push_back( 1 );
	ring.push_back( 2 );
	ring.push_back( 3 );
	HRing<int>::iterator it( ring.begin() );
	ENSURE_EQUALS( "begin failed", *it, 1 );
	++ it;
	ENSURE_EQUALS( "iterator incrementationt failed", *it, 2 );
	++ it;
	ENSURE_EQUALS( "iterator incrementationt failed", *it, 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 49, "more data tests" )
	// create a circular container of capacity 3
	HRing<int> ring( ring::capacity( 3 ) );

	// insert some elements into the circular buffer
	ring.push_back( 1 );
	ring.push_back( 2 );

	// assertions
	ENSURE_EQUALS( "push_back failed", ring[0], 1 );
	ENSURE_EQUALS( "push_back failed", ring[1], 2 );
	ENSURE_EQUALS( "reserve/full failed", ring.full(), false );
	ENSURE_EQUALS( "size falsed", ring.size(), 2 );
	ENSURE_EQUALS( "reserve/capacity falsed", ring.capacity(), 3 );

	// insert some other elements
	ring.push_back( 3 );
	try {
		ring.push_back( 4 );
		fail( "pushing to full ring succeeded" );
	} catch ( HException const& ) {
		/* ok */
	}

	ENSURE_EQUALS( "full failed", ring.full(), true );
	ring.reserve( 5 );
	ring.push_back( 4 );
	ring.pop_front();

	// evaluate the sum
	int sum = accumulate( ring.begin(), ring.end(), 0 );

	// assertions
	ENSURE_EQUALS( "push/pop oper failed", ring[0], 2 );
	ENSURE_EQUALS( "push/pop oper failed", ring[1], 3 );
	ENSURE_EQUALS( "push/pop oper failed", ring[2], 4 );
	ENSURE_EQUALS( "begin/iter deref failed", *ring.begin(), 2 );
	ENSURE_EQUALS( "front failed", ring.front(), 2 );
	ENSURE_EQUALS( "back failed", ring.back(), 4 );
	ENSURE_EQUALS( "bad contents", sum, 9 );
	ENSURE_EQUALS( "full failed", ring.full(), false );
	ENSURE_EQUALS( "size failed", ring.size(), 3 );
	ENSURE_EQUALS( "capacity failed", ring.capacity(), 6 );
TUT_TEARDOWN()

}

