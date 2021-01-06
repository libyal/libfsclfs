/*
 * Record value functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfsclfs_debug.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_libcnotify.h"
#include "libfsclfs_record_value.h"

#include "fsclfs_record.h"

/* Creates a record value
 * Make sure the value record_value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_value_initialize(
     libfsclfs_record_value_t **record_value,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_record_value_initialize";

	if( record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record value.",
		 function );

		return( -1 );
	}
	if( *record_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid record value value already set.",
		 function );

		return( -1 );
	}
	*record_value = memory_allocate_structure(
	                 libfsclfs_record_value_t );

	if( *record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create record value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *record_value,
	     0,
	     sizeof( libfsclfs_record_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear record value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *record_value != NULL )
	{
		memory_free(
		 *record_value );

		*record_value = NULL;
	}
	return( -1 );
}

/* Frees a record value
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_value_free(
     libfsclfs_record_value_t **record_value,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_record_value_free";

	if( record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record value.",
		 function );

		return( -1 );
	}
	if( *record_value != NULL )
	{
		if( ( *record_value )->data != NULL )
		{
			memory_free(
			 ( *record_value )->data );
		}
		memory_free(
		 *record_value );

		*record_value = NULL;
	}
	return( 1 );
}

/* Reads the record value data
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_value_read_data(
     libfsclfs_record_value_t *record_value,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_record_value_read_data";
	uint16_t data_offset  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record value.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( fsclfs_container_record_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: record header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( fsclfs_container_record_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint64_little_endian(
	 ( (fsclfs_container_record_header_t *) data )->virtual_lsn,
	 record_value->virtual_lsn );

	byte_stream_copy_to_uint64_little_endian(
	 ( (fsclfs_container_record_header_t *) data )->undo_next_lsn,
	 record_value->undo_next_lsn );

	byte_stream_copy_to_uint64_little_endian(
	 ( (fsclfs_container_record_header_t *) data )->previous_lsn,
	 record_value->previous_lsn );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_container_record_header_t *) data )->size,
	 record_value->size );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsclfs_container_record_header_t *) data )->flags,
	 record_value->flags );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsclfs_container_record_header_t *) data )->data_offset,
	 data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_container_record_header_t *) data )->record_type,
	 record_value->type );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: virtual log sequence number\t\t: 0x%08" PRIx64 "\n",
		 function,
		 record_value->virtual_lsn );

		libcnotify_printf(
		 "%s: undo-next log sequence number\t\t: 0x%08" PRIx64 "\n",
		 function,
		 record_value->undo_next_lsn );

		libcnotify_printf(
		 "%s: previous log sequence number\t\t: 0x%08" PRIx64 "\n",
		 function,
		 record_value->previous_lsn );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 record_value->size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_container_record_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: flags\t\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 record_value->flags );

		libcnotify_printf(
		 "%s: data offset\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 data_offset );

		libcnotify_printf(
		 "%s: record type\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 record_value->type );
		libfsclfs_debug_print_record_type(
		 record_value->type );
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( ( record_value->size < sizeof( fsclfs_container_record_header_t ) )
	 || ( (size_t) record_value->size > data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid record size value out of bounds.",
		 function );

		goto on_error;
	}
	if( ( data_offset < sizeof( fsclfs_container_record_header_t ) )
	 || ( (size_t) data_offset >= data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( data_offset > sizeof( fsclfs_container_record_header_t ) )
		{
			libcnotify_printf(
			 "%s: record header trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ sizeof( fsclfs_container_record_header_t ) ] ),
			 data_offset - sizeof( fsclfs_container_record_header_t ),
			 0 );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	record_value->data_size = record_value->size - data_offset;

	record_value->data = (uint8_t *) memory_allocate(
	                                  sizeof( uint8_t ) * record_value->data_size );

	if( record_value->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create record value data.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     record_value->data,
	     &( data[ data_offset ] ),
	     record_value->data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy record value data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: record data:\n",
		 function );
		libcnotify_print_data(
		 record_value->data,
		 record_value->data_size,
		 0 );
	}
#endif
	return( 1 );

on_error:
	if( record_value->data != NULL )
	{
		memory_free(
		 record_value->data );

		record_value->data = NULL;
	}
	record_value->data_size = 0;

	return( -1 );
}

/* Retrieve the record type
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_value_get_type(
     libfsclfs_record_value_t *record_value,
     uint32_t *record_type,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_record_value_get_type";

	if( record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record value.",
		 function );

		return( -1 );
	}
	if( record_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record type.",
		 function );

		return( -1 );
	}
	*record_type = record_value->type;

	return( 1 );
}

/* Retrieve the record flags
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_value_get_flags(
     libfsclfs_record_value_t *record_value,
     uint16_t *record_flags,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_record_value_get_flags";

	if( record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record value.",
		 function );

		return( -1 );
	}
	if( record_flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record flags.",
		 function );

		return( -1 );
	}
	*record_flags = record_value->flags;

	return( 1 );
}

/* Retrieve the previous log sequence number (LSN)
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_value_get_previous_lsn(
     libfsclfs_record_value_t *record_value,
     uint64_t *previous_lsn,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_record_value_get_previous_lsn";

	if( record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record value.",
		 function );

		return( -1 );
	}
	if( previous_lsn == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid previous LSN.",
		 function );

		return( -1 );
	}
	*previous_lsn = record_value->previous_lsn;

	return( 1 );
}

/* Retrieve the undo-next log sequence number (LSN)
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_value_get_undo_next_lsn(
     libfsclfs_record_value_t *record_value,
     uint64_t *undo_next_lsn,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_record_value_get_undo_next_lsn";

	if( record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record value.",
		 function );

		return( -1 );
	}
	if( undo_next_lsn == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid undo-next LSN.",
		 function );

		return( -1 );
	}
	*undo_next_lsn = record_value->undo_next_lsn;

	return( 1 );
}

/* Retrieves the record data
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_value_get_data(
     libfsclfs_record_value_t *record_value,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_record_value_get_data";

	if( record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record value.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	*data      = record_value->data;
	*data_size = record_value->data_size;

	return( 1 );
}

