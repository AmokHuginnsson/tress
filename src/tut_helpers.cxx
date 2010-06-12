/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_helpers.cxx - this file is integral part of `tress' project.

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

#include <cstring>
#include <cstdlib>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace std
{

std::ostream& operator << ( std::ostream& out, HComplex const& complex_ )
	{
	M_PROLOG
	double re, im;
	re = complex_.re ( );
	im = complex_.im ( );
	if ( im >= 0 )
		out << re << "+i" << im;
	else
		out << re << "-i" << - im;
	return ( out );
	M_EPILOG
	}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HString const& s )
	{
	out << s.raw();
	return ( out );
	}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HNumber const& n )
	{
	out << n.to_string();
	return ( out );
	}

}

namespace tress
{

namespace tut_helpers
{

namespace
{

bool _watchNext_ = false;
int _number_ = 0;
std::string _group_;

}

HLogger::HLogger( void )
	{
	}

HLogger& HLogger::operator << ( std::string const& string_ )
	{
	M_PROLOG
	if ( _watchNext_ )
		{
		_group_ = string_;
		_watchNext_ = false;
		}
	else
		{
		if ( ! strncmp( string_.c_str(), "TUT: group", 10 ) )
			_watchNext_ = true;
		}
	hcore::log << string_.c_str ( );
	return ( * this );
	M_EPILOG
	}

HLogger& HLogger::operator << ( int const& number_ )
	{
	M_PROLOG
	_number_ = number_;
	hcore::log << number_;
	return ( * this );
	M_EPILOG
	}

HLogger& HLogger::operator << ( std::ostream& ( * const ) ( std::ostream& ) )
	{
	M_PROLOG
	hcore::log << endl;
	return ( * this );
	M_EPILOG
	}

HStreamInterface& operator << ( HStreamInterface& out, std::string const& s )
	{
	out << s.c_str();
	return ( out );
	}

void show_title( char const* const title )
	{
	if ( setup._verbose )
		{
		cout << "------------------------------------------------------------------------" << endl;
		cout << "TUT: " << _group_ << "::<" << _number_ << "> " << title << endl;
		}
	}

void show_end( void )
	{
	if ( setup._verbose )
		cout << "------------------------------------------------------------------------" << endl;
	}

void HSTDGlobalScopeExceptionHandlingPolicy::handle_exception( void )
	{
	try
		{
		throw;
		}
	catch ( HException const& e )
		{
		std::cerr << "Exception `" << e.what() << "' thrown from outside of main() scope." << std::endl;
		}
	catch ( std::exception const& e )
		{
		std::cerr << "Exception `" << e.what() << "' thrown from outside of main() scope." << std::endl;
		}
	catch ( ... )
		{
		std::cerr << "Exception of unknown type thrown from outside of main() scope." << std::endl;
		}
	exit( 1 );
	}

}

}

