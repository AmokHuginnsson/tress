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
	};

typedef test_group < tut_yaal_hcore_hbtree > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hbtree_group ( "yaal::hcore::HBTree" );

template < >
template < >
void module::test<1> ( void )
	{
	set<int> s;
	s.insert ( 2 );
	s.insert ( 7 );
	s.insert ( 4 );
	s.insert ( 3 );
	s.insert ( 11 );
	s.insert ( 0 );
	s.insert ( 5 );
	s.insert ( 6 );
	s.insert ( 1 );
	cout << "start" << endl;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		cout << ( *it ) << endl;
	cout << "end" << endl;
	}

}
