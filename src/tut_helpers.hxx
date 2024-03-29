/* Read tress/LICENSE.md file for copyright and licensing information. */

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
#include <yaal/hcore/hhashset.hxx>
#include <yaal/hcore/hhashmap.hxx>
#include <yaal/hcore/hlist.hxx>
#include <yaal/hcore/hstaticarray.hxx>
#include <yaal/hcore/hvector.hxx>
#include <yaal/hcore/hmatrix.hxx>
#include <yaal/hcore/hclock.hxx>
#include <yaal/tools/hstringstream.hxx>
#include <yaal/tools/hring.hxx>
#include <yaal/tools/htwowaymap.hxx>
#include <yaal/tools/ansi.hxx>

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

#define TUT_UNIT_TEST( ... ) M_MACRO_ARGC( TUT_UNIT_TEST_, __VA_ARGS__ )
#define TUT_UNIT_TEST_1( title ) TUT_UNIT_TEST_2( __COUNTER__, title )
#define TUT_UNIT_TEST_2( no, title ) \
namespace { static int const M_CONCAT( dropIt, __LINE__ ) __attribute__(( __used__ )) = group.register_test( no, title ); } \
template<> template<> void module::test<(no)>( void ) { do { set_test_meta( title, __FILE__, __LINE__ ); } while ( 0 );
#define TUT_TEARDOWN() }
#define TUT_TEST_GROUP( ... ) M_MACRO_ARGC( TUT_TEST_GROUP_, __VA_ARGS__ )
#define TUT_TEST_GROUP_2( mock, name ) \
typedef test_group<mock> tut_group; \
TUT_TEST_GROUP_BODY( mock, name )
#define TUT_TEST_GROUP_3( mock, name, number ) \
typedef test_group<mock, number> tut_group; \
TUT_TEST_GROUP_BODY( mock, name )
#define TUT_TEST_GROUP_BODY( mock, name ) \
typedef tut_group::object module; \
typedef yaal::hcore::HExceptionSafeGlobal<tut_group, tress::tut_helpers::HSTDGlobalScopeExceptionHandlingPolicy> tut_group_holder; \
tut_group_holder mock##_group( ( name ) ); \
namespace { tut_group& group( mock##_group.instance() ); } \
typedef void M_CONCAT( void_type, __COUNTER__ )
#define TUT_SIMPLE_MOCK( name ) struct name : public simple_mock<name> { \
	virtual ~name( void ) \
		{} \
}
#define TIME_CONSTRAINT_EXEMPT time_constraint_exempt

#define TUT_DECLARE( statement ) clog << ansi::brightgreen << ">> " << #statement << ansi::reset << endl; this->set_current_line( __LINE__ ); statement; this->set_current_line( __LINE__ + 1 ); clog << ansi::green << ">> end" << ansi::reset << endl;
#define TUT_INVOKE( statement ) do { clog << ansi::brightcyan << ">> " << #statement << ansi::reset << endl; do { this->set_current_line( __LINE__ ); statement; this->set_current_line( __LINE__ + 1 ); } while ( 0 ); clog << ansi::cyan << ">> end" << ansi::reset << endl; } while ( 0 )
#define TUT_EVAL( statement ) do { this->set_current_line( __LINE__ ); clog << ansi::brightcyan << ">> " << #statement << ansi::reset << " = " << ansi::yellow << ( statement ) << ansi::reset << endl; this->set_current_line( __LINE__ + 1 ); } while ( 0 )

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

namespace yaal {
namespace hcore {
class HComplex;
class HNumber;
class HTime;
}
}

template<typename T1, typename T2>
bool operator == ( yaal::hcore::HList<T1> const& l, std::vector<T2> const& sl ) {
	return ( yaal::safe_equal( l.begin(), l.end(), sl.begin(), sl.end() ) );
}

namespace std {

yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface&, std::string const& );
typedef std::ostream& ( *stream_mod_t )( std::ostream& );
inline yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& os, stream_mod_t const& mod ) {
	if ( mod == static_cast<stream_mod_t const&>( std::endl ) ) {
		os << yaal::hcore::endl;
	} else if ( mod == static_cast<stream_mod_t const&>( std::flush ) ) {
		os << yaal::hcore::flush;
	} else {
		M_ASSERT( !"unsupported stream modifier"[0] );
	}
	return os;
}
std::ostream& operator << ( std::ostream&, yaal::hcore::HComplex const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HNumber const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HString const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HUTF8String const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HTime const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::time::duration_t const& );

template<typename first_t, typename second_t>
std::ostream& operator << ( std::ostream& os, yaal::hcore::HPair<first_t, second_t> const& p ) {
	os << "pair(" << p.first << "," << p.second << ")";
	return os;
}

template<typename container>
std::ostream& container_dump( std::ostream& out,
		container const& container_, char sep_, char const* const name_ ) {
	out << ( name_ ? name_ : "" );
	char sep( '(' );
	for ( typename container::const_iterator it( container_.begin() ), end( container_.end() ); it != end; ++ it, sep = sep_ )
		out << sep << *it;
	if ( container_.empty() )
		out << sep;
	out << ")" << std::flush;
	return out;
}

template<typename container>
std::ostream& container_dump( std::ostream& out,
		container const& container_, char sep_ ) {
	return ( container_dump( out, container_, sep_, nullptr ) );
}

template<typename container>
inline std::ostream& container_dump( std::ostream& out,
		container const& container_, char const* const name_  ) {
	return ( container_dump( out, container_, ' ', name_ ) );
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HArray<tType> const& a ) {
	return ( container_dump( out, a, "array" ) );
}

template<typename tType, int const N>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HStaticArray<tType, N> const& sa ) {
	return ( container_dump( out, sa, "staticarray" ) );
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HDeque<tType> const& d ) {
	return ( container_dump( out, d, "deque" ) );
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HList<tType> const& l ) {
	return ( container_dump( out, l, "list" ) );
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HSet<tType> const& s ) {
	return ( container_dump( out, s, "set" ) );
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HHashSet<tType> const& hs ) {
	return ( container_dump( out, hs, "hash_set" ) );
}

