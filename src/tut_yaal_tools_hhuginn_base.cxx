/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn_base.cxx - this file is integral part of `tress' project.

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

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/filesystem.hxx>

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::huginn;
using namespace tress::tut_helpers;

namespace tress {

void tut_yaal_tools_hhuginn_base::test_file( hcore::HString const& name_ ) {
	filesystem::path_t p( "./data/" );
	p.append( name_ );
	HFile s( p, HFile::OPEN::READING );
	HHuginn h;
	HLock l( _mutex );
	s.read_until( _resultCache );
	_resultCache.shift_left( 2 );
	l.unlock();
	h.load( s );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	l.lock();
	HHuginn::value_t res( h.result() );
	ENSURE_EQUALS( "bad result type", res->type_id(), HHuginn::TYPE::STRING );
	ENSURE_EQUALS( "bad result value", static_cast<HHuginn::HString*>( res.raw() )->value(), _resultCache );
	return;
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute(
	hcore::HString const& source_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_
) {
	clog << source_ << endl;
	HHuginn h;
	HLock l( _mutex );
	_sourceCache.set_buffer( source_ );
	h.load( _sourceCache );
	l.unlock();
	h.preprocess();
	bool p( h.parse() );
	if ( !p ) {
		clog << h.error_message() << endl;
	}
	ENSURE( "parse failed", p );
	bool c( h.compile( huginnCompilerSetup_ ) );
	if ( !c ) {
		clog << h.error_message() << endl;
	}
	ENSURE( "compilation failed", c );
	bool e( h.execute() );
	if ( !e ) {
		clog << h.error_message() << endl;
	}
	ENSURE( "execution failed", e );
	HHuginn::value_t res( h.result() );
	ENSURE_EQUALS( "bad result type", res->type_id(), HHuginn::TYPE::STRING );
	l.lock();
	_resultCache.assign( static_cast<HHuginn::HString*>( res.raw() )->value() );
	return ( _resultCache );
}


}

