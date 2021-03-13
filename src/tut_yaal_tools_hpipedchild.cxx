/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstdio>
#include <cstdlib>
#ifndef _MSC_VER
#include <csignal>
#include <unistd.h>
#else
#define SIGTERM 15
#endif /* #ifndef _MSC_VER */

#include <TUT/tut.hpp>

#include <yaal/tools/hpipedchild.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hcore/hpipe.hxx>
#include <yaal/tools/sleep.hxx>
#include <yaal/tools/stringalgo.hxx>
#include <yaal/tools/hfsitem.hxx>
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace yaal {
namespace tools {

inline bool operator == ( HPipedChild::STATUS left_, HPipedChild::STATUS right_ ) {
	return ( ( left_.type == right_.type ) && ( left_.value == right_.value ) );
}

inline std::ostream& operator << ( std::ostream& out, HPipedChild::STATUS const& s ) {
	out << "(" << static_cast<int>( s.type ) << "," << s.value << ")";
	return out;
}

}
}

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

#ifdef __HOST_OS_TYPE_CYGWIN__
#	define TUT_SUITE_PREFIX "000"
#else
#	define TUT_SUITE_PREFIX ""
#endif

TUT_TEST_GROUP( tut_yaal_tools_hpipedchild, TUT_SUITE_PREFIX "yaal::tools::HPipedChild" );

TUT_UNIT_TEST( "simple constructor" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), HPipedChild::STATUS() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn and finish" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), HPipedChild::STATUS() );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	HPipedChild::STATUS s;
	s.type = HPipedChild::STATUS::TYPE::RUNNING;
	ENSURE_EQUALS( "bad status after spawn", pc.get_status(), s );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
#ifndef __HOST_OS_TYPE_CYGWIN__
#ifndef _MSC_VER
	s.type = HPipedChild::STATUS::TYPE::ABORTED;
#else
	s.type = HPipedChild::STATUS::TYPE::FINISHED;
#endif
	s.value = SIGTERM;
	ENSURE_EQUALS( "bad status after finish", pc.get_status(), s );
#endif
TUT_TEARDOWN()

#ifndef _MSC_VER
TUT_UNIT_TEST( "spawn, pause, continue and finish" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), HPipedChild::STATUS() );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	HPipedChild::STATUS s;
	s.type = HPipedChild::STATUS::TYPE::RUNNING;
	ENSURE_EQUALS( "bad status after pause", pc.get_status(), s );
#ifdef __HOST_OS_TYPE_CYGWIN__
	sleep_for( duration( 1, time::UNIT::SECOND ) );
#endif
	system::kill( pc.get_pid(), SIGSTOP );
	sleep_for( duration( 1, time::UNIT::SECOND ) );
#ifndef __HOST_OS_TYPE_CYGWIN__
	s.type = HPipedChild::STATUS::TYPE::PAUSED;
	s.value = SIGSTOP;
	ENSURE_EQUALS( "bad status after stop", pc.get_status(), s );
#endif
	system::kill( pc.get_pid(), SIGCONT );
	sleep_for( duration( 1, time::UNIT::SECOND ) );
	s.type = HPipedChild::STATUS::TYPE::RUNNING;
	ENSURE_EQUALS( "bad status after cont", pc.get_status(), s );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
#ifndef __HOST_OS_TYPE_CYGWIN__
	s.type = HPipedChild::STATUS::TYPE::ABORTED;
	s.value = SIGTERM;
	ENSURE_EQUALS( "bad status after finish", pc.get_status(), s );
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn, pause and finish" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), HPipedChild::STATUS() );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	HPipedChild::STATUS s;
	s.type = HPipedChild::STATUS::TYPE::RUNNING;
	ENSURE_EQUALS( "bad status after pause", pc.get_status(), s );
#ifdef __HOST_OS_TYPE_CYGWIN__
	sleep_for( duration( 1, time::UNIT::SECOND ) );
#endif
	system::kill( pc.get_pid(), SIGSTOP );
	sleep_for( duration( 1, time::UNIT::SECOND ) );
#ifndef __HOST_OS_TYPE_CYGWIN__
	s.type = HPipedChild::STATUS::TYPE::PAUSED;
	s.value = SIGSTOP;
	ENSURE_EQUALS( "bad status after stop", pc.get_status(), s );
#endif
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
#ifndef __HOST_OS_TYPE_CYGWIN__
	s.type = HPipedChild::STATUS::TYPE::ABORTED;
	s.value = SIGTERM;
	ENSURE_EQUALS( "bad status after finish", pc.get_status(), s );
#endif
TUT_TEARDOWN()
#endif

