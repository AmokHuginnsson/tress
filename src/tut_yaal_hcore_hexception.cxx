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

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID( "$Id: "__ID__" $" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hexception
	{

class A
	{
	typedef A self_t;
public:
	virtual void foo( int const& a ) const
		{ do_foo( a ); }
private:
	virtual void do_foo( int const& a ) const
		{
		if ( ! a )
			M_THROW( "bad arg A", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<A> AE;

class B : public A
	{
	typedef B self_t;
	typedef A hier_t;
	virtual void do_foo( int const& a ) const
		{
		if ( ! a )
			M_THROW( "bad arg B", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<B,AE> BE;

class C : public B
	{
	typedef C self_t;
	typedef B hier_t;
	virtual void do_foo( int const& a ) const
		{
		if ( ! a )
			M_THROW( "bad arg C", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<C,BE> CE;

class P
	{
	typedef P self_t;
public:
	virtual void foo( int const& a ) const
		{ do_foo( a ); }
private:
	virtual void do_foo( int const& a ) const
		{
		if ( ! a )
			M_THROW( "bad arg P", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<P> PE;

class Q : public P
	{
	typedef Q self_t;
	virtual void do_foo( int const& a ) const
		{
		if ( ! a )
			M_THROW( "bad arg Q", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<Q,PE> QE;

class R : public Q
	{
	typedef R self_t;
	typedef Q hier_t;
	virtual void do_foo( int const& a ) const
		{
		if ( ! a )
			M_THROW( "bad arg R", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<R,QE> RE;

	};

TUT_TEST_GROUP( tut_yaal_hcore_hexception, "yaal::hcore::HException" )

TUT_UNIT_TEST( "valid ex hier construct for full hier" )
	try
		{
		A x;
		x.foo( 0 );
		fail( "test bug, exception not thrown" );
		}
	catch ( CE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( BE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( AE const& )
		{
		}
	catch ( HException const& )
		{
		fail( "bad exception caught" );
		}
	catch ( ... )
		{
		fail( "bad exception caught" );
		}
	try
		{
		B x;
		x.foo( 0 );
		fail( "test bug, exception not thrown" );
		}
	catch ( CE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( BE const& )
		{
		}
	catch ( AE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( HException const& )
		{
		fail( "bad exception caught" );
		}
	catch ( ... )
		{
		fail( "bad exception caught" );
		}
	try
		{
		C x;
		x.foo( 0 );
		fail( "test bug, exception not thrown" );
		}
	catch ( CE const& )
		{
		}
	catch ( BE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( AE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		fail( "bad exception caught" );
		}
	catch ( ... )
		{
		fail( "bad exception caught" );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST( "degenerated hier" )
	try
		{
		P x;
		x.foo( 0 );
		fail( "test bug, exception not thrown" );
		}
	catch ( RE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( QE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( PE const& )
		{
		}
	catch ( HException const& )
		{
		fail( "bad exception caught" );
		}
	catch ( ... )
		{
		fail( "bad exception caught" );
		}
	try
		{
		Q x;
		x.foo( 0 );
		fail( "test bug, exception not thrown" );
		}
	catch ( RE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( QE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( PE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( HException const& )
		{
		}
	catch ( ... )
		{
		fail( "bad exception caught" );
		}
	try
		{
		R x;
		x.foo( 0 );
		fail( "test bug, exception not thrown" );
		}
	catch ( RE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( QE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( PE const& )
		{
		fail( "bad exception caught" );
		}
	catch ( HException const& )
		{
		}
	catch ( ... )
		{
		fail( "bad exception caught" );
		}
TUT_TEARDOWN()

}

