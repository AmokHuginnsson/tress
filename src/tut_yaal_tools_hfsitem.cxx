/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hfsitem.cxx - this file is integral part of `tress' project.

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

#include <cstdlib>

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

TUT_SIMPLE_MOCK( tut_yaal_tools_hfsitem );
TUT_TEST_GROUP_N( tut_yaal_tools_hfsitem, "yaal::tools::HFSItem" );

void recurse( HString const& path_ )
	{
	HFSItem dir( path_ );
	cout << "dir: " << dir.get_path() << endl;
	M_ENSURE( dir.is_directory() );
	for ( HFSItem::HIterator it = dir.begin(); it != dir.end(); ++ it )
		{
		cout << "item: " << it->get_path() << endl;
		if ( it->is_directory() && ( it->get_name() != "." ) && ( it->get_name() != ".." ) )
			{
			cout << "descending into ";
			recurse( it->get_path() );
			cout << "back at: " << dir.get_path() << endl;
			}
		}
	}

TUT_UNIT_TEST_N( 1, "exists" )
	char const err[] = "failed to recognize onhological status of given file";
	HFSItem dit1( "./data" );
	ENSURE( err, !! dit1 );
	HFSItem dit2( "./data/" );
	ENSURE( err, !! dit2 );
	HFSItem dit3( "./data/non-existing" );
	ENSURE( err, ! dit3 );
	HFSItem dit4( "./data/non-existing/" );
	ENSURE( err, ! dit4 );
	HFSItem dit5( "./data/xml.xml" );
	ENSURE( err, !! dit5 );
	HFSItem dit6( "./data/xml.xml/" );
	ENSURE( err, ! dit6 );
	HFSItem dit7( "." );
	ENSURE( err, !! dit7 );
	HFSItem dit8( "./" );
	ENSURE( err, !! dit8 );
	HFSItem dit9( ".." );
	ENSURE( err, !! dit9 );
	HFSItem dit10( "../" );
	ENSURE( err, !! dit10 );
	HFSItem dit11( "/" );
	ENSURE( err, !! dit11 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "is_directory" )
	char const err[] = "failed to recognize directoriesness of given file";
	char const err2[] = "spurious status on non-exeisting item acquired";
	HFSItem dit1( "./data" );
	ENSURE( err, dit1.is_directory() );
	HFSItem dit2( "./data/" );
	ENSURE( err, dit2.is_directory() );
	try
		{
		HFSItem dit3( "./data/non-existing" );
		ENSURE( err, ! dit3.is_directory() );
		FAIL( err2 );
		}
	catch ( HFSItemException const& )
		{
		}
	try
		{
		HFSItem dit4( "./data/non-existing/" );
		ENSURE( err, ! dit4.is_directory() );
		FAIL( err2 );
		}
	catch ( HFSItemException const& )
		{
		}
	HFSItem dit5( "./data/xml.xml" );
	ENSURE( err, ! dit5.is_directory() );
	try
		{
		HFSItem dit6( "./data/xml.xml/" );
		ENSURE( err, ! dit6.is_directory() );
		}
	catch ( HFSItemException const& )
		{
		}
	HFSItem dit7( "." );
	ENSURE( err, dit7.is_directory() );
	HFSItem dit8( "./" );
	ENSURE( err, dit8.is_directory() );
	HFSItem dit9( ".." );
	ENSURE( err, dit9.is_directory() );
	HFSItem dit10( "../" );
	ENSURE( err, dit10.is_directory() );
	HFSItem dit11( "/" );
	ENSURE( err, dit11.is_directory() );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 49, "recurively scan directories" )
	char const* home( getenv( "HOME" ) );
	recurse( home ? HString( home  ) + "/bin" : HString( "." ) );
TUT_TEARDOWN()

}
