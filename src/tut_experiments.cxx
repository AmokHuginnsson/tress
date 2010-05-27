/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_experiments.cxx - this file is integral part of `tress' project.

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

TUT_SIMPLE_MOCK( tut_experiments );
TUT_TEST_GROUP_N( tut_experiments, "::experiments" );

struct Derived;
struct FunkyDerived;
class Visitor
	{
public:
	virtual ~Visitor( void ) { }
	virtual void visit( Derived& ) { };
	virtual void visit( Derived const& ) const { };
	virtual void visit( FunkyDerived& ) { };
	virtual void visit( FunkyDerived const& ) const { };
	};

class HVisitorInterface
	{
public:
	virtual ~HVisitorInterface( void ) { }
	virtual void accept( Visitor& ) { }
	virtual void accept( Visitor const& ) const { }
	};

struct Base : public HVisitorInterface
	{
	virtual ~Base( void ) {}
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
	};

struct Derived : public Base
	{
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
	void baz( void ) const
		{ cout << __PRETTY_FUNCTION__ << endl; }
	virtual void accept( Visitor const& call ) const
		{ call.visit( *this ); }
	};

struct FunkyDerived : public Base
	{
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
	void bar( void ) const
		{ cout << __PRETTY_FUNCTION__ << endl; }
	virtual void accept( Visitor const& call ) const
		{ call.visit( *this ); }
	};

class FunkyDerivedBarCall : public Visitor
	{
public:
	void visit( FunkyDerived const& obj ) const
		{ obj.bar(); }
	};

class DerivedBazCall : public Visitor
	{
public:
	void visit( Derived const& obj ) const
		{ obj.baz(); }
	};

TUT_UNIT_TEST_N( 1, "visitor pattern" )
	typedef HPointer<Base> base_ptr_t;
	base_ptr_t a = base_ptr_t( new Derived );
	base_ptr_t b = base_ptr_t( new FunkyDerived );
	(*a).foo();
	(*b).foo();
	if ( dynamic_cast<FunkyDerived*>( a.raw() ) )
		dynamic_cast<FunkyDerived*>( a.raw() )->bar();
	else
		cout << "a is not proper type" << endl;
	if ( dynamic_cast<FunkyDerived*>( b.raw() ) )
		dynamic_cast<FunkyDerived*>( b.raw() )->bar();
	else
		cout << "b is not proper type" << endl;
	if ( dynamic_cast<Derived*>( a.raw() ) )
		dynamic_cast<Derived*>( a.raw() )->baz();
	else
		cout << "a is not proper type" << endl;
	if ( dynamic_cast<Derived*>( b.raw() ) )
		dynamic_cast<Derived*>( b.raw() )->baz();
	else
		cout << "b is not proper type" << endl;
	cout << "now the same but without dynamic cast" << endl;
	a->accept( FunkyDerivedBarCall() );
	b->accept( FunkyDerivedBarCall() );
	a->accept( DerivedBazCall() );
	b->accept( DerivedBazCall() );
TUT_TEARDOWN()

}

