/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstdlib>
#include <memory>
#include <TUT/tut.hpp>

#include <yaal/hcore/hcall.hxx>
#include <yaal/hcore/hformat.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "tut_yaal_hcore_hcall.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hcall : public simple_mock<tut_yaal_hcore_hcall> {
	typedef simple_mock<tut_yaal_hcore_hcall> base_type;
	int _callNo;
	int _fileNo;
	int _suitUt;
	yaal::hcore::HFile _out;
	YaalHCoreHCallClass _value;
	typedef HPointer<YaalHCoreHCallClass> shared_value_t;
	shared_value_t _sharedValue;
	shared_value_t const& _constSharedValue;
	YaalHCoreHCallClass const& _constValue;
	tut_yaal_hcore_hcall( void );
	virtual ~tut_yaal_hcore_hcall( void );
	void generate_yaal_hcore_hcall_tests( void );
	void generate_yaal_hcore_hcall_test( int, int );
	void file_header( void );
	void file_footer( void );
};

TUT_TEST_GROUP( tut_yaal_hcore_hcall, "yaal::hcore::HCall" );

tut_yaal_hcore_hcall::tut_yaal_hcore_hcall( void )
	: base_type()
	, _callNo( 0 )
	, _fileNo( 0 )
	, _suitUt( 0 )
	, _out()
	, _value()
	, _sharedValue( make_pointer<YaalHCoreHCallClass>() )
	, _constSharedValue( _sharedValue )
	, _constValue( _value ) {
	if ( getenv( "GEN_YAAL_HCORE_HCALL" ) ) {
		generate_yaal_hcore_hcall_tests();
	}
}

tut_yaal_hcore_hcall::~tut_yaal_hcore_hcall( void ) {
}

static int const MAX_TESTED_ARGS = 5;
static int const MAX_UT_PER_SUIT = 50;
static int const MAX_TEST_PER_UT = 20;

void tut_yaal_hcore_hcall::generate_yaal_hcore_hcall_tests( void ) {
	file_header();
	for ( int arg = 0; arg <= MAX_TESTED_ARGS; ++ arg ) {
		for ( int freeArg = 0; freeArg <= arg; ++ freeArg ) {
			generate_yaal_hcore_hcall_test( arg, freeArg );
		}
	}
	file_footer();
}

void tut_yaal_hcore_hcall::file_header( void ) {
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
"TUT_SIMPLE_MOCK( tut_yaal_hcore_hcall_" << setfill( '0'_ycp ) << setw( 3 ) << _fileNo << " );\n"
"TUT_TEST_GROUP( tut_yaal_hcore_hcall_" << setw( 3 ) << _fileNo << " , \"yaal::hcore::HCall::" << setw( 3 ) << _fileNo << "\" );\n"
"\n" << flush;
}

void tut_yaal_hcore_hcall::file_footer( void ) {
	_out <<
"}\n"
"\n" << flush;
	_out.close();
}

void tut_yaal_hcore_hcall::generate_yaal_hcore_hcall_test( int arg, int freeArg ) {
	typedef HArray<int> int_vec_t;
	int_vec_t v( arg );
	fill_n( v.begin(), arg - freeArg, 0 );
	generate_n( v.begin() + ( arg - freeArg ), freeArg, inc( 1 ) );
	_callNo = 1;
	bool hasNext( true );
	while ( hasNext ) {
		int localCall( 0 );
		_out << "TUT_UNIT_TEST( " << _suitUt  + 1 << ", \"" << ( arg ? HString( arg ) : HString( "no" )  )
			<< " arg" << ( arg == 1 ? "" : "s" ) << ", " << ( freeArg ? HString( freeArg ) : HString( "no" ) )
			<< " free arg" << ( freeArg == 1 ? "" : "s" ) << ", call #" << _callNo << "... \" )" << endl;
		do {
			_out << "\tENSURE_EQUALS( \"function bind failed\", call( foo" << arg;
			for ( int i = 1; i <= arg; ++ i ) {
				_out << ", " << ( v[i - 1] ? "_" : "" ) << ( v[i - 1] ? v[i - 1] : i );
			}
			_out << " )(" << ( freeArg ? " " : "" );
			for ( int i = 1; i <= freeArg; ++ i ) {
				if ( i > 1 )
					_out << ", ";
				_out << - ( ( find( v.begin(), v.end(), i ) - v.begin() ) + 1 );
			}
			_out << ( freeArg ? " " : "" ) << "), \"foo" << arg << ( arg ? ": " : "" );
			for ( int i = 1; i <= arg; ++ i ) {
				if ( i > 1 )
					_out << ", ";
				_out << "a" << i << " = " << ( v[i - 1] ? "-" : "" ) << i;
			}

			_out << "\" );" << endl;
			++ _callNo;
			++ localCall;
		} while ( ( hasNext = next_permutation( v.begin(), v.end() ) ) && ( localCall < MAX_TEST_PER_UT ) );
		_out << "TUT_TEARDOWN()" << endl << endl;
		++ _suitUt;
		if ( hasNext && ( _suitUt >= MAX_UT_PER_SUIT ) ) {
			_suitUt = 0;
			file_footer();
			++ _fileNo;
			file_header();
		}
	}
	return;
}

