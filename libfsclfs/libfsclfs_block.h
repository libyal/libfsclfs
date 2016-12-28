/*
 * Block functions
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

#if !defined( _LIBFSCLFS_BLOCK_H )
#define _LIBFSCLFS_BLOCK_H

#include <common.h>
#include <types.h>

#include "libfsclfs_io_handle.h"
#include "libfsclfs_libbfio.h"
#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_block libfsclfs_block_t;

struct libfsclfs_block
{
	/* The data
	 */
	uint8_t *data;

	/* The size
	 */
	uint32_t size;

	/* The stream number
	 */
	uint8_t stream_number;

	/* The physical LSN
	 */
	uint64_t physical_lsn;

	/* The next block LSN
	 */
	uint64_t next_block_lsn;

	/* The record data offset
	 */
	uint32_t record_data_offset;

	/* The sector mapping array offset
	 */
	uint32_t sector_mapping_array_offset;

	/* The virtual log range array offset
	 */
	uint32_t virtual_log_range_array_offset;

	/* The fixup values offset
	 */
	uint32_t fixup_values_offset;
};

int libfsclfs_block_initialize(
     libfsclfs_block_t **block,
     libcerror_error_t **error );

int libfsclfs_block_free(
     libfsclfs_block_t **block,
     libcerror_error_t **error );

int libfsclfs_block_read(
     libfsclfs_block_t *block,
     libfsclfs_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t offset,
     libcerror_error_t **error );

int libfsclfs_block_get_record_data(
     libfsclfs_block_t *block,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

int libfsclfs_block_get_sector_mapping_array_data(
     libfsclfs_block_t *block,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

int libfsclfs_block_get_virtual_log_range_array_data(
     libfsclfs_block_t *block,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_BLOCK_H ) */

