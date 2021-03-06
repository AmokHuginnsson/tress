/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hhashmultiset.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace std {

template<typename key_t>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HHashMultiSet<key_t> const& ms ) {
	return ( container_dump( out, ms, "hash_multi_set" ) );
}

}

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hhashmultiset );
TUT_TEST_GROUP( tut_yaal_hcore_hhashmultiset, "yaal::hcore::HHashMultiSet" );

}

namespace yaal {
namespace hcore {
template<>
hash_value_t hash<tress::tut_helpers::HInstanceTracker<tut_yaal_hcore_hhashmultiset>>::operator () ( tress::tut_helpers::HInstanceTracker<tut_yaal_hcore_hhashmultiset> const& key_ ) const {
	return ( static_cast<hash_value_t>( key_.id() ) );
}
}
}

namespace tut {

TUT_UNIT_TEST( "default constructor" )
	typedef HHashMultiSet<int> mset_t;
	mset_t ms;
	ENSURE_EQUALS( "bad size on fresh HHashMultiSet<>", ms.size(), 0 );
	ENSURE( "bad emptinass status on fresh HHashMultiSet<>", ms.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert - copy count" )
	typedef HHashMultiSet<item_t> mset_t;
	/* from lvalue */ {
		item_t::reset();
		mset_t s;
		item_t i( 1 );
		s.insert( i );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert - move count" )
	typedef HHashMultiSet<item_t> mset_t;
	/* from lvalue */ {
		item_t::reset();
		mset_t s;
		item_t i( 1 );
		s.insert( yaal::move( i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
	/* from rvalue */ {
		item_t::reset();
		set_t s;
		s.insert( 1 );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "unique items" )
	typedef HHashMultiSet<int> mset_t;
	mset_t ms;
	ENSURE_EQUALS( "bad size on fresh HHashMultiSet<>", ms.size(), 0 );
	ENSURE( "bad emptinass status on fresh HHashMultiSet<>", ms.is_empty() );
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
	typedef HHashMultiSet<int> mset_t;
	mset_t ms;
	ENSURE_EQUALS( "bad size on fresh HHashMultiSet<>", ms.size(), 0 );
	ENSURE( "bad emptinass status on fresh HHashMultiSet<>", ms.is_empty() );
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

TUT_UNIT_TEST( "iteration" )
	typedef HHashMultiSet<int> mset_t;
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
	HArray<mset_t::value_type> forward( ms.begin(), ms.end() );
	HArray<mset_t::value_type> backward( ms.rbegin(), ms.rend() );
	reverse( backward.begin(), backward.end() );
	ENSURE_EQUALS( "bad teration", backward, forward );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sample data" )
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
	copy( set.begin(), set.end(), stream_iterator( clog ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "compare equals" )
	typedef HHashMultiSet<HString> string_hash_multi_set_t;
	typedef HArray<HString> string_array_t;
	string_hash_multi_set_t a;
	int const dataSize( 64 );
	for ( int i( 0 ); i < dataSize; ++ i ) {
		for ( int k( 0 ); k < ( ( i / 8 ) + 1 ); ++ k ) {
			a.insert( i );
		}
	}
	string_hash_multi_set_t b;
	for ( int i( dataSize - 1 ); i >= 0; -- i ) {
		for ( int k( 0 ); k < ( ( i / 8 ) + 1 ); ++ k ) {
			b.insert( i );
		}
	}
	string_array_t ia( a.begin(), a.end() );
	string_array_t ib( b.begin(), b.end() );
	ENSURE_NOT( "test preparation failed", ia == ib );
	ENSURE_EQUALS( "compare equals operator failed", a, b );
	a.insert( "Ala" );
	ENSURE_NOT( "compare equals operator failed", a == b );
	b.insert( "Ala" );
	ENSURE_EQUALS( "compare equals operator failed", a, b );
	a.insert( "Ala" );
	ENSURE_NOT( "compare equals operator failed", a == b );
	a.insert( "Ala" );
	b.insert( "Ala" );
	b.insert( "Ola" );
	ENSURE( "compare equals operator failed", a != b );
TUT_TEARDOWN()

}

