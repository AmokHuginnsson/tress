/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hmemory.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_tools_hmemory
	{
	static int const SIZE = 256;
	char _buf[SIZE];
	tut_yaal_tools_hmemory( void );
	virtual ~tut_yaal_tools_hmemory( void ) {}
	};

tut_yaal_tools_hmemory::tut_yaal_tools_hmemory( void ) : _buf()
	{
	fill_n( _buf, SIZE, 0 );
	}

TUT_TEST_GROUP_N( tut_yaal_tools_hmemory, "yaal::tools::HMemory" );

TUT_UNIT_TEST_N( 1, "constructor" )
	try
		{
		HMemory m( NULL, 10 );
		FAIL( "construction of null block succeeded" );
		}
	catch ( HFailedAssertion const& )
		{
		// ok
		}
	try
		{
		char b[10];
		HMemory m( b, 0 );
		FAIL( "zero length block construction succeeded" );
		}
	catch ( HFailedAssertion const& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "simple write" )
	char const pattern[] = "Ala ma kota.";
	::memset( _buf, 0, SIZE );
	HMemory m( _buf, SIZE );
	m << pattern;
	ENSURE_EQUALS( "simple write failed", memcmp( _buf, pattern, sizeof ( pattern ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "stacked writes" )
	char const pattern[] = "Ala ma kota.";
	char const pattern_hi[] = "Ala ma";
	char const pattern_lo[] = " kota.";
	::memset( _buf, 0, SIZE );
	HMemory m( _buf, SIZE );
	m << pattern_hi << pattern_lo;
	ENSURE_EQUALS( "simple write failed", memcmp( _buf, pattern, sizeof ( pattern ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "read from empty" )
	HMemory m( _buf, SIZE, HMemory::INITIAL_STATE::INVALID );
	HString line;
	ENSURE_EQUALS( "read byte count from empty", m.read_until( line ), 0 );
TUT_TEARDOWN()

}

