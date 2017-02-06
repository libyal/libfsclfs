/*
 * Record functions
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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
#include "libfsclfs_io_handle.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_record.h"
#include "libfsclfs_record_value.h"
#include "libfsclfs_stream.h"
#include "libfsclfs_types.h"

/* Creates a record
 * Make sure the value record is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_initialize(
     libfsclfs_record_t **record,
     libfsclfs_internal_stream_t *internal_stream,
     libfsclfs_record_value_t *record_value,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfsclfs_internal_record_t *internal_record = NULL;
	static char *function                        = "libfsclfs_record_initialize";

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
	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal stream.",
		 function );

		return( -1 );
	}
	if( ( flags & ~( LIBFSCLFS_RECORD_FLAG_IO_HANDLE_MANAGED ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	internal_record = memory_allocate_structure(
	                   libfsclfs_internal_record_t );

	if( internal_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create record.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_record,
	     0,
	     sizeof( libfsclfs_internal_record_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear record.",
		 function );

		goto on_error;
	}
	internal_record->internal_stream = internal_stream;
	internal_record->record_value    = record_value;
	internal_record->flags           = flags;

	*record = (libfsclfs_record_t *) internal_record;

	return( 1 );

on_error:
	if( internal_record != NULL )
	{
		memory_free(
		 internal_record );
	}
	return( -1 );
}

/* Frees a record
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_free(
     libfsclfs_record_t **record,
     libcerror_error_t **error )
{
	libfsclfs_internal_record_t *internal_record = NULL;
	static char *function                        = "libfsclfs_record_free";
	int result                                   = 1;

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
		internal_record = (libfsclfs_internal_record_t *) *record;
		*record         = NULL;

		/* The internal_stream reference is freed elsewhere
		 */
		if( libfsclfs_record_value_free(
		     &( internal_record->record_value ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free record value.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_record );
	}
	return( result );
}

/* Retrieve the previous log sequence number (LSN)
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_get_previous_lsn(
     libfsclfs_record_t *record,
     uint64_t *previous_lsn,
     libcerror_error_t **error )
{
	libfsclfs_internal_record_t *internal_record = NULL;
	static char *function                        = "libfsclfs_record_get_previous_lsn";

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
	internal_record = (libfsclfs_internal_record_t *) record;

	if( internal_record->record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record - missing record value.",
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
	*previous_lsn = internal_record->record_value->previous_lsn;

	return( 1 );
}

/* Retrieve the undo-next log sequence number (LSN)
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_get_undo_next_lsn(
     libfsclfs_record_t *record,
     uint64_t *undo_next_lsn,
     libcerror_error_t **error )
{
	libfsclfs_internal_record_t *internal_record = NULL;
	static char *function                        = "libfsclfs_record_get_undo_next_lsn";

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
	internal_record = (libfsclfs_internal_record_t *) record;

	if( internal_record->record_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record - missing record value.",
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
	*undo_next_lsn = internal_record->record_value->undo_next_lsn;

	return( 1 );
}

/* Retrieves the record data
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_record_get_data(
     libfsclfs_record_t *record,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfsclfs_internal_record_t *internal_record = NULL;
	static char *function                        = "libfsclfs_record_get_data";

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
	internal_record = (libfsclfs_internal_record_t *) record;

	if( libfsclfs_record_value_get_data(
	     internal_record->record_value,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

