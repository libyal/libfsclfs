/*
 * Block descriptor functions
 *
 * Copyright (C) 2010-2023, Joachim Metz <joachim.metz@gmail.com>
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

#include "libfsclfs_block_descriptor.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_libcnotify.h"

#include "fsclfs_base_log_record.h"

/* Creates a block descriptor
 * Make sure the value block_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_block_descriptor_initialize(
     libfsclfs_block_descriptor_t **block_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_block_descriptor_initialize";

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( *block_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block descriptor value already set.",
		 function );

		return( -1 );
	}
	*block_descriptor = memory_allocate_structure(
	                     libfsclfs_block_descriptor_t );

	if( *block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_descriptor,
	     0,
	     sizeof( libfsclfs_block_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *block_descriptor != NULL )
	{
		memory_free(
		 *block_descriptor );

		*block_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a block descriptor
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_block_descriptor_free(
     libfsclfs_block_descriptor_t **block_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_block_descriptor_free";

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( *block_descriptor != NULL )
	{
		memory_free(
		 *block_descriptor );

		*block_descriptor = NULL;
	}
	return( 1 );
}

/* Reads the block descriptor
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_block_descriptor_read_data(
     libfsclfs_block_descriptor_t *block_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_block_descriptor_read_data";

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
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
		 "%s: block descriptor data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	if( data_size != sizeof( fsclfs_base_log_block_descriptor_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported block descriptor data size: %" PRIzd "\n",
		 function,
		 data_size );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_block_descriptor_t *) data )->block_size,
	 block_descriptor->size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_block_descriptor_t *) data )->block_offset,
	 block_descriptor->offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_block_descriptor_t *) data )->block_number,
	 block_descriptor->block_number );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: unknown1:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_block_descriptor_t *) data )->unknown1,
		 12,
		 0 );

		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 block_descriptor->size );

		libcnotify_printf(
		 "%s: offset\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 block_descriptor->offset );

		libcnotify_printf(
		 "%s: number\t\t\t\t: %" PRIu32 "\n",
		 function,
		 block_descriptor->block_number );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

