/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hfile.cxx - this file is integral part of `tress' project.

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
TUT_TEARDOWN()

}

