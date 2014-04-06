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
	virtual ~tut_yaal_hcore_hvariant( void )
		{}
};

TUT_TEST_GROUP( tut_yaal_hcore_hvariant, "yaal::hcore::HVariant" );

TUT_UNIT_TEST( 1, "PoC of HVariant<>" )
	variant_t v = HString( "ala ma kota" );
	cout << "\"" << v.get<HString>() << "\" of type: " << v.type() << endl;
	cout << "sizeof ( variant_t ): " << sizeof ( v ) << endl;
	cout << "sizeof ( HString ): " << sizeof ( HString ) << endl;
	cout << "sizeof ( HNumber ): " << sizeof ( HNumber ) << endl;
	cout << "sizeof ( double long ): " << sizeof ( double long ) << endl;
	cout << "sizeof ( instance_tracker_t ): " << sizeof ( instance_tracker_t ) << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "uninitialized HVariant<>" )
	variant_t v;
	try { v.get<bool>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<char>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<int short>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<int>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<int long>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<void*>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<double>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<double long>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<HString>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<HNumber>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	try { v.get<instance_tracker_t>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	ENSURE_EQUALS( "bad type id on uninitialized", v.type(), variant_t::INVALID );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "copy of uninitialized HVariant<>" )
	variant_t v;
	variant_t w = v;
	variant_t x;
	variant_t const z;
	x = v;
	x = z;
	variant_t t( v );
	variant_t u( z );
	variant_t const& rz = z;
	variant_t tmp( rz );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "consistency on assign (same types)" )
	variant_t v = instance_tracker_t( 1 );
	variant_t w = instance_tracker_t( 2 );
	w = v;
	ENSURE( "inconsistent bits after assign", w.get<instance_tracker_t>().is_self() );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "consistency on assign (different types)" )
	variant_t v = instance_tracker_t( 1 );
	variant_t w = 1;
	w = v;
	ENSURE( "inconsistent bits after assign", w.get<instance_tracker_t>().is_self() );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "identity switches" )
	variant_t v;
	v = true;
	ENSURE_EQUALS( "bad value (bool)", v.get<bool>(), true );
	v = 1;
	try { v.get<bool>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	ENSURE_EQUALS( "bad value (int)", v.get<int>(), 1 );
	v = 3.141592653589793L;
	try { v.get<int>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	ENSURE_EQUALS( "bad value (double long)", v.get<double long>(), 3.141592653589793L );
	v = HString( "Ala ma kota." );
	try { v.get<double long>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	ENSURE_EQUALS( "bad value (HString)", v.get<HString>(), HString( "Ala ma kota." ) );
	v = HNumber( "2.1718281828459045" );
	try { v.get<HString>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	ENSURE_EQUALS( "bad value (HNumber)", v.get<HNumber>(), HNumber( "2.1718281828459045" ) );
	v = false;
	try { v.get<HNumber>(); fail( "getting data from uninitialized varaiant" ); } catch ( HFailedAssertion const& ) { /* ok */ }
	ENSURE_EQUALS( "bad value (bool)", v.get<bool>(), false );

TUT_TEARDOWN()

}

