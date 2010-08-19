/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hdes.cxx - this file is integral part of `tress' project.

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

#include <cstdio>
#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"
#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_tools_hdes );
TUT_TEST_GROUP_N( tut_yaal_tools_hdes, "yaal::tool::HDes" );


void do_des( HString src_, HString dst_, HDes::action_t const& action_ )
	{
	HFile in;
	HFile out;
	HString passwd;
	cin >> passwd;
	if ( src_ == "-" )
		in.open( stdin );
	else
		in.open( src_, HFile::OPEN::READING );
	if ( dst_ == "-" )
		out.open( stdout );
	else
		out.open( dst_, HFile::OPEN::WRITING );
	if ( action_ == HDes::CRYPT )
		crypto::crypt_3des( in, out, passwd );
	else
		crypto::decrypt_3des( in, out, passwd );
	}

TUT_UNIT_TEST_N( 1, "crypt file" )
	if ( setup._argc > 2 )
		do_des( setup._argv[ 1 ], setup._argv[ 2 ], HDes::CRYPT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "decrypt file" )
	if ( setup._argc > 2 )
		do_des( setup._argv[ 1 ], setup._argv[ 2 ], HDes::DECRYPT );
TUT_TEARDOWN()

}

