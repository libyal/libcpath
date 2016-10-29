/*
 * Cross-platform C path functions library path testing program
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "cpath_test_libcerror.h"
#include "cpath_test_libcpath.h"
#include "cpath_test_libcstring.h"
#include "cpath_test_macros.h"
#include "cpath_test_unused.h"

/* Tests the libcpath_path_get_current_working_directory function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_get_current_working_directory(
     void )
{
	libcerror_error_t *error              = NULL;
	char *current_working_directory       = NULL;
	size_t current_working_directory_size = 0;
	int result                            = 0;

	result = libcpath_path_get_current_working_directory(
	          &current_working_directory,
	          &current_working_directory_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "current_working_directory",
         current_working_directory );

	memory_free(
	 current_working_directory );

	current_working_directory = NULL;

        CPATH_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcpath_path_get_current_working_directory(
	          NULL,
	          &current_working_directory_size,
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

	result = libcpath_path_get_current_working_directory(
	          &current_working_directory,
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
	if( current_working_directory != NULL )
	{
		memory_free(
		 current_working_directory );
	}
	return( 0 );
}

/* Tests the libcpath_path_get_full_path function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_get_full_path(
     void )
{
	char *absolute_paths[] = {
		"/home/user/test.txt",
		"/home/user//test.txt",
		"/../home/user/test.txt",
		"/../home/username/../user/test.txt",
	};
	char *relative_paths[] = {
		"user/test.txt",
		"username/../user/test.txt",
	};

	libcerror_error_t *error                = NULL;
	char *current_working_directory         = NULL;
	char *expected_path                     = NULL;
	char *full_path                         = NULL;
	char *path                              = NULL;
	size_t current_working_directory_length = 0;
	size_t current_working_directory_size   = 0;
	size_t expected_path_length             = 0;
	size_t full_path_length                 = 0;
	size_t full_path_size                   = 0;
	size_t path_length                      = 0;
	int path_index                          = 0;
	int result                              = 0;

	/* Initialize test
	 */
	result = libcpath_path_get_current_working_directory(
	          &current_working_directory,
	          &current_working_directory_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        CPATH_TEST_ASSERT_IS_NOT_NULL(
         "current_working_directory",
         current_working_directory );

        CPATH_TEST_ASSERT_IS_NULL(
         "error",
         error );

	current_working_directory_length = libcstring_narrow_string_length(
	                                    current_working_directory );

	/* Test get full path
	 */
	expected_path = "/home/user/test.txt";

	expected_path_length = libcstring_narrow_string_length(
	                        expected_path );

	for( path_index = 0;
	     path_index < 4;
	     path_index++ )
	{
		path = absolute_paths[ path_index ];

		path_length = libcstring_narrow_string_length(
		               path );

		result = libcpath_path_get_full_path(
		          path,
		          path_length,
		          &full_path,
		          &full_path_size,
		          &error );

		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		full_path_length = libcstring_narrow_string_length(
		                    full_path );

		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "full_path_size",
		 full_path_size,
		 full_path_length + 1 );

		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "full_path_size",
		 full_path_size,
		 expected_path_length + 1 );

		result = libcstring_narrow_string_compare(
		          full_path,
		          expected_path,
		          expected_path_length );

		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		memory_free(
		 full_path );

		full_path = NULL;
	}
	expected_path = "/user/test.txt";

	expected_path_length = libcstring_narrow_string_length(
	                        expected_path );

	for( path_index = 0;
	     path_index < 2;
	     path_index++ )
	{
		path = relative_paths[ path_index ];

		path_length = libcstring_narrow_string_length(
		               path );

		result = libcpath_path_get_full_path(
		          path,
		          path_length,
		          &full_path,
		          &full_path_size,
		          &error );

		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		full_path_length = libcstring_narrow_string_length(
		                    full_path );

/* TODO fix full_path_size
		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "full_path_size",
		 full_path_size,
		 full_path_length + 1 );

		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "full_path_size",
		 full_path_size,
		 current_working_directory_length + expected_path_length + 1 );
*/

		result = libcstring_narrow_string_compare(
		          full_path,
		          current_working_directory,
		          current_working_directory_length );

		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		result = libcstring_narrow_string_compare(
		          &( full_path[ current_working_directory_length ] ),
		          expected_path,
		          expected_path_length );

		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		memory_free(
		 full_path );

		full_path = NULL;
	}

	/* Clean up
	 */
	memory_free(
	 current_working_directory );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( full_path != NULL )
	{
		memory_free(
		 full_path );
	}
	if( current_working_directory != NULL )
	{
		memory_free(
		 current_working_directory );
	}
	return( 0 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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

	/* TODO: add tests for libcpath_path_change_directory */

	CPATH_TEST_RUN(
	 "libcpath_path_get_current_working_directory",
	 cpath_test_path_get_current_working_directory );

	CPATH_TEST_RUN(
	 "libcpath_path_get_full_path",
	 cpath_test_path_get_full_path );

	/* TODO: add tests for libcpath_path_join */
	/* TODO: add tests for libcpath_path_make_directory */
	/* TODO: add tests for libcpath_path_sanitize */
	/* TODO: add tests for libcpath_path_sanitize_filename */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	/* TODO: add tests for libcpath_path_change_directory_wide */
	/* TODO: add tests for libcpath_path_get_current_working_directory_wide */
	/* TODO: add tests for libcpath_path_get_full_path_wide */
	/* TODO: add tests for libcpath_path_join_wide */
	/* TODO: add tests for libcpath_path_make_directory_wide */
	/* TODO: add tests for libcpath_path_sanitize_wide */
	/* TODO: add tests for libcpath_path_sanitize_filename_wide */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