template<typename key_t, typename value_t>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HMap<key_t, value_t> const& m ) {
	return ( container_dump( out, m, "map" ) );
}

template<typename key_t, typename value_t>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HLookupMap<key_t, value_t> const& m ) {
	return ( container_dump( out, m, "lookup_map" ) );
}

template<typename key_t, typename value_t>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HHashMap<key_t, value_t> const& m ) {
	return ( container_dump( out, m, "hash_map" ) );
}

template<typename key_t, typename value_t>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HOrderedHashMap<key_t, value_t> const& m ) {
	return ( container_dump( out, m, "ordered_hash_map" ) );
}

template<typename key_t>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HOrderedHashSet<key_t> const& m ) {
	return ( container_dump( out, m, "ordered_hash_set" ) );
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, yaal::tools::HRing<tType> const& r ) {
	return ( container_dump( out, r, "ring" ) );
}

template<typename left, typename right>
inline std::ostream& operator << ( std::ostream& out, yaal::tools::HTwoWayMap<left, right> const& twm ) {
	return ( container_dump( out, twm, "twowaymap" ) );
}

template<typename type, typename tag>
inline std::ostream& operator << ( std::ostream& out, yaal::hcore::HTaggedPOD<type, tag> const& tp_ ) {
	out << tp_.get();
	return out;
}

template<typename first_t, typename second_t>
inline std::ostream& operator << ( std::ostream& os, std::pair<first_t, second_t> const& p ) {
	os << "pair(" << p.first << "," << p.second << ")";
	return os;
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, std::list<tType> const& l ) {
	out << "list(";
	yaal::copy( l.begin(), l.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( l.begin() != l.end() ) ? "\b)" : ")" ) << std::flush;
	return out;
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, std::vector<tType> const& v ) {
	out << "vector(";
	yaal::copy( v.begin(), v.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( v.begin() != v.end() ) ? "\b)" : ")" ) << std::flush;
	return out;
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out, std::deque<tType> const& v ) {
	out << "deque(";
	yaal::copy( v.begin(), v.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( v.begin() != v.end() ) ? "\b)" : ")" ) << std::flush;
	return out;
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out,
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
	return out;
	M_EPILOG
}

template<typename tType>
inline std::ostream& operator << ( std::ostream& out,
		yaal::hcore::HMatrix<tType> const& matrix_ ) {
	M_PROLOG
	int ctr = 0, ctrLoc = 0;
	int rows( matrix_.rows() );
	int cols( matrix_.columns() );
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
	return out;
	M_EPILOG
}

}

