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

struct tut_yaal_hcore_hstreaminterface : public tress::tut_helpers::simple_mock<tut_yaal_hcore_hstreaminterface> {
	HSynchronizedStream _ss;
	tut_yaal_hcore_hstreaminterface( void )
		: _ss( make_pointer<HStringStream>() ) {
	}
	virtual ~tut_yaal_hcore_hstreaminterface( void ) {
	}
	yaal::hcore::HString data( void ) {
		HString s;
		_ss.read_until( s );
		return ( s );
	}
};
TUT_TEST_GROUP( tut_yaal_hcore_hstreaminterface, "yaal::hcore::HStreamInterface" );

TUT_UNIT_TEST( "manipulators" )
	int i( 7 );
	_ss << "i = '" << i << "'" << endl;
	ENSURE_EQUALS( "plain int", data(), "i = '7'" );
	_ss << "i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	ENSURE_EQUALS( "setw() int", data(), "i = '    7' \tsetw( 5 )" );
	_ss << "i = '" << setfill( '0' ) << i << "'" << " \tsetfill( '0' )" << endl;
	ENSURE_EQUALS( "setfill() int", data(), "i = '7' \tsetfill( '0' )" );
	_ss << "i = '" << setfill( '0' ) << setw( 5 ) << i << "'" << " \tsetfill( '0' ), setw( 5 )" << endl;
	ENSURE_EQUALS( "setfill() setw() int", data(), "i = '00007' \tsetfill( '0' ), setw( 5 )" );
	_ss << "i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	ENSURE_EQUALS( "setw() int", data(), "i = '00007' \tsetw( 5 )" );
	_ss << "i = '" << setfill( '0' ) << i << "'" << " \tsetfill( '0' )" << endl;
	ENSURE_EQUALS( "setfill() int", data(), "i = '7' \tsetfill( '0' )" );
	int k( 103 );
	_ss << "k = '" << k << "'" << endl;
	ENSURE_EQUALS( "dec int", data(), "k = '103'" );
	_ss << "k = '" << hex << k << "' \thex" << endl;
	ENSURE_EQUALS( "dec int hex", data(), "k = '67' \thex" );
	_ss << "k = '" << k << "'" << endl;
	ENSURE_EQUALS( "dec int", data(), "k = '67'" );
	_ss << dec;
	_ss << "k = '" << k << "'" << endl;
	ENSURE_EQUALS( "dec int", data(), "k = '103'" );
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

TUT_UNIT_TEST( "outputs" )
	HStringStream ss;
	ss << 3.141592653589793L;
	ENSURE_EQUALS( "double long output failed", ss.string(), "3.14159265359" );
	ss.clear();
	ss << 3.14159;
	ENSURE_EQUALS( "double output failed", ss.string(), "3.14159" );
	ss.clear();
	ss << 3.14f;
	ENSURE_EQUALS( "float output failed", ss.string(), "3.14" );
	ss.clear();
	ss << 18446744073709551615ULL;
	ENSURE_EQUALS( "unsigned long long int output failed", ss.string(), "18446744073709551615" );
	ss.clear();
	ss << 4294967295UL;
	ENSURE_EQUALS( "unsigned long int output failed", ss.string(), "4294967295" );
	ss.clear();
	ss << static_cast<char unsigned>( 'a' );
	ENSURE_EQUALS( "char unsigned output failed", ss.string(), "a" );
TUT_TEARDOWN()

}

