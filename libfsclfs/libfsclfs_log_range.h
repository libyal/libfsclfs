/*
 * Log range functions
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

#if !defined( _LIBFSCLFS_LOG_RANGE_H )
#define _LIBFSCLFS_LOG_RANGE_H

#include <common.h>
#include <types.h>

#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_log_range libfsclfs_log_range_t;

struct libfsclfs_log_range
{
	/* The stream number
	 */
	uint8_t stream_number;

	/* The start LSN
	 */
	uint64_t start_lsn;

	/* The end LSN
	 */
	uint64_t end_lsn;

	/* The current LSN
	 */
	uint64_t current_lsn;
};

int libfsclfs_log_range_initialize(
     libfsclfs_log_range_t **log_range,
     libcerror_error_t **error );

int libfsclfs_log_range_free(
     libfsclfs_log_range_t **log_range,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_LOG_RANGE_H ) */

