/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hnumber.cxx - this file is integral part of `tress' project.

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

#include <cstdlib>
#include <TUT/tut.hpp>

#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/hrandomizer.hxx>
#include <yaal/hcore/hcore.hxx>
#include <yaal/tools/hpipedchild.hxx>
#include <yaal/tools/hfsitem.hxx>
#include <yaal/tools/xmath.hxx>
#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hnumber : public simple_mock<tut_yaal_hcore_hnumber> {
	typedef simple_mock<tut_yaal_hcore_hnumber> base_type;
	static HString BC_PATH;
	HRandomizer _rnd;
	HPipedChild _bc;
	HString _cache;
	tut_yaal_hcore_hnumber( void );
	HString const& expand_leafs( HString const& );
	HString const& random_real( void );
	virtual ~tut_yaal_hcore_hnumber( void )
		{}
};

HString tut_yaal_hcore_hnumber::BC_PATH = ::getenv( "BC_PATH" ) ? ::getenv( "BC_PATH" ) : "/usr/bin/bc";

tut_yaal_hcore_hnumber::tut_yaal_hcore_hnumber( void )
	: _rnd( randomizer_helper::make_randomizer() ), _bc(), _cache() {
	set_env( "BC_LINE_LENGTH", "10000000" );
	HScopedValueReplacement<int> saveErrno( errno, 0 );
#ifdef __MSVCXX__
	char const WIN_BC_PATH[] = "..\\..\\..\\..\\usr\\windows\\bin\\bc.exe";
	char const WIN_BC_PATH_ALT[] = "..\\..\\..\\usr\\windows\\bin\\bc.exe";
#endif /* #ifdef __MSVCXX__ */
	char const SOLARIS_BC_PATH[] = "/opt/csw/bin/bc";
	char const FREEBSD_GNUBC_PATH[] = "/usr/local/bin/bc";
	if ( !! HFSItem( SOLARIS_BC_PATH ) )
		BC_PATH = SOLARIS_BC_PATH;
	else if ( !! HFSItem( FREEBSD_GNUBC_PATH ) )
		BC_PATH = FREEBSD_GNUBC_PATH;
#ifdef __MSVCXX__
	else if ( !! HFSItem( WIN_BC_PATH ) )
		BC_PATH = WIN_BC_PATH;
	else if ( !! HFSItem( WIN_BC_PATH_ALT ) )
		BC_PATH = WIN_BC_PATH_ALT;
#endif /* #ifdef __MSVCXX__ */
	return;
}


HString const& tut_yaal_hcore_hnumber::random_real( void ) {
	int integralPart( static_cast<int>( _rnd( 40 ) ) );
	int decimalPart( static_cast<int>( _rnd( 40 ) ) );
	_cache = "0";
	if ( integralPart || decimalPart ) {
		_cache.clear();
		if ( _rnd() % 2 )
			_cache += '-';
		for ( int i( 0 ); i < integralPart; ++ i )
			_cache += ( _rnd() % 10 );
		if ( decimalPart > 0 ) {
			_cache += '.';
			for ( int i( 0 ); i < decimalPart; ++ i )
				_cache += ( _rnd() % 10 );
		}
		if ( _cache.find_other_than( "-.0" ) == HString::npos )
			_cache = "0";
	}
	return ( _cache );
}

HString const& tut_yaal_hcore_hnumber::expand_leafs( HString const& template_ ) {
	_cache.clear();
	static HString zeros( "00000000", HNumber::DECIMAL_DIGITS_IN_LEAF - 1 );
	_cache.hs_realloc( template_.get_length() * HNumber::DECIMAL_DIGITS_IN_LEAF + 1 );
	for ( HString::const_iterator it( template_.begin() ), end( template_.end() ); it != end; ++ it ) {
		_cache += *it;
		if ( ( *it != '-' ) && ( *it != '.' ) )
			_cache += zeros;
	}
	return ( _cache );
}

TUT_TEST_GROUP( tut_yaal_hcore_hnumber, "yaal::hcore::HNumber" );

TUT_UNIT_TEST( 1, "default constructor / check default precision" )
	HNumber n;
	ENSURE_EQUALS( "bad default number", n.to_string(), "0" );
	ENSURE_EQUALS( "bad dafault precision", n.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << n.to_string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "construct from double" )
	HNumber n( 3.14159265 );
	ENSURE_EQUALS( "number not created correctly", n.to_string(), "3.14159265" );
	ENSURE_EQUALS( "bad dafault precision", n.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << n.to_string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "construct from double and specify precision / get precision" )
	int const P1 = 20;
	HNumber n( 3.14159265, P1 );
	ENSURE_EQUALS( "number not created correctly", n.to_string(), "3.14159265" );
	ENSURE_EQUALS( "bad specified precision", n.get_precision(), P1 );
	cout << n.to_string() << endl;
	int const M = 16;
	int const P2 = 4;
	HNumber n2( 3.14159265, P2 );
	ENSURE_EQUALS( "bad precision (shall be at least hardcoded minimum)", n2.get_precision(), M );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "construct from string" )
	char const* const pn0 = "3.14159265";
	HNumber n0( pn0 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0 );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try {
		HNumber n( "" );
		FAIL( "empty number created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "-" );
		FAIL( "number that is a minus created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "." );
		FAIL( "number that is a dot created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "-." );
		FAIL( "number that is a minus-dot created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "-..1" );
		FAIL( "number that is a minus-dot created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "..1" );
		FAIL( "number that is a minus-dot created" );
	} catch ( HException& ) {
		// ok
	}

	char const* const pn1 = "-1";
	HNumber n1( pn1 );
	ENSURE_EQUALS( "number not created correctly", n1.to_string(), pn1 );
	ENSURE_EQUALS( "bad dafault precision", n1.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2 = ".5";
	char const* const pn2e = "0.5";
	HNumber n2( pn2 );
	ENSURE_EQUALS( "number not created correctly", n2.to_string(), pn2e );
	ENSURE_EQUALS( "bad dafault precision", n2.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3 = "-.7";
	char const* const pn3e = "-0.7";
	HNumber n3( pn3 );
	ENSURE_EQUALS( "number not created correctly", n3.to_string(), pn3e );
	ENSURE_EQUALS( "bad dafault precision", n3.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4 = "-2.7";
	HNumber n4( pn4 );
	ENSURE_EQUALS( "number not created correctly", n4.to_string(), pn4 );
	ENSURE_EQUALS( "bad dafault precision", n4.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try {
		HNumber nx( "--2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	try {
		HNumber nx( "..27" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	try {
		HNumber nx( "-.-2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	char const* const pn5 = ".2.7";
	HNumber n5( pn5 );
	ENSURE_EQUALS( "number not created correctly", n5.to_string(), "0.2" );
	ENSURE_EQUALS( "bad dafault precision", n5.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	char const* const pn6 = "2.7.44";
	HNumber n6( pn6 );
	ENSURE_EQUALS( "number not created correctly", n6.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n6.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n6 =" << n6.to_string() << " |" << endl;

	char const* const pn7 = "7-44";
	HNumber n7( pn7 );
	ENSURE_EQUALS( "number not created correctly", n7.to_string(), "7" );
	ENSURE_EQUALS( "bad dafault precision", n7.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n7 =" << n7.to_string() << " |" << endl;

	char const* const pn8 = "2.7.44";
	HNumber n8( pn8 );
	ENSURE_EQUALS( "number not created correctly", n8.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n8.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n8 =" << n8.to_string() << " |" << endl;

	char const* const pn9 = "2.700.566-7576-7657";
	HNumber n9( pn9 );
	ENSURE_EQUALS( "number not created correctly", n9.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n9.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n9 =" << n9.to_string() << " |" << endl;
	ENSURE_EQUALS( "number 0 not created correctly", HNumber( "0001200" ).to_string(), "1200" );
	ENSURE_EQUALS( "number 1 not created correctly", HNumber( "-00.200" ).to_string(), "-0.2" );
	ENSURE_EQUALS( "number 2 not created correctly", HNumber( "-00100" ).to_string(), "-100" );
	ENSURE_EQUALS( "number 3 not created correctly", HNumber( "00012.3200" ).to_string(), "12.32" );
	ENSURE_EQUALS( "number 4 not created correctly", HNumber( "-000034.212000" ).to_string(), "-34.212" );
	ENSURE_EQUALS( "number 5 not created correctly", HNumber( "-000" ).to_string(), "0" );
	ENSURE_EQUALS( "number 6 not created correctly", HNumber( "000" ).to_string(), "0" );
	ENSURE_EQUALS( "number 7 not created correctly", HNumber( ".000" ).to_string(), "0" );
	ENSURE_EQUALS( "number 8 not created correctly", HNumber( "000." ).to_string(), "0" );
	ENSURE_EQUALS( "number 9 not created correctly", HNumber( "00.000" ).to_string(), "0" );
	ENSURE_EQUALS( "number 10 not created correctly", HNumber( "-.000" ).to_string(), "0" );
	ENSURE_EQUALS( "number 11 not created correctly", HNumber( "-000.00" ).to_string(), "0" );
	ENSURE_EQUALS( "number 12 not created correctly", HNumber( "-000." ).to_string(), "0" );
	ENSURE_EQUALS( "number 1 5 not created correctly", HNumber( "-0001" ).to_string(), "-1" );
	ENSURE_EQUALS( "number 1 6 not created correctly", HNumber( "0001" ).to_string(), "1" );
	ENSURE_EQUALS( "number 1 7 not created correctly", HNumber( ".0001" ).to_string(), "0.0001" );
	ENSURE_EQUALS( "number 1 8 not created correctly", HNumber( "000.1" ).to_string(), "0.1" );
	ENSURE_EQUALS( "number 1 9 not created correctly", HNumber( "00.0001" ).to_string(), "0.0001" );
	ENSURE_EQUALS( "number 1 10 not created correctly", HNumber( "-.0001" ).to_string(), "-0.0001" );
	ENSURE_EQUALS( "number 1 11 not created correctly", HNumber( "-000.001" ).to_string(), "-0.001" );
	ENSURE_EQUALS( "number 1 12 not created correctly", HNumber( "-0001." ).to_string(), "-1" );
	/* long numbers */
	char const* const lns0 = "12345678901234567890";
	HNumber ln0( lns0 );
	ENSURE_EQUALS( "number ln0 not created correctly", ln0.to_string(), lns0 );

	char const* const lns1 = "-12345678901234567890";
	HNumber ln1( lns1 );
	ENSURE_EQUALS( "number ln1 not created correctly", ln1.to_string(), lns1 );

	char const* const lns2 = "1234567890123456789000000";
	HNumber ln2( lns2 );
	ENSURE_EQUALS( "number ln2 not created correctly", ln2.to_string(), lns2 );

	char const* const lns3 = "-1234567890123456789000000";
	HNumber ln3( lns3 );
	ENSURE_EQUALS( "number ln3 not created correctly", ln3.to_string(), lns3 );

	char const* const lns4 = "1000000000000000000000000";
	HNumber ln4( lns4 );
	ENSURE_EQUALS( "number ln4 not created correctly", ln4.to_string(), lns4 );

	char const* const lns4b = "0.0000000000000000000000001";
	HNumber ln4b( lns4b );
	ENSURE_EQUALS( "number ln4b not created correctly", ln4b.to_string(), lns4b );

	char const* const lns5 = "-1000000000000000000000000";
	HNumber ln5( lns5 );
	ENSURE_EQUALS( "number ln5 not created correctly", ln5.to_string(), lns5 );


	char const* const lns10 = "12345678901234567890.12345678901234567890";
	char const* const lns10r = "12345678901234567890.1234567890123456789";
	HNumber ln10( lns10 );
	ENSURE_EQUALS( "number ln10 not created correctly", ln10.to_string(), lns10r );

	char const* const lns11 = "-12345678901234567890.12345678901234567890";
	char const* const lns11r = "-12345678901234567890.1234567890123456789";
	HNumber ln11( lns11 );
	ENSURE_EQUALS( "number ln11 not created correctly", ln11.to_string(), lns11r );

	char const* const lns12 = "1234567890123456789000000.12345678901234567890";
	char const* const lns12r = "1234567890123456789000000.1234567890123456789";
	HNumber ln12( lns12 );
	ENSURE_EQUALS( "number ln12 not created correctly", ln12.to_string(), lns12r );

	char const* const lns13 = "-1234567890123456789000000.12345678901234567890";
	char const* const lns13r = "-1234567890123456789000000.1234567890123456789";
	HNumber ln13( lns13 );
	ENSURE_EQUALS( "number ln13 not created correctly", ln13.to_string(), lns13r );

	char const* const lns14 = "1000000000000000000000000.12345678901234567890";
	char const* const lns14r = "1000000000000000000000000.1234567890123456789";
	HNumber ln14( lns14 );
	ENSURE_EQUALS( "number ln14 not created correctly", ln14.to_string(), lns14r );

	char const* const lns15 = "-1000000000000000000000000.12345678901234567890";
	char const* const lns15r = "-1000000000000000000000000.1234567890123456789";
	HNumber ln15( lns15 );
	ENSURE_EQUALS( "number ln15 not created correctly", ln15.to_string(), lns15r );

	char const* const lns16 = "12345678901234567890.000000000001234";
	HNumber ln16( lns16 );
	ENSURE_EQUALS( "number ln16 not created correctly", ln16.to_string(), lns16 );

	char const* const lns17 = "12345678901234567890.00000000000123456789";
	HNumber ln17( lns17 );
	ENSURE_EQUALS( "number ln17 not created correctly", ln17.to_string(), lns17 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "construct from string (prefixes)" )
	char const* const pn0 = "???3.14159265";
	HNumber n0( pn0 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0 + 3 );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try {
		HNumber n( "???" );
		FAIL( "empty number created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "$$$-" );
		FAIL( "number that is a minus created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "???." );
		FAIL( "number that is a dot created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "$$$-." );
		FAIL( "number that is a minus-dot created" );
	} catch ( HException& ) {
		// ok
	}

	char const* const pn1 = "$$$-1";
	HNumber n1( pn1 );
	ENSURE_EQUALS( "number not created correctly", n1.to_string(), pn1 + 3 );
	ENSURE_EQUALS( "bad dafault precision", n1.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2 = "???.5";
	HNumber n2( pn2 );
	ENSURE_EQUALS( "number not created correctly", n2.to_string(), "0.5" );
	ENSURE_EQUALS( "bad dafault precision", n2.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3 = "$$$-.7";
	HNumber n3( pn3 );
	ENSURE_EQUALS( "number not created correctly", n3.to_string(), "-0.7" );
	ENSURE_EQUALS( "bad dafault precision", n3.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4 = "$$$-2.7";
	HNumber n4( pn4 );
	ENSURE_EQUALS( "number not created correctly", n4.to_string(), pn4 + 3 );
	ENSURE_EQUALS( "bad dafault precision", n4.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try {
		HNumber nx( "$$$--2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	try {
		HNumber nx( "???..27" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	try {
		HNumber nx( "$$$-.-2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	char const* const pn5 = "???.2.7";
	HNumber n5( pn5 );
	ENSURE_EQUALS( "number not created correctly", n5.to_string(), "0.2" );
	ENSURE_EQUALS( "bad dafault precision", n5.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	char const* const pn6 = "???2.7.44";
	HNumber n6( pn6 );
	ENSURE_EQUALS( "number not created correctly", n6.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n6.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n6 =" << n6.to_string() << " |" << endl;

	char const* const pn7 = "???7-44";
	HNumber n7( pn7 );
	ENSURE_EQUALS( "number not created correctly", n7.to_string(), "7" );
	ENSURE_EQUALS( "bad dafault precision", n7.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n7 =" << n7.to_string() << " |" << endl;

	char const* const pn8 = "???2.7.44";
	HNumber n8( pn8 );
	ENSURE_EQUALS( "number not created correctly", n8.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n8.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n8 =" << n8.to_string() << " |" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "construct from string (postfixes)" )
	char const* const pn0ok = "3.14159265";
	char const* const pn0 = "3.14159265???";
	HNumber n0( pn0 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0ok );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try {
		HNumber n( "???" );
		FAIL( "empty number created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "-???" );
		FAIL( "number that is a minus created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( ".???" );
		FAIL( "number that is a dot created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "-.???" );
		FAIL( "number that is a minus-dot created" );
	} catch ( HException& ) {
		// ok
	}

	char const* const pn1ok = "-1";
	char const* const pn1 = "-1???";
	HNumber n1( pn1 );
	ENSURE_EQUALS( "number not created correctly", n1.to_string(), pn1ok );
	ENSURE_EQUALS( "bad dafault precision", n1.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2ok = "0.5";
	char const* const pn2 = ".5???";
	HNumber n2( pn2 );
	ENSURE_EQUALS( "number not created correctly", n2.to_string(), pn2ok );
	ENSURE_EQUALS( "bad dafault precision", n2.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3ok = "-0.7";
	char const* const pn3 = "-.7???";
	HNumber n3( pn3 );
	ENSURE_EQUALS( "number not created correctly", n3.to_string(), pn3ok );
	ENSURE_EQUALS( "bad dafault precision", n3.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4ok = "-2.7";
	char const* const pn4 = "-2.7???";
	HNumber n4( pn4 );
	ENSURE_EQUALS( "number not created correctly", n4.to_string(), pn4ok );
	ENSURE_EQUALS( "bad dafault precision", n4.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try {
		HNumber nx( "--2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	try {
		HNumber nx( "..27???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	try {
		HNumber nx( "-.-2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	char const* const pn5 = ".2.7???";
	HNumber n5( pn5 );
	ENSURE_EQUALS( "number not created correctly", n5.to_string(), "0.2" );
	ENSURE_EQUALS( "bad dafault precision", n5.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	char const* const pn6 = "2.7.44???";
	HNumber n6( pn6 );
	ENSURE_EQUALS( "number not created correctly", n6.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n6.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n6 =" << n6.to_string() << " |" << endl;

	char const* const pn7 = "7-44???";
	HNumber n7( pn7 );
	ENSURE_EQUALS( "number not created correctly", n7.to_string(), "7" );
	ENSURE_EQUALS( "bad dafault precision", n7.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n7 =" << n7.to_string() << " |" << endl;

	char const* const pn8 = "2.7.44???";
	HNumber n8( pn8 );
	ENSURE_EQUALS( "number not created correctly", n8.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n8.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n8 =" << n8.to_string() << " |" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "construct from string (prepostfixes)" )
	char const* const pn0ok = "3.14159265";
	char const* const pn0 = "???3.14159265???";
	HNumber n0( pn0 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0ok );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try {
		HNumber n( "???" );
		FAIL( "empty number created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "$$$-???" );
		FAIL( "number that is a minus created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "???.???" );
		FAIL( "number that is a dot created" );
	} catch ( HException& ) {
		// ok
	}
	try {
		HNumber n( "$$$-.???" );
		FAIL( "number that is a minus-dot created" );
	} catch ( HException& ) {
		// ok
	}

	char const* const pn1ok = "-1";
	char const* const pn1 = "$$$-1???";
	HNumber n1( pn1 );
	ENSURE_EQUALS( "number not created correctly", n1.to_string(), pn1ok );
	ENSURE_EQUALS( "bad dafault precision", n1.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2ok = "0.5";
	char const* const pn2 = "$$$.5???";
	HNumber n2( pn2 );
	ENSURE_EQUALS( "number not created correctly", n2.to_string(), pn2ok );
	ENSURE_EQUALS( "bad dafault precision", n2.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3ok = "-0.7";
	char const* const pn3 = "$$$-.7???";
	HNumber n3( pn3 );
	ENSURE_EQUALS( "number not created correctly", n3.to_string(), pn3ok );
	ENSURE_EQUALS( "bad dafault precision", n3.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4ok = "-2.7";
	char const* const pn4 = "$$$-2.7???";
	HNumber n4( pn4 );
	ENSURE_EQUALS( "number not created correctly", n4.to_string(), pn4ok );
	ENSURE_EQUALS( "bad dafault precision", n4.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try {
		HNumber nx( "$$$--2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	try {
		HNumber nx( "???..27???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	try {
		HNumber nx( "$$$-.-2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
	} catch ( HException& ) {
		// ok
	}

	char const* const pn5 = "???.2.7???";
	HNumber n5( pn5 );
	ENSURE_EQUALS( "number not created correctly", n5.to_string(), "0.2" );
	ENSURE_EQUALS( "bad dafault precision", n5.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	char const* const pn6 = "???2.7.44???";
	HNumber n6( pn6 );
	ENSURE_EQUALS( "number not created correctly", n6.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n6.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n6 =" << n6.to_string() << " |" << endl;

	char const* const pn7 = "???7-44???";
	HNumber n7( pn7 );
	ENSURE_EQUALS( "number not created correctly", n7.to_string(), "7" );
	ENSURE_EQUALS( "bad dafault precision", n7.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n7 =" << n7.to_string() << " |" << endl;

	char const* const pn8 = "???2.7.44???";
	HNumber n8( pn8 );
	ENSURE_EQUALS( "number not created correctly", n8.to_string(), "2.7" );
	ENSURE_EQUALS( "bad dafault precision", n8.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n8 =" << n8.to_string() << " |" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "construct from string and specify precision" )
	char const* const pn0 = "3.14159265";
	int const P1 = 20;
	HNumber n0( pn0, P1 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0 );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), P1 );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	int const M = 16;
	int const P2 = 4;
	HNumber n2( pn0, P2 );
	ENSURE_EQUALS( "bad precision (shall be at least hardcoded minimum)", n2.get_precision(), M );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "copy constructor" )
	HNumber n( 3.14159265 );
	ENSURE_EQUALS( "number not created correctly", n.to_string(), "3.14159265" );
	ENSURE_EQUALS( "bad dafault precision", n.get_precision(), HNumber::DEFAULT_PRECISION );
	HNumber copy( n );
	ENSURE_EQUALS( "number not created correctly", copy.to_string(), "3.14159265" );
	ENSURE_EQUALS( "bad dafault precision", copy.get_precision(), HNumber::DEFAULT_PRECISION );
	char const* const pn0 = "3.14159265";
	int const P1 = 20;
	HNumber n0( pn0, P1 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0 );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), P1 );
	HNumber copy0( n0 );
	ENSURE_EQUALS( "number not created correctly", copy0.to_string(), pn0 );
	ENSURE_EQUALS( "bad dafault precision", copy0.get_precision(), P1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "set/get precision" )
	HNumber n;
	int const M = 16;
	int const P = 20;
	int const S = 10;
	int const F = 12;
	ENSURE_EQUALS( "bad dafault precision", n.get_precision(), HNumber::DEFAULT_PRECISION );
	n.set_precision( P );
	ENSURE_EQUALS( "bad modified 1 precision", n.get_precision(), P );
	n.set_precision( HNumber::DEFAULT_PRECISION + P );
	ENSURE_EQUALS( "bad modified 2 precision", n.get_precision(), HNumber::DEFAULT_PRECISION + P );
	n.set_precision( HNumber::DEFAULT_PRECISION );
	ENSURE_EQUALS( "bad modified 3 precision", n.get_precision(), HNumber::DEFAULT_PRECISION );
	int const SAVED = HNumber::DEFAULT_PRECISION;
	HNumber::DEFAULT_PRECISION = S;
	n.set_precision( M );
	ENSURE_EQUALS( "bad modified 3 precision M", n.get_precision(), M );
	n.set_precision( S );
	ENSURE_EQUALS( "bad modified 3 precision SM", n.get_precision(), M );
	n = "10."
	"1212121212" "1212121212" "1212121212" "1212121212"
	"1212121212" "1212121212" "1212121212" "1212121212"
	"1212121212" "1212121212" "1212121212" "1212121212"
	"1212121212" "1212121212" "1212121212" "1212121212"
	"1212121212" "1212121212" "1212121212" "1212121";
	ENSURE_EQUALS( "bad precision from string", n.get_precision(), 197 + 1 ); /* numbers from strings are always is_exact() */
	n.set_precision( 100 );
	ENSURE_EQUALS( "bad modified 4 precision", n.get_precision(), 100 ); /* number was exact */
	HNumber numerator( "1" );
	HNumber denominator( "3" );
	HNumber division;
	numerator.set_precision( M );
	denominator.set_precision( M );
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculated 4 precision ( 1/3 )", division.get_precision(), M ); /* number was exact */
	division.set_precision( 100 );
	ENSURE_EQUALS( "bad modified 4 precision ( 1/3 )", division.get_precision(), M ); /* number was exact */

	HNumber s;
	ENSURE_EQUALS( "bad default minimum precision", s.get_precision(), M );
	n.set_precision( F );
	ENSURE_EQUALS( "bad modified precision", s.get_precision(), M );
	HNumber::DEFAULT_PRECISION = SAVED;
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "assignment operator" )
	char const* const p0 = "3.14159265";
	int const SAVED = HNumber::DEFAULT_PRECISION;
	HNumber::DEFAULT_PRECISION = 20;
	HNumber n( p0 );
	ENSURE_EQUALS( "number not created correctly", n.to_string(), p0 );
	HNumber copy;
	ENSURE_EQUALS( "number not created correctly", copy.to_string(), "0" );
	copy = n;
	ENSURE_EQUALS( "number not assigned correctly", copy.to_string(), p0 );
	HNumber another;
	another.set_precision( HNumber::DEFAULT_PRECISION + 5 );
	another = copy;
	ENSURE_EQUALS( "number not assigned correctly", another.to_string(), p0 );
	char const* const p1 = "17";
	HNumber next( p1 );
	next.set_precision( HNumber::DEFAULT_PRECISION + 5 );
	ENSURE_EQUALS( "number not created correctly", next.to_string(), p1 );
	ENSURE_EQUALS( "bad dafault precision", next.get_precision(), HNumber::DEFAULT_PRECISION + 5 );
	another = next;
	ENSURE_EQUALS( "number not created correctly", another.to_string(), p1 );
	ENSURE_EQUALS( "bad dafault precision", another.get_precision(), HNumber::DEFAULT_PRECISION + 5 );
	HNumber::DEFAULT_PRECISION = SAVED;
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "equality operator" )
	char const* const p0 = "3.14159265";
	char const* const p1 = "3.14159265";
	char const* const p2 = "3.141593";
	HNumber n0( p0 );
	HNumber n1( p1 );
	HNumber n2( p2 );
	ENSURE( "equality failed", n0 == n1 );
	ENSURE( "equality failed (not equal)", ! ( n0 == n2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "difference operator" )
	char const* const p0 = "3.14159265";
	char const* const p1 = "3.14159265";
	char const* const p2 = "3.141593";
	HNumber n0( p0 );
	HNumber n1( p1 );
	HNumber n2( p2 );
	ENSURE( "difference failed", n0 != n2 );
	ENSURE( "difference failed (equal)", ! ( n0 != n1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "lower then operator" )
	ENSURE( "lower failed a", HNumber( "-1" ) < HNumber( "1" ) );
	ENSURE( "lower failed b", HNumber( "-1" ) < HNumber( "0" ) );
	ENSURE( "lower failed c", HNumber( "-1" ) < HNumber( "-0.5" ) );
	ENSURE( "lower failed d", HNumber( "0" ) < HNumber( "0.5" ) );
	ENSURE( "lower failed e", HNumber( ".2" ) < HNumber( "0.5" ) );
	ENSURE( "lower failed f", HNumber( ".2" ) < HNumber( "1" ) );
	ENSURE( "lower failed f1", HNumber( ".123" ) < HNumber( ".1231" ) );
	ENSURE( "lower failed g", HNumber( "2.734543" ) < HNumber( "3.145" ) );
	ENSURE( "lower failed g1", HNumber( "0" ) < HNumber( "0.01" ) );

	ENSURE( "lower failed h", ! ( HNumber( "1" ) < HNumber( "-1" ) ) );
	ENSURE( "lower failed i", ! ( HNumber( "0" ) < HNumber( "-1" ) ) );
	ENSURE( "lower failed j", ! ( HNumber( "-0.5" ) < HNumber( "-1" ) ) );
	ENSURE( "lower failed k", ! ( HNumber( "0.5" ) < HNumber( "0" ) ) );
	ENSURE( "lower failed l", ! ( HNumber( "0.5" ) < HNumber( ".2" ) ) );
	ENSURE( "lower failed m", ! ( HNumber( "1" ) < HNumber( ".2" ) ) );
	ENSURE( "lower failed f2", ! ( HNumber( ".1231" ) < HNumber( ".123" ) ) );
	ENSURE( "lower failed n", ! ( HNumber( "3.145" ) < HNumber( "2.734543" ) ) );
	ENSURE( "lower failed o", ! ( HNumber( "1" ) < HNumber( "1" ) ) );
	ENSURE( "lower failed p", ! ( HNumber( "-1" ) < HNumber( "-1" ) ) );
	ENSURE( "lower failed q", ! ( HNumber( ".1" ) < HNumber( ".1" ) ) );
	ENSURE( "lower failed r", ! ( HNumber( "-.1" ) < HNumber( "-.1" ) ) );
	ENSURE( "lower failed s", ! ( HNumber( "0" ) < HNumber( "0" ) ) );
	ENSURE( "lower failed t", ! ( HNumber( "0.01" ) < HNumber( "0" ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "lower or equal then operator" )
	ENSURE( "lower-eq failed a", HNumber( "-1" ) <= HNumber( "1" ) );
	ENSURE( "lower-eq failed b", HNumber( "-1" ) <= HNumber( "0" ) );
	ENSURE( "lower-eq failed c", HNumber( "-1" ) <= HNumber( "-0.5" ) );
	ENSURE( "lower-eq failed d", HNumber( "0" ) <= HNumber( "0.5" ) );
	ENSURE( "lower-eq failed e", HNumber( ".2" ) <= HNumber( "0.5" ) );
	ENSURE( "lower-eq failed f", HNumber( ".2" ) <= HNumber( "1" ) );
	ENSURE( "lower-eq failed f1", HNumber( ".123" ) <= HNumber( ".1231" ) );
	ENSURE( "lower-eq failed g", HNumber( "2.734543" ) <= HNumber( "3.145" ) );
	ENSURE( "lower-eq failed o", HNumber( "1" ) <= HNumber( "1" ) );
	ENSURE( "lower-eq failed p", HNumber( "-1" ) <= HNumber( "-1" ) );
	ENSURE( "lower-eq failed q", HNumber( ".1" ) <= HNumber( ".1" ) );
	ENSURE( "lower-eq failed r", HNumber( "-.1" ) <= HNumber( "-.1" ) );
	ENSURE( "lower-eq failed s", HNumber( "0" ) <= HNumber( "0" ) );

	ENSURE( "lower-eq failed h", ! ( HNumber( "1" ) <= HNumber( "-1" ) ) );
	ENSURE( "lower-eq failed i", ! ( HNumber( "0" ) <= HNumber( "-1" ) ) );
	ENSURE( "lower-eq failed j", ! ( HNumber( "-0.5" ) <= HNumber( "-1" ) ) );
	ENSURE( "lower-eq failed k", ! ( HNumber( "0.5" ) <= HNumber( "0" ) ) );
	ENSURE( "lower-eq failed l", ! ( HNumber( "0.5" ) <= HNumber( ".2" ) ) );
	ENSURE( "lower-eq failed m", ! ( HNumber( "1" ) <= HNumber( ".2" ) ) );
	ENSURE( "lower-eq failed f2", ! ( HNumber( ".1231" ) <= HNumber( ".123" ) ) );
	ENSURE( "lower-eq failed n", ! ( HNumber( "3.145" ) <= HNumber( "2.734543" ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "greater then operator" )
	ENSURE( "greater failed a", HNumber( "1" ) > HNumber( "-1" ) );
	ENSURE( "greater failed b", HNumber( "0" ) > HNumber( "-1" ) );
	ENSURE( "greater failed c", HNumber( "-0.5" ) > HNumber( "-1" ) );
	ENSURE( "greater failed d", HNumber( "0.5" ) > HNumber( "0" ) );
	ENSURE( "greater failed e", HNumber( "0.5" ) > HNumber( ".2" ) );
	ENSURE( "greater failed f", HNumber( "1" ) > HNumber( ".2" ) );
	ENSURE( "greater failed f1", HNumber( ".1231" ) > HNumber( ".123" ) );
	ENSURE( "greater failed g", HNumber( "3.145" ) > HNumber( "2.734543" ) );

	ENSURE( "greater failed h", ! ( HNumber( "-1" ) > HNumber( "1" ) ) );
	ENSURE( "greater failed i", ! ( HNumber( "-1" ) > HNumber( "0" ) ) );
	ENSURE( "greater failed j", ! ( HNumber( "-1" ) > HNumber( "-0.5" ) ) );
	ENSURE( "greater failed k", ! ( HNumber( "0" ) > HNumber( "0.5" ) ) );
	ENSURE( "greater failed l", ! ( HNumber( ".2" ) > HNumber( "0.5" ) ) );
	ENSURE( "greater failed m", ! ( HNumber( ".2" ) > HNumber( "1" ) ) );
	ENSURE( "greater failed f2", ! ( HNumber( ".123" ) > HNumber( ".1231" ) ) );
	ENSURE( "greater failed n", ! ( HNumber( "2.734543" ) > HNumber( "3.145" ) ) );
	ENSURE( "greater failed o", ! ( HNumber( "1" ) > HNumber( "1" ) ) );
	ENSURE( "greater failed p", ! ( HNumber( "-1" ) > HNumber( "-1" ) ) );
	ENSURE( "greater failed q", ! ( HNumber( ".1" ) > HNumber( ".1" ) ) );
	ENSURE( "greater failed r", ! ( HNumber( "-.1" ) > HNumber( "-.1" ) ) );
	ENSURE( "greater failed s", ! ( HNumber( "0" ) > HNumber( "0" ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 17, "greater or equal then operator" )
	ENSURE( "greater-eq failed a", HNumber( "1" ) >= HNumber( "-1" ) );
	ENSURE( "greater-eq failed b", HNumber( "0" ) >= HNumber( "-1" ) );
	ENSURE( "greater-eq failed c", HNumber( "-0.5" ) >= HNumber( "-1" ) );
	ENSURE( "greater-eq failed d", HNumber( "0.5" ) >= HNumber( "0" ) );
	ENSURE( "greater-eq failed e", HNumber( "0.5" ) >= HNumber( ".2" ) );
	ENSURE( "greater-eq failed f", HNumber( "1" ) >= HNumber( ".2" ) );
	ENSURE( "greater-eq failed f1", HNumber( ".1231" ) >= HNumber( ".123" ) );
	ENSURE( "greater-eq failed g", HNumber( "3.145" ) >= HNumber( "2.734543" ) );

	ENSURE( "greater-eq failed h", ! ( HNumber( "-1" ) >= HNumber( "1" ) ) );
	ENSURE( "greater-eq failed i", ! ( HNumber( "-1" ) >= HNumber( "0" ) ) );
	ENSURE( "greater-eq failed j", ! ( HNumber( "-1" ) >= HNumber( "-0.5" ) ) );
	ENSURE( "greater-eq failed k", ! ( HNumber( "0" ) >= HNumber( "0.5" ) ) );
	ENSURE( "greater-eq failed l", ! ( HNumber( ".2" ) >= HNumber( "0.5" ) ) );
	ENSURE( "greater-eq failed m", ! ( HNumber( ".2" ) >= HNumber( "1" ) ) );
	ENSURE( "greater-eq failed f2", ! ( HNumber( ".123" ) >= HNumber( ".1231" ) ) );
	ENSURE( "greater-eq failed n", ! ( HNumber( "2.734543" ) >= HNumber( "3.145" ) ) );
	ENSURE( "greater-eq failed o", HNumber( "1" ) >= HNumber( "1" ) );
	ENSURE( "greater-eq failed p", HNumber( "-1" ) >= HNumber( "-1" ) );
	ENSURE( "greater-eq failed q", HNumber( ".1" ) >= HNumber( ".1" ) );
	ENSURE( "greater-eq failed r", HNumber( "-.1" ) >= HNumber( "-.1" ) );
	ENSURE( "greater-eq failed s", HNumber( "0" ) >= HNumber( "0" ) );
TUT_TEARDOWN()

/*
 * :::::.:::::::::
 *    ++.+++++++++
 * *****.***
 *
 * ressize = 2;
 * dps = 2;
 *
 */

#define ADD_TEST( augend, addend, sum ) \
	ENSURE_EQUALS( "addition failed: `" #augend " + " #addend " = " #sum "'", ( HNumber( #augend ) + HNumber( #addend ) ).to_string(), HNumber( #sum ).to_string() )

