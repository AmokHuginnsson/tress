/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/htuple.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/htime.hxx>
#include <yaal/tools/streamtools.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_htuple );
TUT_TEST_GROUP( tut_yaal_hcore_htuple, "yaal::hcore::HTuple" );

TUT_UNIT_TEST( "constructor" )
	typedef HTuple<int, HString, HNumber, void*, HTime> tuple_t;
	tuple_t t( 7, "Ala ma kota", 3.141592653589793, NULL, HTime::TZ::LOCAL );
	ENSURE_EQUALS( "tuple val[0] failed", t.get<0>(), 7 );
	ENSURE_EQUALS( "tuple val[1] failed", t.get<1>(), "Ala ma kota" );
	ENSURE_EQUALS( "tuple val[2] failed", t.get<2>(), 3.141592653589793 );
	ENSURE_EQUALS( "tuple val[3] failed", t.get<3>(), static_cast<void*>( NULL ) );
	ENSURE_EQUALS( "tuple val[4] failed", t.get<4>(), HTime::TZ::LOCAL );
TUT_TEARDOWN()

TUT_UNIT_TEST( "make_tuple" )
	typedef HTuple<int, HString, HNumber, void*, HTime> tuple_t;
	tuple_t t( make_tuple<int, HString, HNumber, void*, HTime>( 7, "Ala ma kota", 3.141592653589793, NULL, HTime::TZ::LOCAL ) );
	ENSURE_EQUALS( "tuple val[0] failed", t.get<0>(), 7 );
	ENSURE_EQUALS( "tuple val[1] failed", t.get<1>(), "Ala ma kota" );
	ENSURE_EQUALS( "tuple val[2] failed", t.get<2>(), 3.141592653589793 );
	ENSURE_EQUALS( "tuple val[3] failed", t.get<3>(), static_cast<void*>( NULL ) );
	ENSURE_EQUALS( "tuple val[4] failed", t.get<4>(), HTime::TZ::LOCAL );
TUT_TEARDOWN()

}

