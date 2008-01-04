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
	ensure_equals( "number not created correctly", n.to_string(), "3.141593" );
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
	ensure_equals( "number not created correctly", n.to_string(), "3.141593" );
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

	char const* const pn5 = "--2.7";
	HNumber n5( pn5 );
	ensure_equals( "number not created correctly", n5.to_string(), "-2.7" );
	ensure_equals( "bad dafault precision", n5.get_precision(), HNumber::D_DEFAULT_PRECISION );
	cout << "| n5 =" << n5.to_string() << " |" << endl;

	try
		{
		HNumber( "-.-2.7" );
		fail( "phony number created" );
		}
	catch ( HException& )
		{
		// ok
		}

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
	}

/* construct from string and specify precision */
template<>
template<>
void module::test<5>( void )
	{
	}

/* copy constructor */
template<>
template<>
void module::test<6>( void )
	{
	}

}

