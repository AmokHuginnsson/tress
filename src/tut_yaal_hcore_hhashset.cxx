/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <unordered_set>

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
	yaal::reverse( backward.begin(), backward.end() );
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

TUT_UNIT_TEST( "compare equals" )
	typedef HHashSet<HString> hashset_t;
	typedef HArray<HString> string_array_t;
	hashset_t a;
	int const dataSize( 64 );
	for ( int i( 0 ); i < dataSize; ++ i ) {
		a.insert( i );
	}
	hashset_t b;
	for ( int i( dataSize - 1 ); i >= 0; -- i ) {
		b.insert( i );
	}
	string_array_t ia( a.begin(), a.end() );
	string_array_t ib( b.begin(), b.end() );
	ENSURE_NOT( "test preparation failed", ia == ib );
	ENSURE_EQUALS( "compare equals operator failed", a, b );
	a.insert( "Ala" );
	ENSURE_NOT( "compare equals operator failed", a == b );
	b.insert( "Ola" );
	ENSURE( "compare equals operator failed", a != b );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "speed test" )
	TIME_CONSTRAINT_EXEMPT();
	typedef std::unordered_set<int> proto_t;
	typedef HHashSet<int> hashset_type;
	proto_t proto;
	hashset_type hashset;
	double long st( 0 );
	double long yt( 0 );
	int long LOOPS( 1000000 ); {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.insert( static_cast<int>( i ) );
		clog << "*speed* std::unordered_set<>::insert() = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
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

