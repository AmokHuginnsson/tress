/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hhashmap.cxx - this file is integral part of `tress' project.

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

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hhashmap
	{
	typedef HHashMap<int, int> hash_map_t;
	static int const D_TEST_PRIME = 17;
	static int const D_ELEM_COUNT;
	static int const D_LARGE_TABLE;
	static int const D_FEW_ELEMENTS;
	virtual ~tut_yaal_hcore_hhashmap( void )
		{}
	};

int const tut_yaal_hcore_hhashmap::D_ELEM_COUNT = 32;
int const tut_yaal_hcore_hhashmap::D_LARGE_TABLE = 251;
int const tut_yaal_hcore_hhashmap::D_FEW_ELEMENTS = 4;

typedef test_group<tut_yaal_hcore_hhashmap> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hhashmap_group( "yaal::hcore::HHashMap" );

/* Simple constructor. */
template<>
template<>
void module::test<1>( void )
	{
	try
		{
		hash_map_t map( 0 );
		fail ( "Created map with bad hash table size." );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	}

/* Quantity test. */
template<>
template<>
void module::test<2>( void )
	{
	hash_map_t map( 17 );
	ensure_equals ( "newly created map is not empty", map.size(), 0 );
	map[ 0 ] = 7;
	ensure_equals ( "wrong size after add", map.size(), 1 );
	}

/* element insertion */
template<>
template<>
void module::test<3>( void )
	{
	hash_map_t map( D_TEST_PRIME );
	for ( int i = 0; i < D_ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		ensure_equals ( "wrong size after addition", map.size(), i + 1 );
		}
	}

/* iterate */
template<>
template<>
void module::test<4>( void )
	{
	hash_map_t map( D_TEST_PRIME );
	for ( int i = 0; i < D_ELEM_COUNT; ++ i )
		map[ i ] = i;
	int i = 0;
	for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it, ++ i )
		ensure_equals ( "key/value mismatch", it->value, it->key );
	ensure_equals ( "bad number of iterations", i, D_ELEM_COUNT );
	}

/* key, value access */
template<>
template<>
void module::test<5>( void )
	{
	hash_map_t map( D_TEST_PRIME );
	for ( int i = 0; i < D_ELEM_COUNT; ++ i )
		map[ i ] = i;
	int value = 0;
	for ( int i = 0; i < D_ELEM_COUNT; ++ i )
		{
		ensure( "key not present", map.has_key( i ) );
		ensure( "cannot get", ! map.get( i, value ) );
		ensure_equals ( "key/value mismatch", value, i );
		}
	}

/* key removal */
template<>
template<>
void module::test<6>( void )
	{
	hash_map_t map( D_TEST_PRIME );
	for ( int i = 0; i < D_ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		ensure_equals ( "wrong size after addition", map.size(), i + 1 );
		}
	for ( int i = 0; i < D_ELEM_COUNT; ++ i )
		{
		map.remove( i );
		ensure_equals ( "wrong size after add", map.size(), D_ELEM_COUNT - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ensure_equals ( "key/value mismatch", it->value, it->key );
		}
	}

/* iteration on large table with few elements */
template<>
template<>
void module::test<7>( void )
	{
	hash_map_t map( D_LARGE_TABLE );
	for ( int i = 0; i < D_FEW_ELEMENTS; ++ i )
		map[ i ] = i;
	int i = 0;
	for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it, ++ i )
		ensure_equals ( "key/value mismatch", it->value, it->key );
	ensure_equals ( "bad number of iterations", i, D_FEW_ELEMENTS );
	}

}
