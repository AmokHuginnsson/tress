/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hfile.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hfile );
TUT_TEST_GROUP( tut_yaal_hcore_hfile, "yaal::hcore::HFile" );

TUT_UNIT_TEST( "HFile::READ::UNBUFFERED_READS (nl)" )
	HFile in( "./data/nl.txt", HFile::OPEN::READING );
	HString line;
	HString res;
	int lineCount( 0 );
	while ( in.read_line( line, HFile::READ::UNBUFFERED_READS ) >= 0 ) {
		res.append( line );
		++ lineCount;
	}
	ENSURE_EQUALS( "unbuffered reads nl failed", res, "Alamakota." );
	ENSURE_EQUALS( "bad line count for unbuffered reads nl", lineCount, 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFile::READ::UNBUFFERED_READS (crnl)" )
	HFile in( "./data/crnl.txt", HFile::OPEN::READING );
	HString line;
	HString res;
	int lineCount( 0 );
	while ( in.read_line( line, HFile::READ::UNBUFFERED_READS ) >= 0 ) {
		res.append( line );
		++ lineCount;
	}
	ENSURE_EQUALS( "unbuffered reads crnl failed", res, "Alamakota." );
	ENSURE_EQUALS( "bad line count for unbuffered reads crnl", lineCount, 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFile::READ::BUFFERED_READS (nl)" )
	HFile in( "./data/nl.txt", HFile::OPEN::READING );
	HString line;
	HString res;
	int lineCount( 0 );
	while ( in.read_line( line, HFile::READ::BUFFERED_READS ) >= 0 ) {
		res.append( line );
		++ lineCount;
	}
	ENSURE_EQUALS( "buffered reads nl failed", res, "Alamakota." );
	ENSURE_EQUALS( "bad line count for buffered reads nl", lineCount, 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFile::READ::BUFFERED_READS (crnl)" )
	HFile in( "./data/crnl.txt", HFile::OPEN::READING );
	HString line;
	HString res;
	int lineCount( 0 );
	while ( in.read_line( line, HFile::READ::BUFFERED_READS ) >= 0 ) {
		res.append( line );
		++ lineCount;
	}
	ENSURE_EQUALS( "buffered reads crnl failed", res, "Alamakota." );
	ENSURE_EQUALS( "bad line count for buffered reads crnl", lineCount, 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFile::write (overwrite)" )
	for ( int l( 0 ); l < 2; ++ l ) {
		char const data[][8] = {
			"amok00",
			"huginn",
			"yaal00",
			"tress0"
		};
		HFile out( "./out/file.dat", HFile::OPEN::WRITING );
		for ( char const* w : data ) {
			out << w << "\n";
		}
		out.flush();
		out.close();
		HFile in( "./out/file.dat", HFile::OPEN::READING );
		int i( 0 );
		HString line;
		while ( getline( in, line ).good() ) {
			ENSURE_EQUALS( "bad data written to file", line, data[i] );
			++ i;
		}
		ENSURE_EQUALS( "bad line count", i, countof ( data ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFile::write (append)" )
	char const data[][8] = {
		"amok11",
		"huginn",
		"yaal11",
		"tress1"
	};
	char const dataOut[][8] = {
		"amok00",
		"huginn",
		"yaal00",
		"tress0",
		"amok11",
		"huginn",
		"yaal11",
		"tress1"
	};
	HFile out( "./out/file.dat", HFile::OPEN::WRITING | HFile::OPEN::APPEND );
	for ( char const* w : data ) {
		out << w << "\n";
	}
	out.flush();
	out.close();
	HFile in( "./out/file.dat", HFile::OPEN::READING );
	int i( 0 );
	HString line;
	while ( getline( in, line ).good() ) {
		ENSURE_EQUALS( "bad data written to file", line, dataOut[i] );
		++ i;
	}
	ENSURE_EQUALS( "bad line count", i, countof ( dataOut ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFile::tell()" )
	HFile in( "./out/file.dat", HFile::OPEN::READING );
	HString line;
	while ( getline( in, line ).good() ) {
	}
	ENSURE_EQUALS( "bad tell() after full read", in.tell(), 56 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HFile::seek()" )
	HFile in( "./out/file.dat", HFile::OPEN::READING );
	HString line;
	while ( getline( in, line ).good() ) {
	}
	ENSURE_EQUALS( "bad tell() after full read", in.tell(), 56 );
	in.seek( 28 );
	char const data[][8] = {
		"amok11",
		"huginn",
		"yaal11",
		"tress1"
	};
	int i( 0 );
	while ( getline( in, line ).good() ) {
		ENSURE_EQUALS( "bad data written to file", line, data[i] );
		++ i;
	}
	ENSURE_EQUALS( "bad line count", i, countof ( data ) );
	HFile f( "./out/file.dat", HFile::OPEN::READING | HFile::OPEN::WRITING );
	ENSURE_EQUALS( "bad tell() after RW open", f.tell(), 0 );
	f << "XXXXXX" << endl;
	ENSURE_EQUALS( "bad tell() after line write", f.tell(), 7 );
	f.seek( 7, HFile::SEEK::CUR );
	ENSURE_EQUALS( "bad tell() after line write", f.tell(), 14 );
	f << "YYYYYY" << endl;
	ENSURE_EQUALS( "bad tell() after line write", f.tell(), 21 );
	f.seek( -14, HFile::SEEK::END );
	ENSURE_EQUALS( "bad tell() after line write", f.tell(), 56 - 14 );
	f << "ZZZZZZ" << endl;
	ENSURE_EQUALS( "bad tell() after line write", f.tell(), 56 - 7 );
	f.seek( 0, HFile::SEEK::SET );
	char const dataOut[][8] = {
		"XXXXXX",
		"huginn",
		"YYYYYY",
		"tress0",
		"amok11",
		"huginn",
		"ZZZZZZ",
		"tress1"
	};
	i = 0;
	while ( getline( f, line ).good() ) {
		ENSURE_EQUALS( "bad data written to file", line, dataOut[i] );
		++ i;
	}
	ENSURE_EQUALS( "bad line count", i, countof ( dataOut ) );
TUT_TEARDOWN()

}

