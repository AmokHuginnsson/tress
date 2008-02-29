/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	must_not_compile/tut_yaal_hcore_hlist.cxx - this file is integral part of `tress' project.

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

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

#if defined ( BUG_000 )

namespace must_not_compile
{

typedef HList<int> int_list_t;

int sum( int_list_t const& l )
	{
	int l_iSum = 0;

	for ( int_list_t::iterator it = l.begin(); it != l.end(); ++ it ) /* MUST_FAIL_HERE */
		l_iSum += *it;
	return ( l_iSum );
	}

}

int main( int, char** )
	{
	must_not_compile::int_list_t l;
	l.push_back( 1 );
	l.push_back( 3 );
	l.push_back( 5 );
	return ( must_not_compile::sum( l ) );
	}

#elif defined ( BUG_001 )

namespace must_not_compile
{

typedef HList<int> int_list_t;

int sum( int_list_t const& l )
	{
	int l_iSum = 0;
	
	for ( int_list_t::const_iterator it = l.begin(); it != l.end(); ++ it )
		*it = -*it; /* MUST_FAIL_HERE */
	return ( l_iSum );
	}

}

int main( int, char** )
	{
	must_not_compile::int_list_t l;
	l.push_back( 1 );
	l.push_back( 3 );
	l.push_back( 5 );
	return ( must_not_compile::sum( l ) );
	}

#else
#	error NO_SUCH_BUG
#endif
