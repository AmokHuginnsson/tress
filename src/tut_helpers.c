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
M_CVSID ( "$CVSHeader$" )

#include "tut_helpers.h"

using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

HLogger & HLogger::operator << ( char const * const a_pcString )
	{
	M_PROLOG
	hcore::log << a_pcString;
	return ( * this );
	M_EPILOG
	}

HLogger & HLogger::operator << ( string const & a_oString )
	{
	M_PROLOG
	hcore::log << a_oString.c_str ( );
	return ( * this );
	M_EPILOG
	}

HLogger & HLogger::operator << ( int const & a_iNumber )
	{
	M_PROLOG
	hcore::log << a_iNumber;
	return ( * this );
	M_EPILOG
	}

HLogger & HLogger::operator << ( ostream & ( * const ) ( ostream & ) )
	{
	M_PROLOG
	hcore::log << endl;
	return ( * this );
	M_EPILOG
	}

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

