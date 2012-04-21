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
M_VCSID( "$Id: "__ID__" $" )
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

TUT_UNIT_TEST( 1, "duplicated long option" )
	HProgramOptionsHandler po;
	try {
		int otherValue( 0 );
		po( "log_path", program_options_helper::option_value( _logPath ), HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path pointing to file for application logs", "path" )
			( "_jobs", program_options_helper::option_value( _jobs ), "j", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number of concurrent _jobs", "count" )
			( "group", program_options_helper::option_value( _testGroup ), "G", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test group", "name" )
			( "pattern", program_options_helper::option_value( _testGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test groups that are matching pattern", "pattern" )
			( "number", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test number for a given group", "number" )
			( "number", program_options_helper::option_value( otherValue ), "X", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test number for a given group", "number" )
			( "_restartable", program_options_helper::option_value( _restartable ), "R", HProgramOptionsHandler::OOption::TYPE::NONE, "run tests in _restartable mode" );
		FAIL( "program options handler with duplicated long option created" );
	} catch ( HProgramOptionsHandlerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "duplicated short option" )
	HProgramOptionsHandler po;
	try {
		int otherValue( 0 );
		po( "log_path", program_options_helper::option_value( _logPath ), HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path pointing to file for application logs", "path" )
			( "_jobs", program_options_helper::option_value( _jobs ), "j", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number of concurrent _jobs", "count" )
			( "group", program_options_helper::option_value( _testGroup ), "G", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test group", "name" )
			( "pattern", program_options_helper::option_value( _testGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test groups that are matching pattern", "pattern" )
			( "number", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test number for a given group", "number" )
			( "other", program_options_helper::option_value( otherValue ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test number for a given group", "number" )
			( "_restartable", program_options_helper::option_value( _restartable ), "R", HProgramOptionsHandler::OOption::TYPE::NONE, "run tests in _restartable mode" );
		FAIL( "program options handler with duplicated short option created" );
	} catch ( HProgramOptionsHandlerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "duplicated long option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po( "log_path", program_options_helper::option_value( _logPath ), HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path", "path pointing to file for application logs" )
		( "_jobs", program_options_helper::option_value( _jobs ), "j", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "count", "number of concurrent _jobs" )
		( "group", program_options_helper::option_value( _testGroup ), "G", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "name", "select test group" )
		( "pattern", program_options_helper::option_value( _testGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "pattern", "select test groups that are matching pattern" )
		( "number", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
		( "number", program_options_helper::option_value( _testNumber ), "X", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
		( "_restartable", program_options_helper::option_value( _restartable ), "R", HProgramOptionsHandler::OOption::TYPE::NONE, "run tests in _restartable mode" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "duplicated short option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po( "log_path", program_options_helper::option_value( _logPath ), HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path pointing to file for application logs", "path" )
		( "_jobs", program_options_helper::option_value( _jobs ), "j", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number of concurrent _jobs", "count" )
		( "group", program_options_helper::option_value( _testGroup ), "G", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test group", "name" )
		( "pattern", program_options_helper::option_value( _testGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test groups that are matching pattern", "pattern" )
		( "number", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test number for a given group", "number" )
		( "other", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test number for a given group", "number" )
		( "_restartable", program_options_helper::option_value( _restartable ), "R", HProgramOptionsHandler::OOption::TYPE::NONE, "run tests in _restartable mode" );
TUT_TEARDOWN()

}

