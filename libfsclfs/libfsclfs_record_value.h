/*
 * Record value functions
 *
 * Copyright (C) 2010-2022, Joachim Metz <joachim.metz@gmail.com>
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

	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	uint32_t data_size;
};

int libfsclfs_record_value_initialize(
     libfsclfs_record_value_t **record_value,
     libcerror_error_t **error );

int libfsclfs_record_value_free(
     libfsclfs_record_value_t **record_value,
     libcerror_error_t **error );

int libfsclfs_record_value_read_data(
     libfsclfs_record_value_t *record_value,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsclfs_record_value_get_type(
     libfsclfs_record_value_t *record_value,
     uint32_t *record_type,
     libcerror_error_t **error );

int libfsclfs_record_value_get_flags(
     libfsclfs_record_value_t *record_value,
     uint16_t *record_flags,
     libcerror_error_t **error );

int libfsclfs_record_value_get_previous_lsn(
     libfsclfs_record_value_t *record_value,
     uint64_t *previous_lsn,
     libcerror_error_t **error );

int libfsclfs_record_value_get_undo_next_lsn(
     libfsclfs_record_value_t *record_value,
     uint64_t *undo_next_lsn,
     libcerror_error_t **error );

int libfsclfs_record_value_get_data(
     libfsclfs_record_value_t *record_value,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_RECORD_VALUE_H ) */

