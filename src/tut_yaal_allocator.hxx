/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_allocator.hxx - this file is integral part of `tress' project.

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

#include <set>

namespace tut {

template<typename T>
struct booking_allocator {
	typedef T* pointer;
	typedef T const* const_pointer;
	typedef T& reference;
	typedef T const& const_reference;
	typedef T value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	template<typename U>
	struct rebind {
		typedef booking_allocator<U> other;
	};
	typedef std::set<pointer> book_t;
	book_t _book;
	int _id;
	bool _valid;
	booking_allocator( int id_ )
		: _book(), _id( id_ ), _valid( true ) {
	}
	template<typename U>
	booking_allocator( booking_allocator<U> const& allocator_ )
		: _book( allocator_._book ), _id( allocator_._id ), _valid( allocator_._valid ) {

	}
	void swap( booking_allocator& allocator_ ) {
		using std::swap;
		swap( _book, allocator_._book );
		swap( _id, allocator_._id );
		swap( _valid, allocator_._valid );
	}
	pointer allocate( size_type n ) {
		pointer p( reinterpret_cast<pointer>( ::operator new ( sizeof ( T ) * n ) ) );
		_book.insert( p );
		return ( p );
	}
	pointer allocate( size_type n, const_pointer ) {
		pointer p( reinterpret_cast<pointer>( ::operator new ( sizeof ( T ) * n ) ) );
		_book.insert( p );
		return ( p );
	}
	void deallocate( pointer p, size_type ) {
		typename book_t::iterator it( _book.find( p ) );
		if ( it != _book.end() )
			_book.erase( it );
		else
			_valid = false;
		::operator delete ( p );
	}
	pointer address( reference r ) const {
		return ( &r );
	}
	const_pointer address( const_reference s ) const {
		return ( &s );
	}
	size_type max_size( void ) const {
		return ( 0x1fffffff );
	}
/*! \brief true iff you can deallocate with booking_allocator<Y> something allocated with booking_allocator<X>.
 */
	template<typename U>
	bool operator == ( booking_allocator<U> const& allocator_ ) const {
		return ( _id == allocator_._id );
	}
	template<typename U>
	bool operator != ( booking_allocator<U> const& allocator_ ) const {
		return ( _id != allocator_._id );
	}
	void construct( pointer p, const_reference t ) {
		new ( p ) T( t );
	}
	void destroy( pointer p ) {
		p->~T();
	}
	bool is_valid( void ) const {
		return ( _valid );
	}
private:
	booking_allocator& operator = ( booking_allocator const& );
};

}

