/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/color.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_color );
TUT_TEST_GROUP( tut_yaal_tools_color, "yaal::tools::COLOR" );

TUT_UNIT_TEST( "from_string" )
	ENSURE_EQUALS( "reset", COLOR::from_string( "reset" ) + 0, COLOR::ATTR_RESET + 0 );
	ENSURE_EQUALS( "bold", COLOR::from_string( "bold" ) + 0, COLOR::ATTR_BOLD + 0 );
	ENSURE_EQUALS( "underline", COLOR::from_string( "underline" ) + 0, COLOR::ATTR_UNDERLINE + 0 );
	ENSURE_EQUALS( "reverse", COLOR::from_string( "reverse" ) + 0, COLOR::ATTR_REVERSE + 0 );
	ENSURE_EQUALS( "blink", COLOR::from_string( "blink" ) + 0, COLOR::ATTR_BLINK + 0 );
	ENSURE_EQUALS( "red", COLOR::from_string( "red" ) + 0, COLOR::FG_RED + 0 );
	ENSURE_EQUALS( "green", COLOR::from_string( "green" ) + 0, COLOR::FG_GREEN + 0 );
	ENSURE_EQUALS( "blue", COLOR::from_string( "blue" ) + 0, COLOR::FG_BLUE + 0 );
	ENSURE_EQUALS( "brown", COLOR::from_string( "brown" ) + 0, COLOR::FG_BROWN + 0 );
	ENSURE_EQUALS( "black", COLOR::from_string( "black" ) + 0, COLOR::FG_BLACK + 0 );
	ENSURE_EQUALS( "cyan", COLOR::from_string( "cyan" ) + 0, COLOR::FG_CYAN + 0 );
	ENSURE_EQUALS( "magenta", COLOR::from_string( "magenta" ) + 0, COLOR::FG_MAGENTA + 0 );
	ENSURE_EQUALS( "gray", COLOR::from_string( "gray" ) + 0, COLOR::FG_GRAY + 0 );
	ENSURE_EQUALS( "brightred", COLOR::from_string( "brightred" ) + 0, COLOR::FG_BRIGHTRED + 0 );
	ENSURE_EQUALS( "brightgreen", COLOR::from_string( "brightgreen" ) + 0, COLOR::FG_BRIGHTGREEN + 0 );
	ENSURE_EQUALS( "brightblue", COLOR::from_string( "brightblue" ) + 0, COLOR::FG_BRIGHTBLUE + 0 );
	ENSURE_EQUALS( "brightcyan", COLOR::from_string( "brightcyan" ) + 0, COLOR::FG_BRIGHTCYAN + 0 );
	ENSURE_EQUALS( "brightmagenta", COLOR::from_string( "brightmagenta" ) + 0, COLOR::FG_BRIGHTMAGENTA + 0 );
	ENSURE_EQUALS( "yellow", COLOR::from_string( "yellow" ) + 0, COLOR::FG_YELLOW + 0 );
	ENSURE_EQUALS( "white", COLOR::from_string( "white" ) + 0, COLOR::FG_WHITE + 0 );
	ENSURE_EQUALS( "lightgray", COLOR::from_string( "lightgray" ) + 0, COLOR::FG_LIGHTGRAY + 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "fg_to_bg" )
	ENSURE_EQUALS( "red", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_RED ) ), static_cast<int>( COLOR::BG_RED ) );
	ENSURE_EQUALS( "green", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_GREEN ) ), static_cast<int>( COLOR::BG_GREEN ) );
	ENSURE_EQUALS( "blue", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_BLUE ) ), static_cast<int>( COLOR::BG_BLUE ) );
	ENSURE_EQUALS( "brown", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_BROWN ) ), static_cast<int>( COLOR::BG_BROWN ) );
	ENSURE_EQUALS( "black", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_BLACK ) ), static_cast<int>( COLOR::BG_BLACK ) );
	ENSURE_EQUALS( "cyan", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_CYAN ) ), static_cast<int>( COLOR::BG_CYAN ) );
	ENSURE_EQUALS( "magenta", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_MAGENTA ) ), static_cast<int>( COLOR::BG_MAGENTA ) );
	ENSURE_EQUALS( "gray", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_GRAY ) ), static_cast<int>( COLOR::BG_GRAY ) );
	ENSURE_EQUALS( "brightred", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_BRIGHTRED ) ), static_cast<int>( COLOR::BG_BRIGHTRED ) );
	ENSURE_EQUALS( "brightgreen", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_BRIGHTGREEN ) ), static_cast<int>( COLOR::BG_BRIGHTGREEN ) );
	ENSURE_EQUALS( "brightblue", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_BRIGHTBLUE ) ), static_cast<int>( COLOR::BG_BRIGHTBLUE ) );
	ENSURE_EQUALS( "brightcyan", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_BRIGHTCYAN ) ), static_cast<int>( COLOR::BG_BRIGHTCYAN ) );
	ENSURE_EQUALS( "brightmagenta", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_BRIGHTMAGENTA ) ), static_cast<int>( COLOR::BG_BRIGHTMAGENTA ) );
	ENSURE_EQUALS( "yellow", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_YELLOW ) ), static_cast<int>( COLOR::BG_YELLOW ) );
	ENSURE_EQUALS( "white", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_WHITE ) ), static_cast<int>( COLOR::BG_WHITE ) );
	ENSURE_EQUALS( "lightgray", static_cast<int>( COLOR::fg_to_bg( COLOR::FG_LIGHTGRAY ) ), static_cast<int>( COLOR::BG_LIGHTGRAY ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "to_ansi" )
	ENSURE_EQUALS( "reset", *COLOR::to_ansi( COLOR::ATTR_RESET ), *ansi::reset );
	ENSURE_EQUALS( "bold", *COLOR::to_ansi( COLOR::ATTR_BOLD ), *ansi::bold );
	ENSURE_EQUALS( "underline", *COLOR::to_ansi( COLOR::ATTR_UNDERLINE ), *ansi::underline );
	ENSURE_EQUALS( "reverse", *COLOR::to_ansi( COLOR::ATTR_REVERSE ), *ansi::reverse );
	ENSURE_EQUALS( "blink", *COLOR::to_ansi( COLOR::ATTR_BLINK ), *ansi::blink );
	ENSURE_EQUALS( "default", *COLOR::to_ansi( COLOR::ATTR_DEFAULT ), *ansi::reset );
	ENSURE_EQUALS( "default", *COLOR::to_ansi( static_cast<COLOR::color_t>( 100 ) ), *ansi::reset );
	ENSURE_EQUALS( "red", *COLOR::to_ansi( COLOR::FG_RED ), *ansi::red );
	ENSURE_EQUALS( "green", *COLOR::to_ansi( COLOR::FG_GREEN ), *ansi::green );
	ENSURE_EQUALS( "blue", *COLOR::to_ansi( COLOR::FG_BLUE ), *ansi::blue );
	ENSURE_EQUALS( "brown", *COLOR::to_ansi( COLOR::FG_BROWN ), *ansi::brown );
	ENSURE_EQUALS( "black", *COLOR::to_ansi( COLOR::FG_BLACK ), *ansi::black );
	ENSURE_EQUALS( "cyan", *COLOR::to_ansi( COLOR::FG_CYAN ), *ansi::cyan );
	ENSURE_EQUALS( "magenta", *COLOR::to_ansi( COLOR::FG_MAGENTA ), *ansi::magenta );
	ENSURE_EQUALS( "gray", *COLOR::to_ansi( COLOR::FG_GRAY ), *ansi::gray );
	ENSURE_EQUALS( "brightred", *COLOR::to_ansi( COLOR::FG_BRIGHTRED ), *ansi::brightred );
	ENSURE_EQUALS( "brightgreen", *COLOR::to_ansi( COLOR::FG_BRIGHTGREEN ), *ansi::brightgreen );
	ENSURE_EQUALS( "brightblue", *COLOR::to_ansi( COLOR::FG_BRIGHTBLUE ), *ansi::brightblue );
	ENSURE_EQUALS( "brightcyan", *COLOR::to_ansi( COLOR::FG_BRIGHTCYAN ), *ansi::brightcyan );
	ENSURE_EQUALS( "brightmagenta", *COLOR::to_ansi( COLOR::FG_BRIGHTMAGENTA ), *ansi::brightmagenta );
	ENSURE_EQUALS( "yellow", *COLOR::to_ansi( COLOR::FG_YELLOW ), *ansi::yellow );
	ENSURE_EQUALS( "white", *COLOR::to_ansi( COLOR::FG_WHITE ), *ansi::white );
	ENSURE_EQUALS( "lightgray", *COLOR::to_ansi( COLOR::FG_LIGHTGRAY ), *ansi::lightgray );
TUT_TEARDOWN()

}

