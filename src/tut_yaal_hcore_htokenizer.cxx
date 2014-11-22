/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/htokenizer.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_htokenizer : public simple_mock<tut_yaal_hcore_htokenizer> {
	typedef simple_mock<tut_yaal_hcore_htokenizer> base_type;
	static char const* const split_inc_any_failed;
	static char const* const split_inc_whole_sc_failed;
	static char const* const split_inc_whole_mc_failed;
	static char const* const split_skip_any_failed;
	static char const* const split_skip_whole_sc_failed;
	static char const* const split_skip_whole_mc_failed;
	static char const* const split_skip_whole_sc_invalid_success;
	static char const* const split_skip_whole_mc_invalid_success;
	static char const* const split_skip_any_invalid_success;
	virtual ~tut_yaal_hcore_htokenizer( void ) {}
};

char const* const tut_yaal_hcore_htokenizer::split_inc_any_failed = "split include empty delim by any failed";
char const* const tut_yaal_hcore_htokenizer::split_inc_whole_sc_failed = "split include empty delim by whole single character failed";
char const* const tut_yaal_hcore_htokenizer::split_inc_whole_mc_failed = "split include empty delim by whole multi character failed";
char const* const tut_yaal_hcore_htokenizer::split_skip_whole_sc_failed = "split skip empty delim by whole single character failed";
char const* const tut_yaal_hcore_htokenizer::split_skip_whole_mc_failed = "split skip empty delim by whole multi character failed";
char const* const tut_yaal_hcore_htokenizer::split_skip_any_failed = "split skip empty delim by any failed";
char const* const tut_yaal_hcore_htokenizer::split_skip_whole_sc_invalid_success = "split skip delim by whole single character failed due to invalid success";
char const* const tut_yaal_hcore_htokenizer::split_skip_whole_mc_invalid_success = "split skip delim by whole multi character failed due to invalid success";
char const* const tut_yaal_hcore_htokenizer::split_skip_any_invalid_success = "split skip delim by any failed due to invalid success";

TUT_TEST_GROUP( tut_yaal_hcore_htokenizer, "yaal::hcore::HTokenizer" );

