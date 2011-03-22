/*
---           `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	setup.cxx - this file is integral part of `tress' project.

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

#include <cstdio>
#include <iostream>
#include <libintl.h>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "setup.hxx"
#ifdef __TRESS__
#include "tut_helpers.hxx"
#endif /* #ifdef __TRESS__ */

using namespace yaal;
using namespace yaal::hcore;

template<typename Ch, typename Traits = std::char_traits<Ch> >
struct basic_nullbuf : std::basic_streambuf<Ch, Traits>
	{
	typedef std::basic_streambuf<Ch, Traits> base_type;
	typedef typename base_type::int_type int_type;
	typedef typename base_type::traits_type traits_type;

	virtual int_type overflow(int_type c)
		{
		return traits_type::not_eof(c);
		}
	};

typedef basic_nullbuf<char> nullbuf;
nullbuf cnull_obj;

namespace tress
{

void OSetup::test_setup( void )
	{
	M_PROLOG
	if ( _quiet && _verbose )
		yaal::tools::util::failure( 1,
				_( "quiet and verbose options are exclusive\n" ) );
	if ( _verbose )
		clog.reset( HStreamInterface::ptr_t( new HFile( stdout ) ) );
	else
		std::clog.rdbuf( &cnull_obj );
	if ( _quiet )
		{
		cout.reset();
		std::cout.rdbuf( &cnull_obj );
		}
	if ( _listGroups
			&& ( _restartable
				|| ! _testGroupListFilePath.is_empty()
				|| ! _testGroups.is_empty()
				|| ! _testGroupPattern.is_empty() || _testNumber ) )
		M_THROW( _( "group listing conflicts with other switches" ),
				_testNumber );
	if ( _restartable
			&& ( ! _testGroupListFilePath.is_empty()
				|| ! _testGroups.is_empty()
				|| ! _testGroupPattern.is_empty()
				|| _testNumber ) )
		M_THROW( _( "restartable conflicts with other switches" ),
				_testNumber );
	if ( ! _testGroupListFilePath.is_empty()
			&& ( ! _testGroups.is_empty()
				|| ! _testGroupPattern.is_empty()
				|| _testNumber ) )
		M_THROW( _( "group names file is an exclusive switch" ),
				_testNumber );
	if ( ! _testGroups.is_empty() && ! _testGroupPattern.is_empty() )
		M_THROW( _( "pattern and group switches are exclusive" ), errno );
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
	char const* IDE[] = { "console", "vim", "eclipse", "visualstudio" };
	if ( ! count( IDE, IDE + countof ( IDE ), _errorLine ) )
		M_THROW( _( "invalid IDE specified: " ) + _errorLine, 0 );
	if ( _verbose )
		{
		cout << "setup._argc = " << setup._argc << endl;
		for ( int i = 0; i < _argc; ++ i )
			cout << "setup._argv[" << i << "] = " << _argv[i] << endl;
#ifdef __TRESS__
		if ( _debug )
			{
			clog << "test data: ";
			copy( tut_helpers::_testData_[0], tut_helpers::_testData_[0] + countof ( tut_helpers::_testData_[0] ), stream_iterator( clog, " " ) );
			clog << endl;
			}
#endif /* #ifdef __TRESS__ */
		}
	return;
	M_EPILOG
	}

}

