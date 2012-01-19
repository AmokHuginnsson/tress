/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hfsitem.cxx - this file is integral part of `tress' project.

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

#include <cstdlib>

#include <TUT/tut.hpp>

#include <yaal/tools/hfsitem.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hfsitem );
TUT_TEST_GROUP( tut_yaal_tools_hfsitem, "yaal::tools::HFSItem" );

namespace {

void recurse( HString const& path_ ) {
	HFSItem dir( path_ );
	cout << "dir: " << blue << bold << dir.get_path() << reset << endl;
	M_ENSURE( dir.is_directory() );
	for ( HFSItem::HIterator it = dir.begin(); it != dir.end(); ++ it ) {
		cout << yellow << ( it->is_directory() ? "[dir]" : "     " ) << " " << ( it->is_executable() ? "[exec]" : "      " )
			<< " [" << setw( 10 ) << it->get_size() << "] "
			<< white << setw( 8 ) << it->get_user() << " " << setw( 8 ) << it->get_group()
			<< " " << brightmagenta << oct << setw( 4 ) << ( it->get_permissions() & 0777 ) << dec
			<< reset << " " << it->get_path() << " " << it->modified().string() << endl;
		if ( it->is_directory() && ( it->get_name() != "." ) && ( it->get_name() != ".." ) ) {
			cout << "descending into ";
			recurse( it->get_path() );
			cout << "back at: " << blue << bold << dir.get_path() << reset << endl;
		}
	}
}

}

struct PathTest {
	char const* _path;
	bool _exists;
};

TUT_UNIT_TEST( 1, "exists" )
	HString err( "failed to recognize onhological status of given file: " );
	PathTest pathTest[] = {
			{ "./data", true },
			{ "./data/", true },
			{ "./data/non-existing", false },
			{ "./data/non-existing/", false },
			{ "./data/xml.xml", true },
			{ "./data/xml.xml/", false },
			{ ".", true },
			{ "./", true },
			{ "..", true },
			{ "../", true },
			{ "/", true },
			{ "./data//", true },
			{ "./data///", true },
			{ "//", true }
	};
	for ( int i( 0 ); i < countof ( pathTest ); ++ i ) {
		HFSItem fit( pathTest[i]._path );
		ENSURE( err + pathTest[i]._path, xnor( !! fit, pathTest[i]._exists ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "is_directory" )
	char const err[] = "failed to recognize directoriesness of given file";
	char const err2[] = "spurious status on non-existing item acquired";
	HFSItem dit1( "./data" );
	ENSURE( err, dit1.is_directory() );
	HFSItem dit2( "./data/" );
	ENSURE( err, dit2.is_directory() );
	try {
		HFSItem dit3( "./data/non-existing" );
		ENSURE( err, ! dit3.is_directory() );
		FAIL( err2 );
	} catch ( HFSItemException const& ) {
	}
	try {
		HFSItem dit4( "./data/non-existing/" );
		ENSURE( err, ! dit4.is_directory() );
		FAIL( err2 );
	} catch ( HFSItemException const& ) {
	}
	HFSItem dit5( "./data/xml.xml" );
	ENSURE( err, ! dit5.is_directory() );
	try {
		HFSItem dit6( "./data/xml.xml/" );
		ENSURE( err, ! dit6.is_directory() );
	} catch ( HFSItemException const& ) {
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

TUT_UNIT_TEST( 49, "recurively scan directories" )
	recurse( "./build/" );
TUT_TEARDOWN()

}
