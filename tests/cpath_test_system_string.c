/*
 * Library system string functions test program
 *
 * Copyright (C) 2008-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <wide_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cpath_test_libcerror.h"
#include "cpath_test_libcpath.h"
#include "cpath_test_macros.h"
#include "cpath_test_unused.h"

#include "../libcpath/libcpath_system_string.h"

#if defined( __GNUC__ )

/* Tests the libcpath_system_string_size_to_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_system_string_size_to_narrow_string(
     void )
{
	libcerror_error_t *error  = NULL;
	size_t narrow_string_size = 0;
	int result                = 0;

	result = libcpath_system_string_size_to_narrow_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          &narrow_string_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "narrow_string_size",
	 narrow_string_size,
	 (size_t) 12 );

        CPATH_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcpath_system_string_size_to_narrow_string(
	          NULL,
	          12,
	          &narrow_string_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_size_to_narrow_string(
	          _SYSTEM_STRING( "test string" ),
	          (size_t) -1,
	          &narrow_string_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_size_to_narrow_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          NULL,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libcpath_system_string_copy_to_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_system_string_copy_to_narrow_string(
     void )
{
	char narrow_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libcpath_system_string_copy_to_narrow_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          narrow_string,
	          32,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        CPATH_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcpath_system_string_copy_to_narrow_string(
	          NULL,
	          12,
	          narrow_string,
	          32,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_copy_to_narrow_string(
	          _SYSTEM_STRING( "test string" ),
	          (size_t) -1,
	          narrow_string,
	          32,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_copy_to_narrow_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          NULL,
	          32,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_copy_to_narrow_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          narrow_string,
	          (size_t) -1,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcpath_system_string_size_to_wide_string function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_system_string_size_to_wide_string(
     void )
{
	libcerror_error_t *error = NULL;
	size_t wide_string_size  = 0;
	int result               = 0;

	result = libcpath_system_string_size_to_wide_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          &wide_string_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "wide_string_size",
	 wide_string_size,
	 (size_t) 12 );

        CPATH_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcpath_system_string_size_to_wide_string(
	          NULL,
	          12,
	          &wide_string_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_size_to_wide_string(
	          _SYSTEM_STRING( "test string" ),
	          (size_t) -1,
	          &wide_string_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_size_to_wide_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          NULL,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libcpath_system_string_copy_to_wide_string function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_system_string_copy_to_wide_string(
     void )
{
	wchar_t wide_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libcpath_system_string_copy_to_wide_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          wide_string,
	          32,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        CPATH_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcpath_system_string_copy_to_wide_string(
	          NULL,
	          12,
	          wide_string,
	          32,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_copy_to_wide_string(
	          _SYSTEM_STRING( "test string" ),
	          (size_t) -1,
	          wide_string,
	          32,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_copy_to_wide_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          NULL,
	          32,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libcpath_system_string_copy_to_wide_string(
	          _SYSTEM_STRING( "test string" ),
	          12,
	          wide_string,
	          (size_t) -1,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc CPATH_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] CPATH_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc CPATH_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] CPATH_TEST_ATTRIBUTE_UNUSED )
#endif
{
	CPATH_TEST_UNREFERENCED_PARAMETER( argc )
	CPATH_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ )

	CPATH_TEST_RUN(
	 "libcpath_system_string_size_to_narrow_string",
	 cpath_test_system_string_size_to_narrow_string );

	CPATH_TEST_RUN(
	 "libcpath_system_string_copy_to_narrow_string",
	 cpath_test_system_string_copy_to_narrow_string );

	/* TODO: add tests for libcpath_system_string_size_from_narrow_string */
	/* TODO: add tests for libcpath_system_string_copy_from_narrow_string */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CPATH_TEST_RUN(
	 "libcpath_system_string_size_to_wide_string",
	 cpath_test_system_string_size_to_wide_string );

	CPATH_TEST_RUN(
	 "libcpath_system_string_copy_to_wide_string",
	 cpath_test_system_string_copy_to_wide_string );

	/* TODO: add tests for libcpath_system_string_size_from_wide_string */
	/* TODO: add tests for libcpath_system_string_copy_from_wide_string */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

