/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcall.hxx - this file is integral part of `tress' project.

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

#ifndef TUT_YAAL_HCORE_HCALL_HXX_INCLUDED
#define TUT_YAAL_HCORE_HCALL_HXX_INCLUDED 1

#include <yaal/hcore/hstring.hxx>

namespace tut {

#define TUT_YAAL_HCORE_HCALL_CALLABLE( c ) \
yaal::hcore::HString foo0( void ) c; \
yaal::hcore::HString foo1( int a1 ) c; \
yaal::hcore::HString foo2( int a1, int a2 ) c; \
yaal::hcore::HString foo3( int a1, int a2, int a3 ) c; \
yaal::hcore::HString foo4( int a1, int a2, int a3, int a4 ) c; \
yaal::hcore::HString foo5( int a1, int a2, int a3, int a4, int a5 ) c; \
yaal::hcore::HString foo6( int a1, int a2, int a3, int a4, int a5, int a6 ) c; \
yaal::hcore::HString foo7( int a1, int a2, int a3, int a4, int a5, int a6, int a7 ) c; \
yaal::hcore::HString foo8( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8 ) c; \
yaal::hcore::HString foo9( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9 ) c; \
yaal::hcore::HString foo10( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10 ) c;

TUT_YAAL_HCORE_HCALL_CALLABLE()

class YaalHCoreHCallClass {
public:
	YaalHCoreHCallClass( void );
	YaalHCoreHCallClass( YaalHCoreHCallClass const& );
	virtual ~YaalHCoreHCallClass( void );
	TUT_YAAL_HCORE_HCALL_CALLABLE( const )
};

}

#endif /* not TUT_YAAL_HCORE_HCALL_HXX_INCLUDED */

