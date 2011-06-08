/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hset.cxx - this file is integral part of `tress' project.

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

#include <set>

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

struct tut_yaal_hcore_hset : simple_mock<tut_yaal_hcore_hset>
	{
	virtual ~tut_yaal_hcore_hset( void ) {}
	void lower_bound_test( int );
	void upper_bound_test( int );
	};

TUT_TEST_GROUP( tut_yaal_hcore_hset, "yaal::hcore::HSet" );

TUT_UNIT_TEST( 1, "find()" )
	int_set_t set;
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 4 );
	set.insert( 5 );
	int_set_t::const_iterator it( set.find( 3 ) );
	ENSURE( "find with false positive", ! ( it != set.end() ) );
	set.insert( 3 );
	it = set.find( 3 );
	ENSURE( "find with false negative", it != set.end() );
	ENSURE_EQUALS( "find failed", *it, 3 );
TUT_TEARDOWN()

void tut_yaal_hcore_hset::lower_bound_test( int size_ )
	{
	int_set_t set;
	for ( int i( 0 ); i < size_; i += 2 )
		set.insert( i );
	for ( int i( 0 ); i < ( size_ - 1 ); ++i )
		{
		int_set_t::const_iterator it( set.lower_bound( i ) );
		ENSURE( "lower_bound not found", it != set.end() );
		ENSURE_EQUALS( "lower_bound failed", *it, ( i % 2 ) ? i + 1 : i );
		}
	set.clear();
	for ( int i( size_ - 2 ); i >= 0; i -= 2 )
		set.insert( i );
	for ( int i( 0 ); i < ( size_ - 1 ); ++i )
		{
		int_set_t::const_iterator it( set.lower_bound( i ) );
		ENSURE( "lower_bound not found", it != set.end() );
		ENSURE_EQUALS( "lower_bound failed", *it, ( i % 2 ) ? i + 1 : i );
		}
	}

void tut_yaal_hcore_hset::upper_bound_test( int size_ )
	{
	int_set_t set;
	for ( int i( 0 ); i < size_; i += 2 )
		set.insert( i );
	for ( int i( 0 ); i < ( size_ - 2 ); ++i )
		{
		int_set_t::const_iterator it( set.upper_bound( i ) );
		ENSURE( "upper_bound not found", it != set.end() );
		ENSURE_EQUALS( "upper_bound failed", *it, ( i % 2 ) ? i + 1 : i + 2 );
		}
	int_set_t::const_iterator end( set.upper_bound( *set.rbegin() ) );
	ENSURE( "upper_bound found", !( end != set.end() ) );
	set.clear();
	for ( int i( size_ - 2 ); i >= 0; i -= 2 )
		set.insert( i );
	for ( int i( 0 ); i < ( size_ - 2 ); ++i )
		{
		int_set_t::const_iterator it( set.upper_bound( i ) );
		ENSURE( "upper_bound not found", it != set.end() );
		ENSURE_EQUALS( "upper_bound failed", *it, ( i % 2 ) ? i + 1 : i + 2 );
		}
	int_set_t::const_iterator end2( set.upper_bound( *set.rbegin() ) );
	ENSURE( "upper_bound found", !( end2 != set.end() ) );
	}

TUT_UNIT_TEST( 2, "lower_bound()" )
	int_set_t set;
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 4 );
	set.insert( 5 );
	int_set_t::const_iterator it( set.lower_bound( 3 ) );
	ENSURE( "lower_bound not found", it != set.end() );
	ENSURE_EQUALS( "lower_bound failed", *it, 4 );
	set.insert( 3 );
	it = set.lower_bound( 3 );
	ENSURE( "lower_bound not found", it != set.end() );
	ENSURE_EQUALS( "lower_bound failed", *it, 3 );

/* Let's be serious. */
	static int const RANGE( 1024 );
	for ( int i( 0 ); i < RANGE; i += 2 )
		lower_bound_test( i );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "upper_bound()" )
	int_set_t set;
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 4 );
	set.insert( 5 );
	int_set_t::const_iterator it( set.upper_bound( 3 ) );
	ENSURE( "upper_bound not found", it != set.end() );
	ENSURE_EQUALS( "upper_bound failed", *it, 4 );
	set.insert( 3 );
	it = set.upper_bound( 3 );
	ENSURE( "upper_bound not found", it != set.end() );
	ENSURE_EQUALS( "upper_bound failed", *it, 4 );

/* Let's be serious. */
	static int const RANGE( 1024 );
	for ( int i( 2 ); i < RANGE; i += 2 )
		upper_bound_test( i );
TUT_TEARDOWN()

TUT_UNIT_TEST( 49, "sample data" )
	typedef HSet<HString> string_set_t;
	string_set_t set;
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
	typedef std::set<int> proto_t;
	typedef HSet<int> set_type;
	int long LOOPS( 500000 );
		{
		proto_t proto;
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.insert( static_cast<int>( i ) );
		clog << "*speed* std::set<>::insert() = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
		}
		{
		set_type set;
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			set.insert( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HSet<>::insert() = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
		}
TUT_TEARDOWN()

}

