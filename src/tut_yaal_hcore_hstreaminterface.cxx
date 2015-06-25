/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hstreaminterface.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.hpp>

#include <yaal/hcore/hstreaminterface.hxx>
#include <yaal/tools/hmemory.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hstreaminterface );
TUT_TEST_GROUP( tut_yaal_hcore_hstreaminterface, "yaal::hcore::HStreamInterface" );

TUT_UNIT_TEST( "manipulators" )
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

TUT_UNIT_TEST( "read_until (delims stripped)" )
	static char data[] = "Ala\nma\nkota.";
	HMemoryObserver mo( data, static_cast<int>( sizeof( data ) ) - 1 );
	HMemory m( mo );
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

TUT_UNIT_TEST( "read_until (delims not stripped)" )
	static char data[] = "Ala\nma\nkota.";
	HMemoryObserver mo( data, static_cast<int>( sizeof( data ) ) - 1 );
	HMemory m( mo );
	HString line;
	int long nRead( 0 );
	nRead = m.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "Ala\n" );
	nRead = m.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "ma\n" );
	nRead = m.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_until_n (delim stripped, by delim)" )
	static char data[] = "Ala\nma\nkota.";
	HMemoryObserver mo( data, static_cast<int>( sizeof( data ) ) - 1 );
	HMemory m( mo );
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

TUT_UNIT_TEST( "read_until_n (delim stripped, by size)" )
	static char data[] = "Ala\nma\nkota.";
	HMemoryObserver mo( data, static_cast<int>( sizeof( data ) ) - 1 );
	HMemory m( mo );
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

TUT_UNIT_TEST( "read_until_n (delim not stripped, by delim)" )
	static char data[] = "Ala\nma\nkota.";
	HMemoryObserver mo( data, static_cast<int>( sizeof( data ) ) - 1 );
	HMemory m( mo );
	HString line;
	int long nRead( 0 );
	nRead = m.read_until_n( line, 4, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "Ala\n" );
	nRead = m.read_until_n( line, 3, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "ma\n" );
	nRead = m.read_until_n( line, 5, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_until_n (delim not stripped, by size)" )
	static char data[] = "Ala\nma\nkota.";
	HMemoryObserver mo( data, static_cast<int>( sizeof( data ) ) - 1 );
	HMemory m( mo );
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

TUT_UNIT_TEST( "input float" )
	static char data[] = "3.1415 -2.7182";
	HMemoryObserver mo( data, static_cast<int>( sizeof( data ) ) - 1 );
	HMemory m( mo );
	float val( 0 );
	m >> val;
	ENSURE_DISTANCE( "float value read fail", val, static_cast<float>( 3.1415 ), static_cast<float>( epsilon ) );
	m >> val;
	ENSURE_DISTANCE( "float negative value read fail", val, static_cast<float>( -2.7182 ), static_cast<float>( epsilon ) );
TUT_TEARDOWN()

}

