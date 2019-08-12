/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/stringalgo.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::string;
using namespace tress::tut_helpers;

namespace tut {

char const* const msgLevFail = "failed to calculate levenshtein distance";

TUT_SIMPLE_MOCK( tut_yaal_tools_string );
TUT_TEST_GROUP( tut_yaal_tools_string, "yaal::tools::string" );

TUT_UNIT_TEST( "levenshtein distance same strings" )
	ENSURE_EQUALS( msgLevFail,
			distance( "tut_yaal_tools_string", "tut_yaal_tools_string", DISTANCE_METRIC::LEVENSHTEIN ), 0 );
	ENSURE_EQUALS( msgLevFail,
			distance( "tut_yaal_tools_string", "tut_yaal_tools_string", DISTANCE_METRIC::DAMERAU_LEVENSHTEIN ), 0 );
	ENSURE_EQUALS( msgLevFail,
			distance( "tut_yaal_tools_string", "tut_yaal_tools_string", DISTANCE_METRIC::QWERTY ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "levenshtein distance different strings" )
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abpdef", DISTANCE_METRIC::LEVENSHTEIN ), 1 );
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abpdef", DISTANCE_METRIC::DAMERAU_LEVENSHTEIN ), 1 );
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abpdef", DISTANCE_METRIC::QWERTY ), 2 );

	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abdcef", DISTANCE_METRIC::LEVENSHTEIN ), 2 );
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abdcef", DISTANCE_METRIC::DAMERAU_LEVENSHTEIN ), 1 );
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abdcef", DISTANCE_METRIC::QWERTY ), 1 );

	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "adcbef", DISTANCE_METRIC::LEVENSHTEIN ), 2 );
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "adcbef", DISTANCE_METRIC::DAMERAU_LEVENSHTEIN ), 2 );
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "adcbef", DISTANCE_METRIC::QWERTY ), 3 );

	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abvdef", DISTANCE_METRIC::LEVENSHTEIN ), 1 );
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abvdef", DISTANCE_METRIC::DAMERAU_LEVENSHTEIN ), 1 );
	ENSURE_EQUALS( msgLevFail, distance( "abcdef", "abvdef", DISTANCE_METRIC::QWERTY ), 1 );

	ENSURE_EQUALS( msgLevFail, distance( "Sunday", "Saturday", DISTANCE_METRIC::LEVENSHTEIN ), 3 );
	ENSURE_EQUALS( msgLevFail, distance( "Sunday", "Saturday", DISTANCE_METRIC::DAMERAU_LEVENSHTEIN ), 3 );
	ENSURE_EQUALS( msgLevFail, distance( "Sunday", "Saturday", DISTANCE_METRIC::QWERTY ), 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "split" )
	typedef HArray<HString> str_arr_t;
	str_arr_t sa( split<str_arr_t>( "Ala ma kota.", " " ) );
	ENSURE_EQUALS( "bad number of words", sa.get_size(), 3 );
	ENSURE_EQUALS( "bad word", sa[0], "Ala" );
	ENSURE_EQUALS( "bad word", sa[1], "ma" );
	ENSURE_EQUALS( "bad word", sa[2], "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "join" )
	typedef HArray<HString> str_arr_t;
	str_arr_t sa( { "Ala", "ma", "kota." } );
	ENSURE_EQUALS( "join failed", join( sa, " " ), "Ala ma kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "longest_common_prefix<HArray>" )
	typedef HArray<HString> str_arr_t;
	str_arr_t sa( { "forth", "fortran", "formula" } );
	ENSURE_EQUALS( "longest_common_prefix<HArray> failed", longest_common_prefix( sa ), "for" );
	str_arr_t sza( { "forth", "fortran", "formula", "zork" } );
	ENSURE_EQUALS( "longest_common_prefix<HArray> failed", longest_common_prefix( sza ), "" );
	str_arr_t sea;
	ENSURE_EQUALS( "longest_common_prefix<HArray> failed", longest_common_prefix( sea ), "" );
	str_arr_t soa( { "forth" } );
	ENSURE_EQUALS( "longest_common_prefix<HArray> failed", longest_common_prefix( soa ), "forth" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "longest_common_prefix<HList>" )
	typedef HList<HString> str_lst_t;
	str_lst_t sl( { "forth", "fortran", "formula" } );
	ENSURE_EQUALS( "longest_common_prefix<HList> failed", longest_common_prefix( sl ), "for" );
	str_lst_t szl( { "forth", "fortran", "formula", "zork" } );
	ENSURE_EQUALS( "longest_common_prefix<HList> failed", longest_common_prefix( szl ), "" );
	str_lst_t sel;
	ENSURE_EQUALS( "longest_common_prefix<HList> failed", longest_common_prefix( sel ), "" );
	str_lst_t sol( { "forth" } );
	ENSURE_EQUALS( "longest_common_prefix<HList> failed", longest_common_prefix( sol ), "forth" );
TUT_TEARDOWN()

}

