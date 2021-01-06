/*
 * Stream functions
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSCLFS_INTERNAL_STREAM_H )
#define _LIBFSCLFS_INTERNAL_STREAM_H

#include <common.h>
#include <types.h>

#include "libfsclfs_extern.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_record_value.h"
#include "libfsclfs_store.h"
#include "libfsclfs_stream_descriptor.h"
#include "libfsclfs_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_internal_stream libfsclfs_internal_stream_t;

struct libfsclfs_internal_stream
{
	/* The internal store
	 */
	libfsclfs_internal_store_t *internal_store;

	/* The stream descriptors
	 */
	libfsclfs_stream_descriptor_t *stream_descriptor;
};

int libfsclfs_stream_initialize(
     libfsclfs_stream_t **stream,
     libfsclfs_internal_store_t *internal_store,
     libfsclfs_stream_descriptor_t *stream_descriptor,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_stream_free(
     libfsclfs_stream_t **stream,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_stream_get_utf8_name_size(
     libfsclfs_stream_t *stream,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_stream_get_utf8_name(
     libfsclfs_stream_t *stream,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_stream_get_utf16_name_size(
     libfsclfs_stream_t *stream,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_stream_get_utf16_name(
     libfsclfs_stream_t *stream,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_stream_get_base_lsn(
     libfsclfs_stream_t *stream,
     uint64_t *base_lsn,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_stream_get_last_lsn(
     libfsclfs_stream_t *stream,
     uint64_t *last_lsn,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_stream_get_record_by_lsn(
     libfsclfs_stream_t *stream,
     uint64_t record_lsn,
     libfsclfs_record_t **record,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_INTERNAL_STREAM_H ) */

