/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hcomplex.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

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

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_hcore_hcomplex );
TUT_TEST_GROUP( tut_yaal_hcore_hcomplex, "yaal::hcore::HComplex" );

TUT_UNIT_TEST( 1, "Default constructor" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (re)", a.re ( ), 0., 0.001 );
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im ( ), 0., 0.001 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Constructor with initialization." )
	double const RE = 3.14159265;
	double const IM = 2.17;
	HComplex a ( RE );
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im ( ), 0., 0.001 );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re ( ), RE, 0.001 );
	HComplex b ( RE, IM );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", b.re ( ), RE, 0.001 );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", b.im ( ), IM, 0.001 );
TUT_TEARDOWN()

}

