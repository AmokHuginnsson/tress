/*
---           `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	setup.cxx - this file is integral part of `tress' project.

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

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <libintl.h>

#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "setup.hxx"
#ifdef __TRESS__
#include "tut_helpers.hxx"
#endif /* #ifdef __TRESS__ */

using namespace yaal;
using namespace yaal::hcore;

template<typename Ch, typename Traits = std::char_traits<Ch> >
struct basic_nullbuf : std::basic_streambuf<Ch, Traits> {
	typedef std::basic_streambuf<Ch, Traits> base_type;
	typedef typename base_type::int_type int_type;
	typedef typename base_type::traits_type traits_type;

	virtual int_type overflow(int_type c) {
		return traits_type::not_eof(c);
	}
};

typedef basic_nullbuf<char> nullbuf;
nullbuf cnull_obj;

namespace tress {
OSetup::OSetup( void )
	: _quiet( false ), _verbose( false ), _debug( false ),
		_listGroups( false ), _restartable( false ), _exit( false ), _fancy( false ), _color( false ),
		_selftest( false ),
		_testNumber( 0 ), _jobs( DEFAULT_JOB_COUNT ), _timeConstraint( DEFAULT_TIME_CONSTRAINT ),
		_argc( 0 ), _argv( NULL ),
		_programName( NULL ), _logPath(), _testGroups(), _testSets(),
		_testGroupPattern(), _testGroupListFilePath(),
		_reporter( "tut" ), _errorLine( "console" ), _clockQualityMultiplier( DEFAULT_CLOCK_QUALITY_MULTIPLIER ) {
}

void OSetup::test_setup( void ) {
	M_PROLOG
	_reporter.lower();
	if ( _reporter != "tut" ) {
		std::cerr.rdbuf( std::cout.rdbuf() );
		_quiet = true;
		_verbose = false;
	}
	if ( _quiet && _verbose )
		yaal::tools::util::failure( 1,
				_( "quiet and verbose options are mutually exclusive\n" ) );
	if ( _verbose )
		clog.reset( make_pointer<HFile>( stdout, false ) );
	else
		std::clog.rdbuf( &cnull_obj );
	if ( _quiet ) {
		cout.reset();
		std::cout.rdbuf( &cnull_obj );
	}
	if ( _fancy && _verbose )
		yaal::tools::util::failure( 1,
				_( "fancy and verbose options are mutually exclusive\n" ) );
	if ( _listGroups
			&& ( _restartable
				|| ! _testGroupListFilePath.is_empty()
				|| ! _testGroups.is_empty()
				|| ! _testSets.is_empty()
				|| ! _testGroupPattern.is_empty() || _testNumber ) )
		M_THROW( _( "group listing conflicts with other switches" ),
				_testNumber );
	if ( _restartable
			&& ( ! _testGroupListFilePath.is_empty()
				|| ! _testGroups.is_empty()
				|| ! _testSets.is_empty()
				|| ! _testGroupPattern.is_empty()
				|| _testNumber ) )
		M_THROW( _( "restartable conflicts with other switches" ),
				_testNumber );
	if ( ! _testGroupListFilePath.is_empty()
			&& ( ! _testGroups.is_empty()
				|| ! _testSets.is_empty()
				|| ! _testGroupPattern.is_empty()
				|| _testNumber ) )
		M_THROW( _( "group names file is an exclusive switch" ),
				_testNumber );
	if ( ! _testGroups.is_empty() && ! _testGroupPattern.is_empty() )
		M_THROW( _( "pattern and group switches are exclusive" ), errno );
	if ( ! _testSets.is_empty() && ! _testGroupPattern.is_empty() )
		M_THROW( _( "pattern and set switches are exclusive" ), errno );
	if ( ! _testSets.is_empty() && ! _testGroups.is_empty() )
		M_THROW( _( "group and set switches are exclusive" ), errno );
	if ( ! _testGroupPattern.is_empty() && _testNumber )
		M_THROW( _( "setting test number for pattern makes no sense" ),
				_testNumber );
	if ( _testNumber && _testGroups.is_empty() )
		M_THROW( _( "must specify test group for test number" ),
				_testNumber );
	if ( ( _testGroups.size() > 1 ) && ( _testNumber ) )
		M_THROW( _( "test number not supported while running multiple groups" ), _testNumber );
	if ( _jobs < 0 )
		M_THROW( _( "bad job count" ), _jobs );
	if ( _timeConstraint < 0 )
		M_THROW( _( "bad time constraint" ), _timeConstraint );
	char const* FRAMEWORK[] = { "tut", "boost", "google", "cppunit", "xml", "qt", "cute" };
	if ( ! count( FRAMEWORK, FRAMEWORK + countof ( FRAMEWORK ), _reporter ) )
		M_THROW( _( "invalid framework specified: " ) + _reporter, 0 );
	if ( ( _reporter == "qt" ) && ( _argc > 1 ) )
		_argc = 1;
	char const* IDE[] = { "console", "vim", "eclipse", "visualstudio" };
	if ( ( _reporter != FRAMEWORK[0] ) && ( _errorLine != IDE[0] ) )
		M_THROW( _( "specifing IDE for reporter `" ) + _reporter + _( "' is illegal" ), 0 );
	if ( ! count( IDE, IDE + countof ( IDE ), _errorLine ) )
		M_THROW( _( "invalid IDE specified: " ) + _errorLine, 0 );
	if ( ( _errorLine != IDE[0] ) || ! ::getenv( "TERM" ) )
		_color = false;
	if ( _verbose ) {
		cout << "setup._argc = " << setup._argc << endl;
		for ( int i = 0; i < _argc; ++ i )
			cout << "setup._argv[" << i << "] = " << _argv[i] << endl;
#ifdef __TRESS__
		if ( _debug ) {
			clog << "test data: ";
			copy( tut_helpers::_testData_[0], tut_helpers::_testData_[0] + countof ( tut_helpers::_testData_[0] ), stream_iterator( clog, " " ) );
			clog << endl;
		}
#endif /* #ifdef __TRESS__ */
	}
	char const* CLOCK_QUALITY_MULTIPLIER( ::getenv( "TRESS_CLOCK_QUALITY_MULTIPLIER" ) );
	if ( CLOCK_QUALITY_MULTIPLIER ) {
		_clockQualityMultiplier = lexical_cast<int>( CLOCK_QUALITY_MULTIPLIER );
		if ( ( _clockQualityMultiplier < 1 ) || ( _clockQualityMultiplier > 100 ) )
			M_THROW( _( "bad clock quality multiplier" ), _clockQualityMultiplier );
	}
	return;
	M_EPILOG
}

}

