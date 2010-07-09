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

#include <cstdlib>
#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"
#include "tut_yaal_hcore_hcall.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hcall
	{
	int _callNo;
	int _fileNo;
	int _suitUt;
	yaal::hcore::HFile _out;
	tut_yaal_hcore_hcall( void );
	virtual ~tut_yaal_hcore_hcall( void );
	void generate_yaal_hcore_hcall_tests( void );
	void generate_yaal_hcore_hcall_test( int, int );
	void file_header( void );
	void file_footer( void );
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_hcall, "yaal::hcore::HCall" );

tut_yaal_hcore_hcall::tut_yaal_hcore_hcall( void ) : _callNo( 0 ), _fileNo( 0 ), _suitUt( 0 ), _out()
	{
	if ( getenv( "GEN_YAAL_HCORE_HCALL" ) )
		generate_yaal_hcore_hcall_tests();
	}

tut_yaal_hcore_hcall::~tut_yaal_hcore_hcall( void )
	{
	}

static int const MAX_TESTED_ARGS = 5;
static int const MAX_UT_PER_SUIT = 50;
static int const MAX_TEST_PER_UT = 20;

void tut_yaal_hcore_hcall::generate_yaal_hcore_hcall_tests( void )
	{
	file_header();
	for ( int arg = 0; arg <= MAX_TESTED_ARGS; ++ arg )
		{
		for ( int freeArg = 0; freeArg <= arg; ++ freeArg )
			{
			generate_yaal_hcore_hcall_test( arg, freeArg );
			}
		}
	file_footer();
	}

void tut_yaal_hcore_hcall::file_header( void )
	{
	_out.open( ( HFormat( "./src/tut_yaal_hcore_hcall_auto_%03d.cxx" ) % _fileNo ).string(), HFile::open_t( HFile::OPEN::WRITING ) );
	_out <<
"#include <TUT/tut.hpp>\n"
"\n"
"#include <yaal/yaal.hxx>\n"
"M_VCSID( \"$Id: \"__ID__\" $\" )\n"
"#include \"tut_helpers.hxx\"\n"
"#include \"tut_yaal_hcore_hcall.hxx\"\n"
"\n"
"using namespace tut;\n"
"using namespace yaal;\n"
"using namespace yaal::hcore;\n"
"using namespace yaal::tools;\n"
"using namespace yaal::tools::util;\n"
"using namespace tress::tut_helpers;\n"
"\n"
"namespace tut\n"
"{\n"
"\n"
"TUT_SIMPLE_MOCK( tut_yaal_hcore_hcall_" << setfill( '0' ) << setw( 3 ) << _fileNo << " );\n"
"TUT_TEST_GROUP_N( tut_yaal_hcore_hcall_" << setw( 3 ) << _fileNo << " , \"yaal::hcore::HCall::" << setw( 3 ) << _fileNo << "\" );\n"
"\n" << flush;
	}

void tut_yaal_hcore_hcall::file_footer( void )
	{
	_out <<
"}\n"
"\n" << flush;
	_out.close();
	}

