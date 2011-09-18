/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_huniquemovable.cxx - this file is integral part of `tress' project.

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
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_huniquemovable : public simple_mock<tut_yaal_hcore_huniquemovable> {
	virtual ~tut_yaal_hcore_huniquemovable( void ) {}
	typedef HUniqueMovable<item_t> um_t;
};

TUT_TEST_GROUP( tut_yaal_hcore_huniquemovable, "yaal::hcore::HUniqueMovable" );

TUT_UNIT_TEST( 1, "constructor with no parameters" ) {
		um_t um;
		ENSURE_EQUALS( "bad constructor called", (*um).id(), 0 );
		ENSURE_EQUALS( "bad constructor called", um->id(), 0 );
		ENSURE_EQUALS( "inconsistent instance count", item_t::get_instance_count(), 1 );
	}
	ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "constructor with parameters" ) {
		um_t um( 7 );
		ENSURE_EQUALS( "bad constructor called", (*um).id(), 7 );
		ENSURE_EQUALS( "bad constructor called", um->id(), 7 );
		ENSURE_EQUALS( "inconsistent instance count", item_t::get_instance_count(), 1 );
	}
	ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "copy constructor" ) {
		um_t um( 7 );
		ENSURE_EQUALS( "bad constructor called", um->id(), 7 );
		ENSURE_EQUALS( "inconsistent instance count", item_t::get_instance_count(), 1 );
		um_t copy( um );
		ENSURE_EQUALS( "bad constructor called", copy->id(), 7 );
		ENSURE_EQUALS( "inconsistent instance count", item_t::get_instance_count(), 1 );
		try {
			um->id();
			FAIL( "accessing invalidated HUniqueMovable<> succeeded" );
		} catch ( HFailedAssertion const& ) {
			// ok
		}
	}
	ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "assignment operator" ) {
		um_t um( 7 );
		ENSURE_EQUALS( "bad constructor called", um->id(), 7 );
		ENSURE_EQUALS( "inconsistent instance count", item_t::get_instance_count(), 1 );
		um_t copy( 13 );
		ENSURE_EQUALS( "bad constructor called", copy->id(), 13 );
		ENSURE_EQUALS( "inconsistent instance count", item_t::get_instance_count(), 2 );
		copy = um;
		ENSURE_EQUALS( "inconsistent instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad constructor called", copy->id(), 7 );
		try {
			um->id();
			FAIL( "accessing invalidated HUniqueMovable<> succeeded" );
		} catch ( HFailedAssertion const& ) {
			// ok
		}
	}
	ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

}

