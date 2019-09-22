/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstdio>
#include <cstdlib>
#ifdef __GNUC__
#include <unistd.h>
#endif /* #ifdef __GNUC__ */

#include <TUT/tut.hpp>

#include <yaal/tools/hpipedchild.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hcore/hpipe.hxx>
#include <yaal/tools/sleep.hxx>
#include <yaal/tools/hfsitem.hxx>
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

TUT_UNIT_TEST( "spawn, write stream and read stream" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	HPipe inPipe;
	HPipe outPipe;
	HStreamInterface::ptr_t in( inPipe.in() );
	HStreamInterface::ptr_t out( outPipe.out() );
	pc.spawn( CHILD, {}, inPipe.out().raw(), outPipe.in().raw() );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	*in << MSG_OUT << endl;
	HString ack;
	TUT_EVAL( out->read_until( ack ) );
	ENSURE_EQUALS( "bad ack OUT", ack, ACK_OUT );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn, write stream and read stream" )
	HPipe inPipe;
	HPipe outPipe;
	HStreamInterface::ptr_t in( inPipe.in() );
	HStreamInterface::ptr_t out( outPipe.out() );
	HPipedChild pc( inPipe.out(), outPipe.in() );
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD, {} );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	*in << MSG_OUT << endl;
	HString ack;
	TUT_EVAL( out->read_until( ack ) );
	ENSURE_EQUALS( "bad ack OUT", ack, ACK_OUT );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "redirect child stdout to file (passing ownership)" )
	static char const PIPED_CHILD_LOG_PATH[] = "./out/piped-child.log";
	::unlink( PIPED_CHILD_LOG_PATH );
	HPipe inPipe;
	HStreamInterface::ptr_t in( inPipe.in() );
	HStreamInterface::ptr_t out( make_pointer<HFile>( PIPED_CHILD_LOG_PATH, HFile::OPEN::WRITING ) );
	HPipedChild pc( inPipe.out(), out );
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD, {} );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	*in << MSG_OUT << endl;
	for ( int i( 0 ); i < 32; ++ i ) {
		HFSItem fi( PIPED_CHILD_LOG_PATH );
		if ( !! fi && fi.get_size() > 0 ) {
			break;
		}
		sleep_for( duration( 100, time::UNIT::MILLISECOND ) );
	}
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
	HFile logFile( PIPED_CHILD_LOG_PATH, HFile::OPEN::READING );
	HString line;
	getline( logFile, line );
	ENSURE_EQUALS( "bad redirected data", line, ACK_OUT );
	ENSURE_NOT( "spurious data in log file", getline( logFile, line ).good() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "redirect child stdout to file (keep ownership)" )
	static char const PIPED_CHILD_LOG_PATH[] = "./out/piped-child.log";
	::unlink( PIPED_CHILD_LOG_PATH );
	HPipe inPipe;
	HStreamInterface::ptr_t in( inPipe.in() );
	HStreamInterface::ptr_t out( make_pointer<HFile>( PIPED_CHILD_LOG_PATH, HFile::OPEN::WRITING ) );
	HPipedChild pc( inPipe.out() );
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD, {}, nullptr, out.raw() );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	*in << MSG_OUT << endl;
	for ( int i( 0 ); i < 32; ++ i ) {
		HFSItem fi( PIPED_CHILD_LOG_PATH );
		if ( !! fi && fi.get_size() > 0 ) {
			break;
		}
		sleep_for( duration( 100, time::UNIT::MILLISECOND ) );
	}
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
	HFile logFile( PIPED_CHILD_LOG_PATH, HFile::OPEN::READING );
	HString line;
	getline( logFile, line );
	ENSURE_EQUALS( "bad redirected data", line, ACK_OUT );
	ENSURE_NOT( "spurious data in log file", getline( logFile, line ).good() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "redirect child stdout and stderr to the same file (passing ownership)" )
	static char const PIPED_CHILD_LOG_PATH[] = "./out/piped-child.log";
	::unlink( PIPED_CHILD_LOG_PATH );
	HPipe inPipe;
	HStreamInterface::ptr_t in( inPipe.in() );
	HStreamInterface::ptr_t out( make_pointer<HFile>( PIPED_CHILD_LOG_PATH, HFile::OPEN::WRITING ) );
	HPipedChild pc( inPipe.out(), out, out );
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD, { "2" } );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	*in << MSG_OUT << endl;
	*in << MSG_ERR << endl;
	for ( int i( 0 ); i < 32; ++ i ) {
		HFSItem fi( PIPED_CHILD_LOG_PATH );
		if ( !! fi && fi.get_size() > 10 ) {
			break;
		}
		sleep_for( duration( 100, time::UNIT::MILLISECOND ) );
	}
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
	HFile logFile( PIPED_CHILD_LOG_PATH, HFile::OPEN::READING );
	HString line;
	getline( logFile, line );
	ENSURE_EQUALS( "bad redirected stdout data", line, ACK_OUT );
	getline( logFile, line );
	ENSURE_EQUALS( "bad redirected stderr data", line, ACK_ERR );
TUT_TEARDOWN()

TUT_UNIT_TEST( "redirect child stdout and stderr to the same file (keeping ownership)" )
	static char const PIPED_CHILD_LOG_PATH[] = "./out/piped-child.log";
	::unlink( PIPED_CHILD_LOG_PATH );
	HPipe inPipe;
	HStreamInterface::ptr_t in( inPipe.in() );
	HStreamInterface::ptr_t out( make_pointer<HFile>( PIPED_CHILD_LOG_PATH, HFile::OPEN::WRITING ) );
	HPipedChild pc( inPipe.out() );
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD, { "2" }, nullptr, out.raw(), out.raw() );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	*in << MSG_OUT << endl;
	*in << MSG_ERR << endl;
	for ( int i( 0 ); i < 32; ++ i ) {
		HFSItem fi( PIPED_CHILD_LOG_PATH );
		if ( !! fi && fi.get_size() > 10 ) {
			break;
		}
		sleep_for( duration( 100, time::UNIT::MILLISECOND ) );
	}
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
	HFile logFile( PIPED_CHILD_LOG_PATH, HFile::OPEN::READING );
	HString line;
	getline( logFile, line );
	ENSURE_EQUALS( "bad redirected stdout data", line, ACK_OUT );
	getline( logFile, line );
	ENSURE_EQUALS( "bad redirected stderr data", line, ACK_ERR );
TUT_TEARDOWN()

}

