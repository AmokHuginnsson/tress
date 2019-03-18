/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/filesystem.hxx>
#include <yaal/tools/huginn/string.hxx>

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::huginn;
using namespace tress::tut_helpers;

namespace tress {

int tut_yaal_tools_hhuginn_base::_refCount = 0;
yaal::hcore::HMutex tut_yaal_tools_hhuginn_base::_refCountMutex;

HIntrospector::HIntrospector( void )
	: _callStacks()
	, _identifierNamesLog()
	, _identifierNamesLogUp() {
}

void HIntrospector::do_introspect( yaal::tools::HIntrospecteeInterface& introspectee_ ) {
	yaal::tools::HHuginn::call_stack_t callStack( introspectee_.get_call_stack() );
	if ( setup._verbose && setup._debug ) {
		clog << "-------------------------------------------------------------------" << endl;
		for ( yaal::tools::HHuginn::HCallSite const& cs : callStack ) {
			clog << cs.file() << ":" << cs.line() << ":" << cs.column() << ":" << cs.context() << endl;
		}
		clog << "-------------------------------------------------------------------" << endl;
	}
	_callStacks.push_back( yaal::move( callStack ) );
	yaal::tools::HHuginn::HCallSite const& cs( _callStacks.back().front() );
	identifier_names_t in;
	for ( HIntrospecteeInterface::HVariableView const& vv : introspectee_.get_locals( 0 ) ) {
		in.emplace_back( vv.name(), !! vv.value() ? to_string( vv.value() ) : "<undefined>" );
	}
	_identifierNamesLog.insert( make_pair( make_pair( cs.file(), cs.line() ), in ) );
	in.clear();
	for ( HIntrospecteeInterface::HVariableView const& vv : introspectee_.get_locals( 1 ) ) {
		in.emplace_back( vv.name(), !! vv.value() ? to_string( vv.value() ) : "<undefined>" );
	}
	_identifierNamesLogUp.insert( make_pair( make_pair( cs.file(), cs.line() ), in ) );
}

yaal::tools::HHuginn::call_stack_t const* HIntrospector::get_stack( yaal::hcore::HString const& file_, int line_ ) {
	yaal::tools::HHuginn::call_stack_t const* callStack( nullptr );
	for ( yaal::tools::HHuginn::call_stack_t const& cs : _callStacks ) {
		if ( ! cs.is_empty() ) {
			yaal::tools::HHuginn::HCallSite const& callSite( cs.front() );
			if ( ( callSite.file() == file_ ) && ( callSite.line() == line_ ) ) {
				callStack = &cs;
				break;
			}
		}
	}
	return ( callStack );
}

HIntrospector::identifier_names_t const* HIntrospector::get_locals( yaal::hcore::HString const& file_, int line_ ) {
	identifier_names_log_t::const_iterator it( _identifierNamesLog.find( make_pair( file_, line_ ) ) );
	return ( it != _identifierNamesLog.end() ?  &it->second : nullptr );
}

HIntrospector::identifier_names_t const* HIntrospector::get_locals_up( yaal::hcore::HString const& file_, int line_ ) {
	identifier_names_log_t::const_iterator it( _identifierNamesLogUp.find( make_pair( file_, line_ ) ) );
	return ( it != _identifierNamesLogUp.end() ?  &it->second : nullptr );
}

tut_yaal_tools_hhuginn_base::tut_yaal_tools_hhuginn_base( void )
	: _resultCache()
	, _sourceCache()
	, _mutex() {
	M_PROLOG
	HLock l( _refCountMutex );
	if ( _refCount == 0 ) {
		huginn::initialize_packages();
	}
	++ _refCount;
	return;
	M_EPILOG
}

tut_yaal_tools_hhuginn_base::~tut_yaal_tools_hhuginn_base( void ) {
	M_PROLOG
	HLock l( _refCountMutex );
	if ( _refCount == 1 ) {
		huginn::cleanup_packages();
	}
	-- _refCount;
	M_DESTRUCTOR_EPILOG
}

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
	ENSURE_EQUALS( "bad result value", static_cast<huginn::HString*>( res.raw() )->value(), _resultCache );
	return;
}

