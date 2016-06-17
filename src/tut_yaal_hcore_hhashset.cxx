/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hhashset.cxx - this file is integral part of `tress' project.

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

#undef __DEPRECATED
#if defined( __GNUC__ ) && ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ <= 2 ) )
#include <ext/hash_set>
#else /* #if defined( __GNUC__ ) && ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ <= 2 ) ) */
#include <hash_set>
#endif /* #else #if defined( __GNUC__ ) && ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ <= 2 ) ) */

#include <TUT/tut.hpp>

#include <yaal/hcore/hhashset.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hhashset );
TUT_TEST_GROUP( tut_yaal_hcore_hhashset, "yaal::hcore::HHashSet" );

}

namespace yaal {
namespace hcore {
template<>
int long hash<tress::tut_helpers::HInstanceTracker<tut_yaal_hcore_hhashset>>::operator () ( tress::tut_helpers::HInstanceTracker<tut_yaal_hcore_hhashset> const& key_ ) const {
	return ( key_.id() );
}
}
}

namespace tut {

TUT_UNIT_TEST( "default constructor" )
	typedef HHashSet<int> hashset_t;
	hashset_t set;
	ENSURE_EQUALS( "bad size on fresh HSet<>", set.size(), 0 );
	ENSURE( "bad emptinass status on fresh HSet<>", set.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert (unique)" )
	typedef HHashSet<int> hashset_t;
	hashset_t set;
	ENSURE_EQUALS( "bad size on fresh HSet<>", set.size(), 0 );
	ENSURE( "bad emptinass status on fresh HSet<>", set.is_empty() );
	set.insert( 1 );
	ENSURE_EQUALS( "bad size on HSet<> after insert", set.size(), 1 );
	ENSURE_NOT( "bad emptinass status on HSet<> after insert", set.is_empty() );
	ENSURE_EQUALS( "inserted element not found", set.count( 1 ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert (non-unique)" )
	typedef HHashSet<int> hashset_t;
	hashset_t set;
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

TUT_UNIT_TEST( "insert - copy count" )
	typedef HHashSet<item_t> hashset_t;
	/* from lvalue */ {
		item_t::reset();
		hashset_t s;
		item_t i( 1 );
		s.insert( i );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 0 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert - move count" )
	typedef HHashSet<item_t> hashset_t;
	/* from lvalue */ {
		item_t::reset();
		hashset_t s;
		item_t i( 1 );
		s.insert( yaal::move( i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
	/* from rvalue */ {
		item_t::reset();
		hashset_t s;
		s.insert( 1 );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()


TUT_UNIT_TEST( "iteration" )
	typedef HHashSet<int> hashset_t;
	hashset_t set;
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 2 );
	set.insert( 3 );
	set.insert( 3 );
	HArray<hashset_t::value_type> forward( set.begin(), set.end() );
	HArray<hashset_t::value_type> backward( set.rbegin(), set.rend() );
	reverse( backward.begin(), backward.end() );
	ENSURE_EQUALS( "bad teration", backward, forward );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sample data" )
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
	int long LOOPS( 1000000 ); {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.insert( static_cast<int>( i ) );
		clog << "*speed* std::hash_set<>::insert() = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	} {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			hashset.insert( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HHashSet<>::insert() = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	clog << "*speed* HHashSet<>::insert() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	typedef HHashSet<int, HHashSet<int>::hasher_type, HHashSet<int>::equal_key_type, allocator::pool<int> > hashset_on_pool_type;
	hashset_on_pool_type hashSetOnPool; {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			hashSetOnPool.insert( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HHashSet<on_pool>::insert() = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	clog << "*speed* HHashSet<on_pool>::insert() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
TUT_TEARDOWN()

}