namespace tress {

namespace tut_helpers {

#if defined( _MSC_VER ) || defined( __HOST_OS_TYPE_CYGWIN__ )
static double long const epsilon = 0.00001L;
#else /* #if defined( _MSC_VER ) || defined( __HOST_OS_TYPE_CYGWIN__ ) */
static double long const epsilon = 0.000001L;
#endif /* #else #if defined( _MSC_VER ) || defined( __HOST_OS_TYPE_CYGWIN__ ) */
extern int const _testData_[3][ 100 ];
struct inc { int _n; inc( int n ) : _n( n ){} int operator()() { return ( _n ++ ); } };
bool file_binary_compare( yaal::hcore::HString const&, yaal::hcore::HString const& );
int long get_speed( yaal::hcore::time::UNIT );

struct HSTDGlobalScopeExceptionHandlingPolicy {
	static void handle_exception( void ) __attribute__(( __noreturn__ ));
};

#ifndef __HOST_OS_TYPE_RASPBIAN__
#ifndef __sun__
#pragma pack( push, 1 )
#else /* #ifndef __sun__ */
#pragma pack( 1 )
#endif /* #else #ifndef __sun__ */
#endif /* #ifndef __HOST_OS_TYPE_RASPBIAN__ */
template<int const size>
struct Sizer {
	char _buf[yaal::trait::to_unsigned<int, size>::value];
};
template<typename owner_t, int const forced_size = 1>
class HInstanceTracker {
protected:
	typedef HInstanceTracker<owner_t, forced_size> this_type;
	typedef owner_t owner_type;
	static int _copyCount;
	static int _moveCount;
	static int _instances;
	static int _autoIncrement;
	static int _integrityFailures;
	static volatile bool _stopCopying;
	int long _id;
	std::string _origin;
	this_type* _self;
	static int const forced_size_calc = forced_size
				- ( static_cast<int>( sizeof ( int long ) )
					+ static_cast<int>( sizeof ( std::string ) )
					+ static_cast<int>( sizeof ( this_type* ) ) );
	Sizer<(forced_size_calc > 0 ? forced_size_calc : 1)> _forcedSize;
public:
	HInstanceTracker( int long id_ = yaal::meta::max_signed<int long>::value )
		: _id( id_ != yaal::meta::max_signed<int long>::value ? id_ : _autoIncrement )
		, _origin()
		, _self( this )
		, _forcedSize() {
		++ _instances;
		++ _autoIncrement;
	}
	HInstanceTracker( HInstanceTracker const& itrck )
		: _id( itrck._id )
		, _origin( itrck._origin + ":" + std::to_string( itrck._id ) )
		, _self( this )
		, _forcedSize() {
		if ( _stopCopying ) {
			throw std::runtime_error( "Copy constructor invoked!" );
		}
		++ _instances;
		++ _autoIncrement;
		++ _copyCount;
	}
	HInstanceTracker( HInstanceTracker&& itrck ) noexcept
		: _id( itrck._id )
		, _origin( itrck._origin + "'" )
		, _self( this )
		, _forcedSize() {
		++ _instances;
		++ _autoIncrement;
		++ _moveCount;
		itrck._id = -1;
		itrck._origin = "INVALID";
	}
	HInstanceTracker& operator = ( HInstanceTracker const& itrck ) {
		if ( _stopCopying ) {
			throw std::runtime_error( "Assignment operator invoked!" );
		}
		if ( &itrck != this ) {
			HInstanceTracker<owner_t, forced_size> tmp( itrck );
			swap( tmp );
			++ _copyCount;
		}
		return ( *this );
	}
	HInstanceTracker& operator = ( HInstanceTracker&& itrck ) {
		if ( &itrck != this ) {
			swap( itrck );
			itrck._id = -1;
			itrck._origin = "INVALID";
			++ _moveCount;
		}
		return ( *this );
	}
	~HInstanceTracker( void ) {
		-- _instances;
		if ( this != _self ) {
			++ _integrityFailures;
		}
	}
	bool operator == ( HInstanceTracker const& val ) const {
		return ( val._id == _id );
	}
	bool operator == ( int long val ) const {
		return ( val == _id );
	}
	bool operator != ( HInstanceTracker const& val ) const {
		return ( val._id != _id );
	}
	bool operator != ( int long val ) const {
		return ( val != _id );
	}
	bool operator < ( HInstanceTracker const& val ) const {
		return ( _id < val._id );
	}
	bool operator < ( int long val ) const {
		return ( _id < val );
	}
	bool operator > ( HInstanceTracker const& val ) const {
		return ( _id > val._id );
	}
	bool operator > ( int long val ) const {
		return ( _id > val );
	}
	static int get_instance_count( void ) {
		return ( _instances );
	}
	static int get_copy_count( void ) {
		return ( _copyCount );
	}
	static int get_move_count( void ) {
		return ( _moveCount );
	}
	static int get_integrity_failures( void ) {
		return ( _integrityFailures );
	}
	static void set_instance_count( int count_ ) {
		_instances = count_;
	}
	static void set_start_id( int startId_ ) {
		_autoIncrement = startId_;
	}
	static void reset( void ) {
		set_instance_count( 0 );
		set_start_id( 0 );
		_copyCount = 0;
		_moveCount = 0;
	}
	int long get_id( void ) const {
		return ( _id );
	}
	int long id( void ) const {
		return ( _id );
	}
	bool is_self( void ) const {
		return ( _self == this );
	}
	yaal::hcore::HString to_string( void ) const {
		yaal::tools::HStringStream ss;
		ss << "HInstanceTracker<" << yaal::hcore::demangle( typeid( owner_t ).name() ) << ">(" << _origin << ":" << _id << ")";
		return ( ss.string() );
	}
	void swap( HInstanceTracker& itrck ) {
		if ( &itrck != this ) {
			using yaal::swap;
			swap( _id, itrck._id );
			swap( _origin, itrck._origin );
		}
		return;
	}
	static void stop_copying( void ) {
		_stopCopying = true;
	}
	static void allow_copying( void ) {
		_stopCopying = false;
	}
};
#ifndef __HOST_OS_TYPE_RASPBIAN__
#ifndef __sun__
#pragma pack( pop )
#else /* #ifndef __sun__ */
#pragma pack()
#endif /* #else #ifndef __sun__ */
#endif /* #ifndef __HOST_OS_TYPE_RASPBIAN__ */

template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::_copyCount = 0;
template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::_moveCount = 0;
template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::_instances = 0;
template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::_autoIncrement = 0;
template<typename owner_t, int const forced_size>
int HInstanceTracker<owner_t, forced_size>::_integrityFailures = 0;
template<typename owner_t, int const forced_size>
volatile bool HInstanceTracker<owner_t, forced_size>::_stopCopying = false;

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
	typedef yaal::hcore::HHashSet<int> int_hash_set_t;
	typedef yaal::tools::HRing<int> int_ring_t;
	typedef std::list<int> std_list_t;
	typedef std::vector<int> std_vector_t;
	typedef std::deque<int> std_deque_t;
	typedef std::set<int> std_set_t;
	virtual ~simple_mock( void ) {}
	virtual void time_constraint_exempt( void ) = 0;
	virtual void set_current_line( int ) = 0;
};

class HEventDetector {
	yaal::hcore::HMutex _mutex;
	yaal::hcore::HCondition _condition;
	bool _detected;
public:
	HEventDetector( void );
	void signal( void );
	bool wait( yaal::hcore::time::duration_t );
	void reset( void );
};

}

}

