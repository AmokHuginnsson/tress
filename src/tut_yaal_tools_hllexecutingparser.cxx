/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hllexecutingparser.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
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
	typedef yaal::hcore::HPointer<HRule> ptr_t;
	virtual ~HRule( void )
		{}
	bool operator()( HString const& input_ )
		{ return ( do_parse( input_.begin(), input_.end() ) != input_.end() ); }
	bool operator()( HString::const_iterator first_, HString::const_iterator last_ )
		{ return ( do_parse( first_, last_ ) != last_ ); }
	HString::const_iterator parse( HString::const_iterator first_, HString::const_iterator last_ )
		{ return ( do_parse( first_, last_ ) ); }
	ptr_t clone( void ) const {
		return ( do_clone() );
	}
protected:
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator ) {
		return ( first_ );
	}
	static HString::const_iterator skip_space( HString::const_iterator& first_, HString::const_iterator last_ ) {
		while ( ( first_ != last_ ) && isspace( *first_ ) )
			++ first_;
		return ( first_ );
	}
	virtual ptr_t do_clone( void ) const = 0;
};

class HFollows : public HRule {
	typedef yaal::hcore::HList<HRule::ptr_t> rules_t;
	rules_t _rules;
public:
	typedef HFollows this_type;
	typedef HRule base_type;
	HFollows( HRule const& predecessor_, HRule const& successor_ )
		: _rules() {
		_rules.push_back( predecessor_.clone() );
		_rules.push_back( successor_.clone() );
	}
	HFollows( HFollows const& follows_ )
		: _rules() {
		for ( rules_t::const_iterator it( follows_._rules.begin() ), end( follows_._rules.end() ); it != end; ++ it )
			_rules.push_back( (*it)->clone() );
	}
	virtual ~HFollows( void )
		{}
protected:
	ptr_t do_clone( void ) const {
		return ( ptr_t( new HFollows( *this ) ) );
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		HString::const_iterator orig( first_ );
		HString::const_iterator old( last_ );
		for ( rules_t::iterator it( _rules.begin() ), end( _rules.end() ); ( old != first_ ) && ( it != end ); ++ it )
			first_ = (*it)->parse( old = first_, last_ );
		return ( first_ == last_ ? first_ : orig );
	}
};

class HKleeneStar : public HRule {
	HRule::ptr_t _rule;
public:
	typedef HKleeneStar this_type;
	typedef HRule base_type;
	HKleeneStar( HRule const& rule_ )
		: _rule( rule_.clone() )
		{}
	HKleeneStar( HKleeneStar const& kleeneStar_ )
		: _rule( kleeneStar_._rule->clone() )
		{}
	virtual ~HKleeneStar( void )
		{}
protected:
	ptr_t do_clone( void ) const {
		return ( ptr_t( new HKleeneStar( *this ) ) );
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		for ( HString::const_iterator old( last_ ); ( first_ != old ) && ( first_ != last_ ); ) {
			first_ = _rule->parse( old = first_, last_ );
		}
		return ( first_ );
	}
};

HFollows operator >> ( HRule const& predecessor_, HRule const& successor_ ) {
	return ( HFollows( predecessor_, successor_ ) );
}

HKleeneStar operator* ( HRule const& rule_ ) {
	return ( HKleeneStar( rule_ ) );
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
		: _actionDouble(), _actionDoubleLong(),
		_actionNumber(), _actionString(), _cache()
		{}
	HReal( action_double_t actionDouble_, action_double_long_t actionDoubleLong_,
			action_number_t actionNumber_, action_string_t actionString_ )
		: _actionDouble( actionDouble_ ), _actionDoubleLong( actionDoubleLong_ ),
		_actionNumber( actionNumber_ ), _actionString( actionString_ ), _cache()
		{}
	HReal operator[]( action_double_t const& action_ ) {
		return ( HReal( action_, action_double_long_t(), action_number_t(), action_string_t() ) );
	}
	HReal operator[]( action_double_long_t const& action_ ) {
		return ( HReal( action_double_t(), action_, action_number_t(), action_string_t() ) );
	}
	HReal operator[]( action_number_t const& action_ ) {
		return ( HReal( action_double_t(), action_double_long_t(), action_, action_string_t() ) );
	}
	HReal operator[]( action_string_t const& action_ ) {
		return ( HReal( action_double_t(), action_double_long_t(), action_number_t(), action_ ) );
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		first_ = skip_space( first_, last_ );
		_cache.clear();
		real_paring_state_t state( START );
		HString::const_iterator scan( first_ );
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
				_actionDouble( d );
			} else if ( !! _actionDoubleLong ) {
				double long dl( lexical_cast<double long>( _cache ) );
				_actionDoubleLong( dl );
			} else if ( !! _actionNumber ) {
				_actionNumber( _cache );
			} else if ( !! _actionString ) {
				_actionString( _cache );
			}
		}
		return ( first_ );
	}
protected:
	ptr_t do_clone( void ) const {
		return ( ptr_t( new HReal( *this ) ) );
	}
} real;

class HCharacter : public HRule {
	typedef HBoundCall<void ( char const& )> action_t;
	char _character;
	action_t _action;
public:
	typedef HCharacter this_type;
	typedef HRule base_type;
	HCharacter( char character_ = 0 )
		: _character( character_ ), _action() {}
	HCharacter( char character_, action_t action_ )
		: _character( character_ ), _action( action_ )
		{}
	virtual ~HCharacter( void )
		{}
	HCharacter operator[]( action_t const& action_ ) {
		return ( HCharacter( _character, action_ ) );
	}
	HCharacter operator() ( char character_ ) {
		return ( HCharacter( character_, _action ) );
	}
	virtual HString::const_iterator do_parse( HString::const_iterator first_, HString::const_iterator last_ ) {
		first_ = skip_space( first_, last_ );
		M_ENSURE( first_ != last_ );
		char c( *first_ );
		M_ENSURE( ! _character || ( c == _character ) );
		if ( !! _action )
			_action( c );
		++ first_;
		return ( first_ );
	}
protected:
	ptr_t do_clone( void ) const {
		return ( ptr_t( new HCharacter( *this ) ) );
	}
} character;

HFollows operator >> ( char character_, HRule const& successor_ ) {
	return ( HFollows( HCharacter( character_ ), successor_  ) );
}

template<typename container_t>
HBoundCall<void ( typename container_t::value_type const& )> push_back( container_t& container ) {
	return ( call( &container_t::push_back, &container, _1 ) );
}

}

}

}

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

using namespace yaal::tools::ll;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hllexecutingparser );
TUT_TEST_GROUP( tut_yaal_tools_hllexecutingparser, "yaal::tools::HLLExecutingParser" );

TUT_UNIT_TEST( 1, "the test" )
	HArray<double> v;
	if ( real[push_back(v)]( "3.141592653589793" ) )
		cout << "1: failed to consume input" << endl;
	if ( ( real[push_back(v)] >> *( ',' >> real[push_back(v)] ) )( "3.141592653589793, -2.718281828459045, 17, kupa" ) )
		cout << "2: failed to consume input" << endl;
	copy( v.begin(), v.end(), stream_iterator( cout, endl ) );
TUT_TEARDOWN()

}

