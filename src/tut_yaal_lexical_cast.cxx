/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_lexical_cast.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/base.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_lexical_cast );
TUT_TEST_GROUP( tut_yaal_lexical_cast, "yaal::lexical_cast" );

TUT_UNIT_TEST( "0" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "9xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-9xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "9xOlab" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-9xOlab" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "axOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-axOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), 10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), -10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0x" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0x" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), 267 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 16 based cast", lexical_cast<int>( get_test_name().c_str() ), -267 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-x10b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-xOla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-xAla" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_THROW( "lexical_cast to an int from a garbage succeeded", lexical_cast<int>( get_test_name().c_str() ), HLexicalCastException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "01Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-01Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "07Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0o7Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-07Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0o7Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0o8Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "08Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-08Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "078Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-078Ala" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "01" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-01" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0b110b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), 6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0b110b" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), -6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0b110c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), 6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0b11001001010011101010101" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), -6596437 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "0110c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), 72 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-0110c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), true );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 8 based cast", lexical_cast<int>( get_test_name().c_str() ), -72 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "1010c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), 1010 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-1010c" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 10 based cast", lexical_cast<int>( get_test_name().c_str() ), -1010 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "1b010" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "-1b010" )
	ENSURE_EQUALS( "bad base 16 recognition", is_hexadecimal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 8 recognition", is_octal( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad base 2 recognition", is_binary( get_test_name().c_str() ), false );
	ENSURE_EQUALS( "bad 2 based cast", lexical_cast<int>( get_test_name().c_str() ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "string to bool" )
	ENSURE_EQUALS( "yes to bool failed", lexical_cast<bool>( static_cast<char const*>( "yes" ) ), true );
	ENSURE_EQUALS( "no to bool failed", lexical_cast<bool>( static_cast<char const*>( "no" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "true" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "false" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "on" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "off" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "enable" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "disable" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "enabled" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "disabled" ) ), false );
	ENSURE_EQUALS( "true to bool failed", lexical_cast<bool>( static_cast<char const*>( "1" ) ), true );
	ENSURE_EQUALS( "false to bool failed", lexical_cast<bool>( static_cast<char const*>( "0" ) ), false );
	ENSURE_THROW( "casting garbage to bool did not throw", lexical_cast<bool>( static_cast<char const*>( "invalid" ) ), HLexicalCastException );
	ENSURE_THROW( "casting garbage to bool did not throw", lexical_cast<bool>( static_cast<char const*>( "2" ) ), HLexicalCastException );
TUT_TEARDOWN()

}

