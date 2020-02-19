/*
 * Store functions
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

#if !defined( _LIBFSCLFS_INTERNAL_STORE_H )
#define _LIBFSCLFS_INTERNAL_STORE_H

#include <common.h>
#include <types.h>

#include "libfsclfs_extern.h"
#include "libfsclfs_io_handle.h"
#include "libfsclfs_libbfio.h"
#include "libfsclfs_libcdata.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_owner_page.h"
#include "libfsclfs_record_value.h"
#include "libfsclfs_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_internal_store libfsclfs_internal_store_t;

struct libfsclfs_internal_store
{
	/* The IO handle
	 */
	libfsclfs_io_handle_t *io_handle;

	/* The base log file IO handle
	 */
	libbfio_handle_t *base_log_file_io_handle;

	/* The container file IO pool
	 */
	libbfio_pool_t *container_file_io_pool;

	/* Value to indicate if the base log file IO handle was created inside the library
	 */
	uint8_t base_log_file_io_handle_created_in_library;

	/* Value to indicate if the base log file IO handle was opened inside the library
	 */
	uint8_t base_log_file_io_handle_opened_in_library;

	/* Value to indicate if the container file IO pool was created inside the library
	 */
	uint8_t container_file_io_pool_created_in_library;

	/* The store metadata dump count
	 */
	uint32_t store_metadata_dump_count;

	/* The container descriptors array
	 */
	libcdata_array_t *container_descriptors_array;

	/* The stream descriptors array
	 */
	libcdata_array_t *stream_descriptors_array;

	/* The basename
	 */
	system_character_t *basename;

	/* The basename size
	 */
	size_t basename_size;

	/* The access flags
	 */
	int access_flags;

	/* The maximum number of open handles in the container file IO pool
	 */
	int maximum_number_of_open_handles;
};

LIBFSCLFS_EXTERN \
int libfsclfs_store_initialize(
     libfsclfs_store_t **store,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_store_free(
     libfsclfs_store_t **store,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_store_signal_abort(
     libfsclfs_store_t *store,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_store_open(
     libfsclfs_store_t *store,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBFSCLFS_EXTERN \
int libfsclfs_store_open_wide(
     libfsclfs_store_t *store,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBFSCLFS_EXTERN \
int libfsclfs_store_open_file_io_handle(
     libfsclfs_store_t *store,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_store_open_containers(
     libfsclfs_store_t *store,
     libcerror_error_t **error );

/* TODO
LIBFSCLFS_EXTERN \
int libfsclfs_store_open_containers_file_io_pool(
     libfsclfs_store_t *store,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );
*/

int libfsclfs_store_open_container(
     libfsclfs_internal_store_t *internal_store,
     int container_index,
     const char *filename,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libfsclfs_store_open_container_wide(
     libfsclfs_internal_store_t *internal_store,
     int container_index,
     const wchar_t *filename,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

int libfsclfs_store_open_container_file_io_handle(
     libfsclfs_internal_store_t *internal_store,
     int container_index,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_store_close(
     libfsclfs_store_t *store,
     libcerror_error_t **error );

int libfsclfs_store_open_read(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libfsclfs_store_read_block_descriptors(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *file_io_handle,
     uint32_t offset,
     uint32_t size,
     libcdata_array_t *block_descriptors_array,
     libcerror_error_t **error );

int libfsclfs_store_read_store_metadata(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *file_io_handle,
     uint32_t offset,
     uint32_t size,
     libcerror_error_t **error );

int libfsclfs_store_read_container_owner_page(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *container_file_io_handle,
     libfsclfs_owner_page_t *owner_page,
     uint32_t offset,
     libcerror_error_t **error );

int libfsclfs_block_read_record_values(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *container_file_io_handle,
     uint32_t block_offset,
     libcdata_array_t *record_values_array,
     libcerror_error_t **error );

int libfsclfs_store_get_basename_size(
     libfsclfs_internal_store_t *internal_store,
     size_t *basename_size,
     libcerror_error_t **error );

int libfsclfs_store_get_basename(
     libfsclfs_internal_store_t *internal_store,
     char *basename,
     size_t basename_size,
     libcerror_error_t **error );

int libfsclfs_store_set_basename(
     libfsclfs_internal_store_t *internal_store,
     const char *basename,
     size_t basename_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libfsclfs_store_get_basename_size_wide(
     libfsclfs_internal_store_t *internal_store,
     size_t *basename_size,
     libcerror_error_t **error );

int libfsclfs_store_get_basename_wide(
     libfsclfs_internal_store_t *internal_store,
     wchar_t *basename,
     size_t basename_size,
     libcerror_error_t **error );

int libfsclfs_store_set_basename_wide(
     libfsclfs_internal_store_t *internal_store,
     const wchar_t *basename,
     size_t basename_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBFSCLFS_EXTERN \
int libfsclfs_store_get_number_of_containers(
     libfsclfs_store_t *store,
     int *number_of_containers,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_store_get_container(
     libfsclfs_store_t *store,
     int container_index,
     libfsclfs_container_t **container,
     libcerror_error_t **error );

int libfsclfs_store_get_container_physical_number(
     libfsclfs_internal_store_t *internal_store,
     uint32_t container_logical_number,
     uint32_t *container_physical_number,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_store_get_number_of_streams(
     libfsclfs_store_t *store,
     int *number_of_streams,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_store_get_stream(
     libfsclfs_store_t *store,
     int stream_index,
     libfsclfs_stream_t **stream,
     libcerror_error_t **error );

int libfsclfs_store_get_record_value_by_logical_lsn(
     libfsclfs_internal_store_t *internal_store,
     uint16_t stream_number,
     uint32_t container_logical_number,
     uint32_t block_offset,
     uint16_t record_number,
     libfsclfs_record_value_t **record_value,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_INTERNAL_STORE_H ) */

