/*
 * Cross-platform C path functions library path testing program
 *
 * Copyright (C) 2008-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <errno.h>

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )
#define __USE_GNU
#include <dlfcn.h>
#undef __USE_GNU
#endif

#include "cpath_test_libcerror.h"
#include "cpath_test_libcpath.h"
#include "cpath_test_macros.h"
#include "cpath_test_memory.h"
#include "cpath_test_unused.h"

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

static int (*cpath_test_real_chdir)(const char *)      = NULL;
static char *(*cpath_test_real_getcwd)(char *, size_t) = NULL;

int cpath_test_chdir_attempts_before_fail              = -1;
int cpath_test_getcwd_attempts_before_fail             = -1;

#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

/* Custom chdir for testing error cases
 * Returns 0 if successful or an error value otherwise
 */
int chdir(
     const char *path )
{
	int result = 0;

	if( cpath_test_real_chdir == NULL )
	{
		cpath_test_real_chdir = dlsym(
		                         RTLD_NEXT,
		                         "chdir" );
	}
	if( cpath_test_chdir_attempts_before_fail == 0 )
	{
		cpath_test_chdir_attempts_before_fail = -1;

		return( -1 );
	}
	else if( cpath_test_chdir_attempts_before_fail > 0 )
	{
		cpath_test_chdir_attempts_before_fail--;
	}
	result = cpath_test_real_chdir(
	          path );

	return( result );
}

/* Custom getcwd for testing error cases
 * Returns 0 if successful or an error value otherwise
 */
char *getcwd(
       char *buf,
       size_t size )
{
	char *result = NULL;

	if( cpath_test_real_getcwd == NULL )
	{
		cpath_test_real_getcwd = dlsym(
		                          RTLD_NEXT,
		                          "getcwd" );
	}
	if( cpath_test_getcwd_attempts_before_fail == 0 )
	{
		cpath_test_getcwd_attempts_before_fail = -1;

		return( NULL );
	}
	else if( cpath_test_getcwd_attempts_before_fail > 0 )
	{
		cpath_test_getcwd_attempts_before_fail--;
	}
	result = cpath_test_real_getcwd(
	          buf,
	          size );

	return( result );
}

#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

