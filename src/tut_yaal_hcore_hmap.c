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
M_VCSID ( "$CVSHeader: tress/src/tut.c,v 1.6 2006/01/24 11:51:47 amok Exp $" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal_hcore_hmap
	{
	};

typedef test_group < tut_yaal_hcore_hmap > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hmap_group ( "yaal::hcore::HMap" );

/* Simple constructor. */
template < >
template < >
void module::test<1> ( void )
	{
	try
		{
		HMap < int, HString > map ( 0 );
		fail ( "Created map with bad hash table size." );
		}
	catch ( HException const & e )
		{
		cout << e.what ( ) << endl;
		}
	}


/* Quantity test. */
template < >
template < >
void module::test<2> ( void )
	{
	HMap < int, HString > map ( 17 );
	ensure_equals ( "Newly created map is not empty.", map.quantity ( ), 0 );
	map [ 0 ] = "foo";
	ensure_equals ( "Wrong quantity count returned.", map.quantity ( ), 1 );
	}

}
