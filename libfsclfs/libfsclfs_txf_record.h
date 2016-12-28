/*
 * Record value functions
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

#if !defined( _LIBFSCLFS_RECORD_VALUE_H )
#define _LIBFSCLFS_RECORD_VALUE_H

#include <common.h>
#include <types.h>

#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_record_value libfsclfs_record_value_t;

struct libfsclfs_record_value
{
	/* The virtual LSN
	 */
	uint64_t virtual_lsn;

	/* The undo-next LSN
	 */
	uint64_t undo_next_lsn;

	/* The previous LSN
	 */
	uint64_t previous_lsn;

	/* The size
	 */
	uint32_t size;

	/* The flags
	 */
	uint16_t flags;

	/* The type
	 */
	uint32_t type;
};

int libfsclfs_record_value_initialize(
     libfsclfs_record_value_t **record_value,
     libcerror_error_t **error );

int libfsclfs_record_value_free(
     intptr_t *record_value,
     libcerror_error_t **error );

int libfsclfs_record_value_read(
     libfsclfs_record_value_t *record_value,
     const uint8_t *record_data,
     size_t record_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_RECORD_VALUE_H ) */

