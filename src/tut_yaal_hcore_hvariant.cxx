/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hvariant.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hvariant.hxx>
#include <yaal/hcore/htaggedpod.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/hcore/hnumber.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hvariant : public simple_mock<tut_yaal_hcore_hvariant> {
	typedef simple_mock<tut_yaal_hcore_hvariant> base_type;
	typedef HInstanceTracker<tut_yaal_hcore_hvariant> instance_tracker_t;
	typedef HVariant<int, HString, double long> small_variant_t;
	typedef HVariant<bool, char, int short, int, int long, void*, double, double long, HString, HNumber, instance_tracker_t> variant_t;
	typedef HTaggedPOD<int, struct Type0> type0_t;
	typedef HTaggedPOD<int, struct Type1> type1_t;
	typedef HTaggedPOD<int, struct Type2> type2_t;
	typedef HTaggedPOD<int, struct Type3> type3_t;
	typedef HTaggedPOD<int, struct Type4> type4_t;
	typedef HTaggedPOD<int, struct Type5> type5_t;
	typedef HTaggedPOD<int, struct Type6> type6_t;
	typedef HTaggedPOD<int, struct Type7> type7_t;
	typedef HTaggedPOD<int, struct Type8> type8_t;
	typedef HTaggedPOD<int, struct Type9> type9_t;
	typedef HTaggedPOD<int, struct Type10> type10_t;
	typedef HTaggedPOD<int, struct Type11> type11_t;
	typedef HTaggedPOD<int, struct Type12> type12_t;
	typedef HTaggedPOD<int, struct Type13> type13_t;
	typedef HTaggedPOD<int, struct Type14> type14_t;
	typedef HTaggedPOD<int, struct Type15> type15_t;
	typedef HTaggedPOD<int, struct Type16> type16_t;
	typedef HTaggedPOD<int, struct Type17> type17_t;
	typedef HTaggedPOD<int, struct Type18> type18_t;
	typedef HTaggedPOD<int, struct Type19> type19_t;
	typedef HTaggedPOD<int, struct Type20> type20_t;
	typedef HVariant<
		type0_t, type1_t, type2_t, type3_t, type4_t,
		type5_t, type6_t, type7_t, type8_t, type9_t,
		type10_t, type11_t, type12_t, type13_t, type14_t,
		type15_t, type16_t, type17_t, type18_t, type19_t,
		type20_t
	> variant_type_t;
	static type0_t const c0;
	static type1_t const c1;
	static type2_t const c2;
	static type3_t const c3;
	static type4_t const c4;
	static type5_t const c5;
	static type6_t const c6;
	static type7_t const c7;
	static type8_t const c8;
	static type9_t const c9;
	static type10_t const c10;
	static type11_t const c11;
	static type12_t const c12;
	static type13_t const c13;
	static type14_t const c14;
	static type15_t const c15;
	static type16_t const c16;
	static type17_t const c17;
	static type18_t const c18;
	static type19_t const c19;
	static type20_t const c20;
	virtual ~tut_yaal_hcore_hvariant( void )
		{}
};

tut_yaal_hcore_hvariant::type0_t const tut_yaal_hcore_hvariant::c0( 0 );
tut_yaal_hcore_hvariant::type1_t const tut_yaal_hcore_hvariant::c1( 1 );
tut_yaal_hcore_hvariant::type2_t const tut_yaal_hcore_hvariant::c2( 2 );
tut_yaal_hcore_hvariant::type3_t const tut_yaal_hcore_hvariant::c3( 3 );
tut_yaal_hcore_hvariant::type4_t const tut_yaal_hcore_hvariant::c4( 4 );
tut_yaal_hcore_hvariant::type5_t const tut_yaal_hcore_hvariant::c5( 5 );
tut_yaal_hcore_hvariant::type6_t const tut_yaal_hcore_hvariant::c6( 6 );
tut_yaal_hcore_hvariant::type7_t const tut_yaal_hcore_hvariant::c7( 7 );
tut_yaal_hcore_hvariant::type8_t const tut_yaal_hcore_hvariant::c8( 8 );
tut_yaal_hcore_hvariant::type9_t const tut_yaal_hcore_hvariant::c9( 9 );
tut_yaal_hcore_hvariant::type10_t const tut_yaal_hcore_hvariant::c10( 10 );
tut_yaal_hcore_hvariant::type11_t const tut_yaal_hcore_hvariant::c11( 11 );
tut_yaal_hcore_hvariant::type12_t const tut_yaal_hcore_hvariant::c12( 12 );
tut_yaal_hcore_hvariant::type13_t const tut_yaal_hcore_hvariant::c13( 13 );
tut_yaal_hcore_hvariant::type14_t const tut_yaal_hcore_hvariant::c14( 14 );
tut_yaal_hcore_hvariant::type15_t const tut_yaal_hcore_hvariant::c15( 15 );
tut_yaal_hcore_hvariant::type16_t const tut_yaal_hcore_hvariant::c16( 16 );
tut_yaal_hcore_hvariant::type17_t const tut_yaal_hcore_hvariant::c17( 17 );
tut_yaal_hcore_hvariant::type18_t const tut_yaal_hcore_hvariant::c18( 18 );
tut_yaal_hcore_hvariant::type19_t const tut_yaal_hcore_hvariant::c19( 19 );
tut_yaal_hcore_hvariant::type20_t const tut_yaal_hcore_hvariant::c20( 20 );

