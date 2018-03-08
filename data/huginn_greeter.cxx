/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <yaal/tools/hhuginn.hxx>
#include <yaal/tools/huginn/objectfactory.hxx>
#include <yaal/tools/huginn/thread.hxx>
#include <yaal/tools/huginn/runtime.hxx>
#include <yaal/tools/huginn/helper.hxx>
#include <yaal/tools/huginn/packagefactory.hxx>
M_VCSID( "$Id: " __ID__ " $" )
M_VCSID( "$Id: " __TID__ " $" )

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::huginn;

namespace tress {

class HGreeter : public HHuginn::HValue {
public:
	HGreeter( HHuginn::HClass* class_ )
		: HValue( class_ ) {
		return;
	}
	static HHuginn::value_t greet( huginn::HThread* thread_, HHuginn::value_t*, HHuginn::values_t& values_, int position_ ) {
		M_PROLOG
		char const name[] = "Greeter.greet";
		verify_arg_count( name, values_, 1, 2, thread_, position_ );
		verify_arg_type( name, values_, 0, HHuginn::TYPE::STRING, ARITY::MULTIPLE, thread_, position_ );
		HString how( "Hello, " );
		if ( values_.get_size() == 2 ) {
			verify_arg_type( name, values_, 1, HHuginn::TYPE::STRING, ARITY::MULTIPLE, thread_, position_ );
			how = get_string( values_[1] );
		}
		HObjectFactory& of( thread_->object_factory() );
		return ( of.create_string( how + get_string( values_[0] ) ) );
		M_EPILOG
	}
};

namespace package_factory {

class HGreeterCreator : public HPackageCreatorInterface {
protected:
	virtual HHuginn::value_t do_new_instance( HRuntime* );
} greetCreator;

HHuginn::value_t HGreeterCreator::do_new_instance( HRuntime* runtime_ ) {
	M_PROLOG
	HHuginn::class_t c(
		runtime_->create_class(
			"Greeter",
			nullptr,
			"The `Greeter` package provides greeting functionality."
		)
	);
	HHuginn::field_definitions_t fd{
		{ "greet", runtime_->create_method( c.raw(), &HGreeter::greet ), "( *who*, *how* = \"Hello, \" ) - greet *who* with *how*" },
	};
	c->redefine( nullptr, fd );
	runtime_->huginn()->register_class( c );
	return ( runtime_->object_factory()->create<HGreeter>( c.raw() ) );
	M_EPILOG
}

}

}

extern "C" {

M_EXPORT_SYMBOL HPackageCreatorInterface* get_package_creator( void );
M_EXPORT_SYMBOL HPackageCreatorInterface* get_package_creator( void ) {
	return ( &tress::package_factory::greetCreator );
}

}
