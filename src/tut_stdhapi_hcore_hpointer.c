/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.c - this file is integral part of `tress' project.

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

#include "header"
M_CVSID ( "$CVSHeader$" )

using namespace tut;
using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

namespace tut
{

struct tut_stdhapi_hcore_hpointer
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
	tut_stdhapi_hcore_hpointer ( void )
		{
		counter::set_count ( 0 );
		}
	};

int tut_stdhapi_hcore_hpointer::counter::f_iCounter = 0;
int tut_stdhapi_hcore_hpointer::counter::f_iSerialNoIterator = 0;

typedef test_group < tut_stdhapi_hcore_hpointer > tut_group;
typedef tut_group::object module;
tut_group tut_stdhapi_hcore_hpointer_group ( "stdhapi::hcore::HPointer" );

/* Constructor. */
template < >
template < >
void module::test<1> ( void )
	{
		{
		HPointer<counter, HPointerScalar, HPointerRelaxed> ptr ( new counter ( ) );
		ptr->foo ( );
		}
	ensure_equals ( "failed to invoke destructor", counter::get_count ( ), 0 );
	}

/* Copy constructor. */
template < >
template < >
void module::test<2> ( void )
	{
		{
		HPointer<counter, HPointerScalar, HPointerRelaxed> ptr = HPointer<counter, HPointerScalar, HPointerRelaxed> ( new counter ( ) );
		ptr->foo ( );
		}
	ensure_equals ( "failed to invoke destructor", counter::get_count ( ), 0 );
	}

/* Assign operator. */
template < >
template < >
void module::test<3> ( void )
	{
		{
		HPointer<counter, HPointerScalar, HPointerRelaxed> ptr1 = HPointer<counter, HPointerScalar, HPointerRelaxed> ( new counter ( ) );
		HPointer<counter, HPointerScalar, HPointerRelaxed> ptr2 = HPointer<counter, HPointerScalar, HPointerRelaxed> ( new counter ( ) );
		ptr1->foo ( );
		ptr2->foo ( );
		ptr1 = ptr2;
		ensure_equals ( "failed to invoke destructor", counter::get_count ( ), 1 );
		ensure_equals ( "failed to assign pointer", ptr1->get_serial_no ( ), ptr2->get_serial_no ( ) );
		ptr1->foo ( );
		}
	ensure_equals ( "failed to invoke destructor", counter::get_count ( ), 0 );
	}

}
