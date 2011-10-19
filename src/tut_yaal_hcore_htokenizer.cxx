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

#include <yaal/hcore/htokenizer.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_htokenizer {
	static char const* const split_inc_failed;
	static char const* const split_skip_failed;
	static char const* const split_invalid_success;
	virtual ~tut_yaal_hcore_htokenizer( void ) {}
};

char const* const tut_yaal_hcore_htokenizer::split_inc_failed = "split include empty failed";
char const* const tut_yaal_hcore_htokenizer::split_skip_failed = "split skip empty failed";
char const* const tut_yaal_hcore_htokenizer::split_invalid_success = "split failed due to invalid success";

TUT_TEST_GROUP( tut_yaal_hcore_htokenizer, "yaal::hcore::HTokenizer" );

TUT_UNIT_TEST( 1, "direct split include empty set[a]*/" )
	HTokenizer t( ",aa,bb", "," );
	ENSURE_EQUALS( split_inc_failed, t[ 0 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 1 ], "aa" );
	ENSURE_EQUALS( split_inc_failed, t[ 2 ], "bb" );
	ENSURE_EQUALS( split_inc_failed, t[ 3 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "direct split include empty set[b]*/" )
	HTokenizer t( "aa,bb", "," );
	ENSURE_EQUALS( split_inc_failed, t[ 0 ], "aa" );
	ENSURE_EQUALS( split_inc_failed, t[ 1 ], "bb" );
	ENSURE_EQUALS( split_inc_failed, t[ 2 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 3 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "direct split include empty set[c]*/" )
	HTokenizer t( "aa,bb,", "," );
	ENSURE_EQUALS( split_inc_failed, t[ 0 ], "aa" );
	ENSURE_EQUALS( split_inc_failed, t[ 1 ], "bb" );
	ENSURE_EQUALS( split_inc_failed, t[ 2 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 3 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "direct split include empty set[d]*/" )
	HTokenizer t( ",aa,", "," );
	ENSURE_EQUALS( split_inc_failed, t[ 0 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 1 ], "aa" );
	ENSURE_EQUALS( split_inc_failed, t[ 2 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 3 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "direct split include empty set[e]*/" )
	HTokenizer t( ",,,aa,,", "," );
	ENSURE_EQUALS( split_inc_failed, t[ 0 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 1 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 2 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 3 ], "aa" );
	ENSURE_EQUALS( split_inc_failed, t[ 4 ], "" );
	ENSURE_EQUALS( split_inc_failed, t[ 5 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "direct split include empty set[f]*/" )
	HTokenizer t1( "a", ";" );
	HTokenizer t2( "a", "a" );
	ENSURE_EQUALS( split_inc_failed, t1[ 0 ], "a" );
	ENSURE_EQUALS( split_inc_failed, t1[ 1 ], "" );
	ENSURE_EQUALS( split_inc_failed, t1[ 2 ], "" );
	ENSURE_EQUALS( split_inc_failed, t2[ 0 ], "" );
	ENSURE_EQUALS( split_inc_failed, t2[ 1 ], "" );
	ENSURE_EQUALS( split_inc_failed, t2[ 2 ], "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "direct split skip empty set[a]*/" )
	HTokenizer t( ",aa,bb", ",", HTokenizer::SKIP_EMPTY );
	ENSURE_EQUALS( split_skip_failed, t[ 0 ], "aa" );
	ENSURE_EQUALS( split_skip_failed, t[ 1 ], "bb" );
	try {
		t[ 2 ];
		FAIL( split_invalid_success );
	} catch ( HTokenizerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "direct split skip empty set[b]*/" )
	HTokenizer t( "aa,bb", ",", HTokenizer::SKIP_EMPTY );
	ENSURE_EQUALS( split_skip_failed, t[ 0 ], "aa" );
	ENSURE_EQUALS( split_skip_failed, t[ 1 ], "bb" );
	try {
		t[ 2 ];
		FAIL( split_invalid_success );
	} catch ( HTokenizerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "direct split skip empty set[c]*/" )
	HTokenizer t( "aa,bb,", ",", HTokenizer::SKIP_EMPTY );
	ENSURE_EQUALS( split_skip_failed, t[ 0 ], "aa" );
	ENSURE_EQUALS( split_skip_failed, t[ 1 ], "bb" );
	try {
		t[ 2 ];
		FAIL( split_invalid_success );
	} catch ( HTokenizerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "direct split skip empty set[d]*/" )
	HTokenizer t( ",aa,", ",", HTokenizer::SKIP_EMPTY );
	ENSURE_EQUALS( split_skip_failed, t[ 0 ], "aa" );
	try {
		t[ 1 ];
		FAIL( split_invalid_success );
	} catch ( HTokenizerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "direct split skip empty set[e]*/" )
	HTokenizer t( ",,,aa,,", ",", HTokenizer::SKIP_EMPTY );
	ENSURE_EQUALS( split_skip_failed, t[ 0 ], "aa" );
	try {
		t[ 1 ];
		FAIL( split_invalid_success );
	} catch ( HTokenizerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "direct split skip empty set[f]*/" )
	HTokenizer t1( "a", ";", HTokenizer::SKIP_EMPTY );
	HTokenizer t2( "a", "a", HTokenizer::SKIP_EMPTY );
	ENSURE_EQUALS( split_skip_failed, t1[ 0 ], "a" );
	try {
		t1[ 1 ];
		FAIL( split_invalid_success );
	} catch ( HTokenizerException const& ) {
		// ok
	}
	try {
		t2[ 0 ];
		FAIL( split_invalid_success );
	} catch ( HTokenizerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "dereference iterator for single token" )
	HString text( "list_commands" );
	HTokenizer tokenizer( text, _whiteSpace_.data() );
	HTokenizer::HIterator it( tokenizer.begin() );
	ENSURE( "begin failed", it != tokenizer.end() );
	ENSURE_EQUALS( "dereferencing token iterator failed", *it, text );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "tokenize on empty (skip empty)" ) {
	HTokenizer tokenizer( "", "@", HTokenizer::SKIP_EMPTY );
	ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
} {
	HTokenizer tokenizer( "@", HTokenizer::SKIP_EMPTY );
	tokenizer.assign( "" );
	ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
} {
	HTokenizer tokenizer( "Ala@ma@kota.", "@", HTokenizer::SKIP_EMPTY );
	tokenizer.assign( "" );
	ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
}
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "tokenize on empty (include empty)" ) {
	HTokenizer tokenizer( "", "@", HTokenizer::INCLUDE_EMPTY );
	ENSURE( "bogus tokens on empty", tokenizer.begin() != tokenizer.end() );
} {
	HTokenizer tokenizer( "@", HTokenizer::INCLUDE_EMPTY );
	tokenizer.assign( "" );
	ENSURE( "bogus tokens on empty", tokenizer.begin() != tokenizer.end() );
} {
	HTokenizer tokenizer( "Ala@ma@kota.", "@", HTokenizer::INCLUDE_EMPTY );
	tokenizer.assign( "" );
	ENSURE( "bogus tokens on empty", tokenizer.begin() != tokenizer.end() );
}
TUT_TEARDOWN()

}

