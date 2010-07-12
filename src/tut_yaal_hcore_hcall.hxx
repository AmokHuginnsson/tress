/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcall.cxx - this file is integral part of `tress' project.

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

#ifndef TUT_YAAL_HCORE_HCALL_HXX_INCLUDED
#define TUT_YAAL_HCORE_HCALL_HXX_INCLUDED 1

#include <yaal/hcore/hstring.hxx>

namespace tut
{

#define TUT_YAAL_HCORE_HCALL_CALLABLE \
yaal::hcore::HString foo0( void ); \
yaal::hcore::HString foo1( int a1 ); \
yaal::hcore::HString foo2( int a1, int a2 ); \
yaal::hcore::HString foo3( int a1, int a2, int a3 ); \
yaal::hcore::HString foo4( int a1, int a2, int a3, int a4 ); \
yaal::hcore::HString foo5( int a1, int a2, int a3, int a4, int a5 ); \
yaal::hcore::HString foo6( int a1, int a2, int a3, int a4, int a5, int a6 ); \
yaal::hcore::HString foo7( int a1, int a2, int a3, int a4, int a5, int a6, int a7 ); \
yaal::hcore::HString foo8( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8 ); \
yaal::hcore::HString foo9( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9 ); \
yaal::hcore::HString foo10( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10 );

TUT_YAAL_HCORE_HCALL_CALLABLE

class YaalHCoreHCallClass
	{
public:
	YaalHCoreHCallClass( void );
	YaalHCoreHCallClass( YaalHCoreHCallClass const& );
	virtual ~YaalHCoreHCallClass( void );
	TUT_YAAL_HCORE_HCALL_CALLABLE
	};

}

#endif /* not TUT_YAAL_HCORE_HCALL_HXX_INCLUDED */

