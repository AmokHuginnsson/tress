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
	HBTree rb;
	rb.insert ( 2 );
	rb.insert ( 7 );
	rb.insert ( 4 );
	rb.insert ( 3 );
	rb.insert ( 11 );
	rb.insert ( 0 );
	rb.insert ( 5 );
	rb.insert ( 6 );
	rb.insert ( 1 );
	for ( HBTree::HIterator it = rb.begin ( ); it != rb.end ( ); ++ it )
		cout << ( *it ) << endl;
	}

}
