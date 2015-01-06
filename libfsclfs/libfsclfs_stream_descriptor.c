/*
 * Stream descriptor functions
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
#include "libfsclfs_stream_descriptor.h"

/* Creates a stream descriptor
 * Make sure the value stream_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_descriptor_initialize(
     libfsclfs_stream_descriptor_t **stream_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_descriptor_initialize";

	if( stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream descriptor.",
		 function );

		return( -1 );
	}
	if( *stream_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stream descriptor value already set.",
		 function );

		return( -1 );
	}
	*stream_descriptor = memory_allocate_structure(
	                      libfsclfs_stream_descriptor_t );

	if( *stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create stream descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *stream_descriptor,
	     0,
	     sizeof( libfsclfs_stream_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear stream descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *stream_descriptor != NULL )
	{
		memory_free(
		 *stream_descriptor );

		*stream_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a stream descriptor
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_descriptor_free(
     libfsclfs_stream_descriptor_t **stream_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_descriptor_free";

	if( stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream descriptor.",
		 function );

		return( -1 );
	}
	if( *stream_descriptor != NULL )
	{
		if( ( *stream_descriptor )->name != NULL )
		{
			memory_free(
			 ( *stream_descriptor )->name );
		}
		memory_free(
		 *stream_descriptor );

		*stream_descriptor = NULL;
	}
	return( 1 );
}

