/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_.cxx - this file is integral part of `tress' project.

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
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_htokenizer
	{
	static char const* const split_inc_failed;
	static char const* const split_skip_failed;
	static char const* const split_invalid_success;
	virtual ~tut_yaal_hcore_htokenizer( void ) {}
	};

char const* const tut_yaal_hcore_htokenizer::split_inc_failed = "split include empty failed";
char const* const tut_yaal_hcore_htokenizer::split_skip_failed = "split skip empty failed";
char const* const tut_yaal_hcore_htokenizer::split_invalid_success = "split failed due to invalid success";

TUT_TEST_GROUP_N( tut_yaal_hcore_htokenizer, "yaal::hcore::HTokenizer" );

TUT_UNIT_TEST_N( 1, "/* direct split include empty set[a]*/" )
	HTokenizer t( ",aa,bb", "," );
	ensure_equals( split_inc_failed, t[ 0 ], "" );
	ensure_equals( split_inc_failed, t[ 1 ], "aa" );
	ensure_equals( split_inc_failed, t[ 2 ], "bb" );
	ensure_equals( split_inc_failed, t[ 3 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* direct split include empty set[b]*/" )
	HTokenizer t( "aa,bb", "," );
	ensure_equals( split_inc_failed, t[ 0 ], "aa" );
	ensure_equals( split_inc_failed, t[ 1 ], "bb" );
	ensure_equals( split_inc_failed, t[ 2 ], "" );
	ensure_equals( split_inc_failed, t[ 3 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* direct split include empty set[c]*/" )
	HTokenizer t( "aa,bb,", "," );
	ensure_equals( split_inc_failed, t[ 0 ], "aa" );
	ensure_equals( split_inc_failed, t[ 1 ], "bb" );
	ensure_equals( split_inc_failed, t[ 2 ], "" );
	ensure_equals( split_inc_failed, t[ 3 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* direct split include empty set[d]*/" )
	HTokenizer t( ",aa,", "," );
	ensure_equals( split_inc_failed, t[ 0 ], "" );
	ensure_equals( split_inc_failed, t[ 1 ], "aa" );
	ensure_equals( split_inc_failed, t[ 2 ], "" );
	ensure_equals( split_inc_failed, t[ 3 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* direct split include empty set[e]*/" )
	HTokenizer t( ",,,aa,,", "," );
	ensure_equals( split_inc_failed, t[ 0 ], "" );
	ensure_equals( split_inc_failed, t[ 1 ], "" );
	ensure_equals( split_inc_failed, t[ 2 ], "" );
	ensure_equals( split_inc_failed, t[ 3 ], "aa" );
	ensure_equals( split_inc_failed, t[ 4 ], "" );
	ensure_equals( split_inc_failed, t[ 5 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* direct split include empty set[f]*/" )
	HTokenizer t1( "a", ";" );
	HTokenizer t2( "a", "a" );
	ensure_equals( split_inc_failed, t1[ 0 ], "a" );
	ensure_equals( split_inc_failed, t1[ 1 ], "" );
	ensure_equals( split_inc_failed, t1[ 2 ], "" );
	ensure_equals( split_inc_failed, t2[ 0 ], "" );
	ensure_equals( split_inc_failed, t2[ 1 ], "" );
	ensure_equals( split_inc_failed, t2[ 2 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* direct split skip empty set[a]*/" )
	HTokenizer t( ",aa,bb", ",", HTokenizer::SKIP_EMPTY );
	ensure_equals( split_skip_failed, t[ 0 ], "aa" );
	ensure_equals( split_skip_failed, t[ 1 ], "bb" );
	try
		{
		t[ 2 ];
		fail( split_invalid_success );
		}
	catch ( HTokenizerException const& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* direct split skip empty set[b]*/" )
	HTokenizer t( "aa,bb", ",", HTokenizer::SKIP_EMPTY );
	ensure_equals( split_skip_failed, t[ 0 ], "aa" );
	ensure_equals( split_skip_failed, t[ 1 ], "bb" );
	try
		{
		t[ 2 ];
		fail( split_invalid_success );
		}
	catch ( HTokenizerException const& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* direct split skip empty set[c]*/" )
	HTokenizer t( "aa,bb,", ",", HTokenizer::SKIP_EMPTY );
	ensure_equals( split_skip_failed, t[ 0 ], "aa" );
	ensure_equals( split_skip_failed, t[ 1 ], "bb" );
	try
		{
		t[ 2 ];
		fail( split_invalid_success );
		}
	catch ( HTokenizerException const& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "/* direct split skip empty set[d]*/" )
	HTokenizer t( ",aa,", ",", HTokenizer::SKIP_EMPTY );
	ensure_equals( split_skip_failed, t[ 0 ], "aa" );
	try
		{
		t[ 1 ];
		fail( split_invalid_success );
		}
	catch ( HTokenizerException const& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* direct split skip empty set[e]*/" )
	HTokenizer t( ",,,aa,,", ",", HTokenizer::SKIP_EMPTY );
	ensure_equals( split_skip_failed, t[ 0 ], "aa" );
	try
		{
		t[ 1 ];
		fail( split_invalid_success );
		}
	catch ( HTokenizerException const& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* direct split skip empty set[f]*/" )
	HTokenizer t1( "a", ";", HTokenizer::SKIP_EMPTY );
	HTokenizer t2( "a", "a", HTokenizer::SKIP_EMPTY );
	ensure_equals( split_skip_failed, t1[ 0 ], "a" );
	try
		{
		t1[ 1 ];
		fail( split_invalid_success );
		}
	catch ( HTokenizerException const& )
		{
		// ok
		}
	try
		{
		t2[ 0 ];
		fail( split_invalid_success );
		}
	catch ( HTokenizerException const& )
		{
		// ok
		}
TUT_TEARDOWN()

}

