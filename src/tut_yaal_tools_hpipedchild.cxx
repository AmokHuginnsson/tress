/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hpipedchild.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/tools/hpipedchild.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hpipedchild : public simple_mock<tut_yaal_tools_hpipedchild> {
	typedef simple_mock<tut_yaal_tools_hpipedchild> base_type;
	static HString CHILD;
	static HString CHILD_FAKE;
	static HString MSG_OUT;
	static HString MSG_ERR;
	static HString ACK_OUT;
	static HString ACK_ERR;
	virtual ~tut_yaal_tools_hpipedchild( void )
		{}
};

HString tut_yaal_tools_hpipedchild::CHILD( "./data/child" EXE_SUFFIX );
HString tut_yaal_tools_hpipedchild::CHILD_FAKE( "./data/child_fake" );
HString tut_yaal_tools_hpipedchild::MSG_OUT( "out" );
HString tut_yaal_tools_hpipedchild::MSG_ERR( "err" );
HString tut_yaal_tools_hpipedchild::ACK_OUT( "hello-OUT" );
HString tut_yaal_tools_hpipedchild::ACK_ERR( "hello-ERR" );

TUT_TEST_GROUP( tut_yaal_tools_hpipedchild, "yaal::tools::HPipedChild" );

TUT_UNIT_TEST( "simple constructor" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn and finish" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn on non-execuable" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	ENSURE_THROW( "spawning non-executable", pc.spawn( CHILD_FAKE ), HPipedChildException );
	ENSURE_EQUALS( "running after failed spawn", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn, write and read (stdout)" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	pc.in() << MSG_OUT << endl;
	HString ack;
	TUT_INVOKE( cout << pc.out().read_until( ack ) << endl; );
	ENSURE_EQUALS( "bad ack OUT", ack, ACK_OUT );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn, write and read (stderr)" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	pc.in() << MSG_ERR << endl;
	HString ack;
	TUT_INVOKE( cout << pc.err().read_until( ack ) << endl; );
	ENSURE_EQUALS( "bad ack ERR", ack, ACK_ERR );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

}

