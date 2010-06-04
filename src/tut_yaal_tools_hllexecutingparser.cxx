/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hllexecutingparser.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace yaal;
using namespace yaal::hcore;

namespace yaal
{

namespace tools
{

namespace ll
{

class HRule
	{
public:
	virtual ~HRule( void ) {}
	HRule operator >> ( HRule& );
	HRule operator*( void );
	int operator()( HString const& input_ )
		{ return ( do_parse( input_ ) ); }
	virtual int do_parse( HString const& )
		{
		return ( 0 );
		}
	};

class HReal : public HRule
	{
	typedef HBoundCall<1, void, double const&> action_t;
	action_t _action;
public:
	HReal( void ) : _action() {}
	HRule& operator[]( action_t const& action_ )
		{
		_action = action_;
		return ( *this );
		}
	virtual int do_parse( HString const& input_ )
		{
		double d( lexical_cast<double>( input_ ) );
		if ( !! _action )
			_action( d );
		return ( 0 );
		}
	} real;

template<typename container_t>
HBoundCall<1, void, typename container_t::value_type const&> push_back( container_t& container )
	{
	return ( call( &container_t::push_back, &container, _1 ) );
	}

}

}

}

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

using namespace yaal::tools::ll;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_tools_hllexecutingparser );
TUT_TEST_GROUP_N( tut_yaal_tools_hllexecutingparser, "yaal::tools::HLLExecutingParser" );

TUT_UNIT_TEST_N( 1, "the test" )
	HArray<double> v;
	real[push_back(v)]( "3.14159265" );
//	( real[push_back(v)] >> *( ',' >> real[push_back(v)] ) )( "3.141592653589793, 2.1728182818459045" );
	copy( v.begin(), v.end(), stream_iterator( cout, endl ) );
TUT_TEARDOWN()

}