TUT_UNIT_TEST( 18, "addition" )
	ADD_TEST( 0, 0, 0 );
	ADD_TEST( 6, 7, 13 );
	ADD_TEST( 1, 0, 1 );
	ADD_TEST( 0, 1, 1 );
	ADD_TEST( -1, 0, -1 );
	ADD_TEST( 0, -1, -1 );
	ADD_TEST( -1, -1, -2 );
	ADD_TEST( 1, 1, 2 );
	ADD_TEST( -1, 1, 0 );
	ADD_TEST( 1, -1, 0 );
	ADD_TEST( 1.234, 2.345, 3.579 );
	ADD_TEST( 2.345, 3.455, 5.8 );
	ADD_TEST( 12.34, 4.323, 16.663 );
	ADD_TEST( -1.234, 4.2356, 3.0016 );
	ADD_TEST( 123.1, 1.1234, 124.2234 );
	ADD_TEST( 123.1234, 1.12, 124.2434 );
	ADD_TEST( 1.1234, 123.1, 124.2234 );
	ADD_TEST( 1.12, 123.1234, 124.2434 );
	ADD_TEST( -123.1, 1.1234, -121.9766 );
	ADD_TEST( -123.1234, 1.12, -122.0034 );
	ADD_TEST( -1.1234, 123.1, 121.9766 );
	ADD_TEST( -1.12, 123.1234, 122.0034 );
	ADD_TEST( 123.1, -1.1234, 121.9766 );
	ADD_TEST( 123.1234, -1.12, 122.0034 );
	ADD_TEST( 1.1234, -123.1, -121.9766 );
	ADD_TEST( 1.12, -123.1234, -122.0034 );
	ADD_TEST( -123.1, -1.1234, -124.2234 );
	ADD_TEST( -123.1234, -1.12, -124.2434 );
	ADD_TEST( -1.1234, -123.1, -124.2234 );
	ADD_TEST( -1.12, -123.1234, -124.2434 );
	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	for ( int i = 0; i < 1000; ++ i ) {
		HNumber a( random_real() );
		HNumber b( random_real() );
		as = a.to_string();
		bs = b.to_string();
		_bc << as << '+' << bs << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		msg = "addition of random a = " + as + " and b = " + bs + " failed";
		ENSURE_EQUALS( msg, ( a + b ).to_string(), HNumber( res ).to_string() );
		msg += "(R)";
		ENSURE_EQUALS( msg, ( b + a ).to_string(), HNumber( res ).to_string() );
	}
