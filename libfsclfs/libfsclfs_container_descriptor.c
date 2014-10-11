/*
 * Container descriptor functions
 *
 * Copyright (C) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
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

#include "libfsclfs_container_descriptor.h"
#include "libfsclfs_libcerror.h"

/* Creates a container descriptor
 * Make sure the value container_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_descriptor_initialize(
     libfsclfs_container_descriptor_t **container_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_container_descriptor_initialize";

	if( container_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container descriptor.",
		 function );

		return( -1 );
	}
	if( *container_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid container descriptor value already set.",
		 function );

		return( -1 );
	}
	*container_descriptor = memory_allocate_structure(
	                         libfsclfs_container_descriptor_t );

	if( *container_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create container descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *container_descriptor,
	     0,
	     sizeof( libfsclfs_container_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear container descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *container_descriptor != NULL )
	{
		memory_free(
		 *container_descriptor );

		*container_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a container descriptor
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_descriptor_free(
     libfsclfs_container_descriptor_t **container_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_container_descriptor_free";

	if( container_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container descriptor.",
		 function );

		return( -1 );
	}
	if( *container_descriptor != NULL )
	{
		if( ( *container_descriptor )->name != NULL )
		{
			memory_free(
			 ( *container_descriptor )->name );
		}
		memory_free(
		 *container_descriptor );

		*container_descriptor = NULL;
	}
	return( 1 );
}

