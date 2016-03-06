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
#define UDL_STRINGIFY( ... ) __VA_ARGS__
#else
#define UDL_STRINGIFY_REAL( ... ) # __VA_ARGS__
#define UDL_STRINGIFY( ... ) UDL_STRINGIFY_REAL( __VA_ARGS__ )
#endif

#define ENSURE( ... ) do { this->set_current_line( __LINE__ ); tut::ensure_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_NOT( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_not_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_EQUALS( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_equals_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_LESS( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_less_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_GREATER( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_greater_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_LESS_OR_EQUAL( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_less_or_equal_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_GREATER_OR_EQUAL( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_greater_or_equal_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_DISTANCE( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_distance_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ); } while ( false )
#define ENSURE_ERRNO( ... ) do { this->set_current_line( __LINE__ );  tut::ensure_errno_real( __FILE__, __LINE__, UDL_STRINGIFY( # __VA_ARGS__ ), __VA_ARGS__ ); this->set_current_line( __LINE__ + 1 ) }; while ( false )
#define ENSURE_THROW( msg, code, type ) do { try { this->set_current_line( __LINE__ ); code; throw failure( __FILE__, __LINE__, msg ); } catch ( type const& ) { this->set_current_line( __LINE__ + 1 ); } } while ( false )
#define ENSURE_THROW_AUTO( code, type ) do { try { this->set_current_line( __LINE__ ); code; throw failure( __FILE__, __LINE__, "Expected exception `" ##type "' not thrown from: `" ##code "'." ); } catch ( type const& ) { this->set_current_line( __LINE__ + 1 ); } } while ( false )
#define FAIL( msg ) tut::fail_real( __FILE__, __LINE__, ( msg ) )
#define SKIP( msg ) do { if ( ! tress::setup._forceRunAll ) { tut::skip_real( __FILE__, __LINE__, ( msg ) ); } } while ( false )
#define TIME_CONSTRAINT( ms ) tut::time_constraint M_CONCAT( time_constraint_at_, __LINE__ )( ( ms ), __FILE__, __LINE__ )

#endif /* TUT_MACRO_H_GUARD */

