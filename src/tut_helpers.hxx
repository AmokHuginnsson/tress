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
#include <iomanip>
#include <cxxabi.h>

#include <yaal/hcore/hstreaminterface.hxx>
#include <yaal/hcore/hpair.hxx>
#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/hvector.hxx>
#include <yaal/hcore/hmatrix.hxx>
#include <yaal/hcore/xalloc.hxx>
#include <yaal/tools/hstringstream.hxx>

namespace std
{

std::ostream& operator << ( std::ostream&, yaal::hcore::HComplex const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HString const& );
template<typename first_t, typename second_t>
std::ostream& operator << ( std::ostream& os, yaal::hcore::HPair<first_t, second_t> const& p )
	{
	os << "(" << p.first << "," << p.second << ")";
	return ( os );
	}

template<typename tType>
std::ostream& operator << ( std::ostream& out,
		yaal::hcore::HVector<tType> const& a_oVector )
	{
	M_PROLOG
	int long l_iCtr = 0, l_iSize = a_oVector.dim();
	out << std::fixed << "< " << std::setw ( 10 ) << std::setprecision ( 4 );
	out << a_oVector [ 0 ];
	for ( l_iCtr = 1; l_iCtr < l_iSize; l_iCtr ++ )
		{
		out << ", " << std::setw ( 10 ) << std::setprecision ( 4 );
		out << a_oVector [ l_iCtr ];
		}
	out << " >";
	return ( out );
	M_EPILOG
	}

template<typename tType>
std::ostream& operator << ( std::ostream& out,
		yaal::hcore::HMatrix<tType> const& a_oMatrix )
	{
	M_PROLOG
	int l_iCtr = 0, l_iCtrLoc = 0;
	int l_iRows = a_oMatrix.row ( ), l_iCols = a_oMatrix.col ( );
#ifdef __DEBUG__
/*	out << "rows = " << l_iRows << ", cols = " << l_iCols << endl; */
#endif /* __DEBUG__ */
	out << "+--    ";
	for ( l_iCtr = 1; l_iCtr < l_iCols; l_iCtr ++ )
		out <<  "            ";
	out << "    --+" << std::endl;
	for ( l_iCtr = 0; l_iCtr < l_iRows; l_iCtr ++ )
		{
		out << std::fixed << "| " << std::setw ( 10 ) << std::setprecision ( 4 );
		out << a_oMatrix[ l_iCtr ] [ 0 ];
		for ( l_iCtrLoc = 1; l_iCtrLoc < l_iCols; l_iCtrLoc ++ )
			{
			out << ", " << std::setw ( 10 ) << std::setprecision ( 4 );
			out << a_oMatrix [ l_iCtr ] [ l_iCtrLoc ];
			}
		out << " |" << std::endl;
		}
	out << "+--    ";
	for ( l_iCtr = 1; l_iCtr < l_iCols; l_iCtr ++ )
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
	HLogger& operator << ( int const& );
	HLogger& operator << ( std::ostream& ( * const )( std::ostream& ) );
	/*}*/
protected:
	/*{*/
	/*}*/
	};

yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface&, std::string const& );
struct inc { int _n; inc( int n ) : _n( n ){} int operator()() { return ( _n ++ ); } };

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

template<typename owner_t>
class HInstanceTracker
	{
	static int _instances;
	static int _autoIncrement;
	int _id;
	yaal::hcore::HString _origin;
public:
	HInstanceTracker( int = -1 );
	HInstanceTracker( HInstanceTracker const& );
	HInstanceTracker& operator = ( HInstanceTracker const& );
	~HInstanceTracker( void );
	bool operator == ( HInstanceTracker<owner_t> const& ) const;
	bool operator != ( HInstanceTracker<owner_t> const& ) const;
	bool operator == ( int const& ) const;
	bool operator != ( int const& ) const;
	static int get_instance_count( void );
	static void set_instance_count( int = 0 );
	static void set_start_id( int = 0 );
	int get_id( void ) const;
	int id( void ) const;
	yaal::hcore::HString to_string( void ) const;
	void swap( HInstanceTracker& );
	};

template<typename owner_t>
int HInstanceTracker<owner_t>::_instances = 0;
template<typename owner_t>
int HInstanceTracker<owner_t>::_autoIncrement = 0;

template<typename owner_t>
HInstanceTracker<owner_t>::HInstanceTracker( int id_ ) : _id( id_ >= 0 ? id_ : _autoIncrement ), _origin()
	{
	++ _instances;
	++ _autoIncrement;
	}

template<typename owner_t>
HInstanceTracker<owner_t>::HInstanceTracker( HInstanceTracker const& itrck )
	: _id( itrck._id ),
	_origin( itrck._origin + ":" + itrck._id )
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
	int status = 0;
	char* ptr = abi::__cxa_demangle( typeid( owner_t ).name(), 0, 0, &status );
	ss << "HInstanceTracker<" << ( ptr ? ptr : "" ) << ">(" << _origin << ":" << _id << ")";
	yaal::hcore::xfree( ptr );
	return ( ss.string() );
	}

template<typename owner_t>
bool HInstanceTracker<owner_t>::operator == ( int const& val ) const
	{
	return ( val == _id );
	}

template<typename owner_t>
bool HInstanceTracker<owner_t>::operator != ( int const& val ) const
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
bool operator == ( int const& left, HInstanceTracker<owner_t> const& right )
	{
	return ( left == right.get_id() );
	}

template<typename owner_t>
bool operator != ( int const& left, HInstanceTracker<owner_t> const& right )
	{
	return ( left != right.get_id() );
	}

template<typename owner_t>
int HInstanceTracker<owner_t>::get_instance_count( void )
	{
	return ( _instances );
	}

template<typename owner_t>
int HInstanceTracker<owner_t>::get_id( void ) const
	{
	return ( _id );
	}

template<typename owner_t>
int HInstanceTracker<owner_t>::id( void ) const
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

}

template<typename owner_t>
inline void swap( tress::tut_helpers::HInstanceTracker<owner_t>& a, tress::tut_helpers::HInstanceTracker<owner_t>& b )
	{
	a.swap( b );
	}

}

#endif /* not TRESS_TUT_HELPERS_HXX_INCLUDED */

