/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::huginn;
using namespace yaal::tools::executing_parser;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_instructions_range : public tress::tut_yaal_tools_hhuginn_base {
	void test_range_suite( HHuginn::TYPE );
	void test_range( HHuginn::TYPE, char const*, char const* );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_instructions_range, "yaal::tools::HHuginn,instructions.range" );

void tut_yaal_tools_hhuginn_instructions_range::test_range( HHuginn::TYPE type_, char const* range_, char const* result_ ) {
	hcore::HString src;
	char const x[] = "('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z')";
	if ( type_ == HHuginn::TYPE::TUPLE ) {
		src.append( "import Text as T;import Algorithms as A;main(){return(T.join(A.materialize(A.map(" ).append( x ).append( "[" ).append( range_ ).append( "],string),list),\"\"));}" );
	} else if ( type_ == HHuginn::TYPE::STRING ) {
		src.append( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[" ).append( range_ ).append( "]);}" );
	} else {
		src.append( "import Text as t;apply(x,T){i=0;s=size(x);while(i<s){x[i]=T(x[i]);i+=1;}return(x);}main(){return(t.join(apply(" )
			.append( type_ == HHuginn::TYPE::LIST ? "list" : "deque" )
			.append( x )
			.append( "[" )
			.append( range_ )
			.append( "],string),\"\"));}" );
	}
	ENSURE_EQUALS( "range failed", execute( src ), to_string( '"' ).append( result_ ).append( '"' ) );
	return;
}

void tut_yaal_tools_hhuginn_instructions_range::test_range_suite( HHuginn::TYPE type_ ) {
	test_range( type_, ":", "abcdefghijklmnopqrstuvwxyz" );
	test_range( type_, ":0", "" );
	test_range( type_, "5:5", "" );
	test_range( type_, "5:4", "" );
	test_range( type_, ":1", "a" );
	test_range( type_, ":2", "ab" );
	test_range( type_, ":24", "abcdefghijklmnopqrstuvwx" );
	test_range( type_, ":25", "abcdefghijklmnopqrstuvwxy" );
	test_range( type_, ":26", "abcdefghijklmnopqrstuvwxyz" );
	test_range( type_, "0:", "abcdefghijklmnopqrstuvwxyz" );
	test_range( type_, "1:", "bcdefghijklmnopqrstuvwxyz" );
	test_range( type_, "2:", "cdefghijklmnopqrstuvwxyz" );
	test_range( type_, "24:", "yz" );
	test_range( type_, "25:", "z" );
	test_range( type_, "26:", "" );
	test_range( type_, "1:25", "bcdefghijklmnopqrstuvwxy" );
	test_range( type_, "2:24", "cdefghijklmnopqrstuvwx" );
	test_range( type_, "4:8", "efgh" );
	test_range( type_, ":-1", "abcdefghijklmnopqrstuvwxy" );
	test_range( type_, ":-10", "abcdefghijklmnop" );
	test_range( type_, ":-100", "" );
	test_range( type_, "-1:", "z" );
	test_range( type_, "-10:", "qrstuvwxyz" );
	test_range( type_, "-100:", "abcdefghijklmnopqrstuvwxyz" );
	test_range( type_, "-8:-4", "stuv" );
	test_range( type_, ":100", "abcdefghijklmnopqrstuvwxyz" );
	test_range( type_, "::", "abcdefghijklmnopqrstuvwxyz" );
	test_range( type_, "::2", "acegikmoqsuwy" );
	test_range( type_, "::13", "an" );
	test_range( type_, "::25", "az" );
	test_range( type_, "::26", "a" );
	test_range( type_, "::100", "a" );
	test_range( type_, "5:5:-1", "" );
	test_range( type_, "4:5:-1", "" );
	test_range( type_, "::-1", "zyxwvutsrqponmlkjihgfedcba" );
	test_range( type_, "::-2", "zxvtrpnljhfdb" );
	test_range( type_, "::-3", "zwtqnkheb" );
	test_range( type_, ":20:-1", "zyxwv" );
	test_range( type_, "-15:-3:2", "lnprtv" );
	test_range( type_, "-3:-15:-2", "xvtrpn" );
	test_range( type_, "10:-28:-1", "kjihgfedcba" );
	test_range( type_, "-4::-1", "wvutsrqponmlkjihgfedcba" );
	test_range( type_, "-4::", "wxyz" );
}

TUT_UNIT_TEST( "range(slice) [string]" )
	test_range_suite( HHuginn::TYPE::STRING );
TUT_TEARDOWN()

TUT_UNIT_TEST( "range(slice) [tuple]" )
	test_range_suite( HHuginn::TYPE::TUPLE );
TUT_TEARDOWN()

TUT_UNIT_TEST( "range(slice) [list]" )
	test_range_suite( HHuginn::TYPE::LIST );
TUT_TEARDOWN()

TUT_UNIT_TEST( "range(slice) [deque]" )
	test_range_suite( HHuginn::TYPE::DEQUE );
TUT_TEARDOWN()

}

