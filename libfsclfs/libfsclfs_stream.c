/*
 * Stream functions
 *
 * Copyright (C) 2010-2016, Joachim Metz <joachim.metz@gmail.com>
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

#include "libfsclfs_definitions.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_libuna.h"
#include "libfsclfs_record.h"
#include "libfsclfs_record_value.h"
#include "libfsclfs_stream.h"
#include "libfsclfs_types.h"

/* Creates a stream
 * Make sure the value stream is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_initialize(
     libfsclfs_stream_t **stream,
     libfsclfs_internal_store_t *internal_store,
     libfsclfs_stream_descriptor_t *stream_descriptor,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	static char *function                        = "libfsclfs_stream_initialize";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stream value already set.",
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
	internal_stream = memory_allocate_structure(
	                   libfsclfs_internal_stream_t );

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create stream.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_stream,
	     0,
	     sizeof( libfsclfs_internal_stream_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear stream.",
		 function );

		goto on_error;
	}
	internal_stream->internal_store    = internal_store;
	internal_stream->stream_descriptor = stream_descriptor;

	*stream = (libfsclfs_stream_t *) internal_stream;

	return( 1 );

on_error:
	if( internal_stream != NULL )
	{
		memory_free(
		 internal_stream );
	}
	return( -1 );
}

/* Frees a stream
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_free(
     libfsclfs_stream_t **stream,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	static char *function                        = "libfsclfs_stream_free";
	int result                                   = 1;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		internal_stream = (libfsclfs_internal_stream_t *) *stream;
		*stream         = NULL;

		/* The internal_store and store_descriptor references are freed elsewhere
		 */
		memory_free(
		 internal_stream );
	}
	return( result );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_get_utf8_name_size(
     libfsclfs_stream_t *stream,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	static char *function                        = "libfsclfs_stream_get_utf8_name_size";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfsclfs_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_stream->stream_descriptor->name,
	     internal_stream->stream_descriptor->name_size,
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
int libfsclfs_stream_get_utf8_name(
     libfsclfs_stream_t *stream,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	static char *function                        = "libfsclfs_stream_get_utf8_name";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfsclfs_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_stream->stream_descriptor->name,
	     internal_stream->stream_descriptor->name_size,
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
int libfsclfs_stream_get_utf16_name_size(
     libfsclfs_stream_t *stream,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	static char *function                        = "libfsclfs_stream_get_utf16_name_size";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfsclfs_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_stream->stream_descriptor->name,
	     internal_stream->stream_descriptor->name_size,
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
int libfsclfs_stream_get_utf16_name(
     libfsclfs_stream_t *stream,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	static char *function                        = "libfsclfs_stream_get_utf16_name";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfsclfs_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_stream->stream_descriptor->name,
	     internal_stream->stream_descriptor->name_size,
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
int libfsclfs_stream_get_base_lsn(
     libfsclfs_stream_t *stream,
     uint64_t *base_lsn,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	static char *function                        = "libfsclfs_stream_get_base_lsn";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfsclfs_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
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
	*base_lsn = internal_stream->stream_descriptor->base_lsn;

	return( 1 );
}

/* Retrieve the last log sequence number (LSN)
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_stream_get_last_lsn(
     libfsclfs_stream_t *stream,
     uint64_t *last_lsn,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	static char *function                        = "libfsclfs_stream_get_last_lsn";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfsclfs_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
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
	*last_lsn = internal_stream->stream_descriptor->last_lsn;

	return( 1 );
}

/* Retrieve a record with a specific log sequence number (LSN)
 * Returns 1 if successful, 0 if no such record or -1 on error
 */
int libfsclfs_stream_get_record_by_lsn(
     libfsclfs_stream_t *stream,
     uint64_t record_lsn,
     libfsclfs_record_t **record,
     libcerror_error_t **error )
{
	libfsclfs_internal_stream_t *internal_stream = NULL;
	libfsclfs_record_value_t *record_value       = NULL;
	static char *function                        = "libfsclfs_stream_get_record_by_lsn";
        uint32_t block_offset                        = 0;
        uint32_t container_logical_number            = 0;
	uint16_t record_number                       = 0;
	int result                                   = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfsclfs_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( record_lsn == (uint64_t) 0xffffffffUL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record LSN.",
		 function );

		return( -1 );
	}
	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	if( *record != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid record value already set.",
		 function );

		return( -1 );
	}
	block_offset             = (uint32_t) ( record_lsn & 0xfffffe00UL );
        container_logical_number = (uint32_t) ( record_lsn >> 32 );
        record_number            = (uint16_t) ( record_lsn & 0x01ff );

	result = libfsclfs_store_get_record_value_by_logical_lsn(
	          internal_stream->internal_store,
	          internal_stream->stream_descriptor->number,
	          container_logical_number,
	          block_offset,
	          record_number,
	          &record_value,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: unable to retrieve logical LSN: %" PRIx32 ".%" PRIx32 ".%" PRIx32 ".",
		 function,
		 container_logical_number,
		 block_offset,
		 record_number );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( record_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing record value.",
			 function );

			return( -1 );
		}
		if( libfsclfs_record_initialize(
		     record,
		     internal_stream,
		     record_value,
		     LIBFSCLFS_RECORD_FLAGS_DEFAULT,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create record.",
			 function );

/* TODO is record value maintained by a cache ? */

			return( -1 );
		}
	}
	return( result );
}

