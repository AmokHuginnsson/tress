/* Read tress/LICENSE.md file for copyright and licensing information. */

#ifndef TUT_YAAL_HCORE_HSBBSTREE_HXX_INCLUDED
#define TUT_YAAL_HCORE_HSBBSTREE_HXX_INCLUDED 1

#include <TUT/tut.hpp>

#include "tut_helpers.hxx"

namespace tut {

typedef yaal::hcore::HSet<int> set_t;
void helper_stress_just_insert( set_t&, int );
void helper_stress_just_insert( set_t&, int, set_t::iterator, bool );
void helper_stress_just_erase( set_t&, int );

}

#endif /* #ifndef TUT_YAAL_HCORE_HSBBSTREE_HXX_INCLUDED */

