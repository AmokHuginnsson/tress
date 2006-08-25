/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hcomplex.c - this file is integral part of `tress' project.

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
M_VCSID ( "$CVSHeader: tress/src/tut_yaal_hcore_hcomplex.c,v 1.5 2006/01/24 11:51:47 amok Exp $" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal_hcore_hcomplex
	{
	};

typedef test_group < tut_yaal_hcore_hcomplex > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hcomplex_group ( "yaal::hcore::HComplex" );

/* Default constructor */
template < >
template < >
void module::test<1> ( void )
	{
	HComplex a;
	ensure_distance ( "non zero new complex number (re)", a.re ( ), 0., 0.001 );
	ensure_distance ( "non zero new complex number (im)", a.im ( ), 0., 0.001 );
	}

/* Constructor with initialization. */
template < >
template < >
void module::test<2> ( void )
	{
	double const RE = 3.14159265;
	double const IM = 2.17;
	HComplex a ( RE );
	ensure_distance ( "non zero new complex number (im)", a.im ( ), 0., 0.001 );
	ensure_distance ( "re incrorrectly set by constructor", a.re ( ), RE, 0.001 );
	HComplex b ( RE, IM );
	ensure_distance ( "re incrorrectly set by constructor", b.re ( ), RE, 0.001 );
	ensure_distance ( "im incrorrectly set by constructor", b.im ( ), IM, 0.001 );
	}

}

