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

#define ENSURE( ... ) tut::ensure_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define ENSURE_NOT( ... ) tut::ensure_not_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define ENSURE_EQUALS( ... ) tut::ensure_equals_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define ENSURE_DISTANCE( ... ) tut::ensure_distance_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define ENSURE_ERRNO( ... ) tut::ensure_errno_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define FAIL( msg ) tut::fail_real( __FILE__, __LINE__, ( msg ) )
#define TIME_CONSTRAINT( ms ) tut::time_constraint M_CONCAT( time_constraint_at_, __LINE__ )( ( ms ), __FILE__, __LINE__ )

#endif /* TUT_MACRO_H_GUARD */
