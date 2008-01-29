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
#include <boost/filesystem.hpp>

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

using namespace tut;
using namespace tut_helpers;
using namespace std;
using namespace boost;
using namespace boost::filesystem;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_boost
	{
	};

typedef test_group<tut_boost> tut_group;
typedef tut_group::object module;
tut_group tut_boost_group( "boost" );

struct multi
	{
	int _first;
	int _second;
	};

multi make_multi( void )
	{
	static multi res[] = { { 1, 3 }, { 4, 1 }, { 2, 4 }, { 3, 2 } };
	static int idx = 0;
	int i = idx;
	++ idx;
	idx %= ( sizeof ( res ) / sizeof ( multi ) );
	return ( res[ i ] );
	}

ostream& operator << ( ostream& out, multi const& m )
	{
	out << "(" << m._first << "," << m._second << ")";
	return ( out );
	}

/* binding */
template<>
template<>
void module::test<1>( void )
	{
	TITLE( "bind" );
	cout << "sort by field using binding" << endl;
	cout << "{" << endl;
	typedef vector<multi> T;
	T v;
	generate_n( back_insert_iterator<T>( v ), 3, make_multi );
	copy( v.begin(), v.end(), ostream_iterator<multi>( cout ) );
	cout << endl;
	sort( v.begin(), v.end(), bind( &multi::_first, _1 ) < bind( &multi::_first, _2 ) );
	copy( v.begin(), v.end(), ostream_iterator<multi>( cout ) );
	cout << endl;
	cout << "}" << endl;
	}

void dump_dir( path const& dir )
	{
	cout << "dir: " << dir << endl;
	directory_iterator end;
	for ( directory_iterator it( dir ); it != end; ++ it )
		{
		if ( is_directory( *it ) )
			dump_dir( *it );
		else
			cout << "file: " << *it << endl;
		}
	return;
	}

/* filesystem */
template<>
template<>
void module::test<2>( void )
	{
	TITLE( "filesystem" );
	dump_dir( path( "." ) );
	}

}