TUT_UNIT_TEST( "spawn on non-execuable" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	ENSURE_THROW( "spawning non-executable", pc.spawn( CHILD_FAKE ), HPipedChildException );
	ENSURE_EQUALS( "running after failed spawn", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn, write and read (stdout)" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), HPipedChild::STATUS() );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	HPipedChild::STATUS s;
	s.type = HPipedChild::STATUS::TYPE::RUNNING;
	ENSURE_EQUALS( "bad status after spawn", pc.get_status(), s );
	pc.in() << MSG_OUT << endl;
	HString ack;
	TUT_EVAL( getline( pc.out(), ack ).good() );
	ENSURE_EQUALS( "bad ack OUT", ack, ACK_OUT );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
#ifndef __HOST_OS_TYPE_CYGWIN__
#ifndef _MSC_VER
	s.type = HPipedChild::STATUS::TYPE::ABORTED;
	s.value = SIGTERM;
	ENSURE_EQUALS( "bad status after finish", pc.get_status(), s );
#else
	s.type = HPipedChild::STATUS::TYPE::FINISHED;
	HPipedChild::STATUS sa( s );
	sa.value = SIGTERM;
	ENSURE_IN( "bad status after finish", pc.get_status(), std::vector<HPipedChild::STATUS>({ s, sa }) );
#endif
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn, write and continuous read (stdout)" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), HPipedChild::STATUS() );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	HPipedChild::STATUS s;
	s.type = HPipedChild::STATUS::TYPE::RUNNING;
	ENSURE_EQUALS( "bad status after spawn", pc.get_status(), s );
	pc.in() << MSG_OUT << endl;
	HString ack;
	string::tokens_t lines;
	while ( pc.out().good() ) {
		TUT_EVAL( getline( pc.out(), ack ).good() );
		lines.push_back( ack );
	}
	ENSURE_EQUALS( "bad OUT", lines, string::tokens_t( { ACK_OUT, "" } ) );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
#ifndef __HOST_OS_TYPE_CYGWIN__
	s.type = HPipedChild::STATUS::TYPE::FINISHED;
	s.value = 0;
	ENSURE_EQUALS( "bad status after finish", pc.get_status(), s );
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn, write and read (stderr)" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad state on simple construction", pc.is_running(), false );
	pc.spawn( CHILD );
	ENSURE_EQUALS( "bad state after spawn", pc.is_running(), true );
	HPipedChild::STATUS s;
	pc.in() << MSG_ERR << endl;
	HString ack;
	TUT_EVAL( getline( pc.err(), ack ).good() );
	ENSURE_EQUALS( "bad ack ERR", ack, ACK_ERR );
	pc.finish();
	ENSURE_EQUALS( "bad state after finish", pc.is_running(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "finish after very short lived process ends" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), HPipedChild::STATUS() );
	pc.spawn( CHILD );
	HPipedChild::STATUS s;
	s.type = HPipedChild::STATUS::TYPE::RUNNING;
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), s );
	pc.in() << MSG_OUT << endl;
	HString ack;
	HString line;
	while ( pc.out().read_until( line ) > 0 ) {
		if ( ! line.is_empty() ) {
			line.trim_right( "\r" );
			ack.append( line );
		}
	}
	/* Without proper fix on Cygwin this test throws exception from pc.finish() */
	pc.finish();
	ENSURE_EQUALS( "bad ack OUT", ack, ACK_OUT );
	s.type = HPipedChild::STATUS::TYPE::FINISHED;
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), s );
TUT_TEARDOWN()

TUT_UNIT_TEST( "exit status" )
	HPipedChild pc;
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), HPipedChild::STATUS() );
	pc.spawn( CHILD );
	HPipedChild::STATUS s;
	s.type = HPipedChild::STATUS::TYPE::RUNNING;
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), s );
	pc.in() << MSG_ERR << endl;
	HString ack;
	HString line;
	while ( pc.err().read_until( line ) > 0 ) {
		if ( ! line.is_empty() ) {
			line.trim_right( "\r" );
			ack.append( line );
		}
	}
	/* Without proper fix on Cygwin this test throws exception from pc.finish() */
	pc.finish();
	ENSURE_EQUALS( "bad ack ERR", ack, ACK_ERR );
	s.type = HPipedChild::STATUS::TYPE::FINISHED;
	s.value = 7;
	ENSURE_EQUALS( "bad status on simple construction", pc.get_status(), s );
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
			line.trim_right( "\r" );
			ack.append( line );
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
	TUT_EVAL( getline( *out, ack ).good() );
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
	TUT_EVAL( getline( *out, ack ).good() );
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

