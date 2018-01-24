/* Read tress/LICENSE.md file for copyright and licensing information. */

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

