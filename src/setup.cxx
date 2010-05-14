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

using namespace yaal::hcore;

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
		std::clog.rdbuf( NULL );
	if ( _quiet )
		{
		cout.reset();
		std::cout.rdbuf( NULL );
		}
	if ( setup._listGroups
			&& ( setup._restartable
				|| ! setup._testGroupListFilePath.is_empty()
				|| ! setup._testGroup.is_empty()
				|| ! setup._testGroupPattern.is_empty() || setup._testNumber ) )
		M_THROW( _( "group listing conflicts with other switches" ),
				setup._testNumber );
	if ( setup._restartable
			&& ( ! setup._testGroupListFilePath.is_empty()
				|| ! setup._testGroup.is_empty()
				|| ! setup._testGroupPattern.is_empty()
				|| setup._testNumber ) )
		M_THROW( _( "restartable conflicts with other switches" ),
				setup._testNumber );
	if ( ! setup._testGroupListFilePath.is_empty()
			&& ( ! setup._testGroup.is_empty()
				|| ! setup._testGroupPattern.is_empty()
				|| setup._testNumber ) )
		M_THROW( _( "group names file is an exclusive switch" ),
				setup._testNumber );
	if ( ! setup._testGroup.is_empty() && ! setup._testGroupPattern.is_empty() )
		M_THROW( _( "pattern and group switches are exclusive" ), errno );
	if ( ! setup._testGroupPattern.is_empty() && setup._testNumber )
		M_THROW( _( "setting test number for pattern makes no sense" ),
				setup._testNumber );
	if ( setup._testNumber && setup._testGroup.is_empty() )
		M_THROW( _( "must specify test group for test number" ),
				setup._testNumber );
	return;
	M_EPILOG
	}

}

