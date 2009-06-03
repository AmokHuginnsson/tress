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

struct tut_yaal_hcore_hprogram_options_handler
	{
	bool _restartable;
	int _jobs;
	int _testNumber;
	HString _logPath;
	HString _testGroup;
	HString _testGroupPattern;
	tut_yaal_hcore_hprogram_options_handler( void )
		: _restartable( false ), _jobs( 0 ), _testNumber( 0 ), _logPath(), _testGroup(), _testGroupPattern()
		{}
	virtual ~tut_yaal_hcore_hprogram_options_handler( void ) {}
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_hprogram_options_handler, "yaal::hcore::HProgramOptionsHandler" );

TUT_UNIT_TEST_N( 1, "duplicated long option" )
	HProgramOptionsHandler po;
	try
		{
		int otherValue( 0 );
		po( "log_path", program_options_helper::option_value( _logPath ), NULL, HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path", "path pointing to file for application logs" )
			( "_jobs", program_options_helper::option_value( _jobs ), "j", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "count", "number of concurrent _jobs" )
			( "group", program_options_helper::option_value( _testGroup ), "G", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "name", "select test group" )
			( "pattern", program_options_helper::option_value( _testGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "pattern", "select test groups that are matching pattern" )
			( "number", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
			( "number", program_options_helper::option_value( otherValue ), "X", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
			( "_restartable", program_options_helper::option_value( _restartable ), "R", HProgramOptionsHandler::OOption::TYPE::NONE, NULL, "run tests in _restartable mode" );
		fail( "program options handler with duplicated long option created" );
		}
	catch ( HProgramOptionsHandlerException const& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "duplicated short option" )
	HProgramOptionsHandler po;
	try
		{
		int otherValue( 0 );
		po( "log_path", program_options_helper::option_value( _logPath ), NULL, HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path", "path pointing to file for application logs" )
			( "_jobs", program_options_helper::option_value( _jobs ), "j", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "count", "number of concurrent _jobs" )
			( "group", program_options_helper::option_value( _testGroup ), "G", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "name", "select test group" )
			( "pattern", program_options_helper::option_value( _testGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "pattern", "select test groups that are matching pattern" )
			( "number", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
			( "other", program_options_helper::option_value( otherValue ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
			( "_restartable", program_options_helper::option_value( _restartable ), "R", HProgramOptionsHandler::OOption::TYPE::NONE, NULL, "run tests in _restartable mode" );
		fail( "program options handler with duplicated short option created" );
		}
	catch ( HProgramOptionsHandlerException const& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "duplicated long option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po( "log_path", program_options_helper::option_value( _logPath ), NULL, HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path", "path pointing to file for application logs" )
		( "_jobs", program_options_helper::option_value( _jobs ), "j", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "count", "number of concurrent _jobs" )
		( "group", program_options_helper::option_value( _testGroup ), "G", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "name", "select test group" )
		( "pattern", program_options_helper::option_value( _testGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "pattern", "select test groups that are matching pattern" )
		( "number", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
		( "number", program_options_helper::option_value( _testNumber ), "X", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
		( "_restartable", program_options_helper::option_value( _restartable ), "R", HProgramOptionsHandler::OOption::TYPE::NONE, NULL, "run tests in _restartable mode" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "duplicated short option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po( "log_path", program_options_helper::option_value( _logPath ), NULL, HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path", "path pointing to file for application logs" )
		( "_jobs", program_options_helper::option_value( _jobs ), "j", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "count", "number of concurrent _jobs" )
		( "group", program_options_helper::option_value( _testGroup ), "G", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "name", "select test group" )
		( "pattern", program_options_helper::option_value( _testGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "pattern", "select test groups that are matching pattern" )
		( "number", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
		( "other", program_options_helper::option_value( _testNumber ), "N", HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number", "select test number for a given group" )
		( "_restartable", program_options_helper::option_value( _restartable ), "R", HProgramOptionsHandler::OOption::TYPE::NONE, NULL, "run tests in _restartable mode" );
TUT_TEARDOWN()

}

