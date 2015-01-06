/*
 * Log range functions
 *
 * Copyright (C) 2010-2015, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libfsclfs_libcerror.h"
#include "libfsclfs_log_range.h"

/* Creates a log range
 * Make sure the value log_range is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_log_range_initialize(
     libfsclfs_log_range_t **log_range,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_log_range_initialize";

	if( log_range == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid log range.",
		 function );

		return( -1 );
	}
	if( *log_range != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid log range value already set.",
		 function );

		return( -1 );
	}
	*log_range = memory_allocate_structure(
	              libfsclfs_log_range_t );

	if( *log_range == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create log range.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *log_range,
	     0,
	     sizeof( libfsclfs_log_range_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear log range.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *log_range != NULL )
	{
		memory_free(
		 *log_range );

		*log_range = NULL;
	}
	return( -1 );
}

/* Frees a log range
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_log_range_free(
     libfsclfs_log_range_t **log_range,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_log_range_free";

	if( log_range == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid log range.",
		 function );

		return( -1 );
	}
	if( *log_range != NULL )
	{
		memory_free(
		 *log_range );

		*log_range = NULL;
	}
	return( 1 );
}

