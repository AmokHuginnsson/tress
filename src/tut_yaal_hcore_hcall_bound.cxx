/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcall_bound.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hcall_bound
	{
	typedef HInstanceTracker<tut_yaal_hcore_hcall_bound> item_t;
	virtual ~tut_yaal_hcore_hcall_bound( void ) {}
	void foo( void ) {}
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_hcall_bound, "yaal::hcore::HCall,bound" );

TUT_UNIT_TEST_N( 1, "Constructor." )
	HBoundCall<> c( call( &tut_yaal_hcore_hcall_bound::foo, this ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "compare with constant." )
	typedef HList<item_t> list_t;
	item_t a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ), call( &item_t::id, _1 ) < 50 );
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

}

