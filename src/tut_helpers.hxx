/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_helpers.h - this file is integral part of `tress' project.

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

#ifndef __TUT_HELPERS_H
#define __TUT_HELPERS_H

#include <string>
#include <iostream>
#include <iomanip>

#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/hvector.hxx>
#include <yaal/hcore/hmatrix.hxx>

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

std::ostream& operator << ( std::ostream&, yaal::hcore::HComplex const& );
std::ostream& operator << ( std::ostream&, yaal::hcore::HString const& );

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

struct inc { int _n; inc( int n ) : _n( n ){} int operator()() { return ( _n ++ ); } };

void show_title( char const* const );
void show_end( void );

#define TUT_UNIT_TEST_N( no, title ) template<> template<> void module::test<(no)>( void ) { do { set_test_meta( title, __FILE__, __LINE__ ); show_title( title ); } while ( 0 );
#define TUT_UNIT_TEST( title ) TUT_UNIT_TEST_N( ( __COUNTER__ ), ( title ) )
#define TUT_TEARDOWN() show_end(); }
#define TUT_TEST_GROUP_N( mock, name ) \
typedef test_group<mock> tut_group; \
typedef tut_group::object module; \
tut_group tut_##mock##_group( ( name ) );
#define TUT_TEST_GROUP( mock, name ) \
TUT_TEST_GROUP_N( mock, name ) \
namespace { static int const dropIt __attribute__(( __used__ )) = __COUNTER__; }

template<typename symbol_t, typename owner_t>
class counter
	{
	static int _instances;
	symbol_t _symbol;
public:
	counter( void );
	counter( symbol_t const& );
	counter( counter const& );
	~counter( void );
	bool operator == ( counter<symbol_t, owner_t> const& ) const;
	bool operator != ( counter<symbol_t, owner_t> const& ) const;
	bool operator == ( symbol_t const& ) const;
	bool operator != ( symbol_t const& ) const;
	operator symbol_t ( void );
	static int get_instance_count( void );
	static void set_instance_count( int );
	symbol_t get_symbol( void ) const;
	void foo( void );
	};

template<typename symbol_t, typename owner_t>
int counter<symbol_t, owner_t>::_instances = 0;

template<typename symbol_t, typename owner_t>
counter<symbol_t, owner_t>::counter( void ) : _symbol()
	{
	++ _instances;
	}

template<typename symbol_t, typename owner_t>
counter<symbol_t, owner_t>::counter( symbol_t const& symbol ) : _symbol( symbol )
	{
	++ _instances;
	}

template<typename symbol_t, typename owner_t>
counter<symbol_t, owner_t>::counter( counter const& ctr ) : _symbol( ctr._symbol )
	{
	++ _instances;
	}

template<typename symbol_t, typename owner_t>
counter<symbol_t, owner_t>::~counter( void )
	{
	-- _instances;
	}

template<typename symbol_t, typename owner_t>
void counter<symbol_t, owner_t>::set_instance_count( int count )
	{
	_instances = count;
	}

template<typename symbol_t, typename owner_t>
void counter<symbol_t, owner_t>::foo ( void )
	{
	std::cout << "do_foo(" << _symbol << ")" << std::endl;
	}

template<typename symbol_t, typename owner_t>
bool counter<symbol_t, owner_t>::operator == ( symbol_t const& val ) const
	{
	return ( val == _symbol );
	}

template<typename symbol_t, typename owner_t>
bool counter<symbol_t, owner_t>::operator != ( symbol_t const& val ) const
	{
	return ( val != _symbol );
	}

template<typename symbol_t, typename owner_t>
bool counter<symbol_t, owner_t>::operator == ( counter<symbol_t, owner_t> const& val ) const
	{
	return ( val._symbol == _symbol );
	}

template<typename symbol_t, typename owner_t>
bool counter<symbol_t, owner_t>::operator != ( counter<symbol_t, owner_t> const& val ) const
	{
	return ( val._symbol != _symbol );
	}

template<typename symbol_t, typename owner_t>
bool operator == ( symbol_t const& left, counter<symbol_t, owner_t> const& right )
	{
	return ( left == right.get_symbol() );
	}

template<typename symbol_t, typename owner_t>
bool operator != ( symbol_t const& left, counter<symbol_t, owner_t> const& right )
	{
	return ( left != right.get_symbol() );
	}

template<typename symbol_t, typename owner_t>
counter<symbol_t, owner_t>::operator symbol_t ( void )
	{
	return ( _symbol );
	}

template<typename symbol_t, typename owner_t>
int counter<symbol_t, owner_t>::get_instance_count( void )
	{
	return ( _instances );
	}

template<typename symbol_t, typename owner_t>
symbol_t counter<symbol_t, owner_t>::get_symbol( void ) const
	{
	return ( _symbol );
	}

template<typename symbol_t, typename owner_t>
yaal::hcore::HString& operator += ( yaal::hcore::HString& str, counter<symbol_t, owner_t> const& ctr )
	{
	str += ctr.get_symbol();
	return ( str );
	}

template<typename symbol_t, typename owner_t>
std::ostream& operator << ( std::ostream& stream, counter<symbol_t, owner_t> const& ctr )
	{
	stream << ctr.get_symbol();
	return ( stream );
	}

}

}

#endif /* not __TUT_HELPERS_H */

