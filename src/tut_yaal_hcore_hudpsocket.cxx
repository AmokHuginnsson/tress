/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hudpsocket.cxx - this file is integral part of `tress' project.

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

#include <cstdio>
#include <cstdlib>
#include <TUT/tut.hpp>

#include <yaal/hcore/hudpsocket.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"
#include <yaal/hcore/hopenssl.hxx>
#include <yaal/tools/hiodispatcher.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hudpsocket : simple_mock<tut_yaal_hcore_hudpsocket> {
	typedef simple_mock<tut_yaal_hcore_hudpsocket> base_type;
	/* TCP socekt uses 61928, + 1 to avoid conflict in parallel execution. */
	static int const OBSCURE_PORT = 61929;
	tut_yaal_hcore_hudpsocket( void ) {
		errno = 0;
	}
	virtual ~tut_yaal_hcore_hudpsocket( void )
		{}
};

TUT_TEST_GROUP( tut_yaal_hcore_hudpsocket, "yaal::hcore::HUDPSocket" );

struct HUDPServer {
	static int const NO_FD = 17;
	static int const LATENCY = 1000; /* number of miliseconds */
	HString _buffer;
	HIODispatcher _dispatcher;
	HUDPSocket _socket;
	HThread _thread;
	HEvent _event;
	bool _signaled;
	HUDPServer( HUDPSocket::socket_type_t );
public:
	void start( void );
	void stop( void );
  void bind( int, ip_t );
	HString const& buffer( void ) const;
	void* run( void );
	void wait( void );
	void do_not_signal( void );
private:
	void handler_message( int );
	HUDPServer( HUDPServer const& );
	HUDPServer& operator = ( HUDPServer const& );
};

HUDPServer::HUDPServer( HUDPSocket::socket_type_t type_ )
	: _buffer(),
	_dispatcher( NO_FD, LATENCY ), _socket( type_ ),
	_thread(), _event(), _signaled( false )
	{}

void HUDPServer::bind( int port_, ip_t ip_ ) {
	M_PROLOG
	_socket.bind( port_, ip_ );
	cout << "bound to: " << resolver::ip_to_string( ip_ ) << ":" << port_ << endl;
	return;
	M_EPILOG
}

void HUDPServer::start( void ) {
	M_PROLOG
	cout << "starting server thread ..." << endl;
	_dispatcher.register_file_descriptor_handler( _socket.get_file_descriptor(), call( &HUDPServer::handler_message, this, _1 ) );
	_thread.spawn( call( &HUDPServer::run, this ) );
	return;
	M_EPILOG
}

void HUDPServer::stop( void ) {
	M_PROLOG
	_dispatcher.stop();
	_thread.finish();
	cout << "server thread stopped ..." << endl;
	return;
	M_EPILOG
}

void HUDPServer::wait( void ) {
	M_PROLOG
	cout << "waiting for event ..." << endl;
	_event.wait();
	cout << "event arrived ..." << endl;
	return;
	M_EPILOG
}

void HUDPServer::handler_message( int ) {
	M_PROLOG
	ODatagram datagram( 100 );
	cout << "reading data ..." << endl;
	int long nRead( _socket.receive( datagram ) );
	if ( nRead > 0 ) {
		_buffer += datagram._data.get<char>();
		cout << "<-" << datagram._data.get<char>() << endl;
		_event.signal();
		_signaled = true;
	} /* else nRead < 0 => REPEAT */
	return;
	M_EPILOG
}

HString const& HUDPServer::buffer( void ) const {
	M_PROLOG
	return ( _buffer );
	M_EPILOG
}

void* HUDPServer::run( void ) {
	HThread::set_name( "tut::HUDPocket(serv)" );
	try {
		try {
			cout << "starting dispatcher ..." << endl;
			_dispatcher.run();
			cout << "dispatcher finished ..." << endl;
		} catch ( HOpenSSLException& e ) {
			cout << e.what() << endl;
		}
	} catch ( HUDPSocketException& e ) {
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

void HUDPServer::do_not_signal( void ) {
	_signaled = true;
}

TUT_UNIT_TEST( 1, "Simple construction and destruction." )
	HUDPSocket socket;
	ENSURE( "udp socket without fd created", socket.get_file_descriptor() >= 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Constructions with wrong parameters." )
	try {
		HUDPSocket socket( HUDPSocket::socket_type_t( HUDPSocket::TYPE::BLOCKING ) | HUDPSocket::TYPE::NONBLOCKING );
		FAIL( "creation of bad socket possible (TYPE::BLOCKING|TYPE::NONBLOCKING)" );
	} catch ( HUDPSocketException const& e ) {
		cout << e.what() << endl;
	}
	try {
		HUDPSocket socket( HUDPSocket::socket_type_t( HUDPSocket::TYPE::SSL ) | HUDPSocket::TYPE::PLAIN );
		FAIL( "creation of bad socket possible (TYPE::BLOCKING|TYPE::NONBLOCKING)" );
	} catch ( HUDPSocketException const& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "bind on reserved port." )
	try {
		HUDPSocket socket( ( ::getenv( "windir" ) || ::getenv( "WINDIR" ) ? 137 : 22 ) );
		FAIL( "bind on reserved port possible" );
	} catch ( HUDPSocketException const& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "bind on port in use." )
	int const obscurePort( 61928 );
	HUDPSocket block( obscurePort );
	try {
		HUDPSocket socket( obscurePort );
		FAIL( "bind on port in use possible" );
	} catch ( HUDPSocketException const& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

namespace {

void play_scenario( int port_, ip_t ip_, bool withSsl_, bool nonBlockingServer_, bool nonBlockingClient_ ) {
	char test_data[] = "Ala ma kota.";
	const int size = sizeof ( test_data );
	TUT_DECLARE( HUDPServer serv( HUDPSocket::socket_type_t( withSsl_ ? HUDPSocket::TYPE::SSL : HUDPSocket::TYPE::DEFAULT ) | ( nonBlockingServer_ ? HUDPSocket::TYPE::NONBLOCKING : HUDPSocket::TYPE::DEFAULT ) ); );
	TUT_INVOKE( cout << sizeof ( serv ) << endl; );
	TUT_DECLARE( HUDPSocket client( HUDPSocket::socket_type_t( withSsl_ ? HUDPSocket::TYPE::SSL : HUDPSocket::TYPE::DEFAULT ) | ( nonBlockingClient_ ? HUDPSocket::TYPE::NONBLOCKING : HUDPSocket::TYPE::DEFAULT ) ); );
	TUT_INVOKE( serv.bind( port_, ip_ ); );
	try {
		TUT_INVOKE( serv.start(); );
		TUT_INVOKE( client.send_to( ip_, port_, test_data, size ); );
		TUT_INVOKE( serv.wait(); );
	} catch ( HUDPSocketException const& e ) {
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

}

TUT_UNIT_TEST( 19, "Transfering data through network (blocking)." )
	play_scenario( OBSCURE_PORT, ip_t( 127, 0, 0, 1 ), false, false, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "Transfering data through network (non-blocking)." )
	play_scenario( OBSCURE_PORT, ip_t( 127, 0, 0, 1 ), false, true, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 21, "Transfering data through network (blocking server, nonblocking client)." )
	play_scenario( OBSCURE_PORT, ip_t( 127, 0, 0, 1 ), false, false, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "Transfering data through network (non-blocking server, blocking client)." )
	play_scenario( OBSCURE_PORT, ip_t( 127, 0, 0, 1 ), false, true, false );
TUT_TEARDOWN()

#if 0

TUT_UNIT_TEST( 23, "Transfering data through network with SSL. (blocking)" )
	play_scenario( OBSCURE_PORT, ip_t( 127, 0, 0, 1 ), true, false, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "Transfering data through network wiht SSL (non-blocking)." )
	play_scenario( OBSCURE_PORT, ip_t( 127, 0, 0, 1 ), true, true, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 25, "Transfering data through network with SSL. (blocking server, nonblocking client)" )
	play_scenario( OBSCURE_PORT, ip_t( 127, 0, 0, 1 ), true, false, true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 26, "Transfering data through network wiht SSL (non-blocking server, blocking client)." )
	play_scenario( OBSCURE_PORT, ip_t( 127, 0, 0, 1 ), true, true, false );
TUT_TEARDOWN()

#endif

}

