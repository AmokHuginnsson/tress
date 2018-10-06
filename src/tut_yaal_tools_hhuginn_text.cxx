/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_text : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_text( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_text, "yaal::tools::HHuginn.Text" );

TUT_UNIT_TEST( "repeat" )
	ENSURE_EQUALS(
		"Text.repeat failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"text.repeat(\"Huginn\",7);"
			"}\n"
		),
		"\"HuginnHuginnHuginnHuginnHuginnHuginnHuginn\""
	);
	ENSURE_EQUALS(
		"Text.repeat with bad count succeeded",
		execute_except(
			"import Text as text;\n"
			"main() {\n"
			"text.repeat(\"\",-1);"
			"}\n"
		),
		"*anonymous stream*:3:12: Negative repeat count: -1"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "split" )
	ENSURE_EQUALS(
		"Text.split failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"text.split(\"Ala ma kota.\",\" \");"
			"}\n"
		),
		"[\"Ala\", \"ma\", \"kota.\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "join" )
	ENSURE_EQUALS(
		"Text.join failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"text.join([\"Ala\", \"ma\", \"kota.\"], \"+\");"
			"}\n"
		),
		"\"Ala+ma+kota.\""
	);
	ENSURE_EQUALS(
		"Text.join on non collection succeeded",
		execute_except(
			"import Text as text;\n"
			"main() {\n"
			"text.join(\"\",\"\");"
			"}\n"
		),
		"*anonymous stream*:3:10: Text.join() first argument must be a flat uniform collection of strings, not a `string'."
	);
	ENSURE_EQUALS(
		"Text.join on non uniform succeeded",
		execute_except(
			"import Text as text;\n"
			"main() {\n"
			"text.join([\"\",'x'],\"\");"
			"}\n"
		),
		"*anonymous stream*:3:10: Text.join() first argument must be a flat uniform collection of strings, but it contains a `character'."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "distance" )
	ENSURE_EQUALS(
		"Text.distance failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"text.distance(\"Ala ma kota.\",\"Ola ma psa.\");"
			"}\n"
		),
		"4"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "hex, oct, bin" )
	ENSURE_EQUALS(
		"Text.hex, oct, bin failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"[text.hex(100),text.oct(100),text.bin(100), text.bin(0)];"
			"}\n"
		),
		"[\"0x64\", \"0o144\", \"0b1100100\", \"0b0\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream" )
	ENSURE_EQUALS(
		"Text.stream failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"s = text.stream(\"Ala ma kota.\\nKot pije mleko.\");"
			"return ( ( s.read_line(), s.read_line(), s.read_line() ) );\n"
			"}\n"
		),
		"(\"Ala ma kota.\n\", \"Kot pije mleko.\", none)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "character_class" )
	ENSURE_EQUALS(
		"Text.character_class failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"return ( [\n"
			"text.character_class( text.CHARACTER_CLASS.WHITESPACE ),\n"
			"text.character_class( text.CHARACTER_CLASS.BIN_DIGIT ),\n"
			"text.character_class( text.CHARACTER_CLASS.OCT_DIGIT ),\n"
			"text.character_class( text.CHARACTER_CLASS.DIGIT ),\n"
			"text.character_class( text.CHARACTER_CLASS.HEX_DIGIT ),\n"
			"text.character_class( text.CHARACTER_CLASS.LETTER ),\n"
			"text.character_class( text.CHARACTER_CLASS.LOWER_CASE_LETTER ),\n"
			"text.character_class( text.CHARACTER_CLASS.UPPER_CASE_LETTER ),\n"
			"text.character_class( text.CHARACTER_CLASS.WORD ),\n"
			"text.character_class( text.CHARACTER_CLASS.VOWEL ),\n"
			"text.character_class( text.CHARACTER_CLASS.GREEK ),\n"
			"text.character_class( text.CHARACTER_CLASS.LOWER_CASE_GREEK ),\n"
			"text.character_class( text.CHARACTER_CLASS.UPPER_CASE_GREEK ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUBSCRIPT ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUBSCRIPT_DIGIT ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUBSCRIPT_LETTER ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUBSCRIPT_LOWER_CASE_LETTER ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUBSCRIPT_UPPER_CASE_LETTER ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUPERSCRIPT ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUPERSCRIPT_DIGIT ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUPERSCRIPT_LETTER ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUPERSCRIPT_LOWER_CASE_LETTER ),\n"
			"text.character_class( text.CHARACTER_CLASS.SUPERSCRIPT_UPPER_CASE_LETTER )\n"
			" ]);\n"
			"}\n"
		),
		"[\"\a\b \t\v\f\r\n\","
		" \"01\","
		" \"01234567\","
		" \"0123456789\","
		" \"0123456789aAbBcCdDeEfF\","
		" \"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\","
		" \"abcdefghijklmnopqrstuvwxyz\","
		" \"ABCDEFGHIJKLMNOPQRSTUVWXYZ\","
		" \"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\","
		" \"aAeEiIoOuUyY\","
		" \"αβγδεζηθικλμνξοπρστυφχψωΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ\","
		" \"αβγδεζηθικλμνξοπρστυφχψω\","
		" \"ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ\","
		" \"₀₁₂₃₄₅₆₇₈₉ₐₑₕᵢⱼₖₗₘₙₒₚᵣₛₜᵤᵥₓ\","
		" \"₀₁₂₃₄₅₆₇₈₉\","
		" \"ₐₑₕᵢⱼₖₗₘₙₒₚᵣₛₜᵤᵥₓ\","
		" \"ₐₑₕᵢⱼₖₗₘₙₒₚᵣₛₜᵤᵥₓ\","
		" \"\","
		" \"⁰¹²³⁴⁵⁶⁷⁸⁹ᵃᵇᶜᵈᵉᶠᵍʰⁱʲᵏˡᵐⁿᵒᵖʳˢᵗᵘᵛʷˣʸᶻᴬᴮᴰᴱᴳᴴᴵᴶᴷᴸᴹᴺᴼᴾᴿᵀᵁⱽᵂ\","
		" \"⁰¹²³⁴⁵⁶⁷⁸⁹\","
		" \"ᵃᵇᶜᵈᵉᶠᵍʰⁱʲᵏˡᵐⁿᵒᵖʳˢᵗᵘᵛʷˣʸᶻᴬᴮᴰᴱᴳᴴᴵᴶᴷᴸᴹᴺᴼᴾᴿᵀᵁⱽᵂ\","
		" \"ᵃᵇᶜᵈᵉᶠᵍʰⁱʲᵏˡᵐⁿᵒᵖʳˢᵗᵘᵛʷˣʸᶻ\","
		" \"ᴬᴮᴰᴱᴳᴴᴵᴶᴷᴸᴹᴺᴼᴾᴿᵀᵁⱽᵂ\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "substitute_environment" )
	ENSURE_EQUALS(
		"substitute_environment() failed",
		execute(
			"import Text as text;\n"
			"import OperatingSystem as os;\n"
			"main(){\n"
			"os.set_env(\"NEW_ENV_VAR\", \"value\");\n"
			"return(text.substitute_environment(\"some${NEW_ENV_VAR}text\", true));\n"
			"}\n"
		),
		"\"somevaluetext\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "capitalize" )
	ENSURE_EQUALS(
		"capitalize() failed",
		execute(
			"import Text as text;\n"
			"main(){\n"
			"return(text.capitalize(\"caPiTaliZeD\"));\n"
			"}\n"
		),
		"\"Capitalized\""
	);
TUT_TEARDOWN()

}

