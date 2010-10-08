/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_helpers.hxx - this file is integral part of `tress' project.

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

#ifndef TRESS_TUT_HELPERS_HXX_INCLUDED
#define TRESS_TUT_HELPERS_HXX_INCLUDED

#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <list>
#include <vector>

#include <yaal/hcore/hstreaminterface.hxx>
#include <yaal/hcore/hpair.hxx>
#include <yaal/hcore/harray.hxx>
#include <yaal/hcore/hlist.hxx>
#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/hvector.hxx>
#include <yaal/hcore/hmatrix.hxx>
#include <yaal/hcore/xalloc.hxx>
#include <yaal/tools/hstringstream.hxx>

#if defined( __GNUC__ ) && ! defined( stdext )
#define stdext __gnu_cxx
#endif /* defined( __GNUC__ ) && ! defined( stdext ) */

namespace yaal
{

namespace hcore
{

template<typename first_t, typename second_t>
yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& os, yaal::hcore::HPair<first_t, second_t> const& p )
	{
	os << "pair(" << p.first << "," << p.second << ")";
	return ( os );
	}

template<typename tType>
yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& out, yaal::hcore::HArray<tType> const& a )
	{
	out << "array(";
	yaal::copy( a.begin(), a.end(), stream_iterator( out, " " ) );
	out << ( ( a.begin() != a.end() ) ? "\b)" : ")" ) << flush;
	return ( out );
	}

template<typename tType>
yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& out, yaal::hcore::HList<tType> const& l )
	{
	out << "list(";
	yaal::copy( l.begin(), l.end(), stream_iterator( out, " " ) );
	out << "\b)" << flush;
	out << ( ( l.begin() != l.end() ) ? "\b)" : ")" ) << flush;
	return ( out );
	}

}

}

template<typename T1, typename T2>
bool operator == ( yaal::hcore::HArray<T1> const& a, std::vector<T2> const& v )
	{
	return ( yaal::safe_equal( a.begin(), a.end(), v.begin(), v.end() ) );
	}

template<typename T1, typename T2>
bool operator == ( yaal::hcore::HList<T1> const& l, std::list<T2> const& sl )
	{
	return ( yaal::safe_equal( l.begin(), l.end(), sl.begin(), sl.end() ) );
	}

namespace std
{

std::ostream& operator << ( std::ostream&, yaal::hcore::HComplex const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HNumber const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HString const& );
template<typename first_t, typename second_t>
std::ostream& operator << ( std::ostream& os, yaal::hcore::HPair<first_t, second_t> const& p )
	{
	os << "pair(" << p.first << "," << p.second << ")";
	return ( os );
	}

template<typename tType>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HArray<tType> const& a )
	{
	out << "array(";
	yaal::copy( a.begin(), a.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( a.begin() != a.end() ) ? "\b)" : ")" ) << std::flush;
	return ( out );
	}

template<typename tType>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HList<tType> const& l )
	{
	out << "list(";
	yaal::copy( l.begin(), l.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( l.begin() != l.end() ) ? "\b)" : ")" ) << std::flush;
	return ( out );
	}

template<typename first_t, typename second_t>
std::ostream& operator << ( std::ostream& os, std::pair<first_t, second_t> const& p )
	{
	os << "pair(" << p.first << "," << p.second << ")";
	return ( os );
	}

template<typename tType>
std::ostream& operator << ( std::ostream& out, std::list<tType> const& l )
	{
	out << "list(";
	yaal::copy( l.begin(), l.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( l.begin() != l.end() ) ? "\b)" : ")" ) << std::flush;
	return ( out );
	}

template<typename tType>
std::ostream& operator << ( std::ostream& out, std::vector<tType> const& v )
	{
	out << "vector(";
	yaal::copy( v.begin(), v.end(), std::ostream_iterator<tType>( out, " " ) );
	out << ( ( v.begin() != v.end() ) ? "\b)" : ")" ) << std::flush;
	return ( out );
	}

template<typename tType>
std::ostream& operator << ( std::ostream& out,
		yaal::hcore::HVector<tType> const& vector_ )
	{
	M_PROLOG
	int long ctr = 0, size = vector_.dim();
	out << std::fixed << "< " << std::setw ( 10 ) << std::setprecision ( 4 );
	out << vector_ [ 0 ];
	for ( ctr = 1; ctr < size; ctr ++ )
		{
		out << ", " << std::setw ( 10 ) << std::setprecision ( 4 );
		out << vector_ [ ctr ];
		}
	out << " >";
	return ( out );
	M_EPILOG
	}

template<typename tType>
std::ostream& operator << ( std::ostream& out,
		yaal::hcore::HMatrix<tType> const& matrix_ )
	{
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
	for ( ctr = 0; ctr < rows; ctr ++ )
		{
		out << std::fixed << "| " << std::setw ( 10 ) << std::setprecision ( 4 );
		out << matrix_[ ctr ] [ 0 ];
		for ( ctrLoc = 1; ctrLoc < cols; ctrLoc ++ )
			{
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

namespace tress
{

namespace tut_helpers
{

class HLogger
	{
protected:
	/*{*/
	/*}*/
public:
	/*{*/
	HLogger( void );
	HLogger& operator << ( std::string const& );
	HLogger& operator << ( int );
	HLogger& operator << ( std::ostream& ( * const )( std::ostream& ) );
	/*}*/
protected:
	/*{*/
	/*}*/
	};

yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface&, std::string const& );
struct inc { int _n; inc( int n ) : _n( n ){} int operator()() { return ( _n ++ ); } };
bool file_compare( yaal::hcore::HString const&, yaal::hcore::HString const& );

void show_title( char const* const );
void show_end( void );

struct HSTDGlobalScopeExceptionHandlingPolicy
	{
	static void handle_exception( void ) __attribute__(( __noreturn__ ));
	};

#define TUT_UNIT_TEST_N( no, title ) template<> template<> void module::test<(no)>( void ) { do { set_test_meta( title, __FILE__, __LINE__ ); show_title( title ); } while ( 0 );
#define TUT_UNIT_TEST( title ) TUT_UNIT_TEST_N( ( __COUNTER__ ), ( title ) )
#define TUT_TEARDOWN() show_end(); }
#define TUT_TEST_GROUP_N( mock, name ) \
typedef test_group<mock> tut_group; \
typedef tut_group::object module; \
typedef yaal::hcore::HExceptionSafeGlobal<tut_group, tress::tut_helpers::HSTDGlobalScopeExceptionHandlingPolicy> tut_group_holder; \
tut_group_holder tut_##mock##_group( ( name ) )
#define TUT_TEST_GROUP( mock, name ) \
TUT_TEST_GROUP_N( mock, name ) \
namespace { static int const dropIt __attribute__(( __used__ )) = __COUNTER__; }
#define TUT_SIMPLE_MOCK( name ) struct name \
	{ \
	virtual ~name( void ) \
		{} \
	}

#define TUT_DECLARE( statement ) clog << brightgreen << ">> " << #statement << reset << endl; statement clog << green << ">> end" << reset << endl;
#define TUT_INVOKE( statement ) do { clog << brightcyan << ">> " << #statement << reset << endl; do { statement } while ( 0 ); clog << cyan << ">> end" << reset << endl; } while ( 0 )

template<typename owner_t>
class HInstanceTracker
	{
	typedef HInstanceTracker<owner_t> this_type;
	static int _instances;
	static int _autoIncrement;
	int long _id;
	yaal::hcore::HString _origin;
	this_type* _self;
public:
	HInstanceTracker( int long = yaal::meta::max_signed<int long>::value );
	HInstanceTracker( HInstanceTracker const& );
	HInstanceTracker& operator = ( HInstanceTracker const& );
	~HInstanceTracker( void );
	bool operator == ( HInstanceTracker<owner_t> const& ) const;
	bool operator != ( HInstanceTracker<owner_t> const& ) const;
	bool operator == ( int long ) const;
	bool operator != ( int long ) const;
	static int get_instance_count( void );
	static void set_instance_count( int = 0 );
	static void set_start_id( int = 0 );
	int long get_id( void ) const;
	int long id( void ) const;
	bool is_self( void ) const;
	yaal::hcore::HString to_string( void ) const;
	void swap( HInstanceTracker& );
	};

template<typename owner_t>
int HInstanceTracker<owner_t>::_instances = 0;
template<typename owner_t>
int HInstanceTracker<owner_t>::_autoIncrement = 0;

template<typename owner_t>
HInstanceTracker<owner_t>::HInstanceTracker( int long id_ ) : _id( id_ != yaal::meta::max_signed<int long>::value ? id_ : _autoIncrement ), _origin(), _self( this )
	{
	++ _instances;
	++ _autoIncrement;
	}

template<typename owner_t>
HInstanceTracker<owner_t>::HInstanceTracker( HInstanceTracker const& itrck )
	: _id( itrck._id ),
	_origin( itrck._origin + ":" + itrck._id ), _self( this )
	{
	++ _instances;
	++ _autoIncrement;
	}

template<typename owner_t>
HInstanceTracker<owner_t>::~HInstanceTracker( void )
	{
	-- _instances;
	}

template<typename owner_t>
HInstanceTracker<owner_t>& HInstanceTracker<owner_t>::operator = ( HInstanceTracker const& itrck )
	{
	if ( &itrck != this )
		{
		HInstanceTracker<owner_t> tmp( itrck );
		swap( tmp );
		}
	return ( *this );
	}

template<typename owner_t>
void HInstanceTracker<owner_t>::swap( HInstanceTracker& itrck )
	{
	if ( &itrck != this )
		{
		using yaal::swap;
		swap( _id, itrck._id );
		swap( _origin, itrck._origin );
		}
	return;
	}

template<typename owner_t>
void HInstanceTracker<owner_t>::set_instance_count( int count_ )
	{
	_instances = count_;
	}

template<typename owner_t>
void HInstanceTracker<owner_t>::set_start_id( int startId_ )
	{
	_autoIncrement = startId_;
	}

template<typename owner_t>
yaal::hcore::HString HInstanceTracker<owner_t>::to_string( void ) const
	{
	yaal::tools::HStringStream ss;
	ss << "HInstanceTracker<" << yaal::hcore::demangle( typeid( owner_t ).name() ) << ">(" << _origin << ":" << _id << ")";
	return ( ss.string() );
	}

template<typename owner_t>
bool HInstanceTracker<owner_t>::operator == ( int long val ) const
	{
	return ( val == _id );
	}

template<typename owner_t>
bool HInstanceTracker<owner_t>::operator != ( int long val ) const
	{
	return ( val != _id );
	}

template<typename owner_t>
bool HInstanceTracker<owner_t>::operator == ( HInstanceTracker<owner_t> const& val ) const
	{
	return ( val._id == _id );
	}

template<typename owner_t>
bool HInstanceTracker<owner_t>::operator != ( HInstanceTracker<owner_t> const& val ) const
	{
	return ( val._id != _id );
	}

template<typename owner_t>
bool HInstanceTracker<owner_t>::is_self( void ) const
	{
	return ( _self == this );
	}

template<typename owner_t>
bool operator == ( int long left, HInstanceTracker<owner_t> const& right )
	{
	return ( left == right.get_id() );
	}

template<typename owner_t>
bool operator != ( int long left, HInstanceTracker<owner_t> const& right )
	{
	return ( left != right.get_id() );
	}

template<typename owner_t>
int HInstanceTracker<owner_t>::get_instance_count( void )
	{
	return ( _instances );
	}

template<typename owner_t>
int long HInstanceTracker<owner_t>::get_id( void ) const
	{
	return ( _id );
	}

template<typename owner_t>
int long HInstanceTracker<owner_t>::id( void ) const
	{
	return ( _id );
	}

template<typename owner_t>
yaal::hcore::HString& operator += ( yaal::hcore::HString& str, HInstanceTracker<owner_t> const& itrck )
	{
	str += itrck.to_string();
	return ( str );
	}

template<typename owner_t>
std::ostream& operator << ( std::ostream& stream, HInstanceTracker<owner_t> const& itrck )
	{
	stream << itrck.to_string();
	return ( stream );
	}

template<typename owner_t>
yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& stream, HInstanceTracker<owner_t> const& itrck )
	{
	stream << itrck.to_string();
	return ( stream );
	}

}

template<typename owner_t>
inline void swap( tress::tut_helpers::HInstanceTracker<owner_t>& a, tress::tut_helpers::HInstanceTracker<owner_t>& b )
	{
	a.swap( b );
	}

}

#endif /* not TRESS_TUT_HELPERS_HXX_INCLUDED */

