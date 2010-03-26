/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hresource.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hresource
	{
	typedef HInstanceTracker<tut_yaal_hcore_hresource> counter_t;
	tut_yaal_hcore_hresource( void )
		{
		counter_t::set_instance_count( 0 );
		}
	virtual ~tut_yaal_hcore_hresource( void )
		{}
	};

typedef HResource<tut_yaal_hcore_hresource::counter_t> ptr_t;

TUT_TEST_GROUP_N( tut_yaal_hcore_hresource, "yaal::hcore::HResource" );

TUT_UNIT_TEST_N( 1, "default constructor" )
	ptr_t c;
	ENSURE_EQUALS( "dirty default initialized resurce holder", c.get(), static_cast<counter_t*>( NULL ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "freeing the new allocated object" )
		{
		counter_t* p = NULL;
		ptr_t ptr( p = new counter_t() );
		ENSURE_EQUALS( "smart pointer does not hold proper get pointer", ptr.get(), p );
		cout << ptr->to_string() << endl;
		}
	ENSURE_EQUALS( "failed to invoke destructor", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* Copy constructor. */" )
		{
		counter_t* p = NULL;
		ptr_t ptr = ptr_t( p = new counter_t() );
		ENSURE_EQUALS( "smart pointer does not hold proper get pointer", ptr.get(), p );
		cout << ptr->to_string() << endl;
		}
	ENSURE_EQUALS( "failed to invoke destructor", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Assign operator. */" )
		{
		counter_t* p = NULL;
		ptr_t sp1 = ptr_t( new counter_t() );
		ptr_t sp2 = ptr_t( p = new counter_t() );
		ENSURE_EQUALS( "failed to invoke destructor", counter_t::get_instance_count(), 2 );
		cout << sp1->to_string() << endl;
		cout << sp2->to_string() << endl;
		sp1 = sp2;
		ENSURE_EQUALS( "failed to invoke destructor", counter_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "failed to pass pointer", sp2.get(), static_cast<counter_t*>( NULL ) );
		ENSURE_EQUALS( "failed to assign pointer", sp1.get(), p );
		cout << sp1->to_string() << endl;
		}
	ENSURE_EQUALS( "failed to invoke destructor", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Checks constructor with another ptr_t with no module. */" )
		{
		ptr_t sp1;
		ENSURE_EQUALS( "counter_t::get_instance_count: 0", counter_t::get_instance_count(), 0 );
		ptr_t sp2( sp1 );
		ENSURE_EQUALS( "counter_t::get_instance_count: 0", counter_t::get_instance_count(), 0 );
		ENSURE_EQUALS( "counter_t::get_instance_count: 0", counter_t::get_instance_count(), 0 );
		ENSURE( sp2.get() == 0 );
		}
	ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Checks constructor with another ptr_t with module. */" )
		{
		counter_t* p = new counter_t();
		ptr_t sp1(p);
		ENSURE_EQUALS( "get", sp1.get(), p );
		ptr_t sp2(sp1);
		ENSURE_EQUALS( "get", sp1.get(), static_cast<counter_t*>( NULL ) );
		ENSURE_EQUALS( "get", sp2.get(), p );
		ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 1 );
		}
	// ptr left scope
	ENSURE_EQUALS( "destructed", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

// =================================================
// Assignment operators
// =================================================

TUT_UNIT_TEST_N( 7, "/* Checks assignment with non-null module. */" )
		{
		counter_t* p = new counter_t();
		ptr_t sp( p );
		ENSURE("get", sp.get() == p);
		ENSURE_EQUALS("leak !!!", counter_t::get_instance_count(), 1);
		}
	ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* Checks assignment with ptr_t with non-null module. */" )
		{
		counter_t* p = NULL;
		ptr_t sp1( p = new counter_t() );
		ENSURE_EQUALS( "get", sp1.get(), p );
		ptr_t sp2;
		sp2 = sp1;
		ENSURE_EQUALS( "get", sp1.get(), static_cast<counter_t*>( NULL ) );
		ENSURE_EQUALS( "get", sp2.get(), p );
		ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 1 );
		}
	ENSURE_EQUALS( "destructed", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* Checks assignment with itself. */" )
		{
		ptr_t sp1( new counter_t() );
		sp1 = sp1;
		ENSURE( "get", sp1.get() != 0 );
		ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "not destructed", counter_t::get_instance_count(), 1 );
		}
	ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()


// =================================================
// Passing ownership
// =================================================

TUT_UNIT_TEST_N( 10, "/* Checks passing ownership via assignment. */" )
		{
		counter_t *p1 = NULL, *p2 = NULL;
		ptr_t sp1( p1 = new counter_t( 1 ));
		ptr_t sp2( p2 = new counter_t( 2 ));
		ENSURE_EQUALS( "create 1", sp1->get_id(), p1->get_id() );
		ENSURE_EQUALS( "create 2", sp2->get_id(), p2->get_id() );
		ENSURE_EQUALS( "leak !!!=2", counter_t::get_instance_count(), 2 );

		sp1 = sp2;
		ENSURE_EQUALS( "create 2", sp1->get_id(), p2->get_id() );
		ENSURE_EQUALS( "leak !!!=1", counter_t::get_instance_count(), 1 );
		}
	ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* Checks operator -> throws instead of returning null. */" )
		{
		try
			{
			ptr_t sp;
			sp->get_id();
			FAIL( "failed assertion expected" );
			}
		catch ( HFailedAssertion& )
			{
			// ok
			}
		}
	ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* assign smart pointers pointing to the same memory. */" )
		{
		ptr_t sp1( new counter_t() );
		ptr_t sp2 = sp1;
		sp2 = sp1;
		}
	ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

#pragma GCC diagnostic ignored "-Weffc++"

struct non_virt_dtor
	{
	~non_virt_dtor( void ) {};
	};

struct NVDDerive : public non_virt_dtor
	{
	tut_yaal_hcore_hresource::counter_t _counter;
	~NVDDerive( void ) {};
	};

TUT_UNIT_TEST_N( 13, "non virtual destructor" )
	typedef HResource<non_virt_dtor> p_t;
		{
		p_t p( new NVDDerive );
		}
	ENSURE_EQUALS( "leak !!!", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

}

