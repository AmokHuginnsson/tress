/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hmemorymappedfile.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hmemorymappedfile );
TUT_TEST_GROUP( tut_yaal_tools_hmemorymappedfile, "yaal::tools::HMemoryMappedFile" );

TUT_UNIT_TEST( "the test" )
	char const PATH[] = "./data/karatsuba.bc";
	HMemoryMappedFile mmf( PATH );
	typedef yaal::hcore::HArray<yaal::u8_t> data_t;
	data_t m( static_cast<yaal::u8_t*>( mmf.map() ), static_cast<yaal::u8_t*>( mmf.map() ) + mmf.size() );
	HFile f( PATH, HFile::OPEN::READING );
	int s( 10000 );
	HChunk c( s );
	int long rs( f.read( c.raw(), s ) );
	data_t exp( c.get<yaal::u8_t>(), c.get<yaal::u8_t>() + rs );
	ENSURE_EQUALS( "file mapping into memory failed", m, exp );
	clog.write( mmf.map(), mmf.get_size() );
	clog << endl;
TUT_TEARDOWN()

}

