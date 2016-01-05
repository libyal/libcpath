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

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	wchar_t *full_path       = NULL;
#else
	char *full_path          = NULL;
#endif
	libcerror_error_t *error = NULL;
	size_t full_path_size    = 0;

	if( argc < 2 )
	{
		fprintf(
		 stderr,
		 "Missing filename.\n" );

		return( EXIT_FAILURE );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libcpath_path_get_full_path_wide(
	     argv[ 1 ],
	     libcstring_wide_string_length(
	      argv[ 1 ] ),
	     &full_path,
	     &full_path_size,
	     &error ) != 1 )
#else
	if( libcpath_path_get_full_path(
	     argv[ 1 ],
	     libcstring_narrow_string_length(
	      argv[ 1 ] ),
	     &full_path,
	     &full_path_size,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to determine full path.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	fprintf(
	 stdout,
	 "%ls",
	 full_path );
#else
	fprintf(
	 stdout,
	 "%s",
	 full_path );
#endif
	memory_free(
	 full_path );

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	if( full_path != NULL )
	{
		memory_free(
		 full_path );
	}
	return( EXIT_FAILURE );
}

