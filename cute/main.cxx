/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	main.cxx - this file is integral part of `tress' project.

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

#include <unistd.h>
#include <iostream>

#include <yaal/yaal.hxx>
M_VCSID( "$Id$" )

#include "version.hxx"
#include "setup.hxx"
#include "options.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress;

namespace tress
{

OSetup setup;

class HCuteReporter
	{
	typedef HList<HString> report_t;
	HStringStream _out;
	HString _group;
	HString _test;
	int _cnt;
	report_t _rep;
	report_t::iterator _start;
public:
	HCuteReporter( void );
	int run_ut( int, char*[] );
	void handle_line_of_error( HString const& );
	};

}

int main( int a_iArgc, char* a_ppcArgv[] )
	{
	M_PROLOG
/*	variables declarations for main loop:                                 */
	int l_iOpt = 0;
/*	end.                                                                  */
	try
		{
/*	TO-DO:				enter main loop code here                               */
		HSignalServiceFactory::get_instance();
		setup.f_pcProgramName = a_ppcArgv[ 0 ];
		l_iOpt = handle_program_options( a_iArgc, a_ppcArgv );
		setup.test_setup();
		hcore::log.rehash( "x_cute.log", setup.f_pcProgramName );
//		if ( ! is_enabled ( ) )enter_curses (); /* enabling ncurses ablilities*/
/* *BOOM* */
		HCuteReporter r;
		r.run_ut( a_iArgc, a_ppcArgv );
//		if ( is_enabled ( ) )leave_curses ();  /* ending ncurses sesion    */
/*	... there is the place main loop ends. :OD-OT                         */
		}
	catch ( int& )
		{
		/* escape from main loop */
		}
	catch ( ... )
		{
/* ending ncurses sesion        */
		if ( HCons::get_instance().is_enabled() )
			HCons::get_instance().leave_curses();
		throw;
		}
	return ( 0 );
	M_FINAL
	}

namespace tress
{

HCuteReporter::HCuteReporter( void )
	: _out(), _group(), _test(), _cnt( 0 ), _rep(), _start( _rep.end() )
	{
	}

int HCuteReporter::run_ut( int a_iArgc, char* a_ppcArgv[] )
	{
	HPipedChild tress;
	M_ASSERT( ! a_ppcArgv[ a_iArgc ] );
	char const* suite = ::getenv( "CUTE_TARGET" );
	if ( ! suite )
		suite = "./build/tress/1exec";
	HString line;
	HString err;
	timeval t = { 0, 0 };
	HPipedChild::argv_t argv( a_iArgc - 1 );
	for ( int i = 0; i < argv.size(); ++ i )
		argv[ i ] = a_ppcArgv[ i + 1 ];
	do
		{
		tress.spawn( suite, argv );
		bool ok = true;
		bool repeat = false;
		while ( ok || repeat )
			{
			HStreamInterface::STATUS::code_t s;
			tress.set_csoi( HPipedChild::STREAM::D_OUT );
			bool repeatOut = tress.read_poll( &t ) || ( ( s = tress.read_until( line ).code ) == HStreamInterface::STATUS::D_REPEAT );
			bool okOut = ( s == HStreamInterface::STATUS::D_OK );
			if ( okOut && setup.f_bVerbose )
				cout << line.raw() << endl;
			tress.set_csoi( HPipedChild::STREAM::D_ERR );
			bool repeatErr = tress.read_poll( &t ) || ( ( s = tress.read_until( err ).code ) == HStreamInterface::STATUS::D_REPEAT );
			bool okErr = ( s == HStreamInterface::STATUS::D_OK );
			if ( ! repeatErr && okErr && !! err )
				handle_line_of_error( err );
			ok = okOut || okErr;
			repeat = repeatOut || repeatErr;
			}
		}
	while ( setup.f_bRestartable && ( tress.finish().type != HPipedChild::STATUS::TYPE::D_NORMAL ) );
	if ( _start != _rep.end() )
		{
		*_start += _cnt;
		_rep.push_back( _out << "#ending " << _group << _out );
		}
	else
		{
		_rep.push_back( "#beginning tress 1" );
		_rep.push_back( "#starting test" );
		_rep.push_back( "#success test OK" );
		_rep.push_back( "#ending tress" );
		}
	for ( report_t::iterator it = _rep.begin(); it != _rep.end(); ++ it )
		cout << it->raw() << endl;
	return ( 0 );
	}

void HCuteReporter::handle_line_of_error( HString const& in )
	{
	static char const D_GROUP_PREFIX[] = "---> group: ";
	static int const D_GROUP_PREFIX_LEN = sizeof ( D_GROUP_PREFIX ) - 1;

	static char const D_PROBLEM_ASSERTION[] = "problem: assertion failed";
	static char const D_DESC_ASSERTION[] = "failed assertion in \"";
	static int const D_DESC_ASSERTION_LEN = sizeof ( D_DESC_ASSERTION ) - 1;

	static char const D_PROBLEM_EXCEPTION[] = "problem: unexpected exception";
	static char const D_DESC_EXCEPTION[] = "unexpected exception in \"";
	static int const D_DESC_EXCEPTION_LEN = sizeof ( D_DESC_EXCEPTION ) - 1;

	static char const D_PROBLEM_SEGV[] = "problem: would be terminated";
	static char const D_DESC_SEGV[] = "segmentation fault in \"";
	static int const D_DESC_SEGV_LEN = sizeof ( D_DESC_SEGV ) - 1;

	static char const D_NAME[] = "tress/";
	static int const D_NAME_LEN = sizeof ( D_NAME ) - 1;

	static char const D_TEST[] = ", test: ";
	static int const D_TEST_LEN = sizeof ( D_TEST ) - 1;

	_out.clear();
	int long idx = 0;
	bool start = false;
	if ( ( idx = in.find( D_GROUP_PREFIX ) ) >= 0 )
		{
		idx += D_GROUP_PREFIX_LEN;
		int long coma = in.find( ',', idx );
		HString g = in.mid( idx, coma - idx );
		if ( g != _group )
			{
			start = true;
			if ( !! _group )
				{
				*_start += _cnt;
				_out << "#ending " << _group << endl;
				}
			_group = g;
			_out << "#beginning " << _group << " ";
			_cnt = 0;
			}
		idx = in.find( D_TEST, coma );
		M_ENSURE( idx >= 0 );
		idx += D_TEST_LEN;
		HString t = in.mid( idx );
		_test = t;
		}
	else if ( in.find( D_PROBLEM_ASSERTION ) >= 0 )
		{
		// skip
		}
	else if ( in.find( D_PROBLEM_EXCEPTION ) >= 0 )
		{
		// skip
		}
	else if ( in.find( D_PROBLEM_SEGV ) >= 0 )
		{
		// skip
		}
	else if ( ( ( ( idx = in.find( D_DESC_ASSERTION ) ) >= 0 ) && ( idx += D_DESC_ASSERTION_LEN ) )
			|| ( ( ( idx = in.find( D_DESC_EXCEPTION ) ) >= 0 ) && ( idx += D_DESC_EXCEPTION_LEN ) )
			|| ( ( ( idx = in.find( D_DESC_SEGV ) ) >= 0 ) && ( idx += D_DESC_SEGV_LEN ) ) )
		{
		idx = in.find( D_NAME, idx );
		M_ENSURE( idx >= 0 );
		idx += D_NAME_LEN;
		_out << "#starting " << _test << endl;
		_out << "#failure " << _test << " ./" << in.mid( idx, ( in.get_length() - idx ) - 1 );
		++ _cnt;
		}
	else
		cout << in.raw() << endl;
	if ( ! _out.is_empty() )
		{
		_rep.push_back( _out.consume() );
		if ( start )
			_start = _rep.rbegin();
		}
	}

}

