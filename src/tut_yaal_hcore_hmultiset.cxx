/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hmultiset.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hmultiset.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hmultiset );
TUT_TEST_GROUP( tut_yaal_hcore_hmultiset, "yaal::hcore::HMultiSet" );

TUT_UNIT_TEST( "default constructor" )
	typedef HMultiSet<int> mset_t;
	mset_t ms;
	ENSURE_EQUALS( "bad size on fresh HMultiSet<>", ms.size(), 0 );
	ENSURE( "bad emptinass status on fresh HMultiSet<>", ms.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "unique items" )
	typedef HMultiSet<int> mset_t;
	mset_t ms;
	ENSURE_EQUALS( "bad size on fresh HMultiSet<>", ms.size(), 0 );
	ENSURE( "bad emptinass status on fresh HMultiSet<>", ms.is_empty() );
	ms.insert( 1 );
	ENSURE_EQUALS( "bad size after 1 insert", ms.size(), 1 );
	ENSURE_NOT( "bad emptinass status insert", ms.is_empty() );
	ms.insert( 2 );
	ENSURE_EQUALS( "bad size after 2 inserts", ms.size(), 2 );
	ms.insert( 3 );
	ENSURE_EQUALS( "bad size after 3 inserts", ms.size(), 3 );
	ENSURE_EQUALS( "bad count of unique items 1", ms.count( 1 ), 1 );
	ENSURE_EQUALS( "bad count of unique items 2", ms.count( 2 ), 1 );
	ENSURE_EQUALS( "bad count of unique items 3", ms.count( 3 ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "non-unique items" )
	typedef HMultiSet<int> mset_t;
	mset_t ms;
	ENSURE_EQUALS( "bad size on fresh HMultiSet<>", ms.size(), 0 );
	ENSURE( "bad emptinass status on fresh HMultiSet<>", ms.is_empty() );
	ms.insert( 1 );
	ENSURE_EQUALS( "bad size after 1 insert", ms.size(), 1 );
	ENSURE_NOT( "bad emptinass status insert", ms.is_empty() );
	ms.insert( 2 );
	ENSURE_EQUALS( "bad size after 2 inserts", ms.size(), 2 );
	ms.insert( 3 );
	ENSURE_EQUALS( "bad size after 3 inserts", ms.size(), 3 );
	ENSURE_EQUALS( "bad count of unique items 1", ms.count( 1 ), 1 );
	ENSURE_EQUALS( "bad count of unique items 2", ms.count( 2 ), 1 );
	ENSURE_EQUALS( "bad count of unique items 3", ms.count( 3 ), 1 );

	ms.insert( 1 );
	ENSURE_EQUALS( "bad size after 4 insert (1st non unique)", ms.size(), 4 );
	ENSURE_NOT( "bad emptinass status insert", ms.is_empty() );
	ms.insert( 2 );
	ENSURE_EQUALS( "bad size after 5 inserts", ms.size(), 5 );
	ms.insert( 3 );
	ENSURE_EQUALS( "bad size after 6 inserts", ms.size(), 6 );
	ENSURE_EQUALS( "bad count of unique items 1", ms.count( 1 ), 2 );
	ENSURE_EQUALS( "bad count of unique items 2", ms.count( 2 ), 2 );
	ENSURE_EQUALS( "bad count of unique items 3", ms.count( 3 ), 2 );
	ms.insert( 2 );
	ENSURE_EQUALS( "bad size after 5 inserts", ms.size(), 7 );
	ms.insert( 3 );
	ENSURE_EQUALS( "bad size after 6 inserts", ms.size(), 8 );
	ENSURE_EQUALS( "bad count of unique items 1", ms.count( 1 ), 2 );
	ENSURE_EQUALS( "bad count of unique items 2", ms.count( 2 ), 3 );
	ENSURE_EQUALS( "bad count of unique items 3", ms.count( 3 ), 3 );
	ms.insert( 3 );
	ENSURE_EQUALS( "bad size after 6 inserts", ms.size(), 9 );
	ENSURE_EQUALS( "bad count of unique items 1", ms.count( 1 ), 2 );
	ENSURE_EQUALS( "bad count of unique items 2", ms.count( 2 ), 3 );
	ENSURE_EQUALS( "bad count of unique items 3", ms.count( 3 ), 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "forward iteration" )
	typedef HMultiSet<int> mset_t;
	mset_t ms;
	ms.insert( 1 );
	ms.insert( 2 );
	ms.insert( 3 );
	ms.insert( 1 );
	ms.insert( 2 );
	ms.insert( 3 );
	ms.insert( 2 );
	ms.insert( 3 );
	ms.insert( 3 );
	HStringStream ss;
	copy( ms.begin(), ms.end(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bad forward teration", ss.string(), "112223333" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "backward iteration" )
	typedef HMultiSet<int> mset_t;
	mset_t ms;
	ms.insert( 1 );
	ms.insert( 2 );
	ms.insert( 3 );
	ms.insert( 1 );
	ms.insert( 2 );
	ms.insert( 3 );
	ms.insert( 2 );
	ms.insert( 3 );
	ms.insert( 3 );
	HStringStream ss;
	copy( ms.rbegin(), ms.rend(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bad forward teration", ss.string(), "333322211" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sample data" )
	typedef HMultiSet<HString> string_multi_set_t;
	string_multi_set_t set;
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
	string_multi_set_t setCopy( set.begin(), set.end() );
	HStringStream ssSet;
	copy( set.begin(), set.end(), stream_iterator( ssSet ) );
	HStringStream ssCopy;
	copy( setCopy.begin(), setCopy.end(), stream_iterator( ssCopy ) );
	ENSURE_EQUALS( "copy through iters failed size", setCopy.size(), set.size() );
	ENSURE_EQUALS( "copy through iters failed data", ssCopy.string(), ssSet.string() );
TUT_TEARDOWN()

}

