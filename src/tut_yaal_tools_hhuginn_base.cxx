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

#include <cstring>

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

namespace {
bool is_op( char c ) {
	char const ops[] = "+-*/%|&^!=:?<>";
	return ( strchr( ops, c ) != nullptr );
}
hcore::HString prettify( yaal::hcore::HString const& src_ ) {
	HString out;
	int tabs( 0 );
	HString nl;
	for ( int i( 0 ); i < src_.get_length(); ++ i ) {
		char curr( src_[i] );
		if ( ( i + 1 ) < src_.get_length() ) {
			char next( src_[i + 1] );
			if ( curr == '{' ) {
				++ tabs;
			} else if ( next == '}' ) {
				-- tabs;
			}
			nl.assign( "\n", 1 );
			if ( tabs > 0 ) {
				nl.append( tabs, '\t' );
			}
			if ( ( curr == '{' ) || ( curr == ';' ) ) {
				out.push_back( curr );
				if ( next != '\n' ) {
					out.append( nl );
				}
			} else if ( ( curr == '}' ) && ( next != '\n' ) ) {
				out.push_back( curr );
				int n( i + 1 );
				while ( n < src_.get_length() ) {
					char next2( src_[n] );
					if ( ( next2 != ' ' ) && ( next2 != '\t' ) ) {
						break;
					}
					++ n;
				}
				bool keyword( false );
				if ( n < src_.get_length() ) {
					char const kws[][6] = {
						"else",
						"catch",
						"break"
					};
					for ( char const* kw : kws ) {
						int len( static_cast<int>( strlen( kw ) ) );
						if ( ( strncmp( kw, src_.raw() + n, static_cast<size_t>( len ) ) == 0 ) && ! islower( src_.raw()[ n + len ] ) ) {
							keyword = true;
							break;
						}
					}
				}
				if ( ! keyword ) {
					out.append( nl );
				}
			} else if ( ( curr == '(' ) && ( next != ' ' ) && ( next != ')' ) ) {
				out.push_back( curr );
				out.push_back( ' ' );
			} else if ( ( curr != '(' ) && ( curr != ' ' ) && ( next == ')' ) ) {
				out.push_back( curr );
				out.push_back( ' ' );
			} else if ( ( curr == ')' ) && ( next == '{' ) ) {
				out.push_back( curr );
				out.push_back( ' ' );
			} else if ( ( curr != ' ' ) && ( next == '(' ) ) {
				char const kws[][8] = {
					"if", "for", "catch", "return", "switch", "case", "while"
				};
				bool keyword( false );
				for ( char const* kw : kws ) {
					int len( static_cast<int>( strlen( kw ) ) );
					if ( ( i > ( len + 1 ) ) && ( ! islower( src_[i - len] ) ) && ( strncmp( kw, src_.raw() + i + 1 - len, static_cast<size_t>( len ) ) == 0 ) ) {
						keyword = true;
						break;
					}
				}
				out.push_back( curr );
				if ( keyword ) {
					out.push_back( ' ' );
				}
			} else if ( curr == ',' ) {
				out.push_back( curr );
				out.push_back( ' ' );
			} else if ( ( curr != ' ' ) && ( ! is_op( curr ) ) && is_op( next ) ) {
				out.push_back( curr );
				out.push_back( ' ' );
			} else if ( is_op( curr ) && ( ! is_op( next ) ) && ( next != ' ' ) ) {
				out.push_back( curr );
				out.push_back( ' ' );
			} else if ( curr == '\t' ) {
				/* skip */
			} else {
				out.push_back( curr );
				if ( curr == '\n' ) {
					out.append( nl.raw() + 1 );
				}
			}
		} else {
			out.push_back( curr );
		}
	}
	return ( out );
}
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute(
	hcore::HString const& source_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_
) {
	if ( setup._verbose ) {
		clog << prettify( source_ ) << endl;
	}
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
	l.lock();
	_resultCache.assign( to_string( res ) );
	return ( _resultCache );
}


}

