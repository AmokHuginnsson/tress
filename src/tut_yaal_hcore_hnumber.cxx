/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hnumber.cxx - this file is integral part of `tress' project.

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


namespace tut
{

struct tut_yaal_hcore_hnumber
	{
	static HString BC_PATH;
	HRandomizer _rnd;
	HPipedChild _bc;
	tut_yaal_hcore_hnumber( void );
	double long random_real( void );
	virtual ~tut_yaal_hcore_hnumber( void )
		{}
	};

HString tut_yaal_hcore_hnumber::BC_PATH = ::getenv( "BC_PATH" ) ? ::getenv( "BC_PATH" ) : "/usr/bin/bc";

tut_yaal_hcore_hnumber::tut_yaal_hcore_hnumber( void )
	: _rnd( randomizer_helper::make_randomizer() ), _bc()
	{
	set_env( "BC_LINE_LENGTH", "40000" );
#ifdef __MSVCXX__
	char const WIN_BC_PATH[] = "..\\..\\..\\..\\usr\\windows\\bin\\bc.exe";
	char const WIN_BC_PATH_ALT[] = "..\\..\\..\\usr\\windows\\bin\\bc.exe";
#endif /* #ifdef __MSVCXX__ */
	char const SOLARIS_BC_PATH[] = "/opt/csw/bin/bc";
	if ( !! HFSItem( SOLARIS_BC_PATH ) )
		BC_PATH = SOLARIS_BC_PATH;
#ifdef __MSVCXX__
	else if ( !! HFSItem( WIN_BC_PATH ) )
		BC_PATH = WIN_BC_PATH;
	else if ( !! HFSItem( WIN_BC_PATH_ALT ) )
		BC_PATH = WIN_BC_PATH_ALT;
#endif /* #ifdef __MSVCXX__ */
	return;
	}


double long tut_yaal_hcore_hnumber::random_real( void )
	{
	double long n = _rnd();
	double long d = 0;
	while ( d == 0 )
		d = _rnd();
	( _rnd() % 2 ) && ( n = -n );
	return ( n / d );
	}

TUT_TEST_GROUP_N( tut_yaal_hcore_hnumber, "yaal::hcore::HNumber" );

TUT_UNIT_TEST_N( 1, "/* default constructor / check default precision */" )
	HNumber n;
	ENSURE_EQUALS( "bad default number", n.to_string(), "0" );
	ENSURE_EQUALS( "bad dafault precision", n.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << n.to_string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* construct from double */" )
	HNumber n( 3.14159265 );
	ENSURE_EQUALS( "number not created correctly", n.to_string(), "3.14159265" );
	ENSURE_EQUALS( "bad dafault precision", n.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << n.to_string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* construct from double and specify precision / get precision */" )
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

TUT_UNIT_TEST_N( 4, "/* construct from string */" )
	char const* const pn0 = "3.14159265";
	HNumber n0( pn0 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0 );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try
		{
		HNumber n( "" );
		FAIL( "empty number created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-" );
		FAIL( "number that is a minus created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "." );
		FAIL( "number that is a dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-." );
		FAIL( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-..1" );
		FAIL( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "..1" );
		FAIL( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn1 = "-1";
	HNumber n1( pn1 );
	ENSURE_EQUALS( "number not created correctly", n1.to_string(), pn1 );
	ENSURE_EQUALS( "bad dafault precision", n1.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2 = ".5";
	HNumber n2( pn2 );
	ENSURE_EQUALS( "number not created correctly", n2.to_string(), pn2 );
	ENSURE_EQUALS( "bad dafault precision", n2.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3 = "-.7";
	HNumber n3( pn3 );
	ENSURE_EQUALS( "number not created correctly", n3.to_string(), pn3 );
	ENSURE_EQUALS( "bad dafault precision", n3.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4 = "-2.7";
	HNumber n4( pn4 );
	ENSURE_EQUALS( "number not created correctly", n4.to_string(), pn4 );
	ENSURE_EQUALS( "bad dafault precision", n4.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try
		{
		HNumber nx( "--2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "..27" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "-.-2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn5 = ".2.7";
	HNumber n5( pn5 );
	ENSURE_EQUALS( "number not created correctly", n5.to_string(), ".2" );
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
	ENSURE_EQUALS( "number 1 not created correctly", HNumber( "-00.200" ).to_string(), "-.2" );
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
	ENSURE_EQUALS( "number 1 7 not created correctly", HNumber( ".0001" ).to_string(), ".0001" );
	ENSURE_EQUALS( "number 1 8 not created correctly", HNumber( "000.1" ).to_string(), ".1" );
	ENSURE_EQUALS( "number 1 9 not created correctly", HNumber( "00.0001" ).to_string(), ".0001" );
	ENSURE_EQUALS( "number 1 10 not created correctly", HNumber( "-.0001" ).to_string(), "-.0001" );
	ENSURE_EQUALS( "number 1 11 not created correctly", HNumber( "-000.001" ).to_string(), "-.001" );
	ENSURE_EQUALS( "number 1 12 not created correctly", HNumber( "-0001." ).to_string(), "-1" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* construct from string (prefixes) */" )
	char const* const pn0 = "???3.14159265";
	HNumber n0( pn0 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0 + 3 );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try
		{
		HNumber n( "???" );
		FAIL( "empty number created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "$$$-" );
		FAIL( "number that is a minus created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "???." );
		FAIL( "number that is a dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "$$$-." );
		FAIL( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn1 = "$$$-1";
	HNumber n1( pn1 );
	ENSURE_EQUALS( "number not created correctly", n1.to_string(), pn1 + 3 );
	ENSURE_EQUALS( "bad dafault precision", n1.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2 = "???.5";
	HNumber n2( pn2 );
	ENSURE_EQUALS( "number not created correctly", n2.to_string(), pn2 + 3 );
	ENSURE_EQUALS( "bad dafault precision", n2.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3 = "$$$-.7";
	HNumber n3( pn3 );
	ENSURE_EQUALS( "number not created correctly", n3.to_string(), pn3 + 3 );
	ENSURE_EQUALS( "bad dafault precision", n3.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4 = "$$$-2.7";
	HNumber n4( pn4 );
	ENSURE_EQUALS( "number not created correctly", n4.to_string(), pn4 + 3 );
	ENSURE_EQUALS( "bad dafault precision", n4.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try
		{
		HNumber nx( "$$$--2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "???..27" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "$$$-.-2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn5 = "???.2.7";
	HNumber n5( pn5 );
	ENSURE_EQUALS( "number not created correctly", n5.to_string(), ".2" );
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

TUT_UNIT_TEST_N( 6, "/* construct from string (postfixes) */" )
	char const* const pn0ok = "3.14159265";
	char const* const pn0 = "3.14159265???";
	HNumber n0( pn0 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0ok );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try
		{
		HNumber n( "???" );
		FAIL( "empty number created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-???" );
		FAIL( "number that is a minus created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( ".???" );
		FAIL( "number that is a dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-.???" );
		FAIL( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn1ok = "-1";
	char const* const pn1 = "-1???";
	HNumber n1( pn1 );
	ENSURE_EQUALS( "number not created correctly", n1.to_string(), pn1ok );
	ENSURE_EQUALS( "bad dafault precision", n1.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2ok = ".5";
	char const* const pn2 = ".5???";
	HNumber n2( pn2 );
	ENSURE_EQUALS( "number not created correctly", n2.to_string(), pn2ok );
	ENSURE_EQUALS( "bad dafault precision", n2.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3ok = "-.7";
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

	try
		{
		HNumber nx( "--2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "..27???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "-.-2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn5 = ".2.7???";
	HNumber n5( pn5 );
	ENSURE_EQUALS( "number not created correctly", n5.to_string(), ".2" );
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

TUT_UNIT_TEST_N( 7, "/* construct from string (prepostfixes) */" )
	char const* const pn0ok = "3.14159265";
	char const* const pn0 = "???3.14159265???";
	HNumber n0( pn0 );
	ENSURE_EQUALS( "number not created correctly", n0.to_string(), pn0ok );
	ENSURE_EQUALS( "bad dafault precision", n0.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try
		{
		HNumber n( "???" );
		FAIL( "empty number created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "$$$-???" );
		FAIL( "number that is a minus created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "???.???" );
		FAIL( "number that is a dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "$$$-.???" );
		FAIL( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn1ok = "-1";
	char const* const pn1 = "$$$-1???";
	HNumber n1( pn1 );
	ENSURE_EQUALS( "number not created correctly", n1.to_string(), pn1ok );
	ENSURE_EQUALS( "bad dafault precision", n1.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2ok = ".5";
	char const* const pn2 = "$$$.5???";
	HNumber n2( pn2 );
	ENSURE_EQUALS( "number not created correctly", n2.to_string(), pn2ok );
	ENSURE_EQUALS( "bad dafault precision", n2.get_precision(), HNumber::DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3ok = "-.7";
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

	try
		{
		HNumber nx( "$$$--2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "???..27???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "$$$-.-2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		FAIL( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn5 = "???.2.7???";
	HNumber n5( pn5 );
	ENSURE_EQUALS( "number not created correctly", n5.to_string(), ".2" );
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

TUT_UNIT_TEST_N( 8, "/* construct from string and specify precision */" )
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

TUT_UNIT_TEST_N( 9, "/* copy constructor */" )
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

TUT_UNIT_TEST_N( 10, "/* set/get precision */" )
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
	n = "10.1212121212121212121212";
	ENSURE_EQUALS( "bad precision from string", n.get_precision(), 22 + 1 ); /* numbers from strings are always is_exact() */
	n.set_precision( 100 );
	ENSURE_EQUALS( "bad modified 4 precision", n.get_precision(), 100 ); /* number was exact */
	HNumber numerator( "1" );
	HNumber denominator( "3" );
	HNumber division;
	numerator.set_precision( M );
	denominator.set_precision( M );
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculated 4 precision ( 1/3 )", division.get_precision(), M + M ); /* number was exact */
	division.set_precision( 100 );
	ENSURE_EQUALS( "bad modified 4 precision ( 1/3 )", division.get_precision(), M + M ); /* number was exact */

	HNumber s;
	ENSURE_EQUALS( "bad default minimum precision", s.get_precision(), M );
	n.set_precision( F );
	ENSURE_EQUALS( "bad modified precision", s.get_precision(), M );
	HNumber::DEFAULT_PRECISION = SAVED;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* assignment operator */" )
	char const* const p0 = "3.14159265";
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
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* equality operator */" )
	char const* const p0 = "3.14159265";
	char const* const p1 = "3.14159265";
	char const* const p2 = "3.141593";
	HNumber n0( p0 );
	HNumber n1( p1 );
	HNumber n2( p2 );
	ENSURE( "equality failed", n0 == n1 );
	ENSURE( "equality failed (not equal)", ! ( n0 == n2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "/* difference operator */" )
	char const* const p0 = "3.14159265";
	char const* const p1 = "3.14159265";
	char const* const p2 = "3.141593";
	HNumber n0( p0 );
	HNumber n1( p1 );
	HNumber n2( p2 );
	ENSURE( "difference failed", n0 != n2 );
	ENSURE( "difference failed (equal)", ! ( n0 != n1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "/* lower then operator */" )
	ENSURE( "lower failed a", HNumber( "-1" ) < HNumber( "1" ) );
	ENSURE( "lower failed b", HNumber( "-1" ) < HNumber( "0" ) );
	ENSURE( "lower failed c", HNumber( "-1" ) < HNumber( "-0.5" ) );
	ENSURE( "lower failed d", HNumber( "0" ) < HNumber( "0.5" ) );
	ENSURE( "lower failed e", HNumber( ".2" ) < HNumber( "0.5" ) );
	ENSURE( "lower failed f", HNumber( ".2" ) < HNumber( "1" ) );
	ENSURE( "lower failed f1", HNumber( ".123" ) < HNumber( ".1231" ) );
	ENSURE( "lower failed g", HNumber( "2.734543" ) < HNumber( "3.145" ) );

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
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 15, "/* lower or equal then operator */" )
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

TUT_UNIT_TEST_N( 16, "/* greater then operator */" )
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

TUT_UNIT_TEST_N( 17, "/* greater or equal then operator */" )
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

TUT_UNIT_TEST_N( 18, "/* addition */" )
	ENSURE_EQUALS( "addition failed a", ( HNumber( "0" ) + HNumber( "0" ) ).to_string(), HNumber( "0" ).to_string() );
	ENSURE_EQUALS( "addition failed a1", ( HNumber( "6" ) + HNumber( "7" ) ).to_string(), HNumber( "13" ).to_string() );
	ENSURE_EQUALS( "addition failed b", ( HNumber( "1" ) + HNumber( "0" ) ).to_string(), HNumber( "1" ).to_string() );
	ENSURE_EQUALS( "addition failed c", ( HNumber( "0" ) + HNumber( "1" ) ).to_string(), HNumber( "1" ).to_string() );
	ENSURE_EQUALS( "addition failed d", ( HNumber( "-1" ) + HNumber( "0" ) ).to_string(), HNumber( "-1" ).to_string() );
	ENSURE_EQUALS( "addition failed e", ( HNumber( "0" ) + HNumber( "-1" ) ).to_string(), HNumber( "-1" ).to_string() );
	ENSURE_EQUALS( "addition failed f", ( HNumber( "-1" ) + HNumber( "-1" ) ).to_string(), HNumber( "-2" ).to_string() );
	ENSURE_EQUALS( "addition failed g", ( HNumber( "1" ) + HNumber( "1" ) ).to_string(), HNumber( "2" ).to_string() );
	ENSURE_EQUALS( "addition failed h", ( HNumber( "-1" ) + HNumber( "1" ) ).to_string(), HNumber( "0" ).to_string() );
	ENSURE_EQUALS( "addition failed i", ( HNumber( "1" ) + HNumber( "-1" ) ).to_string(), HNumber( "0" ).to_string() );
	ENSURE_EQUALS( "addition failed j", ( HNumber( "1.234" ) + HNumber( "2.345" ) ).to_string(), HNumber( "3.579" ).to_string() );
	ENSURE_EQUALS( "addition failed k", ( HNumber( "2.345" ) + HNumber( "3.455" ) ).to_string(), HNumber( "5.8" ).to_string() );
	ENSURE_EQUALS( "addition failed l", ( HNumber( "12.34" ) + HNumber( "4.323" ) ).to_string(), HNumber( "16.663" ).to_string() );
	ENSURE_EQUALS( "addition failed m", ( HNumber( "-1.234" ) + HNumber( "4.2356" ) ).to_string(), HNumber( "3.0016" ).to_string() );

	ENSURE_EQUALS( "addition failed 0", ( HNumber( "123.1" ) + HNumber( "1.1234" ) ).to_string(), HNumber( "124.2234" ).to_string() );
	ENSURE_EQUALS( "addition failed 1", ( HNumber( "123.1234" ) + HNumber( "1.12" ) ).to_string(), HNumber( "124.2434" ).to_string() );
	ENSURE_EQUALS( "addition failed 2", ( HNumber( "1.1234" ) + HNumber( "123.1" ) ).to_string(), HNumber( "124.2234" ).to_string() );
	ENSURE_EQUALS( "addition failed 3", ( HNumber( "1.12" ) + HNumber( "123.1234" ) ).to_string(), HNumber( "124.2434" ).to_string() );
	ENSURE_EQUALS( "addition failed 4", ( HNumber( "-123.1" ) + HNumber( "1.1234" ) ).to_string(), HNumber( "-121.9766" ).to_string() );
	ENSURE_EQUALS( "addition failed 5", ( HNumber( "-123.1234" ) + HNumber( "1.12" ) ).to_string(), HNumber( "-122.0034" ).to_string() );
	ENSURE_EQUALS( "addition failed 6", ( HNumber( "-1.1234" ) + HNumber( "123.1" ) ).to_string(), HNumber( "121.9766" ).to_string() );
	ENSURE_EQUALS( "addition failed 7", ( HNumber( "-1.12" ) + HNumber( "123.1234" ) ).to_string(), HNumber( "122.0034" ).to_string() );
	ENSURE_EQUALS( "addition failed 8", ( HNumber( "123.1" ) + HNumber( "-1.1234" ) ).to_string(), HNumber( "121.9766" ).to_string() );
	ENSURE_EQUALS( "addition failed 9", ( HNumber( "123.1234" ) + HNumber( "-1.12" ) ).to_string(), HNumber( "122.0034" ).to_string() );
	ENSURE_EQUALS( "addition failed 10", ( HNumber( "1.1234" ) + HNumber( "-123.1" ) ).to_string(), HNumber( "-121.9766" ).to_string() );
	ENSURE_EQUALS( "addition failed 11", ( HNumber( "1.12" ) + HNumber( "-123.1234" ) ).to_string(), HNumber( "-122.0034" ).to_string() );
	ENSURE_EQUALS( "addition failed 12", ( HNumber( "-123.1" ) + HNumber( "-1.1234" ) ).to_string(), HNumber( "-124.2234" ).to_string() );
	ENSURE_EQUALS( "addition failed 13", ( HNumber( "-123.1234" ) + HNumber( "-1.12" ) ).to_string(), HNumber( "-124.2434" ).to_string() );
	ENSURE_EQUALS( "addition failed 14", ( HNumber( "-1.1234" ) + HNumber( "-123.1" ) ).to_string(), HNumber( "-124.2234" ).to_string() );
	ENSURE_EQUALS( "addition failed 15", ( HNumber( "-1.12" ) + HNumber( "-123.1234" ) ).to_string(), HNumber( "-124.2434" ).to_string() );
	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	for ( int i = 0; i < 1000; ++ i )
		{
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

TUT_UNIT_TEST_N( 19, "/* multiplication */" )
	//ENSURE_EQUALS( "multiplication failed x", ( HNumber( ".011931709189" ) * HNumber( "-154.734375" ) ).to_string(), HNumber( "-1.846245564041671875" ).to_string() );
	ENSURE_EQUALS( "multiplication failed a", ( HNumber( "0" ) * HNumber( "0" ) ).to_string(), HNumber( "0" ).to_string() );
	ENSURE_EQUALS( "multiplication failed b", ( HNumber( "0" ) * HNumber( "1" ) ).to_string(), HNumber( "0" ).to_string() );
	ENSURE_EQUALS( "multiplication failed c", ( HNumber( "2" ) * HNumber( "3" ) ).to_string(), HNumber( "6" ).to_string() );
	ENSURE_EQUALS( "multiplication failed d", ( HNumber( "-2" ) * HNumber( "3" ) ).to_string(), HNumber( "-6" ).to_string() );
	ENSURE_EQUALS( "multiplication failed e", ( HNumber( "-2" ) * HNumber( "-3" ) ).to_string(), HNumber( "6" ).to_string() );
	ENSURE_EQUALS( "multiplication failed f", ( HNumber( "12.34" ) * HNumber( "-7.321" ) ).to_string(), HNumber( "-90.34114" ).to_string() );
	ENSURE_EQUALS( "multiplication failed g", ( HNumber( "123.4567" ) * HNumber( "100" ) ).to_string(), HNumber( "12345.67" ).to_string() );
	ENSURE_EQUALS( "multiplication failed h", ( HNumber( "12.345" ) * HNumber( "100000" ) ).to_string(), HNumber( "1234500" ).to_string() );
	ENSURE_EQUALS( "multiplication failed i", ( HNumber( "1234" ) * HNumber( "0.001" ) ).to_string(), HNumber( "1.234" ).to_string() );
	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	_bc << "scale=100" << endl;
	for ( int long i = 0; i < 1000; ++ i )
		{
		HNumber a( random_real() );
		HNumber b( random_real() );
		as = a.to_string();
		bs = b.to_string();
		_bc << as << "* " << bs << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		msg = "multiplication of random a = " + as + " and b = " + bs + " failed";
		ENSURE_EQUALS( msg, ( a * b ).to_string(), HNumber( res ).to_string() );
		msg += "(R)";
		ENSURE_EQUALS( msg, ( b * a ).to_string(), HNumber( res ).to_string() );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 20, "/* substraction */" )
	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	for ( int i = 0; i < 1000; ++ i )
		{
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

TUT_UNIT_TEST_N( 21, "/* division */" )
	try
		{
		HNumber n( "1" );
		HNumber x;
		n /= x;
		FAIL( "division by zero performed" );
		}
	catch ( HException& )
		{
		// ok
		}
	ENSURE_EQUALS( "division failed a     ", ( HNumber( "0" ) / HNumber( "1" ) ).to_string(), HNumber( "0" ).to_string() );
	ENSURE_EQUALS( "division failed b     ", ( HNumber( "0" ) / HNumber( "-1" ) ).to_string(), HNumber( "0" ).to_string() );
	ENSURE_EQUALS( "division failed c     ", ( HNumber( "1" ) / HNumber( "1" ) ).to_string(), HNumber( "1" ).to_string() );
	ENSURE_EQUALS( "division failed c x   ", ( HNumber( "1" ) / HNumber( "10" ) ).to_string(), HNumber( ".1" ).to_string() );
	ENSURE_EQUALS( "division failed c y   ", ( HNumber( "1" ) / HNumber( "100" ) ).to_string(), HNumber( ".01" ).to_string() );
	ENSURE_EQUALS( "division failed c z   ", ( HNumber( "1" ) / HNumber( "1000" ) ).to_string(), HNumber( ".001" ).to_string() );
	ENSURE_EQUALS( "division failed c 0   ", ( HNumber( "10.01" ) / HNumber( "1" ) ).to_string(), HNumber( "10.01" ).to_string() );
	ENSURE_EQUALS( "division failed c 0 2 ", ( HNumber( "10.01" ) / HNumber( "2" ) ).to_string(), HNumber( "5.005" ).to_string() );
	ENSURE_EQUALS( "division failed c 1   ", ( HNumber( "10.01" ) / HNumber( "10" ) ).to_string(), HNumber( "1.001" ).to_string() );
	ENSURE_EQUALS( "division failed c 1,0 ", ( HNumber( "10.001" ) / HNumber( "10" ) ).to_string(), HNumber( "1.0001" ).to_string() );
	ENSURE_EQUALS( "division failed c 1,1 ", ( HNumber( "10.001" ) / HNumber( "100" ) ).to_string(), HNumber( ".10001" ).to_string() );
	ENSURE_EQUALS( "division failed c 1,2 ", ( HNumber( "10.001" ) / HNumber( "1000" ) ).to_string(), HNumber( ".010001" ).to_string() );
	ENSURE_EQUALS( "division failed c 1,3 ", ( HNumber( "100.01" ) / HNumber( "10" ) ).to_string(), HNumber( "10.001" ).to_string() );
	ENSURE_EQUALS( "division failed c 1,4 ", ( HNumber( "100.01" ) / HNumber( "100" ) ).to_string(), HNumber( "1.0001" ).to_string() );
	ENSURE_EQUALS( "division failed c 1,5 ", ( HNumber( "100.01" ) / HNumber( "1000" ) ).to_string(), HNumber( ".10001" ).to_string() );
	ENSURE_EQUALS( "division failed c 1 2 ", ( HNumber( "10.01" ) / HNumber( "20" ) ).to_string(), HNumber( ".5005" ).to_string() );
	ENSURE_EQUALS( "division failed c 2   ", ( HNumber( "10.01" ) / HNumber( "100" ) ).to_string(), HNumber( ".1001" ).to_string() );
	ENSURE_EQUALS( "division failed c 2 2 ", ( HNumber( "10.01" ) / HNumber( "200" ) ).to_string(), HNumber( ".05005" ).to_string() );
	ENSURE_EQUALS( "division failed c 3   ", ( HNumber( "10.01" ) / HNumber( "1000" ) ).to_string(), HNumber( ".01001" ).to_string() );
	ENSURE_EQUALS( "division failed c 3 2 ", ( HNumber( "10.01" ) / HNumber( "2000" ) ).to_string(), HNumber( ".005005" ).to_string() );
	ENSURE_EQUALS( "division failed c 4   ", ( HNumber( "10.01" ) / HNumber( "10000" ) ).to_string(), HNumber( ".001001" ).to_string() );
	ENSURE_EQUALS( "division failed c 4 2 ", ( HNumber( "10.01" ) / HNumber( "20000" ) ).to_string(), HNumber( ".0005005" ).to_string() );
	ENSURE_EQUALS( "division failed c 5   ", ( HNumber( "10.01" ) / HNumber( "100000" ) ).to_string(), HNumber( ".0001001" ).to_string() );
	ENSURE_EQUALS( "division failed c 5 2 ", ( HNumber( "10.01" ) / HNumber( "200000" ) ).to_string(), HNumber( ".00005005" ).to_string() );
	ENSURE_EQUALS( "division failed c 6   ", ( HNumber( "10.01" ) / HNumber( ".1" ) ).to_string(), HNumber( "100.1" ).to_string() );
	ENSURE_EQUALS( "division failed c 6 2 ", ( HNumber( "10.01" ) / HNumber( ".2" ) ).to_string(), HNumber( "50.05" ).to_string() );
	ENSURE_EQUALS( "division failed c 7   ", ( HNumber( "10.01" ) / HNumber( ".01" ) ).to_string(), HNumber( "1001" ).to_string() );
	ENSURE_EQUALS( "division failed c 7 2 ", ( HNumber( "10.01" ) / HNumber( ".02" ) ).to_string(), HNumber( "500.5" ).to_string() );
	ENSURE_EQUALS( "division failed c 8   ", ( HNumber( "10.01" ) / HNumber( ".001" ) ).to_string(), HNumber( "10010" ).to_string() );
	ENSURE_EQUALS( "division failed c 8 2 ", ( HNumber( "10.01" ) / HNumber( ".002" ) ).to_string(), HNumber( "5005" ).to_string() );
	ENSURE_EQUALS( "division failed c 9   ", ( HNumber( "10.01" ) / HNumber( ".0001" ) ).to_string(), HNumber( "100100" ).to_string() );
	ENSURE_EQUALS( "division failed c 9 2 ", ( HNumber( "10.01" ) / HNumber( ".0002" ) ).to_string(), HNumber( "50050" ).to_string() );
	ENSURE_EQUALS( "division failed d     ", ( HNumber( "1" ) / HNumber( "-1" ) ).to_string(), HNumber( "-1" ).to_string() );
	ENSURE_EQUALS( "division failed e     ", ( HNumber( "-1" ) / HNumber( "1" ) ).to_string(), HNumber( "-1" ).to_string() );
	ENSURE_EQUALS( "division failed f     ", ( HNumber( "-1" ) / HNumber( "-1" ) ).to_string(), HNumber( "1" ).to_string() );
	ENSURE_EQUALS( "division failed g     ", ( HNumber( "2" ) / HNumber( "4" ) ).to_string(), HNumber( ".5" ).to_string() );
	ENSURE_EQUALS( "division failed h     ", ( HNumber( "4" ) / HNumber( "2" ) ).to_string(), HNumber( "2" ).to_string() );
	ENSURE_EQUALS( "division failed x     ", ( HNumber( "2468" ) / HNumber( "2" ) ).to_string(), HNumber( "1234" ).to_string() );
	ENSURE_EQUALS( "division failed i     ", ( HNumber( "100" ) / HNumber( "5" ) ).to_string(), HNumber( "20" ).to_string() );
	ENSURE_EQUALS( "division failed j     ", ( HNumber( "5" ) / HNumber( "100" ) ).to_string(), HNumber( ".05" ).to_string() );
	ENSURE_EQUALS( "division failed k     ", ( HNumber( "3.144" ) / HNumber( ".03" ) ).to_string(), HNumber( "104.8" ).to_string() );
	ENSURE_EQUALS( "division failed k 1   ", ( HNumber( "3.15" ) / HNumber( ".03" ) ).to_string(), HNumber( "105" ).to_string() );
	ENSURE_EQUALS( "division failed k 2   ", ( HNumber( "31.44" ) / HNumber( ".03" ) ).to_string(), HNumber( "1048" ).to_string() );
	HNumber numerator( "1" );
	HNumber denominator( "3" );
	int const MIN = 16;
	numerator.set_precision( MIN );
	denominator.set_precision( MIN );
	HNumber division;
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 1", division.to_string(), ".33333333333333333333333333333333" );
	ENSURE( "number shall not be exact", ! division.is_exact() );
	numerator = "2";
	numerator.set_precision( MIN );
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 2", division.to_string(), ".66666666666666666666666666666666" );
	ENSURE( "number shall not be exact", ! division.is_exact() );
	numerator = "2000";
	numerator.set_precision( MIN );
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 3", division.to_string(), "666.66666666666666666666666666666666" );
	ENSURE( "number shall not be exact", ! division.is_exact() );
	denominator = "3000000000000";
	denominator.set_precision( MIN );
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 4", division.to_string(), ".00000000066666666666666666666666" );
	ENSURE( "number shall not be exact", ! division.is_exact() );
	numerator = "2";
	denominator = "4";
	division = numerator / denominator;
	ENSURE_EQUALS( "bad calculus 5", division.to_string(), ".5" );
	ENSURE( "number shall be exact", division.is_exact() );
		{
		HString n( ".491401" );
		HString d( "7.01" );
		HString r( ".0701" );
		ENSURE_EQUALS( "padding front zeros failed 0 0 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		//.59247871334 and b = 3.404513888889 failed: expected .1740274038163329231239957953559 actual .01740274038163329231239957953559
		HString n( ".606" );
		HString d( "3.03" );
		HString r( ".2" );
		ENSURE_EQUALS( "padding front zeros failed 0 0 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".49" );
		HString d( "7" );
		HString r( ".07" );
		ENSURE_EQUALS( "padding front zeros failed 0 1 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( "4.91401" );
		HString d( "70.1" );
		HString r( ".0701" );
		ENSURE_EQUALS( "padding front zeros failed 0 2 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".491401" );
		HString d( "70.1" );
		HString r( ".00701" );
		ENSURE_EQUALS( "padding front zeros failed 0 3 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".0491401" );
		HString d( "70.1" );
		HString r( ".000701" );
		ENSURE_EQUALS( "padding front zeros failed 0 4 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".00491401" );
		HString d( "70.1" );
		HString r( ".0000701" );
		ENSURE_EQUALS( "padding front zeros failed 0 5 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}

		{
		HString n( "4.91401" );
		HString d( "7.01" );
		HString r( ".701" );
		ENSURE_EQUALS( "padding front zeros failed 0 6 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".491401" );
		HString d( "7.01" );
		HString r( ".0701" );
		ENSURE_EQUALS( "padding front zeros failed 0 7 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".0491401" );
		HString d( "7.01" );
		HString r( ".00701" );
		ENSURE_EQUALS( "padding front zeros failed 0 8 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".00491401" );
		HString d( "7.01" );
		HString r( ".000701" );
		ENSURE_EQUALS( "padding front zeros failed 0 9 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}

		{
		HString n( ".491401" );
		HString d( "701" );
		HString r( ".000701" );
		ENSURE_EQUALS( "padding front zeros failed 1 0 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( "491.401" );
		HString d( "701" );
		HString r( ".701" );
		ENSURE_EQUALS( "padding front zeros failed 1 1 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( "49.1401" );
		HString d( "701" );
		HString r( ".0701" );
		ENSURE_EQUALS( "padding front zeros failed 1 2 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( "4.91401" );
		HString d( "701" );
		HString r( ".00701" );
		ENSURE_EQUALS( "padding front zeros failed 1 3 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".4961122700545761418014255" );
		HString d( "-7.059190031153" );
		HString r( "-.0702789226335" );
		ENSURE_EQUALS( "padding front zeros failed a 0 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n( ".4961122700545761418014255" );
		HString d( "7.059190031153" );
		HString r( ".0702789226335" );
		ENSURE_EQUALS( "padding front zeros failed b 0 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}

	ENSURE_EQUALS( "division failed uber  ", ( HNumber( ".4961122700545761418014255" ) / HNumber( "-7.059190031153" ) ).to_string(), HNumber( "-.0702789226335" ).to_string() );

		{
		HString n( ".0077" );
		HString d( ".77" );
		HString r( ".01" );
		ENSURE_EQUALS( "padding front zeros failed 0 0 ", ( HNumber( n ) / HNumber( d ) ).to_string(), HNumber( r ).to_string() );
		}
		{
		HString n(    ".160963010792" );
		HString d( "100.264285714286" );
		HString r( ".001605387" );
		ENSURE_EQUALS( "padding front zeros failed 0 0 ", ( HNumber( n ) / HNumber( d ) ).to_string().left( 10 ), HNumber( r ).to_string() );
		}
		{
		HString n(    ".160963010792" );
		HString d( "100264.285714286" );
		HString r( ".000001605" );
		ENSURE_EQUALS( "padding front zeros failed q 0 ", ( HNumber( n ) / HNumber( d ) ).to_string().left( 10 ), HNumber( r ).to_string() );
		}
		{
		HString n( "1.180629342051" );
		HString d( "-3.6" );
		HString r( "-.3279525950141666666666666666" );
		ENSURE_EQUALS( "padding front zeros failed q 1 ", ( HNumber( n ) / HNumber( d ) ).to_string().left( 30 ), HNumber( r ).to_string() );
		}

	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	int const M = 16;
	_bc << "scale=" << M + M << endl;
	for ( int long i = 0; i < 1000; ++ i )
		{
		HNumber a( random_real() );
		double long den = random_real();
		den || ++ den;
		HNumber b( den );
		a.set_precision( M );
		b.set_precision( M );
		as = a.to_string();
		bs = b.to_string();
		_bc << as << "/ " << bs << endl;
		do _bc.read_until( res ); while ( res.is_empty() );
		msg = "division of random a = " + as + " and b = " + bs + " failed";
		HNumber div = a / b;
		int len = static_cast<int>( res.get_length() );
		( len >= ( M + M - 2 ) ) && ( len = M + M - 2 );
		res = res.left( len );
		int z = static_cast<int>( res.reverse_find_other_than( "0" ) );
		if ( z >= 0 )
			ENSURE_EQUALS( msg, div.to_string().left( len - z ), res.left( len - z ) );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 22, "/* opposite */" )
	ENSURE_EQUALS( "opposite failed a", - HNumber( "0" ), HNumber( "0" ) );
	ENSURE_EQUALS( "opposite failed b", - HNumber( "1" ), HNumber( "-1" ) );
	ENSURE_EQUALS( "opposite failed c", - HNumber( "-1" ), HNumber( "1" ) );
	ENSURE_EQUALS( "opposite failed d", - HNumber( ".01" ), HNumber( "-.01" ) );
	ENSURE_EQUALS( "opposite failed e", - HNumber( "-.01" ), HNumber( ".01" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 23, "/* bc */" )
	TIME_CONSTRAINT_EXEMPT();
	HNumber n = 3;
	n ^= 33333;
	HString myRes = n.to_string();
	_bc.spawn( BC_PATH );
	_bc << "3^33333" << endl;
	HString res;
	do _bc.read_until( res ); while ( res.is_empty() );
	ENSURE_EQUALS( "karatsuba failed", myRes, res );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 24, "/* preincrementation */" )
	HNumber n;
	HNumber k = ++ n;
	ENSURE_EQUALS( "preincrementation failed orig", n, HNumber( "1" ) );
	ENSURE_EQUALS( "preincrementation failed copy", k, HNumber( "1" ) );
	ENSURE_EQUALS( "preincrementation failed", ++ n, HNumber( "2" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 25, "/* predecrementation */" )
	HNumber n;
	HNumber k = -- n;
	ENSURE_EQUALS( "predecrementation failed orig", n, HNumber( "-1" ) );
	ENSURE_EQUALS( "predecrementation failed copy", k, HNumber( "-1" ) );
	ENSURE_EQUALS( "predecrementation failed", -- n, HNumber( "-2" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 26, "/* postincrementation */" )
	HNumber n;
	HNumber k = n ++;
	ENSURE_EQUALS( "postincrementation failed orig", n, HNumber( "1" ) );
	ENSURE_EQUALS( "postincrementation failed copy", k, HNumber( "0" ) );
	ENSURE_EQUALS( "postincrementation failed", n ++, HNumber( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 27, "/* postdecrementation */" )
	HNumber n;
	HNumber k = n --;
	ENSURE_EQUALS( "postdecrementation failed orig", n, HNumber( "-1" ) );
	ENSURE_EQUALS( "postdecrementation failed copy", k, HNumber( "0" ) );
	ENSURE_EQUALS( "postdecrementation failed", n --, HNumber( "-1" ) );
TUT_TEARDOWN()

}

