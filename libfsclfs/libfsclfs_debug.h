/*
 * Debug functions
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

#if !defined( _LIBFSCLFS_DEBUG_H )
#define _LIBFSCLFS_DEBUG_H

#include <common.h>
#include <types.h>

#include "libfsclfs_libbfio.h"
#include "libfsclfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_DEBUG_OUTPUT )

void libfsclfs_debug_print_record_type(
      uint32_t record_type );

int libfsclfs_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#endif

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_DEBUG_H ) */

