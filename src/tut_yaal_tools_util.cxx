/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/unicode.hxx>
#include <yaal/hcore/hprogramoptionshandler.hxx>
#include <yaal/tools/util.hxx>
#include <yaal/tools/escape.hxx>
#include <yaal/tools/hexpression.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_util );
TUT_TEST_GROUP( tut_yaal_tools_util, "yaal::tools::util" );

TUT_UNIT_TEST( "(escape) EscapeTable constrctor" )
	ENSURE_THROW( "bad 1 parameter accepted", EscapeTable et( nullptr, 1, "n", 1 ), HFailedAssertion );
	ENSURE_THROW( "bad 3 parameter accepted", EscapeTable et( "\n", 1, nullptr, 1 ), HFailedAssertion );
	ENSURE_THROW( "size mismatch accepted", EscapeTable et( "\n", 1, "nm", 2 ), HFailedAssertion );
	EscapeTable et( "\n", 1, "n", 1 );
	ENSURE_EQUALS( "escape table preparaton failed", et._rawToSafe[ static_cast<int>( 'a' ) ], 'a' );
	ENSURE_EQUALS( "escape table preparaton failed", et._safeToRaw[ static_cast<int>( 'a' ) ], 'a' );
	ENSURE_EQUALS( "escape table preparaton failed", et._rawToSafe[ static_cast<int>( '\n' ) ], 'n' );
	ENSURE_EQUALS( "escape table preparaton failed", et._safeToRaw[ static_cast<int>( 'n' ) ], '\n' );
TUT_TEARDOWN()

TUT_UNIT_TEST( "escape" )
	EscapeTable et( "\n", 1, "n", 1 );
	HString s( "Ala\nma\nkota." );
	HString es( s );
	escape( es, et );
	ENSURE_EQUALS( "escaping failed", es, "Ala\\nma\\nkota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "unescape" )
	EscapeTable et( "\n", 1, "n", 1 );
	HString s( "Ala\nma\nkota." );
	HString es( s );
	escape( es, et );
	ENSURE_EQUALS( "escaping failed", es, "Ala\\nma\\nkota." );
	unescape( es, et );
	ENSURE_EQUALS( "unescaping failed", es, s );
TUT_TEARDOWN()

TUT_UNIT_TEST( "escape_copy" )
	ENSURE_EQUALS( "escaping (copy) failed", escape_copy( "Ala\nma\nkota.", EscapeTable( "\n", 1, "n", 1 ) ), "Ala\\nma\\nkota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "unescape_copy" )
	ENSURE_EQUALS( "unescaping (copy) failed", unescape_copy( "Ala\\nma\\nkota.", EscapeTable( "\n", 1, "n", 1 ) ), "Ala\nma\nkota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "unescape_copy with escaper as literal" )
	ENSURE_EQUALS( "unescaping (copy) with escaper as literal failed",
			unescape_copy( "Alan\\nna\\nkontach.", EscapeTable( "\n", 1, "n", 1 ) ), "Alan\nna\nkontach." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mask_escape/unmask_escape" )
	/* u8 */ {
		HString s( "some text \\${HOME} more" );
		HString escaped( s );
		escape_mask_map_t emm;
		mask_escape( escaped, emm );
		ENSURE_EQUALS( "mangled normal char", escaped[10], '\\'_ycp );
		ENSURE_EQUALS( "escaped char not masked", escaped[11], unicode::CODE_POINT::SUPPLEMENTARY_PRIVATE_USE_AREA_B );
		unmask_escape( escaped, emm );
		ENSURE_EQUALS( "failed to unmask", escaped, s );
	}
	/* u16 */ {
		HString s( "some text \\${HOME} moreąż" );
		HString escaped( s );
		escape_mask_map_t emm;
		mask_escape( escaped, emm );
		ENSURE_EQUALS( "mangled normal char", escaped[10], '\\'_ycp );
		ENSURE_EQUALS( "escaped char not masked", escaped[11], unicode::CODE_POINT::SUPPLEMENTARY_PRIVATE_USE_AREA_B );
		unmask_escape( escaped, emm );
		ENSURE_EQUALS( "failed to unmask", escaped, s );
	}
	/* u32 */ {
		HString s( "some text \\${HOME} more" );
		s.push_back( unicode::CODE_POINT::EMOJI_SNAKE );
		HString escaped( s );
		escape_mask_map_t emm;
		mask_escape( escaped, emm );
		ENSURE_EQUALS( "mangled normal char", escaped[10], '\\'_ycp );
		ENSURE_EQUALS( "escaped char not masked", escaped[11], unicode::CODE_POINT::SUPPLEMENTARY_PRIVATE_USE_AREA_B );
		unmask_escape( escaped, emm );
		ENSURE_EQUALS( "failed to unmask", escaped, s );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "hide/unhide" )
	HString s( "yyXXzzXXXXqqXXmm" );
	hide( s, "XXXX" );
	s.replace( "XX", "ZZ" );
	unhide( s, "XXXX" );
	ENSURE_EQUALS( "hide/unhide failed", s, "yyZZzzXXXXqqZZmm" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(atof_ex) complex and valid number" )
	HString formula = "2*(3+5)/sin(3.1415926535/2)";
	ENSURE_DISTANCE( "Wrong counting.", atof_ex( formula, true ), 16.L, epsilon );
	ENSURE_DISTANCE( "no parse failed", atof_ex( "3.14", false ), 3.14L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(atof_ex) simple but invalid number" )
	HString formula = "4/e";
	ENSURE_THROW( "invalid formula accepted", atof_ex( formula, true ), HExpressionException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "usun_ogonki" )
	HString s( "Mężny bądź, chroń pułk twój i sześć flag!" );
	ENSURE_EQUALS( "usun_ogonki failed", usun_ogonki( s ), "Mezny badz, chron pulk twoj i szesc flag!" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_token" )
	ENSURE_EQUALS( "get_token failed", get_token( "ala:ma:kota", ":", 1 ), "ma" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "cardinal" )
	ENSURE_EQUALS( "cardinal( 0 ) failed", cardinal( 0 ), "zero" );
	ENSURE_EQUALS( "cardinal( 1 ) failed", cardinal( 1 ), "one" );
	ENSURE_EQUALS( "cardinal( 12 ) failed", cardinal( 12 ), "twelve" );
	ENSURE_EQUALS( "cardinal( 19 ) failed", cardinal( 19 ), "nineteen" );
	ENSURE_EQUALS( "cardinal( -7 ) failed", cardinal( -7 ), "minus seven" );
	ENSURE_EQUALS( "cardinal( 100 ) failed", cardinal( 100 ), "100" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ordinal" )
	ENSURE_THROW( "ordinal( 0 ) failed", ordinal( 0 ), HRuntimeException );
	ENSURE_EQUALS( "ordinal( 1 ) failed", ordinal( 1 ), "first" );
	ENSURE_EQUALS( "ordinal( 12 ) failed", ordinal( 12 ), "twelfth" );
	ENSURE_EQUALS( "ordinal( 19 ) failed", ordinal( 19 ), "nineteenth" );
	ENSURE_THROW( "ordinal( -7 ) failed", ordinal( -7 ), HRuntimeException );
	ENSURE_EQUALS( "ordinal( 100 ) failed", ordinal( 100 ), "100th" );
	ENSURE_EQUALS( "ordinal( 101 ) failed", ordinal( 101 ), "101st" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "show help" )
	HProgramOptionsHandler po;
	HOptionInfo info( po );
	info.name( "tress" )
		.intro( "yaal stress testing suite" )
		.note( "Footer..." )
		.color( false )
		.markdown( false );
	ENSURE_NOT( "color failed", info.color() );
	int i( 0 );
	double d( 0 );
	HString s;
	bool b( false );
	po(
		HProgramOptionsHandler::HOption()
		.long_form( "log-path" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "path pointing to file for application logs" )
		.recipient( s )
		.default_value( "log.txt" )
		.argument_name( "path" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'j' )
		.long_form( "jobs" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "number of concurrent jobs" )
		.recipient( i )
		.default_value( 7 )
		.argument_name( "count" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'r' )
		.long_form( "ratio" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "expected pass/fail ratio" )
		.recipient( d )
		.default_value( .5 )
		.argument_name( "value" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'R' )
		.long_form( "restartable" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "run tests in restartable mode" )
		.recipient( b )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "framework" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "a framework to use =(*abc*|very|long|string|as|one|word|should|be|printed|alone) in this app" )
		.recipient( s )
		.default_value( "work" )
		.argument_name( "fw" )
	);
	HStringStream ss;
	show_help( info, ss );
	char const exp[] =
"Usage: tress [OPTION]... [FILE]...\n"
"tress - yaal stress testing suite\n"
"\n"
"Mandatory arguments to long options are mandatory for short options too.\n"
"Options:\n"
"      --log-path=path   path pointing to file for application logs (default:\n"
"                          log.txt)\n"
"  -j, --jobs=count      number of concurrent jobs (default: 7)\n"
"  -r, --ratio=value     expected pass/fail ratio (default: 0.5)\n"
"  -R, --restartable     run tests in restartable mode\n"
"      --framework[=fw]  a framework to use\n"
"                          =(abc|very|long|string|as|one|word|should|be|printed|alone)\n"
"                          in this app (default: work)\n"
"\n"
"All long form options can be used in program configuration file: tressrc.\n"
"\n"
"Footer...\n";
	ENSURE_EQUALS( "show_help failed", ss.string(), exp );
TUT_TEARDOWN()

TUT_UNIT_TEST( "dump_configuration" )
	HProgramOptionsHandler po;
	HOptionInfo info( po );
	info.name( "tress" ).intro( "yaal stress testing suite" ).note( "Footer..." );
	int i( 0 );
	double d( 0 );
	HString s;
	bool b( false );
	po(
		HProgramOptionsHandler::HOption()
		.long_form( "log-path" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "path pointing to file for application logs" )
		.recipient( s )
		.default_value( "log.txt" )
		.argument_name( "path" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'j' )
		.long_form( "jobs" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "number of concurrent jobs" )
		.recipient( i )
		.default_value( 7 )
		.argument_name( "count" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'r' )
		.long_form( "ratio" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "expected pass/fail ratio" )
		.recipient( d )
		.default_value( .5 )
		.argument_name( "value" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'R' )
		.long_form( "restartable" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "run tests in restartable mode" )
		.recipient( b )
	);
	HStringStream ss;
	dump_configuration( info, ss );
	char const exp[] =
"# this is configuration file for: `tress' program\n"
"# yaal stress testing suite\n"
"\n"
"# comments begin with `#' char and continues until end of line\n"
"# option names are case insensitive\n"
"# in most cases option values are case insensitive also\n"
"# syntax for settings is:\n"
"# ^{option}{white}(['\"]){value1 value2 ... valuen}\\1{white}# comment$\n"
"# value may be surrounded by apostrophes or quotation marks\n"
"# one level of this surrounding is stripped\n"
"# we currently distinguish between four kind of value types:\n"
"# bool   - (true|yes|on|false|no|off)\n"
"# char   - [a-z]\n"
"# int    - [0-9]+\n"
"# string - [^ ].*\n"
"#\n"
"# example:\n"
"# log_path ${HOME}/var/log/program.log\n"
"\n"
"### log-path ###\n"
"# type: character string, default: log.txt\n"
"# path pointing to file for application logs\n"
"log-path \"log.txt\"\n"
"\n"
"### jobs ###\n"
"# type: integer, default: 7\n"
"# number of concurrent jobs\n"
"jobs 7\n"
"\n"
"### ratio ###\n"
"# type: floating point, default: 0.5\n"
"# expected pass/fail ratio\n"
"ratio 0.5\n"
"\n"
"### restartable ###\n"
"# type: boolean\n"
"# run tests in restartable mode\n"
"restartable false\n"
"\n"
"# Footer...\n"
"\n"
"# vim: set ft=conf:\n";
	ENSURE_EQUALS( "dump_configuration failed", ss.string(), exp );
TUT_TEARDOWN()

TUT_UNIT_TEST( "failure" )
	ENSURE_THROW( "failure failed :)", util::failure( 7, "doh!" ), int );
TUT_TEARDOWN()

TUT_UNIT_TEST( "highlight" )
	HTheme t( COLOR::ATTR_BOLD, COLOR::ATTR_UNDERLINE, COLOR::ATTR_REVERSE, COLOR::ATTR_BLINK );
	ENSURE_EQUALS(
		"highlight bold failed",
		highlight( "highlight **bold** text", t ),
		"highlight \033[1mbold\033[0m\033[0m text"
	);
	ENSURE_EQUALS(
		"highlight underline failed",
		highlight( "highlight *underline* text", t ),
		"highlight \033[4munderline\033[0m\033[0m text"
	);
	ENSURE_EQUALS(
		"highlight code failed",
		highlight( "highlight `code` text", t ),
		"highlight \033[7mcode\033[0m\033[0m text"
	);
	ENSURE_EQUALS(
		"highlight special failed",
		highlight( "highlight $special$ text", t ),
		"highlight \033[5mspecial\033[0m\033[0m text"
	);
	ENSURE_EQUALS(
		"highlight mixing failed",
		highlight( "highlight	**x** = `foo( $pi$ )` *// comment* text", t ),
		"highlight	[1mx[0m[0m = [7mfoo( [5mpi[0m[7m )[0m[0m [4m// comment[0m[0m text"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "near_keys" )
	typedef yaal::hcore::HHashMap<char, yaal::hcore::HString> neighbours_t;
	neighbours_t neighbours({
		{ '`', "1\t" },
		{ '1', "`2q\t" },
		{ '2', "31wq" },
		{ '3', "42ew" },
		{ '4', "53re" },
		{ '5', "64tr" },
		{ '6', "75yt" },
		{ '7', "86uy" },
		{ '8', "97iu" },
		{ '9', "08oi" },
		{ '0', "9-po" },
		{ '-', "0=[p" },
		{ '=', "-\b][" },
		{ '\b', "\n]=" },
		{ '\t', "`1q" },
		{ 'q', "\t12wa" },
		{ 'w', "q23esa" },
		{ 'e', "w34rds" },
		{ 'r', "e45tfd" },
		{ 't', "r56ygf" },
		{ 'y', "t67uhg" },
		{ 'u', "y78ijh" },
		{ 'i', "u89okj" },
		{ 'o', "i90plk" },
		{ 'p', "o0-[;l" },
		{ '[', "p-=]';" },
		{ ']', "[=\b\n\\'" },
		{ '\r', "]\b\\" },
		{ '\n', "]\b\\" },
		{ 'a', "qwsz" },
		{ 's', "awedxz" },
		{ 'd', "serfcx" },
		{ 'f', "drtgvc" },
		{ 'g', "ftyhbv" },
		{ 'h', "gyujnb" },
		{ 'j', "huikmn" },
		{ 'k', "jiol,m" },
		{ 'l', "kop;.," },
		{ ';', "lp['/." },
		{ '\'', ";[]\\/" },
		{ '\\', "']\n" },
		{ 'z', "asx" },
		{ 'x', "zsdc " },
		{ 'c', "xdfv " },
		{ 'v', "cfgb " },
		{ 'b', "vghn " },
		{ 'n', "bhjm " },
		{ 'm', "njk, " },
		{ ',', "mkl. " },
		{ '.', ",l;/" },
		{ '/', ".;'" },
		{ ' ', "xcvbnm," },
		/* shift */
		{ '~', "!" },
		{ '!', "~@Q" },
		{ '@', "#!WQ" },
		{ '#', "$@EW" },
		{ '$', "%#RE" },
		{ '%', "^$TR" },
		{ '^', "&%YT" },
		{ '&', "*^UY" },
		{ '*', "(&IU" },
		{ '(', ")*OI" },
		{ ')', "_(PO" },
		{ '_', ")+{P" },
		{ '+', "_}{" },
		{ 'Q', "!@WA" },
		{ 'W', "Q@#ESA" },
		{ 'E', "W#$RDS" },
		{ 'R', "E$%TFD" },
		{ 'T', "R%^YGF" },
		{ 'Y', "T^&UHG" },
		{ 'U', "Y&*IJH" },
		{ 'I', "U*(OKJ" },
		{ 'O', "I()PLK" },
		{ 'P', "O)_{:L" },
		{ '{', "P_+}\":" },
		{ '}', "{+|\"" },
		{ 'A', "QWSZ" },
		{ 'S', "AWEDXZ" },
		{ 'D', "SERFCX" },
		{ 'F', "DRTGVC" },
		{ 'G', "FTYHBV" },
		{ 'H', "GYUJNB" },
		{ 'J', "HUIKMN" },
		{ 'K', "JIOL<M" },
		{ 'L', "KOP:><" },
		{ ':', "LP{\"?>" },
		{ '"', ":{}|?" },
		{ '|', "\"}" },
		{ 'Z', "ASX" },
		{ 'X', "ZSDC" },
		{ 'C', "XDFV" },
		{ 'V', "CFGB" },
		{ 'B', "VGHN" },
		{ 'N', "BHJM" },
		{ 'M', "NJK<" },
		{ '<', "MKL>" },
		{ '>', "<L:?" },
		{ '?', ">:\"" },
	});
	for ( neighbours_t::value_type const& n : neighbours ) {
		ENSURE_EQUALS( "invalid neighbours for: `"_ys.append( n.first ).append( "`" ), util::near_keys( n.first ), n.second );
	}
TUT_TEARDOWN()

}

