/*
 * Owner page functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfsclfs_block.h"
#include "libfsclfs_libbfio.h"
#include "libfsclfs_libcdata.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_libcnotify.h"
#include "libfsclfs_log_range.h"
#include "libfsclfs_owner_page.h"

/* Creates an owner page
 * Make sure the value owner_page is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_owner_page_initialize(
     libfsclfs_owner_page_t **owner_page,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_owner_page_initialize";

	if( owner_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid owner page.",
		 function );

		return( -1 );
	}
	if( *owner_page != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid owner page value already set.",
		 function );

		return( -1 );
	}
	*owner_page = memory_allocate_structure(
	               libfsclfs_owner_page_t );

	if( *owner_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create owner page.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *owner_page,
	     0,
	     sizeof( libfsclfs_owner_page_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear owner page.",
		 function );

		memory_free(
		 *owner_page );

		*owner_page = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *owner_page )->physical_log_ranges_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create physical log ranges array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( ( *owner_page )->virtual_log_ranges_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create virtual log ranges array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *owner_page != NULL )
	{
		if( ( *owner_page )->virtual_log_ranges_array != NULL )
		{
			libcdata_array_free(
			 &( ( *owner_page )->virtual_log_ranges_array ),
			 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
			 NULL );
		}
		if( ( *owner_page )->physical_log_ranges_array != NULL )
		{
			libcdata_array_free(
			 &( ( *owner_page )->physical_log_ranges_array ),
			 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
			 NULL );
		}
		memory_free(
		 *owner_page );

		*owner_page = NULL;
	}
	return( -1 );
}

/* Frees an owner page
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_owner_page_free(
     libfsclfs_owner_page_t **owner_page,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_owner_page_free";
	int result            = 1;

	if( owner_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid owner page.",
		 function );

		return( -1 );
	}
	if( *owner_page != NULL )
	{
		if( libcdata_array_free(
		     &( ( *owner_page )->virtual_log_ranges_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free virtual log ranges array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *owner_page )->physical_log_ranges_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free physical log ranges array.",
			 function );

			result = -1;
		}
		memory_free(
		 *owner_page );

		*owner_page = NULL;
	}
	return( result );
}

/* Reads the owner page
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_owner_page_read(
     libfsclfs_owner_page_t *owner_page,
     libfsclfs_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     int number_of_streams,
     uint32_t offset,
     libcerror_error_t **error )
{
	libcdata_array_t *virtual_log_ranges_array = NULL;
	libfsclfs_block_t *block                   = NULL;
	uint8_t *sector_mapping_array_data         = NULL;
	uint8_t *virtual_log_range_array_data      = NULL;
	static char *function                      = "libfsclfs_owner_page_read";
	size_t sector_mapping_array_data_size      = 0;
	size_t virtual_log_range_array_data_size   = 0;

	if( owner_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid owner page.",
		 function );

		return( -1 );
	}
	if( libfsclfs_block_initialize(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	if( libfsclfs_block_read(
	     block,
	     io_handle,
	     file_io_handle,
	     offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block at offset: %" PRIu32 ".",
		 function,
		 offset );

		goto on_error;
	}
	if( libfsclfs_block_get_virtual_log_range_array_data(
	     block,
	     &virtual_log_range_array_data,
	     &virtual_log_range_array_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable retrieve virtual log range array data.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &virtual_log_ranges_array,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create virtual log ranges array.",
		 function );

		goto on_error;
	}
	if( libfsclfs_owner_page_read_virtual_log_range_array(
	     owner_page,
	     virtual_log_ranges_array,
	     number_of_streams,
	     virtual_log_range_array_data,
	     virtual_log_range_array_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read virtual log range array.",
		 function );

		goto on_error;
	}
	if( libfsclfs_block_get_sector_mapping_array_data(
	     block,
	     &sector_mapping_array_data,
	     &sector_mapping_array_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable retrieve sector mapping array data.",
		 function );

		goto on_error;
	}
	if( libfsclfs_owner_page_read_sector_mapping_array(
	     owner_page,
	     io_handle,
	     virtual_log_ranges_array,
	     number_of_streams,
	     offset,
	     sector_mapping_array_data,
	     sector_mapping_array_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read sector mapping array.",
		 function );

		goto on_error;
	}
	if( libfsclfs_block_free(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free block.",
		 function );

		goto on_error;
	}
	if( libcdata_array_free(
	     &virtual_log_ranges_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free virtual log ranges array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( virtual_log_ranges_array != NULL )
	{
		libcdata_array_free(
		 &virtual_log_ranges_array,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
		 NULL );
	}
	if( block != NULL )
	{
		libfsclfs_block_free(
		 &block,
		 NULL );
	}
	return( -1 );
}

/* Reads the owner page virtual log range array
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_owner_page_read_virtual_log_range_array(
     libfsclfs_owner_page_t *owner_page,
     libcdata_array_t *virtual_log_ranges_array,
     int number_of_streams,
     const uint8_t *virtual_log_range_array_data,
     size_t virtual_log_range_array_data_size,
     libcerror_error_t **error )
{
	libfsclfs_log_range_t *log_range = NULL;
	static char *function            = "libfsclfs_owner_page_read_virtual_log_range_array";
	int stream_index                 = 0;

	if( owner_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid owner page.",
		 function );

		return( -1 );
	}
	if( number_of_streams <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of streams.",
		 function );

		return( -1 );
	}
	if( virtual_log_range_array_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid virtual log range array data.",
		 function );

		return( -1 );
	}
	if( virtual_log_range_array_data_size < (size_t) ( number_of_streams * 16 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid virtual log range array data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: virtual log range array data:\n",
		 function );
		libcnotify_print_data(
		 virtual_log_range_array_data,
		 number_of_streams * 16,
		 0 );
	}
#endif
	if( libcdata_array_resize(
	     virtual_log_ranges_array,
	     number_of_streams,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable resize virtual log ranges array.",
		 function );

		goto on_error;
	}
	for( stream_index = 0;
	     stream_index < number_of_streams;
	     stream_index++ )
	{
		if( libfsclfs_log_range_initialize(
		     &log_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create log range.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint64_little_endian(
		 virtual_log_range_array_data,
		 log_range->start_lsn );

		virtual_log_range_array_data += 8;

		byte_stream_copy_to_uint64_little_endian(
		 virtual_log_range_array_data,
		 log_range->end_lsn );

		virtual_log_range_array_data += 8;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: log range: %02d\t: 0x%08" PRIx64 " - 0x%08" PRIx64 "\n",
			 function,
			 stream_index,
			 log_range->start_lsn,
			 log_range->end_lsn );
		}
#endif
		if( libcdata_array_set_entry_by_index(
		     virtual_log_ranges_array,
		     stream_index,
		     (intptr_t *) log_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set log range: %d.",
			 function,
			 stream_index );

			goto on_error;
		}
		log_range = NULL;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	libcdata_array_resize(
	 virtual_log_ranges_array,
	 0,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
	 NULL );

	if( log_range != NULL )
	{
		libfsclfs_log_range_free(
		 &log_range,
		 NULL );
	}
	return( -1 );
}

/* Reads the owner page sector mapping array
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_owner_page_read_sector_mapping_array(
     libfsclfs_owner_page_t *owner_page,
     libfsclfs_io_handle_t *io_handle,
     libcdata_array_t *virtual_log_ranges_array,
     int number_of_streams,
     uint32_t offset,
     const uint8_t *sector_mapping_array_data,
     size_t sector_mapping_array_data_size,
     libcerror_error_t **error )
{
	libfsclfs_log_range_t *physical_log_range     = NULL;
	libfsclfs_log_range_t *virtual_log_range      = NULL;
	libfsclfs_log_range_t *virtual_full_log_range = NULL;
	static char *function                         = "libfsclfs_owner_page_read_sector_mapping_array";
	uint32_t region_offset                        = 0;
	uint8_t first_block_sector_number             = 0;
	uint8_t last_block_sector_number              = 0;
	uint8_t stream_number                         = 0;
	int entry_index                               = 0;
	int first_sector                              = 0;
	int new_log_range                             = 0;
	int sector_index                              = 0;

	if( owner_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid owner page.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( sector_mapping_array_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sector mapping array data.",
		 function );

		return( -1 );
	}
	if( sector_mapping_array_data_size > ( 1024 * 2 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
		 "%s: invalid sector mapping array data size value too large.",
		 function );

		return( -1 );
	}
	if( number_of_streams <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of streams.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: sector mapping array data:\n",
		 function );
		libcnotify_print_data(
		 sector_mapping_array_data,
		 sector_mapping_array_data_size,
		 0 );
	}
#endif
	region_offset             = offset - io_handle->region_owner_page_offset;
	stream_number             = sector_mapping_array_data[ 0 ];
	first_block_sector_number = sector_mapping_array_data[ 1 ];
	last_block_sector_number  = sector_mapping_array_data[ 1 ];
	sector_index              = 1;

fprintf( stderr, "X: 0x%08" PRIx32 ": 0x%02" PRIx8 ", 0x%02" PRIx8 "\n",
 region_offset,
 sector_mapping_array_data[ 0 ], sector_mapping_array_data[ 1 ] );

	sector_mapping_array_data      += 2;
	sector_mapping_array_data_size -= 2;

	while( sector_mapping_array_data_size > 0 )
	{
		/* The range of the owner page itself is represented by 0xff 0xff
		 */
		if( ( sector_mapping_array_data[ 0 ] == 0xff )
		 && ( sector_mapping_array_data[ 1 ] == 0xff ) )
		{
		}
		else if( sector_mapping_array_data[ 0 ] != stream_number )
		{
			new_log_range = 1;
		}
		else if( sector_mapping_array_data[ 1 ] <= last_block_sector_number )
		{
			new_log_range = 1;
		}
		if( new_log_range != 0 )
		{
			if( ( stream_number == 0 )
			 || ( (int) stream_number >= number_of_streams ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid stream number value out of bounds.",
				 function );

				goto on_error;
			}
			if( libcdata_array_get_entry_by_index(
			     virtual_log_ranges_array,
			     stream_number,
			     (intptr_t **) &virtual_full_log_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve virtual full log range: %d.",
				 function,
				 stream_number );

				goto on_error;
			}
			if( virtual_full_log_range == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing virtual full log range: %d.",
				 function,
				 stream_number );

				goto on_error;
			}
			if( libfsclfs_log_range_initialize(
			     &physical_log_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create physical log range.",
				 function );

				goto on_error;
			}
			if( libfsclfs_log_range_initialize(
			     &virtual_log_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create virtual log range.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: stream: %02" PRIu8 " range\t: %02" PRIu8 " - %02" PRIu8 "\n",
				 function,
				 stream_number,
				 first_block_sector_number,
				 last_block_sector_number );

				libcnotify_printf(
				 "\t\t\t\t\t\t\t\t\t: physical: 0x%08" PRIx64 " - 0x%08" PRIx64 "\n",
				 region_offset + ( first_sector * io_handle->bytes_per_sector ),
				 region_offset + ( sector_index * io_handle->bytes_per_sector ) - 1 );
			}