#ifdef __MSVCXX__
static int const NSSKIP = sizeof ( "tut::" ) - 1;
#else
static int const NSSKIP = 0;
#endif

HString foo0( void ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP );
	return ( ss.string() );
}

HString foo1( int a1 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1;
	return ( ss.string() );
}

HString foo2( int a1, int a2 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2;
	return ( ss.string() );
}

HString foo3( int a1, int a2, int a3 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2 << ", a3 = " << a3;
	return ( ss.string() );
}

HString foo4( int a1, int a2, int a3, int a4 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4;
	return ( ss.string() );
}

HString foo5( int a1, int a2, int a3, int a4, int a5 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5;
	return ( ss.string() );
}

HString foo6( int a1, int a2, int a3, int a4, int a5, int a6 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6;
	return ( ss.string() );
}

HString foo7( int a1, int a2, int a3, int a4, int a5, int a6, int a7 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7;
	return ( ss.string() );
}

HString foo8( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8;
	return ( ss.string() );
}

HString foo9( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8
		<< ", a9 = " << a9;
	return ( ss.string() );
}

HString foo10( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10 ) {
	HStringStream ss;
	ss << ( __FUNCTION__ + NSSKIP ) << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8
		<< ", a9 = " << a9 << ", a10 = " << a10;
	return ( ss.string() );
}

YaalHCoreHCallClass::YaalHCoreHCallClass( void ) {
}

YaalHCoreHCallClass::YaalHCoreHCallClass( YaalHCoreHCallClass const& ) {
	FAIL( "one shall not copy me!" );
}

YaalHCoreHCallClass::~YaalHCoreHCallClass( void ) {
}

HString YaalHCoreHCallClass::foo0( void ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo0() );
}

HString YaalHCoreHCallClass::foo1( int a1 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo1( a1 ) );
}

HString YaalHCoreHCallClass::foo2( int a1, int a2 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo2( a1, a2 ) );
}

HString YaalHCoreHCallClass::foo3( int a1, int a2, int a3 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo3( a1, a2, a3 ) );
}

HString YaalHCoreHCallClass::foo4( int a1, int a2, int a3, int a4 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo4( a1, a2, a3, a4 ) );
}

HString YaalHCoreHCallClass::foo5( int a1, int a2, int a3, int a4, int a5 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo5( a1, a2, a3, a4, a5 ) );
}

HString YaalHCoreHCallClass::foo6( int a1, int a2, int a3, int a4, int a5, int a6 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo6( a1, a2, a3, a4, a5, a6 ) );
}

HString YaalHCoreHCallClass::foo7( int a1, int a2, int a3, int a4, int a5, int a6, int a7 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo7( a1, a2, a3, a4, a5, a6, a7 ) );
}

HString YaalHCoreHCallClass::foo8( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo8( a1, a2, a3, a4, a5, a6, a7, a8 ) );
}

HString YaalHCoreHCallClass::foo9( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo9( a1, a2, a3, a4, a5, a6, a7, a8, a9 ) );
}

HString YaalHCoreHCallClass::foo10( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10 ) const {
	return ( HString( "YaalHCoreHCallClass: " ) + tut::foo10( a1, a2, a3, a4, a5, a6, a7, a8, a9, a10 ) );
}

