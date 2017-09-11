/*
---           `yaal' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

  huginn_package.cxx - this file is integral part of `yaal' project.

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
	static HHuginn::value_t greet( huginn::HThread* thread_, HHuginn::value_t*, HHuginn::values_t const& values_, int position_ ) {
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
			HHuginn::field_definitions_t{
				{ "greet", runtime_->object_factory()->create<HHuginn::HClass::HMethod>( hcore::call( &HGreeter::greet, _1, _2, _3, _4 ) ), "( *who*, *how* = \"Hello, \" ) - greet *who* with *how*" },
			},
			"The `Greeter` package provides greeting functionality."
		)
	);
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
