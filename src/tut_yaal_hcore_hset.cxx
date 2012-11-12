/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hset.cxx - this file is integral part of `tress' project.

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

#include <set>

#include <TUT/tut.hpp>

#include <yaal/hcore/hset.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hset : simple_mock<tut_yaal_hcore_hset> {
	typedef simple_mock<tut_yaal_hcore_hset> base_type;
	virtual ~tut_yaal_hcore_hset( void ) {}
	void lower_bound_test( int );
	void upper_bound_test( int );
};

TUT_TEST_GROUP( tut_yaal_hcore_hset, "yaal::hcore::HSet" );

TUT_UNIT_TEST( 1, "default constructor" )
	int_set_t set;
	ENSURE_EQUALS( "bad size on fresh HSet<>", set.size(), 0 );
	ENSURE( "bad emptinass status on fresh HSet<>", set.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "insert (unique)" )
	int_set_t set;
	ENSURE_EQUALS( "bad size on fresh HSet<>", set.size(), 0 );
	ENSURE( "bad emptinass status on fresh HSet<>", set.is_empty() );
	set.insert( 1 );
	ENSURE_EQUALS( "bad size on HSet<> after insert", set.size(), 1 );
	ENSURE_NOT( "bad emptinass status on HSet<> after insert", set.is_empty() );
	ENSURE_EQUALS( "inserted element not found", set.count( 1 ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "insert (non-unique)" )
	int_set_t set;
	ENSURE_EQUALS( "bad size on fresh HSet<>", set.size(), 0 );
	ENSURE( "bad emptinass status on fresh HSet<>", set.is_empty() );
	set.insert( 1 );
	ENSURE_EQUALS( "bad size on HSet<> after insert", set.size(), 1 );
	ENSURE_NOT( "bad emptinass status on HSet<> after insert", set.is_empty() );
	ENSURE_EQUALS( "inserted element not found", set.count( 1 ), 1 );
	ENSURE_NOT( "non-unique insertion succeeded", set.insert( 1 ).second );
	ENSURE_EQUALS( "bad size on HSet<> after insert", set.size(), 1 );
	ENSURE_NOT( "bad emptinass status on HSet<> after insert", set.is_empty() );
	ENSURE_EQUALS( "inserted element not found", set.count( 1 ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "find()" )
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

void tut_yaal_hcore_hset::lower_bound_test( int size_ ) {
	int_set_t set;
	for ( int i( 0 ); i < size_; i += 2 )
		set.insert( i );
	for ( int i( 0 ); i < ( size_ - 1 ); ++i ) {
		int_set_t::const_iterator it( set.lower_bound( i ) );
		ENSURE( "lower_bound not found", it != set.end() );
		ENSURE_EQUALS( "lower_bound failed", *it, ( i % 2 ) ? i + 1 : i );
	}
	set.clear();
	for ( int i( size_ - 2 ); i >= 0; i -= 2 )
		set.insert( i );
	for ( int i( 0 ); i < ( size_ - 1 ); ++i ) {
		int_set_t::const_iterator it( set.lower_bound( i ) );
		ENSURE( "lower_bound not found", it != set.end() );
		ENSURE_EQUALS( "lower_bound failed", *it, ( i % 2 ) ? i + 1 : i );
	}
}

void tut_yaal_hcore_hset::upper_bound_test( int size_ ) {
	int_set_t set;
	for ( int i( 0 ); i < size_; i += 2 )
		set.insert( i );
	for ( int i( 0 ); i < ( size_ - 2 ); ++i ) {
		int_set_t::const_iterator it( set.upper_bound( i ) );
		ENSURE( "upper_bound not found", it != set.end() );
		ENSURE_EQUALS( "upper_bound failed", *it, ( i % 2 ) ? i + 1 : i + 2 );
	}
	int_set_t::const_iterator end( set.upper_bound( *set.rbegin() ) );
	ENSURE( "upper_bound found", !( end != set.end() ) );
	set.clear();
	for ( int i( size_ - 2 ); i >= 0; i -= 2 )
		set.insert( i );
	for ( int i( 0 ); i < ( size_ - 2 ); ++i ) {
		int_set_t::const_iterator it( set.upper_bound( i ) );
		ENSURE( "upper_bound not found", it != set.end() );
		ENSURE_EQUALS( "upper_bound failed", *it, ( i % 2 ) ? i + 1 : i + 2 );
	}
	int_set_t::const_iterator end2( set.upper_bound( *set.rbegin() ) );
	ENSURE( "upper_bound found", !( end2 != set.end() ) );
}

TUT_UNIT_TEST( 5, "lower_bound()" )
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

TUT_UNIT_TEST( 6, "upper_bound()" )
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

TUT_UNIT_TEST( 7, "forward iteration" )
	int_set_t set;
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 3 );
	HStringStream ss;
	copy( set.begin(), set.end(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bad forward teration", ss.string(), "123" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "backward iteration" )
	int_set_t set;
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 3 );
	HStringStream ss;
	copy( set.rbegin(), set.rend(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bad forward teration", ss.string(), "321" );
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
	proto_t proto;
	set_type set;
	double long st( 0 );
	double long yt( 0 );
	int long LOOPS( 500000 ); {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.insert( static_cast<int>( i ) );
		clog << "*speed* std::set<>::insert() = " << static_cast<int long>( st = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	} {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			set.insert( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HSet<>::insert() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	}
	clog << "*speed* HSet<>::insert() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	typedef HSet<int, HSet<int>::compare_type, allocator::pool<int> > set_on_pool_type;
	set_on_pool_type setOnPool; {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			setOnPool.insert( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HSet<on_pool>::insert() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	}
	clog << "*speed* HSet<on_pool>::insert() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
TUT_TEARDOWN()

}