class Sumator {
	int _arg;
public:
	Sumator( int arg_ ) : _arg( arg_ ) {}
/* cppcheck-suppress functionConst */
	int calculate( void )
		{ return ( _arg ); }
	int calculate( int arg_ )
		{ return ( _arg + arg_ ); }
	int calculate_const( int arg_ ) const
		{ return ( _arg + arg_ ); }
/* cppcheck-suppress functionConst */
	int calculate_volatile( int arg_ ) volatile
		{ return ( _arg + arg_ ); }
	int calculate_const_volatile( int arg_ ) const volatile
		{ return ( _arg + arg_ ); }
	int sum( int a1, int a2, int a3, int a4, int a5, int a6 ) {
		return ( _arg + a1 + a2 + a3 + a4 + a5 + a6 );
	}
};

template<typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t>
int cf( a0_t = trait::no_type(), a1_t = trait::no_type(),
		a2_t = trait::no_type(), a3_t = trait::no_type(),
		a4_t = trait::no_type(), a5_t = trait::no_type() ) {
	return ( call_calculator<void(*)(void), int, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t>::free_standing_args::value );
}

inline void show_rectangle( int a, int b ) {
	clog << "a: " << a << ", b: " << b << endl;
}

TUT_UNIT_TEST( "(hand written) no arg" )
	ENSURE_EQUALS( "function bind failed", call( foo0 )(), "foo0" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo0, &_value )(), "YaalHCoreHCallClass: foo0" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo0, &_constValue )(), "YaalHCoreHCallClass: foo0" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo0, _sharedValue )(), "YaalHCoreHCallClass: foo0" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo0, _constSharedValue )(), "YaalHCoreHCallClass: foo0" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo0, make_resource<YaalHCoreHCallClass>() )(), "YaalHCoreHCallClass: foo0" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(hand written) 1 (free) arg" )
	ENSURE_EQUALS( "function bind failed", call( foo1, _1 )( -2 ), "foo1: a1 = -2" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, &_value, _1 )( -2 ), "YaalHCoreHCallClass: foo1: a1 = -2" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, &_constValue, _1 )( -2 ), "YaalHCoreHCallClass: foo1: a1 = -2" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, _sharedValue, _1 )( -2 ), "YaalHCoreHCallClass: foo1: a1 = -2" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, _constSharedValue, _1 )( -2 ), "YaalHCoreHCallClass: foo1: a1 = -2" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, make_resource<YaalHCoreHCallClass>(), _1 )( -2 ), "YaalHCoreHCallClass: foo1: a1 = -2" );
	ENSURE_EQUALS( "function bind failed", call( foo1, 1 )(), "foo1: a1 = 1" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, &_value, 1 )(), "YaalHCoreHCallClass: foo1: a1 = 1" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, &_constValue, 1 )(), "YaalHCoreHCallClass: foo1: a1 = 1" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, _sharedValue, 1 )(), "YaalHCoreHCallClass: foo1: a1 = 1" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, _constSharedValue, 1 )(), "YaalHCoreHCallClass: foo1: a1 = 1" );
	ENSURE_EQUALS( "function bind failed", call( &YaalHCoreHCallClass::foo1, make_resource<YaalHCoreHCallClass>(), 1 )(), "YaalHCoreHCallClass: foo1: a1 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(hand written) 2 (1 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo2, _1, 2 )( -3 ), "foo2: a1 = -3, a2 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo2, 2, _1 )( -3 ), "foo2: a1 = 2, a2 = -3" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(hand written) 2 (2 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo2, _1, _2 )( -1, -2 ), "foo2: a1 = -1, a2 = -2" );
	ENSURE_EQUALS( "function bind failed", call( foo2, _2, _1 )( -1, -2 ), "foo2: a1 = -2, a2 = -1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(hand written) 3 (0 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, 0, 1, 2 )(), "foo3: a1 = 0, a2 = 1, a3 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(hand written) 3 (1 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, 1, 2 )( -3 ), "foo3: a1 = -3, a2 = 1, a3 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 0, _1, 2 )( -4 ), "foo3: a1 = 0, a2 = -4, a3 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 0, 1, _1 )( -5 ), "foo3: a1 = 0, a2 = 1, a3 = -5" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(hand written) 3 (2 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, _2, 2 )( -3, -4 ), "foo3: a1 = -3, a2 = -4, a3 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _2, _1, 2 )( -3, -4 ), "foo3: a1 = -4, a2 = -3, a3 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 0, _1, _2 )( -4, -5 ), "foo3: a1 = 0, a2 = -4, a3 = -5" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _2, 1, _1 )( -5, -6 ), "foo3: a1 = -6, a2 = 1, a3 = -5" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(hand written) 6 (2 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo6, 2, _1, 4, 8, _2, 16 )( -100, -2000 ), "foo6: a1 = 2, a2 = -100, a3 = 4, a4 = 8, a5 = -2000, a6 = 16" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "(hand written) 10 (4 free) args" )
	ENSURE_EQUALS( "function bind failed", call( foo10, 7, 1, 2, _3, 4, _2, 6, _1, 8, _4 )( -1, -2, -3, -4 ), "foo10: a1 = 7, a2 = 1, a3 = 2, a4 = -3, a5 = 4, a6 = -2, a7 = 6, a8 = -1, a9 = 8, a10 = -4" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "const, volatile qualifiers" )
	Sumator s( 1 );
	ENSURE_EQUALS( "no qualifiers failed", call( static_cast<int (Sumator::*)( int )>( &Sumator::calculate ), &s, _1 )( 3 ), 4 );
	ENSURE_EQUALS( "const qualifier failed", call( &Sumator::calculate_const, &s, _1 )( 3 ), 4 );
	ENSURE_EQUALS( "volatile qualifier failed", call( &Sumator::calculate_volatile, &s, _1 )( 3 ), 4 );
	ENSURE_EQUALS( "const volatile qualifier failed", call( &Sumator::calculate_const_volatile, &s, _1 )( 3 ), 4 );
