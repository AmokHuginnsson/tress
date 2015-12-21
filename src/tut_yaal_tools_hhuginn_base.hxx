/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn_base.hxx - this file is integral part of `tress' project.

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

#ifndef TUT_YAAL_TOOLS_HHUGINN_HXX_INCLUDED
#define TUT_YAAL_TOOLS_HHUGINN_HXX_INCLUDED 1

#include <yaal/tools/hhuginn.hxx>
#include "tut_helpers.hxx"
#include <TUT/tut.hpp>

namespace yaal {
namespace tools {
inline std::ostream& operator << ( std::ostream& out, HHuginn::type_id_t t_ ) {
	out << huginn::type_name( t_ );
	return ( out );
}
inline std::ostream& operator << ( std::ostream& out, HHuginn::TYPE t_ ) {
	out << huginn::type_name( t_ );
	return ( out );
}
}
}

namespace tress {

struct tut_yaal_tools_hhuginn_base : public tut_helpers::simple_mock<tut_yaal_tools_hhuginn_base> {
	typedef tut_helpers::simple_mock<tut_yaal_tools_hhuginn_base> base_type;
	typedef char const* prog_src_t;
	yaal::hcore::HString _resultCache;
	yaal::tools::HStringStream _sourceCache;
	yaal::hcore::HMutex _mutex;
	tut_yaal_tools_hhuginn_base( void )
		: _resultCache()
		, _sourceCache()
		, _mutex() {
		return;
	}
	virtual ~tut_yaal_tools_hhuginn_base( void ) {}
	void test_file( yaal::hcore::HString const& );
	yaal::hcore::HString const& execute( yaal::hcore::HString const& );
};

}

#endif /* not TUT_YAAL_TOOLS_HHUGINN_HXX_INCLUDED */

