/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hpipedchild.cxx - this file is integral part of `tress' project.

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


struct tut_yaal_tools_hpipedchild
	{
	static HString D_CHILD;
	static HString D_CHILD_FAKE;
	static HString D_MSG_OUT;
	static HString D_MSG_ERR;
	static HString D_ACK_OUT;
	static HString D_ACK_ERR;
	};

HString tut_yaal_tools_hpipedchild::D_CHILD( "./data/child" );
HString tut_yaal_tools_hpipedchild::D_CHILD_FAKE( "./data/child_fake" );
HString tut_yaal_tools_hpipedchild::D_MSG_OUT( "out" );
HString tut_yaal_tools_hpipedchild::D_MSG_ERR( "err" );
HString tut_yaal_tools_hpipedchild::D_ACK_OUT( "hello-OUT" );
HString tut_yaal_tools_hpipedchild::D_ACK_ERR( "hello-ERR" );

TUT_TEST_GROUP_N( tut_yaal_tools_hpipedchild, "yaal::tools::HPipedChild" );

TUT_UNIT_TEST_N( 1, "simple constructor" )
	HPipedChild pc;
	ensure_equals( "bad state on simple construction", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "spawn and finish" )
	HPipedChild pc;
	ensure_equals( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( D_CHILD );
	ensure_equals( "bad state after spawn", pc.is_running(), true );
	pc.finish();
	ensure_equals( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "spawn on non-execuable" )
	HPipedChild pc;
	ensure_equals( "bad state on simple construction", pc.is_running(), false );
	try
		{
		pc.spawn( D_CHILD_FAKE );
		fail( "spawning non-executable" );
		}
	catch ( HPipedChildException& )
		{
		// ok
		}
	ensure_equals( "running after failed spawn", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "spawn, write and read (stdout)" )
	HPipedChild pc;
	ensure_equals( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( D_CHILD );
	ensure_equals( "bad state after spawn", pc.is_running(), true );
	pc << D_MSG_OUT << endl;
	HString ack;
	pc.read_until( ack );
	ensure_equals( "bad ack OUT", ack, D_ACK_OUT );
	pc.finish();
	ensure_equals( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

}