TUT_TEST_GROUP( tut_yaal_hcore_hvariant, "yaal::hcore::HVariant" );

TUT_UNIT_TEST( "PoC of HVariant<>" )
	variant_t v( "ala ma kota"_ys );
	clog << "\"" << v.get<HString>() << "\" of type: " << v.type() << endl;
	clog << "sizeof ( variant_t ): " << sizeof ( v ) << endl;
	clog << "sizeof ( HString ): " << sizeof ( HString ) << endl;
	clog << "sizeof ( HNumber ): " << sizeof ( HNumber ) << endl;
	clog << "sizeof ( double long ): " << sizeof ( double long ) << endl;
	clog << "sizeof ( instance_tracker_t ): " << sizeof ( instance_tracker_t ) << endl;
	ENSURE_GREATER_OR_EQUAL( "bad variant size", sizeof ( v ), max( sizeof ( HString ), sizeof( HNumber ), sizeof ( double long ), sizeof ( instance_tracker_t ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "uninitialized HVariant<>" )
	variant_t v;
	ENSURE_THROW( "getting data from uninitialized variant", v.get<bool>(),               HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<char>(),               HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<int short>(),          HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<int>(),                HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<int long>(),           HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<void*>(),              HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<double>(),             HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<double long>(),        HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<HString>(),            HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<HNumber>(),            HFailedAssertion );
	ENSURE_THROW( "getting data from uninitialized variant", v.get<instance_tracker_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad type id on uninitialized", v.type(), variant_t::INVALID + 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy of uninitialized HVariant<>" )
	variant_t v;
	variant_t w = v;
	variant_t x;
	variant_t const z;
	x = v;
	x = z;
	variant_t t = v;
	variant_t u( z );
	variant_t const& rz = z;
	variant_t tmp( rz );
TUT_TEARDOWN()

TUT_UNIT_TEST( "consistency on assign (same types)" )
	variant_t v( instance_tracker_t( 1 ) );
	variant_t w( instance_tracker_t( 2 ) );
	w = v;
	ENSURE( "inconsistent bits after assign", w.get<instance_tracker_t>().is_self() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "consistency on assign (different types)" )
	variant_t v( instance_tracker_t( 1 ) );
	variant_t w( 1 );
	w = v;
	ENSURE( "inconsistent bits after assign", w.get<instance_tracker_t>().is_self() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "identity switches" )
	variant_t v;
	v = variant_t( true );
	ENSURE_EQUALS( "bad value (bool)", v.get<bool>(), true );
	v = variant_t( 1 );
	ENSURE_THROW( "getting data from variant ny wrong type", v.get<bool>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value (int)", v.get<int>(), 1 );
	v = variant_t( 3.141592653589793L );
	ENSURE_THROW( "getting data from variant ny wrong type", v.get<int>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value (double long)", v.get<double long>(), 3.141592653589793L );
	v = variant_t( "Ala ma kota. A very long string."_ys );
	ENSURE_THROW( "getting data from variant ny wrong type", v.get<double long>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value (HString)", v.get<HString>(), HString( "Ala ma kota. A very long string." ) );
	v = variant_t( "2.1718281828459045"_yn );
	ENSURE_THROW( "getting data from variant ny wrong type", v.get<HString>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value (HNumber)", v.get<HNumber>(), HNumber( "2.1718281828459045" ) );
	v = variant_t( false );
	ENSURE_THROW( "getting data from variant ny wrong type", v.get<HNumber>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value (bool)", v.get<bool>(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Copy ctor/swap/move" )
	/* 0 */
	variant_type_t const v0s( c0 );
	variant_type_t v0d( v0s );
	variant_type_t v0d2( -c0 );
	ENSURE_EQUALS( "bad type s0", v0s.type(), 0 );
	ENSURE_EQUALS( "bad type d0", v0d.type(), 0 );
	ENSURE_EQUALS( "bad type d2_0", v0d2.type(), 0 );
	ENSURE_EQUALS( "bad value s0", v0s.get<type0_t>(), 0 );
	ENSURE_EQUALS( "bad value d0", v0d.get<type0_t>(), 0 );
	ENSURE_EQUALS( "bad value d2_0", v0d2.get<type0_t>(), 0 );
	/* 1 */
	variant_type_t const v1s( c1 );
	variant_type_t v1d( v1s );
	variant_type_t v1d2( -c1 );
	ENSURE_EQUALS( "bad type s1", v1s.type(), 1 );
	ENSURE_EQUALS( "bad type d1", v1d.type(), 1 );
	ENSURE_EQUALS( "bad type d2_1", v1d2.type(), 1 );
	ENSURE_EQUALS( "bad value s1", v1s.get<type1_t>(), 1 );
	ENSURE_EQUALS( "bad value d1", v1d.get<type1_t>(), 1 );
	ENSURE_EQUALS( "bad value d2_1", v1d2.get<type1_t>(), -1 );
	/* 2 */
	variant_type_t const v2s( c2 );
	variant_type_t v2d( v2s );
	variant_type_t v2d2( -c2 );
	ENSURE_EQUALS( "bad type s2", v2s.type(), 2 );
	ENSURE_EQUALS( "bad type d2", v2d.type(), 2 );
	ENSURE_EQUALS( "bad type d2_2", v2d2.type(), 2 );
	ENSURE_EQUALS( "bad value s2", v2s.get<type2_t>(), 2 );
	ENSURE_EQUALS( "bad value d2", v2d.get<type2_t>(), 2 );
	ENSURE_EQUALS( "bad value d2_2", v2d2.get<type2_t>(), -2 );
	/* 3 */
	variant_type_t const v3s( c3 );
	variant_type_t v3d( v3s );
	variant_type_t v3d2( -c3 );
	ENSURE_EQUALS( "bad type s3", v3s.type(), 3 );
	ENSURE_EQUALS( "bad type d3", v3d.type(), 3 );
	ENSURE_EQUALS( "bad type d2_3", v3d2.type(), 3 );
	ENSURE_EQUALS( "bad value s3", v3s.get<type3_t>(), 3 );
	ENSURE_EQUALS( "bad value d3", v3d.get<type3_t>(), 3 );
	ENSURE_EQUALS( "bad value d2_3", v3d2.get<type3_t>(), -3 );
	/* 4 */
	variant_type_t const v4s( c4 );
	variant_type_t v4d( v4s );
	variant_type_t v4d2( -c4 );
	ENSURE_EQUALS( "bad type s4", v4s.type(), 4 );
	ENSURE_EQUALS( "bad type d4", v4d.type(), 4 );
	ENSURE_EQUALS( "bad type d2_4", v4d2.type(), 4 );
	ENSURE_EQUALS( "bad value s4", v4s.get<type4_t>(), 4 );
	ENSURE_EQUALS( "bad value d4", v4d.get<type4_t>(), 4 );
	ENSURE_EQUALS( "bad value d2_4", v4d2.get<type4_t>(), -4 );
	/* 5 */
	variant_type_t const v5s( c5 );
	variant_type_t v5d( v5s );
	variant_type_t v5d2( -c5 );
	ENSURE_EQUALS( "bad type s5", v5s.type(), 5 );
	ENSURE_EQUALS( "bad type d5", v5d.type(), 5 );
	ENSURE_EQUALS( "bad type d2_5", v5d2.type(), 5 );
	ENSURE_EQUALS( "bad value s5", v5s.get<type5_t>(), 5 );
	ENSURE_EQUALS( "bad value d5", v5d.get<type5_t>(), 5 );
	ENSURE_EQUALS( "bad value d2_5", v5d2.get<type5_t>(), -5 );
	/* 6 */
	variant_type_t const v6s( c6 );
	variant_type_t v6d( v6s );
	variant_type_t v6d2( -c6 );
	ENSURE_EQUALS( "bad type s6", v6s.type(), 6 );
	ENSURE_EQUALS( "bad type d6", v6d.type(), 6 );
	ENSURE_EQUALS( "bad type d2_6", v6d2.type(), 6 );
	ENSURE_EQUALS( "bad value s6", v6s.get<type6_t>(), 6 );
	ENSURE_EQUALS( "bad value d6", v6d.get<type6_t>(), 6 );
	ENSURE_EQUALS( "bad value d2_6", v6d2.get<type6_t>(), -6 );
	/* 7 */
	variant_type_t const v7s( c7 );
	variant_type_t v7d( v7s );
	variant_type_t v7d2( -c7 );
	ENSURE_EQUALS( "bad type s7", v7s.type(), 7 );
	ENSURE_EQUALS( "bad type d7", v7d.type(), 7 );
	ENSURE_EQUALS( "bad type d2_7", v7d2.type(), 7 );
	ENSURE_EQUALS( "bad value s7", v7s.get<type7_t>(), 7 );
	ENSURE_EQUALS( "bad value d7", v7d.get<type7_t>(), 7 );
	ENSURE_EQUALS( "bad value d2_7", v7d2.get<type7_t>(), -7 );
	/* 8 */
	variant_type_t const v8s( c8 );
	variant_type_t v8d( v8s );
	variant_type_t v8d2( -c8 );
	ENSURE_EQUALS( "bad type s8", v8s.type(), 8 );
	ENSURE_EQUALS( "bad type d8", v8d.type(), 8 );
	ENSURE_EQUALS( "bad type d2_8", v8d2.type(), 8 );
	ENSURE_EQUALS( "bad value s8", v8s.get<type8_t>(), 8 );
	ENSURE_EQUALS( "bad value d8", v8d.get<type8_t>(), 8 );
	ENSURE_EQUALS( "bad value d2_8", v8d2.get<type8_t>(), -8 );
	/* 9 */
	variant_type_t const v9s( c9 );
	variant_type_t v9d( v9s );
	variant_type_t v9d2( -c9 );
	ENSURE_EQUALS( "bad type s9", v9s.type(), 9 );
	ENSURE_EQUALS( "bad type d9", v9d.type(), 9 );
	ENSURE_EQUALS( "bad type d2_9", v9d2.type(), 9 );
	ENSURE_EQUALS( "bad value s9", v9s.get<type9_t>(), 9 );
	ENSURE_EQUALS( "bad value d9", v9d.get<type9_t>(), 9 );
	ENSURE_EQUALS( "bad value d2_9", v9d2.get<type9_t>(), -9 );
	/* 10 */
	variant_type_t const v10s( c10 );
	variant_type_t v10d( v10s );
	variant_type_t v10d2( -c10 );
	ENSURE_EQUALS( "bad type s10", v10s.type(), 10 );
	ENSURE_EQUALS( "bad type d10", v10d.type(), 10 );
	ENSURE_EQUALS( "bad type d2_10", v10d2.type(), 10 );
	ENSURE_EQUALS( "bad value s10", v10s.get<type10_t>(), 10 );
	ENSURE_EQUALS( "bad value d10", v10d.get<type10_t>(), 10 );
	ENSURE_EQUALS( "bad value d2_10", v10d2.get<type10_t>(), -10 );
	/* 11 */
	variant_type_t const v11s( c11 );
	variant_type_t v11d( v11s );
	variant_type_t v11d2( -c11 );
	ENSURE_EQUALS( "bad type s11", v11s.type(), 11 );
	ENSURE_EQUALS( "bad type d11", v11d.type(), 11 );
	ENSURE_EQUALS( "bad type d2_11", v11d2.type(), 11 );
	ENSURE_EQUALS( "bad value s11", v11s.get<type11_t>(), 11 );
	ENSURE_EQUALS( "bad value d11", v11d.get<type11_t>(), 11 );
	ENSURE_EQUALS( "bad value d2_11", v11d2.get<type11_t>(), -11 );
	/* 12 */
	variant_type_t const v12s( c12 );
	variant_type_t v12d( v12s );
	variant_type_t v12d2( -c12 );
	ENSURE_EQUALS( "bad type s12", v12s.type(), 12 );
	ENSURE_EQUALS( "bad type d12", v12d.type(), 12 );
	ENSURE_EQUALS( "bad type d2_12", v12d2.type(), 12 );
	ENSURE_EQUALS( "bad value s12", v12s.get<type12_t>(), 12 );
	ENSURE_EQUALS( "bad value d12", v12d.get<type12_t>(), 12 );
	ENSURE_EQUALS( "bad value d2_12", v12d2.get<type12_t>(), -12 );
	/* 13 */
	variant_type_t const v13s( c13 );
	variant_type_t v13d( v13s );
	variant_type_t v13d2( -c13 );
	ENSURE_EQUALS( "bad type s13", v13s.type(), 13 );
	ENSURE_EQUALS( "bad type d13", v13d.type(), 13 );
	ENSURE_EQUALS( "bad type d2_13", v13d2.type(), 13 );
	ENSURE_EQUALS( "bad value s13", v13s.get<type13_t>(), 13 );
	ENSURE_EQUALS( "bad value d13", v13d.get<type13_t>(), 13 );
	ENSURE_EQUALS( "bad value d2_13", v13d2.get<type13_t>(), -13 );
	/* 14 */
	variant_type_t const v14s( c14 );
	variant_type_t v14d( v14s );
	variant_type_t v14d2( -c14 );
	ENSURE_EQUALS( "bad type s14", v14s.type(), 14 );
	ENSURE_EQUALS( "bad type d14", v14d.type(), 14 );
	ENSURE_EQUALS( "bad type d2_14", v14d2.type(), 14 );
	ENSURE_EQUALS( "bad value s14", v14s.get<type14_t>(), 14 );
	ENSURE_EQUALS( "bad value d14", v14d.get<type14_t>(), 14 );
	ENSURE_EQUALS( "bad value d2_14", v14d2.get<type14_t>(), -14 );
	/* 15 */
	variant_type_t const v15s( c15 );
	variant_type_t v15d( v15s );
	variant_type_t v15d2( -c15 );
	ENSURE_EQUALS( "bad type s15", v15s.type(), 15 );
	ENSURE_EQUALS( "bad type d15", v15d.type(), 15 );
	ENSURE_EQUALS( "bad type d2_15", v15d2.type(), 15 );
	ENSURE_EQUALS( "bad value s15", v15s.get<type15_t>(), 15 );
	ENSURE_EQUALS( "bad value d15", v15d.get<type15_t>(), 15 );
	ENSURE_EQUALS( "bad value d2_15", v15d2.get<type15_t>(), -15 );
	/* 16 */
	variant_type_t const v16s( c16 );
	variant_type_t v16d( v16s );
	variant_type_t v16d2( -c16 );
	ENSURE_EQUALS( "bad type s16", v16s.type(), 16 );
	ENSURE_EQUALS( "bad type d16", v16d.type(), 16 );
	ENSURE_EQUALS( "bad type d2_16", v16d2.type(), 16 );
	ENSURE_EQUALS( "bad value s16", v16s.get<type16_t>(), 16 );
	ENSURE_EQUALS( "bad value d16", v16d.get<type16_t>(), 16 );
	ENSURE_EQUALS( "bad value d2_16", v16d2.get<type16_t>(), -16 );
	/* 17 */
	variant_type_t const v17s( c17 );
	variant_type_t v17d( v17s );
	variant_type_t v17d2( -c17 );
	ENSURE_EQUALS( "bad type s17", v17s.type(), 17 );
	ENSURE_EQUALS( "bad type d17", v17d.type(), 17 );
	ENSURE_EQUALS( "bad type d2_17", v17d2.type(), 17 );
	ENSURE_EQUALS( "bad value s17", v17s.get<type17_t>(), 17 );
	ENSURE_EQUALS( "bad value d17", v17d.get<type17_t>(), 17 );
	ENSURE_EQUALS( "bad value d2_17", v17d2.get<type17_t>(), -17 );
	/* 18 */
	variant_type_t const v18s( c18 );
	variant_type_t v18d( v18s );
	variant_type_t v18d2( -c18 );
	ENSURE_EQUALS( "bad type s18", v18s.type(), 18 );
	ENSURE_EQUALS( "bad type d18", v18d.type(), 18 );
	ENSURE_EQUALS( "bad type d2_18", v18d2.type(), 18 );
	ENSURE_EQUALS( "bad value s18", v18s.get<type18_t>(), 18 );
	ENSURE_EQUALS( "bad value d18", v18d.get<type18_t>(), 18 );
	ENSURE_EQUALS( "bad value d2_18", v18d2.get<type18_t>(), -18 );
	/* 19 */
	variant_type_t const v19s( c19 );
	variant_type_t v19d( v19s );
	variant_type_t v19d2( -c19 );
	ENSURE_EQUALS( "bad type s19", v19s.type(), 19 );
	ENSURE_EQUALS( "bad type d19", v19d.type(), 19 );
	ENSURE_EQUALS( "bad type d2_19", v19d2.type(), 19 );
	ENSURE_EQUALS( "bad value s19", v19s.get<type19_t>(), 19 );
	ENSURE_EQUALS( "bad value d19", v19d.get<type19_t>(), 19 );
	ENSURE_EQUALS( "bad value d2_19", v19d2.get<type19_t>(), -19 );
	/* 20 */
	variant_type_t const v20s( c20 );
	variant_type_t v20d( v20s );
	variant_type_t v20d2( -c20 );
	ENSURE_EQUALS( "bad type s20", v20s.type(), 20 );
	ENSURE_EQUALS( "bad type d20", v20d.type(), 20 );
	ENSURE_EQUALS( "bad type d2_20", v20d2.type(), 20 );
	ENSURE_EQUALS( "bad value s20", v20s.get<type20_t>(), 20 );
	ENSURE_EQUALS( "bad value d20", v20d.get<type20_t>(), 20 );
	ENSURE_EQUALS( "bad value d2_20", v20d2.get<type20_t>(), -20 );
	/* swap */
	using yaal::swap;
	/* 1 */
	swap( v1d, v1d2 );
	ENSURE_EQUALS( "bad type d1", v1d.type(), 1 );
	ENSURE_EQUALS( "bad type d2_1", v1d2.type(), 1 );
	ENSURE_EQUALS( "bad value d1", v1d.get<type1_t>(), -1 );
	ENSURE_EQUALS( "bad value d2_1", v1d2.get<type1_t>(), 1 );
	/* 2 */
	swap( v2d, v2d2 );
	ENSURE_EQUALS( "bad type d2", v2d.type(), 2 );
	ENSURE_EQUALS( "bad type d2_2", v2d2.type(), 2 );
	ENSURE_EQUALS( "bad value d2", v2d.get<type2_t>(), -2 );
	ENSURE_EQUALS( "bad value d2_2", v2d2.get<type2_t>(), 2 );
	/* 3 */
	swap( v3d, v3d2 );
	ENSURE_EQUALS( "bad type d3", v3d.type(), 3 );
	ENSURE_EQUALS( "bad type d2_3", v3d2.type(), 3 );
	ENSURE_EQUALS( "bad value d3", v3d.get<type3_t>(), -3 );
	ENSURE_EQUALS( "bad value d2_3", v3d2.get<type3_t>(), 3 );
	/* 4 */
	swap( v4d, v4d2 );
	ENSURE_EQUALS( "bad type d4", v4d.type(), 4 );
	ENSURE_EQUALS( "bad type d2_4", v4d2.type(), 4 );
	ENSURE_EQUALS( "bad value d4", v4d.get<type4_t>(), -4 );
	ENSURE_EQUALS( "bad value d2_4", v4d2.get<type4_t>(), 4 );
	/* 5 */
	swap( v5d, v5d2 );
	ENSURE_EQUALS( "bad type d5", v5d.type(), 5 );
	ENSURE_EQUALS( "bad type d2_5", v5d2.type(), 5 );
	ENSURE_EQUALS( "bad value d5", v5d.get<type5_t>(), -5 );
	ENSURE_EQUALS( "bad value d2_5", v5d2.get<type5_t>(), 5 );
	/* 6 */
	swap( v6d, v6d2 );
	ENSURE_EQUALS( "bad type d6", v6d.type(), 6 );
	ENSURE_EQUALS( "bad type d2_6", v6d2.type(), 6 );
	ENSURE_EQUALS( "bad value d6", v6d.get<type6_t>(), -6 );
	ENSURE_EQUALS( "bad value d2_6", v6d2.get<type6_t>(), 6 );
	/* 7 */
	swap( v7d, v7d2 );
	ENSURE_EQUALS( "bad type d7", v7d.type(), 7 );
	ENSURE_EQUALS( "bad type d2_7", v7d2.type(), 7 );
	ENSURE_EQUALS( "bad value d7", v7d.get<type7_t>(), -7 );
	ENSURE_EQUALS( "bad value d2_7", v7d2.get<type7_t>(), 7 );
	/* 8 */
	swap( v8d, v8d2 );
	ENSURE_EQUALS( "bad type d8", v8d.type(), 8 );
	ENSURE_EQUALS( "bad type d2_8", v8d2.type(), 8 );
	ENSURE_EQUALS( "bad value d8", v8d.get<type8_t>(), -8 );
	ENSURE_EQUALS( "bad value d2_8", v8d2.get<type8_t>(), 8 );
	/* 9 */
	swap( v9d, v9d2 );
	ENSURE_EQUALS( "bad type d9", v9d.type(), 9 );
	ENSURE_EQUALS( "bad type d2_9", v9d2.type(), 9 );
	ENSURE_EQUALS( "bad value d9", v9d.get<type9_t>(), -9 );
	ENSURE_EQUALS( "bad value d2_9", v9d2.get<type9_t>(), 9 );
	/* 10 */
	swap( v10d, v10d2 );
	ENSURE_EQUALS( "bad type d10", v10d.type(), 10 );
	ENSURE_EQUALS( "bad type d2_10", v10d2.type(), 10 );
	ENSURE_EQUALS( "bad value d10", v10d.get<type10_t>(), -10 );
	ENSURE_EQUALS( "bad value d2_10", v10d2.get<type10_t>(), 10 );
	/* 11 */
	swap( v11d, v11d2 );
	ENSURE_EQUALS( "bad type d11", v11d.type(), 11 );
	ENSURE_EQUALS( "bad type d2_11", v11d2.type(), 11 );
	ENSURE_EQUALS( "bad value d11", v11d.get<type11_t>(), -11 );
	ENSURE_EQUALS( "bad value d2_11", v11d2.get<type11_t>(), 11 );
	/* 12 */
	swap( v12d, v12d2 );
	ENSURE_EQUALS( "bad type d12", v12d.type(), 12 );
	ENSURE_EQUALS( "bad type d2_12", v12d2.type(), 12 );
	ENSURE_EQUALS( "bad value d12", v12d.get<type12_t>(), -12 );
	ENSURE_EQUALS( "bad value d2_12", v12d2.get<type12_t>(), 12 );
	/* 13 */
	swap( v13d, v13d2 );
	ENSURE_EQUALS( "bad type d13", v13d.type(), 13 );
	ENSURE_EQUALS( "bad type d2_13", v13d2.type(), 13 );
	ENSURE_EQUALS( "bad value d13", v13d.get<type13_t>(), -13 );
	ENSURE_EQUALS( "bad value d2_13", v13d2.get<type13_t>(), 13 );
	/* 14 */
	swap( v14d, v14d2 );
	ENSURE_EQUALS( "bad type d14", v14d.type(), 14 );
	ENSURE_EQUALS( "bad type d2_14", v14d2.type(), 14 );
	ENSURE_EQUALS( "bad value d14", v14d.get<type14_t>(), -14 );
	ENSURE_EQUALS( "bad value d2_14", v14d2.get<type14_t>(), 14 );
	/* 15 */
	swap( v15d, v15d2 );
	ENSURE_EQUALS( "bad type d15", v15d.type(), 15 );
	ENSURE_EQUALS( "bad type d2_15", v15d2.type(), 15 );
	ENSURE_EQUALS( "bad value d15", v15d.get<type15_t>(), -15 );
	ENSURE_EQUALS( "bad value d2_15", v15d2.get<type15_t>(), 15 );
	/* 16 */
	swap( v16d, v16d2 );
	ENSURE_EQUALS( "bad type d16", v16d.type(), 16 );
	ENSURE_EQUALS( "bad type d2_16", v16d2.type(), 16 );
	ENSURE_EQUALS( "bad value d16", v16d.get<type16_t>(), -16 );
	ENSURE_EQUALS( "bad value d2_16", v16d2.get<type16_t>(), 16 );
	/* 17 */
	swap( v17d, v17d2 );
	ENSURE_EQUALS( "bad type d17", v17d.type(), 17 );
	ENSURE_EQUALS( "bad type d2_17", v17d2.type(), 17 );
	ENSURE_EQUALS( "bad value d17", v17d.get<type17_t>(), -17 );
	ENSURE_EQUALS( "bad value d2_17", v17d2.get<type17_t>(), 17 );
	/* 18 */
	swap( v18d, v18d2 );
	ENSURE_EQUALS( "bad type d18", v18d.type(), 18 );
	ENSURE_EQUALS( "bad type d2_18", v18d2.type(), 18 );
	ENSURE_EQUALS( "bad value d18", v18d.get<type18_t>(), -18 );
	ENSURE_EQUALS( "bad value d2_18", v18d2.get<type18_t>(), 18 );
	/* 19 */
	swap( v19d, v19d2 );
	ENSURE_EQUALS( "bad type d19", v19d.type(), 19 );
	ENSURE_EQUALS( "bad type d2_19", v19d2.type(), 19 );
	ENSURE_EQUALS( "bad value d19", v19d.get<type19_t>(), -19 );
	ENSURE_EQUALS( "bad value d2_19", v19d2.get<type19_t>(), 19 );
	/* 20 */
	swap( v20d, v20d2 );
	ENSURE_EQUALS( "bad type d20", v20d.type(), 20 );
	ENSURE_EQUALS( "bad type d2_20", v20d2.type(), 20 );
	ENSURE_EQUALS( "bad value d20", v20d.get<type20_t>(), -20 );
	ENSURE_EQUALS( "bad value d2_20", v20d2.get<type20_t>(), 20 );
	/* move */
	variant_type_t v;
	/* 0 */
	v = variant_type_t();
	swap( v0d, v );
	ENSURE_EQUALS( "bad type d0", v0d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 0 );
	ENSURE_THROW( "getting data from uninitialized variant", v0d.get<type0_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type0_t>(), 0 );
	/* 1 */
	v = variant_type_t();
	swap( v1d, v );
	ENSURE_EQUALS( "bad type d1", v1d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 1 );
	ENSURE_THROW( "getting data from uninitialized variant", v1d.get<type1_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type1_t>(), -1 );
	/* 2 */
	v = variant_type_t();
	swap( v2d, v );
	ENSURE_EQUALS( "bad type d2", v2d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 2 );
	ENSURE_THROW( "getting data from uninitialized variant", v2d.get<type2_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type2_t>(), -2 );
	/* 3 */
	v = variant_type_t();
	swap( v3d, v );
	ENSURE_EQUALS( "bad type d3", v3d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 3 );
	ENSURE_THROW( "getting data from uninitialized variant", v3d.get<type3_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type3_t>(), -3 );
	/* 4 */
	v = variant_type_t();
	swap( v4d, v );
	ENSURE_EQUALS( "bad type d4", v4d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 4 );
	ENSURE_THROW( "getting data from uninitialized variant", v4d.get<type4_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type4_t>(), -4 );
	/* 5 */
	v = variant_type_t();
	swap( v5d, v );
	ENSURE_EQUALS( "bad type d5", v5d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 5 );
	ENSURE_THROW( "getting data from uninitialized variant", v5d.get<type5_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type5_t>(), -5 );
	/* 6 */
	v = variant_type_t();
	swap( v6d, v );
	ENSURE_EQUALS( "bad type d6", v6d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 6 );
	ENSURE_THROW( "getting data from uninitialized variant", v6d.get<type6_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type6_t>(), -6 );
	/* 7 */
	v = variant_type_t();
	swap( v7d, v );
	ENSURE_EQUALS( "bad type d7", v7d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 7 );
	ENSURE_THROW( "getting data from uninitialized variant", v7d.get<type7_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type7_t>(), -7 );
	/* 8 */
	v = variant_type_t();
	swap( v8d, v );
	ENSURE_EQUALS( "bad type d8", v8d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 8 );
	ENSURE_THROW( "getting data from uninitialized variant", v8d.get<type8_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type8_t>(), -8 );
	/* 9 */
	v = variant_type_t();
	swap( v9d, v );
	ENSURE_EQUALS( "bad type d9", v9d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 9 );
	ENSURE_THROW( "getting data from uninitialized variant", v9d.get<type9_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type9_t>(), -9 );
	/* 10 */
	v = variant_type_t();
	swap( v10d, v );
	ENSURE_EQUALS( "bad type d10", v10d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 10 );
	ENSURE_THROW( "getting data from uninitialized variant", v10d.get<type10_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type10_t>(), -10 );
	/* 11 */
	v = variant_type_t();
	swap( v11d, v );
	ENSURE_EQUALS( "bad type d11", v11d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 11 );
	ENSURE_THROW( "getting data from uninitialized variant", v11d.get<type11_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type11_t>(), -11 );
	/* 12 */
	v = variant_type_t();
	swap( v12d, v );
	ENSURE_EQUALS( "bad type d12", v12d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 12 );
	ENSURE_THROW( "getting data from uninitialized variant", v12d.get<type12_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type12_t>(), -12 );
	/* 13 */
	v = variant_type_t();
	swap( v13d, v );
	ENSURE_EQUALS( "bad type d13", v13d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 13 );
	ENSURE_THROW( "getting data from uninitialized variant", v13d.get<type13_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type13_t>(), -13 );
	/* 14 */
	v = variant_type_t();
	swap( v14d, v );
	ENSURE_EQUALS( "bad type d14", v14d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 14 );
	ENSURE_THROW( "getting data from uninitialized variant", v14d.get<type14_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type14_t>(), -14 );
	/* 15 */
	v = variant_type_t();
	swap( v15d, v );
	ENSURE_EQUALS( "bad type d15", v15d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 15 );
	ENSURE_THROW( "getting data from uninitialized variant", v15d.get<type15_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type15_t>(), -15 );
	/* 16 */
	v = variant_type_t();
	swap( v16d, v );
	ENSURE_EQUALS( "bad type d16", v16d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 16 );
	ENSURE_THROW( "getting data from uninitialized variant", v16d.get<type16_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type16_t>(), -16 );
	/* 17 */
	v = variant_type_t();
	swap( v17d, v );
	ENSURE_EQUALS( "bad type d17", v17d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 17 );
	ENSURE_THROW( "getting data from uninitialized variant", v17d.get<type17_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type17_t>(), -17 );
	/* 18 */
	v = variant_type_t();
	swap( v18d, v );
	ENSURE_EQUALS( "bad type d18", v18d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 18 );
	ENSURE_THROW( "getting data from uninitialized variant", v18d.get<type18_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type18_t>(), -18 );
	/* 19 */
	v = variant_type_t();
	swap( v19d, v );
	ENSURE_EQUALS( "bad type d19", v19d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 19 );
	ENSURE_THROW( "getting data from uninitialized variant", v19d.get<type19_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type19_t>(), -19 );
	/* 20 */
	v = variant_type_t();
	swap( v20d, v );
	ENSURE_EQUALS( "bad type d20", v20d.type(), -1 );
	ENSURE_EQUALS( "bad type v", v.type(), 20 );
	ENSURE_THROW( "getting data from uninitialized variant", v20d.get<type20_t>(), HFailedAssertion );
	ENSURE_EQUALS( "bad value v", v.get<type20_t>(), -20 );
TUT_TEARDOWN()

}

