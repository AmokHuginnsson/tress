/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hmultimap.cxx - this file is integral part of `tress' project.

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

#include "tut_helpers.hxx"
#include <yaal/tools/streamtools.hxx>
#include <TUT/tut.hpp>

#include <yaal/hcore/hmultimap.hxx>
M_VCSID( "$Id: " __ID__ " $" )

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hmultimap : public simple_mock<tut_yaal_hcore_hmultimap> {
	typedef simple_mock<tut_yaal_hcore_hmultimap> base_type;
	virtual ~tut_yaal_hcore_hmultimap( void ) {}
	typedef HMultiMap<int, int, HMultiMap<int, int>::compare_type, HMultiMap<int, int>::allocator_type, HMultiContainerStorage::HPacked> mmp_t;
	typedef HMultiMap<int, int, HMultiMap<int, int>::compare_type, HMultiMap<int, int>::allocator_type, HMultiContainerStorage::HTransparent> mmt_t;
	typedef HMultiMap<int, item_t, HMultiMap<int, item_t>::compare_type, HMultiMap<int, item_t>::allocator_type, HMultiContainerStorage::HPacked> mmp_item_t;
	typedef HMultiMap<int, item_t, HMultiMap<int, item_t>::compare_type, HMultiMap<int, item_t>::allocator_type, HMultiContainerStorage::HTransparent> mmt_item_t;
};

TUT_TEST_GROUP( tut_yaal_hcore_hmultimap, "yaal::hcore::HMultiMap" );

TUT_UNIT_TEST( "default constructor" )
	mmp_t mm;
	ENSURE_EQUALS( "bad size on fresh HMultiMap<>", mm.size(), 0 );
	ENSURE( "bad emptinass status on fresh HMultiMap<>", mm.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(transparent) insert - copy count" )
	/* from lvalue */ {
		item_t::reset();
		mmt_item_t m;
		item_t i( 1 );
		m.insert( make_pair<int const, item_t>( 1, i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(transparent) insert - move count" )
	/* from lvalue */ {
		item_t::reset();
		mmt_item_t m;
		item_t i( 1 );
		m.insert( make_pair<int const, item_t>( 1, yaal::move( i ) ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
	/* from rvalue */ {
		item_t::reset();
		mmt_item_t m;
		m.insert( make_pair( 1, 1 ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(packed) insert - copy count" )
	/* from lvalue */ {
		item_t::reset();
		mmp_item_t m;
		item_t i( 1 );
		m.insert( make_pair<int const, item_t>( 1, i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(packed) insert - move count" )
	/* from lvalue */ {
		item_t::reset();
		mmp_item_t m;
		item_t i( 1 );
		m.insert( make_pair<int const, item_t>( 1, yaal::move( i ) ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
	/* from rvalue */ {
		item_t::reset();
		mmp_item_t m;
		m.insert( make_pair( 1, 1 ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(transparent) push_back - copy count" )
	/* from lvalue */ {
		item_t::reset();
		mmt_item_t m;
		item_t i( 1 );
		m.push_back( make_pair<int const, item_t>( 1, i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(transparent) push_back - move count" )
	/* from lvalue */ {
		item_t::reset();
		mmt_item_t m;
		item_t i( 1 );
		m.push_back( make_pair<int const, item_t>( 1, yaal::move( i ) ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
	/* from rvalue */ {
		item_t::reset();
		mmt_item_t m;
		m.push_back( make_pair( 1, 1 ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(packed) push_back - copy count" )
	/* from lvalue */ {
		item_t::reset();
		mmp_item_t m;
		item_t i( 1 );
		m.push_back( make_pair<int const, item_t>( 1, i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(packed) push_back - move count" )
	/* from lvalue */ {
		item_t::reset();
		mmp_item_t m;
		item_t i( 1 );
		m.push_back( make_pair<int const, item_t>( 1, yaal::move( i ) ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
	/* from rvalue */ {
		item_t::reset();
		mmp_item_t m;
		m.push_back( make_pair( 1, 1 ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(transparent) push_front - copy count" )
	/* from lvalue */ {
		item_t::reset();
		mmt_item_t m;
		item_t i( 1 );
		m.push_front( make_pair<int const, item_t>( 1, i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(transparent) push_front - move count" )
	/* from lvalue */ {
		item_t::reset();
		mmt_item_t m;
		item_t i( 1 );
		m.push_front( make_pair<int const, item_t>( 1, yaal::move( i ) ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
	/* from rvalue */ {
		item_t::reset();
		mmt_item_t m;
		m.push_front( make_pair( 1, 1 ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(packed) push_front - copy count" )
	/* from lvalue */ {
		item_t::reset();
		mmp_item_t m;
		item_t i( 1 );
		m.push_front( make_pair<int const, item_t>( 1, i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "(packed) push_front - move count" )
	/* from lvalue */ {
		item_t::reset();
		mmp_item_t m;
		item_t i( 1 );
		m.push_front( make_pair<int const, item_t>( 1, yaal::move( i ) ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
	/* from rvalue */ {
		item_t::reset();
		mmp_item_t m;
		m.push_front( make_pair( 1, 1 ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "unique items" )
	mmp_t mm;
	ENSURE_EQUALS( "bad size on fresh HMultiMap<>", mm.size(), 0 );
	ENSURE( "bad emptinass status on fresh HMultiMap<>", mm.is_empty() );
	mm.insert( make_pair( 1, 1 ) );
	ENSURE_EQUALS( "bad size after 1 insert", mm.size(), 1 );
	ENSURE_NOT( "bad emptinass status insert", mm.is_empty() );
	mm.insert( make_pair( 2, 2 ) );
	ENSURE_EQUALS( "bad size after 2 inserts", mm.size(), 2 );
	mm.insert( make_pair( 3, 3 ) );
	ENSURE_EQUALS( "bad size after 3 inserts", mm.size(), 3 );
	ENSURE_EQUALS( "bad count of unique items 1", mm.count( 1 ), 1 );
	ENSURE_EQUALS( "bad count of unique items 2", mm.count( 2 ), 1 );
	ENSURE_EQUALS( "bad count of unique items 3", mm.count( 3 ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "non-unique items" )
	mmp_t mm;
	ENSURE_EQUALS( "bad size on fresh HMultiMap<>", mm.size(), 0 );
	ENSURE( "bad emptinass status on fresh HMultiMap<>", mm.is_empty() );
	mm.insert( make_pair( 1, 1 ) );
	ENSURE_EQUALS( "bad size after 1 insert", mm.size(), 1 );
	ENSURE_NOT( "bad emptinass status insert", mm.is_empty() );
	mm.insert( make_pair( 2, 2 ) );
	ENSURE_EQUALS( "bad size after 2 inserts", mm.size(), 2 );
	mm.insert( make_pair( 3, 3 ) );
	ENSURE_EQUALS( "bad size after 3 inserts", mm.size(), 3 );
	ENSURE_EQUALS( "bad count of unique items 1", mm.count( 1 ), 1 );
	ENSURE_EQUALS( "bad count of unique items 2", mm.count( 2 ), 1 );
	ENSURE_EQUALS( "bad count of unique items 3", mm.count( 3 ), 1 );

	mm.insert( make_pair( 1, 4 ) );
	ENSURE_EQUALS( "bad size after 4 insert (1st non unique)", mm.size(), 4 );
	ENSURE_NOT( "bad emptinass status insert", mm.is_empty() );
	mm.insert( make_pair( 2, 5 ) );
	ENSURE_EQUALS( "bad size after 5 inserts", mm.size(), 5 );
	mm.insert( make_pair( 3, 6 ) );
	ENSURE_EQUALS( "bad size after 6 inserts", mm.size(), 6 );
	ENSURE_EQUALS( "bad count of unique items 1", mm.count( 1 ), 2 );
	ENSURE_EQUALS( "bad count of unique items 2", mm.count( 2 ), 2 );
	ENSURE_EQUALS( "bad count of unique items 3", mm.count( 3 ), 2 );
	mm.insert( make_pair( 2, 7 ) );
	ENSURE_EQUALS( "bad size after 5 inserts", mm.size(), 7 );
	mm.insert( make_pair( 3, 8 ) );
	ENSURE_EQUALS( "bad size after 6 inserts", mm.size(), 8 );
	ENSURE_EQUALS( "bad count of unique items 1", mm.count( 1 ), 2 );
	ENSURE_EQUALS( "bad count of unique items 2", mm.count( 2 ), 3 );
	ENSURE_EQUALS( "bad count of unique items 3", mm.count( 3 ), 3 );
	mm.insert( make_pair( 3, 9 ) );
	ENSURE_EQUALS( "bad size after 6 inserts", mm.size(), 9 );
	ENSURE_EQUALS( "bad count of unique items 1", mm.count( 1 ), 2 );
	ENSURE_EQUALS( "bad count of unique items 2", mm.count( 2 ), 3 );
	ENSURE_EQUALS( "bad count of unique items 3", mm.count( 3 ), 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "forward iteration" )
	mmp_t mm;
	mm.insert( make_pair( 1, 1 ) );
	mm.insert( make_pair( 2, 2 ) );
	mm.insert( make_pair( 3, 3 ) );
	mm.insert( make_pair( 1, 4 ) );
	mm.insert( make_pair( 2, 5 ) );
	mm.insert( make_pair( 3, 6 ) );
	mm.insert( make_pair( 2, 7 ) );
	mm.insert( make_pair( 3, 8 ) );
	mm.insert( make_pair( 3, 9 ) );
	HStringStream ss;
	copy( mm.begin(), mm.end(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bad forward teration", ss.string(), "pair<1,1>pair<1,4>pair<2,2>pair<2,5>pair<2,7>pair<3,3>pair<3,6>pair<3,8>pair<3,9>" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "backward iteration" )
	mmt_t mm;
	mm.insert( make_pair( 1, 1 ) );
	mm.insert( make_pair( 2, 2 ) );
	mm.insert( make_pair( 3, 3 ) );
	mm.insert( make_pair( 1, 4 ) );
	mm.insert( make_pair( 2, 5 ) );
	mm.insert( make_pair( 3, 6 ) );
	mm.insert( make_pair( 2, 7 ) );
	mm.insert( make_pair( 3, 8 ) );
	mm.insert( make_pair( 3, 9 ) );
	HStringStream ss;
	copy( mm.rbegin(), mm.rend(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bad forward teration", ss.string(), "pair<3,9>pair<3,8>pair<3,6>pair<3,3>pair<2,7>pair<2,5>pair<2,2>pair<1,4>pair<1,1>" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find/upper_bound on non existing (packed)" )
	mmp_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mm.insert( make_pair( 1, 3 ) );
	mm.insert( make_pair( 3, 4 ) );
	mm.insert( make_pair( 3, 5 ) );
	mmp_t const& m = mm;
	ENSURE( "find() false positive", ! ( m.find( 2 ) != m.end() ) );
	ENSURE( "upper_bound() failed", m.upper_bound( 2 ) == m.find( 3 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find/upper_bound on existing (packed)" )
	mmp_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mm.insert( make_pair( 1, 3 ) );
	mm.insert( make_pair( 2, 7 ) );
	mm.insert( make_pair( 2, 8 ) );
	mm.insert( make_pair( 3, 4 ) );
	mm.insert( make_pair( 3, 5 ) );
	int acc = 0;
	for ( mmp_t::const_iterator it = mm.find( 2 ), end = mm.upper_bound( 2 ); it != end; ++ it )
		acc += (*it).second;
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", acc, 15 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modify packed by iterator" )
	mmp_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mmp_t::iterator it = mm.begin();
	int const VERIFY = 0;
	(*it).second = VERIFY;
	mmp_t::iterator it_ver = mm.begin();
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", (*it_ver).second, VERIFY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find/upper_bound on non existing" )
	mmt_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mm.insert( make_pair( 1, 3 ) );
	mm.insert( make_pair( 3, 4 ) );
	mm.insert( make_pair( 3, 5 ) );
	mmt_t const& m = mm;
	ENSURE( "find() false positive", ! ( m.find( 2 ) != m.end() ) );
	ENSURE( "upper_bound() failed", m.upper_bound( 2 ) == m.find( 3 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find/upper_bound on existing" )
	mmt_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mm.insert( make_pair( 1, 3 ) );
	mm.insert( make_pair( 2, 7 ) );
	mm.insert( make_pair( 2, 8 ) );
	mm.insert( make_pair( 3, 4 ) );
	mm.insert( make_pair( 3, 5 ) );
	int acc = 0;
	for ( mmt_t::const_iterator it = mm.find( 2 ), end = mm.upper_bound( 2 ); it != end; ++ it )
		acc += (*it).second;
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", acc, 15 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modify transparent by iterator and operator*" )
	mmt_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mmt_t::iterator it = mm.begin();
	int const VERIFY = 0;
	(*it).second = VERIFY;
	mmt_t::iterator it_ver = mm.begin();
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", (*it_ver).second, VERIFY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modify transparent by iterator and operator->" )
	mmt_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mmt_t::iterator it = mm.begin();
	int const VERIFY = 0;
	it->second = VERIFY;
	mmt_t::iterator it_ver = mm.begin();
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", (*it_ver).second, VERIFY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sample data" )
	typedef HMultiMap<HString, int> string_to_int_hmultimap_t;
	string_to_int_hmultimap_t map;
	map.insert( make_pair<HString>( "one", 1 ) );
	map.insert( make_pair<HString>( "two", 2 ) );
	map.insert( make_pair<HString>( "two", 2 ) );
	map.insert( make_pair<HString>( "three", 3 ) );
	map.insert( make_pair<HString>( "three", 3 ) );
	map.insert( make_pair<HString>( "three", 3 ) );
	map.insert( make_pair<HString>( "four", 4 ) );
	map.insert( make_pair<HString>( "four", 4 ) );
	map.insert( make_pair<HString>( "four", 4 ) );
	map.insert( make_pair<HString>( "four", 4 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "one" ), 1 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "one" )->second, 1 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "two" ), 2 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "two" )->second, 2 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "three" ), 3 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "three" )->second, 3 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "four" ), 4 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "four" )->second, 4 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "five" ), 5 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "five" )->second, 5 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "six" ), 6 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "six" )->second, 6 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "seven" ), 7 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "seven" )->second, 7 );
	ENSURE_EQUALS( "failed to insert insert (size)", map.size(), 1 + 2 + 3 + 4 + 5 + 6 + 7 );
TUT_TEARDOWN()

}