#endif
			if( virtual_full_log_range->current_lsn == 0 )
			{
				if( first_block_sector_number == 0 )
				{
					virtual_full_log_range->current_lsn = virtual_full_log_range->start_lsn;
				}
			}
			if( virtual_full_log_range->current_lsn != 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "\t\t\t\t\t\t\t\t\t: virtual:  0x%08" PRIx64 " - 0x%08" PRIx64 "\n",
					 virtual_full_log_range->current_lsn,
					 virtual_full_log_range->current_lsn + ( ( sector_index - first_sector ) * io_handle->bytes_per_sector ) - 1 );
				}
#endif
				virtual_full_log_range->current_lsn = region_offset + ( sector_index * io_handle->bytes_per_sector );
			}
			stream_number             = sector_mapping_array_data[ 0 ];
			first_block_sector_number = sector_mapping_array_data[ 1 ];

			first_sector = sector_index;

			if( libcdata_array_append_entry(
			     owner_page->physical_log_ranges_array,
			     &entry_index,
			     (intptr_t *) physical_log_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable append physical log range.",
				 function );

				goto on_error;
			}
			physical_log_range = NULL;

			if( libcdata_array_append_entry(
			     owner_page->virtual_log_ranges_array,
			     &entry_index,
			     (intptr_t *) virtual_log_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable append virtual log range.",
				 function );

				goto on_error;
			}
			virtual_log_range = NULL;

			new_log_range = 0;
		}
		last_block_sector_number = sector_mapping_array_data[ 1 ];

