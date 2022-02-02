/*
 * Container functions
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

#if !defined( _LIBFSCLFS_INTERNAL_CONTAINER_H )
#define _LIBFSCLFS_INTERNAL_CONTAINER_H

#include <common.h>
#include <types.h>

#include "libfsclfs_container_descriptor.h"
#include "libfsclfs_extern.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_store.h"
#include "libfsclfs_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_internal_container libfsclfs_internal_container_t;

struct libfsclfs_internal_container
{
	/* The internal store
	 */
	libfsclfs_internal_store_t *internal_store;

	/* The container descriptors
	 */
	libfsclfs_container_descriptor_t *container_descriptor;
};

int libfsclfs_container_initialize(
     libfsclfs_container_t **container,
     libfsclfs_internal_store_t *internal_store,
     libfsclfs_container_descriptor_t *container_descriptor,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_container_free(
     libfsclfs_container_t **container,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_container_open(
     libfsclfs_container_t *container,
     const char *filename,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBFSCLFS_EXTERN \
int libfsclfs_container_open_wide(
     libfsclfs_container_t *container,
     const wchar_t *filename,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBFSCLFS_EXTERN \
int libfsclfs_container_get_size(
     libfsclfs_container_t *container,
     size64_t *size,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_container_get_utf8_name_size(
     libfsclfs_container_t *container,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_container_get_utf8_name(
     libfsclfs_container_t *container,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_container_get_utf16_name_size(
     libfsclfs_container_t *container,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFSCLFS_EXTERN \
int libfsclfs_container_get_utf16_name(
     libfsclfs_container_t *container,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_INTERNAL_CONTAINER_H ) */

