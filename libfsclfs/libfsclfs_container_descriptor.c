/*
 * Container descriptor functions
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfsclfs_container_descriptor.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_libcnotify.h"
#include "libfsclfs_libuna.h"

#include "fsclfs_base_log_record.h"

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

/* Reads the container descriptor
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_descriptor_read_data(
     libfsclfs_container_descriptor_t *container_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_container_descriptor_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit  = 0;
	uint32_t value_32bit  = 0;
#endif

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
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: container descriptor data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	if( data_size != sizeof( fsclfs_base_log_container_attributes_record_data_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported container descriptor data size: %" PRIzd "\n",
		 function,
		 data_size );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->file_size,
	 container_descriptor->file_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->physical_number,
	 container_descriptor->physical_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->logical_number,
	 container_descriptor->logical_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->unknown2,
	 container_descriptor->unknown2 );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file size\t\t\t: %" PRIu32 "\n",
		 function,
		 container_descriptor->file_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: physical number\t\t: %" PRIu32 "\n",
		 function,
		 container_descriptor->physical_number );

		libcnotify_printf(
		 "%s: logical number\t\t: %" PRIu32 "\n",
		 function,
		 container_descriptor->logical_number );

		libcnotify_printf(
		 "%s: unknown2\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 container_descriptor->unknown2 );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->number_of_streams,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of streams\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->unknown5,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (fsclfs_base_log_container_attributes_record_data_t *) data )->unknown6,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown6\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_descriptor_get_size(
     libfsclfs_container_descriptor_t *container_descriptor,
     size64_t *size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_container_descriptor_get_size";

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
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = (size64_t) container_descriptor->file_size;

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_descriptor_get_utf8_name_size(
     libfsclfs_container_descriptor_t *container_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_container_descriptor_get_utf8_name_size";

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
	if( libuna_utf8_string_size_from_utf16_stream(
	     container_descriptor->name,
	     container_descriptor->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded name value
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_descriptor_get_utf8_name(
     libfsclfs_container_descriptor_t *container_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_container_descriptor_get_utf8_name";

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
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     container_descriptor->name,
	     container_descriptor->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy name to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_descriptor_get_utf16_name_size(
     libfsclfs_container_descriptor_t *container_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_container_descriptor_get_utf16_name_size";

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
	if( libuna_utf16_string_size_from_utf16_stream(
	     container_descriptor->name,
	     container_descriptor->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded name value
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_container_descriptor_get_utf16_name(
     libfsclfs_container_descriptor_t *container_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_container_descriptor_get_utf16_name";

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
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     container_descriptor->name,
	     container_descriptor->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy name to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

