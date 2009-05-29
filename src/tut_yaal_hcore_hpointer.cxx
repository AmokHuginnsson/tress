/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hpointer.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hpointer
	{
	typedef counter<int, tut_yaal_hcore_hpointer> counter_t;
	tut_yaal_hcore_hpointer( void )
		{
		counter_t::set_instance_count( 0 );
		}
	virtual ~tut_yaal_hcore_hpointer( void )
		{}

	struct Base
		{
		int _tab[0x100];
		Base( void )
			{	cout << __PRETTY_FUNCTION__ << ": " << this << endl;	}
		virtual ~Base( void )
			{	cout << __PRETTY_FUNCTION__ << ": " << this << endl;	}
		virtual int foo( char const* const by )
			{
			cout << __PRETTY_FUNCTION__ << ": " << this << ", by: " << by << endl;
			return ( -1 );
			}
		};

	struct A : virtual public Base
		{
		int _one;
		A ( int one ) : _one ( one )
			{	cout << __PRETTY_FUNCTION__ << ": " << brightblue << this << lightgray << ", " << _one << endl;	}
		virtual ~A ( void )
			{	cout << __PRETTY_FUNCTION__ << ": " << brightblue << this << lightgray <<  ", " << _one << endl;	}
		void bar( char const* const by )
			{ cout << __PRETTY_FUNCTION__ << ": " << brightblue << this << lightgray << ", " << _one << ", by: " << by << endl; }
		virtual int foo( char const* const by )
			{
			cout << __PRETTY_FUNCTION__ << ": " << brightblue << this << lightgray << ", " << _one << ", by: " << by << endl;
			return ( _one );
			}
		};

	struct X
		{
		int long _quality;
		int long _quality1;
		int long _quality2;
		int long _quality3;
		int long _quality4;
		int long _quality5;
		int long _quality6;
		int long _quality7;
		int long _quality8;
		X( void )
			: _quality( 0 ), _quality1( -1 ), _quality2( -2 ), _quality3( -3 ),
			_quality4( -4 ), _quality5( -5 ), _quality6( -6 ), _quality7( -7 ),
			_quality8( -8 )
			{ cout << __PRETTY_FUNCTION__ << ": " << yellow << this << lightgray << endl; }
		virtual ~X ( void )
			{ cout << __PRETTY_FUNCTION__ << ": " << yellow << this << lightgray << endl; }
		virtual int foo( char const* const by )
			{
			cout << __PRETTY_FUNCTION__ << ": " << yellow << this << lightgray << ", by: " << by << endl;
			return ( 0 );
			}
		};

	struct E : public X, public A
		{
		HString _four;
		E ( int one, HString const& four ) : A( one ), _four ( four )
			{ cout << __PRETTY_FUNCTION__ << ": " << brightred << this << lightgray << ", " << _four << endl; }
		virtual ~E ( void )
			{ cout << __PRETTY_FUNCTION__ << ": " << brightred << this << lightgray << ", " << _four << endl; }
		virtual int foo( char const* const by )
			{
			cout << __PRETTY_FUNCTION__ << ": " << brightred << this << lightgray << ", " << _four << ", by: " << by << endl;
			return ( _one );
			}
		};

	typedef HPointer<Base> sp_base_t;
	typedef HPointer<A> sp_a_t;
	typedef HPointer<E> sp_e_t;
	};

typedef test_group < tut_yaal_hcore_hpointer > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hpointer_group ( "yaal::hcore::HPointer" );

typedef HPointer<tut_yaal_hcore_hpointer::counter_t> ptr_t;

