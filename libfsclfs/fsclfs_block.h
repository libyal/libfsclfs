/*
 * The CLFS block definition
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _FSCLFS_BLOCK_H )
#define _FSCLFS_BLOCK_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsclfs_block_header fsclfs_block_header_t;

struct fsclfs_block_header
{
	/* The signature
	 * Consists of 2 bytes
	 * Contains: 0x15 0x00
	 */
	uint8_t signature[ 2 ];

	/* The fix-up place holder value
	 * Consists of 1 byte
	 */
	uint8_t fixup_place_holder;

	/* The stream number
	 * Consists of 1 byte
	 */
	uint8_t stream_number;

	/* The number of sectors
	 * Consists of 2 bytes
	 */
	uint8_t number_of_sectors[ 2 ];

	/* The copy of the number of sectors
	 * Consists of 2 bytes
	 */
	uint8_t number_of_sectors_copy[ 2 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* The physical LSN
	 * Consists of 8 bytes
	 */
	uint8_t physical_lsn[ 8 ];

	/* The next block LSN
	 * Consists of 8 bytes
	 */
	uint8_t next_block_lsn[ 8 ];

	/* The record data offset
	 * Consists of 4 bytes
	 * The offset is relative to the start of the block
	 */
	uint8_t record_data_offset[ 4 ];

	/* The sector mapping array offset
	 * Consists of 4 bytes
	 * The offset is relative to the start of the block
	 */
	uint8_t sector_mapping_array_offset[ 4 ];

	/* The virtual log range array offset
	 * Consists of 4 bytes
	 * The offset is relative to the start of the block
	 */
	uint8_t virtual_log_range_array_offset[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* Unknown
	 * Consists of 44 bytes
	 */
	uint8_t unknown5[ 44 ];

	/* The fix-up values offset
	 * Consists of 4 bytes
	 * The offset is relative to the start of the block
	 */
	uint8_t fixup_values_offset[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSCLFS_BLOCK_H ) */

