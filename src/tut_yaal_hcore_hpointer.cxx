/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal_hcore_hpointer
	{
	class counter
		{
		static int f_iCounter;
		static int f_iSerialNoIterator;
		int f_iSerialNo;
	public:
		counter ( void ) : f_iSerialNo ( f_iSerialNoIterator ++ )
			{
			f_iCounter ++;
			}
		~counter ( void )
			{
			f_iCounter --;
			}
		static int get_count ( void )
			{
			return ( f_iCounter );
			}
		static void set_count ( int a_iCounter )
			{
			f_iCounter = a_iCounter;
			}
		void foo ( void )
			{
			cout << "do_foo(" << f_iSerialNo << ")" << endl;
			}
		int get_serial_no ( void )
			{
			return ( f_iSerialNo );
			}
		};
	tut_yaal_hcore_hpointer ( void )
		{
		counter::set_count ( 0 );
		}
	};

int tut_yaal_hcore_hpointer::counter::f_iCounter = 0;
int tut_yaal_hcore_hpointer::counter::f_iSerialNoIterator = 0;

typedef test_group < tut_yaal_hcore_hpointer > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hpointer_group ( "yaal::hcore::HPointer" );

typedef HPointer<tut_yaal_hcore_hpointer::counter, HPointerScalar, HPointerRelaxed> ptr_t;

/* Default constructor. */
template < >
template < >
void module::test<1> ( void )
	{
	ptr_t ptr;
	ensure_equals ( "failed to invoke destructor", ptr.raw(), static_cast<counter*>( 0  ) );
	}

/* Constructor. */
template < >
template < >
void module::test<2> ( void )
	{
		{
		counter* p = NULL;
		ptr_t ptr ( p = new counter ( ) );
		ensure_equals( "smart pointer does not hold proper raw pointer", ptr.raw(), p );
		ptr->foo ( );
		}
	ensure_equals ( "failed to invoke destructor", counter::get_count ( ), 0 );
	}

/* Copy constructor. */
template < >
template < >
void module::test<3> ( void )
	{
		{
		counter* p = NULL;
		ptr_t ptr = ptr_t ( p = new counter ( ) );
		ensure_equals( "smart pointer does not hold proper raw pointer", ptr.raw(), p );
		ptr->foo ( );
		}
	ensure_equals ( "failed to invoke destructor", counter::get_count ( ), 0 );
	}

/* Assign operator. */
template < >
template < >
void module::test<4> ( void )
	{
		{
		counter* p = NULL;
		ptr_t sp1 = ptr_t ( new counter ( ) );
		ptr_t sp2 = ptr_t ( p = new counter ( ) );
		sp1->foo ( );
		sp2->foo ( );
		sp1 = sp2;
		ensure_equals ( "failed to invoke destructor", counter::get_count ( ), 1 );
		ensure_equals ( "failed to assign pointer", sp1->get_serial_no ( ), sp2->get_serial_no ( ) );
		ensure_equals ( "failed to assign pointer", sp1.raw(), p );
		sp1->foo ( );
		}
	ensure_equals ( "failed to invoke destructor", counter::get_count ( ), 0 );
	}

/**
 * Checks constructor with another ptr_t with no module.
 */
template<>
template<>
void module::test<5>()
	{
	ptr_t sp1;
	ensure_equals( "counter::get_count: 0", counter::get_count(), 0 );
	ptr_t sp2( sp1 );
	ensure_equals( "counter::get_count: 0", counter::get_count(), 0 );
	ensure_equals( "counter::get_count: 0", counter::get_count(), 0 );
	ensure( sp2.raw() == 0 );
	}

/**
 * Checks constructor with another ptr_t with module.
 */
template<>
template<>
void module::test<6>()
	{
		{
		counter* p = new counter();
		ptr_t sp1(p);
		ptr_t sp2(sp1);
		ensure_equals( "get", sp1.raw(), p );
		ensure_equals( "get", sp2.raw(), p );
		ensure_equals( "cnt", counter::get_count(), 1 );
		}
	// ptr left scope
	ensure_equals( "destructed", counter::get_count(), 0 );
	}

// =================================================
// Assignment operators
// =================================================

/**
 * Checks assignment with non-null module.
 */
template<>
template<>
void module::test<7>()
	{
	counter* p = new counter();
	ptr_t sp( p );
	ensure("get", sp.raw() == p);
	ensure("cnt", counter::get_count() == 1);
	}

/**
 * Checks assignment with ptr_t with non-null module.
 */
template<>
template<>
void module::test<8>()
	{
		{
		counter* p = NULL;
		ptr_t sp1( p = new counter() );
		ptr_t sp2;
		sp2 = sp1;
		ensure_equals( "get", sp1.raw(), p );
		ensure_equals( "get", sp2.raw(), p );
		ensure_equals( "cnt", counter::get_count(), 1 );
		}
	ensure_equals( "destructed", counter::get_count(), 0 );
	}

/**
 * Checks assignment with itself.
 */
template<>
template<>
void module::test<9>()
	{
	ptr_t sp1( new counter() );
	sp1 = sp1;
	ensure("get", sp1.raw() != 0);
	ensure("cnt", counter::get_count() == 1);
	ensure_equals( "not destructed", counter::get_count(), 1 );
	}


// =================================================
// Passing ownership
// =================================================

/**
 * Checks passing ownership via assignment.
 */
template<>
template<>
void module::test<10>()
	{
	counter *p1 = NULL, *p2 = NULL;
	ptr_t sp1( p1 = new counter());
	ptr_t sp2( p2 = new counter());
	ensure_equals( "create 1", sp1->get_serial_no(), p1->get_serial_no() );
	ensure_equals( "create 2", sp2->get_serial_no(), p2->get_serial_no() );
	ensure_equals( "cnt=2", counter::get_count(), 2 );

	sp1 = sp2;
	ensure_equals( "create 2", sp1->get_serial_no(), p2->get_serial_no() );
	ensure_equals("cnt=1", counter::get_count(), 1 );
	}

/**
 * Checks operator -&gt; throws instead of returning null.
 */
template<>
template<>
void module::test<11>()
	{
	try
		{
		ptr_t sp;
		sp->get_serial_no();
		fail("exception expected");
		}
	catch (const int&)
		{
		// ok
		}
	}

/**
 * assign smart pointers pointing to the same memory.
 */
template<>
template<>
void module::test<12>()
	{
	ptr_t sp1( new counter() );
	ptr_t sp2 = sp1;
	sp2 = sp1;
	}

}

