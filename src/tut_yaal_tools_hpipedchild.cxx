/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hpipedchild.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/tools/sleep.hxx>
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
	TUT_EVAL( pc.out().read_until( ack ) );
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
	TUT_EVAL( pc.err().read_until( ack ) );
	ENSURE_EQUALS( "bad ack ERR", ack, ACK_ERR );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "finish after very short lived process ends" )
	HPipedChild pc;
	pc.spawn( CHILD );
	pc.in() << MSG_OUT << endl;
	HString ack;
	HString line;
	while ( pc.out().read_until( line ) > 0 ) {
		if ( ! line.is_empty() ) {
			ack = line;
		}
	}
	/* Without proper fix on Cygwin this test throws exception from pc.finish() */
	pc.finish();
	ENSURE_EQUALS( "bad ack OUT", ack, ACK_OUT );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read after very short lived process ends" )
	HPipedChild pc;
	pc.spawn( CHILD );
	pc.in() << MSG_OUT << endl;
	HString ack;
	HString line;
	sleep_for( duration( 1, time::UNIT::SECOND ) );
	/* Without proper fix on MSVCXX next line will hang indefinetly. */
	while ( pc.out().read_until( line ) > 0 ) {
		if ( ! line.is_empty() ) {
			ack = line;
		}
	}
	pc.finish();
	ENSURE_EQUALS( "bad ack OUT", ack, ACK_OUT );
TUT_TEARDOWN()

}

