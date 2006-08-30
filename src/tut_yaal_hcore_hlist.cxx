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

struct tut_yaal_hcore_hlist
	{
	};

typedef test_group < tut_yaal_hcore_hlist > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hlist_group ( "yaal::hcore::HList" );

/* Simple constructor. */
template < >
template < >
void module::test<1> ( void )
	{
	HList < int > l_oList;
	ensure_equals ( "list not empty", l_oList.quantity ( ), 0 );
	}

/* Parametrized constructor. */
template < >
template < >
void module::test<2> ( void )
	{
	HList < int > l_oList ( 3 );
	ensure_equals ( "list not empty", l_oList.quantity ( ), 3 );
	}

/* poor forward iterator while syntax */
template < >
template < >
void module::test<3> ( void )
	{
	int l_iCtr = 0;
	HList < int > l_oList;
	int * l_piVal = NULL;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	l_piVal = & l_oList.go ( 0 );
	while ( l_piVal )
		{
		l_iCtr ++;
		ensure_equals ( "while syntax: forward iterator made wrong move", * l_piVal, l_iCtr );
		l_piVal = l_oList.to_tail ( 1, HList < int >::D_TREAT_AS_OPENED );
		}
	ensure_equals ( "while syntax: not the whole list was iterated", l_iCtr, 5 );
	}

/* poor forward iterator for syntax */
template < >
template < >
void module::test<4> ( void )
	{
	int l_iCtr = 0;
	HList < int > l_oList;
	int * l_piVal = NULL;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	for ( l_piVal = & l_oList.go ( 0 );
			l_piVal; l_piVal = l_oList.to_tail ( 1, HList < int >::D_TREAT_AS_OPENED ) )
		{
		l_iCtr ++;
		ensure_equals ( "for syntax: forward iterator made wrong move", * l_piVal, l_iCtr );
		}
	ensure_equals ( "for syntax: not the whole list was iterated", l_iCtr, 5 );
	}

/* poor backward iterator while syntax */
template < >
template < >
void module::test<5> ( void )
	{
	int l_iCtr = 5;
	HList < int > l_oList;
	int * l_piVal = NULL;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	l_piVal = & l_oList.go ( - 1 );
	while ( l_piVal )
		{
		ensure_equals ( "while syntax: backward iterator made wrong move", * l_piVal, l_iCtr );
		l_iCtr --;
		l_piVal = l_oList.to_head ( 1, HList < int >::D_TREAT_AS_OPENED );
		}
	ensure_equals ( "while syntax: not the whole list was iterated", l_iCtr, 0 );
	}

/* poor backward iterator for syntax */
template < >
template < >
void module::test<6> ( void )
	{
	int l_iCtr = 5;
	HList < int > l_oList;
	int * l_piVal = NULL;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	for ( l_piVal = & l_oList.go ( - 1 );
			l_piVal; l_piVal = l_oList.to_head ( 1, HList < int >::D_TREAT_AS_OPENED ) )
		{
		ensure_equals ( "for syntax: backward iterator made wrong move", * l_piVal, l_iCtr );
		l_iCtr --;
		}
	ensure_equals ( "for syntax: not the whole list was iterated", l_iCtr, 0 );
	}

/* assignation operator (full to empty) */
template < >
template < >
void module::test<7> ( void )
	{
	int l_iCtr = 0;
	HList < int > l_oList;
	HList < int > l_oAnother;
	int * l_piVal = NULL;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	l_oAnother = l_oList;
	for ( l_piVal = & l_oAnother.go ( 0 );
			l_piVal; l_piVal = l_oAnother.to_tail ( 1, HList < int >::D_TREAT_AS_OPENED ) )
		{
		l_iCtr ++;
		ensure_equals ( "assign operation failed, wrong value", * l_piVal, l_iCtr );
		}
	ensure_equals ( "assign operation failed, wrong size", l_iCtr, 5 );
	}

/* assignation operator (empty to full) */
template < >
template < >
void module::test<8> ( void )
	{
	HList < int > l_oList;
	HList < int > l_oAnother;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	l_oList = l_oAnother;
	ensure_equals ( "assign operation failed, wrong size", l_oList.quantity ( ), 0 );
	}

/* assignation operator (full to small) */
template < >
template < >
void module::test<9> ( void )
	{
	int l_iCtr = 0;
	HList < int > l_oList;
	HList < int > l_oAnother;
	int * l_piVal = NULL;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	l_oAnother.add_tail ( ) = 6;
	l_oAnother.add_tail ( ) = 7;
	l_oAnother.add_tail ( ) = 8;
	l_oAnother = l_oList;
	for ( l_piVal = & l_oAnother.go ( 0 );
			l_piVal; l_piVal = l_oAnother.to_tail ( 1, HList < int >::D_TREAT_AS_OPENED ) )
		{
		l_iCtr ++;
		ensure_equals ( "assign operation failed, wrong value", * l_piVal, l_iCtr );
		}
	ensure_equals ( "assign operation failed, wrong size", l_iCtr, 5 );
	}

