/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/hterminal.hxx>
#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/math.hxx>
#include <yaal/tools/hmonitor.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace yaal::tools;
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
		{ clog << __PRETTY_FUNCTION__ << endl; }
};

struct Derived : public Base {
	virtual void foo( void )
		{ clog << __PRETTY_FUNCTION__ << endl; }
	void baz( void ) const
		{ clog << __PRETTY_FUNCTION__ << endl; }
	virtual void accept( Visitor const& call ) const
		{ call.visitDerived( *this ); }
};

struct FunkyDerived : public Base {
	virtual void foo( void )
		{ clog << __PRETTY_FUNCTION__ << endl; }
	void bar( void ) const
		{ clog << __PRETTY_FUNCTION__ << endl; }
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

TUT_UNIT_TEST( "visitor pattern" )
	typedef HPointer<Base> base_ptr_t;
	base_ptr_t a = base_ptr_t( new Derived );
	base_ptr_t b = base_ptr_t( new FunkyDerived );
	(*a).foo();
	(*b).foo();
	if ( dynamic_cast<FunkyDerived*>( a.raw() ) )
		dynamic_cast<FunkyDerived*>( a.raw() )->bar();
	else
		clog << "a is not proper type" << endl;
	if ( dynamic_cast<FunkyDerived*>( b.raw() ) )
		dynamic_cast<FunkyDerived*>( b.raw() )->bar();
	else
		clog << "b is not proper type" << endl;
	if ( dynamic_cast<Derived*>( a.raw() ) )
		dynamic_cast<Derived*>( a.raw() )->baz();
	else
		clog << "a is not proper type" << endl;
	if ( dynamic_cast<Derived*>( b.raw() ) )
		dynamic_cast<Derived*>( b.raw() )->baz();
	else
		clog << "b is not proper type" << endl;
	clog << "now the same but without dynamic cast" << endl;
	a->accept( FunkyDerivedBarCall() );
	b->accept( FunkyDerivedBarCall() );
	a->accept( DerivedBazCall() );
	b->accept( DerivedBazCall() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "terminal size" )
	HLock l( HMonitor::get_instance().acquire( "terminal" ) );
	if ( HTerminal::get_instance().exists() ) {
		HTerminal::HSize s( HTerminal::get_instance().size() );
		clog << "Terminal size: " << s.columns() << "x" << s.lines() << "." << endl;
	} else
		clog << "Terminal is not available." << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "terminal colors" )
	clog << endl;
	HSequence const* bgs[] = {
		&bgblack, &bgred, &bggreen, &bgblue, &bgcyan, &bgmagenta, &bgbrown, &bglightgray,
		&bggray, &bgbrightred, &bgbrightgreen, &bgbrightblue, &bgbrightcyan, &bgbrightmagenta, &bgyellow, &bgwhite
	};
	for ( HSequence const* bg : bgs ) {
		clog << *bg << black << "    black    " << red << "    red    " << green << "    green    " << blue << "    blue    "
			<< cyan << "    cyan    " << magenta << "    magenta    " << brown << " brown "
			<< lightgray << " lightgray" << ansi::reset << endl;
		clog << *bg << gray << "    gray     " << brightred << " brightred " << brightgreen << " brightgreen " << brightblue << " brightblue "
			<< brightcyan << " brightcyan " << brightmagenta << " brightmagenta " << yellow << " yellow "
			<< white << "  white  " << ansi::reset << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "terminal colors 256 (gray scale)" )
	clog << black << "  ";
	for ( int i( 0 ); i < 24; ++ i ) {
		clog << gray_scale( PLANE::BACKGROUND, i ) << "  ";
	}
	clog << white << "  " << ansi::reset << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "terminal colors 256 (6x6x6 color cube)" )
	for ( int g( 0 ); g < 6; ++ g ) {
		for ( int r( 0 ); r < 6; ++ r ) {
			for ( int b( 0 ); b < 6; ++ b ) {
				clog << color256( PLANE::BACKGROUND, r, g, b ) << "  ";
			}
			clog << ansi::reset << " ";
		}
		clog << ansi::reset << endl;
	}
	clog << ansi::reset << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "terminal colors RGB" )
	HLock l( HMonitor::get_instance().acquire( "terminal" ) );
	if ( ! HTerminal::get_instance().exists() ) {
		return;
	}
	HTerminal::HSize s( HTerminal::get_instance().size() );
	int lines( s.lines() );
	int columns( s.columns() );
	static int const EXTRA_LINS( 8 );
	static int const EXTRA_COLUMNS( 1 );
	if ( ( lines <= EXTRA_LINS ) || ( columns <= EXTRA_COLUMNS ) ) {
		return;
	}
	double gi( 1. / static_cast<double>( lines - EXTRA_LINS ) );
	double bi( 1. / math::square_root( static_cast<double>( columns - EXTRA_COLUMNS ) ) );
	double ri( 1. / ( ( 1. / bi ) - 1 ) );
	M_ASSERT( ( gi > 0. ) && ( ri > 0. ) && ( bi > 0. ) );
	for ( double g( 0 ); g < 1.; g += gi ) {
		for ( double r( 0 ); r < 1.; r += ri ) {
			for ( double b( 0 ); b < 1.; b += bi ) {
				clog << rgb( PLANE::BACKGROUND, static_cast<int>( r * 256. ), static_cast<int>( g * 256. ), static_cast<int>( b * 256. ) ) << " ";
			}
		}
		clog << ansi::reset << endl;
	}
	clog << ansi::reset << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "yaal data types instantiations for gdb-pretty-printers and MSVC++ [Visualisers] testing." )
	HString shortStr( "huginn" );
	HString str( "Ala ma żółwia, a żółw ma skorupę." );
	HUTF8String utf8Short( shortStr );
	HUTF8String utf8( str );
	HUTF8String sub( utf8.substr( 7, 4 ) );
	HNumber pi( "3.141592653589793" );
	HNumber e( "2.718281828459045" );
	HNumber a( "0.7" );
	HPair<HString, double> p( make_pair<HString>( "PI", pi.to_floating_point() ) );
	HArray<int> emptyArray;
	HArray<int> array( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	HDeque<int> emptyDeque;
	HDeque<int short> dequeShort( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	HDeque<int> deque( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	HDeque<int long> dequeLong( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	HList<int> emptyList;
	HList<int> list( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	HSet<int> emptySet;
	HSet<int> set( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	HMap<int, int> map;
	HLookupMap<int, int> lookup;
	HTime birth( 1978, 5, 24, 23, 30, 00 );
	for ( int i( 0 ); i < 10; ++ i ) {
		map[i] = i * i;
		lookup[i] = i * i;
	}
	HMap<int, int> emptyMap;
	HLookupMap<int, int> emptyLookup;
	HHashSet<int> emptyHashSet;
	HHashSet<int> hashSet( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	HRing<int> emptyRing;
	HRing<int> ring( ring::capacity_type( yaal::size( _testData_[0] ) * 2 ),
		_testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
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
	clog << shortStr << endl;
	clog << str << endl;
	clog << pi << endl;
	clog << e << endl;
	clog << p << endl;
	clog << array << endl;
	clog << emptyArray << endl;
	clog << deque << endl;
	clog << emptyDeque << endl;
	clog << list << endl;
	clog << emptyList << endl;
	clog << set << endl;
	clog << emptySet << endl;
	clog << map << endl;
	clog << lookup << endl;
	clog << emptyMap << endl;
	clog << emptyLookup << endl;
	clog << hashSet << endl;
	clog << emptyHashSet << endl;
	clog << hashMap << endl;
	clog << emptyHashMap << endl;
	clog << ring << endl;
	clog << emptyRing << endl;
	clog << result << endl;
	clog << birth << endl;
TUT_TEARDOWN()

}

