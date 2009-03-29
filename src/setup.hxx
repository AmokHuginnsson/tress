/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	setup.hxx - this file is integral part of `tress' project.

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

#ifndef TRESS_SETUP_HXX_INCLUDED
#define TRESS_SETUP_HXX_INCLUDED

#include <yaal/hcore/hstring.hxx>

namespace tress
{

struct OSetup
	{
	OSetup ( void )
		: f_bQuiet ( false ), f_bVerbose ( false ), f_bHelp ( false ),
		f_bListGroups ( false ), f_bRestartable ( false ), f_iTestNumber ( 0 ),
		f_iJobs( D_DEFAULT_JOB_COUNT ), f_iArgc ( 0 ), f_ppcArgv ( NULL ),
		f_pcProgramName ( NULL ), f_oLogPath(), f_oTestGroup(),
		f_oTestGroupPattern(), f_oTestGroupListFilePath() {}
	bool f_bQuiet;			/* --quiet, --silent */
	bool f_bVerbose;		/* --verbose */
	bool f_bHelp;
	bool f_bListGroups;
	bool f_bRestartable;
	int f_iTestNumber;
	int f_iJobs;
	int f_iArgc;
	char const * const * f_ppcArgv;
	char * f_pcProgramName;
	yaal::hcore::HString f_oLogPath;
	yaal::hcore::HString f_oTestGroup;
	yaal::hcore::HString f_oTestGroupPattern;
	yaal::hcore::HString f_oTestGroupListFilePath;
	static int const D_DEFAULT_JOB_COUNT = 1;
	void test_setup( void );
private:
	OSetup( OSetup const& );
	OSetup& operator = ( OSetup const& );
	};

extern OSetup setup;

}

#endif /* TRESS_SETUP_HXX_INCLUDED */
