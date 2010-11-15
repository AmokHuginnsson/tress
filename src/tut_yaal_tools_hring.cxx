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

TUT_SIMPLE_MOCK( tut_yaal_tools_hring );
TUT_TEST_GROUP_N( tut_yaal_tools_hring, "yaal::tools::HRing" );

TUT_UNIT_TEST_N( 49, "data test" )
	HRing<int> ring( 3 );

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

	try
		{
		ring.push_back( 4 );  // Overwrite 1 with 4.
		FAIL( "pushing into full ring succeeded" );
		}
	catch ( HException const& )
		{
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

}

