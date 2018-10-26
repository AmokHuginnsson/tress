/* Read tress/LICENSE.md file for copyright and licensing information. */

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

class HIntrospector : public yaal::tools::HIntrospectorInterface {
public:
	struct OVar {
		yaal::hcore::HString name;
		yaal::hcore::HString value;
		OVar( yaal::hcore::HString const& name_, yaal::hcore::HString const& value_ )
			: name( name_ )
			, value( value_ ) {
		}
	};
	typedef yaal::hcore::HArray<yaal::tools::HHuginn::call_stack_t> call_stacks_t;
	typedef yaal::hcore::HPair<yaal::hcore::HString, int> location_t;
	typedef yaal::hcore::HArray<OVar> identifier_names_t;
	typedef yaal::hcore::HHashMap<location_t, identifier_names_t> identifier_names_log_t;
private:
	call_stacks_t _callStacks;
	identifier_names_log_t _identifierNamesLog;
	identifier_names_log_t _identifierNamesLogUp;
public:
	HIntrospector( void );
	yaal::tools::HHuginn::call_stack_t const* get_stack( yaal::hcore::HString const&, int );
	identifier_names_t const* get_locals( yaal::hcore::HString const&, int );
	identifier_names_t const* get_locals_up( yaal::hcore::HString const&, int );
protected:
	virtual void do_introspect( yaal::tools::HIntrospecteeInterface& ) override;
};

struct ErrInfo {
	int _pos;
	int _line;
	int _col;
	char const* _msg;
};

struct tut_yaal_tools_hhuginn_base : public tut_helpers::simple_mock<tut_yaal_tools_hhuginn_base> {
	struct OLine {
		enum class TYPE {
			CODE,
			DEFINITION,
			IMPORT
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
		yaal::tools::HHuginn::ptr_t,
		yaal::hcore::HString const&,
		yaal::tools::HHuginn::paths_t const& = {},
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::DEFAULT,
		HIntrospector* = nullptr
	);
	yaal::hcore::HString const& execute(
		yaal::hcore::HString const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::DEFAULT,
		HIntrospector* = nullptr
	);
	yaal::hcore::HString const& execute(
		yaal::hcore::HString const&,
		yaal::tools::HHuginn::paths_t const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::DEFAULT,
		HIntrospector* = nullptr
	);
	yaal::hcore::HString const& execute_except(
		yaal::hcore::HString const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::DEFAULT
	);
	yaal::hcore::HString const& execute_except(
		yaal::tools::HHuginn::ptr_t,
		yaal::hcore::HString const&,
		yaal::tools::HHuginn::paths_t const& = {},
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::DEFAULT
	);
	yaal::hcore::HString const& execute_except(
		yaal::hcore::HString const&,
		yaal::tools::HHuginn::paths_t const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::DEFAULT
	);
	OHuginnResult execute_result( yaal::hcore::HString const& );
	yaal::hcore::HString const& execute_incremental(
		yaal::tools::HHuginn::ptr_t,
		lines_t const&,
		yaal::tools::HHuginn::paths_t const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::BE_SLOPPY,
		HIntrospector* = nullptr
	);
	yaal::hcore::HString const& execute_incremental(
		lines_t const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::BE_SLOPPY,
		HIntrospector* = nullptr
	);
	yaal::hcore::HString const& execute_incremental(
		lines_t const&,
		yaal::tools::HHuginn::paths_t const&,
		yaal::tools::HHuginn::compiler_setup_t = yaal::tools::HHuginn::COMPILER::BE_SLOPPY,
		HIntrospector* = nullptr
	);
};

}

#endif /* not TUT_YAAL_TOOLS_HHUGINN_HXX_INCLUDED */

