/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSCLFS_IO_HANDLE_H )
#define _LIBFSCLFS_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_io_handle libfsclfs_io_handle_t;

struct libfsclfs_io_handle
{
	/* The number of bytes per sector
	 */
	uint32_t bytes_per_sector;

	/* The region size
	 */
	uint32_t region_size;

	/* The region owner page offset
	 */
	uint32_t region_owner_page_offset;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libfsclfs_io_handle_initialize(
     libfsclfs_io_handle_t **io_handle,
     libcerror_error_t **error );

int libfsclfs_io_handle_free(
     libfsclfs_io_handle_t **io_handle,
     libcerror_error_t **error );

int libfsclfs_io_handle_clear(
     libfsclfs_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_IO_HANDLE_H ) */

