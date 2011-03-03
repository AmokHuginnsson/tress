/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hstreaminterface.cxx - this file is integral part of `tress' project.

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

TUT_SIMPLE_MOCK( tut_yaal_hcore_hstreaminterface );
TUT_TEST_GROUP_N( tut_yaal_hcore_hstreaminterface, "yaal::hcore::HStreamInterface" );

TUT_UNIT_TEST_N( 1, "manipulators" )
	int i( 7 );
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setfill( '0' ) << i << "'" << " \tsetfill( '0' )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setfill( '0' ) << setw( 5 ) << i << "'" << " \tsetfill( '0' ), setw( 5 )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	cout << "[M] i = '" << setfill( '0' ) << i << "'" << " \tsetfill( '0' )" << endl;
	cout << "[O] i = '" << i << "'" << endl;
	int k( 103 );
	cout << "[O] k = '" << k << "'" << endl;
	cout << "[M] k = '" << hex << k << "' \thex" << endl;
	cout << "[O] k = '" << k << "'" << endl;
	cout << dec;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "read_until (delims stripped)" )
	static char data[] = "Ala\nma\nkota.";
	HMemory m( data, sizeof( data ) - 1 );
	HString line;
	int long nRead( 0 );
	nRead = m.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = m.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = m.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "read_until (delims not stripped)" )
	static char data[] = "Ala\nma\nkota.";
	HMemory m( data, sizeof( data ) - 1 );
	HString line;
	int long nRead( 0 );
	nRead = m.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = m.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	char sink;
	m.read( &sink, 1 );
	nRead = m.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = m.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	m.read( &sink, 1 );
	nRead = m.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "read_until_n (delim stripped, by delim)" )
	static char data[] = "Ala\nma\nkota.";
	HMemory m( data, sizeof( data ) - 1 );
	HString line;
	int long nRead( 0 );
	nRead = m.read_until_n( line, 4 );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = m.read_until_n( line, 3 );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = m.read_until_n( line, 5 );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "read_until_n (delim stripped, by size)" )
	static char data[] = "Ala\nma\nkota.";
	HMemory m( data, sizeof( data ) - 1 );
	HString line;
	int long nRead( 0 );
	nRead = m.read_until_n( line, 3 );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = m.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 0 );
	nRead = m.read_until_n( line, 2 );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = m.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 0 );
	nRead = m.read_until_n( line, 5 );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "read_until_n (delim not stripped, by delim)" )
	static char data[] = "Ala\nma\nkota.";
	HMemory m( data, sizeof( data ) - 1 );
	HString line;
	int long nRead( 0 );
	nRead = m.read_until_n( line, 4, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = m.read_until_n( line, 3, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	char sink( 0 );
	m.read( &sink, 1 );
	nRead = m.read_until_n( line, 3, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = m.read_until_n( line, 5, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	m.read( &sink, 1 );
	nRead = m.read_until_n( line, 5, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "read_until_n (delim not stripped, by size)" )
	static char data[] = "Ala\nma\nkota.";
	HMemory m( data, sizeof( data ) - 1 );
	HString line;
	int long nRead( 0 );
	nRead = m.read_until_n( line, 3, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = m.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 0 );
	nRead = m.read_until_n( line, 2, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = m.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 0 );
	nRead = m.read_until_n( line, 5, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

}