namespace yaal {
namespace hcore {

template<typename T>
typename T::to_string_type to_string( tress::tut_helpers::HInstanceTracker<T> const& it_ ) {
	return ( static_cast<typename T::to_string_type>( it_.get_id() ) );
}

}
}

namespace tress {

namespace tut_helpers {

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
			_cache += yaal::hcore::to_string( *it );
		return ( _cache );
	}
	template<typename T, typename collection_t>
	yaal::hcore::HString& to_string( collection_t const& coll_ ) {
		_cache.clear();
		for ( typename collection_t::const_iterator it( coll_.begin() ), end( coll_.end() ); it != end; ++ it )
			_cache += yaal::hcore::to_string( static_cast<T>( *it ) );
		return ( _cache );
	}
};

template<typename T, typename RT = T>
struct defer {
	static void set( T& lval_, RT rval_ ) {
		lval_ = rval_;
	}
	static void set_alt( T& lval_, RT rval_ ) {
		lval_ = -rval_;
	}
	static void add( T& lval_, RT rval_ ) {
		lval_ += rval_;
	}
	static void sub( T& lval_, RT rval_ ) {
		lval_ -= rval_;
	}
	static void mul( T& lval_, RT rval_ ) {
		lval_ *= rval_;
	}
	static void div( T& lval_, RT rval_ ) {
		lval_ /= rval_;
	}
};

template<typename owner_t, int const forced_size>
bool operator == ( int long left, HInstanceTracker<owner_t, forced_size> const& right ) {
	return ( left == right.get_id() );
}

template<typename owner_t, int const forced_size>
bool operator != ( int long left, HInstanceTracker<owner_t, forced_size> const& right ) {
	return ( left != right.get_id() );
}

template<typename owner_t, int const forced_size>
yaal::hcore::HString& operator += ( yaal::hcore::HString& str, HInstanceTracker<owner_t, forced_size> const& itrck ) {
	str += itrck.to_string();
	return str;
}

template<typename owner_t, int const forced_size>
std::ostream& operator << ( std::ostream& stream, HInstanceTracker<owner_t, forced_size> const& itrck ) {
	stream << itrck.to_string();
	return stream;
}

template<typename owner_t, int const forced_size>
yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& stream, HInstanceTracker<owner_t, forced_size> const& itrck ) {
	stream << itrck.to_string();
	return stream;
}

template<typename owner_t, int const forced_size>
inline void swap( tress::tut_helpers::HInstanceTracker<owner_t, forced_size>& a, tress::tut_helpers::HInstanceTracker<owner_t, forced_size>& b ) {
	a.swap( b );
}

}

}

#endif /* not TRESS_TUT_HELPERS_HXX_INCLUDED */

