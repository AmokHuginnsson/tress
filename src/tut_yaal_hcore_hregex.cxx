/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hregex.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hregex );
TUT_TEST_GROUP( tut_yaal_hcore_hregex, "yaal::hcore::HRegex" );

TUT_UNIT_TEST( "empty pattern" )
	HRegex r;
	ENSURE_THROW( "match on unitialized regex succeeded", r.matches( "a" ), HRegexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "simple match" )
	HRegex r( "ala" );
	char const str[] = "xxxalayyy";
	HRegex::HMatchIterator it( r.find( str ) );
	HString m( str + it->start(), it->size() );
	ENSURE_EQUALS( "bad match", m, "ala" );
	ENSURE_NOT( "invalid match", r.matches( "Ala" ) );
	clog << r.error() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "multiple occurrences UTF-8" )
	HString data( "Mężny bądź, chroń pułk twój i sześć flag!" );
	HString expect( "{Mężny}{bądź}{chroń}{pułk}{twój}{i}{sześć}{flag}" );
	HRegex r( "\\p{L}+" );
	HString res;
	int i( 0 );
	for ( HRegex::HMatch const& m : r.matches( data ) ) {
		clog << "match[" << i << "] = ( " << m.start() << ", " << m.size() << " ) = " << data.substr( m.start(), m.size() ) << endl;
		res.append( "{" ).append( data, m.start(), m.size() ).append( "}" );
		++ i;
	}
	ENSURE_EQUALS( "bad match", res, expect );
	clog << r.error() << ": " << res << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "multiple occurrences" )
	HRegex r( "A.a" );
	char const str[] = "xxxAlayyyAgazzz";
	HString res;
	for ( HRegex::HMatch const& m : r.matches( str ) ) {
		res.append( str + m.start(), m.size() );
	}
	ENSURE_EQUALS( "bad match", res, "AlaAga" );
	clog << r.error() << ": " << res << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "multiple occurrences overlapping" )
	HRegex r( "([0-9]+)" );
	char const str[] = "abc012def789ghi";
	HString res;
	for ( HRegex::HMatch const& m : r.matches( str ) ) {
		res.append( str + m.start(), m.size() );
	}
	ENSURE_EQUALS( "bad match", res, "012789" );
	clog << r.error() << ": " << res << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "groups" )
	HRegex r( "^([a-z]*)@([a-z.]*)$" );
	char const str[] = "user@example.com";
	typedef HArray<HString> strings_t;
	strings_t s;
	for ( HRegex::HMatch m : r.groups( str ) ) {
		s.emplace_back( str + m.start(), m.size() );
	}
	ENSURE_EQUALS( "groups failed", s, strings_t{ str, "user", "example.com" } );
	ENSURE( "groups on non-match failed", r.groups( "user@example2.com" ).is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ignorecase match" )
	HRegex r( "ala", HRegex::COMPILE::IGNORE_CASE );
	char const str[] = "xxxAlayyy";
	HRegex::HMatchIterator it( r.find( str ) );
	HString m( str + it->start(), it->size() );
	ENSURE_EQUALS( "bad match", m, "Ala" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "bad regex constructor" )
	ENSURE_THROW( "bad regex constucted", HRegex r( "[a-z" ), HRegexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "bad regex constructor no exception" )
	HRegex r( "[a-z", HRegex::COMPILE::NO_EXCEPTION );
	ENSURE_THROW( "match on unitialized regex succeeded", r.matches( "a" ), HRegexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "match of empty" )
	HRegex r;
	ENSURE( "compilation of loose failed", r.compile( ".*" ) );
	ENSURE( "match of empty failed", r.matches( "" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "huginn identifier from huginn program" )
	hcore::HString identifier( "\\b[a-zA-Z_][a-zA-Z0-9_]*\\b" );
	HRegex r( identifier );
	char const str[] = "main() {\n\treturn( 0 );\n}\n";
	HRegex::HMatchIterator it( r.find( str ) );
	HString m( str + it->start(), it->size() );
	ENSURE_EQUALS( "bad match", m, "main" );
	clog << r.error() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "replace(backref)" )
	HRegex r( "([0-9]+)" );
	ENSURE_EQUALS( "replace(backref) failed (matching)", r.replace( "abc012def789ghi456rst", "$$$1}" ), "abc$012}def$789}ghi$456}rst" );
	ENSURE_EQUALS( "replace(backref) failed (non-matching)", r.replace( "abc!@#def&*(ghi", "{$1}" ), "abc!@#def&*(ghi" );
	ENSURE_THROW( "invlid backref succeeded", r.replace( "abc012def789ghi", "{$" ), HRegexException );
	ENSURE_THROW( "invlid backref succeeded", r.replace( "abc012def789ghi", "a$a" ), HRegexException );
	ENSURE_THROW( "invlid backref succeeded", r.replace( "abc012def789ghi", "$2" ), HRegexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "replace(fun)" )
	HRegex r( "[0-9]+" );
	ENSURE_EQUALS( "replace(fun) failed (matching)", r.replace( "abc012def789ghi", HRegex::replacer_t( []( yaal::hcore::HString const& s ){ return ( "{" + s + "}" ); } ) ), "abc{012}def{789}ghi" );
	ENSURE_EQUALS( "replace(fun) failed (non-matching)", r.replace( "abc!@#def&*(ghi", HRegex::replacer_t( []( yaal::hcore::HString const& s ){ return ( "{" + s + "}" ); } ) ), "abc!@#def&*(ghi" );
TUT_TEARDOWN()

}

