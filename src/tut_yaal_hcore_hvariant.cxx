/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hvariant.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hvariant
	{
	typedef HVariant<int, HString, double long> small_variant_t;
	typedef HVariant<bool, char, int short, int, int long, void*, double, double long, HString> variant_t;
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_hvariant, "yaal::hcore::HVariant" );

TUT_UNIT_TEST_N( 1, "PoC of HVariant<>" )
	variant_t v = HString( "ala ma kota" );
	cout << "\"" << v.get<HString>() << "\" of type: " << v.type() << endl;
	cout << "sizeof ( variant_t ): " << sizeof ( v ) << endl;
	cout << "sizeof ( HString ): " << sizeof ( HString ) << endl;
	cout << "sizeof ( double long ): " << sizeof ( double long ) << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "uninitialized HVariant<>" )
	variant_t v;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "copy of uninitialized HVariant<>" )
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

}

