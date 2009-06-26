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

#define STEP( code ) do { cout << "executing: " << #code << "... " << flush; { code; } cout << " ok." << endl; } while( 0 )

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

struct OServer
	{
	typedef HThreadT<OServer> thread_t;
	int f_iSize;
	char* f_pcBuffer;
	HSocket::ptr_t f_oSocket;
	thread_t f_oThread;
	OServer( void ) : f_iSize( 0 ), f_pcBuffer( NULL ), f_oSocket(), f_oThread( *this ) {}
public:
	void start( void )
		{ f_oThread.spawn(); }
	void stop( void )
		{ f_oThread.finish(); }
	int operator()( thread_t const* const );
private:
	OServer( OServer const& );
	OServer& operator = ( OServer const& );
	};

int OServer::operator()( thread_t const* const )
	{
	int ret = -1;
	try
		{
		ret = static_cast<int>( f_oSocket->read( f_pcBuffer, f_iSize ) );
		f_oSocket->close();
		}
	catch ( HOpenSSLException& e )
		{
		cout << e.what() << endl;
		}
	return ( ret );
	}

TUT_UNIT_TEST_N( 1, "/* Simple construction and destruction. */" )
	HSocket l_oSocket;
	ENSURE_EQUALS ( "uninitialized socket has port", l_oSocket.get_port(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Constructions with wrong parameters. */" )
	try
		{
		HSocket l_oSocket( HSocket::socket_type_t( HSocket::TYPE::FILE ) | HSocket::TYPE::NETWORK );
		FAIL( "creation of bad socket possible (TYPE::FILE|TYPE::NETWORK)" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	try
		{
		HSocket l_oSocket( HSocket::socket_type_t( HSocket::TYPE::BLOCKING ) | HSocket::TYPE::NONBLOCKING );
		FAIL( "creation of bad socket possible (TYPE::BLOCKING|TYPE::NONBLOCKING)" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* Getting port on file socket. */" )
	HSocket l_oSocket( HSocket::TYPE::FILE );
	try
		{
		l_oSocket.get_port();
		FAIL ( "getting port number on file socket possible" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Listening on reserved port. */" )
	HSocket l_oSocket ( HSocket::TYPE::NETWORK, 1 );
	try
		{
		l_oSocket.listen ( "0.0.0.0", 22 );
		FAIL ( "listening on reserved port possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Listening on existing file. */" )
	HSocket l_oSocket ( HSocket::TYPE::FILE, 1 );
	try
		{
		l_oSocket.listen ( "/etc/shadow" );
		FAIL ( "listening on existing file possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Listening on protected file. */" )
	HSocket l_oSocket ( HSocket::TYPE::FILE, 1 );
	try
		{
		l_oSocket.listen ( "/etc/TUT_socket" );
		FAIL ( "listening on protected file possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* Listening on already listening socket. */" )
	HSocket l_oSocket ( HSocket::TYPE::FILE, 1 );
	l_oSocket.listen ( "/tmp/TUT_socket" );
	try
		{
		l_oSocket.listen ( "/tmp/TUT_socket" );
		FAIL ( "listening on already listening socket possible" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* Listening with bad maximum number of clients. */" )
	HSocket l_oSocket ( HSocket::TYPE::FILE );
	try
		{
		l_oSocket.listen ( "/tmp/TUT_socket" );
		FAIL ( "listening with bad maximum number of clients possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* Accept on socket that is not listening. */" )
	HSocket l_oSocket;
	try
		{
		l_oSocket.accept();
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
	char reciv_buffer[ size + 1 ];
	HSocket l_oServer( HSocket::TYPE::FILE, 1 );
	HSocket l_oClient( HSocket::TYPE::FILE );
	l_oServer.listen( "/tmp/TUT_socket" );
	l_oClient.connect( "/tmp/TUT_socket" );
	HSocket::ptr_t l_oLocal = l_oServer.accept();
	l_oClient.write( test_data, size );
	l_oLocal->read( reciv_buffer, size );
	reciv_buffer[ size ] = 0;
	ENSURE_EQUALS( "data broken during transfer", std::string( reciv_buffer ), std::string( test_data ) );
	cout << reciv_buffer << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 20, "Transfering data through file with SSL." )
	char test_data[] = "Ala ma kota.";
	const int size = sizeof ( test_data );
	char reciv_buffer[ size + 1 ];
	HSocket l_oServer( HSocket::socket_type_t( HSocket::TYPE::FILE ) | HSocket::TYPE::SSL_SERVER, 1 );
	HSocket l_oClient( HSocket::socket_type_t( HSocket::TYPE::FILE ) | HSocket::TYPE::SSL_CLIENT );
	l_oServer.listen( "/tmp/TUT_socket" );
	l_oClient.connect( "/tmp/TUT_socket" );
	OServer serv;
	serv.f_oSocket = l_oServer.accept();
	serv.f_pcBuffer = reciv_buffer;
	serv.f_iSize = size;
	STEP( serv.start() );
	STEP( l_oClient.write( test_data, size ) );
	STEP( l_oClient.close() );
	STEP( serv.stop() );
	reciv_buffer[ size ] = 0;
	ENSURE_EQUALS( "data broken during transfer", std::string( reciv_buffer ), std::string( test_data ) );
	cout << reciv_buffer << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 21, "/* Transfering data through network. */" )
	char test_data[] = "A kot ma wpierdol.";
	const int size = sizeof ( test_data );
	char reciv_buffer[ size + 1 ];
	HSocket l_oServer( HSocket::TYPE::NETWORK, 1 );
	HSocket l_oClient( HSocket::TYPE::NETWORK );
	l_oServer.listen( "0.0.0.0", 5555 );
	l_oClient.connect( "127.0.0.1", 5555 );
	HSocket::ptr_t l_oLocal = l_oServer.accept();
	l_oClient.write( test_data, size );
	l_oLocal->read( reciv_buffer, size );
	reciv_buffer[ size ] = 0;
	ENSURE_EQUALS( "data broken during transfer", std::string( reciv_buffer ), std::string( test_data ) );
	cout << reciv_buffer << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 22, "Transfering data through network with SSL." )
	char test_data[] = "A kot ma wpierdol.";
	const int size = sizeof ( test_data );
	char reciv_buffer[ size + 1 ];
	HSocket l_oServer( HSocket::socket_type_t( HSocket::TYPE::NETWORK ) | HSocket::TYPE::SSL_SERVER, 1 );
	HSocket l_oClient( HSocket::socket_type_t( HSocket::TYPE::NETWORK ) | HSocket::TYPE::SSL_CLIENT );
	l_oServer.listen( "0.0.0.0", 5555 );
	l_oClient.connect( "127.0.0.1", 5555 );
	OServer serv;
	serv.f_oSocket = l_oServer.accept();
	serv.f_pcBuffer = reciv_buffer;
	serv.f_iSize = size;
	serv.start();
	l_oClient.write( test_data, size );
	l_oClient.close();
	serv.stop();
	reciv_buffer[ size ] = 0;
	ENSURE_EQUALS( "data broken during transfer", std::string( reciv_buffer ), std::string( test_data ) );
	cout << reciv_buffer << endl;
TUT_TEARDOWN()

}
