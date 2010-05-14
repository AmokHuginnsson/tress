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
#include <unistd.h>
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

namespace tut
{

struct tut_yaal_hcore_hsocket
	{
	tut_yaal_hcore_hsocket( void )
		{
		::unlink( "/tmp/TUT_socket" );
		errno = 0;
		}
	virtual ~tut_yaal_hcore_hsocket( void )
		{}
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_hsocket, "yaal::hcore::HSocket" );

struct HServer
	{
	static int const NO_FD = 17;
	static int const LATENCY = 1;
	HString _buffer;
	HProcess _dispatcher;
	HSocket _socket;
	HThread _thread;
	HEvent _event;
	HServer( HSocket::socket_type_t, int );
public:
	void start( void );
	void stop( void );
  void listen( yaal::hcore::HString const&, int const = 0 );
	HString const& buffer( void ) const;
	void* run( void );
	void wait( void );
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
	_thread(), _event()
	{}

void HServer::listen( yaal::hcore::HString const& path_, int const port_ )
	{
	M_PROLOG
	_socket.listen( path_, port_ );
	cout << "listening on: " << path_ << ( port_ ? ":" : "" ) << ( port_ ? HString( port_ ) : HString() ) << endl;
	return;
	M_EPILOG
	}

void HServer::start( void )
	{
	M_PROLOG
	cout << "starting server thread ..." << endl;
	_dispatcher.register_file_descriptor_handler( _socket.get_file_descriptor(), bound_call( &HServer::handler_connection, this, _1 ) );
	_thread.spawn( bound_call( &HServer::run, this ) );
	return;
	M_EPILOG
	}

void HServer::stop( void )
	{
	M_PROLOG
	_dispatcher.stop();
	_thread.finish();
	cout << "server thread stopped ..." << endl;
	return;
	M_EPILOG
	}

void HServer::wait( void )
	{
	M_PROLOG
	_event.wait();
	return;
	M_EPILOG
	}

void HServer::handler_connection( int )
	{
	M_PROLOG
	HSocket::ptr_t client = _socket.accept();
	M_ASSERT( !! client );
	int fd = client->get_file_descriptor();
	_dispatcher.register_file_descriptor_handler( fd, bound_call( &HServer::handler_message, this, _1 ) );
	cout << green << "new connection" << lightgray << endl;
	return;
	M_EPILOG
	}

void HServer::handler_message( int fileDescriptor_ )
	{
	M_PROLOG
	HString message;
	HSocket::ptr_t client = _socket.get_client( fileDescriptor_ );
	if ( !! client )
		{
		int long nRead( 0 );
		if ( ( nRead = client->read_until( message ) ) > 0 )
			{
			_buffer += message;
			cout << "<-" << message << endl;
			_event.signal();
			}
		else if ( ! nRead )
			disconnect_client( client );
		/* else nRead < 0 => REPEAT */
		}
	return;
	M_EPILOG
	}

void HServer::disconnect_client( yaal::hcore::HSocket::ptr_t& client_ )
	{
	M_PROLOG
	M_ASSERT( !! client_ );
	int fileDescriptor = client_->get_file_descriptor();
	_dispatcher.unregister_file_descriptor_handler( fileDescriptor );
	_socket.shutdown_client( fileDescriptor );
	cout << "client closed connection" << endl;
	return;
	M_EPILOG
	}

HString const& HServer::buffer( void ) const
	{
	M_PROLOG
	return ( _buffer );
	M_EPILOG
	}

void* HServer::run( void )
	{
	try
		{
		cout << "starting dispatcher ..." << endl;
		_dispatcher.run();
		cout << "dispatcher finished ..." << endl;
		_socket.close();
		}
	catch ( HOpenSSLException& e )
		{
		cout << e.what() << endl;
		}
	return ( NULL );
	}

TUT_UNIT_TEST_N( 1, "/* Simple construction and destruction. */" )
	HSocket socket;
	ENSURE_EQUALS ( "uninitialized socket has port", socket.get_port(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Constructions with wrong parameters. */" )
	try
		{
		HSocket socket( HSocket::socket_type_t( HSocket::TYPE::FILE ) | HSocket::TYPE::NETWORK );
		FAIL( "creation of bad socket possible (TYPE::FILE|TYPE::NETWORK)" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	try
		{
		HSocket socket( HSocket::socket_type_t( HSocket::TYPE::BLOCKING ) | HSocket::TYPE::NONBLOCKING );
		FAIL( "creation of bad socket possible (TYPE::BLOCKING|TYPE::NONBLOCKING)" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* Getting port on file socket. */" )
	HSocket socket( HSocket::TYPE::FILE );
	try
		{
		socket.get_port();
		FAIL ( "getting port number on file socket possible" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Listening on reserved port. */" )
	HSocket socket ( HSocket::TYPE::NETWORK, 1 );
	try
		{
		socket.listen ( "0.0.0.0", 22 );
		FAIL ( "listening on reserved port possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Listening on existing file. */" )
	HSocket socket ( HSocket::TYPE::FILE, 1 );
	try
		{
		socket.listen ( "/etc/shadow" );
		FAIL ( "listening on existing file possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Listening on protected file. */" )
	HSocket socket ( HSocket::TYPE::FILE, 1 );
	try
		{
		socket.listen ( "/etc/TUT_socket" );
		FAIL ( "listening on protected file possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* Listening on already listening socket. */" )
	HSocket socket ( HSocket::TYPE::FILE, 1 );
	socket.listen ( "/tmp/TUT_socket" );
	try
		{
		socket.listen ( "/tmp/TUT_socket" );
		FAIL ( "listening on already listening socket possible" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* Listening with bad maximum number of clients. */" )
	HSocket socket ( HSocket::TYPE::FILE );
	try
		{
		socket.listen ( "/tmp/TUT_socket" );
		FAIL ( "listening with bad maximum number of clients possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* Accept on socket that is not listening. */" )
	HSocket socket;
	try
		{
		socket.accept();
		FAIL ( "accept on socket that is not listening possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 19, "/* Transfering data through file. */" )
	char test_data[] = "Ala ma kota.";
	const int size = sizeof ( test_data );
	TUT_DECLARE( HServer serv( HSocket::TYPE::FILE, 1 ); );
	TUT_INVOKE( cout << sizeof ( serv ) << endl; );
	TUT_DECLARE( HSocket client( HSocket::TYPE::FILE ); );
	TUT_INVOKE( serv.listen( "/tmp/TUT_socket" ); );
	TUT_INVOKE( serv.start(); );
	TUT_INVOKE( client.connect( "/tmp/TUT_socket" ); );
	TUT_INVOKE( client.write( test_data, size ); );
	TUT_INVOKE( serv.wait(); );
	TUT_INVOKE( serv.stop(); );
	ENSURE_EQUALS( "data broken during transfer", serv.buffer(), test_data );
	cout << serv.buffer() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 20, "Transfering data through file with SSL." )
	char test_data[] = "Ala ma kota.";
	const int size = sizeof ( test_data );
	TUT_DECLARE( HServer serv( HSocket::socket_type_t( HSocket::TYPE::FILE ) | HSocket::TYPE::SSL_SERVER, 1 ); );
	TUT_DECLARE( HSocket client( HSocket::socket_type_t( HSocket::TYPE::FILE ) | HSocket::TYPE::SSL_CLIENT ); );
	TUT_INVOKE( serv.listen( "/tmp/TUT_socket" ); );
	TUT_INVOKE( serv.start(); );
	TUT_INVOKE( client.connect( "/tmp/TUT_socket" ); );
	TUT_INVOKE( client.write( test_data, size ); );
	TUT_INVOKE( serv.wait(); );
	TUT_INVOKE( serv.stop(); );
	ENSURE_EQUALS( "data broken during transfer", serv.buffer(), test_data );
	cout << serv.buffer() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 21, "/* Transfering data through network. */" )
	char test_data[] = "A kot ma wpierdol.";
	const int size = sizeof ( test_data );
	TUT_DECLARE( HServer serv( HSocket::TYPE::NETWORK, 1 ); );
	TUT_DECLARE( HSocket client( HSocket::TYPE::NETWORK ); );
	TUT_INVOKE( serv.listen( "127.0.0.1", 5555 ); );
	TUT_INVOKE( serv.start(); );
	TUT_INVOKE( client.connect( "127.0.0.1", 5555 ); );
	TUT_INVOKE( client.write( test_data, size ); );
	TUT_INVOKE( serv.wait(); );
	TUT_INVOKE( serv.stop(); );
	ENSURE_EQUALS( "data broken during transfer", serv.buffer(), test_data );
	cout << serv.buffer() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 22, "Transfering data through network with SSL." )
	char test_data[] = "A kot ma wpierdol.";
	const int size = sizeof ( test_data );
	TUT_DECLARE( HServer serv( HSocket::socket_type_t( HSocket::TYPE::NETWORK ) | HSocket::TYPE::SSL_SERVER, 1 ); );
	TUT_DECLARE( HSocket client( HSocket::socket_type_t( HSocket::TYPE::NETWORK ) | HSocket::TYPE::SSL_CLIENT ); );
	TUT_INVOKE( serv.listen( "0.0.0.0", 5555 ); );
	TUT_INVOKE( serv.start(); );
	TUT_INVOKE( client.connect( "127.0.0.1", 5555 ); );
	TUT_INVOKE( client.write( test_data, size ); );
	TUT_INVOKE( serv.wait(); );
	TUT_INVOKE( serv.stop(); );
	ENSURE_EQUALS( "data broken during transfer", serv.buffer(), test_data );
	cout << serv.buffer() << endl;
TUT_TEARDOWN()

}
