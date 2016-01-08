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

#if !defined( _LIBFSCLFS_OWNER_PAGE_H )
#define _LIBFSCLFS_OWNER_PAGE_H

#include <common.h>
#include <types.h>

#include "libfsclfs_io_handle.h"
#include "libfsclfs_libbfio.h"
#include "libfsclfs_libcdata.h"
#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_owner_page libfsclfs_owner_page_t;

struct libfsclfs_owner_page
{
	/* The physical log ranges array
	 */
	libcdata_array_t *physical_log_ranges_array;

	/* The virtual log ranges array
	 */
	libcdata_array_t *virtual_log_ranges_array;
};

int libfsclfs_owner_page_initialize(
     libfsclfs_owner_page_t **owner_page,
     libcerror_error_t **error );

int libfsclfs_owner_page_free(
     libfsclfs_owner_page_t **owner_page,
     libcerror_error_t **error );

int libfsclfs_owner_page_read(
     libfsclfs_owner_page_t *owner_page,
     libfsclfs_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     int number_of_streams,
     uint32_t offset,
     libcerror_error_t **error );

int libfsclfs_owner_page_read_virtual_log_range_array(
     libfsclfs_owner_page_t *owner_page,
     libcdata_array_t *virtual_log_ranges_array,
     int number_of_streams,
     const uint8_t *virtual_log_range_array_data,
     size_t virtual_log_range_array_data_size,
     libcerror_error_t **error );

int libfsclfs_owner_page_read_sector_mapping_array(
     libfsclfs_owner_page_t *owner_page,
     libfsclfs_io_handle_t *io_handle,
     libcdata_array_t *virtual_log_ranges_array,
     int number_of_streams,
     uint32_t offset,
     const uint8_t *sector_mapping_array_data,
     size_t sector_mapping_array_data_size,
     libcerror_error_t **error );

int libfsclfs_owner_page_read_scan_region(
     libfsclfs_owner_page_t *owner_page,
     libfsclfs_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     int number_of_streams,
     uint32_t offset,
     libcerror_error_t **error );

int libfsclfs_owner_page_get_physical_block_offset(
     libfsclfs_owner_page_t *owner_page,
     uint32_t container_logical_number,
     uint32_t virtual_block_offset,
     uint32_t *physical_block_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

