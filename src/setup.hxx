/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	setup.hxx - this file is integral part of `tress' project.

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

#ifndef TRESS_SETUP_HXX_INCLUDED
#define TRESS_SETUP_HXX_INCLUDED

#include <yaal/hcore/hstring.hxx>
#include <yaal/hcore/hdeque.hxx>

#include "config.hxx"

namespace tress {

struct OSetup {
	OSetup( void )
		: _quiet( false ), _verbose( false ), _debug( false ),
		_listGroups( false ), _restartable( false ), _exit( false ), _fancy( false ), _color( false ),
		_selftest( false ),
		_testNumber( 0 ), _jobs( DEFAULT_JOB_COUNT ), _timeConstraint( DEFAULT_TIME_CONSTRAINT ),
		_argc( 0 ), _argv( NULL ),
		_programName( NULL ), _logPath(), _testGroups(), _testSets(),
		_testGroupPattern(), _testGroupListFilePath(),
		_errorLine( "console" ) {}
	typedef yaal::hcore::HDeque<yaal::hcore::HString> group_names_t;
	typedef yaal::hcore::HDeque<yaal::hcore::HString> set_definitions_t;
	bool _quiet;			/* --quiet, --silent */
	bool _verbose;		/* --verbose */
	bool _debug;      /* --debug */
	bool _listGroups;
	bool _restartable;
	bool _exit;
	bool _fancy;
	bool _color;
	bool _selftest;
	int _testNumber;
	int _jobs;
	int long _timeConstraint;
	int _argc;
	char const* const* _argv;
	char* _programName;
	yaal::hcore::HString _logPath;
	group_names_t _testGroups;
	set_definitions_t _testSets;
	yaal::hcore::HString _testGroupPattern;
	yaal::hcore::HString _testGroupListFilePath;
	yaal::hcore::HString _errorLine;
	static int const DEFAULT_JOB_COUNT = 1;
	static int long const DEFAULT_TIME_CONSTRAINT = 0;
	void test_setup( void );
private:
	OSetup( OSetup const& );
	OSetup& operator = ( OSetup const& );
};

extern OSetup setup;

}

#endif /* TRESS_SETUP_HXX_INCLUDED */
