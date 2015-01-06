/*
 * Block descriptor functions
 *
 * Copyright (C) 2010-2015, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSCLFS_BLOCK_DESCRIPTOR_H )
#define _LIBFSCLFS_BLOCK_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsclfs_block_descriptor libfsclfs_block_descriptor_t;

struct libfsclfs_block_descriptor
{
	/* The offset
	 */
	uint32_t offset;

	/* The size
	 */
	uint32_t size;
};

int libfsclfs_block_descriptor_initialize(
     libfsclfs_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

int libfsclfs_block_descriptor_free(
     libfsclfs_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

