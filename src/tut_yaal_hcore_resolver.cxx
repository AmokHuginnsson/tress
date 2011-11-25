/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_resolver.cxx - this file is integral part of `tress' project.

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

#include <arpa/inet.h>

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

std::ostream& operator << ( std::ostream& stream, ip_t const& ip_ ) {
	stream << resolver::ip_to_string( ip_ );
	return ( stream );
}

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_resolver );
TUT_TEST_GROUP( tut_yaal_hcore_resolver, "yaal::hcore::resolver" );

TUT_UNIT_TEST( 1, "get_ip" )
	ENSURE_EQUALS( "get_ip filed", resolver::get_ip( "localhost" ), HIP( 127, 0, 0, 1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "ip_to_string" )
	ENSURE_EQUALS( "ip_to_string failure", resolver::ip_to_string( HIP( 127, 0, 0, 1 ) ), "127.0.0.1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "get_name" )
	ENSURE_EQUALS( "get_name failure", resolver::get_name( HIP( 127, 0, 0, 1 ) ), "localhost" );
TUT_TEARDOWN()

}

