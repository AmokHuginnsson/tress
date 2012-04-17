/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hpool.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.hpp>

#include <yaal/hcore/hpool.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hpool );
TUT_TEST_GROUP( tut_yaal_hcore_hpool, "yaal::hcore::HPool" );

TUT_UNIT_TEST( 1, "object space size" )
/* First test if tut_helpers::Sizer works as intentded. */
	STATIC_ASSERT( sizeof ( Sizer<1> ) == 1 );
	STATIC_ASSERT( sizeof ( Sizer<2> ) == 2 );
	STATIC_ASSERT( sizeof ( Sizer<3> ) == 3 );
	STATIC_ASSERT( sizeof ( Sizer<4> ) == 4 );
	STATIC_ASSERT( sizeof ( Sizer<5> ) == 5 );
	STATIC_ASSERT( sizeof ( Sizer<6> ) == 6 );
	STATIC_ASSERT( sizeof ( Sizer<7> ) == 7 );
	STATIC_ASSERT( sizeof ( Sizer<8> ) == 8 );
	STATIC_ASSERT( sizeof ( Sizer<9> ) == 9 );
	STATIC_ASSERT( sizeof ( Sizer<10> ) == 10 );
	STATIC_ASSERT( sizeof ( Sizer<11> ) == 11 );
	STATIC_ASSERT( sizeof ( Sizer<12> ) == 12 );
	STATIC_ASSERT( sizeof ( Sizer<13> ) == 13 );
	STATIC_ASSERT( sizeof ( Sizer<14> ) == 14 );
	STATIC_ASSERT( sizeof ( Sizer<15> ) == 15 );
	STATIC_ASSERT( sizeof ( Sizer<16> ) == 16 );
	STATIC_ASSERT( sizeof ( Sizer<17> ) == 17 );
	STATIC_ASSERT( sizeof ( Sizer<18> ) == 18 );
	STATIC_ASSERT( sizeof ( Sizer<19> ) == 19 );
	STATIC_ASSERT( sizeof ( Sizer<20> ) == 20 );
/* tut_helpers::Sizer works as intentded. */
	ENSURE_EQUALS( "bad object space size of char", HPool<char>::OBJECT_SPACE, 2 );
	ENSURE_EQUALS( "bad object space size of char", HPool<short>::OBJECT_SPACE, 4 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<3> >::OBJECT_SPACE, 4 );
	ENSURE_EQUALS( "bad object space size of char", HPool<int>::OBJECT_SPACE, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<5> >::OBJECT_SPACE, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<6> >::OBJECT_SPACE, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<7> >::OBJECT_SPACE, 8 );
#if TARGET_CPU_BITS == 64
	ENSURE_EQUALS( "bad object space size of char", HPool<int long long>::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<9> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<10> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<11> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<12> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<13> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<14> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<15> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<16> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<18> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<19> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<20> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<21> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<22> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<23> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<24> >::OBJECT_SPACE, 32 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<25> >::OBJECT_SPACE, 32 );
#elif TARGET_CPU_BITS == 32 /* #if TARGET_CPU_BITS == 64 */
	ENSURE_EQUALS( "bad object space size of char", HPool<int long long>::OBJECT_SPACE, 12 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<9> >::OBJECT_SPACE, 12 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<10> >::OBJECT_SPACE, 12 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<11> >::OBJECT_SPACE, 12 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<12> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<13> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<14> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<15> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<16> >::OBJECT_SPACE, 20 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<18> >::OBJECT_SPACE, 20 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<19> >::OBJECT_SPACE, 20 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<20> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<21> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<22> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<23> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<24> >::OBJECT_SPACE, 28 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<25> >::OBJECT_SPACE, 28 );
#else /* #elif TARGET_CPU_BITS == 32 #if TARGET_CPU_BITS == 64 */
#error Unsupported CPU bitness.
#endif /* #else #elif TARGET_CPU_BITS == 32 #if TARGET_CPU_BITS == 64 */
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "allocate one, deallocate, and allocate again" )
	HPool<int> p;
	/*
	 * Deallocation of last used object frees internal buffer.
	 * Newly allocated internal buffer may have different address
	 * than old one, so we need to make sure that deallocation will not
	 * make internal buffer unused.
	 */
	p.alloc();
	int* p0( p.alloc() );
	p.free( p0 );
	ENSURE_EQUALS( "allocation after deallocation failed", p.alloc(), p0 );
TUT_TEARDOWN()

}

