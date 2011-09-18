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
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {


struct tut_yaal_tools_hpipedchild {
	static HString CHILD;
	static HString CHILD_FAKE;
	static HString MSG_OUT;
	static HString MSG_ERR;
	static HString ACK_OUT;
	static HString ACK_ERR;
	virtual ~tut_yaal_tools_hpipedchild( void )
		{}
};

HString tut_yaal_tools_hpipedchild::CHILD( "./data/child"EXE_SUFFIX );
HString tut_yaal_tools_hpipedchild::CHILD_FAKE( "./data/child_fake" );
HString tut_yaal_tools_hpipedchild::MSG_OUT( "out" );
HString tut_yaal_tools_hpipedchild::MSG_ERR( "err" );
HString tut_yaal_tools_hpipedchild::ACK_OUT( "hello-OUT" );
HString tut_yaal_tools_hpipedchild::ACK_ERR( "hello-ERR" );

TUT_TEST_GROUP( tut_yaal_tools_hpipedchild, "yaal::tools::HPipedChild" );

TUT_UNIT_TEST( 1, "simple constructor" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "spawn and finish" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "spawn on non-execuable" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	try {
		pc.spawn( CHILD_FAKE );
		FAIL( "spawning non-executable" );
	} catch ( HPipedChildException& ) {
		// ok
	}
	ENSURE_EQUALS( "running after failed spawn", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "spawn, write and read (stdout)" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	pc << MSG_OUT << endl;
	HString ack;
	TUT_INVOKE( cout << pc.read_until( ack ) << endl; );
	ENSURE_EQUALS( "bad ack OUT", ack, ACK_OUT );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "spawn, write and read (stderr)" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	pc << MSG_ERR << endl;
	pc.set_csoi( HPipedChild::STREAM::ERR );
	HString ack;
	TUT_INVOKE( cout << pc.read_until( ack ) << endl; );
	ENSURE_EQUALS( "bad ack ERR", ack, ACK_ERR );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

}