/* Tests the libcpath_path_change_directory function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_change_directory(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libcpath_path_change_directory(
	          ".",
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
	result = libcpath_path_change_directory(
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

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libcpath_path_change_directory with chdir failing
	 */
	cpath_test_chdir_attempts_before_fail = 0;

	result = libcpath_path_change_directory(
	          ".",
	          &error );

	if( cpath_test_chdir_attempts_before_fail != -1 )
	{
		cpath_test_chdir_attempts_before_fail = -1;
	}
	else
	{
		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

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

	current_working_directory = (char *) 0x12345678UL;

	result = libcpath_path_get_current_working_directory(
	          &current_working_directory,
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

	current_working_directory = NULL;

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

#if defined( HAVE_CPATH_TEST_MEMORY )

	/* Test libcpath_path_get_current_working_directory with malloc failing
	 */
	cpath_test_malloc_attempts_before_fail = 0;

	result = libcpath_path_get_current_working_directory(
	          &current_working_directory,
	          &current_working_directory_size,
	          &error );

	if( cpath_test_malloc_attempts_before_fail != -1 )
	{
		cpath_test_malloc_attempts_before_fail = -1;

		if( current_working_directory != NULL )
		{
			memory_free(
			 current_working_directory );

			current_working_directory = NULL;
		}
	}
	else
	{
		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "current_working_directory",
		 current_working_directory );

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libcpath_path_get_current_working_directory with memset failing
	 */
	cpath_test_memset_attempts_before_fail = 0;

	result = libcpath_path_get_current_working_directory(
	          &current_working_directory,
	          &current_working_directory_size,
	          &error );

	if( cpath_test_memset_attempts_before_fail != -1 )
	{
		cpath_test_memset_attempts_before_fail = -1;

		if( current_working_directory != NULL )
		{
			memory_free(
			 current_working_directory );

			current_working_directory = NULL;
		}
	}
	else
	{
		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "current_working_directory",
		 current_working_directory );

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CPATH_TEST_MEMORY ) */

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libcpath_path_change_directory with getcwd failing
	 */
	cpath_test_getcwd_attempts_before_fail = 0;

	result = libcpath_path_get_current_working_directory(
	          &current_working_directory,
	          &current_working_directory_size,
	          &error );

	if( cpath_test_getcwd_attempts_before_fail != -1 )
	{
		cpath_test_getcwd_attempts_before_fail = -1;
	}
	else
	{
		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "current_working_directory",
		 current_working_directory );

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

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
#if defined( WINAPI )
	char *absolute_paths[] = {
		"\\home\\user\\test.txt",
		"c:\\home\\user\\test.txt",
		"c:\\home\\user\\\\test.txt",
		"c:\\home\\username\\..\\user\\test.txt",
		"c:\\..\\home\\user\\test.txt",
		"c:\\..\\home\\username\\..\\user\\test.txt",
	};
	char *relative_paths[] = {
		"user\\test.txt",
		"username\\..\\user\\test.txt",
	};
	char *special_paths[] = {
		"\\\\.\\PhysicalDrive0",
		"\\\\?\\Volume{4c1b02c4-d990-11dc-99ae-806e6f6e6963}"
	};
	char *unc_paths[] = {
		"\\\\172.0.0.1\\C$\\test.txt",
		"\\\\?\\UNC\\172.0.0.1\\C$\\test.txt",
	};
#else
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
#endif /* defined( WINAPI ) */

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
	int string_index                        = 0;
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

	current_working_directory_length = narrow_string_length(
	                                    current_working_directory );

	/* Test get full path
	 */
#if defined( WINAPI )
	expected_path = "\\\\?\\C:\\home\\user\\test.txt";
#else
	expected_path = "/home/user/test.txt";
#endif
	expected_path_length = narrow_string_length(
	                        expected_path );

	for( path_index = 0;
	     path_index < 4;
	     path_index++ )
	{
		path = absolute_paths[ path_index ];

		path_length = narrow_string_length(
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

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "full_path",
		 full_path );

		CPATH_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		full_path_length = narrow_string_length(
		                    full_path );

		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "full_path_size",
		 full_path_size,
		 full_path_length + 1 );

		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "full_path_size",
		 full_path_size,
		 expected_path_length + 1 );

#if defined( WINAPI )
		result = narrow_string_compare_no_case(
		          full_path,
		          expected_path,
		          expected_path_length );
#else
		result = narrow_string_compare(
		          full_path,
		          expected_path,
		          expected_path_length );
#endif

		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		memory_free(
		 full_path );

		full_path = NULL;
	}
#if defined( WINAPI )
	expected_path = "\\user\\test.txt";
#else
	expected_path = "/user/test.txt";
