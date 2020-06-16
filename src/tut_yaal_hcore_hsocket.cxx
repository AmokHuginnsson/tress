/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstdio>
#include <cstdlib>
#ifdef __GNUC__
#include <unistd.h>
#endif /* #ifdef __GNUC__ */
#include <TUT/tut.hpp>

#include <yaal/hcore/hsocket.hxx>
#include <yaal/tools/hiodispatcher.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hcore::system;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hsocket : public simple_mock<tut_yaal_hcore_hsocket> {
	typedef simple_mock<tut_yaal_hcore_hsocket> base_type;
	static int const OBSCURE_PORT = 61928;
	tut_yaal_hcore_hsocket( void ) {
		::unlink( "/tmp/TUT_socket" );
		errno = 0;
	}
	virtual ~tut_yaal_hcore_hsocket( void )
		{}
	void play_scenario( HSocket::socket_type_t, HString const&, int, bool, bool, bool );
};

TUT_TEST_GROUP( tut_yaal_hcore_hsocket, "yaal::hcore::HSocket" );

struct HServer {
	static int const NO_FD = 17;
	static int const LATENCY = 1000; /* number of miliseconds */
	HString _buffer;
	HIODispatcher _dispatcher;
	HSocket::ptr_t _socket;
	HThread _thread;
	HEvent _event;
	bool _signaled;
	HServer( HSocket::socket_type_t, int );
public:
	void start( void );
	void stop( void );
  void listen( yaal::hcore::HString const&, int const = 0 );
	HString const& buffer( void ) const;
	void run( void );
	void wait( void );
	void do_not_signal( void );
private:
	void handler_connection( HIODispatcher::stream_t&, IO_EVENT_TYPE );
	void handler_message( HIODispatcher::stream_t&, IO_EVENT_TYPE );
	void disconnect_client( HIODispatcher::stream_t& );
	HServer( HServer const& );
	HServer& operator = ( HServer const& );
};

HServer::HServer( HSocket::socket_type_t type_, int maxConn_ )
	: _buffer()
	, _dispatcher( NO_FD, LATENCY )
	, _socket( make_pointer<HSocket>( type_, maxConn_ ) )
	, _thread()
	, _event()
	, _signaled( false ) {
	return;
}

void HServer::listen( yaal::hcore::HString const& path_, int const port_ ) {
	M_PROLOG
	_socket->listen( path_, port_ );
	clog << "listening on: " << path_ << ( port_ ? ":" : "" ) << ( port_ ? HString( port_ ) : HString() ) << endl;
	return;
	M_EPILOG
}

void HServer::start( void ) {
	M_PROLOG
	clog << "starting server thread ..." << endl;
	_dispatcher.register_file_descriptor_handler( _socket, call( &HServer::handler_connection, this, _1, _2 ), IO_EVENT_TYPE::READ );
	_thread.spawn( call( &HServer::run, this ) );
	return;
	M_EPILOG
}

void HServer::stop( void ) {
	M_PROLOG
	_dispatcher.stop();
	_thread.finish();
	clog << "server thread stopped ..." << endl;
	return;
	M_EPILOG
}

void HServer::wait( void ) {
	M_PROLOG
	clog << "waiting for event ..." << endl;
	_event.wait();
	clog << "event arrived ..." << endl;
	return;
	M_EPILOG
}

void HServer::handler_connection( HIODispatcher::stream_t&, IO_EVENT_TYPE ) {
	M_PROLOG
	HSocket::ptr_t client = _socket->accept();
	M_ASSERT( !! client );
	_dispatcher.register_file_descriptor_handler( client, call( &HServer::handler_message, this, _1, _2 ), IO_EVENT_TYPE::READ );
	clog << green << "new connection" << lightgray << endl;
	return;
	M_EPILOG
}