fprintf( stderr, "X: 0x%08" PRIx32 ": 0x%02" PRIx8 ", 0x%02" PRIx8 "\n",
 region_offset + ( sector_index * io_handle->bytes_per_sector ),
 sector_mapping_array_data[ 0 ], sector_mapping_array_data[ 1 ] );

		sector_index++;

		sector_mapping_array_data      += 2;
		sector_mapping_array_data_size -= 2;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: owner page range\t: 0x%08" PRIx64 " - 0x%08" PRIx64 "\n",
		 function,
		 region_offset + ( first_sector * io_handle->bytes_per_sector ),
		 region_offset + ( sector_index * io_handle->bytes_per_sector ) - 1 );

		libcnotify_printf(
		 "\n" );
	}
#endif
	/* TODO determine physical block offset */

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	libcdata_array_resize(
	 owner_page->physical_log_ranges_array,
	 0,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
	 NULL );

	libcdata_array_resize(
	 owner_page->virtual_log_ranges_array,
	 0,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
	 NULL );

	if( physical_log_range != NULL )
	{
		libfsclfs_log_range_free(
		 &physical_log_range,
		 NULL );
	}
	if( virtual_log_range != NULL )
	{
		libfsclfs_log_range_free(
		 &virtual_log_range,
		 NULL );
	}
	return( -1 );
}

