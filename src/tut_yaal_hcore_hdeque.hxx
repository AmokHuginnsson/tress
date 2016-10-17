/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hdeque_base.hxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#ifndef TUT_YAAL_HCORE_HDEQUE_HXX_INCLUDED
#define TUT_YAAL_HCORE_HDEQUE_HXX_INCLUDED 1

#include <deque>

#include <yaal/hcore/hexception.hxx>
#include <yaal/hcore/hfile.hxx>

#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wkeyword-macro"
#define private public
#define protected public
#pragma GCC diagnostic error "-Wkeyword-macro"
#pragma GCC diagnostic error "-Wpragmas"

#include <yaal/hcore/hdeque.hxx>

#undef protected
#undef private

#include "tut_helpers.hxx"
#include <TUT/tut.hpp>

namespace tress {

template<int const pack>
struct tut_yaal_hcore_hdeque_base : public tut_helpers::simple_mock<tut_yaal_hcore_hdeque_base<pack> > {
	typedef tut_helpers::simple_mock<tut_yaal_hcore_hdeque_base<pack> > base_type;
	struct StatePreserver {
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
	tut_yaal_hcore_hdeque_base( void )
		: base_type(), _statePreserver() {}
	virtual ~tut_yaal_hcore_hdeque_base( void ) {}
	template<typename deque_type>
	void check_consistency( deque_type const&, int long = 0 );
};

template<int const pack>
template<typename deque_type>
void tut_yaal_hcore_hdeque_base<pack>::check_consistency( deque_type const& deque_, int long extraItems ) {
	ENSURE_EQUALS( "deque size with respect to allocated objects", deque_.get_size(), deque_type::value_type::get_instance_count() - extraItems );
	int long firstChunkIndex( deque_._start / deque_type::VALUES_PER_CHUNK );
	int long lastChunkIndex( deque_._size > 0 ? ( ( deque_._start + deque_._size - 1 ) / deque_type::VALUES_PER_CHUNK ) : ( deque_._start / deque_type::VALUES_PER_CHUNK ) );
	int long chunksCount = deque_._chunks.template count_of<typename deque_type::value_type*>();
	int long usedChunks = deque_.used_chunks();
	typename deque_type::value_type const* const* chunks = deque_._chunks.template get<typename deque_type::value_type const*>();
	if ( setup._debug )
		yaal::hcore::clog << "firstChunkIndex: " << firstChunkIndex
			<< ", _statePreserver._firstChunkIndex: " << _statePreserver._firstChunkIndex
			<< ", lastChunkIndex: " << lastChunkIndex
			<< ", _statePreserver._lastChunkIndex: " << _statePreserver._lastChunkIndex
			<< ", deque_._size: " << deque_._size
			<< ", _statePreserver._size: " << _statePreserver._size
			<< ", chunksCount: " << chunksCount
			<< ", _statePreserver._availChunks: " << _statePreserver._availChunks << yaal::hcore::endl;
	if ( deque_._size > 0 ) {
		ENSURE( "chunk range bigger than chunks count", ( lastChunkIndex - firstChunkIndex ) < chunksCount );
		ENSURE( "last chunk outside avail chunks", lastChunkIndex < chunksCount );
	} else {
		ENSURE_EQUALS( "bad indexes for empty deque", lastChunkIndex, firstChunkIndex );
		ENSURE_EQUALS( "wrong number of used chunks calculated", deque_.used_chunks(), 0 );
	}
	ENSURE( "first chunk outside avail chunks", deque_._start >= 0 );
	if ( ( chunksCount > _statePreserver._availChunks )
			|| ( ( true /* deque_._size > _statePreserver._size */ )
				&& ( ( ( firstChunkIndex < chunksCount )
						&& ( firstChunkIndex != _statePreserver._firstChunkIndex )
						&& ( chunks[ firstChunkIndex ] == _statePreserver._firstChunk )
						&& ( ( _statePreserver._lastChunkIndex + 1 + yaal::abs( usedChunks - _statePreserver._usedChunks ) ) >= _statePreserver._availChunks ) )
					|| ( ( lastChunkIndex < chunksCount )
						&& ( lastChunkIndex != _statePreserver._lastChunkIndex )
						&& ( chunks[ lastChunkIndex ] == _statePreserver._lastChunk )
						&& ( ( _statePreserver._firstChunkIndex - yaal::abs( usedChunks - _statePreserver._usedChunks ) ) < 0 ) )
					) ) ) {
		int long startGap( firstChunkIndex );
		int long endGap( ( chunksCount - lastChunkIndex ) - 1 );
		if ( setup._debug )
			yaal::hcore::clog << "startGap: " << startGap << ", endGap: " << endGap << yaal::hcore::endl;
		if ( deque_._size > 0 )
			ENSURE_DISTANCE( "chunks are not centered", yaal::abs( endGap - startGap ), 0l, 2l );
	} else if ( _statePreserver._size
			&& ( chunksCount >= _statePreserver._availChunks )
			&& ( ( firstChunkIndex > _statePreserver._firstChunkIndex ) || ( lastChunkIndex < _statePreserver._lastChunkIndex ) ) ) {
		ENSURE( "unnecesarry chunks move", ( deque_._size < _statePreserver._size ) || ( chunksCount > _statePreserver._availChunks ) );
	}
	for ( int long i( 0 ); i < firstChunkIndex; ++ i )
		ENSURE_EQUALS( "not used chunks at the begining not cleared", chunks[ i ], static_cast<typename deque_type::value_type*>( NULL ) );
	for ( int long i( lastChunkIndex + 1 ); i < chunksCount; ++ i )
		ENSURE_EQUALS( "not used chunks at the end not cleared", chunks[ i ], static_cast<typename deque_type::value_type*>( NULL ) );
	if ( ( chunksCount > 0 ) && ! deque_._size )
		ENSURE_EQUALS( "not all chunks are nulled after resize( 0 )", chunks[ firstChunkIndex ], static_cast<typename deque_type::value_type*>( NULL ) );
	if ( deque_._size > 0 ) {
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

#ifndef __sun__
#pragma pack( push, 1 )
#else /* #ifndef __sun__ */
#pragma pack( 1 )
#endif /* #else #ifndef __sun__ */
	template<int const SIZE>
	class FixedArray {
		char _data[SIZE];
	};
#ifndef __sun__
#pragma pack( pop )
#else /* #ifndef __sun__ */
#pragma pack()
#endif /* #else #ifndef __sun__ */

}

#endif /* not TUT_YAAL_HCORE_HDEQUE_HXX_INCLUDED */

