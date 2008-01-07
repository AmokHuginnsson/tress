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
	};

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
	ensure( "lower failed g", HNumber( "2.734543" ) < HNumber( "3.145" ) );

	ensure( "lower failed h", ! ( HNumber( "1" ) < HNumber( "-1" ) ) );
	ensure( "lower failed i", ! ( HNumber( "0" ) < HNumber( "-1" ) ) );
	ensure( "lower failed j", ! ( HNumber( "-0.5" ) < HNumber( "-1" ) ) );
	ensure( "lower failed k", ! ( HNumber( "0.5" ) < HNumber( "0" ) ) );
	ensure( "lower failed l", ! ( HNumber( "0.5" ) < HNumber( ".2" ) ) );
	ensure( "lower failed m", ! ( HNumber( "1" ) < HNumber( ".2" ) ) );
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
	ensure( "greater failed g", HNumber( "3.145" ) > HNumber( "2.734543" ) );

	ensure( "greater failed h", ! ( HNumber( "-1" ) > HNumber( "1" ) ) );
	ensure( "greater failed i", ! ( HNumber( "-1" ) > HNumber( "0" ) ) );
	ensure( "greater failed j", ! ( HNumber( "-1" ) > HNumber( "-0.5" ) ) );
	ensure( "greater failed k", ! ( HNumber( "0" ) > HNumber( "0.5" ) ) );
	ensure( "greater failed l", ! ( HNumber( ".2" ) > HNumber( "0.5" ) ) );
	ensure( "greater failed m", ! ( HNumber( ".2" ) > HNumber( "1" ) ) );
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
	ensure( "greater-eq failed g", HNumber( "3.145" ) >= HNumber( "2.734543" ) );

	ensure( "greater-eq failed h", ! ( HNumber( "-1" ) >= HNumber( "1" ) ) );
	ensure( "greater-eq failed i", ! ( HNumber( "-1" ) >= HNumber( "0" ) ) );
	ensure( "greater-eq failed j", ! ( HNumber( "-1" ) >= HNumber( "-0.5" ) ) );
	ensure( "greater-eq failed k", ! ( HNumber( "0" ) >= HNumber( "0.5" ) ) );
	ensure( "greater-eq failed l", ! ( HNumber( ".2" ) >= HNumber( "0.5" ) ) );
	ensure( "greater-eq failed m", ! ( HNumber( ".2" ) >= HNumber( "1" ) ) );
	ensure( "greater-eq failed n", ! ( HNumber( "2.734543" ) >= HNumber( "3.145" ) ) );
	ensure( "greater-eq failed o", HNumber( "1" ) >= HNumber( "1" ) );
	ensure( "greater-eq failed p", HNumber( "-1" ) >= HNumber( "-1" ) );
	ensure( "greater-eq failed q", HNumber( ".1" ) >= HNumber( ".1" ) );
	ensure( "greater-eq failed r", HNumber( "-.1" ) >= HNumber( "-.1" ) );
	ensure( "greater-eq failed s", HNumber( "0" ) >= HNumber( "0" ) );
	}

/* addition */
template<>
template<>
void module::test<18>( void )
	{
	ensure_equals( "addition failed a", ( HNumber( "" ) + HNumber( "" ) ).to_string(), HNumber( "" ).to_string() );
	}

/* multiplication */
template<>
template<>
void module::test<19>( void )
	{
	}

/* substraction */
template<>
template<>
void module::test<20>( void )
	{
	}

/* division */
template<>
template<>
void module::test<21>( void )
	{
	}

}

