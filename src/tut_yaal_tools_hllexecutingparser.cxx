/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hllexecutingparser.cxx - this file is integral part of `tress' project.

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

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace yaal;
using namespace yaal::hcore;

namespace yaal {

namespace tools {

namespace ll {

class HRule {
public:
	typedef HRule this_type;
	typedef HBoundCall<> action_t;
	typedef HBoundCall<> executor_t;
	typedef HArray<executor_t> executors_t;
	typedef yaal::hcore::HPointer<HRule> ptr_t;
protected:
	ptr_t _rule;
	action_t _action;
	executors_t _excutors;
	bool _matched;
public:
	HRule( void )
		: _rule(), _action(), _excutors(), _matched( false )
		{}
public:
	HRule( HRule const& rule_ )
		: _rule( rule_.clone() ), _action(), _excutors(), _matched( false )
		{}
	virtual ~HRule( void )
		{}
	HRule operator[]( action_t action_ ) {
		M_PROLOG
		return ( HRule( _rule, action_ ) );
		M_EPILOG
	}
	bool operator()( HString const& input_ ) {
		M_PROLOG
		return ( parse( input_.begin(), input_.end() ) != input_.end() );
		M_EPILOG
	}
	bool operator()( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		return ( parse( first_, last_ ) != last_ );
		M_EPILOG
	}
	void operator()( void ) {
		M_PROLOG
		execute();
		return;
		M_EPILOG
	}
	void execute( void ) {
		M_PROLOG
		M_ENSURE( _matched );
		do_execute();
		for ( executors_t::iterator it( _excutors.begin() ), end( _excutors.end() ); it != end; ++ it )
			(*it)();
		return;
		M_EPILOG
	}
	void cancel_execution( void ) {
		M_PROLOG
		_matched = false;
		do_cancel_execution();
		_excutors.clear();
		return;
		M_EPILOG
	}
	HString::const_iterator parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		HString::const_iterator it( do_parse( first_, last_ ) );
		_matched = it != first_;
		return ( it );
		M_EPILOG
	}
	ptr_t clone( void ) const {
		M_PROLOG
		return ( do_clone() );
		M_EPILOG
	}
	bool is_optional( void ) const {
		M_PROLOG
		return ( do_is_optional() );
		M_EPILOG
	}
private:
	HRule( ptr_t rule_, action_t action_ )
		: _rule( rule_ ), _action( action_ ), _excutors(), _matched( false )
		{}
protected:
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		HString::const_iterator ret( !! _rule ? _rule->parse( first_, last_ ) : first_ );
		if ( ( ret == last_ ) && !! _action )
			_excutors.push_back( _action );
		return ( ret );
		M_EPILOG
	}
	virtual void do_execute( void ) {
		M_PROLOG
		if ( !! _rule )
			_rule->execute();
		return;
		M_EPILOG
	}
	virtual void do_cancel_execution( void ) {
		M_PROLOG
		if ( !! _rule )
			_rule->cancel_execution();
		return;
		M_EPILOG
	}
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( !! _rule ? _rule->clone() : ptr_t() );
		M_EPILOG
	}
	virtual bool do_is_optional( void ) const
		{ return ( false ); }
	static HString::const_iterator skip_space( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		while ( ( first_ != last_ ) && isspace( *first_ ) )
			++ first_;
		return ( first_ );
		M_EPILOG
	}
};

typedef HExceptionT<HRule> HRuleException;

class HFollows : public HRule {
	typedef yaal::hcore::HList<HRule::ptr_t> rules_t;
	rules_t _rules;
public:
	typedef HFollows this_type;
	typedef HRule base_type;
	HFollows( HRule const& predecessor_, HRule const& successor_ )
		: HRule(), _rules() {
		M_PROLOG
		_rules.push_back( predecessor_.clone() );
		_rules.push_back( successor_.clone() );
		return;
		M_EPILOG
	}
	HFollows( HFollows const& follows_ )
		: HRule(), _rules() {
		M_PROLOG
		for ( rules_t::const_iterator it( follows_._rules.begin() ), end( follows_._rules.end() ); it != end; ++ it )
			_rules.push_back( (*it)->clone() );
		return;
		M_EPILOG
	}
	HFollows( HFollows const& predecessors_, HRule const& successor_ )
		: HRule(), _rules() {
		M_PROLOG
		for ( rules_t::const_iterator it( predecessors_._rules.begin() ), end( predecessors_._rules.end() ); it != end; ++ it )
			_rules.push_back( (*it)->clone() );
		_rules.push_back( successor_.clone() );
		return;
		M_EPILOG
	}
	virtual ~HFollows( void )
		{}
protected:
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( ptr_t( new HFollows( *this ) ) );
		M_EPILOG
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		HString::const_iterator orig( first_ );
		bool matched( true );
		for ( rules_t::iterator it( _rules.begin() ), end( _rules.end() ); it != end; ++ it ) {
			HString::const_iterator old( first_ );
			first_ = (*it)->parse( first_, last_ );
			if ( ( first_ == old ) && ( !(*it)->is_optional() ) ) {
				matched = false;
				break;
			}
		}
		return ( matched ? first_ : orig );
		M_EPILOG
	}
	virtual void do_cancel_execution( void ) {
		M_PROLOG
		for ( rules_t::iterator it( _rules.begin() ), end( _rules.end() ); it != end; ++ it )
			(*it)->cancel_execution();
		return;
		M_EPILOG
	}
	virtual void do_execute( void ) {
		M_PROLOG
		for ( rules_t::iterator it( _rules.begin() ), end( _rules.end() ); it != end; ++ it )
			(*it)->execute();
		return;
		M_EPILOG
	}
};

typedef HExceptionT<HFollows, HRuleException> HFollowsException;

class HKleeneStar : public HRule {
public:
	typedef HKleeneStar this_type;
	typedef HRule base_type;
	HKleeneStar( HRule const& rule_ )
		: HRule( rule_ )
		{}
	HKleeneStar( HKleeneStar const& kleeneStar_ )
		: HRule( *kleeneStar_._rule )
		{}
	virtual ~HKleeneStar( void )
		{}
protected:
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( ptr_t( new HKleeneStar( *this ) ) );
		M_EPILOG
	}
	virtual bool do_is_optional( void ) const
		{ return ( true ); }
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		HString::const_iterator old( last_ );
		while ( ( first_ != last_ ) && ( first_ != old ) )
			first_ = HRule::do_parse( old = first_, last_ );
		return ( first_ );
		M_EPILOG
	}
};

typedef HExceptionT<HKleeneStar, HRuleException> HKleeneStarException;

class HKleenePlus : public HRule {
public:
	typedef HKleenePlus this_type;
	typedef HRule base_type;
	HKleenePlus( HRule const& rule_ )
		: HRule( rule_ )
		{}
	HKleenePlus( HKleenePlus const& kleenePlus_ )
		: HRule( *kleenePlus_._rule )
		{}
	virtual ~HKleenePlus( void )
		{}
protected:
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( ptr_t( new HKleenePlus( *this ) ) );
		M_EPILOG
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		HString::const_iterator old( last_ );
		while ( ( first_ != last_ ) && ( first_ != old ) )
			first_ = HRule::do_parse( old = first_, last_ );
		return ( first_ );
		M_EPILOG
	}
};

typedef HExceptionT<HKleenePlus, HRuleException> HKleenePlusException;

class HAlternative : public HRule {
	typedef yaal::hcore::HList<HRule::ptr_t> rules_t;
	rules_t _rules;
public:
	typedef HAlternative this_type;
	typedef HRule base_type;
	HAlternative( HRule const& choice1_, HRule const& choice2_ )
		: HRule(), _rules() {
		M_PROLOG
		_rules.push_back( choice1_.clone() );
		_rules.push_back( choice2_.clone() );
		return;
		M_EPILOG
	}
	HAlternative( HAlternative const& alternative_ )
		: HRule(), _rules() {
		M_PROLOG
		for ( rules_t::const_iterator it( alternative_._rules.begin() ), end( alternative_._rules.end() ); it != end; ++ it )
			_rules.push_back( (*it)->clone() );
		return;
		M_EPILOG
	}
	HAlternative( HAlternative const& alternative_, HRule const& choice_ )
		: HRule(), _rules() {
		M_PROLOG
		for ( rules_t::const_iterator it( alternative_._rules.begin() ), end( alternative_._rules.end() ); it != end; ++ it )
			_rules.push_back( (*it)->clone() );
		_rules.push_back( choice_.clone() );
		return;
		M_EPILOG
	}
protected:
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( ptr_t( new HAlternative( *this ) ) );
		M_EPILOG
	}
};

typedef HExceptionT<HAlternative, HRuleException> HAlternativeException;

class HOptional : public HRule {
protected:
	virtual bool do_is_optional( void ) const
		{ return ( true ); }
};

namespace {

typedef HExceptionT<HOptional, HRuleException> HOptionalException;

HFollows operator >> ( HRule const& predecessor_, HRule const& successor_ ) {
	M_PROLOG
	return ( HFollows( predecessor_, successor_ ) );
	M_EPILOG
}

HFollows operator >> ( HFollows const& predecessors_, HRule const& successor_ ) {
	M_PROLOG
	return ( HFollows( predecessors_, successor_ ) );
	M_EPILOG
}

HAlternative operator | ( HRule const& choice1_, HRule const& choice2_ ) {
	M_PROLOG
	return ( HAlternative( choice1_, choice2_ ) );
	M_EPILOG
}

HAlternative operator | ( HAlternative const& alternative_, HRule const& choice_ ) {
	M_PROLOG
	return ( HAlternative( alternative_, choice_ ) );
	M_EPILOG
}

HKleeneStar operator* ( HRule const& rule_ ) {
	M_PROLOG
	return ( HKleeneStar( rule_ ) );
	M_EPILOG
}

HKleenePlus operator+ ( HRule const& rule_ ) {
	M_PROLOG
	return ( HKleenePlus( rule_ ) );
	M_EPILOG
}

}

class HReal : public HRule {
	typedef HBoundCall<void ( double const& )> action_double_t;
	typedef HBoundCall<void ( double long const& )> action_double_long_t;
	typedef HBoundCall<void ( HNumber const& )> action_number_t;
	typedef HBoundCall<void ( HString const& )> action_string_t;
	action_double_t _actionDouble;
	action_double_long_t _actionDoubleLong;
	action_number_t _actionNumber;
	action_string_t _actionString;
	HString _cache;
	typedef enum {
		START = 0,
		MINUS = 1,
		INTEGRAL = 2,
		DOT = 3,
		DECIMAL = 4
	} real_paring_state_t;
public:
	typedef HReal this_type;
	typedef HRule base_type;
	HReal( void )
		: HRule(), _actionDouble(), _actionDoubleLong(),
		_actionNumber(), _actionString(), _cache()
		{}
	HReal( action_double_t actionDouble_, action_double_long_t actionDoubleLong_,
			action_number_t actionNumber_, action_string_t actionString_ )
		: HRule(), _actionDouble( actionDouble_ ), _actionDoubleLong( actionDoubleLong_ ),
		_actionNumber( actionNumber_ ), _actionString( actionString_ ), _cache()
		{}
	HReal( HReal const& real_ )
		: HRule(), _actionDouble( real_._actionDouble ), _actionDoubleLong( real_._actionDoubleLong ),
		_actionNumber( real_._actionNumber ), _actionString( real_._actionString ), _cache( real_._cache ) {}
	using HRule::operator[];
	HReal operator[]( action_double_t const& action_ ) {
		M_PROLOG
		return ( HReal( action_, action_double_long_t(), action_number_t(), action_string_t() ) );
		M_EPILOG
	}
	HReal operator[]( action_double_long_t const& action_ ) {
		M_PROLOG
		return ( HReal( action_double_t(), action_, action_number_t(), action_string_t() ) );
		M_EPILOG
	}
	HReal operator[]( action_number_t const& action_ ) {
		M_PROLOG
		return ( HReal( action_double_t(), action_double_long_t(), action_, action_string_t() ) );
		M_EPILOG
	}
	HReal operator[]( action_string_t const& action_ ) {
		M_PROLOG
		return ( HReal( action_double_t(), action_double_long_t(), action_number_t(), action_ ) );
		M_EPILOG
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		HString::const_iterator scan( skip_space( first_, last_ ) );
		_cache.clear();
		real_paring_state_t state( START );
		while ( scan != last_ ) {
			bool stop( false );
			char ch( *scan );
			switch ( state ) {
				case ( START ): {
					if ( isdigit( ch ) )
						state = INTEGRAL;
					else if ( ch == '-' )
						state = MINUS;
					else if ( ch == '.' )
						state = DOT;
					else
						stop = true;
				} break;
				case ( MINUS ):
				case ( INTEGRAL ): {
					if ( isdigit( ch ) )
						state = INTEGRAL;
					else if ( ch == '.' )
						state = DOT;
					else
						stop = true;
				} break;
				case ( DOT ):
				case ( DECIMAL ): {
					if ( isdigit( ch ) )
						state = DECIMAL;
					else
						stop = true;
				} break;
				default: {
					M_ASSERT( ! "invalid hardcoded state" );
				}
			}
			if ( stop )
				break;
			_cache.push_back( *scan );
			++ scan;
		}
		if ( state >= INTEGRAL ) {
			first_ = scan;
			if ( !! _actionDouble ) {
				double d( lexical_cast<double>( _cache ) );
				_excutors.push_back( call( _actionDouble, d ) );
			} else if ( !! _actionDoubleLong ) {
				double long dl( lexical_cast<double long>( _cache ) );
				_excutors.push_back( call( _actionDoubleLong, dl ) );
			} else if ( !! _actionNumber ) {
				_excutors.push_back( call( _actionNumber, _cache ) );
			} else if ( !! _actionString ) {
				_excutors.push_back( call( _actionString, _cache ) );
			}
		}
		return ( first_ );
		M_EPILOG
	}
protected:
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( ptr_t( new HReal( *this ) ) );
		M_EPILOG
	}
} real;

typedef HExceptionT<HReal, HRuleException> HRealException;

class HInteger : public HRule {
	typedef HBoundCall<void ( int long const& )> action_int_long_t;
	typedef HBoundCall<void ( int const& )> action_int_t;
	typedef HBoundCall<void ( HNumber const& )> action_number_t;
	typedef HBoundCall<void ( HString const& )> action_string_t;
	action_int_long_t _actionIntLong;
	action_int_t _actionInt;
	action_number_t _actionNumber;
	action_string_t _actionString;
	HString _cache;
	typedef enum {
		START = 0,
		MINUS = 1,
		DIGIT = 2
	} real_paring_state_t;
public:
	typedef HInteger this_type;
	typedef HRule base_type;
	HInteger( void )
		: HRule(), _actionIntLong(), _actionInt(),
		_actionNumber(), _actionString(), _cache()
		{}
	HInteger( action_int_long_t actionDouble_, action_int_t actionDoubleLong_,
			action_number_t actionNumber_, action_string_t actionString_ )
		: HRule(), _actionIntLong( actionDouble_ ), _actionInt( actionDoubleLong_ ),
		_actionNumber( actionNumber_ ), _actionString( actionString_ ), _cache()
		{}
	HInteger( HInteger const& real_ )
		: HRule(), _actionIntLong( real_._actionIntLong ), _actionInt( real_._actionInt ),
		_actionNumber( real_._actionNumber ), _actionString( real_._actionString ), _cache( real_._cache ) {}
	using HRule::operator[];
	HInteger operator[]( action_int_long_t const& action_ ) {
		M_PROLOG
		return ( HInteger( action_, action_int_t(), action_number_t(), action_string_t() ) );
		M_EPILOG
	}
	HInteger operator[]( action_int_t const& action_ ) {
		M_PROLOG
		return ( HInteger( action_int_long_t(), action_, action_number_t(), action_string_t() ) );
		M_EPILOG
	}
	HInteger operator[]( action_number_t const& action_ ) {
		M_PROLOG
		return ( HInteger( action_int_long_t(), action_int_t(), action_, action_string_t() ) );
		M_EPILOG
	}
	HInteger operator[]( action_string_t const& action_ ) {
		M_PROLOG
		return ( HInteger( action_int_long_t(), action_int_t(), action_number_t(), action_ ) );
		M_EPILOG
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		HString::const_iterator scan( skip_space( first_, last_ ) );
		_cache.clear();
		real_paring_state_t state( START );
		while ( scan != last_ ) {
			bool stop( false );
			char ch( *scan );
			switch ( state ) {
				case ( START ): {
					if ( isdigit( ch ) )
						state = DIGIT;
					else if ( ch == '-' )
						state = MINUS;
					else
						stop = true;
				} break;
				case ( MINUS ):
				case ( DIGIT ): {
					if ( isdigit( ch ) )
						state = DIGIT;
					else
						stop = true;
				} break;
				default: {
					M_ASSERT( ! "invalid hardcoded state" );
				}
			}
			if ( stop )
				break;
			_cache.push_back( *scan );
			++ scan;
		}
		if ( state >= DIGIT ) {
			first_ = scan;
			if ( !! _actionIntLong ) {
				int long il( lexical_cast<int long>( _cache ) );
				_excutors.push_back( call( _actionIntLong, il ) );
			} else if ( !! _actionInt ) {
				int i( lexical_cast<int>( _cache ) );
				_excutors.push_back( call( _actionInt, i ) );
			} else if ( !! _actionNumber ) {
				_excutors.push_back( call( _actionNumber, _cache ) );
			} else if ( !! _actionString ) {
				_excutors.push_back( call( _actionString, _cache ) );
			}
		}
		return ( first_ );
		M_EPILOG
	}
protected:
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( ptr_t( new HInteger( *this ) ) );
		M_EPILOG
	}
} integer;

typedef HExceptionT<HInteger, HRuleException> HIntegerException;

class HCharacter : public HRule {
	typedef HBoundCall<void ( char const& )> action_t;
	char _character;
	action_t _action;
public:
	typedef HCharacter this_type;
	typedef HRule base_type;
	HCharacter( char character_ = 0 )
		: HRule(), _character( character_ ), _action()
		{}
	HCharacter( char character_, action_t action_ )
		: HRule(), _character( character_ ), _action( action_ )
		{}
	HCharacter( HCharacter const& character_ )
		: HRule(), _character( character_._character ), _action( character_._action ) {}
	virtual ~HCharacter( void )
		{}
	using HRule::operator[];
	HCharacter operator[]( action_t const& action_ ) {
		M_PROLOG
		return ( HCharacter( _character, action_ ) );
		M_EPILOG
	}
	HCharacter operator() ( char character_ ) {
		M_PROLOG
		return ( HCharacter( character_, _action ) );
		M_EPILOG
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		M_PROLOG
		M_ENSURE( first_ != last_ );
		HString::const_iterator scan( skip_space( first_, last_ ) );
		char c( *scan );
		if ( _character ) {
			if ( ! _character || ( c == _character ) ) {
				if ( !! _action )
					_excutors.push_back( call( _action, c ) );
				++ scan;
				first_ = scan;
			}
		}
		return ( first_ );
		M_EPILOG
	}
protected:
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( ptr_t( new HCharacter( *this ) ) );
		M_EPILOG
	}
} character;

typedef HExceptionT<HCharacter, HRuleException> HCharacterException;

namespace {

HFollows operator >> ( char character_, HRule const& successor_ ) {
	M_PROLOG
	return ( HFollows( HCharacter( character_ ), successor_  ) );
	M_EPILOG
}

}

class HString : public HRule {
	typedef HBoundCall<void ( HString const& )> action_t;
	hcore::HString _string;
	action_t _action;
public:
	typedef HString this_type;
	typedef HRule base_type;
	HString( hcore::HString const& string_ = hcore::HString() )
		: HRule(), _string( string_ ), _action()
		{}
	HString( hcore::HString const& string_, action_t action_ )
		: HRule(), _string( string_ ), _action( action_ )
		{}
	HString( HString const& string_ )
		: HRule(), _string( string_._string ), _action( string_._action ) {}
	virtual ~HString( void )
		{}
	using HRule::operator[];
	HString operator[]( action_t const& action_ ) {
		M_PROLOG
		return ( HString( _string, action_ ) );
		M_EPILOG
	}
	HString operator() ( hcore::HString const& string_ ) {
		M_PROLOG
		return ( HString( string_, _action ) );
		M_EPILOG
	}
	virtual hcore::HString::const_iterator do_parse( hcore::HString::const_iterator first_, hcore::HString::const_iterator last_ ) {
		M_PROLOG
		M_ENSURE( first_ != last_ );
		return ( first_ );
		M_EPILOG
	}
protected:
	virtual ptr_t do_clone( void ) const {
		M_PROLOG
		return ( ptr_t( new HString( *this ) ) );
		M_EPILOG
	}
} string;

typedef HExceptionT<HString, HRuleException> HStringException;

namespace {

HFollows operator >> ( char const* string_, HRule const& successor_ ) {
	M_PROLOG
	return ( HFollows( HString( string_ ), successor_  ) );
	M_EPILOG
}

HFollows operator >> ( hcore::HString const& string_, HRule const& successor_ ) {
	M_PROLOG
	return ( HFollows( HString( string_ ), successor_  ) );
	M_EPILOG
}

}

template<typename container_t>
HBoundCall<void ( typename container_t::value_type const& )> push_back( container_t& container ) {
	M_PROLOG
	return ( call( &container_t::push_back, &container, _1 ) );
	M_EPILOG
}

}

}

}

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

using namespace yaal::tools::ll;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hllexecutingparser );
TUT_TEST_GROUP( tut_yaal_tools_hllexecutingparser, "yaal::tools::HLLExecutingParser" );

TUT_UNIT_TEST( 1, "empty parser" )
	HRule r;
	hcore::HString text( "1+2" );
	ENSURE( "empty parser consumed input", r.parse( text.begin(), text.end() ) == text.begin() );
	ENSURE( "empty parser succeeded on non empty input", r( text ) );
	try {
		r();
		FAIL( "execution of empty parser succeeded" );
	} catch ( HRuleException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "the test" )
	HArray<double> v;
	if ( real[push_back(v)]( "3.141592653589793" ) )
		cout << "1: failed to consume input" << endl;
	HRule r( real[push_back(v)] >> *( ',' >> real[push_back(v)] ) );
	r( "3.141592653589793, -2.718281828459045, 17" );
	r();
	if ( r( "3.141592653589793, -2.718281828459045, 17, kupa" ) )
		cout << "2: failed to consume input" << endl;
	copy( v.begin(), v.end(), stream_iterator( cout, endl ) );
TUT_TEARDOWN()

}