/* Reads the owner page by scanning a region
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_owner_page_read_scan_region(
     libfsclfs_owner_page_t *owner_page,
     libfsclfs_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     int number_of_streams,
     uint32_t offset,
     libcerror_error_t **error )
{
	libfsclfs_log_range_t *physical_log_range = NULL;
	libfsclfs_log_range_t *virtual_log_range  = NULL;
	libfsclfs_block_t *block                  = NULL;
	uint8_t *record_data                      = NULL;
	static char *function                     = "libfsclfs_owner_page_read";
	size_t record_data_size                   = 0;
	uint64_t record_virtual_lsn               = 0;
	uint32_t block_offset                     = 0;
	int entry_index                           = 0;

	if( owner_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid owner page.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( libfsclfs_block_initialize(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	block_offset = offset - io_handle->region_owner_page_offset;

	while( block_offset < offset )
	{
/* TODO handle non-block data */
		if( libfsclfs_block_read(
		     block,
		     io_handle,
		     file_io_handle,
		     block_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block at offset: %" PRIu32 ".",
			 function,
			 offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				if( ( error != NULL )
				 && ( *error != NULL ) )
				{
					libcnotify_print_error_backtrace(
					 *error );
				}
			}
#endif
			libcerror_error_free(
			 error );

			block_offset += io_handle->bytes_per_sector;

			continue;
		}
		if( ( block->stream_number == 0 )
		 || ( (int) block->stream_number >= number_of_streams ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid block stream number value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( block->physical_lsn & 0xfffffe00UL ) != block_offset )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_INPUT,
			 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
			 "%s: mismatch in block offset and block physical log sequence number.",
			 function );

			goto on_error;
		}
		if( libfsclfs_block_get_record_data(
		     block,
		     &record_data,
		     &record_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable retrieve record data.",
			 function );

			goto on_error;
		}
		if( record_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing record data.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint64_little_endian(
		 record_data,
		 record_virtual_lsn );

		if( libfsclfs_log_range_initialize(
		     &physical_log_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create physical log range.",
			 function );

			goto on_error;
		}
		if( libfsclfs_log_range_initialize(
		     &virtual_log_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create virtual log range.",
			 function );

			goto on_error;
		}
		physical_log_range->stream_number = 0;
		physical_log_range->start_lsn     = block->physical_lsn;
		physical_log_range->end_lsn       = block->physical_lsn + block->size;

		virtual_log_range->stream_number  = block->stream_number;
		virtual_log_range->start_lsn      = record_virtual_lsn;
		virtual_log_range->end_lsn        = record_virtual_lsn + block->size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: physical log range: 0x%08" PRIx64 " - 0x%08" PRIx64 " stream: %02" PRIu8 " virtual log range: 0x%08" PRIx64 " - 0x%08" PRIx64 "\n\n",
			 function,
			 physical_log_range->start_lsn,
			 physical_log_range->end_lsn,
			 virtual_log_range->stream_number,
			 virtual_log_range->start_lsn,
			 virtual_log_range->end_lsn );
		}