TUT_UNIT_TEST( "direct split include empty set[a]*/" )
	/* delim by whole single character */ {
		HTokenizer t( ",aa,bb", "," );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 1 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 2 ], "bb" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 3 ], "" );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "://aa://bb", "://" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 1 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 2 ], "bb" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 3 ], "" );
	}
	/* delim by any */ {
		HTokenizer t( ",aa;bb", ",:;", HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "aa" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 2 ], "bb" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 3 ], "" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split include empty set[b]*/" )
	/* delim by whole single character */ {
		HTokenizer t( "aa,bb", "," );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 1 ], "bb" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 3 ], "" );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "aa://bb", "://" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 1 ], "bb" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 3 ], "" );
	}
	/* delim by any */ {
		HTokenizer t( "aa,bb", ",", HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "bb" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 3 ], "" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split include empty set[c]*/" )
	/* delim by whole single character */ {
		HTokenizer t( "aa,bb,", "," );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 1 ], "bb" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 3 ], "" );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "aa://bb://", "://" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 1 ], "bb" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 3 ], "" );
	}
	/* delim by any */ {
		HTokenizer t( "aa,bb;", ";:,", HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "bb" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 3 ], "" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split include empty set[d]*/" )
	/* delim by whole single character */ {
		HTokenizer t( ",aa,", "," );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 1 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 3 ], "" );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "://aa://", "://" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 1 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 3 ], "" );
	}
	/* delim by any */ {
		HTokenizer t( ";aa,", ",:;", HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "aa" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 3 ], "" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split include empty set[e]*/" )
	/* delim by whole single character */ {
		HTokenizer t( ",,,aa,,", "," );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 1 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 3 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 4 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t[ 5 ], "" );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "://://://aa://://", "://" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 1 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 3 ], "aa" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 4 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t[ 5 ], "" );
	}
	/* delim by any */ {
		HTokenizer t( ",;,aa;,", ",:;", HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 3 ], "aa" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 4 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 5 ], "" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split include empty set[f]*/" )
	/* delim by whole single character */ {
		HTokenizer t1( "a", ";" );
		HTokenizer t2( "a", "a" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t1[ 0 ], "a" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t1[ 1 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t1[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t2[ 0 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t2[ 1 ], "" );
		ENSURE_EQUALS( split_inc_whole_sc_failed, t2[ 2 ], "" );
	}
	/* delim by whole multi character */ {
		HTokenizer t1( "a", "://" );
		HTokenizer t2( "a", "a" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t1[ 0 ], "a" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t1[ 1 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t1[ 2 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t2[ 0 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t2[ 1 ], "" );
		ENSURE_EQUALS( split_inc_whole_mc_failed, t2[ 2 ], "" );
	}
	/* delim by any */ {
		HTokenizer t1( "a", ";:,", HTokenizer::DELIMITED_BY_ANY_OF );
		HTokenizer t2( "a", "a", HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_inc_any_failed, t1[ 0 ], "a" );
		ENSURE_EQUALS( split_inc_any_failed, t1[ 1 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t1[ 2 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t2[ 0 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t2[ 1 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t2[ 2 ], "" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split skip empty set[a]*/" )
	/* delim by whole single character */ {
		HTokenizer t( ",aa,bb", ",", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_whole_sc_invalid_success, t[ 2 ], HTokenizerException );
	}
	/* delim by whole multi character */ {
		HTokenizer t( ",aa,bb", ",", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_whole_mc_invalid_success, t[ 2 ], HTokenizerException );
	}
	/* delim by any */ {
		HTokenizer t( ",aa,bb", ",", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_any_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_any_invalid_success, t[ 2 ], HTokenizerException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split skip empty set[b]*/" )
	/* delim by whole single character */ {
		HTokenizer t( "aa,bb", ",", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_whole_sc_invalid_success, t[ 2 ], HTokenizerException );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "aa://bb", "://", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_whole_mc_invalid_success, t[ 2 ], HTokenizerException );
	}
	/* delim by any */ {
		HTokenizer t( "aa,bb", ";:,", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_any_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_any_invalid_success, t[ 2 ], HTokenizerException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split skip empty set[c]*/" )
	/* delim by whole single character */ {
		HTokenizer t( "aa,bb,", ",", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_whole_sc_invalid_success, t[ 2 ], HTokenizerException );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "aa://bb://", "://", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_whole_mc_invalid_success, t[ 2 ], HTokenizerException );
	}
	/* delim by any */ {
		HTokenizer t( "aa,bb,", ",", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa" );
		ENSURE_EQUALS( split_skip_any_failed, t[ 1 ], "bb" );
		ENSURE_THROW( split_skip_any_invalid_success, t[ 2 ], HTokenizerException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split skip empty set[d]*/" )
	/* delim by whole single character */ {
		HTokenizer t( ",aa,", ",", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t[ 0 ], "aa" );
		ENSURE_THROW( split_skip_whole_sc_invalid_success, t[ 1 ], HTokenizerException );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "://aa://", "://", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t[ 0 ], "aa" );
		ENSURE_THROW( split_skip_whole_mc_invalid_success, t[ 1 ], HTokenizerException );
	}
	/* delim by any */ {
		HTokenizer t( ";aa,", ",:;", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa" );
		ENSURE_THROW( split_skip_any_invalid_success, t[ 1 ], HTokenizerException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split skip empty set[e]*/" )
	/* delim by whole single character */ {
		HTokenizer t( ",,,aa,,", ",", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t[ 0 ], "aa" );
		ENSURE_THROW( split_skip_whole_sc_invalid_success, t[ 1 ], HTokenizerException );
	}
	/* delim by whole multi character */ {
		HTokenizer t( "://://://aa://://", "://", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t[ 0 ], "aa" );
		ENSURE_THROW( split_skip_whole_mc_invalid_success, t[ 1 ], HTokenizerException );
	}
	/* delim by any */ {
		HTokenizer t( ",;,aa;,", ",:;", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa" );
		ENSURE_THROW( split_skip_any_invalid_success, t[ 1 ], HTokenizerException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "direct split skip empty set[f]*/" )
	/* delim by whole single character */ {
		HTokenizer t1( "a", ";", HTokenizer::SKIP_EMPTY );
		HTokenizer t2( "a", "a", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_sc_failed, t1[ 0 ], "a" );
		ENSURE_THROW( split_skip_whole_sc_invalid_success, t1[ 1 ], HTokenizerException );
		ENSURE_THROW( split_skip_whole_sc_invalid_success, t2[ 0 ], HTokenizerException );
	}
	/* delim by whole multi character */ {
		HTokenizer t1( "a", "://", HTokenizer::SKIP_EMPTY );
		HTokenizer t2( "a", "a", HTokenizer::SKIP_EMPTY );
		ENSURE_EQUALS( split_skip_whole_mc_failed, t1[ 0 ], "a" );
		ENSURE_THROW( split_skip_whole_mc_invalid_success, t1[ 1 ], HTokenizerException );
		ENSURE_THROW( split_skip_whole_mc_invalid_success, t2[ 0 ], HTokenizerException );
	}
	/* delim by any */ {
		HTokenizer t1( "a", ";:,", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF );
		HTokenizer t2( "a", "a", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF );
		ENSURE_EQUALS( split_skip_any_failed, t1[ 0 ], "a" );
		ENSURE_THROW( split_skip_any_invalid_success, t1[ 1 ], HTokenizerException );
		ENSURE_THROW( split_skip_any_invalid_success, t2[ 0 ], HTokenizerException );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "dereference iterator for single token" )
	/* delim by whole single character */ {
		HString text( "list_commands" );
		HTokenizer tokenizer( text, "," );
		HTokenizer::HIterator it( tokenizer.begin() );
		ENSURE( "begin failed", it != tokenizer.end() );
		ENSURE_EQUALS( "dereferencing token iterator failed", *it, text );
	}
	/* delim by whole multi character */ {
		HString text( "list_commands" );
		HTokenizer tokenizer( text, _whiteSpace_.data() );
		HTokenizer::HIterator it( tokenizer.begin() );
		ENSURE( "begin failed", it != tokenizer.end() );
		ENSURE_EQUALS( "dereferencing token iterator failed", *it, text );
	}
	/* delim by any */ {
		HString text( "list_commands" );
		HTokenizer tokenizer( text, _whiteSpace_.data(), HTokenizer::DELIMITED_BY_ANY_OF );
		HTokenizer::HIterator it( tokenizer.begin() );
		ENSURE( "begin failed", it != tokenizer.end() );
		ENSURE_EQUALS( "dereferencing token iterator failed", *it, text );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "tokenize on empty (skip empty)" )
	/* delim by whole single character */ {
		/* scope */ {
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
	}
	/* delim by whole multi character */ {
		/* scope */ {
			HTokenizer tokenizer( "", "://", HTokenizer::SKIP_EMPTY );
			ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
		} {
			HTokenizer tokenizer( "://", HTokenizer::SKIP_EMPTY );
			tokenizer.assign( "" );
			ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
		} {
			HTokenizer tokenizer( "Ala://ma://kota.", "://", HTokenizer::SKIP_EMPTY );
			tokenizer.assign( "" );
			ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
		}
	}
	/* delim by any */ {
		/* scope */ {
			HTokenizer tokenizer( "", ".:;", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF );
			ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
		} {
			HTokenizer tokenizer( ",:;", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF );
			tokenizer.assign( "" );
			ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
		} {
			HTokenizer tokenizer( "Ala;ma,kota.", ",:;", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF );
			tokenizer.assign( "" );
			ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "tokenize on empty (include empty)" )
	/* delim by whole single character */ {
		/* scope */ {
			HTokenizer tokenizer( "", "@", HTokenizer::INCLUDE_EMPTY );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		} {
			HTokenizer tokenizer( "@", HTokenizer::INCLUDE_EMPTY );
			tokenizer.assign( "" );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		} {
			HTokenizer tokenizer( "Ala@ma@kota.", "@", HTokenizer::INCLUDE_EMPTY );
			tokenizer.assign( "" );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		}
	}
	/* delim by whole multi character */ {
		/* scope */ {
			HTokenizer tokenizer( "", "://", HTokenizer::INCLUDE_EMPTY );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		} {
			HTokenizer tokenizer( "://", HTokenizer::INCLUDE_EMPTY );
			tokenizer.assign( "" );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		} {
			HTokenizer tokenizer( "Ala://ma://kota.", "://", HTokenizer::INCLUDE_EMPTY );
			tokenizer.assign( "" );
			ENSURE( "no tokens on non-empty", tokenizer.begin() != tokenizer.end() );
		}
	}
	/* delim by any */ {
		/* scope */ {
			HTokenizer tokenizer( "", ",:;", HTokenizer::INCLUDE_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		} {
			HTokenizer tokenizer( ",:;", HTokenizer::INCLUDE_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF );
			tokenizer.assign( "" );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		} {
			HTokenizer tokenizer( "Ala;ma,kota.", ",:;", HTokenizer::INCLUDE_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF );
			tokenizer.assign( "" );
			ENSURE( "no tokens on non-empty", tokenizer.begin() != tokenizer.end() );
		}
	}
TUT_TEARDOWN()

}

