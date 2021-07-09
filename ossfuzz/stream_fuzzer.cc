/*
 * OSS-Fuzz target for libfsclfs stream type
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libfsclfs.h"

#if !defined( LIBFSCLFS_HAVE_BFIO )

/* Opens a store using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBFSCLFS_EXTERN \
int libfsclfs_store_open_file_io_handle(
     libfsclfs_store_t *store,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libfsclfs_error_t **error );

#endif /* !defined( LIBFSCLFS_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	libbfio_handle_t *file_io_handle = NULL;
	libfsclfs_store_t *store         = NULL;
	libfsclfs_stream_t *stream       = NULL;
	int number_of_streams            = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libfsclfs_store_initialize(
	     &store,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libfsclfs_store_open_file_io_handle(
	     store,
	     file_io_handle,
	     LIBFSCLFS_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libfsclfs;
	}
	if( libfsclfs_store_get_number_of_streams(
	     store,
	     &number_of_streams,
	     NULL ) != 1 )
	{
		goto on_error_libfsclfs;
	}
	if( number_of_streams > 0 )
	{
		if( libfsclfs_store_get_stream_by_index(
		     store,
		     0,
		     &stream,
		     NULL ) != 1 )
		{
			goto on_error_libfsclfs;
		}
		libfsclfs_stream_free(
		 &stream,
		 NULL );
	}
on_error_libfsclfs:
	libfsclfs_store_free(
	 &store,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */

