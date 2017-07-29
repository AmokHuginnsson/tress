/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_util.cxx - this file is integral part of `tress' project.

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
	ENSURE_THROW( "bad 1 parameter accepted", EscapeTable et( NULL, 1, "n", 1 ), HFailedAssertion );
	ENSURE_THROW( "bad 3 parameter accepted", EscapeTable et( "\n", 1, NULL, 1 ), HFailedAssertion );
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

}

