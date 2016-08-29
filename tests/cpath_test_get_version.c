/*
 * Library get version test program
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

#include "cpath_test_libcpath.h"
#include "cpath_test_libcstring.h"
#include "cpath_test_macros.h"
#include "cpath_test_unused.h"

/* Tests retrieving the library version
 * Returns 1 if successful or 0 if not
 */
int cpath_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = libcpath_get_version();

	result = libcstring_narrow_string_compare(
	          version_string,
	          LIBCPATH_VERSION_STRING,
	          9 );

	CPATH_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
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

	CPATH_TEST_RUN(
	 "libcpath_get_version",
	 cpath_test_get_version() )

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