TUT_UNIT_TEST_N( 1, "/* Default constructor. */" )
	ptr_t ptr;
	ensure_equals ( "failed to invoke destructor", ptr.raw(), static_cast<counter_t*>( NULL ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Constructor. */" )
		{
		counter_t* p = NULL;
		ptr_t ptr( p = new counter_t() );
		ensure_equals( "smart pointer does not hold proper raw pointer", ptr.raw(), p );
		ptr->foo();
		}
	ensure_equals ( "failed to invoke destructor", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* Copy constructor. */" )
		{
		counter_t* p = NULL;
		ptr_t ptr = ptr_t( p = new counter_t() );
		ensure_equals( "smart pointer does not hold proper raw pointer", ptr.raw(), p );
		ptr->foo();
		}
	ensure_equals( "failed to invoke destructor", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Assign operator. */" )
		{
		counter_t* p = NULL;
		ptr_t sp1 = ptr_t( new counter_t() );
		ptr_t sp2 = ptr_t( p = new counter_t() );
		sp1->foo();
		sp2->foo();
		sp1 = sp2;
		ensure_equals( "failed to invoke destructor", counter_t::get_instance_count(), 1 );
		ensure_equals( "failed to assign pointer", sp1->get_symbol(), sp2->get_symbol() );
		ensure_equals( "failed to assign pointer", sp1.raw(), p );
		sp1->foo();
		}
	ensure_equals( "failed to invoke destructor", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Checks constructor with another ptr_t with no module. */" )
		{
		ptr_t sp1;
		ensure_equals( "counter_t::get_instance_count: 0", counter_t::get_instance_count(), 0 );
		ptr_t sp2( sp1 );
		ensure_equals( "counter_t::get_instance_count: 0", counter_t::get_instance_count(), 0 );
		ensure_equals( "counter_t::get_instance_count: 0", counter_t::get_instance_count(), 0 );
		ensure( sp2.raw() == 0 );
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Checks constructor with another ptr_t with module. */" )
		{
		counter_t* p = new counter_t();
		ptr_t sp1(p);
		ptr_t sp2(sp1);
		ensure_equals( "get", sp1.raw(), p );
		ensure_equals( "get", sp2.raw(), p );
		ensure_equals( "leak !!!", counter_t::get_instance_count(), 1 );
		}
	// ptr left scope
	ensure_equals( "destructed", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

// =================================================
// Assignment operators
// =================================================

TUT_UNIT_TEST_N( 7, "/* Checks assignment with non-null module. */" )
		{
		counter_t* p = new counter_t();
		ptr_t sp( p );
		ensure("get", sp.raw() == p);
		ensure("leak !!!", counter_t::get_instance_count() == 1);
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* Checks assignment with ptr_t with non-null module. */" )
		{
		counter_t* p = NULL;
		ptr_t sp1( p = new counter_t() );
		ptr_t sp2;
		sp2 = sp1;
		ensure_equals( "get", sp1.raw(), p );
		ensure_equals( "get", sp2.raw(), p );
		ensure_equals( "leak !!!", counter_t::get_instance_count(), 1 );
		}
	ensure_equals( "destructed", counter_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* Checks assignment with itself. */" )
		{
		ptr_t sp1( new counter_t() );
		sp1 = sp1;
		ensure( "get", sp1.raw() != 0 );
		ensure( "leak !!!", counter_t::get_instance_count() == 1 );
		ensure_equals( "not destructed", counter_t::get_instance_count(), 1 );
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()


// =================================================
// Passing ownership
// =================================================

TUT_UNIT_TEST_N( 10, "/* Checks passing ownership via assignment. */" )
		{
		counter_t *p1 = NULL, *p2 = NULL;
		ptr_t sp1( p1 = new counter_t( 1 ));
		ptr_t sp2( p2 = new counter_t( 2 ));
		ensure_equals( "create 1", sp1->get_symbol(), p1->get_symbol() );
		ensure_equals( "create 2", sp2->get_symbol(), p2->get_symbol() );
		ensure_equals( "leak !!!=2", counter_t::get_instance_count(), 2 );

		sp1 = sp2;
		ensure_equals( "create 2", sp1->get_symbol(), p2->get_symbol() );
		ensure_equals( "leak !!!=1", counter_t::get_instance_count(), 1 );
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* Checks operator -&gt; throws instead of returning null. */" )
		{
		try
			{
			ptr_t sp;
			sp->get_symbol();
			fail( "failed assertion expected" );
			}
		catch ( HFailedAssertion& )
			{
			// ok
			}
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* assign smart pointers pointing to the same memory. */" )
		{
		ptr_t sp1( new counter_t() );
		ptr_t sp2 = sp1;
		sp2 = sp1;
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

/* Weak pointer related tests. */
typedef HPointer<tut_yaal_hcore_hpointer::counter_t, HPointerScalar, HPointerWeak> weak_t;

TUT_UNIT_TEST_N( 13, "/* default constructor */" )
		{
		weak_t w;
		ptr_t p( w );
		ensure( "bad default constructor", p.raw() == NULL );
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "/* copy constructor */" )
		{
		ptr_t p( new counter_t() );
		weak_t w( p );
		ensure( "bad copy constructor", p.raw() != NULL );
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 15, "/* accessing nullified weak */" )
		{
		weak_t w;
			{
			ptr_t p( new counter_t() );
			w = p;
			ensure( "weak could not pass ownership", w == p );
			ptr_t o( w );
			ensure( "weak could not pass ownership", o == p );
			}
		ptr_t a( w );
		ensure( "weak performed forbidden operation", a.raw() == NULL );
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

struct ODummy : public HPointerFromThisInterface<ODummy>
	{
	};

typedef HPointer<ODummy> ftp_t;

TUT_UNIT_TEST_N( 16, "/* from this */" )
	ODummy* raw = NULL;
	ftp_t p( raw = new ODummy );
	ftp_t o( raw->get_pointer() );
	ensure( "from this failed", p == o );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 17, "/* hierarchy issues */" )
		{
		static int const MY_VAL = 2;
		A* rpa = NULL;
		E* rpe = NULL;
		sp_a_t spa( rpa = new A( 1 ) );
		sp_e_t spe( rpe = new E( MY_VAL, "2" ) );
		rpa = rpe;
		spa = spe;
		A*a = spe.raw();
		E*e = spe.raw();
		M_ASSERT( a == rpa );
		M_ASSERT( e == rpe );
		rpa->A::foo( "rpa->A::foo" );
		rpa->foo( "rpa->foo" );
		rpe->A::foo( "rpe->A::foo" );
		rpe->foo( "rpe->foo" );
		rpa->A::bar( "rpa->A::bar" );
		rpa->bar( "rpa->bar" );
		rpe->A::bar( "rpe->A::bar" );
		rpe->bar( "rpe->bar" );
		a->A::foo( "a->A::foo" );
		a->foo( "a->foo" );
		spa->A::foo( "spa->A::foo" );
		spa->foo( "spa->foo" );
		ensure_equals( "hierarchy problem", spa->A::foo( "ensure" ), MY_VAL );
		e->A::foo( "e->A::foo" );
		e->E::foo( "e->E::foo" );
		e->foo( "e->foo" );
		spe->A::foo( "spe->A::foo" );
		spe->E::foo( "spe->E::foo" );
		spe->foo( "spe->foo" );
		a->bar( "a->bar" );
		a->A::bar( "a->A::bar" );
		spa->bar( "spa->bar" );
		spa->A::bar( "spa->A::bar" );
		e->A::bar( "e->A::bar" );
		e->bar( "e->bar" );
		spe->A::bar( "spe->A::bar" );
		spe->bar( "spe->bar" );
		}
TUT_TEARDOWN()

#pragma GCC diagnostic ignored "-Weffc++"

struct non_virt_dtor
	{
	~non_virt_dtor( void ) {};
	};

struct NVDDerive : public non_virt_dtor
	{
	tut_yaal_hcore_hpointer::counter_t _counter;
	~NVDDerive( void ) {};
	};

TUT_UNIT_TEST_N( 18, "non virtual destructor" )
	typedef HPointer<non_virt_dtor> p_t;
		{
		p_t p( new NVDDerive );
		}
	ensure( "leak !!!", counter_t::get_instance_count() == 0 );
TUT_TEARDOWN()

}