#endif
	expected_path_length = narrow_string_length(
	                        expected_path );

	for( path_index = 0;
	     path_index < 2;
	     path_index++ )
	{
		path = relative_paths[ path_index ];

		path_length = narrow_string_length(
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

		full_path_length = narrow_string_length(
		                    full_path );

		/* A full path on Windows is prefixed with \\?\ while
		 * the current working directory is not.
		 */
		if( ( full_path_length >= 4 ) 
		 && ( full_path[ 0 ] == '\\' )
		 && ( full_path[ 1 ] == '\\' )
		 && ( full_path[ 2 ] == '?' )
		 && ( full_path[ 3 ] == '\\' ) )
		{
			string_index = 4;
		}
		else
		{
			string_index = 0;
		}
		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "full_path_length",
		 full_path_length,
		 string_index + current_working_directory_length + expected_path_length );

/* TODO fix
		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "full_path_size",
		 full_path_size,
		 full_path_length + 1 );
*/

#if defined( WINAPI )
		result = narrow_string_compare_no_case(
		          &( full_path[ string_index ] ),
		          current_working_directory,
		          current_working_directory_length );
#else
		result = narrow_string_compare(
		          &( full_path[ string_index ] ),
		          current_working_directory,
		          current_working_directory_length );
#endif

		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

#if defined( WINAPI )
		result = narrow_string_compare_no_case(
		          &( full_path[ string_index + current_working_directory_length ] ),
		          expected_path,
		          expected_path_length );
#else
		result = narrow_string_compare(
		          &( full_path[ string_index + current_working_directory_length ] ),
		          expected_path,
		          expected_path_length );
#endif

		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		memory_free(
		 full_path );

		full_path = NULL;
	}
	/* Test error cases
	 */
	result = libcpath_path_get_full_path(
	          NULL,
	          8,
	          &full_path,
	          &full_path_size,
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

	result = libcpath_path_get_full_path(
	          "test.txt",
	          0,
	          &full_path,
	          &full_path_size,
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

	result = libcpath_path_get_full_path(
	          "test.txt",
	          (size_t) -1,
	          &full_path,
	          &full_path_size,
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

	result = libcpath_path_get_full_path(
	          "test.txt",
	          8,
	          NULL,
	          &full_path_size,
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

	full_path = (char *) 0x12345678UL;

	result = libcpath_path_get_full_path(
	          "test.txt",
	          8,
	          &full_path,
	          &full_path_size,
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

	full_path = NULL;

	result = libcpath_path_get_full_path(
	          "test.txt",
	          8,
	          &full_path,
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

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libcpath_path_change_directory with getcwd failing
	 */
	cpath_test_getcwd_attempts_before_fail = 0;

	result = libcpath_path_get_full_path(
	          "test.txt",
	          8,
	          &full_path,
	          &full_path_size,
	          &error );

	if( cpath_test_getcwd_attempts_before_fail != -1 )
	{
		cpath_test_getcwd_attempts_before_fail = -1;
	}
	else
	{
		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "full_path",
		 full_path );

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

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

/* Tests the libcpath_path_get_sanitized_filename function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_get_sanitized_filename(
     void )
{
	libcerror_error_t *error       = NULL;
	char *expected_filename        = NULL;
	char *sanitized_filename       = NULL;
	char *test_filename            = NULL;
	size_t expected_filename_size  = 0;
	size_t sanitized_filename_size = 0;
	size_t test_filename_length    = 0;
	int result                     = 0;

	/* Test libcpath_path_get_sanitized_filename without replacement characters
	 */
	test_filename          = "test.txt";
	test_filename_length   = 8;
	expected_filename      = "test.txt";
	expected_filename_size = 9;

	result = libcpath_path_get_sanitized_filename(
	          test_filename,
	          test_filename_length,
	          &sanitized_filename,
	          &sanitized_filename_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_IS_NOT_NULL(
	 "sanitized_filename",
	 sanitized_filename );

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "sanitized_filename_size",
	 sanitized_filename_size,
	 expected_filename_size );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          sanitized_filename,
	          expected_filename,
	          expected_filename_size );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 sanitized_filename );

	sanitized_filename      = NULL;
	sanitized_filename_size = 0;

	/* Test libcpath_path_get_sanitized_filename with replacement characters
	 */
#if defined( WINAPI )
	test_filename          = "t\x00sT!.t^t";
	test_filename_length   = 8;
	expected_filename      = "t^x00sT^x21.t^^t";
	expected_filename_size = 17;
#else
	test_filename          = "t\x00sT!.t\\t";
	test_filename_length   = 9;
	expected_filename      = "t\\x00sT\\x21.t\\\\t";
	expected_filename_size = 17;
#endif

	result = libcpath_path_get_sanitized_filename(
	          "t\x00sT!.t\\t",
	          9,
	          &sanitized_filename,
	          &sanitized_filename_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_IS_NOT_NULL(
	 "sanitized_filename",
	 sanitized_filename );

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "sanitized_filename_size",
	 sanitized_filename_size,
	 expected_filename_size );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          sanitized_filename,
	          expected_filename,
	          expected_filename_size );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 sanitized_filename );

	sanitized_filename      = NULL;
	sanitized_filename_size = 0;

	/* Test error cases
	 */
	result = libcpath_path_get_sanitized_filename(
	          NULL,
	          8,
	          &sanitized_filename,
	          &sanitized_filename_size,
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

	result = libcpath_path_get_sanitized_filename(
	          "test.txt",
	          (size_t) -1,
	          &sanitized_filename,
	          &sanitized_filename_size,
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

	result = libcpath_path_get_sanitized_filename(
	          "test.txt",
	          8,
	          NULL,
	          &sanitized_filename_size,
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

	sanitized_filename = (char *) 0x12345678UL;

	result = libcpath_path_get_sanitized_filename(
	          "test.txt",
	          8,
	          &sanitized_filename,
	          &sanitized_filename_size,
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

	sanitized_filename = NULL;

	result = libcpath_path_get_sanitized_filename(
	          "test.txt",
	          8,
	          &sanitized_filename,
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

#if defined( HAVE_CPATH_TEST_MEMORY )

	/* Test libcpath_path_get_sanitized_filename with malloc failing
	 */
	cpath_test_malloc_attempts_before_fail = 0;

	result = libcpath_path_get_sanitized_filename(
	          "test.txt",
	          8,
	          &sanitized_filename,
	          &sanitized_filename_size,
	          &error );

	if( cpath_test_malloc_attempts_before_fail != -1 )
	{
		cpath_test_malloc_attempts_before_fail = -1;

		if( sanitized_filename != NULL )
		{
			memory_free(
			 sanitized_filename );

			sanitized_filename = NULL;
		}
	}
	else
	{
		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "sanitized_filename",
		 sanitized_filename );

		CPATH_TEST_ASSERT_EQUAL_SIZE(
		 "sanitized_filename_size",
		 sanitized_filename_size,
		 (size_t) 0 );

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CPATH_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( sanitized_filename != NULL )
	{
		memory_free(
		 sanitized_filename );
	}
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libcpath_path_get_sanitized_path function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_get_sanitized_path(
     void )
{
	libcerror_error_t *error   = NULL;
	char *sanitized_path       = NULL;
	size_t sanitized_path_size = 0;
	int result                 = 0;

	result = libcpath_path_get_sanitized_path(
	          "test.txt",
	          8,
	          &sanitized_path,
	          &sanitized_path_size,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

/* TODO implement function
	CPATH_TEST_ASSERT_IS_NOT_NULL(
	 "sanitized_path",
	 sanitized_path );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	memory_free(
	 sanitized_path );

	sanitized_path = NULL;
*/

	/* Test error cases
	 */
	result = libcpath_path_get_sanitized_path(
	          NULL,
	          8,
	          &sanitized_path,
	          &sanitized_path_size,
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

	result = libcpath_path_get_sanitized_path(
	          "test.txt",
	          (size_t) -1,
	          &sanitized_path,
	          &sanitized_path_size,
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

	result = libcpath_path_get_sanitized_path(
	          "test.txt",
	          8,
	          NULL,
	          &sanitized_path_size,
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

	sanitized_path = (char *) 0x12345678UL;

	result = libcpath_path_get_sanitized_path(
	          "test.txt",
	          8,
	          &sanitized_path,
	          &sanitized_path_size,
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

	sanitized_path = NULL;

	result = libcpath_path_get_sanitized_path(
	          "test.txt",
	          8,
	          &sanitized_path,
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
	if( sanitized_path != NULL )
	{
		memory_free(
		 sanitized_path );
	}
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libcpath_path_join function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_join(
     void )
{
	libcerror_error_t *error  = NULL;
	const char *expected_path = NULL;
	const char *test_path1    = NULL;
	const char *test_path2    = NULL;
	const char *test_path3    = NULL;
	const char *test_path4    = NULL;
	char *path                = NULL;
	size_t path_size          = 0;
	int result                = 0;

#if defined( WINAPI )
	test_path1    = "\\first\\second";
	test_path2    = "third\\fourth";
	test_path3    = "\\first\\second\\";
	test_path4    = "\\third\\fourth";
	expected_path = "\\first\\second\\third\\fourth";
#else
	test_path1    = "/first/second";
	test_path2    = "third/fourth";
	test_path3    = "/first/second/";
	test_path4    = "/third/fourth";
	expected_path = "/first/second/third/fourth";
#endif

	result = libcpath_path_join(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          test_path2,
	          12,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          path,
	          expected_path,
	          26 );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 27 );

	result = libcpath_path_join(
	          &path,
	          &path_size,
	          test_path3,
	          14,
	          test_path2,
	          12,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          path,
	          expected_path,
	          26 );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 27 );

	result = libcpath_path_join(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          test_path4,
	          13,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          path,
	          expected_path,
	          26 );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 27 );

	/* Test error cases
	 */
	result = libcpath_path_join(
	          NULL,
	          &path_size,
	          test_path1,
	          13,
	          test_path2,
	          12,
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

	path = (char *) 0x12345678UL;

	result = libcpath_path_join(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          test_path2,
	          12,
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

	path = NULL;

	result = libcpath_path_join(
	          &path,
	          NULL,
	          test_path1,
	          13,
	          test_path2,
	          12,
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

	result = libcpath_path_join(
	          &path,
	          &path_size,
	          NULL,
	          13,
	          test_path2,
	          12,
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

	result = libcpath_path_join(
	          &path,
	          &path_size,
	          test_path1,
	          (size_t) SSIZE_MAX + 1,
	          test_path2,
	          12,
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

	result = libcpath_path_join(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          NULL,
	          12,
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

	result = libcpath_path_join(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          test_path2,
	          (size_t) SSIZE_MAX + 1,
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
	if( path != NULL )
	{
		memory_free(
		 path );
	}
	return( 0 );
}

/* Tests the libcpath_path_make_directory function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_make_directory(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcpath_path_make_directory(
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

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcpath_path_change_directory_wide function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_change_directory_wide(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libcpath_path_change_directory_wide(
	          L".",
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
	result = libcpath_path_change_directory_wide(
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

/* Tests the libcpath_path_get_current_working_directory_wide function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_get_current_working_directory_wide(
     void )
{
	libcerror_error_t *error              = NULL;
	wchar_t *current_working_directory    = NULL;
	size_t current_working_directory_size = 0;
	int result                            = 0;

	result = libcpath_path_get_current_working_directory_wide(
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
	result = libcpath_path_get_current_working_directory_wide(
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

	current_working_directory = (wchar_t *) 0x12345678UL;

	result = libcpath_path_get_current_working_directory_wide(
	          &current_working_directory,
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

	current_working_directory = NULL;

	result = libcpath_path_get_current_working_directory_wide(
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

#if defined( HAVE_CPATH_TEST_MEMORY )

	/* Test libcpath_path_get_current_working_directory_wide with malloc failing
	 */
	cpath_test_malloc_attempts_before_fail = 0;

	result = libcpath_path_get_current_working_directory_wide(
	          &current_working_directory,
	          &current_working_directory_size,
	          &error );

	if( cpath_test_malloc_attempts_before_fail != -1 )
	{
		cpath_test_malloc_attempts_before_fail = -1;

		if( current_working_directory != NULL )
		{
			memory_free(
			 current_working_directory );

			current_working_directory = NULL;
		}
	}
	else
	{
		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "current_working_directory",
		 current_working_directory );

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libcpath_path_get_current_working_directory_wide with memset failing
	 */
	cpath_test_memset_attempts_before_fail = 0;

	result = libcpath_path_get_current_working_directory_wide(
	          &current_working_directory,
	          &current_working_directory_size,
	          &error );

	if( cpath_test_memset_attempts_before_fail != -1 )
	{
		cpath_test_memset_attempts_before_fail = -1;

		if( current_working_directory != NULL )
		{
			memory_free(
			 current_working_directory );

			current_working_directory = NULL;
		}
	}
	else
	{
		CPATH_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CPATH_TEST_ASSERT_IS_NULL(
		 "current_working_directory",
		 current_working_directory );

		CPATH_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CPATH_TEST_MEMORY ) */

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

/* Tests the libcpath_path_get_sanitized_filename_wide function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_get_sanitized_filename_wide(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcpath_path_get_sanitized_filename_wide(
	          NULL,
	          0,
	          NULL,
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

/* Tests the libcpath_path_get_sanitized_path_wide function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_get_sanitized_path_wide(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcpath_path_get_sanitized_path_wide(
	          NULL,
	          0,
	          NULL,
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

/* Tests the libcpath_path_join_wide function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_join_wide(
     void )
{
	libcerror_error_t *error     = NULL;
	const wchar_t *expected_path = NULL;
	wchar_t *path                = NULL;
	const wchar_t *test_path1    = NULL;
	const wchar_t *test_path2    = NULL;
	const wchar_t *test_path3    = NULL;
	const wchar_t *test_path4    = NULL;
	size_t path_size             = 0;
	int result                   = 0;

#if defined( WINAPI )
	test_path1    = L"\\first\\second";
	test_path2    = L"third\\fourth";
	test_path3    = L"\\first\\second\\";
	test_path4    = L"\\third\\fourth";
	expected_path = L"\\first\\second\\third\\fourth";
#else
	test_path1    = L"/first/second";
	test_path2    = L"third/fourth";
	test_path3    = L"/first/second/";
	test_path4    = L"/third/fourth";
	expected_path = L"/first/second/third/fourth";
#endif

	result = libcpath_path_join_wide(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          test_path2,
	          12,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          path,
	          expected_path,
	          26 );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 27 );

	result = libcpath_path_join_wide(
	          &path,
	          &path_size,
	          test_path3,
	          14,
	          test_path2,
	          12,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          path,
	          expected_path,
	          26 );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 27 );

	result = libcpath_path_join_wide(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          test_path4,
	          13,
	          &error );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CPATH_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          path,
	          expected_path,
	          26 );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	CPATH_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 27 );

	/* Test error cases
	 */
	result = libcpath_path_join_wide(
	          NULL,
	          &path_size,
	          test_path1,
	          13,
	          test_path2,
	          12,
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

	path = (wchar_t *) 0x12345678UL;

	result = libcpath_path_join_wide(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          test_path2,
	          12,
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

	path = NULL;

	result = libcpath_path_join_wide(
	          &path,
	          NULL,
	          test_path1,
	          13,
	          test_path2,
	          12,
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

	result = libcpath_path_join_wide(
	          &path,
	          &path_size,
	          NULL,
	          13,
	          test_path2,
	          12,
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

	result = libcpath_path_join_wide(
	          &path,
	          &path_size,
	          test_path1,
	          (size_t) SSIZE_MAX + 1,
	          test_path2,
	          12,
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

	result = libcpath_path_join_wide(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          NULL,
	          12,
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

	result = libcpath_path_join_wide(
	          &path,
	          &path_size,
	          test_path1,
	          13,
	          test_path2,
	          (size_t) SSIZE_MAX + 1,
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
	if( path != NULL )
	{
		memory_free(
		 path );
	}
	return( 0 );
}

/* Tests the libcpath_path_make_directory_wide function
 * Returns 1 if successful or 0 if not
 */
int cpath_test_path_make_directory_wide(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcpath_path_make_directory_wide(
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

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

	CPATH_TEST_RUN(
	 "libcpath_path_change_directory",
	 cpath_test_path_change_directory );

	CPATH_TEST_RUN(
	 "libcpath_path_get_current_working_directory",
	 cpath_test_path_get_current_working_directory );

	CPATH_TEST_RUN(
	 "libcpath_path_get_full_path",
	 cpath_test_path_get_full_path );

	CPATH_TEST_RUN(
	 "libcpath_path_get_sanitized_filename",
	 cpath_test_path_get_sanitized_filename );

	CPATH_TEST_RUN(
	 "libcpath_path_get_sanitized_path",
	 cpath_test_path_get_sanitized_path );

	CPATH_TEST_RUN(
	 "libcpath_path_join",
	 cpath_test_path_join );

	CPATH_TEST_RUN(
	 "libcpath_path_make_directory",
	 cpath_test_path_make_directory );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CPATH_TEST_RUN(
	 "libcpath_path_change_directory_wide",
	 cpath_test_path_change_directory_wide );

	CPATH_TEST_RUN(
	 "libcpath_path_get_current_working_directory_wide",
	 cpath_test_path_get_current_working_directory_wide );

	/* TODO: add tests for libcpath_path_get_full_path_wide */

	CPATH_TEST_RUN(
	 "libcpath_path_get_sanitized_filename_wide",
	 cpath_test_path_get_sanitized_filename_wide );

	CPATH_TEST_RUN(
	 "libcpath_path_get_sanitized_path_wide",
	 cpath_test_path_get_sanitized_path_wide );

	CPATH_TEST_RUN(
	 "libcpath_path_join_wide",
	 cpath_test_path_join_wide );

	CPATH_TEST_RUN(
	 "libcpath_path_make_directory_wide",
	 cpath_test_path_make_directory_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

