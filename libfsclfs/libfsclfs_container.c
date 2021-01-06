/*
 * Container functions
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfsclfs_container.h"
#include "libfsclfs_container_descriptor.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_store.h"
#include "libfsclfs_types.h"

/* Creates a container
 * Make sure the value container is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_initialize(
     libfsclfs_container_t **container,
     libfsclfs_internal_store_t *internal_store,
     libfsclfs_container_descriptor_t *container_descriptor,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_initialize";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	if( *container != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid container value already set.",
		 function );

		return( -1 );
	}
	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
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
	internal_container = memory_allocate_structure(
	                      libfsclfs_internal_container_t );

	if( internal_container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create container.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_container,
	     0,
	     sizeof( libfsclfs_internal_container_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear container.",
		 function );

		goto on_error;
	}
	internal_container->internal_store       = internal_store;
	internal_container->container_descriptor = container_descriptor;

	*container = (libfsclfs_container_t *) internal_container;

	return( 1 );

on_error:
	if( internal_container != NULL )
	{
		memory_free(
		 internal_container );
	}
	return( -1 );
}

/* Frees a container
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_free(
     libfsclfs_container_t **container,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_free";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	if( *container != NULL )
	{
		internal_container = (libfsclfs_internal_container_t *) *container;
		*container         = NULL;

		/* The internal_store and container_descriptor references are freed elsewhere
		 */
		memory_free(
		 internal_container );
	}
	return( 1 );
}

/* Opens a container
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_open(
     libfsclfs_container_t *container,
     const char *filename,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_open";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	internal_container = (libfsclfs_internal_container_t *) container;

	if( internal_container->container_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid container - missing container descriptor.",
		 function );

		return( -1 );
	}
	if( libfsclfs_store_open_container(
	     internal_container->internal_store,
	     internal_container->container_descriptor->physical_number,
	     filename,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open container: %s.",
		 function,
		 filename );

		return( -1 );
	}
	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a container
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_open_wide(
     libfsclfs_container_t *container,
     const wchar_t *filename,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_open_wide";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	internal_container = (libfsclfs_internal_container_t *) container;

	if( internal_container->container_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid container - missing container descriptor.",
		 function );

		return( -1 );
	}
	if( libfsclfs_store_open_container_wide(
	     internal_container->internal_store,
	     internal_container->container_descriptor->physical_number,
	     filename,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open container: %ls.",
		 function,
		 filename );

		return( -1 );
	}
	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_get_size(
     libfsclfs_container_t *container,
     size64_t *size,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_get_size";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	internal_container = (libfsclfs_internal_container_t *) container;

	if( libfsclfs_container_descriptor_get_size(
	     internal_container->container_descriptor,
	     size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size from container descriptor.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_get_utf8_name_size(
     libfsclfs_container_t *container,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_get_utf8_name_size";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	internal_container = (libfsclfs_internal_container_t *) container;

	if( libfsclfs_container_descriptor_get_utf8_name_size(
	     internal_container->container_descriptor,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 name size from container descriptor.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded name value
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_get_utf8_name(
     libfsclfs_container_t *container,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_get_utf8_name";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	internal_container = (libfsclfs_internal_container_t *) container;

	if( libfsclfs_container_descriptor_get_utf8_name(
	     internal_container->container_descriptor,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 name from container descriptor.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_get_utf16_name_size(
     libfsclfs_container_t *container,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_get_utf16_name_size";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	internal_container = (libfsclfs_internal_container_t *) container;

	if( libfsclfs_container_descriptor_get_utf16_name_size(
	     internal_container->container_descriptor,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 name size from container descriptor.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded name value
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_get_utf16_name(
     libfsclfs_container_t *container,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_container_t *internal_container = NULL;
	static char *function                              = "libfsclfs_container_get_utf16_name";

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	internal_container = (libfsclfs_internal_container_t *) container;

	if( libfsclfs_container_descriptor_get_utf16_name(
	     internal_container->container_descriptor,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 name from container descriptor.",
		 function );

		return( -1 );
	}
	return( 1 );
}

