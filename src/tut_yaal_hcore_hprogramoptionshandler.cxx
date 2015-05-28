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
			"log_path",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"path pointing to file for application logs",
			program_options_helper::option_value( _logPath ),
			"path"
		)(
			'j',
			"_jobs",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"number of concurrent _jobs",
			program_options_helper::option_value( _jobs ),
			"count"
		)(
			'G',
			"group",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"select test group",
			program_options_helper::option_value( _testGroup ),
			"name"
		)(
			'P',
			"pattern",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"select test groups that are matching pattern",
			program_options_helper::option_value( _testGroupPattern ),
			"pattern"
		)(
			'N',
			"number",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"select test number for a given group",
			program_options_helper::option_value( _testNumber ),
			"number"
		)(
			'X',
			"number",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"select test number for a given group",
			program_options_helper::option_value( otherValue ),
			"number"
		)(
			'R',
			"_restartable",
			HProgramOptionsHandler::HOption::ARGUMENT::NONE,
			"run tests in _restartable mode",
			program_options_helper::option_value( _restartable )
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
			"log_path",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"path pointing to file for application logs",
			program_options_helper::option_value( _logPath ),
			"path"
		)(
			'j',
			"_jobs",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"number of concurrent _jobs",
			program_options_helper::option_value( _jobs ),
			"count"
		)(
			'G',
			"group",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"select test group",
			program_options_helper::option_value( _testGroup ),
			"name"
		)(
			'P',
			"pattern",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"select test groups that are matching pattern",
			program_options_helper::option_value( _testGroupPattern ),
			"pattern"
		)(
			'N',
			"number",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"select test number for a given group",
			program_options_helper::option_value( _testNumber ),
			"number"
		)(
			'N',
			"other",
			HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
			"select test number for a given group",
			program_options_helper::option_value( otherValue ),
			"number"
		)(
			'R',
			"_restartable",
			HProgramOptionsHandler::HOption::ARGUMENT::NONE,
			"run tests in _restartable mode",
			program_options_helper::option_value( _restartable )
		);
		FAIL( "program options handler with duplicated short option created" );
	} catch ( HProgramOptionsHandlerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "duplicated long option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po(
		"log_path",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"path pointing to file for application logs",
		program_options_helper::option_value( _logPath ),
		"path"
	)(
		'j',
		"_jobs",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"number of concurrent _jobs",
		program_options_helper::option_value( _jobs ),
		"count"
	)(
		'G',
		"group",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test group",
		program_options_helper::option_value( _testGroup ),
		"name"
	)(
		'P',
		"pattern",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test groups that are matching pattern",
		program_options_helper::option_value( _testGroupPattern ),
		"pattern"
	)(
		'N',
		"number",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test number for a given group",
		program_options_helper::option_value( _testNumber ),
		"number"
	)(
		'X',
		"number",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test number for a given group",
		program_options_helper::option_value( _testNumber ),
		"number"
	)(
		'R',
		"_restartable",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"run tests in _restartable mode",
		program_options_helper::option_value( _restartable )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "duplicated short option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po(
		"log_path",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"path pointing to file for application logs",
		program_options_helper::option_value( _logPath ),
		"path"
	)(
		'j',
		"_jobs",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"number of concurrent _jobs",
		program_options_helper::option_value( _jobs ),
		"count"
	)(
		'G',
		"group",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test group",
		program_options_helper::option_value( _testGroup ),
		"name"
	)(
		'P',
		"pattern",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test groups that are matching pattern",
		program_options_helper::option_value( _testGroupPattern ),
		"pattern"
	)(
		'N',
		"number",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test number for a given group",
		program_options_helper::option_value( _testNumber ),
		"number"
	)(
		'N',
		"other",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test number for a given group",
		program_options_helper::option_value( _testNumber ),
		"number"
	)(
		'R',
		"_restartable",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"run tests in _restartable mode",
		program_options_helper::option_value( _restartable )
	);
TUT_TEARDOWN()

}

