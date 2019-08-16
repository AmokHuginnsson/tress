/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <algorithm>
#include "config.hxx"
#ifdef __GNUC__
#ifdef HAVE_SGI_STL_EXTENSIONS
#include <ext/algorithm>
#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */
#endif /* #ifdef __GNUC__ */

#include "tut_helpers.hxx"
#include <TUT/tut.hpp>

#include <yaal/hcore/algorithm.hxx>
#include <yaal/hcore/hhashset.hxx>
#include <yaal/hcore/random.hxx>
#include <yaal/hcore/hformat.hxx>
#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::random;
using namespace yaal::ansi;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_algorithm );
TUT_TEST_GROUP( tut_yaal_algorithm, "yaal::algorithm" );

TUT_UNIT_TEST( "lexicographical_compare" )
	HString s1( "abcd" );
	HString s1b( "abcd" );
	HString s2( "abcde" );
	HString s3( "abdd" );
	ENSURE_NOT( "lexicographical_compare on rand-acc eq failed", lexicographical_compare( s1.begin(), s1.end(), s1b.begin(), s1b.end() ) );
	ENSURE( "lexicographical_compare rand-acc abcd < abdd failed", lexicographical_compare( s1.begin(), s1.end(), s3.begin(), s3.end() ) );
	ENSURE_NOT( "lexicographical_compare rand-acc abdd < abcd failed", lexicographical_compare( s3.begin(), s3.end(), s1.begin(), s1.end() ) );
	ENSURE( "lexicographical_compare rand-acc abcd < abcde failed", lexicographical_compare( s1.begin(), s1.end(), s2.begin(), s2.end() ) );
	ENSURE_NOT( "lexicographical_compare rand-acc abcde < abcd failed", lexicographical_compare( s2.begin(), s2.end(), s1.begin(), s1.end() ) );

	ENSURE_NOT( "lexicographical_compare rand-acc (op) on eq failed", lexicographical_compare( s1.begin(), s1.end(), s1b.begin(), s1b.end(), yaal::less<code_point_t>() ) );
	ENSURE( "lexicographical_compare rand-acc abcd (op) abdd failed", lexicographical_compare( s1.begin(), s1.end(), s3.begin(), s3.end(), yaal::less<code_point_t>() ) );
	ENSURE_NOT( "lexicographical_compare rand-acc abdd (op) abcd failed", lexicographical_compare( s3.begin(), s3.end(), s1.begin(), s1.end(), yaal::less<code_point_t>() ) );
	ENSURE( "lexicographical_compare rand-acc abcd (op) abcde failed", lexicographical_compare( s1.begin(), s1.end(), s2.begin(), s2.end(), yaal::less<code_point_t>() ) );
	ENSURE_NOT( "lexicographical_compare rand-acc abcde (op) abcd failed", lexicographical_compare( s2.begin(), s2.end(), s1.begin(), s1.end(), yaal::less<code_point_t>() ) );

	int_list_t l1( { 'a', 'b', 'c', 'd' } );
	int_list_t l1b( { 'a', 'b', 'c', 'd' } );
	int_list_t l2( { 'a', 'b', 'c', 'd', 'e' } );
	int_list_t l3( { 'a', 'b', 'd', 'd' } );
	ENSURE_NOT( "lexicographical_compare fwd on eq failed", lexicographical_compare( l1.begin(), l1.end(), l1b.begin(), l1b.end() ) );
	ENSURE( "lexicographical_compare fwd abcd < abdd failed", lexicographical_compare( l1.begin(), l1.end(), l3.begin(), l3.end() ) );
	ENSURE_NOT( "lexicographical_compare fwd abdd < abcd failed", lexicographical_compare( l3.begin(), l3.end(), l1.begin(), l1.end() ) );
	ENSURE( "lexicographical_compare fwd abcd < abcde failed", lexicographical_compare( l1.begin(), l1.end(), l2.begin(), l2.end() ) );
	ENSURE_NOT( "lexicographical_compare fwd abcde < abcd failed", lexicographical_compare( l2.begin(), l2.end(), l1.begin(), l1.end() ) );

	ENSURE_NOT( "lexicographical_compare fwd (op) on eq failed", lexicographical_compare( l1.begin(), l1.end(), l1b.begin(), l1b.end(), yaal::less<yaal::u32_t>() ) );
	ENSURE( "lexicographical_compare fwd abcd (op) abdd failed", lexicographical_compare( l1.begin(), l1.end(), l3.begin(), l3.end(), yaal::less<yaal::u32_t>() ) );
	ENSURE_NOT( "lexicographical_compare fwd abdd (op) abcd failed", lexicographical_compare( l3.begin(), l3.end(), l1.begin(), l1.end(), yaal::less<yaal::u32_t>() ) );
	ENSURE( "lexicographical_compare fwd abcd (op) abcde failed", lexicographical_compare( l1.begin(), l1.end(), l2.begin(), l2.end(), yaal::less<yaal::u32_t>() ) );
	ENSURE_NOT( "lexicographical_compare fwd abcde (op) abcd failed", lexicographical_compare( l2.begin(), l2.end(), l1.begin(), l1.end(), yaal::less<yaal::u32_t>() ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse" )
	int const LENE = 4;
	HPointer<char[]> spe( new char[ LENE + 1 ] );
	char* se( spe.raw() );
	char const* datae = "1234\0";
	char const* revdatae = "4321\0";
	copy_n( datae, LENE + 1, se );
	ENSURE_EQUALS( "test init failed (even)", HString( se ), HString( datae ) );
	yaal::reverse( se, se + LENE );
	ENSURE_EQUALS( "reverse of even number of elements failed", HString( se ), HString( revdatae ) );

	int const LENO = 5;
	HPointer<char[]> spo( new char[ LENO + 1 ] );
	char* so( spo.raw() );
	char const* datao = "12345\0";
	char const* revdatao = "54321\0";
	copy_n( datao, LENO + 1, so );
	ENSURE_EQUALS( "test init failed (odd)", HString( so ), HString( datao ) );
	yaal::reverse( so, so + LENO );
	ENSURE_EQUALS( "reverse of even number of elements failed", HString( so ), HString( revdatao ) );
	HString s1( "!ABCa#$q%^&w0def1ghi2@" );
	HString s2( "@2ihg1fed0w&^%q$#aCBA!" );
	yaal::reverse( s2.begin(), s2.end() );
	ENSURE_EQUALS( "reverse on HString failed", s2, s1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "next_permutation, len = 1 (even)" )
	int const LEN = 1;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "next_permutation, len = 2 (even)" )
	int const LEN = 2;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "12\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "next_permutation, len = 3 (odd)" )
	int const LEN = 3;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "123\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "123" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "next_permutation len = 4 (even)" )
	int const LEN = 4;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1234\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1234" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "next_permutation len = 5 (odd)" )
	int const LEN = 5;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "12345\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12345" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12354" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12435" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12453" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12534" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12543" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13245" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13254" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13425" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13452" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13524" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13542" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14235" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14253" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14325" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14352" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14523" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14532" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21345" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21354" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21435" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21453" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21534" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21543" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23145" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23154" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23415" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23451" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23514" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23541" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24135" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24153" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24315" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24351" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24513" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24531" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31245" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31254" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31425" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31452" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31524" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31542" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32145" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32154" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32415" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32451" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32514" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32541" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34125" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34152" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34215" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34251" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34512" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34521" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41235" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41253" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41325" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41352" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41523" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41532" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42135" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42153" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42315" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42351" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42513" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42531" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43125" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43152" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43215" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43251" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43512" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43521" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12345" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "prev_permutation, len = 1 (even)" )
	int const LEN = 1;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "prev_permutation, len = 2 (even)" )
	int const LEN = 2;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "21\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "prev_permutation len = 3 (odd)" )
	int const LEN = 3;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "321\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "321" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "312" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "231" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "213" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "132" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "123" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "321" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "prev_permutation len = 4 (even)" )
	int const LEN = 4;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "4321\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4321" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4312" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4231" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4213" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4132" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4123" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3421" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3412" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3241" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3214" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3142" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3124" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2431" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2413" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2341" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2314" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2143" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2134" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1432" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1423" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1342" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1324" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1243" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1234" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4321" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "prev_permutation len = 5 (odd)" )
	int const LEN = 5;
	HPointer<char[]> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "54321\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54321" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54312" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54231" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54213" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54132" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54123" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53421" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53412" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53241" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53214" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53142" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53124" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52431" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52413" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52341" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52314" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52143" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52134" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51432" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51423" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51342" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51324" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51243" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51234" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45321" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45312" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45231" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45213" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45132" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45123" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43521" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43512" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43251" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43215" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43152" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43125" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42531" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42513" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42351" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42315" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42153" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42135" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41532" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41523" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41352" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41325" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41253" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41235" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35421" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35412" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35241" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35214" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35142" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35124" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34521" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34512" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34251" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34215" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34152" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34125" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32541" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32514" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32451" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32415" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32154" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32145" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31542" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31524" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31452" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31425" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31254" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31245" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25431" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25413" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25341" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25314" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25143" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25134" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24531" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24513" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24351" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24315" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24153" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24135" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23541" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23514" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23451" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23415" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23154" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23145" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21543" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21534" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21453" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21435" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21354" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21345" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15432" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15423" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15342" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15324" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15243" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15234" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14532" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14523" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14352" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14325" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14253" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14235" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13542" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13524" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13452" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13425" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13254" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13245" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12543" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12534" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12453" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12435" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12354" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12345" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54321" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_heap" )
	std_vector_t v( begin( _testData_[0] ), end( _testData_[0] ) );
	int_array_t a( begin( _testData_[0] ), end( _testData_[0] ) );
	for ( int i( 2 ); i < yaal::size( _testData_[0] ); ++ i ) {
#ifndef _MSC_VER
#ifdef HAVE_SGI_STL_EXTENSIONS
		ENSURE_EQUALS( "stdext::is_heap false positive: " + lexical_cast<HString>( i ), stdext::is_heap( v.begin(), v.begin() + i ), false );
#endif /* #ifdef HAVE_SGI_STL_EXTENSIONS */
#endif /* #ifndef _MSC_VER */
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		yaal::push_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::is_heap false negative: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), true );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "push_heap" )
	std_vector_t v( begin( _testData_[0] ), end( _testData_[0] ) );
	int_array_t a( begin( _testData_[0] ), end( _testData_[0] ) );
	for ( int i( 2 ); i <= yaal::size( _testData_[0] ); ++ i ) {
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		push_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::push_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), true );
		ENSURE_EQUALS( "yaal::push_heap wrong: " + lexical_cast<HString>( i ), a, v );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "pop_heap" )
	std_vector_t v( begin( _testData_[0] ), end( _testData_[0] ) );
	int_array_t a( begin( _testData_[0] ), end( _testData_[0] ) );
	for ( int i( 2 ); i <= yaal::size( _testData_[0] ); ++ i ) {
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		push_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::push_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), true );
		ENSURE_EQUALS( "yaal::push_heap wrong: " + lexical_cast<HString>( i ), a, v );
	}

	for ( int i( yaal::size( _testData_[0] ) ); i > 0; -- i ) {
		std::pop_heap( v.begin(), v.begin() + i );
		pop_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::pop_heap wrong: " + lexical_cast<HString>( i ), a, v );
		ENSURE_EQUALS( "yaal::pop_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i - 1 ), true );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "make_heap" )
	std_vector_t v( begin( _testData_[0] ), end( _testData_[0] ) );
	int_array_t a( begin( _testData_[0] ), end( _testData_[0] ) );
	ENSURE_EQUALS( "yaal::is_heap false positive", yaal::is_heap( a.begin(), a.end() ), false );
	std::make_heap( v.begin(), v.end() );
	make_heap( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::make_heap failed", yaal::is_heap( a.begin(), a.end() ), true );
	for ( int i( yaal::size( _testData_[0] ) ); i > 0; -- i ) {
		std::pop_heap( v.begin(), v.begin() + i );
		pop_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::pop_heap wrong: " + lexical_cast<HString>( i ), a.front(), v.front() );
		ENSURE_EQUALS( "yaal::pop_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i - 1 ), true );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "sort_heap" )
	std_vector_t v( 100 );
	int_array_t a( 100 );
	distribution::HDiscrete r( 0, 255 );
	r.generator()->set_seed( 0 );
	ENSURE_EQUALS( "bad range on randomizer", r.range(), static_cast<u64_t>( 256 ) );
	std::generate( v.begin(), v.end(), r );
	r.generator()->set_seed( 0 );
	yaal::generate( a.begin(), a.end(), r );
	*v.rbegin() = -1;
	*a.rbegin() = -1;
	ENSURE_EQUALS( "wrong generation", a, v );
	clog << a << endl;
	ENSURE_EQUALS( "yaal::is_heap false positive", yaal::is_heap( a.begin(), a.end() ), false );
	std::make_heap( v.begin(), v.end() );
	make_heap( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::make_heap failed", yaal::is_heap( a.begin(), a.end() ), true );
	/* ENSURE_EQUALS( "yaal::make_heap wrong", a, v ); */
	std::sort_heap( v.begin(), v.end() );
	sort_heap( a.begin(), a.begin() ); /* Will crash if badly implemented. */
	sort_heap( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::sort_heap wrong", a, v );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sort" )
	int_array_t a( 100 );
	distribution::HDiscrete rng( 0, 255 );
	rng.generator()->set_seed( 0 );
	yaal::generate( a.begin(), a.end(), rng );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	std::sort( v.begin(), v.end() );
	sort( a.begin(), a.begin() ); /* Will crash if badly implemented. */
	sort( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::sort wrong", a, v );
	clog << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "unique" )
	int_array_t a( 100 );
	distribution::HDiscrete rng( 0, 255 );
	rng.generator()->set_seed( 0 );
	yaal::generate( a.begin(), a.end(), rng );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	std::sort( v.begin(), v.end() );
	sort( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::sort wrong", a, v );
	clog << a << endl;
	v.erase( std::unique( v.begin(), v.end() ), v.end() );
	a.erase( unique( a.begin(), a.end() ), a.end() );
	ENSURE_EQUALS( "yaal::sort wrong", a, v );
	clog << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "rotate" )
	int_array_t a( 100 );
	yaal::generate( a.begin(), a.end(), inc( 1 ) );
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	int_array_t::iterator it( rotate( a.begin(), a.begin() + 33, a.end() ) );
	std::rotate( v.begin(), v.begin() + 33, v.end() );
	ENSURE_EQUALS( "yaal::rotate wrong", a, v );
	clog << "(" << *it << ") " << a << endl;
	int_array_t::iterator it2( rotate( a.begin(), it, a.end() ) );
	std::rotate( v.begin(), v.begin() + 67, v.end() );
	ENSURE_EQUALS( "yaal::rotate wrong", a, v );
	clog << "(" << *it2 << ") " << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "inplace_merge" )
	int_array_t a( 100 );
	yaal::generate( a.begin(), a.end(), inc( 1 ) );
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	int_array_t::iterator it( rotate( a.begin(), a.begin() + 33, a.end() ) );
	std::rotate( v.begin(), v.begin() + 33, v.end() );
	ENSURE_EQUALS( "yaal::rotate wrong", a, v );
	clog << "(" << *it << ") " << a << endl;
	inplace_merge( a.begin(), it, a.end() );
	std::inplace_merge( v.begin(), v.begin() + 67, v.end() );
	ENSURE_EQUALS( "yaal::inplace_merge wrong", a, v );
	clog << a << endl;
	int arrTempl[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 3, 6, 9, 15, 18, 21, 24, 27, 30 };
	int_array_t arr( arrTempl, arrTempl + yaal::size( arrTempl ) );
	std_vector_t varr( &*arr.begin(), &*arr.begin() + arr.get_size() );
	std::clog << varr << std::endl;
	std::inplace_merge( varr.begin(), varr.begin() + 9, varr.end() );
	std::clog << varr << std::endl;
	clog << arr << endl;
	inplace_merge( arr.begin(), arr.begin() + 9, arr.end() );
	clog << arr << endl;
	ENSURE_EQUALS( "yaal::inplace_merge wrong", arr, varr );
	std::copy( arrTempl, arrTempl + yaal::size( arrTempl ), varr.begin() );
	std::rotate( varr.begin(), varr.begin() + 9, varr.end() );
	std::clog << varr << std::endl;
	copy( arrTempl, arrTempl + yaal::size( arrTempl ), arr.begin() );
	rotate( arr.begin(), arr.begin() + 9, arr.end() );
	clog << arr << endl;
	ENSURE_EQUALS( "yaal::copy + yaal::rotate wrong", arr, varr );
	std::inplace_merge( varr.begin(), varr.begin() + 9, varr.end() );
	std::clog << varr << std::endl;
	inplace_merge( arr.begin(), arr.begin() + 9, arr.end() );
	clog << arr << endl;
	ENSURE_EQUALS( "yaal::inplace_merge wrong", arr, varr );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert_sort" )
	TIME_CONSTRAINT_EXEMPT(); {
	int_array_t a( 8000 );
	yaal::generate( a.begin(), a.end(), HRandomNumberGenerator( 0 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	std::sort( v.begin(), v.end() ); {
		HClock c;
		insert_sort( a.begin(), a.end(), less<int>(), iterator_category::forward() );
		clog << "*speed* yaal::insert_sort(forward) = " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
	}
	ENSURE_EQUALS( "yaal::insert_sort(forward) wrong", a, v ); {
		HClock c;
		insert_sort( a.begin(), a.end(), less<int>(), iterator_category::forward() );
		clog << "*speed* yaal::insert_sort(forward) sorted = " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
	}
	ENSURE_EQUALS( "yaal::insert_sort(forward) wrong", a, v );
} {
	int_array_t a( 8000 );
	yaal::generate( a.begin(), a.end(), HRandomNumberGenerator( 0 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	std::sort( v.begin(), v.end() ); {
		HClock c;
		insert_sort( a.begin(), a.end(), less<int>(), iterator_category::random_access() );
		clog << "*speed* yaal::insert_sort(random_access) = " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
	}
	ENSURE_EQUALS( "yaal::insert_sort(random_access) wrong", a, v ); {
		HClock c;
		insert_sort( a.begin(), a.end(), less<int>(), iterator_category::random_access() );
		clog << "*speed* yaal::insert_sort(random_access) = " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
	}
	ENSURE_EQUALS( "yaal::insert_sort(random_access) wrong", a, v );
}
TUT_TEARDOWN()

TUT_UNIT_TEST( "selection_sort" )
	TIME_CONSTRAINT_EXEMPT();
	int_array_t a( 8000 );
	yaal::generate( a.begin(), a.end(), HRandomNumberGenerator( 0 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	std::sort( v.begin(), v.end() );
	HClock c;
	selection_sort( a.begin(), a.end(), less<int>() );
	clog << "*speed* yaal::selection_sort = " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
	ENSURE_EQUALS( "yaal::selection_sort wrong", a, v );
TUT_TEARDOWN()

TUT_UNIT_TEST( "heap_sort" )
	int_array_t a( 8000 );
	yaal::generate( a.begin(), a.end(), HRandomNumberGenerator( 0 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	std::sort( v.begin(), v.end() );
	HClock c;
	heap_sort( a.begin(), a.begin() ); /* Will crash if badly implemented. */
	heap_sort( a.begin(), a.end() );
	clog << "*speed* yaal::heap_sort = " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
	ENSURE_EQUALS( "yaal::stable_sort wrong", a, v );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stable_sort" )
	int_array_t a( 100 );
	distribution::HDiscrete rng( 0, 255 );
	rng.generator()->set_seed( 0 );
	yaal::generate( a.begin(), a.end(), rng );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	std::stable_sort( v.begin(), v.end() );
	stable_sort( a.begin(), a.begin() ); /* Will crash if badly implemented. */
	stable_sort( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::stable_sort wrong", a, v );
	clog << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "distance" )
	HArray<int> array( begin( _testData_[0] ), end( _testData_[0] ) );
	HDeque<int> deque( begin( _testData_[0] ), end( _testData_[0] ) );
	HList<int> list( begin( _testData_[0] ), end( _testData_[0] ) );
	HSet<int> set( begin( _testData_[0] ), end( _testData_[0] ) );
	HHashSet<int> hashSet( begin( _testData_[0] ), end( _testData_[0] ) );
	HRing<int> ring( ring::capacity_type( yaal::size( _testData_[0] ) * 2 ),
		begin( _testData_[0] ), end( _testData_[0] ) );
	using yaal::distance;
	ENSURE_EQUALS( "distance on HArray<> failed", distance( array.begin(), array.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HDeque<> failed", distance( deque.begin(), deque.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HList<> failed", distance( list.begin(), list.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HSet<> failed", distance( set.begin(), set.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HHashSet<> failed", distance( hashSet.begin(), hashSet.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HRing<> failed", distance( ring.begin(), ring.end() ), yaal::size( _testData_[0] ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	HArray<int> array( begin( _testData_[0] ), end( _testData_[0] ) );
	HDeque<int> deque( begin( _testData_[0] ), end( _testData_[0] ) );
	HList<int> list( begin( _testData_[0] ), end( _testData_[0] ) );
	HSet<int> set( begin( _testData_[0] ), end( _testData_[0] ) );
	HHashSet<int> hashSet( begin( _testData_[0] ), end( _testData_[0] ) );
	HRing<int> ring( ring::capacity_type( yaal::size( _testData_[0] ) * 2 ),
		begin( _testData_[0] ), end( _testData_[0] ) );
	using yaal::distance;
	HArray<int> array2;
	HDeque<int> deque2;
	HList<int> list2;
	HSet<int> set2;
	HHashSet<int> hashSet2;
	HRing<int> ring2;
	swap( array, array2 );
	swap( deque, deque2 );
	swap( list, list2 );
	swap( set, set2 );
	swap( hashSet, hashSet2 );
	swap( ring, ring2 );
	ENSURE_EQUALS( "swap on HArray<> failed", distance( array2.begin(), array2.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HDeque<> failed", distance( deque2.begin(), deque2.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HList<> failed", distance( list2.begin(), list2.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HSet<> failed", distance( set2.begin(), set2.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HHashSet<> failed", distance( hashSet2.begin(), hashSet2.end() ), yaal::size( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HRing<> failed", distance( ring2.begin(), ring2.end() ), yaal::size( _testData_[0] ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "search" )
	char const S1[] = "Hello, world!";
	char const S2[] = "world";
	char const* p( search( S1, ( S1 + yaal::size( S1 ) - 1 ), S2, ( S2 + yaal::size( S2 ) ) - 1 ) );
	ENSURE_EQUALS( "search failed", p, S1 + 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_first_of" )
	char const S1[] = "Hello, world!";
	char const S2[] = "world";
	char const S3[] = "word";
	char const* p( find_first_of( S1, ( S1 + yaal::size( S1 ) - 1 ), S2, ( S2 + yaal::size( S2 ) ) - 1 ) );
	ENSURE_EQUALS( "find_first_of failed (world)", p, S1 + 2 );
	char const* p2( find_first_of( S1, ( S1 + yaal::size( S1 ) - 1 ), S3, ( S3 + yaal::size( S3 ) ) - 1 ) );
	ENSURE_EQUALS( "find_first_of failed (word)", p2, S1 + 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_first_of(cond)" )
	typedef HPair<HString, HString> person_t;
	person_t a[] = { person_t( "Ala", "Kowalska" ), person_t( "Gall", "Anonim" ), person_t( "Marcin", "Konarski" ), person_t( "Magdalena", "Nowak" ), person_t( "Wojciech", "Igrekowski" ) };
	HString n[] = { "Marcin", "Wojciech", "Magdalena" };
	person_t* p( find_first_of( a, a + yaal::size( a ), n, n + yaal::size( n ), compose_binary( equal_to<HString>(), select1st<person_t>(), identity<HString>() ) ) );
	ENSURE_EQUALS( "find_first_of failed (word)", p, a + 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_first_not_of" )
	char const S1[] = "Hello, world!";
	char const S2[] = "worldH";
	char const S3[] = "worldHe";
	char const* p( find_first_not_of( S1, ( S1 + yaal::size( S1 ) - 1 ), S2, ( S2 + yaal::size( S2 ) ) - 1 ) );
	ENSURE_EQUALS( "find_first_not_of failed (worldH)", p, S1 + 1 );
	char const* p2( find_first_not_of( S1, ( S1 + yaal::size( S1 ) - 1 ), S3, ( S3 + yaal::size( S3 ) ) - 1 ) );
	ENSURE_EQUALS( "find_first_not_of failed (worldHe)", p2, S1 + 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_first_not_of(cond)" )
	typedef HPair<HString, HString> person_t;
	person_t a[] = { person_t( "Ala", "Kowalska" ), person_t( "Gall", "Anonim" ), person_t( "Marcin", "Konarski" ), person_t( "Magdalena", "Nowak" ), person_t( "Wojciech", "Igrekowski" ) };
	HString n[] = { "Ala", "Gall", "Magdalena" };
	person_t* p( find_first_not_of( a, a + yaal::size( a ), n, n + yaal::size( n ), compose_binary( equal_to<HString>(), select1st<person_t>(), identity<HString>() ) ) );
	ENSURE_EQUALS( "find_first_not_of failed (word)", p, a + 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "lower_bound() on list" )
	/* distinct */ {
		int_list_t list( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i <= _testData_[0][yaal::size( _testData_[0] ) - 1]; ++ i ) {
			int_list_t::const_iterator it( lower_bound( list.begin(), list.end(), i ) );
			int const* p( std::lower_bound( begin( _testData_[0] ), end( _testData_[0] ), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance( _testData_[0], p ) );
		}
		int_list_t::const_iterator first( lower_bound( list.begin(), list.end(), _testData_[0][0] - 1 ) );
		ENSURE( "lower_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( lower_bound( list.begin(), list.end(), _testData_[0][yaal::size( _testData_[0] ) - 1] + 1 ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	/* repeating */ {
		int_list_t list( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i <= _testData_[2][yaal::size( _testData_[2] ) - 1]; ++ i ) {
			int_list_t::const_iterator it( lower_bound( list.begin(), list.end(), i ) );
			int const* p( std::lower_bound( begin( _testData_[2] ), end( _testData_[2] ), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance( _testData_[2], p ) );
		}
		int_list_t::const_iterator first( lower_bound( list.begin(), list.end(), _testData_[2][0] - 1 ) );
		ENSURE( "lower_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( lower_bound( list.begin(), list.end(), _testData_[2][yaal::size( _testData_[2] ) - 1] + 1 ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	/* repeating generator (increasing range) */ {
		int_list_t list;
		std_list_t data;
		int const NO_RANGES( 16 );
		for ( int r( 1 ); r <= NO_RANGES; ++ r ) {
			for ( int i( 0 ); i < r; ++ i ) {
				list.push_back( r * 2 );
				data.push_back( r * 2 );
			}
		}
		for ( int i( 0 ); i <= ( NO_RANGES * 2 ); ++ i ) {
			int_list_t::const_iterator it( lower_bound( list.begin(), list.end(), i ) );
			std_list_t::const_iterator p( std::lower_bound( data.begin(), data.end(), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance<std_list_t::const_iterator>( data.begin(), p ) );
		}
		int_list_t::const_iterator first( lower_bound( list.begin(), list.end(), -1 ) );
		ENSURE( "lower_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( lower_bound( list.begin(), list.end(), NO_RANGES * 2 + 1 ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	/* repeating generator (decreasing range) */ {
		int_list_t list;
		std_list_t data;
		int const NO_RANGES( 16 );
		for ( int r( 0 ); r < NO_RANGES; ++ r ) {
			for ( int i( 0 ); i < ( NO_RANGES - r ); ++ i ) {
				list.push_back( r * 2 );
				data.push_back( r * 2 );
			}
		}
		for ( int i( 0 ); i < ( NO_RANGES * 2 - 1 ); ++ i ) {
			int_list_t::const_iterator it( lower_bound( list.begin(), list.end(), i ) );
			std_list_t::const_iterator p( std::lower_bound( data.begin(), data.end(), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance<std_list_t::const_iterator>( data.begin(), p ) );
		}
		int_list_t::const_iterator first( lower_bound( list.begin(), list.end(), -1 ) );
		ENSURE( "lower_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( lower_bound( list.begin(), list.end(), NO_RANGES * 2 + 1 ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	int_list_t empty;
	int_list_t::const_iterator it( lower_bound( empty.begin(), empty.end(), 0 ) );
	ENSURE( "lower_bound on empty failed", it == empty.begin() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "lower_bound() on array" )
	/* distinct */ {
		int_array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i <= _testData_[0][yaal::size( _testData_[0] ) - 1]; ++ i ) {
			int_array_t::const_iterator it( lower_bound( array.begin(), array.end(), i ) );
			int const* p( std::lower_bound( begin( _testData_[0] ), end( _testData_[0] ), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance( _testData_[0], p ) );
		}
		int_array_t::const_iterator first( lower_bound( array.begin(), array.end(), _testData_[0][0] - 1 ) );
		ENSURE( "lower_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( lower_bound( array.begin(), array.end(), _testData_[0][yaal::size( _testData_[0] ) - 1] + 1 ) );
		ENSURE( "lower_bound after range failed", last == array.end() );
	}
	/* repeating */ {
		int_array_t array( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i <= _testData_[2][yaal::size( _testData_[2] ) - 1]; ++ i ) {
			int_array_t::const_iterator it( lower_bound( array.begin(), array.end(), i ) );
			int const* p( std::lower_bound( begin( _testData_[2] ), end( _testData_[2] ), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance( _testData_[2], p ) );
		}
		int_array_t::const_iterator first( lower_bound( array.begin(), array.end(), _testData_[2][0] - 1 ) );
		ENSURE( "lower_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( lower_bound( array.begin(), array.end(), _testData_[2][yaal::size( _testData_[2] ) - 1] + 1 ) );
		ENSURE( "lower_bound after range failed", last == array.end() );
	}
	/* repeating generator (increasing range) */ {
		int_array_t array;
		std_vector_t data;
		int const NO_RANGES( 16 );
		for ( int r( 1 ); r <= NO_RANGES; ++ r ) {
			for ( int i( 0 ); i < r; ++ i ) {
				array.push_back( r * 2 );
				data.push_back( r * 2 );
			}
		}
		for ( int i( 0 ); i <= ( NO_RANGES * 2 ); ++ i ) {
			int_array_t::const_iterator it( lower_bound( array.begin(), array.end(), i ) );
			std_vector_t::const_iterator p( std::lower_bound( data.begin(), data.end(), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance<std_vector_t::const_iterator>( data.begin(), p ) );
		}
		int_array_t::const_iterator first( lower_bound( array.begin(), array.end(), -1 ) );
		ENSURE( "lower_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( lower_bound( array.begin(), array.end(), NO_RANGES * 2 + 1 ) );
		ENSURE( "lower_bound after range failed", last == array.end() );
	}
	/* repeating generator (decreasing range) */ {
		int_array_t array;
		std_vector_t data;
		int const NO_RANGES( 16 );
		for ( int r( 0 ); r < NO_RANGES; ++ r ) {
			for ( int i( 0 ); i < ( NO_RANGES - r ); ++ i ) {
				array.push_back( r * 2 );
				data.push_back( r * 2 );
			}
		}
		for ( int i( 0 ); i < NO_RANGES; ++ i ) {
			int_array_t::const_iterator it( lower_bound( array.begin(), array.end(), i ) );
			std_vector_t::const_iterator p( std::lower_bound( data.begin(), data.end(), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance<std_vector_t::const_iterator>( data.begin(), p ) );
		}
		int_array_t::const_iterator first( lower_bound( array.begin(), array.end(), -1 ) );
		ENSURE( "lower_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( lower_bound( array.begin(), array.end(), NO_RANGES * 2 + 1 ) );
		ENSURE( "lower_bound after range failed", last == array.end() );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "upper_bound() on list" )
	/* distinct */ {
		int_list_t list( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i < _testData_[0][yaal::size( _testData_[0] ) - 1]; ++ i ) {
			int_list_t::const_iterator it( upper_bound( list.begin(), list.end(), i ) );
			int const* p( std::upper_bound( begin( _testData_[0] ), end( _testData_[0] ), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance( _testData_[0], p ) );
		}
		int_list_t::const_iterator first( upper_bound( list.begin(), list.end(), _testData_[0][0] - 1 ) );
		ENSURE( "upper_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( upper_bound( list.begin(), list.end(), _testData_[0][yaal::size( _testData_[0] ) - 1] ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	/* repeating */ {
		int_list_t list( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i < _testData_[2][yaal::size( _testData_[2] ) - 1]; ++ i ) {
			int_list_t::const_iterator it( upper_bound( list.begin(), list.end(), i ) );
			int const* p( std::upper_bound( begin( _testData_[2] ), end( _testData_[2] ), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance( _testData_[2], p ) );
		}
		int_list_t::const_iterator first( upper_bound( list.begin(), list.end(), _testData_[2][0] - 1 ) );
		ENSURE( "upper_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( upper_bound( list.begin(), list.end(), _testData_[2][yaal::size( _testData_[2] ) - 1] ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	/* repeating generator (increasing range) */ {
		int_list_t list;
		std_list_t data;
		int const NO_RANGES( 16 );
		for ( int r( 1 ); r <= NO_RANGES; ++ r ) {
			for ( int i( 0 ); i < r; ++ i ) {
				list.push_back( r * 2 );
				data.push_back( r * 2 );
			}
		}
		for ( int i( 0 ); i < ( NO_RANGES * 2 ); ++ i ) {
			int_list_t::const_iterator it( upper_bound( list.begin(), list.end(), i ) );
			std_list_t::const_iterator p( std::upper_bound( data.begin(), data.end(), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "upper_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance<std_list_t::const_iterator>( data.begin(), p ) );
		}
		int_list_t::const_iterator first( upper_bound( list.begin(), list.end(), -1 ) );
		ENSURE( "upper_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( upper_bound( list.begin(), list.end(), ( NO_RANGES * 2 ) ) );
		ENSURE( "upper_bound after range failed", last == list.end() );
	}
	/* repeating generator (decreasing range) */ {
		int_list_t list;
		std_list_t data;
		int const NO_RANGES( 16 );
		for ( int r( 0 ); r < NO_RANGES; ++ r ) {
			for ( int i( 0 ); i < ( NO_RANGES - r ); ++ i ) {
				list.push_back( r * 2 );
				data.push_back( r * 2 );
			}
		}
		for ( int i( 0 ); i < ( NO_RANGES * 2 ) - 2; ++ i ) {
			int_list_t::const_iterator it( upper_bound( list.begin(), list.end(), i ) );
			std_list_t::const_iterator p( std::upper_bound( data.begin(), data.end(), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "upper_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance<std_list_t::const_iterator>( data.begin(), p ) );
		}
		int_list_t::const_iterator first( upper_bound( list.begin(), list.end(), -1 ) );
		ENSURE( "upper_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( upper_bound( list.begin(), list.end(), ( NO_RANGES * 2 ) ) );
		ENSURE( "upper_bound after range failed", last == list.end() );
	}
	int_list_t empty;
	int_list_t::const_iterator it( upper_bound( empty.begin(), empty.end(), 0 ) );
	ENSURE( "lower_bound on empty failed", it == empty.begin() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "upper_bound() on array" )
	/* distinct */ {
		int_array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i < _testData_[0][yaal::size( _testData_[0] ) - 1]; ++ i ) {
			int_array_t::const_iterator it( upper_bound( array.begin(), array.end(), i ) );
			int const* p( std::upper_bound( begin( _testData_[0] ), end( _testData_[0] ), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
		}
		int_array_t::const_iterator first( upper_bound( array.begin(), array.end(), _testData_[0][0] - 1 ) );
		ENSURE( "upper_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( upper_bound( array.begin(), array.end(), _testData_[0][yaal::size( _testData_[0] ) - 1] ) );
		ENSURE( "upper_bound after range failed", last == array.end() );
	}
	/* repeating */ {
		int_array_t array( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i < _testData_[2][yaal::size( _testData_[2] ) - 1]; ++ i ) {
			int_array_t::const_iterator it( upper_bound( array.begin(), array.end(), i ) );
			int const* p( std::upper_bound( begin( _testData_[2] ), end( _testData_[2] ), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance( _testData_[2], p ) );
		}
		int_array_t::const_iterator first( upper_bound( array.begin(), array.end(), _testData_[2][0] - 1 ) );
		ENSURE( "upper_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( upper_bound( array.begin(), array.end(), _testData_[2][yaal::size( _testData_[2] ) - 1] ) );
		ENSURE( "lower_bound after range failed", last == array.end() );
	}
	/* repeating generator (increasing range) */ {
		int_array_t array;
		std_vector_t data;
		int const NO_RANGES( 16 );
		for ( int r( 1 ); r <= NO_RANGES; ++ r ) {
			for ( int i( 0 ); i < r; ++ i ) {
				array.push_back( r * 2 );
				data.push_back( r * 2 );
			}
		}
		for ( int i( 0 ); i < ( NO_RANGES * 2 ); ++ i ) {
			int_array_t::const_iterator it( upper_bound( array.begin(), array.end(), i ) );
			std_vector_t::const_iterator p( std::upper_bound( data.begin(), data.end(), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "upper_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance<std_vector_t::const_iterator>( data.begin(), p ) );
		}
		int_array_t::const_iterator first( upper_bound( array.begin(), array.end(), -1 ) );
		ENSURE( "upper_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( upper_bound( array.begin(), array.end(), ( NO_RANGES * 2 ) ) );
		ENSURE( "upper_bound after range failed", last == array.end() );
	}
	/* repeating generator (decreasing range) */ {
		int_array_t array;
		std_vector_t data;
		int const NO_RANGES( 16 );
		for ( int r( 0 ); r < NO_RANGES; ++ r ) {
			for ( int i( 0 ); i < ( NO_RANGES - r ); ++ i ) {
				array.push_back( r * 2 );
				data.push_back( r * 2 );
			}
		}
		for ( int i( 0 ); i < ( NO_RANGES * 2 ) - 2; ++ i ) {
			int_array_t::const_iterator it( upper_bound( array.begin(), array.end(), i ) );
			std_vector_t::const_iterator p( std::upper_bound( data.begin(), data.end(), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "upper_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance<std_vector_t::const_iterator>( data.begin(), p ) );
		}
		int_array_t::const_iterator first( upper_bound( array.begin(), array.end(), -1 ) );
		ENSURE( "upper_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( upper_bound( array.begin(), array.end(), ( NO_RANGES * 2 ) ) );
		ENSURE( "upper_bound after range failed", last == array.end() );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "binary_search() on list" )
	/* distinct */ {
		int_list_t list( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i < _testData_[0][yaal::size( _testData_[0] ) - 1] + 1; ++ i ) {
			ENSURE_EQUALS( "binary_search on range failed",
					binary_search( list.begin(), list.end(), i ),
					std::binary_search( begin( _testData_[0] ), end( _testData_[0] ), i ) );
		}
	}
	/* repeating */ {
		int_list_t list( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i < _testData_[2][yaal::size( _testData_[2] ) - 1] + 1; ++ i ) {
			ENSURE_EQUALS( "binary_search on range failed",
					binary_search( list.begin(), list.end(), i ),
					std::binary_search( begin( _testData_[2] ), end( _testData_[2] ), i ) );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "binary_search() on array" )
	/* distinct */ {
		int_array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i < _testData_[0][yaal::size( _testData_[0] ) - 1] + 1; ++ i ) {
			ENSURE_EQUALS( "binary_search on range failed",
					binary_search( array.begin(), array.end(), i ),
					std::binary_search( begin( _testData_[0] ), end( _testData_[0] ), i ) );
		}
	}
	/* repeating */ {
		int_array_t array( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i < _testData_[2][yaal::size( _testData_[2] ) - 1] + 1; ++ i ) {
			ENSURE_EQUALS( "binary_search on range failed",
					binary_search( array.begin(), array.end(), i ),
					std::binary_search( begin( _testData_[2] ), end( _testData_[2] ), i ) );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_sorted" )
	ENSURE( "is_sorted on empty failed", is_sorted( _testData_[0], _testData_[0] ) );
	ENSURE( "is_sorted on large failed", is_sorted( begin( _testData_[0] ), end( _testData_[0] ) ) );
	int left[] = { 2, 1, 3, 4, 5, 6, 7 };
	int mid[] = { 1, 2, 3, 5, 4, 6, 7 };
	int right[] = { 1, 2, 3, 4, 5, 7, 6 };
	ENSURE_NOT( "is_sorted false positive on left", is_sorted( left, left + yaal::size( left ) ) );
	ENSURE_NOT( "is_sorted false positive on mid", is_sorted( mid, mid + yaal::size( mid ) ) );
	ENSURE_NOT( "is_sorted false positive on right", is_sorted( right, right + yaal::size( right ) ) );
	ENSURE( "is_sorted on one elem failed", is_sorted( _testData_[0], _testData_[0] + 1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "partition" )
	static int const range = 100;
	int_array_t a( range );
	distribution::HDiscrete r( rng_helper::make_random_number_generator( range ) );
	for ( int n( -range / 3 ); n < range / 3; n += 3 ) {
		for ( int_array_t::iterator it( a.begin() ), end( a.end() ); it != end; ++ it ) {
			*it = static_cast<int>( r() ) - range / 2 + n;
		}
		clog << "pre: " << a << endl;
		int_array_t::iterator m( partition( a.begin(), a.end(), bind2nd( less<int>(), 0 ) ) );
		clog << "pos: " << a << endl;
		for ( int_array_t::iterator it( a.begin() ); it != m; ++ it ) {
			ENSURE( "partition failed (*it < 0)", *it < 0 );
		}
		for ( int_array_t::iterator it( m ), end( a.end() ); it != end; ++ it ) {
			ENSURE( "partition failed (*it >= 0)", *it >= 0 );
		}
		generate( a.begin(), a.end(), inc( -50 + n ) );
		for ( int i( 0 ); i < ( range / 2 ); i += 20 ) {
			swap_ranges( a.begin() + i, a.begin() + i + 10, a.begin() + i + 50 );
		}
		clog << "pre: " << a << endl;
		m = partition( a.begin(), a.end(), bind2nd( less<int>(), 0 ) );
		clog << "pos: " << a << endl;
		for ( int_array_t::iterator it( a.begin() ); it != m; ++ it ) {
			ENSURE( "partition failed (*it < 0)", *it < 0 );
		}
		for ( int_array_t::iterator it( m ), end( a.end() ); it != end; ++ it ) {
			ENSURE( "partition failed (*it >= 0)", *it >= 0 );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "nth_element" )
	int tt[] = { 0, 2 };
	for ( int t( 0 ); t < 2; ++ t ) {
		int_array_t src( begin( _testData_[tt[t]] ), end( _testData_[tt[t]] ) );
		for ( int k( 0 ); k < 10; ++ k ) {
			yaal::random_shuffle( src.begin(), src.end() );
			for ( int i( 0 ); i < static_cast<int>( src.get_size() ); ++ i ) {
				int_array_t data( src );
				nth_element( data.begin(), data.begin() + i, data.end() );
				ENSURE_EQUALS( format( "nth_element %d failed", i ), data[i], _testData_[tt[t]][i] );
			}
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "stable_partition" )
	static int const range( 100 );
	int_array_t a( range );
	distribution::HDiscrete r( rng_helper::make_random_number_generator( range ) );
	for ( int_array_t::iterator it( a.begin() ), end( a.end() ); it != end; ++ it )
		*it = static_cast<int>( r() ) - range / 2;
	clog << a << endl;
	sort( a.begin(), a.end() );
	clog << a << endl;
	int_array_t::iterator m( stable_partition( a.begin(), a.end(), bind1st( less<int>(), 0 ) ) );
	clog << a << endl;
	for ( int_array_t::iterator it( a.begin() ); it != m; ++ it )
		ENSURE( "stable_partition failed (*it > 0)", *it > 0 );
	for ( int_array_t::iterator it( m ), end( a.end() ); it != end; ++ it )
		ENSURE( "stable_partition failed (*it <= 0)", *it <= 0 );
	ENSURE( "stable_partition failed (left is_sorted)", is_sorted( a.begin(), m ) );
	ENSURE( "stable_partition failed (right is_sorted)", is_sorted( m, a.end() ) );
	for ( int i( 0 ); i < ( range / 20 ); ++ i ) {
		generate( a.begin() + i * 20, a.begin() + i * 20 + 10, inc( -49 + i * 10 ) );
		generate( a.begin() + i * 20 + 10, a.begin() + i * 20 + 20, inc( i * 10 + 1 ) );
	}
	clog << a << endl;
	m = stable_partition( a.begin(), a.end(), bind1st( less<int>(), 0 ) );
	clog << a << endl;
	for ( int_array_t::iterator it( a.begin() ); it != m; ++ it )
		ENSURE( "stable_partition failed (*it > 0)", *it > 0 );
	for ( int_array_t::iterator it( m ), end( a.end() ); it != end; ++ it )
		ENSURE( "stable_partition failed (*it <= 0)", *it <= 0 );
	ENSURE( "stable_partition failed (left is_sorted)", is_sorted( a.begin(), m ) );
	ENSURE( "stable_partition failed (right is_sorted)", is_sorted( m, a.end() ) );
TUT_TEARDOWN()

struct IncGen {
	int _n;
	int _lim;
	IncGen( int n, int lim )
		: _n( n )
		, _lim( lim ) {
	}
	int operator()( void ) {
		int lim( static_cast<int>( _lim - 1 ) );
		int val( _n < lim ? _n : lim );
		++ _n;
		-- _lim;
		return ( val );
	}
};

TUT_UNIT_TEST( "random_shuffle" )
	static int const range( 100 );
	int_array_t a( range );
	yaal::generate( a.begin(), a.end(), inc( 1 ) );
	int_array_t b( a );
	random_shuffle( a.begin(), a.end() );
	ENSURE_NOT( "Probability of every element staying in its original position after random shuffle is N! which for this test is 100!, go play a lottery",  a == b );
	clog << a << endl;
	sort( a.begin(), a.end() );
	ENSURE_EQUALS( "random_shuffle lost some elements!", a, b );
	random_shuffle( a.begin(), a.end(), IncGen( 0, range ) );
	clog << a << endl;
	yaal::reverse( a.begin(), a.end() );
	ENSURE_EQUALS( "random_shuffle did not use given randomizer properly", a, b );
TUT_TEARDOWN()

TUT_UNIT_TEST( "random_sample" )
	static int const range( 1024 );
	int_array_t a( range );
	yaal::generate( a.begin(), a.end(), inc( 1 ) );
	int_array_t b( range / 2, -1 );
	int loTotal( 0 );
	static int const tries( 256 );
	HRandomNumberGenerator rng;
	for ( int t( 0 ); t < tries; ++ t ) {
		rng.set_seed( static_cast<u64_t>( t ) );
		random_sample( a.begin(), a.end(), b.begin(), b.end(), rng );
		int lo( static_cast<int>( count_if( b.begin(), b.end(), bind1st( less<int>(), range / 2 ) ) ) );
		loTotal += lo;
	}
	int loAverage( loTotal / tries );
	clog << loAverage << endl;
	ENSURE_DISTANCE( "random sample not uniformly random", loAverage, tries, 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "min" )
	ENSURE_EQUALS( "min failed", yaal::min( 31, 13, 2, 7, 5 ), 2 );
	ENSURE_EQUALS( "min failed", yaal::min({ 31, 13, 2, 7, 5 }), 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "max" )
	ENSURE_EQUALS( "max failed", yaal::max( 2, 13, 2, 31, 7, 5 ), 31 );
	ENSURE_EQUALS( "max failed", yaal::max({ 2, 13, 2, 31, 7, 5 }), 31 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_intersection" )
	int_array_t a( { 1, 3, 5, 7, 9, 11, 13, 15, 17 } );
	int_array_t b( { 0, 2, 4, 6, 8, 10, 12, 14, 16 } );
	int_array_t c( { 0, 2, 4, 5, 6, 8, 9, 10, 12, 14, 16 } );
	int_array_t e;
	int_array_t s;
	set_intersection( a.begin(), a.end(), b.begin(), b.end(), back_insert_iterator<int_array_t>( e ) );
	ENSURE( "set_intersection failed", e.is_empty() );
	set_intersection( a.begin(), a.end(), c.begin(), c.end(), back_insert_iterator<int_array_t>( s ) );
	ENSURE_EQUALS( "set_intersection failed", s, int_array_t( { 5, 9 } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "does_intersect" )
	int_array_t a( { 1, 3, 5, 7, 9 } );
	int_array_t b( { 0, 2, 4, 6, 8 } );
	int_array_t c( { 0, 2, 4, 5, 6, 8 } );
	ENSURE_NOT( "does_intersect failed", does_intersect( a.begin(), a.end(), b.begin(), b.end() ) );
	ENSURE( "does_intersect failed", does_intersect( a.begin(), a.end(), c.begin(), c.end() ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "sort speed" )
	TIME_CONSTRAINT_EXEMPT();
	double long st( 0 );
	double long yt( 0 );
	int_array_t a( 100000 ); {
		yaal::generate( a.begin(), a.end(), HRandomNumberGenerator( 0 ) );
		*a.rbegin() = -1;
		std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() ); {
			HClock c;
			std::stable_sort( v.begin(), v.end() );
			clog << "*speed* std::stable_sort = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		} {
			HClock c;
			stable_sort( a.begin(), a.end() );
			clog << "*speed* yaal::stable_sort = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::stable_sort wrong", a, v );
		clog << "*speed* stable_sort result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl; {
			HClock c;
			std::stable_sort( v.begin(), v.end() );
			clog << "*speed* std::stable_sort (on sorted) = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		} {
			HClock c;
			stable_sort( a.begin(), a.end() );
			clog << "*speed* yaal::stable_sort (on sorted) = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::stable_sort (on sorted) wrong", a, v );
		clog << "*speed* stable_sort (on sorted) result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	} {
		yaal::generate( a.begin(), a.end(), HRandomNumberGenerator( 0 ) );
		*a.rbegin() = -1;
		std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() ); {
			HClock c;
			std::sort( v.begin(), v.end() );
			clog << "*speed* std::sort = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		} {
			HClock c;
			sort( a.begin(), a.end() );
			clog << "*speed* yaal::sort = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::sort wrong", a, v );
		clog << "*speed* sort result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl; {
			HClock c;
			std::sort( v.begin(), v.end() );
			clog << "*speed* std::sort (on sorted) = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		} {
			HClock c;
			sort( a.begin(), a.end() );
			clog << "*speed* yaal::sort (on sorted) = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::sort (on sorted) wrong", a, v );
		clog << "*speed* sort (on sorted) result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	} {
		yaal::generate( a.begin(), a.end(), HRandomNumberGenerator( 0 ) );
		*a.rbegin() = -1;
		std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() ); {
			HClock c;
			std::make_heap( v.begin(), v.end() );
			std::sort_heap( v.begin(), v.end() );
			clog << "*speed* std::heap_sort = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		} {
			HClock c;
			heap_sort( a.begin(), a.end() );
			clog << "*speed* yaal::heap_sort = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::heap_sort wrong", a, v );
		clog << "*speed* heap_sort result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl; {
			HClock c;
			std::make_heap( v.begin(), v.end() );
			std::sort_heap( v.begin(), v.end() );
			clog << "*speed* std::heap_sort (on sorted) = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		} {
			HClock c;
			heap_sort( a.begin(), a.end() );
			clog << "*speed* yaal::heap_sort (on sorted) = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::heap_sort (on sorted) wrong", a, v );
		clog << "*speed* heap_sort (on sorted) result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	}
TUT_TEARDOWN()

}

