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

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

#define RESOLE_MACRO_FOR_MAKE_C_STRING( x ) ( #x )
#define MAKE_C_STRING( x ) RESOLE_MACRO_FOR_MAKE_C_STRING( x )

#define SELF_SUMATOR self_sumator
extern "C"
int SELF_SUMATOR( int a, int b )
	{
	return ( a + b );
	}

namespace tut
{

struct tut_yaal_tools_hplugin
	{
	};

TUT_TEST_GROUP_N( tut_yaal_tools_hplugin, "yaal::tools::HPlugin" );

typedef int ( * sumator_t )( int, int );

TUT_UNIT_TEST_N( 1, "load external library and resolve symbol" )
	static char const* const D_TRESS_PLUGIN = "./data/tressplugin.so";
	int const T1 = 7;
	int const T2 = 13;
	HPlugin p;
	p.load( D_TRESS_PLUGIN );
	sumator_t my_sum;
	p.resolve( "tut_yaal_tools_hplugin_sum", my_sum );
	ensure_equals( "cound not utilize plugin", my_sum( T1, T2 ), T1 + T2 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "resolve symbol from self" )
	int const T1 = 7;
	int const T2 = 13;
	HPlugin p;
	p.load( HString() );
	sumator_t my_sum;
	p.resolve( MAKE_C_STRING( SELF_SUMATOR ), my_sum );
	ensure_equals( "cound not utilise self-contained symbols", my_sum( T1, T2 ), T1 + T2 );
TUT_TEARDOWN()

}