TUT_TEARDOWN()

namespace {
void foo( tut_yaal_hcore_hcall::item_t const& ) {
	return;
}
}

TUT_UNIT_TEST( "pass argument by value" )
	item_t::reset();
	item_t item;
	typedef call_calculator<void (*)( item_t const& ), item_t&>::type::type func_by_val_t;
	ENSURE_EQUALS( "environment dirty", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "environment dirty", item_t::get_move_count(), 0 );
	func_by_val_t f( call( &foo, item ) );
	ENSURE_EQUALS( "argument not copied", item_t::get_copy_count(), 1 );
	ENSURE_EQUALS( "argument was moved", item_t::get_move_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "move argument by rvalue" )
	item_t::reset();
	item_t item;
	typedef call_calculator<void (*)( item_t const& ), item_t>::type::type func_by_rval_t;
	ENSURE_EQUALS( "environment dirty", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "environment dirty", item_t::get_move_count(), 0 );
	func_by_rval_t f( call( &foo, yaal::move( item ) ) );
	ENSURE_EQUALS( "argument copied", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "argument was moved", item_t::get_move_count(), 1 );
TUT_TEARDOWN()

#if 0
namespace {
void rfoo( tut_yaal_hcore_hcall::item_t&& ) {
	return;
}
}
/*
 * If function expects rvalue reference as an argument
 * than current implementation of HCall<> fails cause it
 * always passed bound arguments as lvalue references.
 */
TUT_UNIT_TEST( "move argument by rvalue to rvalue expecting function" )
	item_t::reset();
	item_t item;
	typedef call_calculator<void (*)( item_t&& ), item_t>::type::type func_by_rval_t;
	ENSURE_EQUALS( "environment dirty", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "environment dirty", item_t::get_move_count(), 0 );
	func_by_rval_t f( call( &rfoo, yaal::move( item ) ) );
	ENSURE_EQUALS( "argument copied", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "argument was moved", item_t::get_move_count(), 4 );
TUT_TEARDOWN()
#endif

///////////////////////////////////////////////////////////////////////////

namespace {
void foobar( tut_yaal_hcore_hcall::item_t const& item_, HString const& name_ ) {
	clog << name_ << " = " << item_.to_string() << endl;
}
}

