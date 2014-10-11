/*
 * The CLFS record definition
 *
 * Copyright (C) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _FSCLFS_RECORD_H )
#define _FSCLFS_RECORD_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsclfs_container_record_header fsclfs_container_record_header_t;

struct fsclfs_container_record_header
{
	/* The virtual LSN
	 * Consists of 8 bytes
	 */
	uint8_t virtual_lsn[ 8 ];

	/* The undo-next LSN
	 * Consists of 8 bytes
	 */
	uint8_t undo_next_lsn[ 8 ];

	/* The previous LSN
	 * Consists of 8 bytes
	 */
	uint8_t previous_lsn[ 8 ];

	/* The record size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The flags
	 * Consists of 2 bytes
	 */
	uint8_t flags[ 2 ];

	/* The data offset
	 * Consists of 2 bytes
	 */
	uint8_t data_offset[ 2 ];

	/* The record type
	 * Consists of 4 bytes
	 */
	uint8_t record_type[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif

