/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hresource.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hresource.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hresource : public simple_mock<tut_yaal_hcore_hresource> {
	typedef simple_mock<tut_yaal_hcore_hresource> base_type;
	tut_yaal_hcore_hresource( void )
		: base_type() {
		item_t::set_instance_count( 0 );
	}
	virtual ~tut_yaal_hcore_hresource( void )
		{}
};

typedef HResource<tut_yaal_hcore_hresource::item_t> ptr_t;

TUT_TEST_GROUP( tut_yaal_hcore_hresource, "yaal::hcore::HResource" );

TUT_UNIT_TEST( "default constructor" )
	ptr_t c;
	ENSURE_EQUALS( "dirty default initialized resurce holder", c.get(), static_cast<item_t*>( NULL ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "freeing the new allocated object" ) {
		item_t* p = new item_t();
		ptr_t ptr( p );
		ENSURE_EQUALS( "smart pointer does not hold proper get pointer", ptr.get(), p );
		clog << ptr->to_string() << endl;
	}
	ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Copy constructor." ) {
		item_t* p = NULL;
		ptr_t ptr = ptr_t( p = new item_t() );
		ENSURE_EQUALS( "smart pointer does not hold proper get pointer", ptr.get(), p );
		clog << ptr->to_string() << endl;
	}
	ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Assign operator." ) {
		item_t* p = NULL;
		ptr_t sp1 = ptr_t( new item_t() );
		ptr_t sp2 = ptr_t( p = new item_t() );
		ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 2 );
		clog << sp1->to_string() << endl;
		clog << sp2->to_string() << endl;
		sp1 = yaal::move( sp2 );
		ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "failed to pass pointer", sp2.get(), static_cast<item_t*>( NULL ) );
		ENSURE_EQUALS( "failed to assign pointer", sp1.get(), p );
		clog << sp1->to_string() << endl;
	}
	ENSURE_EQUALS( "failed to invoke destructor", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Checks constructor with another ptr_t with no module." ) {
		ptr_t sp1;
		ENSURE_EQUALS( "item_t::get_instance_count: 0", item_t::get_instance_count(), 0 );
		ptr_t sp2( yaal::move( sp1 ) );
		ENSURE_EQUALS( "item_t::get_instance_count: 0", item_t::get_instance_count(), 0 );
		ENSURE_EQUALS( "item_t::get_instance_count: 0", item_t::get_instance_count(), 0 );
		ENSURE( sp2.get() == 0 );
	}
	ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Checks constructor with another ptr_t with module." ) {
		item_t* p = new item_t();
		ptr_t sp1( p );
		ENSURE_EQUALS( "get", sp1.get(), p );
		ptr_t sp2( yaal::move( sp1 ) );
		ENSURE_EQUALS( "get", sp1.get(), static_cast<item_t*>( NULL ) );
		ENSURE_EQUALS( "get", sp2.get(), p );
		ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 1 );
	}
	// ptr left scope
	ENSURE_EQUALS( "destructed", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

// =================================================
// Assignment operators
// =================================================

TUT_UNIT_TEST( "Checks assignment with non-null module." ) {
		item_t* p = new item_t();
		ptr_t sp( p );
		ENSURE("get", sp.get() == p);
		ENSURE_EQUALS("leak !!!", item_t::get_instance_count(), 1);
	}
	ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Checks assignment with ptr_t with non-null module." ) {
		item_t* p = NULL;
		ptr_t sp1( p = new item_t() );
		ENSURE_EQUALS( "get", sp1.get(), p );
		ptr_t sp2;
		sp2 = yaal::move( sp1 );
		ENSURE_EQUALS( "get", sp1.get(), static_cast<item_t*>( NULL ) );
		ENSURE_EQUALS( "get", sp2.get(), p );
		ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 1 );
	}
	ENSURE_EQUALS( "destructed", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Checks assignment with itself." ) {
		ptr_t sp1( new item_t() );
		sp1 = yaal::move( sp1 );
		ENSURE( "get", sp1.get() != 0 );
		ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "not destructed", item_t::get_instance_count(), 1 );
	}
	ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()


// =================================================
// Passing ownership
// =================================================

TUT_UNIT_TEST( "Checks passing ownership via assignment." ) {
		item_t *p1 = NULL, *p2 = NULL;
		ptr_t sp1( p1 = new item_t( 1 ));
		ptr_t sp2( p2 = new item_t( 2 ));
		ENSURE_EQUALS( "create 1", sp1->get_id(), p1->get_id() );
		ENSURE_EQUALS( "create 2", sp2->get_id(), p2->get_id() );
		ENSURE_EQUALS( "leak !!!=2", item_t::get_instance_count(), 2 );

		sp1 = yaal::move( sp2 );
		ENSURE_EQUALS( "create 2", sp1->get_id(), p2->get_id() );
		ENSURE_EQUALS( "leak !!!=1", item_t::get_instance_count(), 1 );
	}
	ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Checks operator -> throws instead of returning null." ) {
		ptr_t sp;
		ENSURE_THROW( "failed assertion expected", sp->get_id(), HFailedAssertion );
	}
	ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assign smart pointers pointing to the same memory." ) {
		ptr_t sp1( new item_t() );
		ptr_t sp2 = yaal::move( sp1 );
		sp2 = yaal::move( sp1 );
	}
	ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sizeof ( HResource<> )" )
	ENSURE_EQUALS( "sizeof ( HResource<> ) != sizeof ( auto_ptr<> )", sizeof ( HResource<item_t> ), sizeof ( void* ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "array" ) {
		typedef HResource<item_t[]> arr_t;
		arr_t arr( new item_t[5] );
		ENSURE_EQUALS( "construction failed???", item_t::get_instance_count(), 5 );
	}
	ENSURE_EQUALS( "leak !!!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

}