TUT_UNIT_TEST( "lvalue copy count on bound" )
	item_t::reset();
	ENSURE_EQUALS( "environment dirty", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "environment dirty", item_t::get_move_count(), 0 );
	item_t item;
	call( &foobar, item, _1 )( "item" );
	ENSURE_EQUALS( "argument copied", item_t::get_copy_count(), 1 );
	ENSURE_EQUALS( "argument was moved", item_t::get_move_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "lvalue copy count on unbound" )
	item_t::reset();
	ENSURE_EQUALS( "environment dirty", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "environment dirty", item_t::get_move_count(), 0 );
	item_t item;
	call( &foobar, _1, "item" )( item );
	ENSURE_EQUALS( "argument copied", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "argument was moved", item_t::get_move_count(), 0 );
TUT_TEARDOWN()

namespace {
tut_yaal_hcore_hcall::item_t make_item( void ) {
	return ( tut_yaal_hcore_hcall::item_t() );
}
}

TUT_UNIT_TEST( "rvalue copy count on bound" )
	item_t::reset();
	ENSURE_EQUALS( "environment dirty", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "environment dirty", item_t::get_move_count(), 0 );
	call( &foobar, make_item(), _1 )( "item" );
	ENSURE_EQUALS( "argument copied", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "argument was moved", item_t::get_move_count(), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rvalue copy count on unbound" )
	item_t::reset();
	ENSURE_EQUALS( "environment dirty", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "environment dirty", item_t::get_move_count(), 0 );
	call( &foobar, _1, "item" )( make_item() );
	ENSURE_EQUALS( "argument copied", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "argument was moved", item_t::get_move_count(), 0 );
TUT_TEARDOWN()

namespace {

class MemFunTest {
	int _base;
public:
	MemFunTest( int base_ ) : _base( base_ ) {}
/* cppcheck-suppress functionConst */
	int value( void )
		{ return ( _base ); }
	int value_const( void ) const
		{ return ( _base ); }
/* cppcheck-suppress functionConst */
	int calc( int arg_ )
		{ return ( _base + arg_ ); }
	int calc_const( int arg_ ) const
		{ return ( _base + arg_ ); }
};

}

TUT_UNIT_TEST( "call() and const call on ptr and on ref" )
	typedef HPointer<MemFunTest> mem_fun_test_ptr_t;
	typedef HList<mem_fun_test_ptr_t> mem_fun_ptr_list_t;
	typedef HList<MemFunTest*> naked_list_t;
	typedef HList<MemFunTest const*> const_naked_list_t;

	mem_fun_ptr_list_t l;
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 0 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 1 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 3 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 7 ) ) );

	naked_list_t nl;
	const_naked_list_t cnl;
	transform( l.begin(), l.end(), back_insert_iterator( nl ), call( static_cast<tut::MemFunTest* ( yaal::hcore::HPointer<tut::MemFunTest>::* )( void )>( &mem_fun_test_ptr_t::raw ), _1 ) );
	transform( l.begin(), l.end(), back_insert_iterator( cnl ), call( static_cast<tut::MemFunTest const* ( yaal::hcore::HPointer<tut::MemFunTest>::* )( void ) const>( &mem_fun_test_ptr_t::raw ), _1 ) );
	HStringStream ss;
	transform( nl.begin(), nl.end(), stream_iterator( ss, " " ), call( &MemFunTest::value, _1 ) );
	ENSURE_EQUALS( "call failed", ss.string(), "0 1 3 7 " );
	clog << ss.string() << endl;
	ss.reset();
	transform( cnl.begin(), cnl.end(), stream_iterator( ss, " " ), call( &MemFunTest::value_const, _1 ) );
	ENSURE_EQUALS( "call failed", ss.string(), "0 1 3 7 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "call(arg) const and non-const ref and ptr." )
	int a[] = { 1, 4, 9, 16 };
	typedef HPointer<MemFunTest> mem_fun_test_ptr_t;
	typedef HList<mem_fun_test_ptr_t> mem_fun_ptr_list_t;
	typedef HList<MemFunTest*> naked_list_t;
	typedef HList<MemFunTest const*> const_naked_list_t;

	mem_fun_ptr_list_t l;
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 0 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 1 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 3 ) ) );
	l.push_back( mem_fun_test_ptr_t( new MemFunTest( 7 ) ) );

	naked_list_t nl;
	const_naked_list_t cnl;
	transform( l.begin(), l.end(), back_insert_iterator( nl ), call( static_cast<tut::MemFunTest* ( yaal::hcore::HPointer<tut::MemFunTest>::* )( void )>( &mem_fun_test_ptr_t::raw ), _1 ) );
	transform( l.begin(), l.end(), back_insert_iterator( cnl ), call( static_cast<tut::MemFunTest const* ( yaal::hcore::HPointer<tut::MemFunTest>::* )( void ) const>( &mem_fun_test_ptr_t::raw ), _1 ) );
	HStringStream ss;
	transform( nl.begin(), nl.end(), a, stream_iterator( ss, " " ), call( &MemFunTest::calc, _1, _2 ) );
	ENSURE_EQUALS( "call failed", ss.string(), "1 5 12 23 " );
	clog << ss.string() << endl;
	ss.reset();
	transform( cnl.begin(), cnl.end(), a, stream_iterator( ss, " " ), call( &MemFunTest::calc_const, _1, _2 ) );
	ENSURE_EQUALS( "call failed", ss.string(), "1 5 12 23 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "call(arg) ref" )
	int a[] = { 1, 4, 9, 16 };
	typedef HList<MemFunTest> mem_fun_list_t;

	mem_fun_list_t l;
	l.push_back( MemFunTest( 0 ) );
	l.push_back( MemFunTest( 1 ) );
	l.push_back( MemFunTest( 3 ) );
	l.push_back( MemFunTest( 7 ) );

	HStringStream ss;
	transform( l.begin(), l.end(), a, stream_iterator( ss, " " ), call( &MemFunTest::calc, _1, _2 ) );
	ENSURE_EQUALS( "mem_fun1_ref failed", ss.string(), "1 5 12 23 " );
	clog << ss.string() << endl;
TUT_TEARDOWN()

struct ArgumentReturnValueType {
	int _data;
	ArgumentReturnValueType( int data_ )
		: _data( data_ )
		{}
	void set_value( int data_ ) {
		_data = data_;
	}
	void set_value_ref( int& data_ ) {
		_data = data_;
	}
	void set_value_const_ref( int const& data_ ) {
		_data = data_;
	}
	void value_ref( int& data_ ) {
		data_ = _data;
	}
	int get_value( void ) {
		return ( _data );
	}
	int& get_value_ref( void ) {
		return ( _data );
	}
	int const& get_value_const_ref( void ) {
		return ( _data );
	}
};

TUT_UNIT_TEST( "argument value types" )
	ArgumentReturnValueType arvt( 0 );
	call( &ArgumentReturnValueType::set_value, &arvt, _1 )( 1 );
	ENSURE_EQUALS( "set_value failed", arvt._data, 1 );
	call( &ArgumentReturnValueType::set_value_const_ref, &arvt, _1 )( 2 );
	ENSURE_EQUALS( "set_value_const_ref failed", arvt._data, 2 );
	int three( 3 );
	call( &ArgumentReturnValueType::set_value_ref, &arvt, _1 )( three );
	ENSURE_EQUALS( "set_value_ref failed", arvt._data, 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "return value types" )
	ArgumentReturnValueType arvt( 7 );
	ENSURE_EQUALS( "get_value failed", call( &ArgumentReturnValueType::get_value, &arvt )(), 7 );
	int const& crVal( call( &ArgumentReturnValueType::get_value_const_ref, &arvt )() );
	ENSURE_EQUALS( "get_value_const_ref failed", crVal, 7 );
	arvt._data = 13;
	ENSURE_EQUALS( "get_value_const_ref failed", crVal, 13 );
	call( &ArgumentReturnValueType::get_value_ref, &arvt )() = 42;
	ENSURE_EQUALS( "get_value_ref failed", arvt._data, 42 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "use call as a functor in an algorithm" )
	HArray<int> tab( 10 );
	generate_n( tab.begin(), tab.size(), inc( 1 ) );
	for_each( tab.begin(), tab.end(), call( show_rectangle, _1, 2 ) );
	for_each( tab.begin(), tab.end(), call( show_rectangle, 2, _1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "random free standing args" )
	Sumator s( 1 );
	call( static_cast<int (Sumator::*)( void )>( &Sumator::calculate ), &s );
	ENSURE_EQUALS( "this as free standing", call( static_cast<int (Sumator::*)( void )>( &Sumator::calculate ), _1 )( s ), 1 );
TUT_TEARDOWN()

}

