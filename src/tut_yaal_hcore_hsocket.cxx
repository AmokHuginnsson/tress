/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID( "$Id: "__ID__" $" )

using namespace tut;
using namespace std;
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
	};

typedef test_group < tut_yaal_hcore_hsocket > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hsocket_group ( "yaal::hcore::HSocket" );

struct OServer : public HThread
	{
	int f_iSize;
	char* f_pcBuffer;
	HSocket::ptr_t f_oSocket;
protected:
	virtual int run( void );
	};

int OServer::run( void )
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

/* Simple construction and destruction. */
template<>
template<>
void module::test<1> ( void )
	{
	HSocket l_oSocket;
	ensure_equals ( "uninitialized socket has port", l_oSocket.get_port(), 0 );
	}

/* Constructions with wrong parameters. */
template<>
template<>
void module::test<2> ( void )
	{
	try
		{
		HSocket l_oSocket( HSocket::TYPE::D_FILE | HSocket::TYPE::D_NETWORK );
		fail( "creation of bad socket possible (TYPE::D_FILE|TYPE::D_NETWORK)" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	try
		{
		HSocket l_oSocket( HSocket::TYPE::D_BLOCKING | HSocket::TYPE::D_NONBLOCKING );
		fail( "creation of bad socket possible (TYPE::D_BLOCKING|TYPE::D_NONBLOCKING)" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	}

/* Getting port on file socket. */
template<>
template<>
void module::test<3> ( void )
	{
	HSocket l_oSocket( HSocket::TYPE::D_FILE );
	try
		{
		l_oSocket.get_port();
		fail ( "getting port number on file socket possible" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	}

/* Listening on reserved port. */
template<>
template<>
void module::test<4> ( void )
	{
	HSocket l_oSocket ( HSocket::TYPE::D_NETWORK, 1 );
	try
		{
		l_oSocket.listen ( "0.0.0.0", 22 );
		fail ( "listening on reserved port possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
	}

/* Listening on existing file. */
template<>
template<>
void module::test<5> ( void )
	{
	HSocket l_oSocket ( HSocket::TYPE::D_FILE, 1 );
	try
		{
		l_oSocket.listen ( "/etc/shadow" );
		fail ( "listening on existing file possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
	}

/* Listening on protected file. */
template<>
template<>
void module::test<6> ( void )
	{
	HSocket l_oSocket ( HSocket::TYPE::D_FILE, 1 );
	try
		{
		l_oSocket.listen ( "/etc/TUT_socket" );
		fail ( "listening on protected file possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
	}

/* Listening on already listening socket. */
template<>
template<>
void module::test<7> ( void )
	{
	HSocket l_oSocket ( HSocket::TYPE::D_FILE, 1 );
	l_oSocket.listen ( "/tmp/TUT_socket" );
	try
		{
		l_oSocket.listen ( "/tmp/TUT_socket" );
		fail ( "listening on already listening socket possible" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	}

/* Listening with bad maximum number of clients. */
template<>
template<>
void module::test<8> ( void )
	{
	HSocket l_oSocket ( HSocket::TYPE::D_FILE );
	try
		{
		l_oSocket.listen ( "/tmp/TUT_socket" );
		fail ( "listening with bad maximum number of clients possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
	}

/* Accept on socket that is not listening. */
template<>
template<>
void module::test<9> ( void )
	{
	HSocket l_oSocket;
	try
		{
		l_oSocket.accept();
		fail ( "accept on socket that is not listening possible" );
		}
	catch ( HException & e )
		{
		cout << e.what() << endl;
		}
	}

/* Transfering data through file. */
template<>
template<>
void module::test<19> ( void )
	{
	char test_data[] = "Ala ma kota.";
	const int size = sizeof ( test_data );
	char reciv_buffer[ size + 1 ];
	HSocket l_oServer( HSocket::TYPE::D_FILE, 1 );
	HSocket l_oClient( HSocket::TYPE::D_FILE );
	l_oServer.listen( "/tmp/TUT_socket" );
	l_oClient.connect( "/tmp/TUT_socket" );
	HSocket::ptr_t l_oLocal = l_oServer.accept();
	l_oClient.write( test_data, size );
	l_oLocal->read( reciv_buffer, size );
	reciv_buffer[ size ] = 0;
	ensure_equals( "data broken during transfer", string( reciv_buffer ), string( test_data ) );
	cout << reciv_buffer << endl;
	}

TUT_UNIT_TEST_N( 20, "Transfering data through file with SSL." )
	char test_data[] = "Ala ma kota.";
	const int size = sizeof ( test_data );
	char reciv_buffer[ size + 1 ];
	HSocket l_oServer( HSocket::TYPE::D_FILE | HSocket::TYPE::D_SSL_SERVER, 1 );
	HSocket l_oClient( HSocket::TYPE::D_FILE | HSocket::TYPE::D_SSL_CLIENT );
	l_oServer.listen( "/tmp/TUT_socket" );
	l_oClient.connect( "/tmp/TUT_socket" );
	OServer serv;
	serv.f_oSocket = l_oServer.accept();
	serv.f_pcBuffer = reciv_buffer;
	serv.f_iSize = size;
	serv.spawn();
	l_oClient.write( test_data, size );
	l_oClient.close();
	serv.finish();
	reciv_buffer[ size ] = 0;
	ensure_equals( "data broken during transfer", string( reciv_buffer ), string( test_data ) );
	cout << reciv_buffer << endl;
TUT_TEARDOWN()

/* Transfering data through network. */
template<>
template<>
void module::test<21> ( void )
	{
	char test_data [ ] = "A kot ma wpierdol.";
	const int size = sizeof ( test_data );
	char reciv_buffer [ size + 1 ];
	HSocket l_oServer ( HSocket::TYPE::D_NETWORK, 1 );
	HSocket l_oClient ( HSocket::TYPE::D_NETWORK );
	l_oServer.listen ( "0.0.0.0", 5555 );
	l_oClient.connect ( "127.0.0.1", 5555 );
	HSocket::ptr_t l_oLocal = l_oServer.accept();
	l_oClient.write ( test_data, size );
	l_oLocal->read( reciv_buffer, size );
	reciv_buffer [ size ] = 0;
	ensure_equals ( "data broken during transfer", string ( reciv_buffer ), string ( test_data ) );
	cout << reciv_buffer << endl;
	}

TUT_UNIT_TEST_N( 22, "Transfering data through network with SSL." )
	char test_data [ ] = "A kot ma wpierdol.";
	const int size = sizeof ( test_data );
	char reciv_buffer [ size + 1 ];
	HSocket l_oServer ( HSocket::TYPE::D_NETWORK | HSocket::TYPE::D_SSL_SERVER, 1 );
	HSocket l_oClient ( HSocket::TYPE::D_NETWORK | HSocket::TYPE::D_SSL_CLIENT );
	l_oServer.listen ( "0.0.0.0", 5555 );
	l_oClient.connect ( "127.0.0.1", 5555 );
	OServer serv;
	serv.f_oSocket = l_oServer.accept();
	serv.f_pcBuffer = reciv_buffer;
	serv.f_iSize = size;
	serv.spawn();
	l_oClient.write ( test_data, size );
	l_oClient.close();
	serv.finish();
	reciv_buffer [ size ] = 0;
	ensure_equals ( "data broken during transfer", string ( reciv_buffer ), string ( test_data ) );
	cout << reciv_buffer << endl;
TUT_TEARDOWN()

}
