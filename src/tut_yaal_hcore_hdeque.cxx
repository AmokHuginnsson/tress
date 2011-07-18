/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hdeque.cxx - this file is integral part of `tress' project.

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
#include <deque>

#include <yaal/hcore/hexception.hxx>

#define private public
#define protected public

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
using namespace tress;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hdeque : public simple_mock<tut_yaal_hcore_hdeque>
	{
	struct StatePreserver
		{
		int long _size;
		int long _usedChunks;
		int long _availChunks;
		int long _firstChunkIndex;
		int long _lastChunkIndex;
		void const* _firstChunk;
		void const* _lastChunk;
		};
	StatePreserver _statePreserver;
	typedef std::deque<int> proto_t;
	tut_yaal_hcore_hdeque( void )
		: _statePreserver() {}
	virtual ~tut_yaal_hcore_hdeque( void ) {}
	template<typename deque_type>
	void check_consistency( deque_type const&, int long = 0 );
	template<int const item_size>
	void test_resize( void );
	template<int const item_size>
	void test_erase( int, int );
	template<int const item_size>
	void test_erase( void );
	template<int const item_size>
	void test_push_back( void );
	template<int const item_size>
	void test_push_front( void );
	template<int const item_size>
	void test_pop_back( void );
	template<int const item_size>
	void test_pop_front( void );
	template<int const item_size>
	void test_insert_pos( void );
	template<int const item_size>
	void test_insert( void );
	};

template<typename deque_type>
void tut_yaal_hcore_hdeque::check_consistency( deque_type const& deque_, int long extraItems )
	{
	ENSURE_EQUALS( "deque size with respect to allocated objects", deque_.get_size(), deque_type::value_type::get_instance_count() - extraItems );
	int long firstChunkIndex( deque_._start / deque_type::VALUES_PER_CHUNK );
	int long lastChunkIndex( deque_._size > 0 ? ( ( deque_._start + deque_._size - 1 ) / deque_type::VALUES_PER_CHUNK ) : ( deque_._start / deque_type::VALUES_PER_CHUNK ) );
	int long chunksCount = deque_._chunks.template count_of<typename deque_type::value_type*>();
	int long usedChunks = deque_.used_chunks();
	typename deque_type::value_type const* const* chunks = deque_._chunks.template get<typename deque_type::value_type const*>();
	if ( setup._debug )
		clog << "firstChunkIndex: " << firstChunkIndex << ", _statePreserver._firstChunkIndex: " << _statePreserver._firstChunkIndex << ", lastChunkIndex: " << lastChunkIndex << ", _statePreserver._lastChunkIndex: " << _statePreserver._lastChunkIndex << ", deque_._size: " << deque_._size << ", _statePreserver._size: " << _statePreserver._size << ", chunksCount: " << chunksCount << ", _statePreserver._availChunks: " << _statePreserver._availChunks << endl;
	if ( deque_._size > 0 )
		{
		ENSURE( "chunk range bigger than chunks count", ( lastChunkIndex - firstChunkIndex ) < chunksCount );
		ENSURE( "last chunk outside avail chunks", lastChunkIndex < chunksCount );
		}
	else
		{
		ENSURE_EQUALS( "bad indexes for empty deque", lastChunkIndex, firstChunkIndex );
		ENSURE_EQUALS( "wrong number of used chunks calculated", deque_.used_chunks(), 0 );
		}
	ENSURE( "first chunk outside avail chunks", deque_._start >= 0 );
	if ( ( chunksCount > _statePreserver._availChunks )
			|| ( ( true /* deque_._size > _statePreserver._size */ )
				&& ( ( ( firstChunkIndex < chunksCount )
						&& ( firstChunkIndex != _statePreserver._firstChunkIndex )
						&& ( chunks[ firstChunkIndex ] == _statePreserver._firstChunk )
						&& ( ( _statePreserver._lastChunkIndex + 1 + abs( usedChunks - _statePreserver._usedChunks ) ) >= _statePreserver._availChunks ) )
					|| ( ( lastChunkIndex < chunksCount )
						&& ( lastChunkIndex != _statePreserver._lastChunkIndex )
						&& ( chunks[ lastChunkIndex ] == _statePreserver._lastChunk )
						&& ( ( _statePreserver._firstChunkIndex - abs( usedChunks - _statePreserver._usedChunks ) ) < 0 ) )
					) ) )
		{
		int long startGap( firstChunkIndex );
		int long endGap( ( chunksCount - lastChunkIndex ) - 1 );
		if ( setup._debug )
			clog << "startGap: " << startGap << ", endGap: " << endGap << endl;
		if ( deque_._size > 0 )
			ENSURE_DISTANCE( "chunks are not centered", abs( endGap - startGap ), 0l, 2l );
		}
	else if ( _statePreserver._size
			&& ( chunksCount >= _statePreserver._availChunks )
			&& ( ( firstChunkIndex > _statePreserver._firstChunkIndex ) || ( lastChunkIndex < _statePreserver._lastChunkIndex ) ) )
		{
		ENSURE( "unnecesarry chunks move", ( deque_._size < _statePreserver._size ) || ( chunksCount > _statePreserver._availChunks ) );
		}
	for ( int long i( 0 ); i < firstChunkIndex; ++ i )
		ENSURE_EQUALS( "not used chunks at the begining not cleared", chunks[ i ], static_cast<typename deque_type::value_type*>( NULL ) );
	for ( int long i( lastChunkIndex + 1 ); i < chunksCount; ++ i )
		ENSURE_EQUALS( "not used chunks at the end not cleared", chunks[ i ], static_cast<typename deque_type::value_type*>( NULL ) );
	if ( ( chunksCount > 0 ) && ! deque_._size )
		ENSURE_EQUALS( "not all chunks are nulled after resize( 0 )", chunks[ firstChunkIndex ], static_cast<typename deque_type::value_type*>( NULL ) );
	if ( deque_._size > 0 )
		{
		for ( int long i( firstChunkIndex ); i < ( lastChunkIndex + 1 ); ++ i )
			ENSURE_EQUALS( "a nil in used chunks range", chunks[ i ] ? true : false, true );
		}
	_statePreserver._size = deque_._size;
	_statePreserver._usedChunks = usedChunks;
	_statePreserver._availChunks = chunksCount;
	_statePreserver._firstChunkIndex = firstChunkIndex;
	_statePreserver._lastChunkIndex = lastChunkIndex;
	if ( firstChunkIndex < chunksCount )
		_statePreserver._firstChunk = chunks[ firstChunkIndex ];
	if ( lastChunkIndex < chunksCount )
		_statePreserver._lastChunk = chunks[ lastChunkIndex ];
	}

TUT_TEST_GROUP( tut_yaal_hcore_hdeque, "yaal::hcore::HDeque" );

#ifndef __sun__
#pragma pack( push, 1 )
#else /* #ifndef __sun__ */
#pragma pack( 1 )
#endif /* #else #ifndef __sun__ */
	template<int const SIZE>
	class FixedArray
		{
		char _data[SIZE];
		};
#ifndef __sun__
#pragma pack( pop )
#else /* #ifndef __sun__ */
#pragma pack()
#endif /* #else #ifndef __sun__ */

TUT_UNIT_TEST( 1, "CHUNK_SIZE, VALUES_PER_CHUNK and Constructor." )
	STATIC_ASSERT( sizeof ( FixedArray<1> ) == 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<1> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<1> >::VALUES_PER_CHUNK, 512 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<2> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<2> >::VALUES_PER_CHUNK, 256 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<3> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<3> >::VALUES_PER_CHUNK, 171 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<4> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<4> >::VALUES_PER_CHUNK, 128 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<5> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<5> >::VALUES_PER_CHUNK, 102 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<6> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<6> >::VALUES_PER_CHUNK, 85 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<7> >::CHUNK_SIZE, 511 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<7> >::VALUES_PER_CHUNK, 73 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<8> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<8> >::VALUES_PER_CHUNK, 64 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<9> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<9> >::VALUES_PER_CHUNK, 57 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<10> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<10> >::VALUES_PER_CHUNK, 51 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<11> >::CHUNK_SIZE, 517 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<11> >::VALUES_PER_CHUNK, 47 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<12> >::CHUNK_SIZE, 516 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<12> >::VALUES_PER_CHUNK, 43 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<13> >::CHUNK_SIZE, 507 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<13> >::VALUES_PER_CHUNK, 39 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<14> >::CHUNK_SIZE, 518 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<14> >::VALUES_PER_CHUNK, 37 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<15> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<15> >::VALUES_PER_CHUNK, 34 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<16> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<16> >::VALUES_PER_CHUNK, 32 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<17> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<17> >::VALUES_PER_CHUNK, 30 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<18> >::CHUNK_SIZE, 504 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<18> >::VALUES_PER_CHUNK, 28 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<19> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<19> >::VALUES_PER_CHUNK, 27 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<20> >::CHUNK_SIZE, 520 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<20> >::VALUES_PER_CHUNK, 26 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<21> >::CHUNK_SIZE, 504 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<21> >::VALUES_PER_CHUNK, 24 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<22> >::CHUNK_SIZE, 506 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<22> >::VALUES_PER_CHUNK, 23 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<23> >::CHUNK_SIZE, 506 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<23> >::VALUES_PER_CHUNK, 22 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<24> >::CHUNK_SIZE, 504 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<24> >::VALUES_PER_CHUNK, 21 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<25> >::CHUNK_SIZE, 500 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<25> >::VALUES_PER_CHUNK, 20 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<26> >::CHUNK_SIZE, 520 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<26> >::VALUES_PER_CHUNK, 20 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<27> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<27> >::VALUES_PER_CHUNK, 19 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<28> >::CHUNK_SIZE, 504 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<28> >::VALUES_PER_CHUNK, 18 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<29> >::CHUNK_SIZE, 522 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<29> >::VALUES_PER_CHUNK, 18 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<30> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<30> >::VALUES_PER_CHUNK, 17 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<31> >::CHUNK_SIZE, 527 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<31> >::VALUES_PER_CHUNK, 17 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<32> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<32> >::VALUES_PER_CHUNK, 16 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<33> >::CHUNK_SIZE, 528 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<33> >::VALUES_PER_CHUNK, 16 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<34> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<34> >::VALUES_PER_CHUNK, 15 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<35> >::CHUNK_SIZE, 525 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<35> >::VALUES_PER_CHUNK, 15 );

	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<255> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<255> >::VALUES_PER_CHUNK, 2 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<256> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<256> >::VALUES_PER_CHUNK, 2 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<257> >::CHUNK_SIZE, 514 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<257> >::VALUES_PER_CHUNK, 2 );

	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<300> >::CHUNK_SIZE, 600 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<300> >::VALUES_PER_CHUNK, 2 );

	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<340> >::CHUNK_SIZE, 680 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<340> >::VALUES_PER_CHUNK, 2 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<341> >::CHUNK_SIZE, 682 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<341> >::VALUES_PER_CHUNK, 2 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<342> >::CHUNK_SIZE, 342 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<382> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<343> >::CHUNK_SIZE, 343 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<343> >::VALUES_PER_CHUNK, 1 );

	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<511> >::CHUNK_SIZE, 511 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<511> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<512> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<512> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<513> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<513> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<767> >::CHUNK_SIZE, 767 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<767> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<768> >::CHUNK_SIZE, 768 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<768> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<769> >::CHUNK_SIZE, 769 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<769> >::VALUES_PER_CHUNK, 1 );
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	try
		{
		deque_t deque( BAD_SIZE );
		FAIL( "deque with negative size created" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_resize( void )
	{
	clog << "testing resize: " << item_size << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
		{
		deque_type deque;
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 1 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 2 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 7 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 15 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 16 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 17 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 64 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 128 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 64 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 17 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 16 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 15 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 7 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 2 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 1 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 33 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 33 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 33 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 2 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( deque_type::VALUES_PER_CHUNK ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( deque_type::VALUES_PER_CHUNK + 1 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		if ( deque_type::VALUES_PER_CHUNK > 1 )
			{
			TUT_INVOKE( deque.resize( deque_type::VALUES_PER_CHUNK - 1 ); );
			check_consistency( deque );
			TUT_INVOKE( deque.pop_front(); );
			check_consistency( deque );
			TUT_INVOKE( deque.resize( 0 ); );
			check_consistency( deque );
			}
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		}
	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	return;
	}

TUT_UNIT_TEST( 2, "Constructor and get_size()." )
	{
	item_t::set_start_id( 0 );
	int const SIZE_FOR_ONE = 0;
	int const SIZE_FOR_TWO = 7;
	deque_t one( SIZE_FOR_ONE );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", one.get_size(), SIZE_FOR_ONE );
	check_consistency( one );
	deque_t two( SIZE_FOR_TWO );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE + SIZE_FOR_TWO );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", two.get_size(), SIZE_FOR_TWO );
	check_consistency( two );
	}
	ENSURE_EQUALS( "object leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "Constructor with filling." )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	try
		{
		deque_t badDeque( BAD_SIZE, FILLER_FOR_ARRAY );
		FAIL( "deque with negative size created" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	deque_t deque( SIZE_FOR_ARRAY, FILLER_FOR_ARRAY );
	check_consistency( deque );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "deque element not filled with default value", deque[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "resize" )
	TIME_CONSTRAINT_EXEMPT();
	test_resize<1>();
	test_resize<2>();
	test_resize<3>();
	test_resize<4>();
	test_resize<5>();
	test_resize<6>();
	test_resize<7>();
	test_resize<8>();
	test_resize<9>();
	test_resize<10>();
	test_resize<11>();
	test_resize<12>();
	test_resize<13>();
	test_resize<14>();
	test_resize<15>();
	test_resize<16>();
	test_resize<17>();
	test_resize<18>();
	test_resize<19>();
	test_resize<20>();
	test_resize<21>();
	test_resize<22>();
	test_resize<23>();
	test_resize<24>();
	test_resize<25>();
	test_resize<26>();
	test_resize<27>();
	test_resize<28>();
	test_resize<29>();
	test_resize<30>();
	test_resize<31>();
	test_resize<32>();
	test_resize<33>();
	test_resize<34>();
	test_resize<35>();
	test_resize<36>();
	test_resize<37>();
	test_resize<38>();
	test_resize<39>();
	test_resize<40>();
	test_resize<41>();
	test_resize<42>();
	test_resize<43>();
	test_resize<44>();
	test_resize<45>();
	test_resize<46>();
	test_resize<47>();
	test_resize<48>();
	test_resize<49>();
	test_resize<64>();
	test_resize<128>();
	test_resize<200>();
	test_resize<511>();
	test_resize<512>();
	test_resize<513>();
	test_resize<640>();
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "Constructor with range initialization." )
	item_t::set_start_id( 0 );
	deque_t deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	proto_t proto( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	check_consistency( deque );
	ENSURE_EQUALS( "range initialization failed", deque, proto );
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, 128> big_item_t;
	typedef HDeque<big_item_t> big_deque_t;
	big_deque_t big_deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	check_consistency( deque );
	check_consistency( big_deque );
	ENSURE_EQUALS( "range initialization failed", big_deque, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "Copy constructor." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	deque_t deque( SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		deque[ i ] = i;
	check_consistency( deque );
	deque_t copy( deque );
	check_consistency( copy, SIZE );
	ENSURE_EQUALS( "inconsistient size after copy constructor", copy.get_size(), SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		ENSURE_EQUALS( "wrong content after copy constructor", copy[ i ], i );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "Operator [ ]." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	deque_t deque ( SIZE );
	try
		{
		deque [ SIZE ] = 0;
		FAIL( "access beyond size succed" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	try
		{
		deque[ - SIZE - 1 ] = 0;
		FAIL( "access with negative index succed" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "Operator bool." )
	item_t::set_start_id( 0 );
	int const EMPTY = 0;
	int const SIZE = 7;
	deque_t empty( EMPTY );
	ENSURE_EQUALS( "test for deque emptiness faild", ! empty, true );
	deque_t normal( SIZE );
	ENSURE_EQUALS( "test for deque fullness faild", ! normal, false );
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_erase( int first_, int last_ )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
		{
		clog << "testing erase: " << item_size << ", first: " << first_ << ", last: " << last_ << endl;
		item_type::set_start_id( 0 );
		deque_type deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
		check_consistency( deque );
		proto_t proto( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
		proto.erase( proto.begin() + first_, proto.begin() + last_ );
		deque.erase( deque.begin() + first_, deque.begin() + last_ );
		check_consistency( deque );
		ENSURE_EQUALS( "range initialization failed", deque, proto );
		}

	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	}

template<int const item_size>
void tut_yaal_hcore_hdeque::test_erase( void )
	{
	test_erase<item_size>( 0, countof( _testData_[0] ) / 2 );
	test_erase<item_size>( countof( _testData_[0] ) / 2, countof( _testData_[0] ) );
	test_erase<item_size>( 0, countof( _testData_[0] ) );
	test_erase<item_size>( 0, 1 );
	test_erase<item_size>( countof ( _testData_[0] ) - 1, countof ( _testData_[0] ) );
	test_erase<item_size>( 1, countof ( _testData_[0] ) - 1 );
	test_erase<item_size>( 3, 6 );
	test_erase<item_size>( countof ( _testData_[0] ) - 6, countof ( _testData_[0] ) - 3 );
	test_erase<item_size>( countof ( _testData_[0] ) / 2 - 3, countof ( _testData_[0] ) / 2 + 3 );
	test_erase<item_size>( 0, countof( _testData_[0] ) / 2 + countof ( _testData_[0] ) / 4 );
	test_erase<item_size>( 3, countof( _testData_[0] ) / 2 + countof ( _testData_[0] ) / 4 );
	test_erase<item_size>( countof ( _testData_[0] ) / 4, countof( _testData_[0] ) );
	test_erase<item_size>( countof ( _testData_[0] ) / 4, countof( _testData_[0] ) - 3 );
	}

TUT_UNIT_TEST( 9, "range erase" )
	test_erase<1>();
	test_erase<2>();
	test_erase<3>();
	test_erase<7>();
	test_erase<15>();
	test_erase<16>();
	test_erase<17>();
	test_erase<64>();
	test_erase<128>();
	test_erase<200>();
	test_erase<511>();
	test_erase<512>();
	test_erase<513>();
	test_erase<640>();
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_push_back( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing push_back: " << item_size << endl;
		{
		deque_type deque;
		proto_t proto;
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.push_back( static_cast<int>( i ) );
			deque.push_back( static_cast<int>( i ) );
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
			}
		}
	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	}

TUT_UNIT_TEST( 10, "push_back" )
	TIME_CONSTRAINT_EXEMPT();
	test_push_back<1>();
	test_push_back<2>();
	test_push_back<3>();
	test_push_back<7>();
	test_push_back<15>();
	test_push_back<16>();
	test_push_back<17>();
	test_push_back<64>();
	test_push_back<128>();
	test_push_back<200>();
	test_push_back<511>();
	test_push_back<512>();
	test_push_back<513>();
	test_push_back<640>();
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_push_front( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing push_front: " << item_size << endl;
		{
		deque_type deque;
		proto_t proto;
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.push_front( static_cast<int>( i ) );
			deque.push_front( static_cast<int>( i ) );
			check_consistency( deque );
			ENSURE_EQUALS( "push_front failed", deque, proto );
			}
		}
	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	}

TUT_UNIT_TEST( 11, "push_front" )
	TIME_CONSTRAINT_EXEMPT();
	test_push_front<1>();
	test_push_front<2>();
	test_push_front<3>();
	test_push_front<7>();
	test_push_front<15>();
	test_push_front<16>();
	test_push_front<17>();
	test_push_front<64>();
	test_push_front<128>();
	test_push_front<200>();
	test_push_front<511>();
	test_push_front<512>();
	test_push_front<513>();
	test_push_front<640>();
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_pop_back( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing pop_back: " << item_size << endl;
		{
		deque_type deque( 2048 );
		check_consistency( deque );
		proto_t proto( 2048 );
		/* Bug in GCC 4.2.1 enforces namespace prefix here. */
		yaal::generate( deque.begin(), deque.end(), inc( 0 ) );
		yaal::generate( proto.begin(), proto.end(), inc( 0 ) );
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.pop_back();
			deque.pop_back();
			check_consistency( deque );
			ENSURE_EQUALS( "pop_back failed", deque, proto );
			}
		ENSURE_EQUALS( "not empty!", deque.is_empty(), true );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

TUT_UNIT_TEST( 12, "pop_back" )
	TIME_CONSTRAINT_EXEMPT();
	test_pop_back<1>();
	test_pop_back<2>();
	test_pop_back<3>();
	test_pop_back<7>();
	test_pop_back<15>();
	test_pop_back<16>();
	test_pop_back<17>();
	test_pop_back<64>();
	test_pop_back<128>();
	test_pop_back<200>();
	test_pop_back<511>();
	test_pop_back<512>();
	test_pop_back<513>();
	test_pop_back<640>();
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_pop_front( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing pop_front: " << item_size << endl;
		{
		deque_type deque( 2048 );
		check_consistency( deque );
		proto_t proto( 2048 );
		/* Bug in GCC 4.2.1 enforces namespace prefix here. */
		yaal::generate( deque.begin(), deque.end(), inc( 0 ) );
		yaal::generate( proto.begin(), proto.end(), inc( 0 ) );
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.pop_front();
			deque.pop_front();
			check_consistency( deque );
			ENSURE_EQUALS( "pop_front failed", deque, proto );
			}
		ENSURE_EQUALS( "not empty!", deque.is_empty(), true );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

TUT_UNIT_TEST( 13, "pop_front" )
	TIME_CONSTRAINT_EXEMPT();
	test_pop_front<1>();
	test_pop_front<2>();
	test_pop_front<3>();
	test_pop_front<7>();
	test_pop_front<15>();
	test_pop_front<16>();
	test_pop_front<17>();
	test_pop_front<64>();
	test_pop_front<128>();
	test_pop_front<200>();
	test_pop_front<511>();
	test_pop_front<512>();
	test_pop_front<513>();
	test_pop_front<640>();
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "copy constructor (of empty)" )
	deque_t a1;
	check_consistency( a1 );
	ENSURE( "construction of empty deque", a1.is_empty() );
	deque_t a2( a1 );
	check_consistency( a2 );
	ENSURE( "construction of empty deque", a2.is_empty() );
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_insert_pos( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing insert(pos): " << item_size << endl;
	item_t::set_start_id( 0 );
		{
		proto_t proto( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
		deque_type deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.begin(), -7 );
		proto.insert( proto.begin(), -7 );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.begin() + 5, -7 );
		proto.insert( proto.begin() + 5, -7 );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.end() - 1, -7 );
		proto.insert( proto.end() - 1, -7 );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.end(), -99 );
		proto.insert( proto.end(), -99 );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

TUT_UNIT_TEST( 15, "insert( pos, value )" )
	test_insert_pos<1>();
	test_insert_pos<2>();
	test_insert_pos<3>();
	test_insert_pos<7>();
	test_insert_pos<15>();
	test_insert_pos<16>();
	test_insert_pos<17>();
	test_insert_pos<64>();
	test_insert_pos<128>();
	test_insert_pos<200>();
	test_insert_pos<511>();
	test_insert_pos<512>();
	test_insert_pos<513>();
	test_insert_pos<640>();
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "assign operator (=)" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int a1[] = { -36, -1, -4, -9 };
	item_t::set_start_id( 0 );
		{
		deque_t deque( a0, a0 + countof ( a0 ) );
		check_consistency( deque );
		deque_t small( a1, a1 + countof ( a1 ) );
		check_consistency( small, deque.get_size() );
		deque = small;
		check_consistency( deque, small.get_size() );
		ENSURE_EQUALS( "assgin failed", deque, small );
		deque_t big( a0, a0 + countof ( a0 ) );
		check_consistency( big, deque.get_size() + small.get_size() );
		deque = big;
		check_consistency( deque, big.get_size() + small.get_size() );
		ENSURE_EQUALS( "assgin failed", deque, big );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_insert( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing insert range: " << item_size << endl;
	item_t::set_start_id( 0 );
		{
		int const len0( countof ( _testData_[0] ) );
		int const len1( countof ( _testData_[1] ) );
		proto_t proto( _testData_[0], _testData_[0] + len0 );
		deque_type deque( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end() - 1, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin() + deque.size() / 2, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin() + deque.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin() + deque.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin() + deque.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end() - deque.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end() - deque.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		}
		{
		int const len0( countof ( _testData_[0] ) );
		int const len1( countof ( _testData_[1] ) );
		proto_t proto( _testData_[0], _testData_[0] + len0 );
		deque_type deque( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end() - 1, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin() + deque.size() / 2, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin() + deque.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin() + deque.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin() + deque.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end() - deque.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end() - deque.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

TUT_UNIT_TEST( 17, "insert range" )
	test_insert<1>();
	test_insert<2>();
	test_insert<3>();
	test_insert<7>();
	test_insert<15>();
	test_insert<16>();
	test_insert<17>();
	test_insert<64>();
	test_insert<128>();
	test_insert<200>();
	test_insert<511>();
	test_insert<512>();
	test_insert<513>();
	test_insert<640>();
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "speed test" )
	TIME_CONSTRAINT_EXEMPT();
	typedef HDeque<int> deque_type;
	int long LOOPS( 1000000 );
	proto_t proto;
	deque_type deque;
	double long st( 0 );
	double long yt( 0 );
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.push_back( static_cast<int>( i ) );
		clog << "*speed* std::deque<>::push_back() = " << static_cast<int long>( st = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			deque.push_back( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HDeque<>::push_back() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
	clog << "*speed* HDeque<>::push_back() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.pop_back();
		clog << "*speed* std::deque<>::pop_back() = " << static_cast<int long>( st = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			deque.pop_back();
		clog << "*speed* yaal::hcore::HDeque<>::pop_back() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
	clog << "*speed* HDeque<>::pop_back() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.push_front( static_cast<int>( i ) );
		clog << "*speed* std::deque<>::push_front() = " << static_cast<int long>( st = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			deque.push_front( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HDeque<>::push_front() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
	clog << "*speed* HDeque<>::push_front() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.pop_front();
		clog << "*speed* std::deque<>::pop_front() = " << static_cast<int long>( st = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
		{
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			deque.pop_front();
		clog << "*speed* yaal::hcore::HDeque<>::pop_front() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
		}
	clog << "*speed* HDeque<>::pop_front() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
TUT_TEARDOWN()

}

