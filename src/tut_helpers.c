/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_helpers.c - this file is integral part of `tress' project.

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

#include <iostream>
#include <iomanip>

#include <stdhapi.h>

using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

ostream & operator << ( ostream & out, HComplex a_oComplex )
	{
	M_PROLOG
	double re, im;
	re = a_oComplex.re ( );
	im = a_oComplex.im ( );
	if ( im >= 0 )
		out << re << " + i" << im;
	else
		out << re << " - i" << - im;
	return ( out );
	M_EPILOG
	}

template < class tType >
ostream & operator << ( ostream & out, HVector < tType > a_oVector )
	{
	M_PROLOG
	int l_iCtr = 0, l_iSize = a_oVector.get_size ( );
	out << fixed << "< " << setw ( 10 ) << setprecision ( 4 ) << a_oVector [ 0 ];
	for ( l_iCtr = 1; l_iCtr < l_iSize; l_iCtr ++ )
		out << ", " << setw ( 10 ) << setprecision ( 4 ) << a_oVector [ l_iCtr ];
	out << " >";
	return ( out );
	M_EPILOG
	}

template < class tType >
ostream & operator << ( ostream & out, HMatrix < tType > a_oMatrix )
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
	out << "    --+" << endl;
	for ( l_iCtr = 0; l_iCtr < l_iRows; l_iCtr ++ )
		{
		out << fixed << "| " << setw ( 10 ) << setprecision ( 4 );
		out << a_oMatrix [ l_iCtr ] [ 0 ];
		for ( l_iCtrLoc = 1; l_iCtrLoc < l_iCols; l_iCtrLoc ++ )
			out << ", " << setw ( 10 ) << setprecision ( 4 ) << a_oMatrix [ l_iCtr ] [ l_iCtrLoc ];
		out << " |" << endl;
		}
	out << "+--    ";
	for ( l_iCtr = 1; l_iCtr < l_iCols; l_iCtr ++ )
		out << "            ";
	out << "    --+" << endl;
	return ( out );
	M_EPILOG
	}