TUT_TEARDOWN()

#undef ADD_TEST

#define MUL_TEST( multiplicand, factor, product ) \
	ENSURE_EQUALS( "multiplication failed: `" #multiplicand " * " #factor " = " #product "'", ( HNumber( #multiplicand ) * HNumber( #factor ) ).to_string(), HNumber( #product ).to_string() )

TUT_UNIT_TEST( 19, "multiplication" )
	MUL_TEST( 0, 0, 0 );
	MUL_TEST( 0, 1, 0 );
	MUL_TEST( 1, 1, 1 );
	MUL_TEST( 2, 3, 6 );
	MUL_TEST( -2, 3, -6 );
	MUL_TEST( -2, -3, 6 );
	MUL_TEST( 12.34, -7.321, -90.34114 );
	MUL_TEST( 123.4567, 100, 12345.67 );
	MUL_TEST( 12.345, 100000, 1234500 );
	MUL_TEST( 1234, 0.001, 1.234 );
	MUL_TEST( 584833018983741997878722386503334636.78288384371198912247950986, -9495561202762179256808404731.0288638, -5553317725156297579601206726057421373895864032769682350068288883.613387831060572493018571736697068 );
	MUL_TEST( 930000000096000000000, 95, 88350000009120000000000 );
	MUL_TEST( .011931709189, -154.734375, -1.846245564041671875 );

	if ( HNumber::DECIMAL_DIGITS_IN_LEAF != 1 ) {
		ENSURE_EQUALS( "multiplication failed j2", ( HNumber( expand_leafs( "584833018983741997878722386503334636.78288384371198912247950986" ) ) * HNumber( expand_leafs( "-9495561202762179256808404731.0288638" ) ) ).to_string(), HNumber( "-450000000920000001130000001850000001600000002010000001520000001330000001740000001810000002730000002880000003460000003320000003330000004040000003690000004310000005220000005730000006090000005550000006080000005660000005400000006000000006500000006950000005840000006380000007140000007250000006850000007680000008630000008560000007890000008190000007130000008310000008830000008350000009030000007850000007980000007600000007910000007760000007460000008030000009560000008740000008170000006950000007660000007640000007430000007680000007570000008300000008020000007960000006450000007070000007.20000000639000000671000000670000000517000000633000000683000000647000000480000000539000000613000000528000000437000000357000000410000000403000000422000000375000000327000000221000000249000000239000000259000000208000000171000000201000000235000000206000000123000000132000000082000000048" ).to_string() );
		ENSURE_EQUALS( "multiplication failed k2", ( HNumber( expand_leafs( "930000000096000000000" ) ) * HNumber( expand_leafs( "95" ) ) ).to_string(), HNumber( "810000000720000000150000000000000000000000000000000000000000000000000000000000000000000000810000000990000000300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" ).to_string() );
		ENSURE_EQUALS( "multiplication failed x2", ( HNumber( expand_leafs( ".011931709189" ) ) * HNumber( expand_leafs( "-154.734375" ) ) ).to_string(), HNumber( "-10000000060000000.18000000059000000062000000094000000094000000099000000149000000151000000213000000154000000185000000153000000125000000112000000088000000103000000045" ).to_string() );
	}
	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	_bc << "scale=100" << endl;
	for ( int long i = 0; i < 1000; ++ i ) {
		as = random_real();
		bs = random_real();
		HNumber a( as );
		HNumber b( bs );
		_bc << as << "* " << bs << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		msg = "multiplication of random a = " + as + " and b = " + bs + " failed";
		
		ENSURE_EQUALS( msg, ( a * b ).to_string(), HNumber( res ).to_string() );
		msg += "(R)";
		ENSURE_EQUALS( msg, ( b * a ).to_string(), HNumber( res ).to_string() );
	}
TUT_TEARDOWN()

#undef MUL_TEST

TUT_UNIT_TEST( 20, "substraction" )
	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	for ( int i = 0; i < 1000; ++ i ) {
		HNumber a( random_real() );
		HNumber b( random_real() );
		as = a.to_string();
		bs = b.to_string();
		msg = "substraction of random a = " + as + " and b = " + bs + " failed";
		_bc << as << "- " << bs << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		ENSURE_EQUALS( msg, ( a - b ).to_string(), HNumber( res ).to_string() );
		msg += "(R)";
		ENSURE_EQUALS( msg, ( b - a ).to_string(), ( -HNumber( res ) ).to_string() );
	}
TUT_TEARDOWN()

#define DIV_TEST_MSG( msg, dividend, divisor, quotient ) \
	do { \
		HNumber quot( #dividend ); \
		HNumber div( #divisor ); \
		clog << ansi::brightcyan << ">> " << #dividend << " / " << #divisor << ansi::reset << " = " << flush; \
		quot /= div; \
		clog << ansi::yellow << quot.to_string() << ansi::reset << endl; \
		ENSURE_EQUALS( msg ": `" #dividend " / " #divisor " = " #quotient "'", quot.to_string(), HNumber( #quotient ).to_string() ); \
	} while ( false )

#define DIV_TEST_MSG_LIM( msg, dividend, divisor, quotient, lim ) \
	ENSURE_EQUALS( msg ": `" #dividend " / " #divisor " = " #quotient "'", ( HNumber( #dividend ) / HNumber( #divisor ) ).to_string().left( lim ), HNumber( #quotient ).to_string() )

#define DIV_TEST( dividend, divisor, quotient ) \
	DIV_TEST_MSG( "division failed", dividend, divisor, quotient )

TUT_UNIT_TEST( 21, "division" )
	try {
		HNumber n( "1" );
		HNumber x;
		n /= x;
		FAIL( "division by zero performed" );
	} catch ( HException& ) {
		// ok
	}
	DIV_TEST( 2, 2, 1 );
	DIV_TEST( 0, 1, 0 );
	DIV_TEST( 0, -1, 0 );
	DIV_TEST( 1, 1, 1 );
	DIV_TEST( 1, 10, .1 );
	DIV_TEST( 1, 100, .01 );
	DIV_TEST( 1, 1000, .001 );
	DIV_TEST( 1, 1000000000, .000000001 );
	DIV_TEST( 1, .1, 10 );
	DIV_TEST( 1, .01, 100 );
	DIV_TEST( 1, .001, 1000 );
	DIV_TEST( 1, .0000000001, 10000000000 );
	DIV_TEST( .1, 1, .1 );
	DIV_TEST( .1, 10, .01 );
	DIV_TEST( .11, 11, .01 );
	DIV_TEST( .011, 1.1, .01 );
	DIV_TEST( .0011, .11, .01 );
	DIV_TEST( .00011, .011, .01 );
	DIV_TEST( .00011, .011, .01 );
	DIV_TEST( .9801, .99, .99 );
	DIV_TEST( .998001, .999, .999 );
	DIV_TEST( .99980001, .9999, .9999 );
	DIV_TEST( .1, 100, .001 );
	DIV_TEST( .1, 1000, .0001 );
	DIV_TEST( .1, 1000000000, .0000000001 );
	DIV_TEST( .01, 1, .01 );
	DIV_TEST( .01, 10, .001 );
	DIV_TEST( .01, 100, .0001 );
	DIV_TEST( .01, 1000, .00001 );
	DIV_TEST( .001, 1, .001 );
	DIV_TEST( .001, 10, .0001 );
	DIV_TEST( .001, 100, .00001 );
	DIV_TEST( .001, 1000, .000001 );
	DIV_TEST( 10.01, 1, 10.01 );
	DIV_TEST( 100.01, 1, 100.01 );
	DIV_TEST( 10.001, 1, 10.001 );
	DIV_TEST( 10.01, 2, 5.005 );
	DIV_TEST( 10.01, 10, 1.001 );
	DIV_TEST( 10.001, 10, 1.0001 );
	DIV_TEST( 10.001, 100, .10001 );
	DIV_TEST( 10.001, 1000, .010001 );
	DIV_TEST( 100.01, 10, 10.001 );
	DIV_TEST( 100.01, 100, 1.0001 );
	DIV_TEST( 100.01, 1000, .10001 );
	DIV_TEST( 10.01, 20, .5005 );
	DIV_TEST( 10.01, 100, .1001 );
	DIV_TEST( 10.01, 200, .05005 );
	DIV_TEST( 10.01, 1000, .01001 );
	DIV_TEST( 10.01, 2000, .005005 );
	DIV_TEST( 10.01, 10000, .001001 );
	DIV_TEST( 10.01, 20000, .0005005 );
	DIV_TEST( 10.01, 100000, .0001001 );
	DIV_TEST( 10.01, 200000, .00005005 );
	DIV_TEST( 10.01, .1, 100.1 );
	DIV_TEST( 10.01, .2, 50.05 );
	DIV_TEST( 10.01, .01, 1001 );
	DIV_TEST( 10.01, .02, 500.5 );
	DIV_TEST( 10.01, .001, 10010 );
	DIV_TEST( 10.01, .002, 5005 );
	DIV_TEST( 10.01, .0001, 100100 );
	DIV_TEST( 10.01, .0000000001, 100100000000 );
	DIV_TEST( 10.01, .0002, 50050 );
	DIV_TEST( 1, 4, .25 );
	DIV_TEST( 1, -1, -1 );
	DIV_TEST( -1, 1, -1 );
	DIV_TEST( -1, -1, 1 );
	DIV_TEST( 2, 4, .5 );
	DIV_TEST( 4, 2, 2 );
	DIV_TEST( 2468, 2, 1234 );
	DIV_TEST( 100, 5, 20 );
	DIV_TEST( 5, 100, .05 );
	DIV_TEST( 3.144, .03, 104.8 );
	DIV_TEST( 3.15, .03, 105 );
	DIV_TEST( 31.44, .03, 1048 );
	DIV_TEST( 12351235.57, 1234, 10009.105 );
	HNumber numerator( "1" );
	HNumber denominator( "3" );
	int const MIN = 16;
	numerator.set_precision( MIN );
	denominator.set_precision( MIN );
	HNumber division;
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 1", division.to_string(), "0.3333333333333333" );
	ENSURE( "number shall not be exact", ! division.is_exact() );
	numerator = "2";
	numerator.set_precision( MIN );
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 2", division.to_string(), "0.6666666666666666" );
	ENSURE( "number shall not be exact", ! division.is_exact() );
	numerator = "2000";
	numerator.set_precision( MIN );
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 3", division.to_string(), "666.6666666666666666" );
	ENSURE( "number shall not be exact", ! division.is_exact() );
	denominator = "3000000000000";
	denominator.set_precision( MIN );
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 4", division.to_string(), "0.0000000006666666" );
	ENSURE( "number shall not be exact", ! division.is_exact() );
	numerator = "2";
	denominator = "4";
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 5", division.to_string(), "0.5" );
	ENSURE( "number shall be exact", division.is_exact() );
	DIV_TEST_MSG( "padding front zeros failed", .491401, 7.01, 0.0701 );
		//.59247871334 and b = 3.404513888889 failed: expected .1740274038163329231239957953559 actual .01740274038163329231239957953559
	DIV_TEST_MSG( "padding front zeros failed", .606, 3.03, 0.2 );
	DIV_TEST_MSG( "padding front zeros failed", .49, 7, 0.07 );
	DIV_TEST_MSG( "padding front zeros failed", 4.91401, 70.1, 0.0701 );
	DIV_TEST_MSG( "padding front zeros failed", .491401, 70.1, 0.00701 );
	DIV_TEST_MSG( "padding front zeros failed", .0491401, 70.1, 0.000701 );
	DIV_TEST_MSG( "padding front zeros failed", .00491401, 70.1, 0.0000701 );
	DIV_TEST_MSG( "padding front zeros failed", 4.91401, 7.01, 0.701 );
	DIV_TEST_MSG( "padding front zeros failed", .491401, 7.01, 0.0701 );
	DIV_TEST_MSG( "padding front zeros failed", .0491401, 7.01, 0.00701 );
	DIV_TEST_MSG( "padding front zeros failed", .00491401, 7.01, 0.000701 );
	DIV_TEST_MSG( "padding front zeros failed", .491401, 701, 0.000701 );
	DIV_TEST_MSG( "padding front zeros failed", 491.401, 701, 0.701 );
	DIV_TEST_MSG( "padding front zeros failed", 49.1401, 701, 0.0701 );
	DIV_TEST_MSG( "padding front zeros failed", 4.91401, 701, 0.00701 );
	DIV_TEST_MSG( "padding front zeros failed", .4961122700545761418014255, -7.059190031153, -0.0702789226335 );
	DIV_TEST_MSG( "padding front zeros failed", .4961122700545761418014255, 7.059190031153, 0.0702789226335 );
	DIV_TEST( .4961122700545761418014255, -7.059190031153, -0.0702789226335 );
	DIV_TEST_MSG( "padding front zeros failed", .0077, .77, 0.01 );
	DIV_TEST_MSG( "padding front zeros failed", .777, 777, 0.001 );
	DIV_TEST_MSG( "padding front zeros failed", .000777, .777, 0.001 );
	DIV_TEST_MSG_LIM( "padding front zeros failed", .160963010792, 100.264285714286, 0.00160538729863, 16 );
	DIV_TEST_MSG_LIM( "padding front zeros failed", .160963010792, 100264.285714286, 0.000001605387298, 17 );
	DIV_TEST_MSG_LIM( "padding front zeros failed", 1.180629342051, -3.6, -0.327952595014166666666666666666, 33 );

	char const pdividend[] = "0001201440012000144000012000";
	char const pdivisor[] = "00012000";
	char const pquotient[] = "0000000010012000100001200000100000000";
	HString dividend;
	HString divisor;
	HString quotient;
	int const dividendLen( static_cast<int>( sizeof ( pdividend ) - 1 ) );
	int const divisorLen( static_cast<int>( sizeof ( pdivisor ) - 1 ) );

	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	int const M = 16;
	_bc << "scale=" << M + M << endl;

	for ( int dividendPos( 0 ); dividendPos <= dividendLen; ++ dividendPos ) {
		for ( int divisorPos( 0 ); divisorPos <= divisorLen; ++ divisorPos ) {
			dividend = pdividend;
			dividend.insert( dividendPos, "." );
			divisor = pdivisor;
			divisor.insert( divisorPos, "." );
			quotient = pquotient;
			quotient.insert( xmath::clip( 0, dividendPos - divisorPos + 9, static_cast<int>( sizeof ( pquotient ) ) ), "." );

			HNumber a( expand_leafs( dividend ) );
			HString const& den( expand_leafs( divisor ) );
			HNumber b( den != "0" ? den : "1" );
			a.set_precision( M * 2 );
			b.set_precision( M * 2 );
			as = a.to_string();
			bs = b.to_string();
			_bc << as << "/ " << bs << endl;
			do _bc.read_until( res ); while ( res.is_empty() );
			msg = "division of large leaf a = " + as + " and b = " + bs + " failed";
			HNumber div = a / b;
			int len = static_cast<int>( res.get_length() );
			( len >= ( M + M ) ) && ( len = M + M );
			res = res.left( len );
			if ( res[0] == '.' )
				res.insert( 0, 1, '0' );
			else if ( ( res[0] == '-' ) && ( res[1] == '.' ) )
				res.insert( 1, 1, '0' );
			int z( static_cast<int>( res.find( '.' ) != HString::npos ?  res.reverse_find_other_than( "0." ) : res.get_length() ) );
			ENSURE_EQUALS( msg, div.to_string().left( len - z ), res.left( len - z ) );
		}
	}

	static int const scale( 1000 );
	_bc << "scale=" << scale << endl;
	for ( int long i = 0; i < 1000; ++ i ) {
		HNumber a( random_real(), scale );
		HNumber b( random_real(), scale );
		if ( b == "0" )
			++ b;
		as = a.to_string();
		bs = b.to_string();
		_bc << as << "/ " << bs << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		msg = "division of random a = " + as + " and b = " + bs + " failed";
		HNumber div( a / b );
		int len = static_cast<int>( res.get_length() );
		( len >= ( scale + 1 ) ) && ( len = scale + 1 );
		res = res.left( len );
		if ( res[0] == '.' )
			res.insert( 0, 1, '0' );
		else if ( ( res[0] == '-' ) && ( res[1] == '.' ) )
			res.insert( 1, 1, '0' );
		int z( static_cast<int>( res.find( '.' ) != HString::npos ?  res.reverse_find_other_than( "0." ) : res.get_length() ) );
		ENSURE_EQUALS( msg, div.to_string().left( len - z ), res.left( len - z ) );
	}
TUT_TEARDOWN()

#undef DIV_TEST

TUT_UNIT_TEST( 22, "opposite" )
	ENSURE_EQUALS( "opposite failed a", - HNumber( "0" ), HNumber( "0" ) );
	ENSURE_EQUALS( "opposite failed b", - HNumber( "1" ), HNumber( "-1" ) );
	ENSURE_EQUALS( "opposite failed c", - HNumber( "-1" ), HNumber( "1" ) );
	ENSURE_EQUALS( "opposite failed d", - HNumber( ".01" ), HNumber( "-.01" ) );
	ENSURE_EQUALS( "opposite failed e", - HNumber( "-.01" ), HNumber( ".01" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "preincrementation" )
	HNumber n;
	ENSURE_EQUALS( n, "0" );
	HNumber k = ++ n;
	ENSURE_EQUALS( "preincrementation failed orig", n, HNumber( "1" ) );
	ENSURE_EQUALS( "preincrementation failed copy", k, HNumber( "1" ) );
	ENSURE_EQUALS( "preincrementation failed", ++ n, HNumber( "2" ) );
	HNumber x0( "-0.12345" );
	++ x0;
	ENSURE_EQUALS( "preincrementation sign change failed", x0, "0.87655" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 25, "predecrementation" )
	HNumber n;
	HNumber k = -- n;
	ENSURE_EQUALS( "predecrementation failed orig", n, HNumber( "-1" ) );
	ENSURE_EQUALS( "predecrementation failed copy", k, HNumber( "-1" ) );
	ENSURE_EQUALS( "predecrementation failed", -- n, HNumber( "-2" ) );
	HNumber x0( "0.12345" );
	-- x0;
	ENSURE_EQUALS( "preincrementation sign change failed", x0, "-0.87655" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 26, "postincrementation" )
	HNumber n;
	HNumber k = n ++;
	ENSURE_EQUALS( "postincrementation failed orig", n, HNumber( "1" ) );
	ENSURE_EQUALS( "postincrementation failed copy", k, HNumber( "0" ) );
	ENSURE_EQUALS( "postincrementation failed", n ++, HNumber( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 27, "postdecrementation" )
	HNumber n;
	HNumber k = n --;
	ENSURE_EQUALS( "postdecrementation failed orig", n, HNumber( "-1" ) );
	ENSURE_EQUALS( "postdecrementation failed copy", k, HNumber( "0" ) );
	ENSURE_EQUALS( "postdecrementation failed", n --, HNumber( "-1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 28, "construct from int" )
	ENSURE_EQUALS( "construction from int failed", HNumber( 0 ), HNumber( "0" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 29, "is_exact()" )
	HString sn( "0.1234567891234567891234567891" );
	HNumber n( sn );
	ENSURE( "not exact from string", n.is_exact() );
	ENSURE_EQUALS( "bad precision", n.get_precision(), HNumber::DEFAULT_PRECISION );
	static int const HARDCODED_MINIMUM_PRECISION( 16 );
	for ( HNumber::size_t i( static_cast<HNumber::size_t>( sn.get_length() ) - 3 ); i >= HARDCODED_MINIMUM_PRECISION; -- i ) {
		n.set_precision( i );
		ENSURE_EQUALS( "failed to set precision", n.get_precision(), i );
		ENSURE_NOT( "exact after trimming precision below fractional length", n.is_exact() );
	}
TUT_TEARDOWN()

#define SQRT_TEST_MSG( msg, value, root ) \
	ENSURE_EQUALS( msg ": `sqrt(" #value ") = " #root "'", square_root( HNumber( #value ) ).to_string(), HNumber( #root ).to_string() )

#define SQRT_TEST_MSG_LIM( msg, value, root, lim ) \
	ENSURE_EQUALS( msg ": `sqrt(" #value ") = " #root "'", square_root( HNumber( #value ) ).to_string().left( lim ), HNumber( #root ).to_string().left( lim ) )

#define SQRT_TEST( value, root ) \
	SQRT_TEST_MSG( "square root failed", value, root )

TUT_UNIT_TEST( 30, "square_root<HNumber>()" )
	SQRT_TEST( 0, 0 );
	SQRT_TEST( 0.01, 0.1 );
	SQRT_TEST( 0.04, 0.2 );
	SQRT_TEST( 0.09, 0.3 );
	SQRT_TEST( 0.16, 0.4 );
	SQRT_TEST( 0.25, 0.5 );
	SQRT_TEST( 0.36, 0.6 );
	SQRT_TEST( 0.49, 0.7 );
	SQRT_TEST( 0.64, 0.8 );
	SQRT_TEST( 0.81, 0.9 );
	SQRT_TEST( 1, 1 );
	SQRT_TEST( 4, 2 );
	SQRT_TEST( 9, 3 );
	SQRT_TEST( 16, 4 );
	SQRT_TEST( 25, 5 );
	SQRT_TEST( 36, 6 );
	SQRT_TEST( 49, 7 );
	SQRT_TEST( 64, 8 );
	SQRT_TEST( 81, 9 );
	SQRT_TEST( 100, 10 );
	HString s;
	HString msg;
	HString res;
	_bc.spawn( BC_PATH );
	static int const naturalScale = 100;
	_bc << "scale=" << naturalScale << endl;
	for ( int long i = 0; i < 100; ++ i ) {
		HNumber val( random_real() );
		if ( val < 0 )
			val = -val;
		s = val.to_string();
		_bc << "sqrt(" << s << ")" << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		msg = "square root of random val = " + s + " failed";
		HNumber root( square_root( val ) );
		clog << ansi::brightcyan << ">> " << "square_root(" << s << ")" << ansi::reset << " = " << ansi::yellow << root.to_string() << ansi::reset << endl;
		int len = static_cast<int>( res.get_length() );
		( len >= ( naturalScale + 1 ) ) && ( len = naturalScale + 1 );
		res = res.left( len );
		if ( res[0] == '.' )
			res.insert( 0, 1, '0' );
		int z( static_cast<int>( res.find( '.' ) != HString::npos ?  res.reverse_find_other_than( "0." ) : res.get_length() ) );
		/* We need to take rounding in to account here. */
		++ z;
		ENSURE_EQUALS( msg, root.to_string().left( len - z ), res.left( len - z ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 32, "abs<HNumber>()" )
	HNumber n0( "0" );
	ENSURE_EQUALS( "abs(0) failed", n0.abs(), "0" );
	HNumber n1( "1" );
	ENSURE_EQUALS( "abs(1) failed", n1.abs(), "1" );
	HNumber n2( "1000000000000000000000000000" );
	ENSURE_EQUALS( "abs(1000000000000000000000000000) failed", n2.abs(), "1000000000000000000000000000" );
	HNumber n3( "-1" );
	ENSURE_EQUALS( "abs(-1) failed", n3.abs(), "1" );
	HNumber n4( "-1000000000000000000000000000" );
	ENSURE_EQUALS( "abs(-1000000000000000000000000000) failed", n4.abs(), "1000000000000000000000000000" );

	HNumber n5( "0.123" );
	ENSURE_EQUALS( "abs(0.123) failed", n5.abs(), "0.123" );
	HNumber n6( "1.123" );
	ENSURE_EQUALS( "abs(1,123) failed", n6.abs(), "1.123" );
	HNumber n7( "1000000000000000000000000000.123" );
	ENSURE_EQUALS( "abs(1000000000000000000000000000.123) failed", n7.abs(), "1000000000000000000000000000.123" );
	HNumber n8( "-1.123" );
	ENSURE_EQUALS( "abs(-1.123) failed", n8.abs(), "1.123" );
	HNumber n9( "-1000000000000000000000000000.123" );
	ENSURE_EQUALS( "abs(-1000000000000000000000000000.123) failed", n9.abs(), "1000000000000000000000000000.123" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 33, "ln<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 34, "exp<HNumber>()" )
TUT_TEARDOWN()
	
TUT_UNIT_TEST( 35, "pow<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 36, "sin<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 37, "tan<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 38, "floor<HNumber>()" )
	HNumber n0( "0" );
	ENSURE_EQUALS( "floor(0) failed", n0.floor(), "0" );
	HNumber n1( "1" );
	ENSURE_EQUALS( "floor(1) failed", n1.floor(), "1" );
	HNumber n2( "1000000000000000000000000000" );
	ENSURE_EQUALS( "floor(1000000000000000000000000000) failed", n2.floor(), "1000000000000000000000000000" );
	HNumber n3( "-1" );
	ENSURE_EQUALS( "floor(-1) failed", n3.floor(), "-1" );
	HNumber n4( "-1000000000000000000000000000" );
	ENSURE_EQUALS( "floor(-1000000000000000000000000000) failed", n4.floor(), "-1000000000000000000000000000" );

	HNumber n5( "0.123" );
	ENSURE_EQUALS( "floor(0.123) failed", n5.floor(), "0" );
	HNumber n5b( "-0.123" );
	ENSURE_EQUALS( "floor(-0.123) failed", n5b.floor(), "-1" );
	HNumber n6( "1.123" );
	ENSURE_EQUALS( "floor(1,123) failed", n6.floor(), "1" );
	HNumber n7( "1000000000000000000000000000.123" );
	ENSURE_EQUALS( "floor(1000000000000000000000000000.123) failed", n7.floor(), "1000000000000000000000000000" );
	HNumber n8( "-1.123" );
	ENSURE_EQUALS( "floor(-1.123) failed", n8.floor(), "-2" );
	HNumber n9( "-1000000000000000000000000000.123" );
	ENSURE_EQUALS( "floor(-1000000000000000000000000000.123) failed", n9.floor(), "-1000000000000000000000000001" );

	HNumber n10( "0.123456789123456789" );
	ENSURE_EQUALS( "floor(0.123456789123456789) failed", n10.floor(), "0" );
	HNumber n11( "1.123456789123456789" );
	ENSURE_EQUALS( "floor(1.123456789123456789) failed", n11.floor(), "1" );
	HNumber n12( "1000000000000000000000000000.123456789123456789" );
	ENSURE_EQUALS( "floor(1000000000000000000000000000.123456789123456789) failed", n12.floor(), "1000000000000000000000000000" );
	HNumber n13( "-1.123456789123456789" );
	ENSURE_EQUALS( "floor(-1.123456789123456789) failed", n13.floor(), "-2" );
	HNumber n14( "-1000000000000000000000000000.123456789123456789" );
	ENSURE_EQUALS( "floor(-1000000000000000000000000000.123456789123456789) failed", n14.floor(), "-1000000000000000000000000001" );

	HNumber n15( "-9.5" );
	ENSURE_EQUALS( "floor(-9.5) failed", n15.floor(), "-10" );
	HNumber n16( "-99.5" );
	ENSURE_EQUALS( "floor(-99.5) failed", n16.floor(), "-100" );
	HNumber n17( "-999.5" );
	ENSURE_EQUALS( "floor(-999.5) failed", n17.floor(), "-1000" );
	HNumber n18( "-9999.5" );
	ENSURE_EQUALS( "floor(-9999.5) failed", n18.floor(), "-10000" );
	HNumber n19( "-99999.5" );
	ENSURE_EQUALS( "floor(-99999.5) failed", n19.floor(), "-100000" );
	HNumber n20( "-999999.5" );
	ENSURE_EQUALS( "floor(-999999.5) failed", n20.floor(), "-1000000" );
	HNumber n21( "-9999999.5" );
	ENSURE_EQUALS( "floor(-9999999.5) failed", n21.floor(), "-10000000" );
	HNumber n22( "-99999999.5" );
	ENSURE_EQUALS( "floor(-99999999.5) failed", n22.floor(), "-100000000" );
	HNumber n23( "-999999999.5" );
	ENSURE_EQUALS( "floor(-999999999.5) failed", n23.floor(), "-1000000000" );
	HNumber n24( "-9999999999.5" );
	ENSURE_EQUALS( "floor(-9999999999.5) failed", n24.floor(), "-10000000000" );
	HNumber n25( "-99999999999.5" );
	ENSURE_EQUALS( "floor(-99999999999.5) failed", n25.floor(), "-100000000000" );
	HNumber n26( "-999999999999.5" );
	ENSURE_EQUALS( "floor(-999999999999.5) failed", n26.floor(), "-1000000000000" );
	HNumber n27( "-9999999999999.5" );
	ENSURE_EQUALS( "floor(-9999999999999.5) failed", n27.floor(), "-10000000000000" );
	HNumber n28( "-99999999999999.5" );
	ENSURE_EQUALS( "floor(-99999999999999.5) failed", n28.floor(), "-100000000000000" );
	HNumber n29( "-999999999999999.5" );
	ENSURE_EQUALS( "floor(-999999999999999.5) failed", n29.floor(), "-1000000000000000" );
	HNumber n30( "-9999999999999999.5" );
	ENSURE_EQUALS( "floor(-9999999999999999.5) failed", n30.floor(), "-10000000000000000" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 39, "ceil<HNumber>()" )
	HNumber n0( "0" );
	ENSURE_EQUALS( "ceil(0) failed", n0.ceil(), "0" );
	HNumber n1( "1" );
	ENSURE_EQUALS( "ceil(1) failed", n1.ceil(), "1" );
	HNumber n2( "1000000000000000000000000000" );
	ENSURE_EQUALS( "ceil(1000000000000000000000000000) failed", n2.ceil(), "1000000000000000000000000000" );
	HNumber n3( "-1" );
	ENSURE_EQUALS( "ceil(-1) failed", n3.ceil(), "-1" );
	HNumber n4( "-1000000000000000000000000000" );
	ENSURE_EQUALS( "ceil(-1000000000000000000000000000) failed", n4.ceil(), "-1000000000000000000000000000" );

	HNumber n5( "0.123" );
	ENSURE_EQUALS( "ceil(0.123) failed", n5.ceil(), "1" );
	HNumber n6( "1.123" );
	ENSURE_EQUALS( "ceil(1,123) failed", n6.ceil(), "2" );
	HNumber n7( "1000000000000000000000000000.123" );
	ENSURE_EQUALS( "ceil(1000000000000000000000000000.123) failed", n7.ceil(), "1000000000000000000000000001" );
	HNumber n8( "-1.123" );
	ENSURE_EQUALS( "ceil(-1.123) failed", n8.ceil(), "-1" );
	HNumber n9( "-1000000000000000000000000000.123" );
	ENSURE_EQUALS( "ceil(-1000000000000000000000000000.123) failed", n9.ceil(), "-1000000000000000000000000000" );

	HNumber n10( "0.123456789123456789" );
	ENSURE_EQUALS( "ceil(0.123456789123456789) failed", n10.ceil(), "1" );
	HNumber n11( "1.123456789123456789" );
	ENSURE_EQUALS( "ceil(1.123456789123456789) failed", n11.ceil(), "2" );
	HNumber n12( "1000000000000000000000000000.123456789123456789" );
	ENSURE_EQUALS( "ceil(1000000000000000000000000000.123456789123456789) failed", n12.ceil(), "1000000000000000000000000001" );
	HNumber n13( "-1.123456789123456789" );
	ENSURE_EQUALS( "ceil(-1.123456789123456789) failed", n13.ceil(), "-1" );
	HNumber n14( "-1000000000000000000000000000.123456789123456789" );
	ENSURE_EQUALS( "ceil(-1000000000000000000000000000.123456789123456789) failed", n14.ceil(), "-1000000000000000000000000000" );

	HNumber n15( "9.5" );
	ENSURE_EQUALS( "ceil(9.5) failed", n15.ceil(), "10" );
	HNumber n16( "99.5" );
	ENSURE_EQUALS( "ceil(99.5) failed", n16.ceil(), "100" );
	HNumber n17( "999.5" );
	ENSURE_EQUALS( "ceil(999.5) failed", n17.ceil(), "1000" );
	HNumber n18( "9999.5" );
	ENSURE_EQUALS( "ceil(9999.5) failed", n18.ceil(), "10000" );
	HNumber n19( "99999.5" );
	ENSURE_EQUALS( "ceil(99999.5) failed", n19.ceil(), "100000" );
	HNumber n20( "999999.5" );
	ENSURE_EQUALS( "ceil(999999.5) failed", n20.ceil(), "1000000" );
	HNumber n21( "9999999.5" );
	ENSURE_EQUALS( "ceil(9999999.5) failed", n21.ceil(), "10000000" );
	HNumber n22( "99999999.5" );
	ENSURE_EQUALS( "ceil(99999999.5) failed", n22.ceil(), "100000000" );
	HNumber n23( "999999999.5" );
	ENSURE_EQUALS( "ceil(999999999.5) failed", n23.ceil(), "1000000000" );
	HNumber n24( "9999999999.5" );
	ENSURE_EQUALS( "ceil(9999999999.5) failed", n24.ceil(), "10000000000" );
	HNumber n25( "99999999999.5" );
	ENSURE_EQUALS( "ceil(99999999999.5) failed", n25.ceil(), "100000000000" );
	HNumber n26( "999999999999.5" );
	ENSURE_EQUALS( "ceil(999999999999.5) failed", n26.ceil(), "1000000000000" );
	HNumber n27( "9999999999999.5" );
	ENSURE_EQUALS( "ceil(9999999999999.5) failed", n27.ceil(), "10000000000000" );
	HNumber n28( "99999999999999.5" );
	ENSURE_EQUALS( "ceil(99999999999999.5) failed", n28.ceil(), "100000000000000" );
	HNumber n29( "999999999999999.5" );
	ENSURE_EQUALS( "ceil(999999999999999.5) failed", n29.ceil(), "1000000000000000" );
	HNumber n30( "9999999999999999.5" );
	ENSURE_EQUALS( "ceil(9999999999999999.5) failed", n30.ceil(), "10000000000000000" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 40, "round<HNumber>()" )
	char const numsU[][21] = {
		"0.123456789123456789",
		"0.12345678912345679",
		"0.1234567891234568",
		"0.123456789123457",
		"0.12345678912346",
		"0.1234567891235",
		"0.123456789123",
		"0.12345678912",
		"0.1234567891",
		"0.123456789",
		"0.12345679",
		"0.1234568",
		"0.123457",
		"0.12346",
		"0.1235",
		"0.123",
		"0.12",
		"0.1",
		"0"
	};
	char const numsD[][21] = {
		"0.987654321987654321",
		"0.98765432198765432",
		"0.9876543219876543",
		"0.987654321987654",
		"0.98765432198765",
		"0.9876543219877",
		"0.987654321988",
		"0.98765432199",
		"0.987654322",
		"0.987654322",
		"0.98765432",
		"0.9876543",
		"0.987654",
		"0.98765",
		"0.9877",
		"0.988",
		"0.99",
		"1",
		"1"
	};
	HString msg;
	for ( int i( 0 ); i < countof ( numsU ); ++ i ) {
		HNumber U( "0.123456789123456789" );
		int round( ( countof ( numsU ) ) - i - 1 );
		msg.format( "round( U, %d ) failed", round );
		ENSURE_EQUALS( msg, U.round( round ), numsU[i] );
	}
	for ( int i( 0 ); i < countof ( numsD ); ++ i ) {
		HNumber D( "0.987654321987654321" );
		int round( ( countof ( numsD ) ) - i - 1 );
		msg.format( "round( D, %d ) failed", round );
		ENSURE_EQUALS( msg, D.round( round ), numsD[i] );
	}

	HNumber n0( "0" );
	ENSURE_EQUALS( "round( 0, 10 ) failed", n0.round( 10 ), "0" );
	ENSURE_EQUALS( "round( 0, 1 ) failed", n0.round( 1 ), "0" );
	ENSURE_EQUALS( "round( 0, 0 ) failed", n0.round( 0 ), "0" );

	HNumber n1( "1" );
	ENSURE_EQUALS( "round( 1, 10 ) failed", n1.round( 10 ), "1" );
	ENSURE_EQUALS( "round( 1, 1 ) failed", n1.round( 1 ), "1" );
	ENSURE_EQUALS( "round( 1, 0 ) failed", n1.round( 0 ), "1" );

	HNumber n2( "-1" );
	ENSURE_EQUALS( "round( -1, 10 ) failed", n2.round( 10 ), "-1" );
	ENSURE_EQUALS( "round( -1, 1 ) failed", n2.round( 1 ), "-1" );
	ENSURE_EQUALS( "round( -1, 0 ) failed", n2.round( 0 ), "-1" );

	HNumber n3( "1.123" );
	ENSURE_EQUALS( "round( 1.123, 15 ) failed", n3.round( 15 ), "1.123" );
	ENSURE_EQUALS( "round( 1.123, 10 ) failed", n3.round( 10 ), "1.123" );
	ENSURE_EQUALS( "round( 1.123, 5 ) failed", n3.round( 5 ), "1.123" );
	ENSURE_EQUALS( "round( 1.123, 1 ) failed", n3.round( 1 ), "1.1" );
	ENSURE_EQUALS( "round( 1.123, 0 ) failed", n3.round( 0 ), "1" );

	HNumber n4( "1.444455" );
	ENSURE_EQUALS( "round( 1.444455, 15 ) failed", n4.round( 15 ), "1.444455" );
	ENSURE_EQUALS( "round( 1.444455, 10 ) failed", n4.round( 10 ), "1.444455" );
	ENSURE_EQUALS( "round( 1.444455, 5 ) failed", n4.round( 5 ), "1.44446" );
	ENSURE_EQUALS( "round( 1.444455, 1 ) failed", n4.round( 1 ), "1.4" );
	ENSURE_EQUALS( "round( 1.444455, 0 ) failed", n4.round( 0 ), "1" );

	HNumber n5( "1.999999999999999999999" );
	ENSURE_EQUALS( "round( 1.999999999999999999999, 15 ) failed", n5.round( 15 ), "2" );
	ENSURE_EQUALS( "round( 1.999999999999999999999, 10 ) failed", n5.round( 10 ), "2" );
	ENSURE_EQUALS( "round( 1.999999999999999999999, 5 ) failed", n5.round( 5 ), "2" );
	ENSURE_EQUALS( "round( 1.999999999999999999999, 1 ) failed", n5.round( 1 ), "2" );
	ENSURE_EQUALS( "round( 1.999999999999999999999, 0 ) failed", n5.round( 0 ), "2" );

	HNumber n6( "0.5" );
	ENSURE_EQUALS( "round( 0.5, 0 ) failed", n6.round( 0 ), "1" );

	HNumber n7( "-0.5" );
	ENSURE_EQUALS( "round( 0.5, 0 ) failed", n7.round( 0 ), "-1" );

	HNumber x0( "999.9999999998" );
	ENSURE_EQUALS( "round( 999.9999999998, 0 ) failed", x0.round( 0 ), "1000" );
	HNumber x1( "999.9999999998" );
	ENSURE_EQUALS( "round( 999.9999999998, 0 ) failed", x1.round( 9 ), "1000" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 41, "log10<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 42, "asin<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 43, "atan<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 44, "sinh<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 45, "tanh<HNumber>()" )
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "speed" )
	double long y( 0 );
	HNumber n( 3 );
	TIME_CONSTRAINT_EXEMPT(); {
		HClock c;
		n ^= 133333;
		clog << "*speed* HNumber multiplication = " << static_cast<int long>( y = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
	}
	HString myRes = n.to_string();
	_bc.spawn( BC_PATH );
	double long bc( 0 );
	HString res; {
		HClock c;
		_bc << "3^133333" << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		clog << "*speed* bc multiplication = " << static_cast<int long>( bc = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
	}
	ENSURE_EQUALS( "karatsuba failed", myRes, res );
	clog << "*speed* HNumber multiplication result = " << ( ( bc > y ) ? green : red ) << ( y / bc ) << lightgray << endl;
	/**/ {
		HClock c;
		n = square_root( HNumber( 91, 10000 ) );
		clog << "*speed* HNumber square root = " << static_cast<int long>( y = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
	}
	myRes = n.to_string();
	/**/ {
		HClock c;
		_bc << "scale=10000" << endl;
		_bc << "sqrt(91)" << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		clog << "*speed* bc square root = " << static_cast<int long>( bc = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
	}
	ENSURE_EQUALS( "square root failed", myRes, res );
	clog << "*speed* HNumber square root result = " << ( ( bc > y ) ? green : red ) << ( y / bc ) << lightgray << endl;
TUT_TEARDOWN()

}

