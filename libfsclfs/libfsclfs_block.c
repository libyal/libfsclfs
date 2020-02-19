/*
 * Block functions
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

#include "libfsclfs_block.h"
#include "libfsclfs_definitions.h"
#include "libfsclfs_io_handle.h"
#include "libfsclfs_libbfio.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_libcnotify.h"

#include "fsclfs_block.h"

const uint8_t fsclfs_block_signature[ 2 ] = { 0x15, 0x00 };

/* Creates a block
 * Make sure the value block is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_block_initialize(
     libfsclfs_block_t **block,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_block_initialize";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block value already set.",
		 function );

		return( -1 );
	}
	*block = memory_allocate_structure(
	          libfsclfs_block_t );

	if( *block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block,
	     0,
	     sizeof( libfsclfs_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *block != NULL )
	{
		memory_free(
		 *block );

		*block = NULL;
	}
	return( -1 );
}

/* Frees a block
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_block_free(
     libfsclfs_block_t **block,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_block_free";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		if( ( *block )->data != NULL )
		{
			memory_free(
			 ( *block )->data );
		}
		memory_free(
		 *block );

		*block = NULL;
	}
	return( 1 );
}

/* Reads the block
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_block_read(
     libfsclfs_block_t *block,
     libfsclfs_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t offset,
     libcerror_error_t **error )
{
	static char *function           = "libfsclfs_block_read";
	void *reallocation              = NULL;
	ssize_t read_count              = 0;
	uint32_t block_data_offset      = 0;
	uint32_t block_format_version   = 0;
	uint32_t fixup_offset           = 0;
	uint32_t fixup_value_index      = 0;
	uint32_t fixup_value_offset     = 0;
	uint32_t owner_page_offset      = 0;
	uint32_t read_size              = 0;
	uint32_t region_offset          = 0;
	uint32_t remaining_block_size   = 0;
	uint32_t stored_checksum        = 0;
	uint16_t number_of_sectors      = 0;
	uint16_t number_of_sectors_copy = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit            = 0;
	uint16_t fixup_value            = 0;
	uint16_t value_16bit            = 0;
#endif

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading block at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 offset,
		 offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     (off64_t) offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek block offset: %" PRIu32 ".",
		 function,
		 offset );

		return( -1 );
	}
	if( block->data != NULL )
	{
		memory_free(
		 block->data );
	}
	block->data = (uint8_t *) memory_allocate(
	                           sizeof( fsclfs_block_header_t ) );

	if( block->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              block->data,
	              sizeof( fsclfs_block_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( fsclfs_block_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block header data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: block header data:\n",
		 function );
		libcnotify_print_data(
		 block->data,
		 sizeof( fsclfs_block_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (fsclfs_block_header_t *) block->data )->signature,
	     fsclfs_block_signature,
	     2 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid block signature.",
		 function );

		goto on_error;
	}
	block->stream_number = ( (fsclfs_block_header_t *) block->data )->stream_number;

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->number_of_sectors,
	 number_of_sectors );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->number_of_sectors_copy,
	 number_of_sectors_copy );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->checksum,
	 stored_checksum );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->format_version,
	 block_format_version );

	byte_stream_copy_to_uint64_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->physical_lsn,
	 block->physical_lsn );

	byte_stream_copy_to_uint64_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->next_block_lsn,
	 block->next_block_lsn );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->record_data_offset,
	 block->record_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->sector_mapping_array_offset,
	 block->sector_mapping_array_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->virtual_log_range_array_offset,
	 block->virtual_log_range_array_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_block_header_t *) block->data )->fixup_values_offset,
	 block->fixup_values_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t\t: 0x%02x 0x%02x\n",
		 function,
		 ( (fsclfs_block_header_t *) block->data )->signature[ 0 ],
		 ( (fsclfs_block_header_t *) block->data )->signature[ 1 ] );

		libcnotify_printf(
		 "%s: fixup place holder\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 ( (fsclfs_block_header_t *) block->data )->fixup_place_holder );

		libcnotify_printf(
		 "%s: stream number\t\t\t\t\t: %" PRIu8 "\n",
		 function,
		 block->stream_number );

		libcnotify_printf(
		 "%s: number of sectors\t\t\t\t\t: %" PRIu16 " (size: %" PRIu32 ")\n",
		 function,
		 number_of_sectors,
		 (uint32_t) number_of_sectors * io_handle->bytes_per_sector );

		libcnotify_printf(
		 "%s: number of sectors copy\t\t\t\t: %" PRIu16 " (size: %" PRIu32 ")\n",
		 function,
		 number_of_sectors_copy,
		 (uint32_t) number_of_sectors_copy * io_handle->bytes_per_sector );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_block_header_t *) block->data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: checksum\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 stored_checksum );

		libcnotify_printf(
		 "%s: format version\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 block_format_version );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_block_header_t *) block->data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: physical log sequence number\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 block->physical_lsn );

		libcnotify_printf(
		 "%s: next block log sequence number\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 block->next_block_lsn );

		libcnotify_printf(
		 "%s: record data offset\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 block->record_data_offset );

		libcnotify_printf(
		 "%s: sector mapping array offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 block->sector_mapping_array_offset );

		libcnotify_printf(
		 "%s: virtual log range array offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 block->virtual_log_range_array_offset );

		libcnotify_printf(
		 "%s: unknown4:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_block_header_t *) block->data )->unknown4,
		 8,
		 0 );

		libcnotify_printf(
		 "%s: unknown5:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_block_header_t *) block->data )->unknown5,
		 44,
		 0 );

		libcnotify_printf(
		 "%s: fix-up values offset\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 block->fixup_values_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_block_header_t *) block->data )->unknown6,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown6\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( number_of_sectors != number_of_sectors_copy )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
		 "%s: mismatch between number of sectors and copy.",
		 function );

		goto on_error;
	}
	block->size = (uint32_t) number_of_sectors * io_handle->bytes_per_sector;

	if( block->size < sizeof( fsclfs_block_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block size value out of bounds.",
		 function );

		goto on_error;
	}
#if UINT32_MAX > SSIZE_MAX
	if( (size_t) block->size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block data size value out of bounds.",
		 function );

		goto on_error;
	}
#endif
	if( ( block->fixup_values_offset < sizeof( fsclfs_block_header_t ) )
	 || ( block->fixup_values_offset >= block->size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid fix-up values offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( ( block->record_data_offset != 0 )
	 && ( ( block->record_data_offset < sizeof( fsclfs_block_header_t ) )
	  || ( block->record_data_offset >= block->fixup_values_offset ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid record data offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( ( block->virtual_log_range_array_offset != 0 )
	 && ( ( block->virtual_log_range_array_offset < sizeof( fsclfs_block_header_t ) )
	  || ( block->virtual_log_range_array_offset >= block->fixup_values_offset ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid virtual log range array offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( ( block->sector_mapping_array_offset != 0 )
	 && ( ( block->sector_mapping_array_offset < sizeof( fsclfs_block_header_t ) )
	  || ( block->sector_mapping_array_offset >= block->virtual_log_range_array_offset ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sector mapping array offset value out of bounds.",
		 function );

		goto on_error;
	}
	reallocation = memory_reallocate(
	                block->data,
	                sizeof( uint8_t ) * block->size );

	if( reallocation == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to resize block data.",
		 function );

		goto on_error;
	}
	block->data = (uint8_t *) reallocation;

	remaining_block_size = block->size - sizeof( fsclfs_block_header_t );

	region_offset = ( offset / io_handle->region_size )
	              * io_handle->region_size;

	owner_page_offset = region_offset
	                  + io_handle->region_owner_page_offset;

	block_data_offset = sizeof( fsclfs_block_header_t );

	if( ( offset + remaining_block_size ) <= owner_page_offset )
	{
		read_size = remaining_block_size;
	}
	else
	{
		read_size = owner_page_offset - offset;
	}
	read_count = libbfio_handle_read_buffer(
		      file_io_handle,
		      &( ( block->data )[ block_data_offset ] ),
		      (size_t) read_size,
		      error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block data.",
		 function );

		goto on_error;
	}
	remaining_block_size -= read_size;

	if( remaining_block_size > 0 )
	{
		block_data_offset += read_size;
		region_offset     += io_handle->region_size;

		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     (off64_t) region_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek next region offset: %" PRIu32 ".",
			 function,
			 region_offset );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      &( ( block->data )[ block_data_offset ] ),
			      (size_t) remaining_block_size,
			      error );

		if( read_count != (ssize_t) remaining_block_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block data.",
			 function );

			goto on_error;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( block->record_data_offset > sizeof( fsclfs_block_header_t ) )
		{
			libcnotify_printf(
			 "%s: block header trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( ( block->data )[ sizeof( fsclfs_block_header_t ) ] ),
			 block->record_data_offset,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
		libcnotify_printf(
		 "%s: fix-up values data:\n",
		 function );
		libcnotify_print_data(
		 &( ( block->data )[ block->fixup_values_offset ] ),
		 block->size - block->fixup_values_offset,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( ( ( number_of_sectors * 2 ) > block->size )
	 || ( block->fixup_values_offset >= ( block->size - ( number_of_sectors * 2 ) ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid fixup value offset value out of bounds.",
		 function );

		goto on_error;
	}
	/* Apply the fix-up values
	 */
	fixup_value_offset = block->fixup_values_offset;
	fixup_offset       = io_handle->bytes_per_sector - 2;

	for( fixup_value_index = 0;
	     fixup_value_index < number_of_sectors;
	     fixup_value_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 &( ( block->data )[ fixup_offset ] ),
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 &( ( block->data )[ fixup_value_offset ] ),
			 fixup_value );

			libcnotify_printf(
			 "%s: fixup value: %" PRIu32 "\t\t\t\t\t: 0x%04" PRIx16 " = 0x%04" PRIx16 "\n",
			 function,
			 fixup_value_index,
			 value_16bit,
			 fixup_value );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( ( block->data )[ fixup_offset ] >= 0x80 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_INPUT,
			 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
			 "%s: mismatch in fixup value.",
			 function );

			goto on_error;
		}
		if( fixup_value_index == 0 )
		{
			if( ( ( block->data )[ fixup_offset ] & 0x40 ) == 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_INPUT,
				 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
				 "%s: mismatch in fixup value.",
				 function );

				goto on_error;
			}
			( block->data )[ fixup_offset ] ^= 0x40;
		}
		if( ( fixup_value_index + 1 ) == number_of_sectors )
		{
			if( ( ( block->data )[ fixup_offset ] & 0x20 ) == 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_INPUT,
				 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
				 "%s: mismatch in fixup value.",
				 function );

				goto on_error;
			}
			( block->data )[ fixup_offset ] ^= 0x20;
		}
		if( ( ( block->data )[ fixup_offset ] != 0x00 )
		 && ( ( block->data )[ fixup_offset ] != 0x04 )
		 && ( ( block->data )[ fixup_offset ] != 0x08 )
		 && ( ( block->data )[ fixup_offset ] != 0x10 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_INPUT,
			 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
			 "%s: mismatch in fixup value.",
			 function );

			goto on_error;
		}
		if( ( block->data )[ fixup_offset + 1 ] != ( (fsclfs_block_header_t *) block->data )->fixup_place_holder )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_INPUT,
			 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
			 "%s: mismatch in fixup value.",
			 function );

			goto on_error;
		}
		( block->data )[ fixup_offset ]     = ( block->data )[ fixup_value_offset ];
		( block->data )[ fixup_offset + 1 ] = ( block->data )[ fixup_value_offset + 1 ];

		fixup_value_offset += 2;
		fixup_offset       += io_handle->bytes_per_sector;
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
	if( block->data != NULL )
	{
		memory_free(
		 block->data );

		block->data = NULL;
	}
	return( -1 );
}

