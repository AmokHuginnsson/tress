#include "tut_yaal_hcore_hsbbstree.hxx"

namespace tut {

void helper_stress_just_insert( set_t& ob, int val ) {
	ob.insert( val );
}

void helper_stress_just_insert( set_t& ob, int val, set_t::iterator it, bool forceHint ) {
	ob.insert( it, val, forceHint );
}

void helper_stress_just_erase( set_t& ob, int val ) {
	ob.insert( val );
}

}

