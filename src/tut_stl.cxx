/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_stl.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every yaal::copy
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
#include <functional>
#include <boost/bind.hpp>

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace boost;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_stl
	{
	};

typedef test_group<tut_stl> tut_group;
typedef tut_group::object module;
tut_group tut_stl_group( "std" );

TUT_UNIT_TEST_N( 1, "create by_hand" )
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
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "display automatically" )
	cout << "display container contents automatically ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 3 );
	yaal::copy( s.begin(), s.end(), ostream_iterator<int>( cout ) );
	cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "create contents automatically" )
	cout << "create container contents automatically ..." << endl;
	cout << "{" << endl;
	typedef set<int> T;
	T s;
	generate_n( insert_iterator<T>( s, s.begin() ), 3, inc( 1 ) );
	yaal::copy( s.begin(), s.end(), ostream_iterator<int>( cout ) );
	cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "reverse container content automatically" )
	cout << "reverse container content ..." << endl;
	cout << "{" << endl;
	typedef list<int> T;
	T l;
	generate_n( back_insert_iterator<T>( l ), 3, inc( 1 ) );
	yaal::copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	reverse( l.begin(), l.end() );
	yaal::copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	T lc;
	reverse_copy( l.begin(), l.end(), back_insert_iterator<T>( lc ) );
	yaal::copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	yaal::copy( lc.begin(), lc.end(), ostream_iterator<int>( cout ) ); cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "transform (negate) container content automatically" )
	cout << "negate container content ..." << endl;
	cout << "{" << endl;
	typedef list<int> T;
	T l;
	generate_n( back_insert_iterator<T>( l ), 20, inc( 1 ) );
	yaal::copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	std::replace_if(l.begin(), l.end(), std::bind2nd(std::less<int>(), 10), 10);
	yaal::copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	yaal::transform( l.begin(), l.end(), l.begin(), negate<int>() );
	yaal::copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	yaal::transform( l.begin(), l.end(), l.begin(), yaal::bind2nd( yaal::plus<int>(), 7 ) );
	yaal::copy( l.begin(), l.end(), ostream_iterator<int>( cout ) ); cout << endl;
	cout << "}" << endl;
	vector<string> vs;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "max_size of string" )
	string str;
	cout << str.max_size() << endl;
TUT_TEARDOWN()

}

