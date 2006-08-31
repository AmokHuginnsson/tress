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

namespace yaal
{

template < typename tType >
struct set
	{
	struct iterator
		{
		HBTree::HIterator f_oEngine;
		explicit iterator ( HBTree::HIterator const & it ) : f_oEngine ( it ){};
		iterator & operator ++ ( void )
			{
			++ f_oEngine;
			return ( * this );
			}
		tType & operator * ( void )
			{	return ( f_oEngine.get<tType> ( ) );	}
		tType * operator -> ( void )
			{ return ( & f_oEngine.get<tType> ( ) );	}
		bool operator == ( iterator const & it ) const
			{ return ( f_oEngine == it.f_oEngine ); }
		bool operator != ( iterator const & it ) const
			{ return ( f_oEngine != it.f_oEngine ); }
		};
	HBTree f_oEngine;
	set ( void ) : f_oEngine ( ) {};
	long int quantity ( void )
		{ return ( f_oEngine.quantity ( ) );	}
	void insert ( tType const & e )
		{	f_oEngine.insert ( e );	}
	void remove ( tType const & e )
		{	f_oEngine.remove ( e );	}
	iterator find ( tType const & e )
		{ return ( f_oEngine.find ( e ) ); }
	iterator begin ( void )
		{ return ( iterator ( f_oEngine.begin ( ) ) ); }
	iterator end ( void )
		{ return ( iterator ( f_oEngine.end ( ) ) ); }
	iterator rbegin ( void )
		{ return ( iterator ( f_oEngine.rbegin ( ) ) ); }
	iterator rend ( void )
		{ return ( iterator ( f_oEngine.rend ( ) ) ); }
	};

}

namespace tut
{

struct tut_yaal_hcore_hbtree
	{
	static int const NUMBER_OF_TEST_NODES = 20000;
	};

typedef test_group < tut_yaal_hcore_hbtree > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hbtree_group ( "yaal::hcore::HBTree" );

template < >
template < >
void module::test<1> ( void )
	{
	set<int> s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

template < >
template < >
void module::test<2> ( void )
	{
	HRandomizer r;
	set<int> s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

template < >
template < >
void module::test<3> ( void )
	{
	HRandomizer r;
	set<int> s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( r.rnd ( 20000 ) );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

}

