#ifndef TUT_TERMINAL
#define TUT_TERMINAL

#include "tut.hpp"
#include <yaal/tools/ansi.hxx>
#include <yaal/tools/hterminal.hxx>

namespace yaal {

namespace ansi {

inline std::ostream& operator << ( std::ostream& os_, yaal::ansi::HSequence const& seq_ ) {
	if ( tress::setup._color
		&& (
			( ( &os_ != &std::cerr ) && ( &os_ != &std::cout ) && ( &os_ != &std::clog ) )
				|| yaal::tools::is_a_tty( os_ )
		)
	) {
		os_  << *seq_;
	}
	return os_;
}

}

}

#endif

