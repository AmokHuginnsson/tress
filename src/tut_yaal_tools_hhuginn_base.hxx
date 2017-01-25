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
inline std::ostream& operator << ( std::ostream& out, yaal::tools::HHuginn::type_id_t t_ ) {
	out << huginn::type_name( t_ );
	return ( out );
}
inline std::ostream& operator << ( std::ostream& out, yaal::tools::HHuginn::TYPE t_ ) {
	out << huginn::type_name( t_ );
	return ( out );
}
}
}

namespace tress {

struct tut_yaal_tools_hhuginn_base : public tut_helpers::simple_mock<tut_yaal_tools_hhuginn_base> {
	struct OLine {
		enum class TYPE {
			CODE,
			DEFINITION
		};
		yaal::hcore::HString _text;
		TYPE _type;
		OLine( yaal::hcore::HString const& text_, TYPE type_ = TYPE::CODE )
			: _text( text_ )
			, _type( type_ ) {
		}
	};
	typedef yaal::hcore::HArray<OLine> lines_t;
	typedef tut_helpers::simple_mock<tut_yaal_tools_hhuginn_base> base_type;
	typedef char const* prog_src_t;
	struct OHuginnResult {
		yaal::tools::HHuginn::ptr_t _huginn;
		yaal::tools::HHuginn::value_t _result;
	};
	yaal::hcore::HString _resultCache;
	yaal::tools::HStringStream _sourceCache;
	yaal::hcore::HMutex _mutex;
	static int _refCount;
	static yaal::hcore::HMutex _refCountMutex;
	tut_yaal_tools_hhuginn_base( void );
	virtual ~tut_yaal_tools_hhuginn_base( void );
	void test_file( yaal::hcore::HString const& );
	yaal::hcore::HString const& execute(
		yaal::hcore::HString const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::DEFAULT
	);
	yaal::hcore::HString const& execute_except(
		yaal::hcore::HString const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::DEFAULT
	);
	OHuginnResult execute_result( yaal::hcore::HString const& );
	yaal::hcore::HString execute_incremental(
		lines_t const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::BE_SLOPPY
	);
};

}

#endif /* not TUT_YAAL_TOOLS_HHUGINN_HXX_INCLUDED */

