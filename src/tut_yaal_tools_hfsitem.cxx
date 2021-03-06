/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstdlib>

#include <TUT/tut.hpp>

#include <yaal/tools/hfsitem.hxx>
#include <yaal/tools/filesystem.hxx>
#include <yaal/tools/sleep.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::filesystem;
using namespace yaal::ansi;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hfsitem );
TUT_TEST_GROUP( tut_yaal_tools_hfsitem, "yaal::tools::HFSItem" );

namespace {

void recurse( HString const& path_ ) {
	HFSItem dir( path_ );
	clog << "dir: " << blue << bold << dir.get_path() << reset << endl;
	M_ENSURE( dir.is_directory() );
	for ( HFSItem::HIterator it = dir.begin(); it != dir.end(); ++ it ) {
		clog << yellow << ( it->is_directory() ? "[dir]" : "     " ) << " " << ( it->is_executable() ? "[exec]" : "      " )
			<< " [" << setw( 10 ) << it->get_size() << "] "
			<< white << setw( 8 ) << it->get_user() << " " << setw( 8 ) << it->get_group()
			<< " " << brightmagenta << oct << setw( 4 ) << ( it->get_permissions() & 0777 ) << dec
			<< reset << " " << it->get_path() << " " << it->modified().string() << endl;
		if ( it->is_directory() ) {
			clog << "descending into ";
			recurse( it->get_path() );
			clog << "back at: " << blue << bold << dir.get_path() << reset << endl;
		}
	}
}

}

struct PathTest {
	char const* _path;
	bool _exists;
};

TUT_UNIT_TEST( "exists" )
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
	for ( int i( 0 ); i < yaal::size( pathTest ); ++ i ) {
		HFSItem fit( pathTest[i]._path );
		ENSURE( err + pathTest[i]._path, xnor( !! fit, pathTest[i]._exists ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_directory" )
	char const err[] = "failed to recognize directoriesness of given file";
	char const err2[] = "spurious status on non-existing item acquired";
	HFSItem dit1( "./data" );
	ENSURE( err, dit1.is_directory() );
	HFSItem dit2( "./data/" );
	ENSURE( err, dit2.is_directory() );
	HFSItem dit3( "./data/non-existing" );
	ENSURE_THROW( err2, dit3.is_directory(), HFSItemException );
	HFSItem dit4( "./data/non-existing/" );
	ENSURE_THROW( err2, dit4.is_directory(), HFSItemException );
	HFSItem dit5( "./data/xml.xml" );
	ENSURE( err, ! dit5.is_directory() );
	HFSItem dit6( "./data/xml.xml/" );
	ENSURE_THROW( err2, dit6.is_directory(), HFSItemException );
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

TUT_UNIT_TEST( "recurively scan directories" )
	char const* dir = ( setup._argc > 1 ) ? setup._argv[ 1 ] : "./build/";
	recurse( dir );
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_file()" )
	HFSItem f( "./data/bit.xml" );
	HFSItem d( "./data" );
	ENSURE( "invalid is_file on file", f.is_file() );
	ENSURE_NOT( "invalid is_file on directory", d.is_file() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "size()" )
	HFSItem f( "./data/karatsuba.bc" );
	ENSURE_EQUALS( "bad size", f.size(), 1137 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_name()" )
	static char const PATH[] = "./data/karatsuba.bc";
	HFSItem f( PATH );
	ENSURE_EQUALS( "bad size", f.get_name(), PATH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "status_changed()" )
	static char const PATH[] = "./out/file.txt";
	filesystem::remove( PATH );
	HFile f( PATH, HFile::OPEN::WRITING );
	HTime now( now_local() );
	HFSItem fi( PATH );
	ENSURE_EQUALS( "bad status_changed", fi.status_changed(), now );
	ENSURE_EQUALS( "bad modified", fi.modified(), now );
	ENSURE_EQUALS( "bad accessed", fi.accessed(), now );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modified()" )
	sleep_for( time::duration( 2, time::UNIT::SECOND ) );
	static char const PATH[] = "./out/file.txt";
	HFile f( PATH, HFile::OPEN::WRITING | HFile::OPEN::APPEND );
	f << "data" << endl;
	f.close();
	HTime now( now_local() );
	HFSItem fi( PATH );
	ENSURE_EQUALS( "bad modified", fi.modified(), now );
	ENSURE_EQUALS( "bad status_changed", fi.status_changed(), now );
/* this test will fail on file systems with noatime option enabled */
#ifndef __MSVCXX__
#ifndef __HOST_OS_TYPE_CYGWIN__
	ENSURE( "bad accessed", fi.accessed() != now );
#endif
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "accessed()" )
	sleep_for( time::duration( 2, time::UNIT::SECOND ) );
	static char const PATH[] = "./out/file.txt";
	HFile f( PATH, HFile::OPEN::READING );
	HString l;
	getline( f, l );
	f.close();
	HTime now( now_local() );
	HFSItem fi( PATH );
	ENSURE( "bad status_changed", fi.status_changed() != now );
	ENSURE( "bad modified", fi.modified() != now );
/* Linux: This test will fail on file systems with noatime option enabled */
/* Windows: To save system resources in Vista, Microsoft disabled the Last Access Time Stamp. */
#ifndef __MSVCXX__
#ifndef __HOST_OS_TYPE_CYGWIN__
#ifndef __HOST_OS_TYPE_DARWIN__
	ENSURE_EQUALS( "bad accessed", fi.accessed(), now );
#endif
#endif
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_permissions()" )
	static char const PATH[] = "./out/file.txt";
	filesystem::chmod( PATH, 0600 );
	HFSItem f( PATH );
#ifdef __MSVCXX__
	int rwExpect( 0666 );
	int roExpect( 0444 );
#else
	int rwExpect( 0600 );
	int roExpect( 0400 );
#endif
	ENSURE_EQUALS( "bad permissions", f.get_permissions(), rwExpect );
	filesystem::chmod( PATH, 0400 );
	HFSItem f2( PATH );
	ENSURE_EQUALS( "bad permissions", f2.get_permissions(), roExpect );
	filesystem::chmod( PATH, 0666 );
	filesystem::remove( PATH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	HFSItem f( "./data/karatsuba.bc" );
	u64_t fid( f.id() );
	HFSItem d( "./data" );
	u64_t did( d.id() );
	using yaal::swap;
	swap( f, d );
	ENSURE_EQUALS( "bad id after swap", f.id(), did );
	ENSURE_EQUALS( "bad id after swap", d.id(), fid );
TUT_TEARDOWN()

TUT_UNIT_TEST( "iterator swap" )
	HFSItem d( "./data" );
	HFSItem::HIterator it( d.begin() );
	HFSItem::HIterator it2( it );
	u64_t id0( (*it).id() );
	++ it;
	u64_t id1( (*it).id() );
	ENSURE( "++ failed", it->id() != id0 );
	using yaal::swap;
	swap( it, it2 );
	ENSURE_EQUALS( "swap in iter failed", it->id(), id0 );
	ENSURE_EQUALS( "swap in iter failed", it2->id(), id1 );
	it2 = it;
	ENSURE_EQUALS( "assign of iter failed", it2->id(), id0 );
	++ it;
	ENSURE_EQUALS( "++ on iter failed", it->id(), id1 );
	++ it2;
	ENSURE_EQUALS( "++ on iter failed", it2->id(), id1 );
TUT_TEARDOWN()

}
