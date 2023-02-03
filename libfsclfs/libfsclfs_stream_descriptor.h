/*
 * Stream descriptor functions
 *
 * Copyright (C) 2010-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSCLFS_STREAM_DESCRIPTOR_H )
#define _LIBFSCLFS_STREAM_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_stream_descriptor libfsclfs_stream_descriptor_t;

struct libfsclfs_stream_descriptor
{
	/* The number
	 */
	uint16_t number;

	/* The name
	 */
	uint8_t *name;

	/* The name size
	 */
	uint32_t name_size;

	/* The base lsn
	 */
	uint64_t base_lsn;

	/* The last flushed lsn
	 */
	uint64_t last_flushed_lsn;

	/* The last lsn
	 */
	uint64_t last_lsn;
};

int libfsclfs_stream_descriptor_initialize(
     libfsclfs_stream_descriptor_t **stream_descriptor,
     libcerror_error_t **error );

int libfsclfs_stream_descriptor_free(
     libfsclfs_stream_descriptor_t **stream_descriptor,
     libcerror_error_t **error );

int libfsclfs_stream_descriptor_read_data(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsclfs_stream_descriptor_get_utf8_name_size(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfsclfs_stream_descriptor_get_utf8_name(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libfsclfs_stream_descriptor_get_utf16_name_size(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfsclfs_stream_descriptor_get_utf16_name(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libfsclfs_stream_descriptor_get_base_lsn(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     uint64_t *base_lsn,
     libcerror_error_t **error );

int libfsclfs_stream_descriptor_get_last_lsn(
     libfsclfs_stream_descriptor_t *stream_descriptor,
     uint64_t *last_lsn,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_STREAM_DESCRIPTOR_H ) */

