/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hsocket.cxx - this file is integral part of `tress' project.

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
#include <cstdlib>
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

struct tut_yaal_hcore_hsocket {
	tut_yaal_hcore_hsocket( void ) {
		::unlink( "/tmp/TUT_socket" );
		errno = 0;
	}
	virtual ~tut_yaal_hcore_hsocket( void )
		{}
};

TUT_TEST_GROUP( tut_yaal_hcore_hsocket, "yaal::hcore::HSocket" );

struct HServer {
	static int const NO_FD = 17;
	static int const LATENCY = 1000; /* number of miliseconds */
	HString _buffer;
	HIODispatcher _dispatcher;
	HSocket _socket;
	HThread _thread;
	HEvent _event;
	bool _signaled;
	HServer( HSocket::socket_type_t, int );
public:
	void start( void );
	void stop( void );
  void listen( yaal::hcore::HString const&, int const = 0 );
	HString const& buffer( void ) const;
	void* run( void );
	void wait( void );
	void do_not_signal( void );
private:
	void handler_connection( int );
	void handler_message( int );
	void disconnect_client( yaal::hcore::HSocket::ptr_t& );
	HServer( HServer const& );
	HServer& operator = ( HServer const& );
};

HServer::HServer( HSocket::socket_type_t type_, int maxConn_ )
	: _buffer(),
	_dispatcher( NO_FD, LATENCY ), _socket( type_, maxConn_ ),
	_thread(), _event(), _signaled( false )
	{}

void HServer::listen( yaal::hcore::HString const& path_, int const port_ ) {
	M_PROLOG
	_socket.listen( path_, port_ );
	cout << "listening on: " << path_ << ( port_ ? ":" : "" ) << ( port_ ? HString( port_ ) : HString() ) << endl;
	return;
	M_EPILOG
}

void HServer::start( void ) {
	M_PROLOG
	cout << "starting server thread ..." << endl;
	_dispatcher.register_file_descriptor_handler( _socket.get_file_descriptor(), call( &HServer::handler_connection, this, _1 ) );
	_thread.spawn( call( &HServer::run, this ) );
	return;
	M_EPILOG
}

void HServer::stop( void ) {
	M_PROLOG
	_dispatcher.stop();
	_thread.finish();
	cout << "server thread stopped ..." << endl;
	return;
	M_EPILOG
}

void HServer::wait( void ) {
	M_PROLOG
	cout << "waiting for event ..." << endl;
	_event.wait();
	cout << "event arrived ..." << endl;
	return;
	M_EPILOG
}

void HServer::handler_connection( int ) {
	M_PROLOG
	HSocket::ptr_t client = _socket.accept();
	M_ASSERT( !! client );
	int fd = client->get_file_descriptor();
	_dispatcher.register_file_descriptor_handler( fd, call( &HServer::handler_message, this, _1 ) );
	cout << green << "new connection" << lightgray << endl;
	return;
	M_EPILOG
}

void HServer::handler_message( int fileDescriptor_ ) {
	M_PROLOG
	HString message;
	HSocket::ptr_t client = _socket.get_client( fileDescriptor_ );
	if ( !! client ) {
		int long nRead( 0 );
		cout << "reading data ..." << endl;
		if ( ( nRead = client->read_until( message ) ) > 0 ) {
			_buffer += message;
			cout << "<-" << message << endl;
			_event.signal();
			_signaled = true;
		} else if ( ! nRead )
			disconnect_client( client );
		/* else nRead < 0 => REPEAT */
	}
	return;
	M_EPILOG
}

void HServer::disconnect_client( yaal::hcore::HSocket::ptr_t& client_ ) {
	M_PROLOG
	M_ASSERT( !! client_ );
	cout << "closing client connection ..." << endl;
	int fileDescriptor = client_->get_file_descriptor();
	_dispatcher.unregister_file_descriptor_handler( fileDescriptor );
	_socket.shutdown_client( fileDescriptor );
	cout << "client closed connection ..." << endl;
	return;
	M_EPILOG
}

HString const& HServer::buffer( void ) const {
	M_PROLOG
	return ( _buffer );
	M_EPILOG
}

void* HServer::run( void ) {
	try {
		try {
			cout << "starting dispatcher ..." << endl;
			_dispatcher.run();
			cout << "dispatcher finished ..." << endl;
			_socket.close();
			cout << "socket closed ..." << endl;
		} catch ( HOpenSSLException& e ) {
			cout << e.what() << endl;
		}
	} catch ( HException& e ) {
		_thread.stack_exception( e.what(), e.code() );
	} catch ( ... ) {
		_thread.stack_exception( "unknown exception", errno );
	}
	if ( ! _signaled ) {
		_event.signal();
		_signaled = true;
	}
	return ( NULL );
}

void HServer::do_not_signal( void ) {
	_signaled = true;
}

TUT_UNIT_TEST( 1, "Simple construction and destruction." )
	HSocket socket;
	ENSURE_EQUALS ( "uninitialized socket has port", socket.get_port(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Constructions with wrong parameters." )
	try {
		HSocket socket( HSocket::socket_type_t( HSocket::TYPE::FILE ) | HSocket::TYPE::NETWORK );
		FAIL( "creation of bad socket possible (TYPE::FILE|TYPE::NETWORK)" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
	try {
		HSocket socket( HSocket::socket_type_t( HSocket::TYPE::BLOCKING ) | HSocket::TYPE::NONBLOCKING );
		FAIL( "creation of bad socket possible (TYPE::BLOCKING|TYPE::NONBLOCKING)" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "Getting port on file socket." )
	HSocket socket( HSocket::TYPE::FILE );
	try {
		socket.get_port();
		FAIL( "getting port number on file socket possible" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "Listening on reserved port." )
	HSocket socket( HSocket::TYPE::NETWORK, 1 );
	try {
		socket.listen( "0.0.0.0", ( ::getenv( "windir" ) || ::getenv( "WINDIR" ) ? 135 : 22 ) );
		FAIL( "listening on reserved port possible" );
	} catch ( HException & e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "Listening on port in use." )
	int const obscurePort( 61928 );
	HSocket block( HSocket::TYPE::NETWORK, 1 );
	block.listen( "0.0.0.0", obscurePort );
	HSocket socket( HSocket::TYPE::NETWORK, 1 );
	try {
		socket.listen( "0.0.0.0", obscurePort );
		FAIL( "listening on port in use possible" );
	} catch ( HException & e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "Listening on existing file." )
	HSocket socket( HSocket::TYPE::FILE, 1 );
	try {
		socket.listen( "/etc/shadow" );
		FAIL( "listening on existing file possible" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "Listening on protected file." )
	HSocket socket( HSocket::TYPE::FILE, 1 );
	try {
		socket.listen( "/etc/TUT_socket" );
		FAIL( "listening on protected file possible" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "Listening on already listening socket." )
	HSocket socket( HSocket::TYPE::FILE, 1 );
	socket.listen( "/tmp/TUT_socket" );
	try {
		socket.listen( "/tmp/TUT_socket" );
		FAIL( "listening on already listening socket possible" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "Listening with bad maximum number of clients." )
	HSocket socket( HSocket::TYPE::FILE );
	try {
		socket.listen( "/tmp/TUT_socket" );
		FAIL( "listening with bad maximum number of clients possible" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "Accept on socket that is not listening." )
	HSocket socket;
	try {
		socket.accept();
		FAIL( "accept on socket that is not listening possible" );
	} catch ( HException & e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

void play_scenario( HSocket::socket_type_t type_, HString const& path_, int port_ = 0, bool withSsl_ = false ) {
	char test_data[] = "Ala ma kota.";
	const int size = sizeof ( test_data );
	TUT_DECLARE( HServer serv( type_ | ( withSsl_ ? HSocket::TYPE::SSL_SERVER : HSocket::TYPE::DEFAULT ), 1 ); );
	TUT_INVOKE( cout << sizeof ( serv ) << endl; );
	TUT_DECLARE( HSocket client( type_ | ( withSsl_ ? HSocket::TYPE::SSL_CLIENT : HSocket::TYPE::DEFAULT ) ); );
	TUT_INVOKE( serv.listen( path_, port_ ); );
	try {
		TUT_INVOKE( serv.start(); );
		TUT_INVOKE( client.connect( path_, port_ ); );
		TUT_INVOKE( client.write( test_data, size ); );
		TUT_INVOKE( serv.wait(); );
	} catch ( HException const& e ) {
		cout << e.what() << endl;
		serv.do_not_signal();
		TUT_INVOKE( serv.stop(); );
		throw;
	} catch ( ... ) {
		serv.do_not_signal();
		TUT_INVOKE( serv.stop(); );
		throw;
	}
	TUT_INVOKE( serv.stop(); );
	ENSURE_EQUALS( "data broken during transfer", serv.buffer(), test_data );
	cout << serv.buffer() << endl;
	return;
}

TUT_UNIT_TEST( 19, "Transfering data through file (blocking)." )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "Transfering data through file (non-blocking)." )
	play_scenario( HSocket::socket_type_t( HSocket::TYPE::DEFAULT ) | HSocket::TYPE::FILE | HSocket::TYPE::NONBLOCKING, "/tmp/TUT_socket" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 21, "Transfering data through file with SSL." )
	play_scenario( HSocket::TYPE::FILE, "/tmp/TUT_socket", 0, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "Transfering data through network (blocking)." )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", 5555 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 23, "Transfering data through network (non-blocking)." )
	play_scenario( HSocket::socket_type_t( HSocket::TYPE::DEFAULT ) | HSocket::TYPE::NETWORK | HSocket::TYPE::NONBLOCKING, "127.0.0.1", 5555 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "Transfering data through network with SSL." )
	play_scenario( HSocket::TYPE::NETWORK, "127.0.0.1", 5555, true );
TUT_TEARDOWN()

}
