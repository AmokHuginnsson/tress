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

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_tools_hbitmap
	{
	};

M_TEST_GROUP( tut_yaal_tools_hbitmap, "yaal::tools::HBitmap" );

M_UNIT_TEST( "/* Default constructor */" )
	HBitmap bmp;
	ensure_equals( "size", bmp.get_size(), 0 );
	ensure_equals( "raw", bmp.raw(), static_cast<void*>( NULL ) );
M_TEARDOWN()

M_UNIT_TEST( "/* constructor from size */" )
	static int const D_SIZE = 7;
	HBitmap bmp( D_SIZE );
	ensure_equals( "constructor from size size", bmp.get_size(), D_SIZE );
	ensure( "default constructor raw", bmp.raw() != static_cast<void*>( NULL ) );
	ensure( "default constructor ", bmp.raw() != static_cast<void*>( NULL ) );
M_TEARDOWN()

M_UNIT_TEST( "/* set */" )
	HBitmap bmp;
	try
		{
		bmp.set( 0, true );
		fail( "default constructor set" );
		}
	catch ( int& )
		{
		// ok
		}
M_TEARDOWN()

M_UNIT_TEST( "/* get */" )
	HBitmap bmp;
	try
		{
		bmp.get( 0 );
		fail( "default constructor set" );
		}
	catch ( int& )
		{
		// ok
		}
M_TEARDOWN()

M_UNIT_TEST( "/* rotate_left */" )
	HBitmap bmp;
	try
		{
		bmp.rotate_left( 0, 0, 0 );
		fail( "default constructor set" );
		}
	catch ( int& )
		{
		// ok
		}
M_TEARDOWN()

M_UNIT_TEST( "/* rotate_right */" )
	HBitmap bmp;
	try
		{
		bmp.rotate_right( 0, 0, 0 );
		fail( "default constructor set" );
		}
	catch ( int& )
		{
		// ok
		}
M_TEARDOWN()

}