namespace {
bool is_op( code_point_t c ) {
	char const ops[] = "+-*/%|&^!=:?<>";
	return ( is_ascii( c ) && ( strchr( ops, static_cast<char>( c.get() ) ) != nullptr ) );
}
hcore::HString prettify( yaal::hcore::HString const& src_ ) {
	hcore::HString out;
	int tabs( 0 );
	hcore::HString nl;
	for ( int i( 0 ); i < src_.get_length(); ++ i ) {
		code_point_t curr( src_[i] );
		if ( ( curr == '"' ) || ( curr == '\'' ) ) {
			out.push_back( curr );
			for ( int s( i + 1 ); i < src_.get_length(); ++ s ) {
				code_point_t scan( src_[s] );
				if ( scan == '\\' ) {
					out.push_back( scan );
					++ s;
					if ( s < src_.get_length() ) {
						out.push_back( src_[s] );
					}
					continue;
				}
				if ( scan == curr ) {
					i = s;
					break;
				}
				out.push_back( scan );
			}
		}
		if ( ( i + 1 ) < src_.get_length() ) {
			code_point_t next( src_[i + 1] );
			if ( curr == '{' ) {
				++ tabs;
			} else if ( next == '}' ) {
				-- tabs;
			}
			nl.assign( "\n", 1 );
			if ( tabs > 0 ) {
				nl.append( tabs, '\t'_ycp );
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
					code_point_t next2( src_[n] );
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
						if ( ( src_.substr( n, len ) == kw ) && ! is_lower( src_[ n + len ] ) ) {
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
				out.push_back( ' '_ycp );
			} else if ( ( curr != '(' ) && ( curr != ' ' ) && ( next == ')' ) ) {
				out.push_back( curr );
				out.push_back( ' '_ycp );
			} else if ( ( curr == ')' ) && ( next == '{' ) ) {
				out.push_back( curr );
				out.push_back( ' '_ycp );
			} else if ( ( curr != ' ' ) && ( next == '(' ) ) {
				char const kws[][8] = {
					"if", "for", "catch", "return", "switch", "case", "while"
				};
				bool keyword( false );
				for ( char const* kw : kws ) {
					int len( static_cast<int>( strlen( kw ) ) );
					if ( ( i > ( len + 1 ) ) && ( ! is_lower( src_[i - len] ) ) && ( src_.substr( i + 1 - len, len ) == kw ) ) {
						keyword = true;
						break;
					}
				}
				out.push_back( curr );
				if ( keyword ) {
					out.push_back( ' '_ycp );
				}
			} else if ( curr == ',' ) {
				out.push_back( curr );
				out.push_back( ' '_ycp );
			} else if ( ( curr != ' ' ) && ( ! is_op( curr ) ) && is_op( next ) ) {
				out.push_back( curr );
				out.push_back( ' '_ycp );
			} else if ( is_op( curr ) && ( ! is_op( next ) ) && ( next != ' ' ) ) {
				out.push_back( curr );
				out.push_back( ' '_ycp );
			} else if ( curr == '\t' ) {
				/* skip */
			} else {
				out.push_back( curr );
				if ( curr == '\n' ) {
					out.append( nl.substr( 1 ) );
				}
			}
		} else {
			out.push_back( curr );
		}
	}
	return ( out );
}
}

yaal::tools::HHuginn::ptr_t tut_yaal_tools_hhuginn_base::compile_function( yaal::hcore::HString const& source_ ) {
	if ( setup._verbose ) {
		if ( setup._debug ) {
			clog << "// HUGINN TEST CASE START" << endl;
		}
		clog << prettify( source_ ) << endl;
		if ( setup._debug ) {
			clog << "// HUGINN TEST CASE FINISH" << endl;
		}
	}
	HHuginn::ptr_t h( make_pointer<HHuginn>() );
	/* load code */ {
		HLock l( _mutex );
		_sourceCache.set_buffer( source_ );
		h->load( _sourceCache );
	}
	h->preprocess();
	bool p( h->parse() );
	if ( !p ) {
		clog << h->error_message() << endl;
	}
	ENSURE( "parse failed", p );
	bool c( h->compile() );
	if ( !c ) {
		clog << h->error_message() << endl;
	}
	ENSURE( "compilation failed", c );
	return ( h );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute(
	yaal::tools::HHuginn::ptr_t huginn_,
	hcore::HString const& source_,
	yaal::tools::HHuginn::paths_t const& modulePaths_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_,
	HIntrospector* introspector_
) {
	if ( setup._verbose ) {
		if ( setup._debug ) {
			clog << "// HUGINN TEST CASE START" << endl;
		}
		clog << prettify( source_ ) << endl;
		if ( setup._debug ) {
			clog << "// HUGINN TEST CASE FINISH" << endl;
		}
	}
	HLock l( _mutex );
	_sourceCache.set_buffer( source_ );
	huginn_->load( _sourceCache );
	l.unlock();
	huginn_->preprocess();
	bool p( huginn_->parse() );
	if ( !p ) {
		clog << huginn_->error_message() << endl;
	}
	ENSURE( "parse failed", p );
	bool c( huginn_->compile( modulePaths_, huginnCompilerSetup_, introspector_ ) );
	if ( !c ) {
		clog << huginn_->error_message() << endl;
	}
	ENSURE( "compilation failed", c );
	bool e( huginn_->execute() );
	if ( !e ) {
		clog << huginn_->error_message() << endl;
	}
	ENSURE( "execution failed", e );
	HHuginn::value_t res( huginn_->result() );
	l.lock();
	_resultCache.assign( to_string( res, huginn_.raw() ) );
	return ( _resultCache );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute(
	hcore::HString const& source_,
	yaal::tools::HHuginn::paths_t const& modulePaths_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_,
	HIntrospector* introspector_
) {
	return ( execute( make_pointer<HHuginn>(), source_, modulePaths_, huginnCompilerSetup_, introspector_ ) );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute(
	hcore::HString const& source_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_,
	HIntrospector* introspector_
) {
	return ( execute( make_pointer<HHuginn>(), source_, {}, huginnCompilerSetup_, introspector_ ) );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute_except(
	yaal::tools::HHuginn::ptr_t huginn_,
	hcore::HString const& source_,
	yaal::tools::HHuginn::paths_t const& modulePaths_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_
) {
	if ( setup._verbose ) {
		if ( setup._debug ) {
			clog << "// HUGINN TEST CASE START" << endl;
		}
		clog << prettify( source_ ) << endl;
		if ( setup._debug ) {
			clog << "// HUGINN TEST CASE FINISH" << endl;
		}
	}
	huginn_->set_max_call_stack_size( 128 );
	HLock l( _mutex );
	_sourceCache.set_buffer( source_ );
	huginn_->load( _sourceCache );
	l.unlock();
	huginn_->preprocess();
	bool p( huginn_->parse() );
	if ( !p ) {
		clog << huginn_->error_message() << endl;
	}
	ENSURE( "parse failed", p );
	bool c( huginn_->compile( modulePaths_, huginnCompilerSetup_ ) );
	if ( !c ) {
		clog << huginn_->error_message() << endl;
	}
	ENSURE( "compilation failed", c );
	bool e( huginn_->execute() );
	ENSURE_NOT( "execution did not fail!", e );
	_resultCache.assign( huginn_->error_message() );
	return ( _resultCache );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute_except(
	hcore::HString const& source_,
	yaal::tools::HHuginn::paths_t const& modulePaths_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_
) {
	return ( execute_except( make_pointer<HHuginn>(), source_, modulePaths_, huginnCompilerSetup_ ) );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute_except(
	hcore::HString const& source_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_
) {
	return ( execute_except( make_pointer<HHuginn>(), source_, {}, huginnCompilerSetup_ ) );
}

tut_yaal_tools_hhuginn_base::OHuginnResult tut_yaal_tools_hhuginn_base::execute_result( yaal::hcore::HString const& source_ ) {
	if ( setup._verbose ) {
		if ( setup._debug ) {
			clog << "// HUGINN TEST CASE START" << endl;
		}
		clog << prettify( source_ ) << endl;
		if ( setup._debug ) {
			clog << "// HUGINN TEST CASE FINISH" << endl;
		}
	}
	HHuginn::ptr_t h( make_pointer<HHuginn>() );
	HLock l( _mutex );
	_sourceCache.set_buffer( source_ );
	h->load( _sourceCache );
	l.unlock();
	h->preprocess();
	bool p( h->parse() );
	if ( !p ) {
		clog << h->error_message() << endl;
	}
	ENSURE( "parse failed", p );
	bool c( h->compile() );
	if ( !c ) {
		clog << h->error_message() << endl;
	}
	ENSURE( "compilation failed", c );
	bool e( h->execute() );
	if ( !e ) {
		clog << h->error_message() << endl;
	}
	ENSURE( "execution failed", e );
	HHuginn::value_t r( h->result() );
	ENSURE( "nothing returned", !! r );
	return ( OHuginnResult{ h, r } );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute_incremental(
	yaal::tools::HHuginn::ptr_t huginn_,
	lines_t const& lines_,
	yaal::tools::HHuginn::paths_t const& modulePaths_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_,
	HIntrospector* introspector_
) {
	hcore::HString head( "main(){\n" );
	hcore::HString foot( "}\n" );
	hcore::HString okImports;
	hcore::HString okDefinitions;
	hcore::HString okBody;
	HStringStream src;
	HStringStream out;
	_resultCache.clear();
	huginn_->set_output_stream( out );
	huginn_->reset();
	for ( OLine const& line : lines_ ) {
		hcore::HString imports( okImports );
		hcore::HString definitions( okDefinitions );
		hcore::HString body( okBody );
		if ( line._type == OLine::TYPE::CODE ) {
			body.append( line._text ).append( ! line._text.is_empty() && ( line._text.back() != '\n' ) ? "\n" : "" );
		} else if ( line._type == OLine::TYPE::IMPORT ) {
			imports.append( line._text ).append( ! line._text.is_empty() && ( line._text.back() != '\n' ) ? "\n" : "" );
		} else if ( line._type == OLine::TYPE::DEFINITION ) {
			definitions.append( line._text ).append( ! line._text.is_empty() && ( line._text.back() != '\n' ) ? "\n" : "" );
		}
		src.clear();
		src << imports << definitions << head << body << foot;
		huginn_->reset();
		if ( setup._verbose ) {
			clog << prettify( src.string() ) << endl;
		}
		huginn_->load( src );
		huginn_->preprocess();
		bool p( huginn_->parse() );
		if ( !p ) {
			clog << huginn_->error_message() << endl;
		}
		ENSURE( "parse failed", p );
		bool c( huginn_->compile( modulePaths_, huginnCompilerSetup_, introspector_ ) );
		if ( !c ) {
			_resultCache.append( huginn_->error_message() );
			continue;
		}
		ENSURE( "compilation failed", c );
		bool e( huginn_->execute() );
		if ( !e ) {
			_resultCache.append( huginn_->error_message() );
			continue;
		}
		ENSURE( "execution failed!", e );
		HHuginn::value_t r( huginn_->result() );
		ENSURE( "nothing returned", !! r );
		okImports = imports;
		okDefinitions = definitions;
		okBody = body;
		_resultCache.append( out.string() );
		_resultCache.trim_right();
		out.reset();
		_resultCache.append( to_string( r, huginn_.raw() ) );
	}
	return ( _resultCache );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute_incremental(
	lines_t const& lines_,
	yaal::tools::HHuginn::paths_t const& modulePaths_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_,
	HIntrospector* introspector_
) {
	return ( execute_incremental( make_pointer<HHuginn>(), lines_, modulePaths_, huginnCompilerSetup_, introspector_ ) );
}

hcore::HString const& tut_yaal_tools_hhuginn_base::execute_incremental(
	lines_t const& lines_,
	yaal::tools::HHuginn::compiler_setup_t huginnCompilerSetup_,
	HIntrospector* introspector_
) {
	return ( execute_incremental( make_pointer<HHuginn>(), lines_, {}, huginnCompilerSetup_, introspector_ ) );
}

}

