/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.c - this file is integral part of `tress' project.

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

#include "header"
M_VCSID ( "$CVSHeader: tress/src/tut_yaal_hcore_hsocket.c,v 1.4 2006/01/24 11:51:47 amok Exp $" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal_hcore_hsocket
	{
	};

typedef test_group < tut_yaal_hcore_hsocket > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hsocket_group ( "yaal::hcore::HSocket" );

/* Simple construction and destruction. */
template < >
template < >
void module::test<1> ( void )
	{
	HSocket l_oSocket;
	ensure_equals ( "uninitialized socket has port", l_oSocket.get_port ( ), 0 );
	}

/* Constructions with wrong parameters. */
template < >
template < >
void module::test<2> ( void )
	{
	try
		{
		HSocket l_oSocket ( HSocket::D_FILE | HSocket::D_NETWORK );
		fail ( "creation of bad socket possible (D_FILE|D_NETWORK)" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	try
		{
		HSocket l_oSocket ( HSocket::D_BLOCKING | HSocket::D_NONBLOCKING );
		fail ( "creation of bad socket possible (D_BLOCKING|D_NONBLOCKING)" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Getting port on file socket. */
template < >
template < >
void module::test<3> ( void )
	{
	HSocket l_oSocket ( HSocket::D_FILE );
	try
		{
		l_oSocket.get_port ( );
		fail ( "getting port number on file socket possible" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Listening on reserved port. */
template < >
template < >
void module::test<4> ( void )
	{
	HSocket l_oSocket ( HSocket::D_NETWORK, 1 );
	try
		{
		l_oSocket.listen ( "0.0.0.0", 22 );
		fail ( "listening on reserved port possible" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Listening on existing file. */
template < >
template < >
void module::test<5> ( void )
	{
	HSocket l_oSocket ( HSocket::D_FILE, 1 );
	try
		{
		l_oSocket.listen ( "/etc/shadow" );
		fail ( "listening on existing file possible" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Listening on protected file. */
template < >
template < >
void module::test<6> ( void )
	{
	HSocket l_oSocket ( HSocket::D_FILE, 1 );
	try
		{
		l_oSocket.listen ( "/etc/TUT_socket" );
		fail ( "listening on protected file possible" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Listening on already listening socket. */
template < >
template < >
void module::test<7> ( void )
	{
	HSocket l_oSocket ( HSocket::D_FILE, 1 );
	l_oSocket.listen ( "/tmp/TUT_socket" );
	try
		{
		l_oSocket.listen ( "/tmp/TUT_socket" );
		fail ( "listening on already listening socket possible" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Listening with bad maximum number of clients. */
template < >
template < >
void module::test<8> ( void )
	{
	HSocket l_oSocket ( HSocket::D_FILE );
	try
		{
		l_oSocket.listen ( "/tmp/TUT_socket" );
		fail ( "listening with bad maximum number of clients possible" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Accept on socket that is not listening. */
template < >
template < >
void module::test<9> ( void )
	{
	HSocket l_oSocket;
	try
		{
		l_oSocket.accept ( );
		fail ( "accept on socket that is not listening possible" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Transfering data through file. */
template < >
template < >
void module::test<20> ( void )
	{
	char test_data [ ] = "Ala ma kota.";
	const int size = sizeof ( test_data );
	char reciv_buffer [ size + 1 ];
	HSocket l_oServer ( HSocket::D_FILE, 1 );
	HSocket l_oClient ( HSocket::D_FILE );
	l_oServer.listen ( "/tmp/TUT_socket" );
	l_oClient.connect ( "/tmp/TUT_socket" );
	HSocket * l_poLocal = l_oServer.accept ( );
	l_oClient.write ( test_data, size );
	l_poLocal->read ( reciv_buffer, size );
	reciv_buffer [ size ] = 0;
	ensure_equals ( "data broken during transfer", string ( reciv_buffer ), string ( test_data ) );
	cout << reciv_buffer << endl;
	}

/* Transfering data through network. */
template < >
template < >
void module::test<21> ( void )
	{
	char test_data [ ] = "A kot ma wpierdol.";
	const int size = sizeof ( test_data );
	char reciv_buffer [ size + 1 ];
	HSocket l_oServer ( HSocket::D_NETWORK, 1 );
	HSocket l_oClient ( HSocket::D_NETWORK );
	l_oServer.listen ( "0.0.0.0", 5555 );
	l_oClient.connect ( "127.0.0.1", 5555 );
	HSocket * l_poLocal = l_oServer.accept ( );
	l_oClient.write ( test_data, size );
	l_poLocal->read ( reciv_buffer, size );
	reciv_buffer [ size ] = 0;
	ensure_equals ( "data broken during transfer", string ( reciv_buffer ), string ( test_data ) );
	cout << reciv_buffer << endl;
	}

}
