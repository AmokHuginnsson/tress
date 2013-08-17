/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_experiments.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/hconsole/hterminal.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace yaal::hconsole;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_experiments );
TUT_TEST_GROUP( tut_experiments, "::experiments" );

struct Derived;
struct FunkyDerived;
class Visitor {
public:
	virtual ~Visitor( void ) { }
	virtual void visitDerived( Derived const& ) const { };
	virtual void visitFunkyDerived( FunkyDerived const& ) const { };
};

class HVisitorInterface {
public:
	virtual ~HVisitorInterface( void ) { }
	virtual void accept( Visitor const& ) const { }
};

struct Base : public HVisitorInterface {
	virtual ~Base( void ) {}
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
};

struct Derived : public Base {
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
	void baz( void ) const
		{ cout << __PRETTY_FUNCTION__ << endl; }
	virtual void accept( Visitor const& call ) const
		{ call.visitDerived( *this ); }
};

struct FunkyDerived : public Base {
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
	void bar( void ) const
		{ cout << __PRETTY_FUNCTION__ << endl; }
	virtual void accept( Visitor const& call ) const
		{ call.visitFunkyDerived( *this ); }
};

#pragma GCC diagnostic ignored "-Woverloaded-virtual"
class FunkyDerivedBarCall : public Visitor {
public:
	void visitFunkyDerived( FunkyDerived const& obj ) const
		{ obj.bar(); }
};

class DerivedBazCall : public Visitor {
public:
	void visitDerived( Derived const& obj ) const
		{ obj.baz(); }
};
#pragma GCC diagnostic error "-Woverloaded-virtual"

TUT_UNIT_TEST( 1, "visitor pattern" )
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

TUT_UNIT_TEST( 2, "terminal size" )
	if ( _terminal_.exists() ) {
		HTerminal::coord_t c( _terminal_.size() );
		clog << "Terminal size: " << c.second << "x" << c.first << "." << endl;
	} else
		clog << "Terminal is not available." << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "terminal colors" )
	clog << endl;
	clog << red << "    red    " << green << "    green    " << blue << "    blue    "
		<< cyan << "    cyan    " << magenta << "    magenta    " << brown << " brown "
		<< lightgray << " lightgray" << endl;
	clog << brightred << " brightred " << brightgreen << " brightgreen " << brightblue << " brightblue "
		<< brightcyan << " brightcyan " << brightmagenta << " brightmagenta " << yellow << " yellow "
		<< white << "  white" << ansi::reset << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "yaal data types instantiations for gdb-pretty-printers and MSVC++ [Visualisers] testing." )
	HString shortStr( "huginn" );
	HString str( "Ala ma kota, a kot ma mleczko." );
	HNumber pi( "3.141592653589793" );
	HNumber e( "2.718281828459045" );
	HNumber a( "0.7" );
	HPair<HString, double> p( make_pair<HString>( "PI", pi.to_floating_point() ) );
	HArray<int> emptyArray;
	HArray<int> array( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	HDeque<int> emptyDeque;
	HDeque<int short> dequeShort( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	HDeque<int> deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	HDeque<int long> dequeLong( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	HList<int> emptyList;
	HList<int> list( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	HSet<int> emptySet;
	HSet<int> set( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	HMap<int, int> map;
	for ( int i( 0 ); i < 10; ++ i )
		map[i] = i * i;
	HMap<int, int> emptyMap;
	HHashSet<int> emptyHashSet;
	HHashSet<int> hashSet( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	HRing<int> emptyRing;
	HRing<int> ring( ring::capacity( countof ( _testData_[0] ) * 2 ),
		_testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	HHashMap<int, int> hashMap;
	HHashMap<int, int> emptyHashMap;
	for ( int i( 0 ); i < 10; ++ i )
		hashMap[i] = i * i;
	HString result( ( pi * e ).to_string() );
	HPointer<HString> pr( new HString( result ) );
	HPointer<HArray<int> > pa;
	pa = HPointer<HArray<int> >( new HArray<int>( _testData_[0], _testData_[0] + 7 ) );
	HResource<HString> ppr( new HString( result ) );
	HResource<HArray<int> > ppa;
	ppa = HResource<HArray<int> >( new HArray<int>( _testData_[0], _testData_[0] + 7 ) );
	cout << shortStr << endl;
	cout << str << endl;
	cout << pi << endl;
	cout << e << endl;
	cout << p << endl;
	cout << array << endl;
	cout << emptyArray << endl;
	cout << deque << endl;
	cout << emptyDeque << endl;
	cout << list << endl;
	cout << emptyList << endl;
	cout << set << endl;
	cout << emptySet << endl;
	cout << map << endl;
	cout << emptyMap << endl;
	cout << hashSet << endl;
	cout << emptyHashSet << endl;
	cout << hashMap << endl;
	cout << emptyHashMap << endl;
	cout << ring << endl;
	cout << emptyRing << endl;
	cout << result << endl;
TUT_TEARDOWN()

}

