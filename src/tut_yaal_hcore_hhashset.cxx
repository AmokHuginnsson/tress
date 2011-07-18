/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hhashset.cxx - this file is integral part of `tress' project.

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

#undef __DEPRECATED
#if defined( __GNUC__ ) && ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ <= 2 ) )
#include <ext/hash_set>
#else /* #if defined( __GNUC__ ) && ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ <= 2 ) ) */
#include <hash_set>
#endif /* #else #if defined( __GNUC__ ) && ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ <= 2 ) ) */

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

TUT_SIMPLE_MOCK( tut_yaal_hcore_hhashset );
TUT_TEST_GROUP( tut_yaal_hcore_hhashset, "yaal::hcore::HHashSet" );

TUT_UNIT_TEST( 49, "sample data" )
	typedef HHashSet<HString> string_hash_set_t;
	string_hash_set_t set;
	set.insert( "one" );
	set.insert( "two" );
	set.insert( "two" );
	set.insert( "three" );
	set.insert( "three" );
	set.insert( "three" );
	set.insert( "four" );
	set.insert( "five" );
	set.insert( "six" );
	set.insert( "seven" );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "one" ), 1 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "two" ), 1 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "three" ), 1 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "four" ), 1 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "five" ), 1 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "six" ), 1 );
	ENSURE_EQUALS( "failed to insert .insert() (data)", set.count( "seven" ), 1 );
	ENSURE_EQUALS( "failed to insert .insert() (size)", set.size(), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "speed test" )
	TIME_CONSTRAINT_EXEMPT();
	typedef stdext::hash_set<int> proto_t;
	typedef HHashSet<int> hashset_type;
	proto_t proto;
	hashset_type hashset;
	double long st( 0 );
	double long yt( 0 );
	int long LOOPS( 1000000 );
		{
		HClock c;
#ifdef __MSVCXX__
		LOOPS /= 10;
#endif /* #ifdef __MSVCXX__ */
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.insert( static_cast<int>( i ) );
		clog << "*speed* std::hash_set<>::insert() = " << static_cast<int long>( st = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			hashset.insert( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HHashSet<>::insert() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
	clog << "*speed* HHashSet<>::insert() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
TUT_TEARDOWN()

}

