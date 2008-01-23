/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <boost/bind.hpp>

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

using namespace tut;
using namespace tut_helpers;
using namespace std;
using namespace boost;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal
	{
	};

typedef test_group<tut_yaal> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_group( "yaal" );

/* abstract call */

struct ci
	{
	struct dummy{};
	virtual ~ci() {}
	virtual void invoke( void ) = 0;
	};

template<typename c_t, typename m_t,
	typename a1t = ci::dummy, typename a2t = ci::dummy>
struct call : public ci
	{
	c_t _obj;
	m_t M;
	a1t _a1;
	a2t _a2;
	call( c_t obj, m_t m, a1t a1 = a1t(), a2t a2 = a2t() )
		: _obj( obj ), M( m ), _a1( a1 ), _a2( a2 ) {}
	void invoke( a1t const*, a2t const* )
		{ (_obj.*M)( _a1, _a2 ); }
	void invoke( a1t const*, ci::dummy* )
		{ (_obj.*M)( _a1 ); }
	void invoke( ci::dummy*, ci::dummy* )
		{ (_obj.*M)(); }
	virtual void invoke( void )
		{ invoke( static_cast<a1t*>( NULL ), static_cast<a2t*>( NULL ) ); }
	};

struct prod
	{
	void foo()
		{ cout << __PRETTY_FUNCTION__ << endl; }
	void bar( int a1 )
		{ cout << __PRETTY_FUNCTION__ << ": " << a1 << endl; }
	void baz( int a1, int a2 )
		{ cout << __PRETTY_FUNCTION__ << ": " << a1 << ", " << a2 << endl; }
	};

template<>
template<>
void module::test<1>( void )
	{
	prod p;
	call<prod&, typeof( &prod::foo )> c0( p, &prod::foo );
	c0.invoke();
	call<prod&, typeof( &prod::bar ), int> c1( p, &prod::bar, 3 );
	c1.invoke();
	call<prod&, typeof( &prod::baz ), int, int> c2( p, &prod::baz, 11, -7 );
	c2.invoke();
	}

}