void tut_yaal_hcore_hcall::generate_yaal_hcore_hcall_test( int arg, int freeArg )
	{
	typedef HArray<int> int_vec_t;
	int_vec_t v( arg );
	fill_n( v.begin(), arg - freeArg, 0 );
	generate_n( v.begin() + ( arg - freeArg ), freeArg, inc( 1 ) );
	_callNo = 1;
	bool hasNext( true );
	while ( hasNext )
		{
		int localCall( 0 );
		_out << "TUT_UNIT_TEST_N( " << _suitUt  + 1 << ", \"" << ( arg ? HString( arg ) : HString( "no" )  )
			<< " arg" << ( arg == 1 ? "" : "s" ) << ", " << ( freeArg ? HString( freeArg ) : HString( "no" ) )
			<< " free arg" << ( freeArg == 1 ? "" : "s" ) << ", call #" << _callNo << "... \" )" << endl;
		do
			{
			_out << "\tENSURE_EQUALS( \"function bind failed\", call( foo" << arg;
			for ( int i = 1; i <= arg; ++ i )
				{
				_out << ", " << ( v[i - 1] ? "_" : "" ) << ( v[i - 1] ? v[i - 1] : i );
				}
			_out << " )(" << ( freeArg ? " " : "" );
			for ( int i = 1; i <= freeArg; ++ i )
				{
				if ( i > 1 )
					_out << ", ";
				_out << - ( ( find( v.begin(), v.end(), i ) - v.begin() ) + 1 );
				}
			_out << ( freeArg ? " " : "" ) << "), \"foo" << arg << ( arg ? ": " : "" );
			for ( int i = 1; i <= arg; ++ i )
				{
				if ( i > 1 )
					_out << ", ";
				_out << "a" << i << " = " << ( v[i - 1] ? "-" : "" ) << i;
				}

			_out << "\" );" << endl;
			++ _callNo;
			++ localCall;
			}
		while ( ( hasNext = next_permutation( v.begin(), v.end() ) ) && ( localCall < MAX_TEST_PER_UT ) );
		_out << "TUT_TEARDOWN()" << endl << endl;
		++ _suitUt;
		if ( hasNext && ( _suitUt >= MAX_UT_PER_SUIT ) )
			{
			_suitUt = 0;
			file_footer();
			++ _fileNo;
			file_header();
			}
		}
	return;
	}

HString foo0( void )
	{
	HStringStream ss;
	ss << __FUNCTION__;
	return ( ss.string() );
	}

HString foo1( int a1 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1;
	return ( ss.string() );
	}

HString foo2( int a1, int a2 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2;
	return ( ss.string() );
	}

HString foo3( int a1, int a2, int a3 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2 << ", a3 = " << a3;
	return ( ss.string() );
	}

HString foo4( int a1, int a2, int a3, int a4 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4;
	return ( ss.string() );
	}

HString foo5( int a1, int a2, int a3, int a4, int a5 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5;
	return ( ss.string() );
	}

HString foo6( int a1, int a2, int a3, int a4, int a5, int a6 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6;
	return ( ss.string() );
	}

HString foo7( int a1, int a2, int a3, int a4, int a5, int a6, int a7 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7;
	return ( ss.string() );
	}

HString foo8( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8;
	return ( ss.string() );
	}

HString foo9( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8
		<< ", a9 = " << a9;
	return ( ss.string() );
	}

HString foo10( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8
		<< ", a9 = " << a9 << ", a10 = " << a10;
	return ( ss.string() );
	}

YaalHCoreHCallClass::YaalHCoreHCallClass( void )
	{
	}

YaalHCoreHCallClass::~YaalHCoreHCallClass( void )
	{
	}

HString YaalHCoreHCallClass::foo0( void )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo0() );
	}

HString YaalHCoreHCallClass::foo1( int a1 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo1( a1 ) );
	}

HString YaalHCoreHCallClass::foo2( int a1, int a2 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo2( a1, a2 ) );
	}

HString YaalHCoreHCallClass::foo3( int a1, int a2, int a3 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo3( a1, a2, a3 ) );
	}

HString YaalHCoreHCallClass::foo4( int a1, int a2, int a3, int a4 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo4( a1, a2, a3, a4 ) );
	}

HString YaalHCoreHCallClass::foo5( int a1, int a2, int a3, int a4, int a5 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo5( a1, a2, a3, a4, a5 ) );
	}

HString YaalHCoreHCallClass::foo6( int a1, int a2, int a3, int a4, int a5, int a6 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo6( a1, a2, a3, a4, a5, a6 ) );
	}

HString YaalHCoreHCallClass::foo7( int a1, int a2, int a3, int a4, int a5, int a6, int a7 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo7( a1, a2, a3, a4, a5, a6, a7 ) );
	}

HString YaalHCoreHCallClass::foo8( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo8( a1, a2, a3, a4, a5, a6, a7, a8 ) );
	}

HString YaalHCoreHCallClass::foo9( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo9( a1, a2, a3, a4, a5, a6, a7, a8, a9 ) );
	}

HString YaalHCoreHCallClass::foo10( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10 )
	{
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo10( a1, a2, a3, a4, a5, a6, a7, a8, a9, a10 ) );
	}

