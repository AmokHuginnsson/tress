/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_helpers.hxx - this file is integral part of `tress' project.

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

#ifndef TRESS_TUT_HELPERS_HXX_INCLUDED
#define TRESS_TUT_HELPERS_HXX_INCLUDED

#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <list>
#include <vector>
#include <deque>
#include <set>
#include <stdexcept>

#include <yaal/hcore/hstreaminterface.hxx>
#include <yaal/hcore/hfile.hxx>
#include <yaal/hcore/hpair.hxx>
#include <yaal/hcore/harray.hxx>
#include <yaal/hcore/hdeque.hxx>
#include <yaal/hcore/hset.hxx>
#include <yaal/hcore/hlist.hxx>
#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/hvector.hxx>
#include <yaal/hcore/hmatrix.hxx>
#include <yaal/hcore/hclock.hxx>
#include <yaal/tools/hstringstream.hxx>
#include <yaal/tools/hring.hxx>
#include <yaal/tools/htwowaymap.hxx>
#include <yaal/hconsole/console.hxx>

#if defined( __GNUC__ ) && ! defined( stdext )
#define stdext __gnu_cxx
#endif /* defined( __GNUC__ ) && ! defined( stdext ) */

#ifdef TUT_UNIT_TEST
#	error Tress redefines TUT_UNIT_TEST macro.
#endif /* #ifdef TUT_UNIT_TEST */
#ifdef TUT_TEARDOWN
#	error Tress redefines TUT_TEARDOWN macro.
#endif /* #ifdef TUT_TEARDOWN */
#ifdef TUT_TEST_GROUP
#	error Tress redefines TUT_TEST_GROUP macro.
#endif /* #ifdef TUT_TEST_GROUP */
#ifdef TUT_SIMPLE_MOCK
#	error Tress redefines TUT_SIMPLE_MOCK macro.
#endif /* #ifdef TUT_SIMPLE_MOCK */
#ifdef TIME_CONSTRAINT_EXEMPT
#	error Tress redefines TIME_CONSTRAINT_EXEMPT macro.
#endif /* #ifdef TIME_CONSTRAINT_EXEMPT */
#ifdef TUT_DECLARE
#	error Tress redefines TUT_DECLARE macro.
#endif /* #ifdef TUT_DECLARE */
#ifdef TUT_INVOKE
#	error Tress redefines TUT_INVOKE macro.
#endif /* #ifdef TUT_INVOKE */
#ifdef TUT_EVAL
#	error Tress redefines TUT_EVAL macro.
#endif /* #ifdef TUT_EVAL */

#define TUT_UNIT_TEST( no, title ) \
namespace { static int const M_CONCAT( dropIt, __LINE__ ) __attribute__(( __used__ )) = group.register_test( no, title ); } \
template<> template<> void module::test<(no)>( void ) { do { set_test_meta( title, __FILE__, __LINE__ ); } while ( 0 );
#define TUT_TEARDOWN() }
#define TUT_TEST_GROUP( mock, name ) \
typedef test_group<mock> tut_group; \
typedef tut_group::object module; \
typedef yaal::hcore::HExceptionSafeGlobal<tut_group, tress::tut_helpers::HSTDGlobalScopeExceptionHandlingPolicy> tut_group_holder; \
tut_group_holder mock##_group( ( name ) ); \
namespace { tut_group& group( mock##_group.instance() ); } \
typedef void void_type
#define TUT_SIMPLE_MOCK( name ) struct name : public simple_mock<name> { \
	virtual ~name( void ) \
		{} \
}
#define TIME_CONSTRAINT_EXEMPT time_constraint_exempt

#define TUT_DECLARE( statement ) clog << hconsole::brightgreen << ">> " << #statement << hconsole::reset << endl; statement clog << hconsole::green << ">> end" << hconsole::reset << endl;
#define TUT_INVOKE( statement ) do { clog << hconsole::brightcyan << ">> " << #statement << hconsole::reset << endl; do { statement } while ( 0 ); clog << hconsole::cyan << ">> end" << hconsole::reset << endl; } while ( 0 )
#define TUT_EVAL( statement ) do { clog << hconsole::brightcyan << ">> " << #statement << hconsole::reset << " = " << hconsole::yellow << ( statement ) << hconsole::reset << endl; } while ( 0 )

template<typename T1, typename T2>
bool operator == ( yaal::hcore::HArray<T1> const& a, std::vector<T2> const& v ) {
	return ( yaal::safe_equal( a.begin(), a.end(), v.begin(), v.end() ) );
}

template<typename T1, typename T2>
bool operator == ( yaal::hcore::HDeque<T1> const& a, std::deque<T2> const& v ) {
	return ( yaal::safe_equal( a.begin(), a.end(), v.begin(), v.end() ) );
}

template<typename T1, typename T2>
bool operator == ( yaal::hcore::HList<T1> const& l, std::list<T2> const& sl ) {
	return ( yaal::safe_equal( l.begin(), l.end(), sl.begin(), sl.end() ) );
}

namespace std {

yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface&, std::string const& );
typedef std::ostream& ( *stream_mod_t )( std::ostream& );
yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface&, stream_mod_t const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HComplex const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HNumber const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HString const& );
template<typename first_t, typename second_t>
std::ostream& operator << ( std::ostream& os, yaal::hcore::HPair<first_t, second_t> const& p ) {
	os << "pair(" << p.first << "," << p.second << ")";
	return ( os );
}

template<typename container>
std::ostream& container_dump( std::ostream& out,
		container const& container_, char sep_, char const* const name_ ) {
	out << ( name_ ? name_ : "" );
	char sep( '(' );
	for ( typename container::const_iterator it( container_.begin() ), end( container_.end() ); it != end; ++ it, sep = sep_ )
		out << sep << *it;
	out << ")" << std::flush;
	return ( out );
}

template<typename container>
std::ostream& container_dump( std::ostream& out,
		container const& container_, char sep_ ) {
	return ( container_dump( out, container_, sep_, NULL ) );
}

template<typename container>
std::ostream& container_dump( std::ostream& out,
		container const& container_, char const* const name_  ) {
	return ( container_dump( out, container_, ' ', name_ ) );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HArray<tType> const& a ) {
	return ( container_dump( out, a, "array" ) );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HDeque<tType> const& d ) {
	return ( container_dump( out, d, "deque" ) );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HList<tType> const& l ) {
	return ( container_dump( out, l, "list" ) );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HSet<tType> const& s ) {
	return ( container_dump( out, s, "set" ) );
}

template<typename key_t, typename value_t>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HMap<key_t, value_t> const& m ) {
	return ( container_dump( out, m, "map" ) );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out, yaal::tools::HRing<tType> const& r ) {
	return ( container_dump( out, r, "ring" ) );
}

template<typename left, typename right>
std::ostream& operator << ( std::ostream& out, yaal::tools::HTwoWayMap<left, right> const& twm ) {
	return ( container_dump( out, twm, "twowaymap" ) );
}

template<typename first_t, typename second_t>
std::ostream& operator << ( std::ostream& os, std::pair<first_t, second_t> const& p ) {
	os << "pair(" << p.first << "," << p.second << ")";
	return ( os );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out, std::list<tType> const& l ) {
	out << "list(";
	yaal::copy( l.begin(), l.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( l.begin() != l.end() ) ? "\b)" : ")" ) << std::flush;
	return ( out );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out, std::vector<tType> const& v ) {
	out << "vector(";
	yaal::copy( v.begin(), v.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( v.begin() != v.end() ) ? "\b)" : ")" ) << std::flush;
	return ( out );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out, std::deque<tType> const& v ) {
	out << "deque(";
	yaal::copy( v.begin(), v.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( v.begin() != v.end() ) ? "\b)" : ")" ) << std::flush;
	return ( out );
}

template<typename tType>
std::ostream& operator << ( std::ostream& out,
		yaal::hcore::HVector<tType> const& vector_ ) {
	M_PROLOG
	int long ctr = 0, size = vector_.dim();
	out << std::fixed << "< " << std::setw ( 10 ) << std::setprecision ( 4 );
	out << vector_ [ 0 ];
	for ( ctr = 1; ctr < size; ctr ++ ) {
		out << ", " << std::setw ( 10 ) << std::setprecision ( 4 );
		out << vector_ [ ctr ];
	}
	out << " >";
	return ( out );
	M_EPILOG
}

template<typename tType>
std::ostream& operator << ( std::ostream& out,
		yaal::hcore::HMatrix<tType> const& matrix_ ) {
	M_PROLOG
	int ctr = 0, ctrLoc = 0;
	int rows = matrix_.row ( ), cols = matrix_.col ( );
#ifdef __DEBUG__
/*	out << "rows = " << rows << ", cols = " << cols << endl; */
#endif /* __DEBUG__ */
	out << "+--    ";
	for ( ctr = 1; ctr < cols; ctr ++ )
		out <<  "            ";
	out << "    --+" << std::endl;
	for ( ctr = 0; ctr < rows; ctr ++ ) {
		out << std::fixed << "| " << std::setw ( 10 ) << std::setprecision ( 4 );
		out << matrix_[ ctr ] [ 0 ];
		for ( ctrLoc = 1; ctrLoc < cols; ctrLoc ++ ) {
			out << ", " << std::setw ( 10 ) << std::setprecision ( 4 );
			out << matrix_ [ ctr ] [ ctrLoc ];
		}
		out << " |" << std::endl;
	}
	out << "+--    ";
	for ( ctr = 1; ctr < cols; ctr ++ )
		out << "            ";
	out << "    --+" << std::endl;
	return ( out );
	M_EPILOG
}

}

namespace tress {

namespace tut_helpers {

extern double long PI;
extern double long E;
extern int const _testData_[3][ 100 ];
struct inc { int _n; inc( int n ) : _n( n ){} int operator()() { return ( _n ++ ); } };
bool file_compare( yaal::hcore::HString const&, yaal::hcore::HString const& );
int long get_speed( yaal::hcore::HClock::UNIT::unit_t );

struct HSTDGlobalScopeExceptionHandlingPolicy {
	static void handle_exception( void ) __attribute__(( __noreturn__ ));
};

#ifndef __sun__
#pragma pack( push, 1 )
#else /* #ifndef __sun__ */
#pragma pack( 1 )
#endif /* #else #ifndef __sun__ */
template<typename owner_t, int const forced_size = 1>
class HInstanceTracker {
protected:
	typedef HInstanceTracker<owner_t, forced_size> this_type;
	static int _instances;
	static int _autoIncrement;
	static int _integrityFailures;
	static volatile bool _stopCopying;
	int long _id;
	std::string _origin;
	this_type* _self;
	static int const forced_size_calc = forced_size
#ifdef __MSVCXX__
				- ( static_cast<int>( sizeof ( int long ) )
					+ static_cast<int>( sizeof ( std::string ) )
					+ static_cast<int>( sizeof ( this_type* ) ) );
#else /* #ifdef __MSVCXX__ */
				- ( static_cast<int>( sizeof ( static_cast<this_type*>( NULL )->_id ) )
					+ static_cast<int>( sizeof ( static_cast<this_type*>( NULL )->_origin ) )
					+ static_cast<int>( sizeof ( static_cast<this_type*>( NULL )->_self ) ) );
#endif /* #else #ifdef __MSVCXX__ */
	char _forcedSize[ forced_size_calc > 0 ? forced_size_calc : 1 ];
public:
	HInstanceTracker( int long = yaal::meta::max_signed<int long>::value );
	HInstanceTracker( HInstanceTracker const& );
	HInstanceTracker& operator = ( HInstanceTracker const& );
	~HInstanceTracker( void );
	bool operator == ( HInstanceTracker const& ) const;
	bool operator != ( HInstanceTracker const& ) const;
	bool operator == ( int long ) const;
	bool operator != ( int long ) const;
	bool operator < ( HInstanceTracker const& ) const;
	bool operator < ( int long ) const;
	bool operator > ( HInstanceTracker const& ) const;
	bool operator > ( int long ) const;
	static int get_instance_count( void );
	static int get_integrity_failures( void );
	static void set_instance_count( int = 0 );
	static void set_start_id( int = 0 );
	int long get_id( void ) const;
	int long id( void ) const;
	bool is_self( void ) const;
	yaal::hcore::HString to_string( void ) const;
	void swap( HInstanceTracker& );
	static void stop_copying( void ) {
		_stopCopying = true;
	}
	static void allow_copying( void ) {
		_stopCopying = false;
	}
};
#ifndef __sun__
#pragma pack( pop )
#else /* #ifndef __sun__ */
#pragma pack()
#endif /* #else #ifndef __sun__ */

template<typename T>
struct simple_mock {
	typedef HInstanceTracker<T> item_t;
	typedef yaal::hcore::HList<item_t> list_t;
	typedef yaal::hcore::HArray<item_t> array_t;
	typedef yaal::hcore::HDeque<item_t> deque_t;
	typedef yaal::hcore::HSet<item_t> set_t;
	typedef yaal::tools::HRing<item_t> ring_t;
	typedef yaal::hcore::HList<int> int_list_t;
	typedef yaal::hcore::HArray<int> int_array_t;
	typedef yaal::hcore::HDeque<int> int_deque_t;
	typedef yaal::hcore::HSet<int> int_set_t;
	typedef yaal::tools::HRing<int> int_ring_t;
	typedef std::list<int> std_list_t;
	typedef std::vector<int> std_vector_t;
	typedef std::deque<int> std_deque_t;
	typedef std::set<int> std_set_t;
	virtual ~simple_mock( void ) {}
	virtual void time_constraint_exempt( void ) = 0;
};

class Stringifier {
	yaal::hcore::HString _cache;
public:
	Stringifier( void )
		: _cache()
		{}
	template<typename collection_t>
	yaal::hcore::HString& to_string( collection_t const& coll_ ) {
		_cache.clear();
		for ( typename collection_t::const_iterator it( coll_.begin() ), end( coll_.end() ); it != end; ++ it )
			_cache += *it;
		return ( _cache );
	}
	template<typename T, typename collection_t>
	yaal::hcore::HString& to_string( collection_t const& coll_ ) {
		_cache.clear();
		for ( typename collection_t::const_iterator it( coll_.begin() ), end( coll_.end() ); it != end; ++ it )
			_cache += static_cast<T>( *it );
		return ( _cache );
	}
};

template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::_instances = 0;
template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::_autoIncrement = 0;
template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::_integrityFailures = 0;
template<typename owner_t, int const forced_size>
volatile bool HInstanceTracker<owner_t, forced_size>::_stopCopying = false;

template<typename owner_t, int const forced_size>
HInstanceTracker<owner_t, forced_size>::HInstanceTracker( int long id_ )
	: _id( id_ != yaal::meta::max_signed<int long>::value ? id_ : _autoIncrement ),
	_origin(), _self( this ), _forcedSize() {
	++ _instances;
	++ _autoIncrement;
}

template<typename owner_t, int const forced_size>
HInstanceTracker<owner_t, forced_size>::HInstanceTracker( HInstanceTracker const& itrck )
	: _id( itrck._id ),
	_origin( itrck._origin + ":" + yaal::hcore::HString( itrck._id ).c_str() ), _self( this ), _forcedSize() {
	if ( _stopCopying )
		throw std::runtime_error( "Copy constructor invoked!" );
	++ _instances;
	++ _autoIncrement;
}

template<typename owner_t, int const forced_size>
HInstanceTracker<owner_t, forced_size>::~HInstanceTracker( void ) {
	-- _instances;
	if ( this != _self )
		++ _integrityFailures;
}

template<typename owner_t, int const forced_size>
HInstanceTracker<owner_t, forced_size>& HInstanceTracker<owner_t, forced_size>::operator = ( HInstanceTracker const& itrck ) {
	if ( _stopCopying )
		throw std::runtime_error( "Assignment operator invoked!" );
	if ( &itrck != this ) {
		HInstanceTracker<owner_t, forced_size> tmp( itrck );
		swap( tmp );
	}
	return ( *this );
}

template<typename owner_t, int const forced_size>
void HInstanceTracker<owner_t, forced_size>::swap( HInstanceTracker& itrck ) {
	if ( &itrck != this ) {
		using yaal::swap;
		swap( _id, itrck._id );
		swap( _origin, itrck._origin );
	}
	return;
}

template<typename owner_t, int const forced_size>
void HInstanceTracker<owner_t, forced_size>::set_instance_count( int count_ ) {
	_instances = count_;
}

template<typename owner_t, int const forced_size>
void HInstanceTracker<owner_t, forced_size>::set_start_id( int startId_ ) {
	_autoIncrement = startId_;
}

template<typename owner_t, int const forced_size>
yaal::hcore::HString HInstanceTracker<owner_t, forced_size>::to_string( void ) const {
	yaal::tools::HStringStream ss;
	ss << "HInstanceTracker<" << yaal::hcore::demangle( typeid( owner_t ).name() ) << ">(" << _origin << ":" << _id << ")";
	return ( ss.string() );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::operator == ( int long val ) const {
	return ( val == _id );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::operator != ( int long val ) const {
	return ( val != _id );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::operator == ( HInstanceTracker const& val ) const {
	return ( val._id == _id );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::operator != ( HInstanceTracker const& val ) const {
	return ( val._id != _id );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::operator < ( HInstanceTracker const& val ) const {
	return ( _id < val._id );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::operator < ( int long val ) const {
	return ( _id < val );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::operator > ( HInstanceTracker const& val ) const {
	return ( _id > val._id );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::operator > ( int long val ) const {
	return ( _id > val );
}

template<typename owner_t, int const forced_size>
bool HInstanceTracker<owner_t, forced_size>::is_self( void ) const {
	return ( _self == this );
}

template<typename owner_t, int const forced_size>
bool operator == ( int long left, HInstanceTracker<owner_t, forced_size> const& right ) {
	return ( left == right.get_id() );
}

template<typename owner_t, int const forced_size>
bool operator != ( int long left, HInstanceTracker<owner_t, forced_size> const& right ) {
	return ( left != right.get_id() );
}

template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::get_instance_count( void ) {
	return ( _instances );
}

template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::get_integrity_failures( void ) {
	return ( _integrityFailures );
}

template<typename owner_t, int const forced_size>
int long HInstanceTracker<owner_t, forced_size>::get_id( void ) const {
	return ( _id );
}

template<typename owner_t, int const forced_size>
int long HInstanceTracker<owner_t, forced_size>::id( void ) const {
	return ( _id );
}

template<typename owner_t, int const forced_size>
yaal::hcore::HString& operator += ( yaal::hcore::HString& str, HInstanceTracker<owner_t, forced_size> const& itrck ) {
	str += itrck.to_string();
	return ( str );
}

template<typename owner_t, int const forced_size>
std::ostream& operator << ( std::ostream& stream, HInstanceTracker<owner_t, forced_size> const& itrck ) {
	stream << itrck.to_string();
	return ( stream );
}

template<typename owner_t, int const forced_size>
yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& stream, HInstanceTracker<owner_t, forced_size> const& itrck ) {
	stream << itrck.to_string();
	return ( stream );
}

}

template<typename owner_t, int const forced_size>
inline void swap( tress::tut_helpers::HInstanceTracker<owner_t, forced_size>& a, tress::tut_helpers::HInstanceTracker<owner_t, forced_size>& b ) {
	a.swap( b );
}

}

#endif /* not TRESS_TUT_HELPERS_HXX_INCLUDED */

