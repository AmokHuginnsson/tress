/* Read tress/LICENSE.md file for copyright and licensing information. */

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
	/* delim by any, escape */ {
		HTokenizer t( ",aa\\:zz;bb\\;cc", ",:;", HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "aa\\:zz" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 2 ], "bb\\;cc" );
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
	/* delim by any, escape */ {
		HTokenizer t( "aa\\,zz,bb\\,cc", ",", HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "aa\\,zz" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "bb\\,cc" );
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
	/* delim by any, escape */ {
		HTokenizer t( "aa\\:zz,bb\\:cc;", ";:,", HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "aa\\:zz" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "bb\\:cc" );
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
	/* delim by any */ {
		HTokenizer t( ";aa\\:zz,", ",:;", HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "aa\\:zz" );
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
	/* delim by any, escape */ {
		HTokenizer t( ",;,aa\\:zz;,", ",:;", HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_inc_any_failed, t[ 0 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 1 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 2 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t[ 3 ], "aa\\:zz" );
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
	/* delim by any */ {
		HTokenizer t1( "a\\:z", ";:,", HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		HTokenizer t2( "a\\:z", "a", HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_inc_any_failed, t1[ 0 ], "a\\:z" );
		ENSURE_EQUALS( split_inc_any_failed, t1[ 1 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t1[ 2 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t2[ 0 ], "" );
		ENSURE_EQUALS( split_inc_any_failed, t2[ 1 ], "\\:z" );
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
	/* delim by any, escape */ {
		HTokenizer t( ",aa\\:zz,bb\\:cc", ",", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa\\:zz" );
		ENSURE_EQUALS( split_skip_any_failed, t[ 1 ], "bb\\:cc" );
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
	/* delim by any, escape */ {
		HTokenizer t( "aa\\:zz,bb\\:cc", ";:,", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa\\:zz" );
		ENSURE_EQUALS( split_skip_any_failed, t[ 1 ], "bb\\:cc" );
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
	/* delim by any, escape */ {
		HTokenizer t( "aa\\:zz,bb\\:cc,", ",", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa\\:zz" );
		ENSURE_EQUALS( split_skip_any_failed, t[ 1 ], "bb\\:cc" );
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
	/* delim by any, escape */ {
		HTokenizer t( ";aa\\:zz,", ",:;", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa\\:zz" );
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
	/* delim by any */ {
		HTokenizer t( ",;,aa\\:zz;,", ",:;", HTokenizer::behavior_t( HTokenizer::SKIP_EMPTY ) | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_skip_any_failed, t[ 0 ], "aa\\:zz" );
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
	/* delim by any, escape */ {
		HTokenizer t1( "a\\:z", ";:,", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		HTokenizer t2( "a\\:z", "a", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
		ENSURE_EQUALS( split_skip_any_failed, t1[ 0 ], "a\\:z" );
		ENSURE_THROW( split_skip_any_invalid_success, t1[ 1 ], HTokenizerException );
		ENSURE_EQUALS( split_skip_any_failed, t2[ 0 ], "\\:z" );
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
		HTokenizer tokenizer( text, character_class<CHARACTER_CLASS::WHITESPACE>().data() );
		HTokenizer::HIterator it( tokenizer.begin() );
		ENSURE( "begin failed", it != tokenizer.end() );
		ENSURE_EQUALS( "dereferencing token iterator failed", *it, text );
	}
	/* delim by any */ {
		HString text( "list_commands" );
		HTokenizer tokenizer( text, character_class<CHARACTER_CLASS::WHITESPACE>().data(), HTokenizer::DELIMITED_BY_ANY_OF );
		HTokenizer::HIterator it( tokenizer.begin() );
		ENSURE( "begin failed", it != tokenizer.end() );
		ENSURE_EQUALS( "dereferencing token iterator failed", *it, text );
	}
	/* delim by any, escape */ {
		HString text( "list_commands" );
		HTokenizer tokenizer( text, character_class<CHARACTER_CLASS::WHITESPACE>().data(), HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
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
	/* delim by any, escape */ {
		/* scope */ {
			HTokenizer tokenizer( "", ".:;", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
			ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
		} {
			HTokenizer tokenizer( ",:;", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
			tokenizer.assign( "" );
			ENSURE( "bogus tokens on empty", ! ( tokenizer.begin() != tokenizer.end() ) );
		} {
			HTokenizer tokenizer( "Ala;ma,kota.", ",:;", HTokenizer::SKIP_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
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
	/* delim by any, escape */ {
		/* scope */ {
			HTokenizer tokenizer( "", ",:;", HTokenizer::INCLUDE_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		} {
			HTokenizer tokenizer( ",:;", HTokenizer::INCLUDE_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
			tokenizer.assign( "" );
			ENSURE( "no tokens on sep-only", tokenizer.begin() != tokenizer.end() );
		} {
			HTokenizer tokenizer( "Ala;ma,kota.", ",:;", HTokenizer::INCLUDE_EMPTY | HTokenizer::DELIMITED_BY_ANY_OF, '\\'_ycp );
			tokenizer.assign( "" );
			ENSURE( "no tokens on non-empty", tokenizer.begin() != tokenizer.end() );
		}
	}
TUT_TEARDOWN()

}

