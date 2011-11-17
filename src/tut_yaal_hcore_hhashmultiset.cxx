/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hhashmultiset.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hhashmultiset.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hhashmultiset );
TUT_TEST_GROUP( tut_yaal_hcore_hhashmultiset, "yaal::hcore::HHashMultiSet" );

TUT_UNIT_TEST( 50, "sample data" )
	typedef HHashMultiSet<HString> string_hash_multi_set_t;
	string_hash_multi_set_t set;
	set.insert( "one" );
	set.insert( "two" );
	set.insert( "two" );
	set.insert( "three" );
	set.insert( "three" );
	set.insert( "three" );
	set.insert( "four" );
	set.insert( "four" );
	set.insert( "four" );
	set.insert( "four" );
	set.insert( "five" );
	set.insert( "five" );
	set.insert( "five" );
	set.insert( "five" );
	set.insert( "five" );
	set.insert( "six" );
	set.insert( "six" );
	set.insert( "six" );
	set.insert( "six" );
	set.insert( "six" );
	set.insert( "six" );
	set.insert( "seven" );
	set.insert( "seven" );
	set.insert( "seven" );
	set.insert( "seven" );
	set.insert( "seven" );
	set.insert( "seven" );
	set.insert( "seven" );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "one" ), 1 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "two" ), 2 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "three" ), 3 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "four" ), 4 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "five" ), 5 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "six" ), 6 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "seven" ), 7 );
	ENSURE_EQUALS( "failed to insert .insert() (size)", set.size(), 1 + 2 + 3 + 4 + 5 + 6 + 7 );
	string_hash_multi_set_t setCopy( set.begin(), set.end() );
	set.resize( 30 );
	setCopy.resize( 30 );
	HStringStream ssSet;
	copy( set.begin(), set.end(), stream_iterator( ssSet ) );
	HStringStream ssCopy;
	copy( setCopy.begin(), setCopy.end(), stream_iterator( ssCopy ) );
	ENSURE_EQUALS( "copy through iters failed size", setCopy.size(), set.size() );
	ENSURE_EQUALS( "copy through iters failed data", ssCopy.string(), ssSet.string() );
	copy( set.begin(), set.end(), stream_iterator( cout ) );
TUT_TEARDOWN()

}

