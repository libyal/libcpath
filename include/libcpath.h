/*
 * Library to support cross-platform C path functions
 *
 * Copyright (c) 2008-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBCPATH_H )
#define _LIBCPATH_H

#include <libcpath/codepage.h>
#include <libcpath/definitions.h>
#include <libcpath/error.h>
#include <libcpath/extern.h>
#include <libcpath/features.h>
#include <libcpath/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version as a string
 */
LIBCPATH_EXTERN \
const char *libcpath_get_version(
             void );

#if defined( __cplusplus )
}
#endif

#endif

