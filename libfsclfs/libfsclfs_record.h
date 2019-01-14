/*
 * Record functions
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSCLFS_INTERNAL_RECORD_H )
#define _LIBFSCLFS_INTERNAL_RECORD_H

#include <common.h>
#include <types.h>

#include "libfsclfs_extern.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_record_value.h"
#include "libfsclfs_stream.h"
#include "libfsclfs_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_internal_record libfsclfs_internal_record_t;

struct libfsclfs_internal_record
{
	/* The internal stream
	 */
	libfsclfs_internal_stream_t *internal_stream;

	/* The record value
	 */
	libfsclfs_record_value_t *record_value;

	/* The file entry flags
	 */
	uint8_t flags;
};

int libfsclfs_record_initialize(
     libfsclfs_record_t **record,
     libfsclfs_internal_stream_t *internal_stream,
     libfsclfs_record_value_t *record_value,
     uint8_t flags,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_record_free(
     libfsclfs_record_t **record,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_record_get_type(
     libfsclfs_record_t *record,
     uint32_t *record_type,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_record_get_flags(
     libfsclfs_record_t *record,
     uint16_t *record_flags,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_record_get_previous_lsn(
     libfsclfs_record_t *record,
     uint64_t *previous_lsn,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_record_get_undo_next_lsn(
     libfsclfs_record_t *record,
     uint64_t *undo_next_lsn,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_record_get_data(
     libfsclfs_record_t *record,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_INTERNAL_RECORD_H ) */

