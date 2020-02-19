/*
 * Stream descriptor functions
 *
 * Copyright (C) 2010-2020, Joachim Metz <joachim.metz@gmail.com>
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

#include "libfsclfs_libcerror.h"
#include "libfsclfs_stream_descriptor.h"
#include "libfsclfs_libcnotify.h"
#include "libfsclfs_libuna.h"

#include "fsclfs_base_log_record.h"

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

/* Reads the stream descriptor
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_descriptor_read_data(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_descriptor_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit  = 0;
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

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
		 "%s: stream descriptor data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	if( data_size != sizeof( fsclfs_base_log_stream_attributes_record_data_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported stream descriptor data size: %" PRIzd "\n",
		 function,
		 data_size );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->stream_number,
	 stream_descriptor->number );

	byte_stream_copy_to_uint64_little_endian(
	 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->base_lsn,
	 stream_descriptor->base_lsn );

	byte_stream_copy_to_uint64_little_endian(
	 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->last_flushed_lsn,
	 stream_descriptor->last_flushed_lsn );

	byte_stream_copy_to_uint64_little_endian(
	 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->last_lsn,
	 stream_descriptor->last_lsn );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: stream number\t\t\t: %" PRIu16 "\n",
		 function,
		 stream_descriptor->number );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->unknown1,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->flush_queue_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: flush queue size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown3:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->unknown3,
		 40,
		 0 );

		byte_stream_copy_to_uint64_little_endian(
		 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->unknown4,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: base log sequence number\t\t: 0x%08" PRIx64 "\n",
		 function,
		 stream_descriptor->base_lsn );

		libcnotify_printf(
		 "%s: last flushed log sequence number\t: 0x%08" PRIx64 "\n",
		 function,
		 stream_descriptor->last_flushed_lsn );

		libcnotify_printf(
		 "%s: last log sequence number\t\t: 0x%08" PRIx64 "\n",
		 function,
		 stream_descriptor->last_lsn );

		byte_stream_copy_to_uint64_little_endian(
		 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->unknown5,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->unknown6,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown6\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: unknown7:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_stream_attributes_record_data_t *) data )->unknown7,
		 32,
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_descriptor_get_utf8_name_size(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_descriptor_get_utf8_name_size";

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
	if( libuna_utf8_string_size_from_utf16_stream(
	     stream_descriptor->name,
	     stream_descriptor->name_size,
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
int libfsclfs_stream_descriptor_get_utf8_name(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_descriptor_get_utf8_name";

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
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     stream_descriptor->name,
	     stream_descriptor->name_size,
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
int libfsclfs_stream_descriptor_get_utf16_name_size(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_descriptor_get_utf16_name_size";

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
	if( libuna_utf16_string_size_from_utf16_stream(
	     stream_descriptor->name,
	     stream_descriptor->name_size,
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
int libfsclfs_stream_descriptor_get_utf16_name(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_descriptor_get_utf16_name";

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
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     stream_descriptor->name,
	     stream_descriptor->name_size,
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

/* Retrieve the base log sequence number (LSN)
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_descriptor_get_base_lsn(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     uint64_t *base_lsn,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_descriptor_get_base_lsn";

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
	if( base_lsn == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base LSN.",
		 function );

		return( -1 );
	}
	*base_lsn = stream_descriptor->base_lsn;

	return( 1 );
}

/* Retrieve the last log sequence number (LSN)
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_descriptor_get_last_lsn(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     uint64_t *last_lsn,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_stream_get_last_lsn";

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
	if( last_lsn == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid last LSN.",
		 function );

		return( -1 );
	}
	*last_lsn = stream_descriptor->last_lsn;

	return( 1 );
}
