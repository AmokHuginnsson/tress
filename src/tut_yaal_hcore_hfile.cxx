/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hfile.cxx - this file is integral part of `tress' project.

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
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_hcore_hfile );
TUT_TEST_GROUP_N( tut_yaal_hcore_hfile, "yaal::hcore::HFile" );

TUT_UNIT_TEST_N( 1, "HFile::READ::UNBUFFERED_READS (nl)" )
	HFile in( "./data/nl.txt", HFile::OPEN::READING );
	HString line;
	while ( in.read_line( line,	HFile::READ::UNBUFFERED_READS ) >= 0 )
		{
		cout << line << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "HFile::READ::UNBUFFERED_READS (crnl)" )
	HFile in( "./data/crnl.txt", HFile::OPEN::READING );
	HString line;
	while ( in.read_line( line,	HFile::READ::UNBUFFERED_READS ) >= 0 )
		{
		cout << line << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "HFile::READ::BUFFERED_READS (nl)" )
	HFile in( "./data/nl.txt", HFile::OPEN::READING );
	HString line;
	while ( in.read_line( line,	HFile::READ::BUFFERED_READS ) >= 0 )
		{
		cout << line << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "HFile::READ::BUFFERED_READS (crnl)" )
	HFile in( "./data/crnl.txt", HFile::OPEN::READING );
	HString line;
	while ( in.read_line( line,	HFile::READ::BUFFERED_READS ) >= 0 )
		{
		cout << line << endl;
		}
TUT_TEARDOWN()

}
