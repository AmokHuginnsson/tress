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

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <boost/bind.hpp>

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

using namespace tut;
using namespace tut_helpers;
using namespace std;
using namespace boost;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_stl
	{
	};

typedef test_group<tut_stl> tut_group;
typedef tut_group::object module;
tut_group tut_stl_group( "std" );

/* create */
template<>
template<>
void module::test<1>( void )
	{
	TITLE( "by_hand" );
	cout << "lets do everything by hand ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 3 );

	for ( T::const_iterator it = s.begin(); it != s.end(); ++ it )
		cout << *it;
	cout << endl;

	cout << "}" << endl;
	}

/* display automatically */
template<>
template<>
void module::test<2>( void )
	{
	TITLE( "display" );
	cout << "display container contents automatically ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 3 );
	copy( s.begin(), s.end(), ostream_iterator<int>( cout ) );
	cout << endl;
	cout << "}" << endl;
	}

struct inc { int _n; inc( int n ) : _n( n ){} int operator()() { return ( _n ++ ); } };
/* create contents automatically */
template<>
template<>
void module::test<3>( void )
	{
	TITLE( "create" );
	cout << "create container contents automatically ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	generate_n( insert_iterator<T>( s, s.begin() ), 3, inc( 1 ) );
	copy( s.begin(), s.end(), ostream_iterator<int>( cout ) );
	cout << endl;
	cout << "}" << endl;
	}

}

