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
M_VCSID ( "$Id$" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal_hcore_hnumber
	{
	static HString BC_PATH;
	HRandomizer _rnd;
	HPipedChild _bc;
	tut_yaal_hcore_hnumber( void );
	double long random_real( void );
	};

HString tut_yaal_hcore_hnumber::BC_PATH = "/usr/bin/bc";

tut_yaal_hcore_hnumber::tut_yaal_hcore_hnumber( void ) : _rnd(), _bc()
	{
	randomizer_helper::init_randomizer_from_time( _rnd );
	}


double long tut_yaal_hcore_hnumber::random_real( void )
	{
	double long n = _rnd.rnd();
	double long d = 0;
	while ( d == 0 )
		d = _rnd.rnd();
	( _rnd.rnd() % 2 ) && ( n = -n );
	return ( n / d );
	}

typedef test_group<tut_yaal_hcore_hnumber> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hnumber_group( "yaal::hcore::HNumber" );

/* default constructor / check default precision */
template<>
template<>
void module::test<1>( void )
	{
	HNumber n;
	ensure_equals( "bad default number", n.to_string(), "0" );
	ensure_equals( "bad dafault precision", n.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << n.to_string() << endl;
	}

/* construct from double */
template<>
template<>
void module::test<2>( void )
	{
	HNumber n( 3.14159265 );
	ensure_equals( "number not created correctly", n.to_string(), "3.14159265" );
	ensure_equals( "bad dafault precision", n.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << n.to_string() << endl;
	}

/* construct from double and specify precision / get precision */
template<>
template<>
void module::test<3>( void )
	{
	int const P1 = 20;
	HNumber n( 3.14159265, P1 );
	ensure_equals( "number not created correctly", n.to_string(), "3.14159265" );
	ensure_equals( "bad specified precision", n.get_precision(), P1 );
	cout << n.to_string() << endl;
	int const M = 16;
	int const P2 = 4;
	HNumber n2( 3.14159265, P2 );
	ensure_equals( "bad precision (shall be at least hardcoded minimum)", n2.get_precision(), M );
	}

/* construct from string */
template<>
template<>
void module::test<4>( void )
	{
	char const* const pn0 = "3.14159265";
	HNumber n0( pn0 );
	ensure_equals( "number not created correctly", n0.to_string(), pn0 );
	ensure_equals( "bad dafault precision", n0.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try
		{
		HNumber n( "" );
		fail( "empty number created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-" );
		fail( "number that is a minus created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "." );
		fail( "number that is a dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-." );
		fail( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-..1" );
		fail( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "..1" );
		fail( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn1 = "-1";
	HNumber n1( pn1 );
	ensure_equals( "number not created correctly", n1.to_string(), pn1 );
	ensure_equals( "bad dafault precision", n1.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2 = ".5";
	HNumber n2( pn2 );
	ensure_equals( "number not created correctly", n2.to_string(), pn2 );
	ensure_equals( "bad dafault precision", n2.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3 = "-.7";
	HNumber n3( pn3 );
	ensure_equals( "number not created correctly", n3.to_string(), pn3 );
	ensure_equals( "bad dafault precision", n3.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4 = "-2.7";
	HNumber n4( pn4 );
	ensure_equals( "number not created correctly", n4.to_string(), pn4 );
	ensure_equals( "bad dafault precision", n4.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try
		{
		HNumber nx( "--2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "..27" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "-.-2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn5 = ".2.7";
	HNumber n5( pn5 );
	ensure_equals( "number not created correctly", n5.to_string(), ".2" );
	ensure_equals( "bad dafault precision", n5.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	char const* const pn6 = "2.7.44";
	HNumber n6( pn6 );
	ensure_equals( "number not created correctly", n6.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n6.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n6 =" << n6.to_string() << " |" << endl;

	char const* const pn7 = "7-44";
	HNumber n7( pn7 );
	ensure_equals( "number not created correctly", n7.to_string(), "7" );
	ensure_equals( "bad dafault precision", n7.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n7 =" << n7.to_string() << " |" << endl;

	char const* const pn8 = "2.7.44";
	HNumber n8( pn8 );
	ensure_equals( "number not created correctly", n8.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n8.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n8 =" << n8.to_string() << " |" << endl;

	char const* const pn9 = "2.700.566-7576-7657";
	HNumber n9( pn9 );
	ensure_equals( "number not created correctly", n9.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n9.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n9 =" << n9.to_string() << " |" << endl;
	ensure_equals( "number 0 not created correctly", HNumber( "0001200" ).to_string(), "1200" );
	ensure_equals( "number 1 not created correctly", HNumber( "-00.200" ).to_string(), "-.2" );
	ensure_equals( "number 2 not created correctly", HNumber( "-00100" ).to_string(), "-100" );
	ensure_equals( "number 3 not created correctly", HNumber( "00012.3200" ).to_string(), "12.32" );
	ensure_equals( "number 4 not created correctly", HNumber( "-000034.212000" ).to_string(), "-34.212" );
	ensure_equals( "number 5 not created correctly", HNumber( "-000" ).to_string(), "0" );
	ensure_equals( "number 6 not created correctly", HNumber( "000" ).to_string(), "0" );
	ensure_equals( "number 7 not created correctly", HNumber( ".000" ).to_string(), "0" );
	ensure_equals( "number 8 not created correctly", HNumber( "000." ).to_string(), "0" );
	ensure_equals( "number 9 not created correctly", HNumber( "00.000" ).to_string(), "0" );
	ensure_equals( "number 10 not created correctly", HNumber( "-.000" ).to_string(), "0" );
	ensure_equals( "number 11 not created correctly", HNumber( "-000.00" ).to_string(), "0" );
	ensure_equals( "number 12 not created correctly", HNumber( "-000." ).to_string(), "0" );
	ensure_equals( "number 1 5 not created correctly", HNumber( "-0001" ).to_string(), "-1" );
	ensure_equals( "number 1 6 not created correctly", HNumber( "0001" ).to_string(), "1" );
	ensure_equals( "number 1 7 not created correctly", HNumber( ".0001" ).to_string(), ".0001" );
	ensure_equals( "number 1 8 not created correctly", HNumber( "000.1" ).to_string(), ".1" );
	ensure_equals( "number 1 9 not created correctly", HNumber( "00.0001" ).to_string(), ".0001" );
	ensure_equals( "number 1 10 not created correctly", HNumber( "-.0001" ).to_string(), "-.0001" );
	ensure_equals( "number 1 11 not created correctly", HNumber( "-000.001" ).to_string(), "-.001" );
	ensure_equals( "number 1 12 not created correctly", HNumber( "-0001." ).to_string(), "-1" );
	}

/* construct from string (prefixes) */
template<>
template<>
void module::test<5>( void )
	{
	char const* const pn0 = "???3.14159265";
	HNumber n0( pn0 );
	ensure_equals( "number not created correctly", n0.to_string(), pn0 + 3 );
	ensure_equals( "bad dafault precision", n0.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try
		{
		HNumber n( "???" );
		fail( "empty number created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "$$$-" );
		fail( "number that is a minus created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "???." );
		fail( "number that is a dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "$$$-." );
		fail( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn1 = "$$$-1";
	HNumber n1( pn1 );
	ensure_equals( "number not created correctly", n1.to_string(), pn1 + 3 );
	ensure_equals( "bad dafault precision", n1.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2 = "???.5";
	HNumber n2( pn2 );
	ensure_equals( "number not created correctly", n2.to_string(), pn2 + 3 );
	ensure_equals( "bad dafault precision", n2.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3 = "$$$-.7";
	HNumber n3( pn3 );
	ensure_equals( "number not created correctly", n3.to_string(), pn3 + 3 );
	ensure_equals( "bad dafault precision", n3.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4 = "$$$-2.7";
	HNumber n4( pn4 );
	ensure_equals( "number not created correctly", n4.to_string(), pn4 + 3 );
	ensure_equals( "bad dafault precision", n4.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try
		{
		HNumber nx( "$$$--2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "???..27" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "$$$-.-2.7" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn5 = "???.2.7";
	HNumber n5( pn5 );
	ensure_equals( "number not created correctly", n5.to_string(), ".2" );
	ensure_equals( "bad dafault precision", n5.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	char const* const pn6 = "???2.7.44";
	HNumber n6( pn6 );
	ensure_equals( "number not created correctly", n6.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n6.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n6 =" << n6.to_string() << " |" << endl;

	char const* const pn7 = "???7-44";
	HNumber n7( pn7 );
	ensure_equals( "number not created correctly", n7.to_string(), "7" );
	ensure_equals( "bad dafault precision", n7.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n7 =" << n7.to_string() << " |" << endl;

	char const* const pn8 = "???2.7.44";
	HNumber n8( pn8 );
	ensure_equals( "number not created correctly", n8.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n8.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n8 =" << n8.to_string() << " |" << endl;
	}

/* construct from string (postfixes) */
template<>
template<>
void module::test<6>( void )
	{
	char const* const pn0ok = "3.14159265";
	char const* const pn0 = "3.14159265???";
	HNumber n0( pn0 );
	ensure_equals( "number not created correctly", n0.to_string(), pn0ok );
	ensure_equals( "bad dafault precision", n0.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try
		{
		HNumber n( "???" );
		fail( "empty number created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-???" );
		fail( "number that is a minus created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( ".???" );
		fail( "number that is a dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "-.???" );
		fail( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn1ok = "-1";
	char const* const pn1 = "-1???";
	HNumber n1( pn1 );
	ensure_equals( "number not created correctly", n1.to_string(), pn1ok );
	ensure_equals( "bad dafault precision", n1.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2ok = ".5";
	char const* const pn2 = ".5???";
	HNumber n2( pn2 );
	ensure_equals( "number not created correctly", n2.to_string(), pn2ok );
	ensure_equals( "bad dafault precision", n2.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3ok = "-.7";
	char const* const pn3 = "-.7???";
	HNumber n3( pn3 );
	ensure_equals( "number not created correctly", n3.to_string(), pn3ok );
	ensure_equals( "bad dafault precision", n3.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4ok = "-2.7";
	char const* const pn4 = "-2.7???";
	HNumber n4( pn4 );
	ensure_equals( "number not created correctly", n4.to_string(), pn4ok );
	ensure_equals( "bad dafault precision", n4.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try
		{
		HNumber nx( "--2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "..27???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "-.-2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn5 = ".2.7???";
	HNumber n5( pn5 );
	ensure_equals( "number not created correctly", n5.to_string(), ".2" );
	ensure_equals( "bad dafault precision", n5.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	char const* const pn6 = "2.7.44???";
	HNumber n6( pn6 );
	ensure_equals( "number not created correctly", n6.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n6.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n6 =" << n6.to_string() << " |" << endl;

	char const* const pn7 = "7-44???";
	HNumber n7( pn7 );
	ensure_equals( "number not created correctly", n7.to_string(), "7" );
	ensure_equals( "bad dafault precision", n7.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n7 =" << n7.to_string() << " |" << endl;

	char const* const pn8 = "2.7.44???";
	HNumber n8( pn8 );
	ensure_equals( "number not created correctly", n8.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n8.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n8 =" << n8.to_string() << " |" << endl;
	}

/* construct from string (prepostfixes) */
template<>
template<>
void module::test<7>( void )
	{
	char const* const pn0ok = "3.14159265";
	char const* const pn0 = "???3.14159265???";
	HNumber n0( pn0 );
	ensure_equals( "number not created correctly", n0.to_string(), pn0ok );
	ensure_equals( "bad dafault precision", n0.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	try
		{
		HNumber n( "???" );
		fail( "empty number created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "$$$-???" );
		fail( "number that is a minus created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "???.???" );
		fail( "number that is a dot created" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		HNumber n( "$$$-.???" );
		fail( "number that is a minus-dot created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn1ok = "-1";
	char const* const pn1 = "$$$-1???";
	HNumber n1( pn1 );
	ensure_equals( "number not created correctly", n1.to_string(), pn1ok );
	ensure_equals( "bad dafault precision", n1.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n1 =" << n1.to_string() << " |" << endl;

	char const* const pn2ok = ".5";
	char const* const pn2 = "$$$.5???";
	HNumber n2( pn2 );
	ensure_equals( "number not created correctly", n2.to_string(), pn2ok );
	ensure_equals( "bad dafault precision", n2.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n2 =" << n2.to_string() << " |" << endl;

	char const* const pn3ok = "-.7";
	char const* const pn3 = "$$$-.7???";
	HNumber n3( pn3 );
	ensure_equals( "number not created correctly", n3.to_string(), pn3ok );
	ensure_equals( "bad dafault precision", n3.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n3 =" << n3.to_string() << " |" << endl;

	char const* const pn4ok = "-2.7";
	char const* const pn4 = "$$$-2.7???";
	HNumber n4( pn4 );
	ensure_equals( "number not created correctly", n4.to_string(), pn4ok );
	ensure_equals( "bad dafault precision", n4.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n4 =" << n4.to_string() << " |" << endl;

	try
		{
		HNumber nx( "$$$--2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "???..27???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	try
		{
		HNumber nx( "$$$-.-2.7???" );
		cout << "| nx =" << nx.to_string() << " |" << endl;
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

	char const* const pn5 = "???.2.7???";
	HNumber n5( pn5 );
	ensure_equals( "number not created correctly", n5.to_string(), ".2" );
	ensure_equals( "bad dafault precision", n5.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	char const* const pn6 = "???2.7.44???";
	HNumber n6( pn6 );
	ensure_equals( "number not created correctly", n6.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n6.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n6 =" << n6.to_string() << " |" << endl;

	char const* const pn7 = "???7-44???";
	HNumber n7( pn7 );
	ensure_equals( "number not created correctly", n7.to_string(), "7" );
	ensure_equals( "bad dafault precision", n7.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n7 =" << n7.to_string() << " |" << endl;

	char const* const pn8 = "???2.7.44???";
	HNumber n8( pn8 );
	ensure_equals( "number not created correctly", n8.to_string(), "2.7" );
	ensure_equals( "bad dafault precision", n8.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n8 =" << n8.to_string() << " |" << endl;
	}

/* construct from string and specify precision */
template<>
template<>
void module::test<8>( void )
	{
	char const* const pn0 = "3.14159265";
	int const P1 = 20;
	HNumber n0( pn0, P1 );
	ensure_equals( "number not created correctly", n0.to_string(), pn0 );
	ensure_equals( "bad dafault precision", n0.get_precision(), P1 );
	cout << "| n0 = " << n0.to_string() << " |" << endl;
	int const M = 16;
	int const P2 = 4;
	HNumber n2( pn0, P2 );
	ensure_equals( "bad precision (shall be at least hardcoded minimum)", n2.get_precision(), M );
	}

/* copy constructor */
template<>
template<>
void module::test<9>( void )
	{
	HNumber n( 3.14159265 );
	ensure_equals( "number not created correctly", n.to_string(), "3.14159265" );
	ensure_equals( "bad dafault precision", n.get_precision(), HNumber::D_DEFAULT_PRECISION );
	HNumber copy( n );
	ensure_equals( "number not created correctly", copy.to_string(), "3.14159265" );
	ensure_equals( "bad dafault precision", copy.get_precision(), HNumber::D_DEFAULT_PRECISION );
	char const* const pn0 = "3.14159265";
	int const P1 = 20;
	HNumber n0( pn0, P1 );
	ensure_equals( "number not created correctly", n0.to_string(), pn0 );
	ensure_equals( "bad dafault precision", n0.get_precision(), P1 );
	HNumber copy0( n0 );
	ensure_equals( "number not created correctly", copy0.to_string(), pn0 );
	ensure_equals( "bad dafault precision", copy0.get_precision(), P1 );
	}

/* set/get precision */
template<>
template<>
void module::test<10>( void )
	{
	HNumber n;
	int const M = 16;
	int const P = 20;
	int const S = 10;
	int const F = 12;
	ensure_equals( "bad dafault precision", n.get_precision(), HNumber::D_DEFAULT_PRECISION );
	n.set_precision( P );
	ensure_equals( "bad modified 1 precision", n.get_precision(), P );
	n.set_precision( HNumber::D_DEFAULT_PRECISION + P );
	ensure_equals( "bad modified 2 precision", n.get_precision(), HNumber::D_DEFAULT_PRECISION + P );
	n.set_precision( HNumber::D_DEFAULT_PRECISION );
	ensure_equals( "bad modified 3 precision", n.get_precision(), HNumber::D_DEFAULT_PRECISION );
	int const SAVED = HNumber::D_DEFAULT_PRECISION;
	HNumber::D_DEFAULT_PRECISION = S;
	n.set_precision( M );
	n = "10.1212121212121212121212";
	ensure_equals( "bad precision from string", n.get_precision(), 22 );
	n.set_precision( 100 );
	ensure_equals( "bad modified 4 precision", n.get_precision(), 22 );
	HNumber s;
	ensure_equals( "bad default minimum precision", s.get_precision(), M );
	n.set_precision( F );
	ensure_equals( "bad modified precision", s.get_precision(), M );
	HNumber::D_DEFAULT_PRECISION = SAVED;
	}

/* assignment operator */
template<>
template<>
void module::test<11>( void )
	{
	char const* const p0 = "3.14159265";
	HNumber n( p0 );
	ensure_equals( "number not created correctly", n.to_string(), p0 );
	ensure_equals( "bad dafault precision", n.get_precision(), HNumber::D_DEFAULT_PRECISION );
	HNumber copy;
	ensure_equals( "number not created correctly", copy.to_string(), "0" );
	ensure_equals( "bad dafault precision", copy.get_precision(), HNumber::D_DEFAULT_PRECISION );
	copy = n;
	ensure_equals( "number not assigned correctly", copy.to_string(), p0 );
	ensure_equals( "bad assigned precision", copy.get_precision(), HNumber::D_DEFAULT_PRECISION );
	HNumber another;
	another.set_precision( HNumber::D_DEFAULT_PRECISION + 5 );
	another = copy;
	ensure_equals( "number not assigned correctly", another.to_string(), p0 );
	ensure_equals( "bad assigned precision", another.get_precision(), HNumber::D_DEFAULT_PRECISION );
	char const* const p1 = "17";
	HNumber next( p1 );
	next.set_precision( HNumber::D_DEFAULT_PRECISION + 5 );
	ensure_equals( "number not created correctly", next.to_string(), p1 );
	ensure_equals( "bad dafault precision", next.get_precision(), HNumber::D_DEFAULT_PRECISION + 5 );
	another = next;
	ensure_equals( "number not created correctly", another.to_string(), p1 );
	ensure_equals( "bad dafault precision", another.get_precision(), HNumber::D_DEFAULT_PRECISION + 5 );
	}

/* equality operator */
template<>
template<>
void module::test<12>( void )
	{
	char const* const p0 = "3.14159265";
	char const* const p1 = "3.14159265";
	char const* const p2 = "3.141593";
	HNumber n0( p0 );
	HNumber n1( p1 );
	HNumber n2( p2 );
	ensure( "equality failed", n0 == n1 );
	ensure( "equality failed (not equal)", ! ( n0 == n2 ) );
	}

/* difference operator */
template<>
template<>
void module::test<13>( void )
	{
	char const* const p0 = "3.14159265";
	char const* const p1 = "3.14159265";
	char const* const p2 = "3.141593";
	HNumber n0( p0 );
	HNumber n1( p1 );
	HNumber n2( p2 );
	ensure( "difference failed", n0 != n2 );
	ensure( "difference failed (equal)", ! ( n0 != n1 ) );
	}

/* lower then operator */
template<>
template<>
void module::test<14>( void )
	{
	ensure( "lower failed a", HNumber( "-1" ) < HNumber( "1" ) );
	ensure( "lower failed b", HNumber( "-1" ) < HNumber( "0" ) );
	ensure( "lower failed c", HNumber( "-1" ) < HNumber( "-0.5" ) );
	ensure( "lower failed d", HNumber( "0" ) < HNumber( "0.5" ) );
	ensure( "lower failed e", HNumber( ".2" ) < HNumber( "0.5" ) );
	ensure( "lower failed f", HNumber( ".2" ) < HNumber( "1" ) );
	ensure( "lower failed f1", HNumber( ".123" ) < HNumber( ".1231" ) );
	ensure( "lower failed g", HNumber( "2.734543" ) < HNumber( "3.145" ) );

	ensure( "lower failed h", ! ( HNumber( "1" ) < HNumber( "-1" ) ) );
	ensure( "lower failed i", ! ( HNumber( "0" ) < HNumber( "-1" ) ) );
	ensure( "lower failed j", ! ( HNumber( "-0.5" ) < HNumber( "-1" ) ) );
	ensure( "lower failed k", ! ( HNumber( "0.5" ) < HNumber( "0" ) ) );
	ensure( "lower failed l", ! ( HNumber( "0.5" ) < HNumber( ".2" ) ) );
	ensure( "lower failed m", ! ( HNumber( "1" ) < HNumber( ".2" ) ) );
	ensure( "lower failed f2", ! ( HNumber( ".1231" ) < HNumber( ".123" ) ) );
	ensure( "lower failed n", ! ( HNumber( "3.145" ) < HNumber( "2.734543" ) ) );
	ensure( "lower failed o", ! ( HNumber( "1" ) < HNumber( "1" ) ) );
	ensure( "lower failed p", ! ( HNumber( "-1" ) < HNumber( "-1" ) ) );
	ensure( "lower failed q", ! ( HNumber( ".1" ) < HNumber( ".1" ) ) );
	ensure( "lower failed r", ! ( HNumber( "-.1" ) < HNumber( "-.1" ) ) );
	ensure( "lower failed s", ! ( HNumber( "0" ) < HNumber( "0" ) ) );
	}

/* lower or equal then operator */
template<>
template<>
void module::test<15>( void )
	{
	ensure( "lower-eq failed a", HNumber( "-1" ) <= HNumber( "1" ) );
	ensure( "lower-eq failed b", HNumber( "-1" ) <= HNumber( "0" ) );
	ensure( "lower-eq failed c", HNumber( "-1" ) <= HNumber( "-0.5" ) );
	ensure( "lower-eq failed d", HNumber( "0" ) <= HNumber( "0.5" ) );
	ensure( "lower-eq failed e", HNumber( ".2" ) <= HNumber( "0.5" ) );
	ensure( "lower-eq failed f", HNumber( ".2" ) <= HNumber( "1" ) );
	ensure( "lower-eq failed f1", HNumber( ".123" ) <= HNumber( ".1231" ) );
	ensure( "lower-eq failed g", HNumber( "2.734543" ) <= HNumber( "3.145" ) );
	ensure( "lower-eq failed o", HNumber( "1" ) <= HNumber( "1" ) );
	ensure( "lower-eq failed p", HNumber( "-1" ) <= HNumber( "-1" ) );
	ensure( "lower-eq failed q", HNumber( ".1" ) <= HNumber( ".1" ) );
	ensure( "lower-eq failed r", HNumber( "-.1" ) <= HNumber( "-.1" ) );
	ensure( "lower-eq failed s", HNumber( "0" ) <= HNumber( "0" ) );

	ensure( "lower-eq failed h", ! ( HNumber( "1" ) <= HNumber( "-1" ) ) );
	ensure( "lower-eq failed i", ! ( HNumber( "0" ) <= HNumber( "-1" ) ) );
	ensure( "lower-eq failed j", ! ( HNumber( "-0.5" ) <= HNumber( "-1" ) ) );
	ensure( "lower-eq failed k", ! ( HNumber( "0.5" ) <= HNumber( "0" ) ) );
	ensure( "lower-eq failed l", ! ( HNumber( "0.5" ) <= HNumber( ".2" ) ) );
	ensure( "lower-eq failed m", ! ( HNumber( "1" ) <= HNumber( ".2" ) ) );
	ensure( "lower-eq failed f2", ! ( HNumber( ".1231" ) <= HNumber( ".123" ) ) );
	ensure( "lower-eq failed n", ! ( HNumber( "3.145" ) <= HNumber( "2.734543" ) ) );
	}

/* greater then operator */
template<>
template<>
void module::test<16>( void )
	{
	ensure( "greater failed a", HNumber( "1" ) > HNumber( "-1" ) );
	ensure( "greater failed b", HNumber( "0" ) > HNumber( "-1" ) );
	ensure( "greater failed c", HNumber( "-0.5" ) > HNumber( "-1" ) );
	ensure( "greater failed d", HNumber( "0.5" ) > HNumber( "0" ) );
	ensure( "greater failed e", HNumber( "0.5" ) > HNumber( ".2" ) );
	ensure( "greater failed f", HNumber( "1" ) > HNumber( ".2" ) );
	ensure( "greater failed f1", HNumber( ".1231" ) > HNumber( ".123" ) );
	ensure( "greater failed g", HNumber( "3.145" ) > HNumber( "2.734543" ) );

	ensure( "greater failed h", ! ( HNumber( "-1" ) > HNumber( "1" ) ) );
	ensure( "greater failed i", ! ( HNumber( "-1" ) > HNumber( "0" ) ) );
	ensure( "greater failed j", ! ( HNumber( "-1" ) > HNumber( "-0.5" ) ) );
	ensure( "greater failed k", ! ( HNumber( "0" ) > HNumber( "0.5" ) ) );
	ensure( "greater failed l", ! ( HNumber( ".2" ) > HNumber( "0.5" ) ) );
	ensure( "greater failed m", ! ( HNumber( ".2" ) > HNumber( "1" ) ) );
	ensure( "greater failed f2", ! ( HNumber( ".123" ) > HNumber( ".1231" ) ) );
	ensure( "greater failed n", ! ( HNumber( "2.734543" ) > HNumber( "3.145" ) ) );
	ensure( "greater failed o", ! ( HNumber( "1" ) > HNumber( "1" ) ) );
	ensure( "greater failed p", ! ( HNumber( "-1" ) > HNumber( "-1" ) ) );
	ensure( "greater failed q", ! ( HNumber( ".1" ) > HNumber( ".1" ) ) );
	ensure( "greater failed r", ! ( HNumber( "-.1" ) > HNumber( "-.1" ) ) );
	ensure( "greater failed s", ! ( HNumber( "0" ) > HNumber( "0" ) ) );
	}

/* greater or equal then operator */
template<>
template<>
void module::test<17>( void )
	{
	ensure( "greater-eq failed a", HNumber( "1" ) >= HNumber( "-1" ) );
	ensure( "greater-eq failed b", HNumber( "0" ) >= HNumber( "-1" ) );
	ensure( "greater-eq failed c", HNumber( "-0.5" ) >= HNumber( "-1" ) );
	ensure( "greater-eq failed d", HNumber( "0.5" ) >= HNumber( "0" ) );
	ensure( "greater-eq failed e", HNumber( "0.5" ) >= HNumber( ".2" ) );
	ensure( "greater-eq failed f", HNumber( "1" ) >= HNumber( ".2" ) );
	ensure( "greater-eq failed f1", HNumber( ".1231" ) >= HNumber( ".123" ) );
	ensure( "greater-eq failed g", HNumber( "3.145" ) >= HNumber( "2.734543" ) );

	ensure( "greater-eq failed h", ! ( HNumber( "-1" ) >= HNumber( "1" ) ) );
	ensure( "greater-eq failed i", ! ( HNumber( "-1" ) >= HNumber( "0" ) ) );
	ensure( "greater-eq failed j", ! ( HNumber( "-1" ) >= HNumber( "-0.5" ) ) );
	ensure( "greater-eq failed k", ! ( HNumber( "0" ) >= HNumber( "0.5" ) ) );
	ensure( "greater-eq failed l", ! ( HNumber( ".2" ) >= HNumber( "0.5" ) ) );
	ensure( "greater-eq failed m", ! ( HNumber( ".2" ) >= HNumber( "1" ) ) );
	ensure( "greater-eq failed f2", ! ( HNumber( ".123" ) >= HNumber( ".1231" ) ) );
	ensure( "greater-eq failed n", ! ( HNumber( "2.734543" ) >= HNumber( "3.145" ) ) );
	ensure( "greater-eq failed o", HNumber( "1" ) >= HNumber( "1" ) );
	ensure( "greater-eq failed p", HNumber( "-1" ) >= HNumber( "-1" ) );
	ensure( "greater-eq failed q", HNumber( ".1" ) >= HNumber( ".1" ) );
	ensure( "greater-eq failed r", HNumber( "-.1" ) >= HNumber( "-.1" ) );
	ensure( "greater-eq failed s", HNumber( "0" ) >= HNumber( "0" ) );
	}

/*
 * :::::.:::::::::
 *    ++.+++++++++
 * *****.***
 *
 * ressize = 2;
 * dps = 2;
 *
 */

/* addition */
template<>
template<>
void module::test<18>( void )
	{
	ensure_equals( "addition failed a", ( HNumber( "0" ) + HNumber( "0" ) ).to_string(), HNumber( "0" ).to_string() );
	ensure_equals( "addition failed a1", ( HNumber( "6" ) + HNumber( "7" ) ).to_string(), HNumber( "13" ).to_string() );
	ensure_equals( "addition failed b", ( HNumber( "1" ) + HNumber( "0" ) ).to_string(), HNumber( "1" ).to_string() );
	ensure_equals( "addition failed c", ( HNumber( "0" ) + HNumber( "1" ) ).to_string(), HNumber( "1" ).to_string() );
	ensure_equals( "addition failed d", ( HNumber( "-1" ) + HNumber( "0" ) ).to_string(), HNumber( "-1" ).to_string() );
	ensure_equals( "addition failed e", ( HNumber( "0" ) + HNumber( "-1" ) ).to_string(), HNumber( "-1" ).to_string() );
	ensure_equals( "addition failed f", ( HNumber( "-1" ) + HNumber( "-1" ) ).to_string(), HNumber( "-2" ).to_string() );
	ensure_equals( "addition failed g", ( HNumber( "1" ) + HNumber( "1" ) ).to_string(), HNumber( "2" ).to_string() );
	ensure_equals( "addition failed h", ( HNumber( "-1" ) + HNumber( "1" ) ).to_string(), HNumber( "0" ).to_string() );
	ensure_equals( "addition failed i", ( HNumber( "1" ) + HNumber( "-1" ) ).to_string(), HNumber( "0" ).to_string() );
	ensure_equals( "addition failed j", ( HNumber( "1.234" ) + HNumber( "2.345" ) ).to_string(), HNumber( "3.579" ).to_string() );
	ensure_equals( "addition failed k", ( HNumber( "2.345" ) + HNumber( "3.455" ) ).to_string(), HNumber( "5.8" ).to_string() );
	ensure_equals( "addition failed l", ( HNumber( "12.34" ) + HNumber( "4.323" ) ).to_string(), HNumber( "16.663" ).to_string() );
	ensure_equals( "addition failed m", ( HNumber( "-1.234" ) + HNumber( "4.2356" ) ).to_string(), HNumber( "3.0016" ).to_string() );

	ensure_equals( "addition failed 0", ( HNumber( "123.1" ) + HNumber( "1.1234" ) ).to_string(), HNumber( "124.2234" ).to_string() );
	ensure_equals( "addition failed 1", ( HNumber( "123.1234" ) + HNumber( "1.12" ) ).to_string(), HNumber( "124.2434" ).to_string() );
	ensure_equals( "addition failed 2", ( HNumber( "1.1234" ) + HNumber( "123.1" ) ).to_string(), HNumber( "124.2234" ).to_string() );
	ensure_equals( "addition failed 3", ( HNumber( "1.12" ) + HNumber( "123.1234" ) ).to_string(), HNumber( "124.2434" ).to_string() );
	ensure_equals( "addition failed 4", ( HNumber( "-123.1" ) + HNumber( "1.1234" ) ).to_string(), HNumber( "-121.9766" ).to_string() );
	ensure_equals( "addition failed 5", ( HNumber( "-123.1234" ) + HNumber( "1.12" ) ).to_string(), HNumber( "-122.0034" ).to_string() );
	ensure_equals( "addition failed 6", ( HNumber( "-1.1234" ) + HNumber( "123.1" ) ).to_string(), HNumber( "121.9766" ).to_string() );
	ensure_equals( "addition failed 7", ( HNumber( "-1.12" ) + HNumber( "123.1234" ) ).to_string(), HNumber( "122.0034" ).to_string() );
	ensure_equals( "addition failed 8", ( HNumber( "123.1" ) + HNumber( "-1.1234" ) ).to_string(), HNumber( "121.9766" ).to_string() );
	ensure_equals( "addition failed 9", ( HNumber( "123.1234" ) + HNumber( "-1.12" ) ).to_string(), HNumber( "122.0034" ).to_string() );
	ensure_equals( "addition failed 10", ( HNumber( "1.1234" ) + HNumber( "-123.1" ) ).to_string(), HNumber( "-121.9766" ).to_string() );
	ensure_equals( "addition failed 11", ( HNumber( "1.12" ) + HNumber( "-123.1234" ) ).to_string(), HNumber( "-122.0034" ).to_string() );
	ensure_equals( "addition failed 12", ( HNumber( "-123.1" ) + HNumber( "-1.1234" ) ).to_string(), HNumber( "-124.2234" ).to_string() );
	ensure_equals( "addition failed 13", ( HNumber( "-123.1234" ) + HNumber( "-1.12" ) ).to_string(), HNumber( "-124.2434" ).to_string() );
	ensure_equals( "addition failed 14", ( HNumber( "-1.1234" ) + HNumber( "-123.1" ) ).to_string(), HNumber( "-124.2234" ).to_string() );
	ensure_equals( "addition failed 15", ( HNumber( "-1.12" ) + HNumber( "-123.1234" ) ).to_string(), HNumber( "-124.2434" ).to_string() );
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
		_bc.read_until( res );
		msg = "addition of random a = " + as + " and b = " + bs + " failed";
		ensure_equals( msg, ( a + b ).to_string(), HNumber( res ).to_string() );
		msg += "(R)";
		ensure_equals( msg, ( b + a ).to_string(), HNumber( res ).to_string() );
		}
	}

/* multiplication */
template<>
template<>
void module::test<19>( void )
	{
	//ensure_equals( "multiplication failed x", ( HNumber( ".011931709189" ) * HNumber( "-154.734375" ) ).to_string(), HNumber( "-1.846245564041671875" ).to_string() );
	ensure_equals( "multiplication failed a", ( HNumber( "0" ) * HNumber( "0" ) ).to_string(), HNumber( "0" ).to_string() );
	ensure_equals( "multiplication failed b", ( HNumber( "0" ) * HNumber( "1" ) ).to_string(), HNumber( "0" ).to_string() );
	ensure_equals( "multiplication failed c", ( HNumber( "2" ) * HNumber( "3" ) ).to_string(), HNumber( "6" ).to_string() );
	ensure_equals( "multiplication failed d", ( HNumber( "-2" ) * HNumber( "3" ) ).to_string(), HNumber( "-6" ).to_string() );
	ensure_equals( "multiplication failed e", ( HNumber( "-2" ) * HNumber( "-3" ) ).to_string(), HNumber( "6" ).to_string() );
	ensure_equals( "multiplication failed f", ( HNumber( "12.34" ) * HNumber( "-7.321" ) ).to_string(), HNumber( "-90.34114" ).to_string() );
	ensure_equals( "multiplication failed g", ( HNumber( "123.4567" ) * HNumber( "100" ) ).to_string(), HNumber( "12345.67" ).to_string() );
	ensure_equals( "multiplication failed h", ( HNumber( "12.345" ) * HNumber( "100000" ) ).to_string(), HNumber( "1234500" ).to_string() );
	ensure_equals( "multiplication failed i", ( HNumber( "1234" ) * HNumber( "0.001" ) ).to_string(), HNumber( "1.234" ).to_string() );
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
		_bc.read_until( res );
		msg = "multiplication of random a = " + as + " and b = " + bs + " failed";
		ensure_equals( msg, ( a * b ).to_string(), HNumber( res ).to_string() );
		msg += "(R)";
		ensure_equals( msg, ( b * a ).to_string(), HNumber( res ).to_string() );
		}
	}

/* substraction */
template<>
template<>
void module::test<20>( void )
	{
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
		_bc.read_until( res );
		ensure_equals( msg, ( a - b ).to_string(), HNumber( res ).to_string() );
		msg += "(R)";
		ensure_equals( msg, ( b - a ).to_string(), ( -HNumber( res ) ).to_string() );
		}
	}

/* division */
template<>
template<>
void module::test<21>( void )
	{
	try
		{
		HNumber n( "1" );
		HNumber x;
		n /= x;
		fail( "division by zero performed" );
		}
	catch ( HException& )
		{
		// ok
		}
	cout << "a" << endl;
	ensure_equals( "division failed a", ( HNumber( "0" ) / HNumber( "1" ) ).to_string(), HNumber( "0" ).to_string() );
	cout << "b" << endl;
	ensure_equals( "division failed b", ( HNumber( "0" ) / HNumber( "-1" ) ).to_string(), HNumber( "0" ).to_string() );
	cout << "c" << endl;
	ensure_equals( "division failed c", ( HNumber( "1" ) / HNumber( "1" ) ).to_string(), HNumber( "1" ).to_string() );
	ensure_equals( "division failed c 0", ( HNumber( "10.01" ) / HNumber( "1" ) ).to_string(), HNumber( "10.01" ).to_string() );
	ensure_equals( "division failed c 1", ( HNumber( "10.01" ) / HNumber( "10" ) ).to_string(), HNumber( "1.001" ).to_string() );
	ensure_equals( "division failed c 2", ( HNumber( "10.01" ) / HNumber( "100" ) ).to_string(), HNumber( ".1001" ).to_string() );
	ensure_equals( "division failed c 3", ( HNumber( "10.01" ) / HNumber( "1000" ) ).to_string(), HNumber( ".01001" ).to_string() );
	ensure_equals( "division failed c 4", ( HNumber( "10.01" ) / HNumber( "10000" ) ).to_string(), HNumber( ".001001" ).to_string() );
	ensure_equals( "division failed c 5", ( HNumber( "10.01" ) / HNumber( ".1" ) ).to_string(), HNumber( "100.1" ).to_string() );
	ensure_equals( "division failed c 6", ( HNumber( "10.01" ) / HNumber( ".01" ) ).to_string(), HNumber( "1001" ).to_string() );
	ensure_equals( "division failed c 7", ( HNumber( "10.01" ) / HNumber( ".001" ) ).to_string(), HNumber( "10010" ).to_string() );
	ensure_equals( "division failed c 8", ( HNumber( "10.01" ) / HNumber( ".0001" ) ).to_string(), HNumber( "100100" ).to_string() );
	cout << "d" << endl;
	ensure_equals( "division failed d", ( HNumber( "1" ) / HNumber( "-1" ) ).to_string(), HNumber( "-1" ).to_string() );
	cout << "e" << endl;
	ensure_equals( "division failed e", ( HNumber( "-1" ) / HNumber( "1" ) ).to_string(), HNumber( "-1" ).to_string() );
	cout << "f" << endl;
	ensure_equals( "division failed f", ( HNumber( "-1" ) / HNumber( "-1" ) ).to_string(), HNumber( "1" ).to_string() );
	cout << "g" << endl;
	ensure_equals( "division failed g", ( HNumber( "2" ) / HNumber( "4" ) ).to_string(), HNumber( ".5" ).to_string() );
	cout << "h" << endl;
	ensure_equals( "division failed h", ( HNumber( "4" ) / HNumber( "2" ) ).to_string(), HNumber( "2" ).to_string() );
	cout << "x" << endl;
	ensure_equals( "division failed x", ( HNumber( "2468" ) / HNumber( "2" ) ).to_string(), HNumber( "1234" ).to_string() );
	cout << "i" << endl;
	ensure_equals( "division failed i", ( HNumber( "100" ) / HNumber( "5" ) ).to_string(), HNumber( "20" ).to_string() );
	cout << "j" << endl;
	ensure_equals( "division failed j", ( HNumber( "5" ) / HNumber( "100" ) ).to_string(), HNumber( ".05" ).to_string() );
	cout << "k" << endl;
	ensure_equals( "division failed k", ( HNumber( "3.144" ) / HNumber( ".03" ) ).to_string(), HNumber( "104.8" ).to_string() );
	_bc.spawn( BC_PATH );
	HString msg;
	HString res;
	HString as;
	HString bs;
	_bc << "scale=100" << endl;
	for ( int long i = 0; i < 1000; ++ i )
		{
		HNumber a( random_real() );
		double long den = random_real();
		den || ++ den;
		HNumber b( den );
		as = a.to_string();
		bs = b.to_string();
		_bc << as << "/ " << bs << endl;
		_bc.read_until( res );
		msg = "division of random a = " + as + " and b = " + bs + " failed";
		ensure_equals( msg, ( a / b ).to_string(), HNumber( res ).to_string() );
		}
	}

/* opposite */
template<>
template<>
void module::test<22>( void )
	{
	ensure_equals( "opposite failed a", ( - HNumber( "0" ) ).to_string(), HNumber( "0" ).to_string() );
	ensure_equals( "opposite failed b", ( - HNumber( "1" ) ).to_string(), HNumber( "-1" ).to_string() );
	ensure_equals( "opposite failed c", ( - HNumber( "-1" ) ).to_string(), HNumber( "1" ).to_string() );
	ensure_equals( "opposite failed d", ( - HNumber( ".01" ) ).to_string(), HNumber( "-.01" ).to_string() );
	ensure_equals( "opposite failed e", ( - HNumber( "-.01" ) ).to_string(), HNumber( ".01" ).to_string() );
	}

/* bc */
template<>
template<>
void module::test<23>( void )
	{
	HNumber n = 3;
	/* n ^= 333333; time: 9:26.91 vs 0:06.01 of bc */
	n ^= 3333;
	cout << n.to_string() << endl;
	}

}

