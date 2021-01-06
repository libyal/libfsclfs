/*
 * The CLFS base log record definition
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

#if !defined( _FSCLFS_BSAE_LOG_RECORD_H )
#define _FSCLFS_BSAE_LOG_RECORD_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsclfs_base_log_block_descriptors_header fsclfs_base_log_block_descriptors_header_t;

struct fsclfs_base_log_block_descriptors_header
{
	/* The dump count
	 * Consists of 4 bytes
	 */
	uint8_t dump_count[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* Unknown
	 * Consists of 48 bytes
	 */
	uint8_t unknown5[ 48 ];

	/* The number of block descriptors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_block_descriptors[ 4 ];
};

typedef struct fsclfs_base_log_block_descriptor fsclfs_base_log_block_descriptor_t;

struct fsclfs_base_log_block_descriptor
{
	/* Unknown
	 * Consists of 12 bytes
	 */
	uint8_t unknown1[ 12 ];

	/* The block size
	 * Consists of 4 bytes
	 */
	uint8_t block_size[ 4 ];

	/* The block offset
	 * Consists of 4 bytes
	 */
	uint8_t block_offset[ 4 ];

	/* The block number
	 * Consists of 4 bytes
	 */
	uint8_t block_number[ 4 ];
};

typedef struct fsclfs_base_log_store_metadata_header fsclfs_base_log_store_metadata_header_t;

struct fsclfs_base_log_store_metadata_header
{
	/* The dump count
	 * Consists of 4 bytes
	 */
	uint8_t dump_count[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The store identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t store_identifier[ 16 ];

	/* Unknown
	 * Consists of 44 bytes
	 */
	uint8_t unknown3[ 44 ];

	/* Unknown
	 * Consists of 44 bytes
	 */
	uint8_t unknown4[ 44 ];

	/* Unknown
	 * Consists of 44 bytes
	 */
	uint8_t unknown5[ 44 ];

	/* Unknown
	 * Consists of 44 bytes
	 */
	uint8_t unknown6[ 44 ];

	/* Unknown
	 * Consists of 44 bytes
	 */
	uint8_t unknown7[ 44 ];

	/* Unknown
	 * Consists of 44 bytes
	 */
	uint8_t unknown8[ 44 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown11[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown12[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown13[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown14[ 4 ];

	/* Unknown
	 * Consists of 496 bytes
	 */
	uint8_t unknown15[ 496 ];

	/* Unknown
	 * Consists of 4096 bytes
	 */
	uint8_t unknown16[ 4096 ];

	/* The information records data size
	 * Consists of 4 bytes
	 */
	uint8_t information_records_data_size[ 4 ];

	/* Unknown
	 * Consists of 12 bytes
	 */
	uint8_t unknown17[ 12 ];
};

typedef struct fsclfs_base_log_information_record_header fsclfs_base_log_information_record_header_t;

struct fsclfs_base_log_information_record_header
{
	/* The type
	 * Consists of 4 bytes
	 */
	uint8_t type[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];
};

typedef struct fsclfs_base_log_file_information_record_data fsclfs_base_log_file_information_record_data_t;

struct fsclfs_base_log_file_information_record_data
{
	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The name offset
	 * Consists of 4 bytes
	 */
	uint8_t name_offset[ 4 ];

	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown1[ 16 ];

	/* The block name offset
	 * Consists of 4 bytes
	 */
	uint8_t block_name_offset[ 4 ];

	/* The block file attributes offset
	 * Consists of 4 bytes
	 */
	uint8_t block_file_attributes_offset[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown2[ 8 ];
};

typedef struct fsclfs_base_log_stream_attributes_record_data fsclfs_base_log_stream_attributes_record_data_t;

struct fsclfs_base_log_stream_attributes_record_data
{
	/* The stream number
	 * Consists of 2 bytes
	 */
	uint8_t stream_number[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown1[ 2 ];

	/* The flush queue (threshold) size
	 * Consists of 4 bytes
	 */
	uint8_t flush_queue_size[ 4 ];

	/* Unknown
	 * Consists of 40 bytes
	 */
	uint8_t unknown3[ 40 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* The base LSN
	 * Consists of 8 bytes
	 */
	uint8_t base_lsn[ 8 ];

	/* The last flushed LSN
	 * Consists of 8 bytes
	 */
	uint8_t last_flushed_lsn[ 8 ];

	/* The last LSN
	 * Consists of 8 bytes
	 */
	uint8_t last_lsn[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown5[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown6[ 8 ];

	/* Unknown
	 * Consists of 32 bytes
	 */
	uint8_t unknown7[ 32 ];
};

typedef struct fsclfs_base_log_container_attributes_record_data fsclfs_base_log_container_attributes_record_data_t;

struct fsclfs_base_log_container_attributes_record_data
{
	/* The file size
	 * Consists of 4 bytes
	 */
	uint8_t file_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The physical container number
	 * Consists of 4 bytes
	 */
	uint8_t physical_number[ 4 ];

	/* The logical container number
	 * Consists of 4 bytes
	 */
	uint8_t logical_number[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* The number of streams in the container
	 * Consists of 4 bytes
	 */
	uint8_t number_of_streams[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown6[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSCLFS_BSAE_LOG_RECORD_H ) */