void HServer::handler_message( HIODispatcher::stream_t& stream_, IO_EVENT_TYPE ) {
	M_PROLOG
	HString message;
	if ( !! stream_ ) {
		int long nRead( 0 );
		clog << "reading data ..." << endl;
		if ( ( nRead = stream_->read_until( message ) ) > 0 ) {
			_buffer += message;
			clog << "<-" << message << endl;
			if ( message == "stop" ) {
				_event.signal();
				_signaled = true;
			}
		} else if ( ! nRead ) {
			disconnect_client( stream_ );
		}
		/* else nRead < 0 => REPEAT */
	}
	return;
	M_EPILOG
}

void HServer::disconnect_client( HIODispatcher::stream_t& client_ ) {
	M_PROLOG
	M_ASSERT( !! client_ );
	clog << "closing client connection ..." << endl;
	_dispatcher.unregister_file_descriptor_handler( client_ );
	clog << "client closed connection ..." << endl;
	return;
	M_EPILOG
}

HString const& HServer::buffer( void ) const {
	M_PROLOG
	return ( _buffer );
	M_EPILOG
}

void HServer::run( void ) {
	HThread::set_name( "tut::HSocket(serv)" );
	try {
		try {
			clog << "starting dispatcher ..." << endl;
			_dispatcher.run();
			clog << "dispatcher finished ..." << endl;
			_socket->close();
			clog << "socket closed ..." << endl;
		} catch ( HOpenSSLException& e ) {
			clog << e.what() << endl;
		}
	} catch ( HSocketException& e ) {
		_thread.stack_exception( e.what(), e.code() );
	} catch ( ... ) {
		_thread.stack_exception( "unknown exception", errno );
	}
	if ( ! _signaled ) {
		_event.signal();
		_signaled = true;
	}
	return;
}

void HServer::do_not_signal( void ) {
	_signaled = true;
}

