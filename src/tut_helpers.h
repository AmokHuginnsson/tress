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
#include <yaal/yaal.h>

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
	HLogger & operator << ( std::string const & );
	HLogger & operator << ( int const & );
	HLogger & operator << ( std::ostream & ( * const ) ( std::ostream & ) );
	/*}*/
protected:
	/*{*/
	/*}*/
	};

std::ostream & operator << ( std::ostream &, yaal::hcore::HComplex );

template < class tType >
std::ostream & operator << ( std::ostream & out,
		yaal::hcore::HVector < tType > a_oVector )
	{
	M_PROLOG
	int l_iCtr = 0, l_iSize = a_oVector.get_size ( );
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

template < class tType >
std::ostream & operator << ( std::ostream & out,
		yaal::hcore::HMatrix < tType > a_oMatrix )
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
		out << a_oMatrix [ l_iCtr ] [ 0 ];
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

//#define TITLE( title ) void TITLE( tut(title) )
void TITLE( char const* const );

template<typename tType>
class counter
	{
	static int _instances;
	tType _symbol;
public:
	counter( void );
	counter( tType const& );
	counter( counter const& );
	~counter( void );
	bool operator == ( counter<tType> const& ) const;
	bool operator != ( counter<tType> const& ) const;
	bool operator == ( tType const& ) const;
	bool operator != ( tType const& ) const;
	operator tType ( void );
	static int get_instances_count( void );
	tType get_symbol( void ) const;
	};

template<typename tType>
int counter<tType>::_instances = 0;

template<typename tType>
counter<tType>::counter( void ) : _symbol()
	{
	++ _instances;
	}

template<typename tType>
counter<tType>::counter( tType const& symbol ) : _symbol( symbol )
	{
	++ _instances;
	}

template<typename tType>
counter<tType>::counter( counter const& ctr ) : _symbol( ctr._symbol )
	{
	++ _instances;
	}

template<typename tType>
counter<tType>::~counter( void )
	{
	-- _instances;
	}

template<typename tType>
bool counter<tType>::operator == ( tType const& val ) const
	{
	return ( val == _symbol );
	}

template<typename tType>
bool counter<tType>::operator != ( tType const& val ) const
	{
	return ( val != _symbol );
	}

template<typename tType>
bool counter<tType>::operator == ( counter<tType> const& val ) const
	{
	return ( val._symbol == _symbol );
	}

template<typename tType>
bool counter<tType>::operator != ( counter<tType> const& val ) const
	{
	return ( val._symbol != _symbol );
	}

template<typename tType>
bool operator == ( tType const& left, counter<tType> const& right )
	{
	return ( left == right.get_symbol() );
	}

template<typename tType>
bool operator != ( tType const& left, counter<tType> const& right )
	{
	return ( left != right.get_symbol() );
	}

template<typename tType>
counter<tType>::operator tType ( void )
	{
	return ( _symbol );
	}

template<typename tType>
int counter<tType>::get_instances_count( void )
	{
	return ( _instances );
	}

template<typename tType>
tType counter<tType>::get_symbol( void ) const
	{
	return ( _symbol );
	}

template<typename tType>
yaal::hcore::HString& operator += ( yaal::hcore::HString& str, counter<tType> const& ctr )
	{
	str += ctr.get_symbol();
	return ( str );
	}

template<typename tType>
std::ostream& operator << ( std::ostream& stream, counter<tType> const& ctr )
	{
	stream << ctr.get_symbol();
	return ( stream );
	}

}

#endif /* not __TUT_HELPERS_H */