#endif
		if( libcdata_array_append_entry(
		     owner_page->physical_log_ranges_array,
		     &entry_index,
		     (intptr_t *) physical_log_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable append physical log range.",
			 function );

			goto on_error;
		}
		physical_log_range = NULL;

		if( libcdata_array_append_entry(
		     owner_page->virtual_log_ranges_array,
		     &entry_index,
		     (intptr_t *) virtual_log_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable append virtual log range.",
			 function );

			goto on_error;
		}
		virtual_log_range = NULL;

		block_offset += block->size;
	}
	if( libfsclfs_block_free(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free block.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	libcdata_array_resize(
	 owner_page->physical_log_ranges_array,
	 0,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
	 NULL );

	libcdata_array_resize(
	 owner_page->virtual_log_ranges_array,
	 0,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_log_range_free,
	 NULL );

	if( physical_log_range != NULL )
	{
		libfsclfs_log_range_free(
		 &physical_log_range,
		 NULL );
	}
	if( virtual_log_range != NULL )
	{
		libfsclfs_log_range_free(
		 &virtual_log_range,
		 NULL );
	}
	if( block != NULL )
	{
		libfsclfs_block_free(
		 &block,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the physical block offset for a certain virtual block LSN
 * Returns 1 if successful, 0 if no such virtual block LSN or -1 on error
 */
int libfsclfs_owner_page_get_physical_block_offset(
     libfsclfs_owner_page_t *owner_page,
     uint32_t container_logical_number,
     uint32_t virtual_block_offset,
     uint32_t *physical_block_offset,
     libcerror_error_t **error )
{
	libfsclfs_log_range_t *physical_log_range = NULL;
	libfsclfs_log_range_t *virtual_log_range  = NULL;
	static char *function                     = "libfsclfs_owner_page_get_physical_block_offset";
	int log_range_index                       = 0;
	int number_of_physical_log_ranges         = 0;
	int number_of_virtual_log_ranges          = 0;

	if( owner_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid owner page.",
		 function );

		return( -1 );
	}
	if( physical_block_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical block offset.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     owner_page->physical_log_ranges_array,
	     &number_of_physical_log_ranges,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of physical log ranges array entries.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     owner_page->virtual_log_ranges_array,
	     &number_of_virtual_log_ranges,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of virtual log ranges array entries.",
		 function );

		return( -1 );
	}
	if( number_of_physical_log_ranges != number_of_virtual_log_ranges )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: mismatch in number of physical and virtual log ranges.",
		 function );

		return( -1 );
	}
	for( log_range_index = 0;
	     log_range_index < number_of_virtual_log_ranges;
	     log_range_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     owner_page->virtual_log_ranges_array,
		     log_range_index,
		     (intptr_t **) &virtual_log_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve virtual log range: %d.",
			 function,
			 log_range_index );

			return( -1 );
		}
		if( virtual_log_range == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing virtual log range: %d.",
			 function,
			 log_range_index );

			return( -1 );
		}
		if( ( (uint32_t) ( virtual_log_range->start_lsn >> 32 ) == container_logical_number )
		 && ( (uint32_t) ( virtual_log_range->start_lsn & 0xffffffffUL ) == virtual_block_offset ) )
		{
			if( libcdata_array_get_entry_by_index(
			     owner_page->physical_log_ranges_array,
			     log_range_index,
			     (intptr_t **) &physical_log_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve physical log range: %d.",
				 function,
				 log_range_index );

				return( -1 );
			}
			if( physical_log_range == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing physical log range: %d.",
				 function,
				 log_range_index );

				return( -1 );
			}
			*physical_block_offset = (uint32_t) ( physical_log_range->start_lsn & 0xffffffffUL );

			return( 1 );
		}
	}
	return( 0 );
}