TUT_UNIT_TEST( "Simple construction and destruction." )
	HSocket socket;
	ENSURE_EQUALS ( "uninitialized socket has port", socket.get_port(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructions with wrong parameters." )
	ENSURE_THROW( "creation of bad socket possible (TYPE::FILE|TYPE::NETWORK)",
			HSocket socket( HSocket::socket_type_t( HSocket::TYPE::FILE ) | HSocket::TYPE::NETWORK ),
			HSocketException );
	ENSURE_THROW( "creation of bad socket possible (TYPE::BLOCKING|TYPE::NONBLOCKING)",
			HSocket socket( HSocket::socket_type_t( HSocket::TYPE::BLOCKING ) | HSocket::TYPE::NONBLOCKING ),
			HSocketException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Getting port on file socket." )
	HSocket socket( HSocket::TYPE::FILE );
	ENSURE_THROW( "getting port number on file socket possible", socket.get_port(), HSocketException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Listening on reserved port." )
	HSocket socket( HSocket::TYPE::NETWORK, 1 );
	ENSURE_THROW( "listening on reserved port possible",
			socket.listen( "0.0.0.0", ( ::getenv( "windir" ) || ::getenv( "WINDIR" ) ? 135 : 22 ) ),
			HSocketException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Listening on port in use." )
	HSocket block( HSocket::TYPE::NETWORK, 1 );
	block.listen( "0.0.0.0", OBSCURE_PORT );
	HSocket socket( HSocket::TYPE::NETWORK, 1 );
	ENSURE_THROW( "listening on port in use possible", socket.listen( "0.0.0.0", OBSCURE_PORT ), HSocketException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Listening on existing file." )
	HSocket socket( HSocket::TYPE::FILE, 1 );
	ENSURE_THROW( "listening on existing file possible", socket.listen( "/etc/shadow" ), HSocketException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Listening on protected file." )
	HSocket socket( HSocket::TYPE::FILE, 1 );
	ENSURE_THROW( "listening on protected file possible", socket.listen( "/etc/TUT_socket" ), HSocketException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Listening on already listening socket." )
	HSocket socket( HSocket::TYPE::FILE, 1 );
	socket.listen( "/tmp/TUT_socket" );
	ENSURE_THROW( "listening on already listening socket possible", socket.listen( "/tmp/TUT_socket" ), HSocketException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Listening with bad maximum number of clients." )
	HSocket socket( HSocket::TYPE::FILE );
	ENSURE_THROW( "listening with bad maximum number of clients possible", socket.listen( "/tmp/TUT_socket" ), HSocketException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Accept on socket that is not listening." )
	HSocket socket;
	ENSURE_THROW( "accept on socket that is not listening possible", socket.accept(), HSocketException );
TUT_TEARDOWN()

void tut_yaal_hcore_hsocket::play_scenario( HSocket::socket_type_t type_,
		HString const& path_, int port_, bool withSsl_,
		bool nonBlockingServer_, bool nonBlockingClient_ ) {
	char test_data[] = "Ala ma kota." "\n" "A kot ma mleczko." "\n" "Even more data to..." "\n" "...read" "\n" "stop";
	char test_exp[]  = "Ala ma kota."      "A kot ma mleczko."      "Even more data to..."      "...read"      "stop";
	TUT_DECLARE( HServer serv( type_ | HSocket::TYPE::SERVER | ( withSsl_ ? HSocket::TYPE::SSL : HSocket::TYPE::DEFAULT ) | ( nonBlockingServer_ ? HSocket::TYPE::NONBLOCKING : HSocket::TYPE::DEFAULT ), 1 ); );
	TUT_INVOKE( clog << sizeof ( serv ) << endl; );
	TUT_DECLARE( HSocket client( type_ | HSocket::TYPE::CLIENT | ( withSsl_ ? HSocket::TYPE::SSL : HSocket::TYPE::DEFAULT ) | ( nonBlockingClient_ ? HSocket::TYPE::NONBLOCKING : HSocket::TYPE::DEFAULT ) ); );
	TUT_INVOKE( serv.listen( path_, port_ ); );
	try {
		TUT_INVOKE( serv.start(); );
		TUT_INVOKE( client.connect( path_, port_ ); );
		TUT_EVAL( client.write( test_data, static_cast<int>( sizeof ( test_data ) ) ) );
		client.flush();
		TUT_INVOKE( serv.wait(); );
	} catch ( HOpenSSLException const& e ) {
		clog << e.what() << endl;
		serv.do_not_signal();
		TUT_INVOKE( serv.stop(); );
		throw;
	} catch ( HSocketException const& e ) {
		clog << e.what() << endl;
		serv.do_not_signal();
		TUT_INVOKE( serv.stop(); );
		throw;
	} catch ( ... ) {
		serv.do_not_signal();
		TUT_INVOKE( serv.stop(); );
		throw;
	}
	TUT_INVOKE( serv.stop(); );
	ENSURE_EQUALS( "data broken during transfer", serv.buffer(), test_exp );
	clog << serv.buffer() << endl;
	return;
}

TUT_UNIT_TEST( "Transfering data through file (blocking)." )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, false, false, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through file (non-blocking)." )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, false, true, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through file (blocking server, nonblocking client)." )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, false, false, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through file (non-blocking server, blocking client)." )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, false, true, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through file with SSL. (blocking)" )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, true, false, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through file with SSL (non-blocking)." )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, true, false, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through file with SSL. (blocking server, nonblocking client)" )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, true, false, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through file with SSL (non-blocking server, blocking client)." )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, true, true, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through network (blocking)." )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", OBSCURE_PORT, false, false, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through network (non-blocking)." )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", OBSCURE_PORT, false, true, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through network (blocking server, nonblocking client)." )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", OBSCURE_PORT, false, false, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through network (non-blocking server, blocking client)." )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", OBSCURE_PORT, false, true, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through network with SSL. (blocking)" )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", OBSCURE_PORT, true, false, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through network wiht SSL (non-blocking)." )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", OBSCURE_PORT, true, true, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through network with SSL. (blocking server, nonblocking client)" )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", OBSCURE_PORT, true, false, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Transfering data through network wiht SSL (non-blocking server, blocking client)." )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", OBSCURE_PORT, true, true, false );
TUT_TEARDOWN()

}