/* Retrieves the record data
 * Returns 1 if successful, 0 if the record data offset is empty or -1 on error
 */
int libfsclfs_block_get_record_data(
     libfsclfs_block_t *block,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_block_get_record_data";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
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
	if( block->record_data_offset == 0 )
	{
		return( 0 );
	}
	*data      = &( ( block->data )[ block->record_data_offset ] );
	*data_size = block->fixup_values_offset - block->record_data_offset;

	return( 1 );
}

/* Retrieves the sector mapping array data
 * Returns 1 if successful, 0 if the sector mapping array offset is empty or -1 on error
 */
int libfsclfs_block_get_sector_mapping_array_data(
     libfsclfs_block_t *block,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_block_get_sector_mapping_array_data";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
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
	if( block->sector_mapping_array_offset == 0 )
	{
		return( 0 );
	}
	*data      = &( ( block->data )[ block->sector_mapping_array_offset ] );
	*data_size = block->virtual_log_range_array_offset - block->sector_mapping_array_offset;

	return( 1 );
}

/* Retrieves the virtual log range array data
 * Returns 1 if successful, 0 if the virtual log range array offset is empty or -1 on error
 */
int libfsclfs_block_get_virtual_log_range_array_data(
     libfsclfs_block_t *block,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_block_get_virtual_log_range_array_data";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
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
	if( block->virtual_log_range_array_offset == 0 )
	{
		return( 0 );
	}
	*data      = &( ( block->data )[ block->virtual_log_range_array_offset ] );
	*data_size = block->fixup_values_offset - block->virtual_log_range_array_offset;

	return( 1 );
}