/* assignation operator (full to big) */
template < >
template < >
void module::test<10> ( void )
	{
	int l_iCtr = 0;
	HList < int > l_oList;
	HList < int > l_oAnother;
	int * l_piVal = NULL;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	l_oAnother.add_tail ( ) = 6;
	l_oAnother.add_tail ( ) = 7;
	l_oAnother.add_tail ( ) = 8;
	l_oAnother.add_tail ( ) = 9;
	l_oAnother.add_tail ( ) = 10;
	l_oAnother.add_tail ( ) = 11;
	l_oAnother.add_tail ( ) = 12;
	l_oAnother = l_oList;
	for ( l_piVal = & l_oAnother.go ( 0 );
			l_piVal; l_piVal = l_oAnother.to_tail ( 1, HList < int >::D_TREAT_AS_OPENED ) )
		{
		l_iCtr ++;
		ensure_equals ( "assign operation failed, wrong value", * l_piVal, l_iCtr );
		}
	ensure_equals ( "assign operation failed, wrong size", l_iCtr, 5 );
	}

/* remove element */
template < >
template < >
void module::test<11> ( void )
	{
	bool re = false;
	int * l_piVal = NULL;
	cout << endl;
	for ( int i = 1; i < 6; i ++ )
		{
		HList < int > l_oList;
		l_oList.add_tail ( ) = 1;
		l_oList.add_tail ( ) = 2;
		l_oList.add_tail ( ) = 3;
		l_oList.add_tail ( ) = 4;
		l_oList.add_tail ( ) = 5;
		for ( l_piVal = & l_oList.go ( - 1 );
				l_piVal; l_piVal = l_oList.to_head ( 1, HList < int >::D_TREAT_AS_OPENED ) )
			{
			while ( 1 )
				{
				cout << ( * l_piVal ) << " ";
				if ( ( * l_piVal ) == i )
					{
					re = false;
					if ( & l_oList.present ( ) == & l_oList.tail ( ) )
						re = true;
					l_oList.remove_element ( HList < int >::D_FORCE_REMOVE_ELEMENT | HList < int >::D_TREAT_AS_OPENED );
					if ( re )
						{
						l_piVal = & l_oList.go ( - 1 );
						continue;
						}
					}
				break;
				}
			}
		cout << endl;
		}
	for ( int i = 1; i < 6; i ++ )
		{
		HList < int > l_oList;
		l_oList.add_tail ( ) = 1;
		l_oList.add_tail ( ) = 2;
		l_oList.add_tail ( ) = 3;
		l_oList.add_tail ( ) = 4;
		l_oList.add_tail ( ) = 5;
		l_piVal = & l_oList.go ( 0 );
		while ( l_piVal )
			{
			cout << ( * l_piVal ) << " ";
			if ( ( * l_piVal ) == i )
				{
				l_oList.remove_element ( HList < int >::D_FORCE_REMOVE_ELEMENT | HList < int >::D_TREAT_AS_OPENED, & l_piVal );
				if ( l_piVal && l_oList.quantity ( ) )
					{
					l_piVal = & l_oList.present ( );
					continue;
					}
				else break;
				}
			else l_piVal = l_oList.to_tail ( 1, HList < int >::D_TREAT_AS_OPENED );
			}
		cout << endl;
		}
	}

/* true forward iterator */
template < >
template < >
void module::test<12> ( void )
	{
	int l_iCtr = 0;
	HList < int > l_oList;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	for ( HList<int>::HIterator it = l_oList.begin ( );
			it != l_oList.end ( ); ++ it )
		{
		l_iCtr ++;
		ensure_equals ( "for syntax: forward iterator made wrong move", ( * it ), l_iCtr );
		}
	ensure_equals ( "for syntax: not the whole list was iterated", l_iCtr, 5 );
	}

/* true backward iterator */
template < >
template < >
void module::test<13> ( void )
	{
	int l_iCtr = 5;
	HList < int > l_oList;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 4;
	l_oList.add_tail ( ) = 5;
	for ( HList<int>::HIterator it = l_oList.rend ( );
			it != l_oList.rbegin ( ); -- it )
		{
		ensure_equals ( "for syntax: backward iterator made wrong move", ( * it ), l_iCtr );
		l_iCtr --;
		}
	ensure_equals ( "for syntax: not the whole list was iterated", l_iCtr, 0 );
	}

/* Sorting. */
template < >
template < >
void module::test<40> ( void )
	{
	HList < int > l_oList;
	l_oList.add_tail ( ) = 3;
	l_oList.add_tail ( ) = 1;
	l_oList.add_tail ( ) = 2;
	ensure_equals ( "operator[] or add_tail failed", l_oList [ 0 ], 3 );
	ensure_equals ( "operator[] or add_tail failed", l_oList [ 1 ], 1 );
	ensure_equals ( "operator[] or add_tail failed", l_oList [ 2 ], 2 );
	l_oList.sort_by_contents ( );
	ensure_equals ( "sort failed", l_oList [ 0 ], 1 );
	ensure_equals ( "sort failed", l_oList [ 1 ], 2 );
	ensure_equals ( "sort failed", l_oList [ 2 ], 3 );
	}

}
