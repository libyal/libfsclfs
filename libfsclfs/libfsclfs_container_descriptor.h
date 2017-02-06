/*
 * Container descriptor functions
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSCLFS_CONTAINER_DESCRIPTOR_H )
#define _LIBFSCLFS_CONTAINER_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_container_descriptor libfsclfs_container_descriptor_t;

struct libfsclfs_container_descriptor
{
	/* The name
	 */
	uint8_t *name;

	/* The name size
	 */
	uint32_t name_size;

	/* The file size
	 */
	uint32_t file_size;

	/* The physical number
	 */
	uint32_t physical_number;

	/* The logical number
	 */
	uint32_t logical_number;
};

int libfsclfs_container_descriptor_initialize(
     libfsclfs_container_descriptor_t **container_descriptor,
     libcerror_error_t **error );

int libfsclfs_container_descriptor_free(
     libfsclfs_container_descriptor_t **container_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_CONTAINER_DESCRIPTOR_H ) */