class Sumator
	{
	int _arg;
public:
	Sumator( int arg_ ) : _arg( arg_ ) {}
	int calculate( void )
		{ return ( _arg ); }
	int calculate( int arg_ )
		{ return ( _arg + arg_ ); }
	int calculate_const( int arg_ ) const
		{ return ( _arg + arg_ ); }
	int calculate_volatile( int arg_ ) volatile
		{ return ( _arg + arg_ ); }
	int calculate_const_volatile( int arg_ ) const volatile
		{ return ( _arg + arg_ ); }
	int sum( int a1, int a2, int a3, int a4, int a5, int a6 )
		{
		return ( _arg + a1 + a2 + a3 + a4 + a5 + a6 );
		}
	};

template<typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t>
int cf( a0_t = trait::no_type(), a1_t = trait::no_type(),
		a2_t = trait::no_type(), a3_t = trait::no_type(),
		a4_t = trait::no_type(), a5_t = trait::no_type() )
	{
	return ( call_calculator<void(*)(void), int, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t>::free_standing_args::value );
	}

void show_rectangle( int a, int b )
	{
	cout << "a: " << a << ", b: " << b << endl;
	}

TUT_UNIT_TEST_N( 1, "(hand written) no arg" )
	ENSURE_EQUALS( "function bind failed", call( foo0 )(), "foo0" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "(hand written) 1 (free) arg" )
	ENSURE_EQUALS( "function bind failed", call( foo1, _1 )( -2 ), "foo1: a1 = -2" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "(hand written) 2 (1 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo2, _1, 2 )( -3 ), "foo2: a1 = -3, a2 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo2, 2, _1 )( -3 ), "foo2: a1 = 2, a2 = -3" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "(hand written) 2 (2 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo2, _1, _2 )( -1, -2 ), "foo2: a1 = -1, a2 = -2" );
	ENSURE_EQUALS( "function bind failed", call( foo2, _2, _1 )( -1, -2 ), "foo2: a1 = -2, a2 = -1" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "(hand written) 3 (0 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, 0, 1, 2 )(), "foo3: a1 = 0, a2 = 1, a3 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "(hand written) 3 (1 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, 1, 2 )( -3 ), "foo3: a1 = -3, a2 = 1, a3 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 0, _1, 2 )( -4 ), "foo3: a1 = 0, a2 = -4, a3 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 0, 1, _1 )( -5 ), "foo3: a1 = 0, a2 = 1, a3 = -5" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "(hand written) 3 (2 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, _2, 2 )( -3, -4 ), "foo3: a1 = -3, a2 = -4, a3 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _2, _1, 2 )( -3, -4 ), "foo3: a1 = -4, a2 = -3, a3 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 0, _1, _2 )( -4, -5 ), "foo3: a1 = 0, a2 = -4, a3 = -5" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _2, 1, _1 )( -5, -6 ), "foo3: a1 = -6, a2 = 1, a3 = -5" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "(hand written) 6 (2 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo6, 2, _1, 4, 8, _2, 16 )( -100, -2000 ), "foo6: a1 = 2, a2 = -100, a3 = 4, a4 = 8, a5 = -2000, a6 = 16" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "(hand written) 10 (4 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo10, 7, 1, 2, _3, 4, _2, 6, _1, 8, _4 )( -1, -2, -3, -4 ), "foo10: a1 = 7, a2 = 1, a3 = 2, a4 = -3, a5 = 4, a6 = -2, a7 = 6, a8 = -1, a9 = 8, a10 = -4" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 30, "use call as a functor in an algorithm" )
	HArray<int> tab( 10 );
	generate_n( tab.begin(), tab.size(), inc( 1 ) );
	for_each( tab.begin(), tab.end(), call( show_rectangle, _1, 2 ) );
	for_each( tab.begin(), tab.end(), call( show_rectangle, 2, _1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 31, "random free standing args" )
	Sumator s( 1 );
	call( static_cast<int (Sumator::*)( void )>( &Sumator::calculate ), &s );
	ENSURE_EQUALS( "this as free standing", call( static_cast<int (Sumator::*)( void )>( &Sumator::calculate ), _1 )( s ), 1 );
TUT_TEARDOWN()

}

