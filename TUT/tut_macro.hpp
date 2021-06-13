#ifndef TUT_MACRO_H_GUARD
#define TUT_MACRO_H_GUARD 1

#ifdef ENSURE
#	error Tress redefines ENSURE macro.
#endif /* #ifdef ENSURE */
#ifdef ENSURE_NOT
#	error Tress redefines ENSURE_NOT macro.
#endif /* #ifdef ENSURE_NOT */
#ifdef ENSURE_EQUALS
#	error Tress redefines ENSURE_EQUALS macro.
#endif /* #ifdef ENSURE_EQUALS */
#ifdef ENSURE_DISTANCE
#	error Tress redefines ENSURE_DISTANCE macro.
#endif /* #ifdef ENSURE_DISTANCE */
#ifdef ENSURE_ERRNO
#	error Tress redefines ENSURE_ERRNO macro.
#endif /* #ifdef ENSURE_ERRNO */
#ifdef FAIL
#	error Tress redefines FAIL macro.
#endif /* #ifdef FAIL */
#ifdef TIME_CONSTRAINT
#	error Tress redefines TIME_CONSTRAINT macro.
#endif /* #ifdef TIME_CONSTRAINT */

/*
 * Workaround for GCC bug: 65860.
 */
#ifdef __clang__
#define TUT_STRINGIFY( ... ) __VA_ARGS__
#else
#define TUT_STRINGIFY_REAL( ... ) # __VA_ARGS__
#define TUT_STRINGIFY( ... ) TUT_STRINGIFY_REAL( __VA_ARGS__ )
#endif
#define TUT_EXPAND( x ) x
#define TUT_ARG_COUNT_2_3(...) TUT_ARG_COUNT_2_3_( , ##__VA_ARGS__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, N__, 3, 2, N__, N__ )
#define TUT_ARG_COUNT_2_3_( z, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, cnt, ... ) cnt
#define TUT_CONCAT_REAL( a, b ) a ## b
#define TUT_CONCAT( a, b ) TUT_CONCAT_REAL( a, b )
#define TUT_MACRO_ARGC_HELPER_2( MACRO, NUM, ... ) TUT_EXPAND( TUT_CONCAT( MACRO, NUM )( __VA_ARGS__ ) )
#define TUT_MACRO_ARGC_HELPER( MACRO, COUNT_GETTER, ... ) TUT_MACRO_ARGC_HELPER_2( MACRO, TUT_EXPAND( COUNT_GETTER( __VA_ARGS__ ) ), __VA_ARGS__ )
#define TUT_MACRO_ARGC( COUNT, MACRO, ... ) TUT_MACRO_ARGC_HELPER( MACRO, TUT_CONCAT( TUT_ARG_COUNT_, COUNT ), __VA_ARGS__ )

#define ENSURE( ... ) do { this->set_current_line( __LINE__ ); tut::ensure_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_NOT( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_not_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_EQUALS_NARG_2( actual, expected ) do { this->set_current_line( __LINE__ );  tut::ensure_equals_impl( __FILE__, __LINE__, # actual " == " # expected, ( actual ), ( expected ) ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_EQUALS_NARG_3( message, actual, expected ) do { this->set_current_line( __LINE__ );  tut::ensure_equals_impl( __FILE__, __LINE__, message, #actual, #expected, ( actual ), ( expected ) ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_EQUALS_NARG_N__( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_equals_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_EQUALS( ... ) TUT_MACRO_ARGC( 2_3, ENSURE_EQUALS_NARG_, __VA_ARGS__ )
#define ENSURE_IN( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_in_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_LESS( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_less_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_GREATER( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_greater_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_LESS_OR_EQUAL( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_less_or_equal_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_GREATER_OR_EQUAL( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_greater_or_equal_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_DISTANCE( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_distance_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_SAME_CONTENT( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_same_content_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_ERRNO( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_errno_impl( __FILE__, __LINE__, TUT_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ) }; while ( false )
#define ENSURE_THROW( msg, code, type ) do { try { this->set_current_line( __LINE__ ); code; throw failure( __FILE__, __LINE__, msg ); } catch ( type const& ) { this->set_current_line( __LINE__ + 1 ); } } while ( false )
#define ENSURE_THROW_AUTO( code, type ) do { try { this->set_current_line( __LINE__ ); code; throw failure( __FILE__, __LINE__, "Expected exception `" #type "' not thrown from: `" #code "'." ); } catch ( type const& ) { this->set_current_line( __LINE__ + 1 ); } } while ( false )
#define FAIL( msg ) tut::fail_impl( __FILE__, __LINE__, ( msg ) )
#define SKIP( msg ) do { if ( ! tress::setup._forceRunAll ) { tut::skip_impl( __FILE__, __LINE__, ( msg ) ); } } while ( false )
#define TIME_CONSTRAINT( ms ) tut::time_constraint TUT_CONCAT( time_constraint_at_, __LINE__ )( ( ms ), __FILE__, __LINE__ )

#endif /* TUT_MACRO_H_GUARD */

