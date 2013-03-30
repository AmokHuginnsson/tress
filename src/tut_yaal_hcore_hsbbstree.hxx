/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hsbbstree.hxx - this file is integral part of `tress' project.

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

#ifndef TUT_YAAL_HCORE_HSBBSTREE_HXX_INCLUDED
#define TUT_YAAL_HCORE_HSBBSTREE_HXX_INCLUDED 1

#include <TUT/tut.hpp>

#include "tut_helpers.hxx"

namespace tut {

typedef yaal::hcore::HSet<int> set_t;
void helper_stress_just_insert( set_t&, int );
void helper_stress_just_erase( set_t&, int );

}

#endif /* #ifndef TUT_YAAL_HCORE_HSBBSTREE_HXX_INCLUDED */
