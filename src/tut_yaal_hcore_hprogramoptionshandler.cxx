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

#include <yaal/hcore/hprogramoptionshandler.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hprogram_options_handler : simple_mock<tut_yaal_hcore_hprogram_options_handler> {
	typedef simple_mock<tut_yaal_hcore_hprogram_options_handler> base_type;
	bool _restartable;
	int _jobs;
	int _testNumber;
	HString _logPath;
	HString _testGroup;
	HString _testGroupPattern;
	tut_yaal_hcore_hprogram_options_handler( void )
		: base_type(),
		_restartable( false ), _jobs( 0 ), _testNumber( 0 ),
		_logPath(), _testGroup(), _testGroupPattern()
		{}
	virtual ~tut_yaal_hcore_hprogram_options_handler( void ) {}
};

TUT_TEST_GROUP( tut_yaal_hcore_hprogram_options_handler, "yaal::hcore::HProgramOptionsHandler" );

TUT_UNIT_TEST( "duplicated long option" )
	HProgramOptionsHandler po;
	try {
		int otherValue( 0 );
		po(
			HProgramOptionsHandler::HOption()
			.long_form( "log_path" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "path pointing to file for application logs" )
			.recipient( _logPath )
			.argument_name( "path" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'j' )
			.long_form( "jobs" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "number of concurrent jobs" )
			.recipient( _jobs )
			.argument_name( "count" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'G' )
			.long_form( "group" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test group" )
			.recipient( _testGroup )
			.argument_name( "name" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'P' )
			.long_form( "pattern" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test groups that are matching pattern" )
			.recipient( _testGroupPattern )
			.argument_name( "pattern" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'N' )
			.long_form( "number" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test number for a given group" )
			.recipient( _testNumber )
			.argument_name( "number" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'X' )
			.long_form( "number" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test number for a given group" )
			.recipient( otherValue )
			.argument_name( "number" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'R' )
			.long_form( "restartable" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
			.description( "run tests in restartable mode" )
			.recipient( _restartable )
		);
		FAIL( "program options handler with duplicated long option created" );
	} catch ( HProgramOptionsHandlerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "duplicated short option" )
	HProgramOptionsHandler po;
	try {
		int otherValue( 0 );
		po(
			HProgramOptionsHandler::HOption()
			.long_form( "log_path" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "path pointing to file for application logs" )
			.recipient( _logPath )
			.argument_name( "path" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'j' )
			.long_form( "jobs" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "number of concurrent jobs" )
			.recipient( _jobs )
			.argument_name( "count" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'G' )
			.long_form( "group" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test group" )
			.recipient( _testGroup )
			.argument_name( "name" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'P' )
			.long_form( "pattern" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test groups that are matching pattern" )
			.recipient( _testGroupPattern )
			.argument_name( "pattern" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'N' )
			.long_form( "number" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test number for a given group" )
			.recipient( _testNumber )
			.argument_name( "number" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'N' )
			.long_form( "other" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test number for a given group" )
			.recipient( otherValue )
			.argument_name( "number" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'R' )
			.long_form( "restartable" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
			.description( "run tests in restartable mode" )
			.recipient( _restartable )
		);
		FAIL( "program options handler with duplicated short option created" );
	} catch ( HProgramOptionsHandlerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "duplicated long option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po(
		HProgramOptionsHandler::HOption()
		.long_form( "log_path" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "path pointing to file for application logs" )
		.recipient( _logPath )
		.argument_name( "path" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'j' )
		.long_form( "jobs" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "number of concurrent jobs" )
		.recipient( _jobs )
		.argument_name( "count" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'G' )
		.long_form( "group" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test group" )
		.recipient( _testGroup )
		.argument_name( "name" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'P' )
		.long_form( "pattern" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test groups that are matching pattern" )
		.recipient( _testGroupPattern )
		.argument_name( "pattern" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'N' )
		.long_form( "number" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( _testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'X' )
		.long_form( "number" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( _testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'R' )
		.long_form( "restartable" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "run tests in restartable mode" )
		.recipient( _restartable )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "duplicated short option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po(
		HProgramOptionsHandler::HOption()
		.long_form( "log_path" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "path pointing to file for application logs" )
		.recipient( _logPath )
		.argument_name( "path" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'j' )
		.long_form( "jobs" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "number of concurrent jobs" )
		.recipient( _jobs )
		.argument_name( "count" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'G' )
		.long_form( "group" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test group" )
		.recipient( _testGroup )
		.argument_name( "name" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'P' )
		.long_form( "pattern" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test groups that are matching pattern" )
		.recipient( _testGroupPattern )
		.argument_name( "pattern" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'N' )
		.long_form( "number" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( _testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'N' )
		.long_form( "other" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( _testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'R' )
		.long_form( "restartable" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "run tests in restartable mode" )
		.recipient( _restartable )
	);
TUT_TEARDOWN()

}

