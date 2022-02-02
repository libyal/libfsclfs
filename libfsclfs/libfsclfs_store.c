/*
 * Store functions
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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfsclfs_block.h"
#include "libfsclfs_block_descriptor.h"
#include "libfsclfs_container.h"
#include "libfsclfs_container_descriptor.h"
#include "libfsclfs_debug.h"
#include "libfsclfs_definitions.h"
#include "libfsclfs_io_handle.h"
#include "libfsclfs_libbfio.h"
#include "libfsclfs_libcdata.h"
#include "libfsclfs_libcerror.h"
#include "libfsclfs_libclocale.h"
#include "libfsclfs_libcnotify.h"
#include "libfsclfs_libfguid.h"
#include "libfsclfs_libuna.h"
#include "libfsclfs_owner_page.h"
#include "libfsclfs_store.h"
#include "libfsclfs_stream.h"
#include "libfsclfs_stream_descriptor.h"
#include "libfsclfs_types.h"

#include "fsclfs_base_log_record.h"

/* Creates a store
 * Make sure the value store is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_initialize(
     libfsclfs_store_t **store,
     libcerror_error_t **error )
{
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_initialize";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	if( *store != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid store value already set.",
		 function );

		return( -1 );
	}
	internal_store = memory_allocate_structure(
	                  libfsclfs_internal_store_t );

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create store.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_store,
	     0,
	     sizeof( libfsclfs_internal_store_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear store.",
		 function );

		memory_free(
		 internal_store );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_store->container_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create container descriptors array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_store->stream_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create stream descriptors array.",
		 function );

		goto on_error;
	}
	if( libfsclfs_io_handle_initialize(
	     &( internal_store->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	internal_store->maximum_number_of_open_handles = LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES;

	*store = (libfsclfs_store_t *) internal_store;

	return( 1 );

on_error:
	if( internal_store != NULL )
	{
		if( internal_store->stream_descriptors_array != NULL )
		{
			libcdata_array_free(
			 &( internal_store->stream_descriptors_array ),
			 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_stream_descriptor_free,
			 NULL );
		}
		if( internal_store->container_descriptors_array != NULL )
		{
			libcdata_array_free(
			 &( internal_store->container_descriptors_array ),
			 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_container_descriptor_free,
			 NULL );
		}
		memory_free(
		 internal_store );
	}
	return( -1 );
}

/* Frees a store
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_free(
     libfsclfs_store_t **store,
     libcerror_error_t **error )
{
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_free";
	int result                                 = 1;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	if( *store != NULL )
	{
		internal_store = (libfsclfs_internal_store_t *) *store;

		if( ( internal_store->base_log_file_io_handle != NULL )
		 || ( internal_store->container_file_io_pool != NULL ) )
		{
			if( libfsclfs_store_close(
			     *store,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close store.",
				 function );

				result = -1;
			}
		}
		*store = NULL;

		if( libcdata_array_free(
		     &( internal_store->container_descriptors_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_container_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free container descriptors array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_store->stream_descriptors_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_stream_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free stream descriptors array.",
			 function );

			result = -1;
		}
		if( internal_store->basename != NULL )
		{
			memory_free(
			 internal_store->basename );
		}
		if( libfsclfs_io_handle_free(
		     &( internal_store->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_store );
	}
	return( result );
}

/* Signals the store to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_signal_abort(
     libfsclfs_store_t *store,
     libcerror_error_t **error )
{
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_signal_abort";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( internal_store->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_store->io_handle->abort = 1;

	return( 1 );
}

/* Opens a store using a base log
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_open(
     libfsclfs_store_t *store,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle           = NULL;
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_open";
	size_t basename_length                     = 0;
	size_t filename_length                     = 0;
	char *basename_end                         = NULL;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBFSCLFS_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBFSCLFS_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBFSCLFS_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	filename_length = narrow_string_length(
	                   filename );

	basename_end = narrow_string_search_character_reverse(
	                filename,
	                LIBFSCLFS_PATH_SEPARATOR,
	                filename_length + 1 );

	if( basename_end != NULL )
	{
		basename_length = (size_t) ( basename_end - filename ) + 1;
	}
	if( basename_length > 0 )
	{
		if( libfsclfs_store_set_basename(
		     internal_store,
		     filename,
		     basename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set basename.",
			 function );

			goto on_error;
		}
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libfsclfs_store_open_file_io_handle(
	     store,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open store: %s.",
		 function,
		 filename );

		goto on_error;
	}
	internal_store->base_log_file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a store using a base log
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_open_wide(
     libfsclfs_store_t *store,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle           = NULL;
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_open_wide";
	size_t basename_length                     = 0;
	size_t filename_length                     = 0;
	wchar_t *basename_end                      = NULL;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBFSCLFS_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBFSCLFS_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBFSCLFS_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	filename_length = wide_string_length(
	                   filename );

/* TODO does this work for UTF-16 ? */
	basename_end = wide_string_search_character_reverse(
	                filename,
	                (wint_t) LIBFSCLFS_PATH_SEPARATOR,
	                filename_length + 1 );

	if( basename_end != NULL )
	{
		basename_length = (size_t) ( basename_end - filename ) + 1;
	}
	if( basename_length > 0 )
	{
		if( libfsclfs_store_set_basename_wide(
		     internal_store,
		     filename,
		     basename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set basename.",
			 function );

			goto on_error;
		}
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

                goto on_error;
	}
#endif
	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( libfsclfs_store_open_file_io_handle(
	     store,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open store: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	internal_store->base_log_file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a store using a Basic File IO (bfio) handle of a base log
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_open_file_io_handle(
     libfsclfs_store_t *store,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_open_file_io_handle";
	int bfio_access_flags                      = 0;
	int file_io_handle_is_open                 = 0;
	int file_io_handle_opened_in_library       = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( internal_store->base_log_file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - base log file IO handle already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBFSCLFS_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBFSCLFS_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBFSCLFS_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBFSCLFS_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to determine if file IO handle is open.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libfsclfs_store_open_read(
	     internal_store,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
	internal_store->base_log_file_io_handle                   = file_io_handle;
	internal_store->base_log_file_io_handle_opened_in_library = file_io_handle_opened_in_library;
	internal_store->access_flags                              = access_flags;

	return( 1 );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 NULL );
	}
	return( -1 );
}

/* Opens the containers
 * This function assumes the container files are in the same location as the base log file
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_open_containers(
     libfsclfs_store_t *store,
     libcerror_error_t **error )
{
	libfsclfs_container_descriptor_t *container_descriptor = NULL;
	libfsclfs_internal_store_t *internal_store             = NULL;
	system_character_t *container_location                 = NULL;
	system_character_t *container_name                     = NULL;
	system_character_t *container_name_start               = NULL;
	static char *function                                  = "libfsclfs_store_open_containers";
	size_t container_location_size                         = 0;
	size_t container_name_size                             = 0;
	int container_descriptor_index                         = 0;
	int number_of_container_descriptors                    = 0;
	int result                                             = 1;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( internal_store->base_log_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing base log file IO handle.",
		 function );

		return( -1 );
 	}
	if( libcdata_array_get_number_of_entries(
	     internal_store->container_descriptors_array,
	     &number_of_container_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of container descriptors.",
		 function );

		return( -1 );
	}
	for( container_descriptor_index = 0;
	     container_descriptor_index < number_of_container_descriptors;
	     container_descriptor_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_store->container_descriptors_array,
		     container_descriptor_index,
		     (intptr_t **) &container_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve container descriptor: %d.",
			 function,
			 container_descriptor_index );

			return( -1 );
		}
		if( container_descriptor == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing container descriptor: %d.",
			 function,
			 container_descriptor_index );

			return( -1 );
		}
/* TODO determine what unknown2 contains
		if( container_descriptor->unknown2 == 0 )
		{
			continue;
		}
*/
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsclfs_container_descriptor_get_utf16_name_size(
		          container_descriptor,
		          &container_name_size,
		          error );
#else
		result = libfsclfs_container_descriptor_get_utf8_name_size(
		          container_descriptor,
		          &container_name_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine container name size.",
			 function );

			return( -1 );
		}
		container_name = system_string_allocate(
		                  container_name_size );

		if( container_name == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create container name.",
			 function );

			return( -1 );
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsclfs_container_descriptor_get_utf16_name(
		          container_descriptor,
		          (libuna_utf16_character_t *) container_name,
		          container_name_size,
		          error );
#else
		result = libfsclfs_container_descriptor_get_utf8_name(
		          container_descriptor,
		          (libuna_utf8_character_t *) container_name,
		          container_name_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy container name.",
			 function );

			memory_free(
			 container_name );

			return( -1 );
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		container_name_start = wide_string_search_character_reverse(
		                        container_name,
		                        (wint_t) '\\',
		                        container_name_size );
#else
		container_name_start = narrow_string_search_character_reverse(
		                        container_name,
		                        (int) '\\',
		                        container_name_size );
#endif

		if( container_name_start != NULL )
		{
			/* Ignore the path separator itself
			 */
			container_name_start++;

/* TODO does this work for UTF-16 ? */
			container_name_size -= (size_t) ( container_name_start - container_name );
		}
		else
		{
			container_name_start = container_name;
		}
		if( internal_store->basename != NULL )
		{
			container_location_size = internal_store->basename_size + container_name_size - 1;

			container_location = system_string_allocate(
			                      container_location_size );

			if( container_location == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create container location.",
				 function );

				memory_free(
				 container_name );

				return( -1 );
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			if( wide_string_copy(
			     container_location,
			     internal_store->basename,
			     internal_store->basename_size - 1 ) == NULL )
#else
			if( narrow_string_copy(
			     container_location,
			     internal_store->basename,
			     internal_store->basename_size - 1 ) == NULL )
#endif
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy basename to container location.",
				 function );

				memory_free(
				 container_location );
				memory_free(
				 container_name );

				return( -1 );
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			if( wide_string_copy(
			     &( container_location[ internal_store->basename_size - 1 ] ),
			     container_name_start,
			     container_name_size - 1 ) == NULL )
#else
			if( narrow_string_copy(
			     &( container_location[ internal_store->basename_size - 1 ] ),
			     container_name_start,
			     container_name_size - 1 ) == NULL )
#endif
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy container name to container location.",
				 function );

				memory_free(
				 container_location );
				memory_free(
				 container_name );

				return( -1 );
			}
			memory_free(
			 container_name );

			container_location[ container_location_size - 1 ] = 0;
		}
		else
		{
			container_location      = container_name_start;
			container_location_size = container_name_size;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: opening container: %" PRIs_SYSTEM "\n",
			 function,
			 container_location );
		}
#endif
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsclfs_store_open_container_wide(
		          internal_store,
		          container_descriptor->physical_number,
		          container_location,
		          error );
#else
		result = libfsclfs_store_open_container(
		          internal_store,
		          container_descriptor->physical_number,
		          container_location,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open container: %" PRIs_SYSTEM ".",
			 function,
			 container_location );
		}
		if( container_location != container_name_start )
		{
			memory_free(
			 container_location );
		}
		else
		{
			memory_free(
			 container_name );
		}
		if( result != 1 )
		{
			break;
		}
	}
	return( result );
}

/* Opens a specific container
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_open_container(
     libfsclfs_internal_store_t *internal_store,
     int container_index,
     const char *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libfsclfs_store_open_container";
	size_t filename_length           = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( internal_store->base_log_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing base log file IO handle.",
		 function );

		return( -1 );
 	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

                goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( libfsclfs_store_open_container_file_io_handle(
	     internal_store,
	     container_index,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open container: %s.",
		 function,
		 filename );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a specific container
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_open_container_wide(
     libfsclfs_internal_store_t *internal_store,
     int container_index,
     const wchar_t *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libfsclfs_container_open_wide";
	size_t filename_length           = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( internal_store->base_log_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing base log file IO handle.",
		 function );

		return( -1 );
 	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

                goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

                goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( libfsclfs_store_open_container_file_io_handle(
	     internal_store,
	     container_index,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open container: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a container using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_open_container_file_io_handle(
     libfsclfs_internal_store_t *internal_store,
     int container_index,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function               = "libfsclfs_store_open_container_file_io_handle";
	int bfio_access_flags               = 0;
	int number_of_container_descriptors = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( internal_store->base_log_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing base log file IO handle.",
		 function );

		return( -1 );
 	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( internal_store->access_flags & LIBFSCLFS_ACCESS_FLAG_READ ) == 0 )
	 && ( ( internal_store->access_flags & LIBFSCLFS_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( internal_store->access_flags & LIBFSCLFS_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( internal_store->container_file_io_pool == NULL )
	{
		if( libcdata_array_get_number_of_entries(
		     internal_store->container_descriptors_array,
		     &number_of_container_descriptors,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of container descriptors.",
			 function );

			return( -1 );
		}
		if( libbfio_pool_initialize(
		     &( internal_store->container_file_io_pool ),
		     number_of_container_descriptors,
		     internal_store->maximum_number_of_open_handles,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create container file IO pool.",
			 function );

			return( -1 );
		}
		internal_store->container_file_io_pool_created_in_library = 1;
	}
	if( ( internal_store->access_flags & LIBFSCLFS_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	if( libbfio_handle_open(
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_IO,
                 LIBCERROR_IO_ERROR_OPEN_FAILED,
                 "%s: unable to open file IO handle.",
                 function );

                return( -1 );
	}
	/* This function currently does not allow the file_io_handle to be set more than once
	 */
	if( libbfio_pool_set_handle(
	     internal_store->container_file_io_pool,
	     container_index,
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set file IO handle: %d in pool.",
		 function,
		 container_index );

		return( -1 );
	}
	return( 1 );
}

/* Closes a store
 * Returns 0 if successful or -1 on error
 */
int libfsclfs_store_close(
     libfsclfs_store_t *store,
     libcerror_error_t **error )
{
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_close";
	int result                                 = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( internal_store->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_store->base_log_file_io_handle_created_in_library != 0 )
		{
			if( libfsclfs_debug_print_read_offsets(
			     internal_store->base_log_file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );
			}
		}
	}
#endif
	if( internal_store->base_log_file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_store->base_log_file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close base log file IO handle.",
			 function );

			result = -1;
		}
		internal_store->base_log_file_io_handle_opened_in_library = 0;
	}
	if( internal_store->base_log_file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_store->base_log_file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free base log file IO handle.",
			 function );

			result = -1;
		}
		internal_store->base_log_file_io_handle_created_in_library = 0;
	}
	internal_store->base_log_file_io_handle = NULL;

	if( internal_store->container_file_io_pool_created_in_library != 0 )
	{
		if( libbfio_pool_close_all(
		     internal_store->container_file_io_pool,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close all container file IO pool handles.",
			 function );

			result = -1;
		}
		if( libbfio_pool_free(
		     &( internal_store->container_file_io_pool ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free container file IO pool.",
			 function );

			result = -1;
		}
		internal_store->container_file_io_pool_created_in_library = 0;
	}
	internal_store->container_file_io_pool    = NULL;
	internal_store->store_metadata_dump_count = 0;

	if( libfsclfs_io_handle_clear(
	     internal_store->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( internal_store->basename != NULL )
	{
		memory_free(
		 internal_store->basename );

		internal_store->basename      = NULL;
		internal_store->basename_size = 0;
	}
	if( libcdata_array_empty(
	     internal_store->container_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_container_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty container descriptors array.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_store->stream_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_stream_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty stream descriptors array.",
		 function );

		result = -1;
	}
	return( result );
}

/* Opens a store for reading
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_open_read(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libcdata_array_t *block_descriptors_array      = NULL;
	libfsclfs_block_descriptor_t *block_descriptor = NULL;
	static char *function                          = "libfsclfs_store_open_read";
	uint32_t block_descriptors_block_size          = 0;
	uint32_t store_metadata_block_size             = 0;
	int block_descriptor_index                     = 0;
	int number_of_block_descriptors                = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( internal_store->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing IO handle.",
		 function );

		return( -1 );
	}
	block_descriptors_block_size = internal_store->io_handle->bytes_per_sector * 0x02;
	store_metadata_block_size    = internal_store->io_handle->bytes_per_sector * 0x3d;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading block descriptors\n" );
	}
#endif
	if( libcdata_array_initialize(
	     &block_descriptors_array,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block descriptors array.",
		 function );

		goto on_error;
	}
	if( libfsclfs_store_read_block_descriptors(
	     internal_store,
	     file_io_handle,
	     0,
	     block_descriptors_block_size,
	     block_descriptors_array,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block descriptors.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     block_descriptors_array,
	     &number_of_block_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of block descriptors.",
		 function );

		goto on_error;
	}
	internal_store->store_metadata_dump_count = 0;

	for( block_descriptor_index = 0;
	     block_descriptor_index < number_of_block_descriptors;
	     block_descriptor_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     block_descriptors_array,
		     block_descriptor_index,
		     (intptr_t **) &block_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve block descriptor: %d from array.",
			 function,
			 block_descriptor_index );

			goto on_error;
		}
		if( block_descriptor == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing block descriptor: %d.",
			 function,
			 block_descriptor_index );

			goto on_error;
		}
		if( block_descriptor->size == store_metadata_block_size )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "Reading store metadata\n" );
			}
#endif
			if( libfsclfs_store_read_store_metadata(
			     internal_store,
			     file_io_handle,
			     block_descriptor->offset,
			     block_descriptor->size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read store metadata.",
				 function );

				goto on_error;
			}
		}
	}
	if( libcdata_array_free(
	     &block_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_block_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free block descriptors array.",
		 function );

		return( -1 );
	}
	return( 1 );

on_error:
	if( block_descriptors_array != NULL )
	{
		libcdata_array_free(
		 &block_descriptors_array,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_block_descriptor_free,
		 NULL );
	}
	return( -1 );
}

/* Reads the block descriptors
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_read_block_descriptors(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *file_io_handle,
     uint32_t block_offset,
     uint32_t block_size,
     libcdata_array_t *block_descriptors_array,
     libcerror_error_t **error )
{
	libfsclfs_block_t *block                       = NULL;
	libfsclfs_block_descriptor_t *block_descriptor = NULL;
	uint8_t *record_data                           = NULL;
	static char *function                          = "libfsclfs_store_read_block_descriptors";
	size_t record_data_size                        = 0;
	uint32_t block_descriptor_index                = 0;
	uint32_t block_descriptors_data_size           = 0;
	uint32_t number_of_block_descriptors           = 0;
	uint32_t unknown2                              = 0;
	uint32_t unknown3                              = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                           = 0;
	uint64_t value_64bit                           = 0;
#endif

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( libfsclfs_block_initialize(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	if( libfsclfs_block_read(
	     block,
	     internal_store->io_handle,
	     file_io_handle,
	     block_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block at offset: %" PRIu32 ".",
		 function,
		 block_offset );

		goto on_error;
	}
	if( block->size != block_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_INPUT,
		 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
		 "%s: mismatch in block size value.",
		 function );

		goto on_error;
	}
	if( libfsclfs_block_get_record_data(
	     block,
	     &record_data,
	     &record_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable retrieve record data.",
		 function );

		goto on_error;
	}
	if( record_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing record data.",
		 function );

		goto on_error;
	}
	if( record_data_size < sizeof( fsclfs_base_log_block_descriptors_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid record data size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: block descriptors header data:\n",
		 function );
		libcnotify_print_data(
		 record_data,
		 sizeof( fsclfs_base_log_block_descriptors_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_block_descriptors_header_t *) record_data )->unknown2,
	 unknown2 );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_block_descriptors_header_t *) record_data )->unknown3,
	 unknown3 );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_block_descriptors_header_t *) record_data )->number_of_block_descriptors,
	 number_of_block_descriptors );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_block_descriptors_header_t *) record_data )->dump_count,
		 value_32bit );
		libcnotify_printf(
		 "%s: dump count\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_block_descriptors_header_t *) record_data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown2\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 unknown2 );

		libcnotify_printf(
		 "%s: unknown3\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 unknown3 );

		byte_stream_copy_to_uint64_little_endian(
		 ( (fsclfs_base_log_block_descriptors_header_t *) record_data )->unknown4,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: unknown5:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_block_descriptors_header_t *) record_data )->unknown5,
		 48,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		libcnotify_printf(
		 "%s: number of block descriptors\t: %" PRIu32 "\n",
		 function,
		 number_of_block_descriptors );

		libcnotify_printf(
		 "\n" );
	}
#endif
	record_data_size -= sizeof( fsclfs_base_log_block_descriptors_header_t );

	if( unknown2 != 0x00005f1c )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_INPUT,
		 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
		 "%s: mismatch in unknown2 value.",
		 function );

		goto on_error;
	}
	if( unknown3 != 0xc1f5c1f5 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_INPUT,
		 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
		 "%s: mismatch in unknown3 value.",
		 function );

		goto on_error;
	}
	if( ( number_of_block_descriptors < 6 )
	 || ( number_of_block_descriptors >= 32 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of block descriptors value out of bounds.",
		 function );

		goto on_error;
	}
	block_descriptors_data_size = number_of_block_descriptors * sizeof( fsclfs_base_log_block_descriptor_t );

	if( block_descriptors_data_size > record_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block descriptors data size value out of bounds.",
		 function );

		goto on_error;
	}
	record_data += sizeof( fsclfs_base_log_block_descriptors_header_t );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: block descriptors data:\n",
		 function );
		libcnotify_print_data(
		 record_data,
		 block_descriptors_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libcdata_array_resize(
	     block_descriptors_array,
	     (int) number_of_block_descriptors,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_block_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable resize block descriptors array.",
		 function );

		goto on_error;
	}
	for( block_descriptor_index = 0;
	     block_descriptor_index < number_of_block_descriptors;
	     block_descriptor_index++ )
	{
		if( libfsclfs_block_descriptor_initialize(
		     &block_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create block descriptor.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading block descriptor %02" PRIu32 ".\n",
			 function,
			 block_descriptor_index );
		}
#endif
/* TODO replace direct pass of sizeof() */
		if( libfsclfs_block_descriptor_read_data(
		     block_descriptor,
		     record_data,
		     sizeof( fsclfs_base_log_block_descriptor_t ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block descriptor.",
			 function );

			goto on_error;
		}
		/* Note that this function also check if the block_number is within bounds
		 */
		if( libcdata_array_set_entry_by_index(
		     block_descriptors_array,
		     (int) block_descriptor->block_number,
		     (intptr_t *) block_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set block descriptor: %" PRIu32 " in array.",
			 function,
			 block_descriptor->block_number );

			goto on_error;
		}
		block_descriptor = NULL;

		record_data += sizeof( fsclfs_base_log_block_descriptor_t );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	if( libfsclfs_block_free(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free block.",
		 function );

		return( -1 );
	}
	return( 1 );

on_error:
	if( block_descriptor != NULL )
	{
		libfsclfs_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	if( block != NULL )
	{
		libfsclfs_block_free(
		 &block,
		 NULL );
	}
	return( -1 );
}

/* Reads the store metadata
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_read_store_metadata(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *file_io_handle,
     uint32_t block_offset,
     uint32_t block_size,
     libcerror_error_t **error )
{
	libfsclfs_block_t *block                               = NULL;
	libfsclfs_container_descriptor_t *container_descriptor = NULL;
	libfsclfs_stream_descriptor_t *stream_descriptor       = NULL;
	uint8_t *record_data                                   = NULL;
	uint8_t *name_data                                     = NULL;
	static char *function                                  = "libfsclfs_store_read_store_metadata";
	size_t record_data_offset                              = 0;
	size_t record_data_size                                = 0;
	uint32_t alignment_padding_size                        = 0;
	uint32_t block_file_attributes_offset                  = 0;
	uint32_t block_name_offset                             = 0;
	uint32_t dump_count                                    = 0;
	uint32_t information_record_size                       = 0;
	uint32_t information_record_type                       = 0;
	uint32_t information_records_data_size                 = 0;
	uint32_t name_data_size                                = 0;
	int entry_index                                        = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t guid_string[ 48 ];

	system_character_t *value_string                       = NULL;
	libfguid_identifier_t *guid                            = NULL;
	size_t value_string_size                               = 0;
	uint32_t value_32bit                                   = 0;
	int result                                             = 0;
#endif

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( libfsclfs_block_initialize(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	if( libfsclfs_block_read(
	     block,
	     internal_store->io_handle,
	     file_io_handle,
	     block_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block at offset: %" PRIu32 ".",
		 function,
		 block_offset );

		goto on_error;
	}
	if( block->size != block_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_INPUT,
		 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
		 "%s: mismatch in block size value.",
		 function );

		goto on_error;
	}
	if( libfsclfs_block_get_record_data(
	     block,
	     &record_data,
	     &record_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable retrieve record data.",
		 function );

		goto on_error;
	}
	if( record_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing record data.",
		 function );

		goto on_error;
	}
	if( record_data_size < sizeof( fsclfs_base_log_store_metadata_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid record data size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: store metadata header data:\n",
		 function );
		libcnotify_print_data(
		 record_data,
		 sizeof( fsclfs_base_log_store_metadata_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->dump_count,
	 dump_count );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->information_records_data_size,
	 information_records_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: dump count\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 dump_count );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     ( (fsclfs_base_log_store_metadata_header_t *) record_data )->store_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			libfguid_identifier_free(
			 &guid,
			 NULL );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			libfguid_identifier_free(
			 &guid,
			 NULL );

			goto on_error;
		}
		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: store identifier\t\t\t: %" PRIs_SYSTEM "\n",
		 function,
		 guid_string );

		libcnotify_printf(
		 "%s: unknown3:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown3,
		 44,
		 0 );

		libcnotify_printf(
		 "%s: unknown4:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown4,
		 44,
		 0 );

		libcnotify_printf(
		 "%s: unknown5:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown5,
		 44,
		 0 );

		libcnotify_printf(
		 "%s: unknown6:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown6,
		 44,
		 0 );

		libcnotify_printf(
		 "%s: unknown7:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown7,
		 44,
		 0 );

		libcnotify_printf(
		 "%s: unknown8:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown8,
		 44,
		 0 );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown9,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown9\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown10,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown10\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown11,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown11\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown12,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown12\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown13,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown13\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown14,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown14\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown15:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown15,
		 496,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		libcnotify_printf(
		 "%s: unknown16:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown16,
		 4096,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		libcnotify_printf(
		 "%s: information records data size\t: %" PRIu32 "\n",
		 function,
		 information_records_data_size );

		libcnotify_printf(
		 "%s: unknown17:\n",
		 function );
		libcnotify_print_data(
		 ( (fsclfs_base_log_store_metadata_header_t *) record_data )->unknown17,
		 12,
		 0 );
	}
#endif
	record_data_offset += sizeof( fsclfs_base_log_store_metadata_header_t );

	if( ( record_data_offset + (size_t) information_records_data_size ) > record_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid information records data size value out of bounds.",
		 function );

		goto on_error;
	}
	record_data += sizeof( fsclfs_base_log_store_metadata_header_t );

	if( dump_count > internal_store->store_metadata_dump_count )
	{
		if( libcdata_array_resize(
		     internal_store->container_descriptors_array,
		     0,
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_container_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
			 "%s: unable resize container descriptors array.",
			 function );

			goto on_error;
		}
		if( libcdata_array_resize(
		     internal_store->stream_descriptors_array,
		     0,
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_stream_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
			 "%s: unable resize stream descriptors array.",
			 function );

			goto on_error;
		}
	}
	while( information_records_data_size > 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_information_record_header_t *) record_data )->type,
		 information_record_type );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsclfs_base_log_information_record_header_t *) record_data )->size,
		 information_record_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: type\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 information_record_type );

			libcnotify_printf(
			 "%s: size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 information_record_size );
		}
#endif
		if( ( information_record_size < 8 )
		 || ( ( record_data_offset + information_record_size ) > record_data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid information records size value out of bounds.",
			 function );

			goto on_error;
		}
		record_data                   += 8;
		record_data_offset            += 8;
		information_records_data_size -= 8;
		information_record_size       -= 8;

		if( ( information_record_type != 0xc1fdf006 )
		 && ( information_record_type != 0xc1fdf007 )
		 && ( information_record_type != 0xc1fdf008 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported information record type: 0x%08" PRIx32 ".",
			 function,
			 information_record_type );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: information record data:\n",
			 function );
			libcnotify_print_data(
			 record_data,
			 information_record_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		if( information_record_type == 0xc1fdf006 )
		{
			if( information_record_size != sizeof( fsclfs_base_log_file_information_record_data_t ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported information record size: %" PRIu32 " for type: 0x%08" PRIx32 ".",
				 function,
				 information_record_size,
				 information_record_type );

				goto on_error;
			}
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsclfs_base_log_file_information_record_data_t *) record_data )->block_name_offset,
			 block_name_offset );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsclfs_base_log_file_information_record_data_t *) record_data )->block_file_attributes_offset,
			 block_file_attributes_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (fsclfs_base_log_file_information_record_data_t *) record_data )->checksum,
				 value_32bit );
				libcnotify_printf(
				 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (fsclfs_base_log_file_information_record_data_t *) record_data )->name_offset,
				 value_32bit );
				libcnotify_printf(
				 "%s: name offset\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );

				libcnotify_printf(
				 "%s: unknown1:\n",
				 function );
				libcnotify_print_data(
				 ( (fsclfs_base_log_file_information_record_data_t *) record_data )->unknown1,
				 16,
				 0 );

				libcnotify_printf(
				 "%s: block name offset\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 block_name_offset );

				libcnotify_printf(
				 "%s: block file attributes offset\t: 0x%08" PRIx32 "\n",
				 function,
				 block_file_attributes_offset );

				libcnotify_printf(
				 "%s: unknown2:\n",
				 function );
				libcnotify_print_data(
				 ( (fsclfs_base_log_file_information_record_data_t *) record_data )->unknown2,
				 8,
				 0 );
			}
#endif
			record_data                   += sizeof( fsclfs_base_log_file_information_record_data_t );
			record_data_offset            += sizeof( fsclfs_base_log_file_information_record_data_t );
			information_records_data_size -= sizeof( fsclfs_base_log_file_information_record_data_t );
			information_record_size       -= sizeof( fsclfs_base_log_file_information_record_data_t );
		}
		else if( information_record_type == 0xc1fdf007 )
		{
			if( information_record_size != sizeof( fsclfs_base_log_stream_attributes_record_data_t ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported information record size: %" PRIu32 " for type: 0x%08" PRIx32 ".",
				 function,
				 information_record_size,
				 information_record_type );

				goto on_error;
			}
			if( libfsclfs_stream_descriptor_initialize(
			     &stream_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create stream descriptor.",
				 function );

				goto on_error;
			}
/* TODO replace direct pass of sizeof() */
			if( libfsclfs_stream_descriptor_read_data(
			     stream_descriptor,
			     record_data,
			     sizeof( fsclfs_base_log_stream_attributes_record_data_t ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read stream descriptor.",
				 function );

				goto on_error;
			}
			record_data                   += sizeof( fsclfs_base_log_stream_attributes_record_data_t );
			record_data_offset            += sizeof( fsclfs_base_log_stream_attributes_record_data_t );
			information_records_data_size -= sizeof( fsclfs_base_log_stream_attributes_record_data_t );
			information_record_size       -= sizeof( fsclfs_base_log_stream_attributes_record_data_t );

			block_file_attributes_offset = 0;
		}
		else if( information_record_type == 0xc1fdf008 )
		{
			if( information_record_size != sizeof( fsclfs_base_log_container_attributes_record_data_t ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported information record size: %" PRIu32 " for type: 0x%08" PRIx32 ".",
				 function,
				 information_record_size,
				 information_record_type );

				goto on_error;
			}
			if( libfsclfs_container_descriptor_initialize(
			     &container_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create container descriptor.",
				 function );

				goto on_error;
			}
/* TODO replace direct pass of sizeof() */
			if( libfsclfs_container_descriptor_read_data(
			     container_descriptor,
			     record_data,
			     sizeof( fsclfs_base_log_container_attributes_record_data_t ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read container descriptor.",
				 function );

				goto on_error;
			}
			record_data                   += sizeof( fsclfs_base_log_container_attributes_record_data_t );
			record_data_offset            += sizeof( fsclfs_base_log_container_attributes_record_data_t );
			information_records_data_size -= sizeof( fsclfs_base_log_container_attributes_record_data_t );
			information_record_size       -= sizeof( fsclfs_base_log_container_attributes_record_data_t );

			block_file_attributes_offset = 0;
		}
		if( block_name_offset == record_data_offset )
		{
			if( information_record_type == 0xc1fdf007 )
			{
				if( stream_descriptor == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing stream descriptor.",
					 function );

					goto on_error;
				}
			}
			else if( information_record_type == 0xc1fdf008 )
			{
				if( container_descriptor == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing container descriptor.",
					 function );

					goto on_error;
				}
			}
			else
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported information record type: 0x%08" PRIx32 ".",
				 function,
				 information_record_type );

				goto on_error;
			}
			for( name_data_size = 0;
			     ( name_data_size + 1 ) < information_records_data_size;
			     name_data_size += 2 )
			{
				if( ( record_data[ name_data_size ] == 0 )
				 && ( record_data[ name_data_size + 1 ] == 0 ) )
				{
					break;
				}
			}
			name_data_size += 2;

			name_data = (uint8_t *) memory_allocate(
			                         sizeof( uint8_t ) * name_data_size );

			if( name_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create name string.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     name_data,
			     record_data,
			     name_data_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy name string.",
				 function );

				memory_free(
				 name_data );

				goto on_error;
			}
			if( information_record_type == 0xc1fdf007 )
			{
				stream_descriptor->name      = name_data;
				stream_descriptor->name_size = name_data_size;
			}
			else if( information_record_type == 0xc1fdf008 )
			{
				container_descriptor->name      = name_data;
				container_descriptor->name_size = name_data_size;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: file name size\t\t\t: %" PRIu32 "\n",
				 function,
				 name_data_size );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libuna_utf16_string_size_from_utf16_stream(
					  name_data,
					  name_data_size,
					  LIBUNA_ENDIAN_LITTLE,
					  &value_string_size,
					  error );
#else
				result = libuna_utf8_string_size_from_utf16_stream(
					  name_data,
					  name_data_size,
					  LIBUNA_ENDIAN_LITTLE,
					  &value_string_size,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to determine size of name string.",
					 function );

					goto on_error;
				}
				value_string = system_string_allocate(
				                value_string_size );

				if( value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create name string.",
					 function );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libuna_utf16_string_copy_from_utf16_stream(
					  (libuna_utf16_character_t *) value_string,
					  value_string_size,
					  name_data,
					  name_data_size,
					  LIBUNA_ENDIAN_LITTLE,
					  error );
#else
				result = libuna_utf8_string_copy_from_utf16_stream(
					  (libuna_utf8_character_t *) value_string,
					  value_string_size,
					  name_data,
					  name_data_size,
					  LIBUNA_ENDIAN_LITTLE,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set name string.",
					 function );

					memory_free(
					 value_string );

					goto on_error;
				}
				libcnotify_printf(
				 "%s: name\t\t\t\t: %" PRIs_SYSTEM "\n",
				 function,
				 value_string );

				memory_free(
				 value_string );

				libcnotify_printf(
				 "\n" );
			}
#endif
			record_data                   += name_data_size;
			record_data_offset            += name_data_size;
			information_records_data_size -= name_data_size;

			if( ( record_data_offset % 8 ) != 0 )
			{
				alignment_padding_size = 8 - ( record_data_offset % 8 );

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: alignment padding:\n",
					 function );
					libcnotify_print_data(
					 record_data,
					 alignment_padding_size,
					 0 );
				}
#endif
				record_data                   += alignment_padding_size;
				record_data_offset            += alignment_padding_size;
				information_records_data_size -= alignment_padding_size;
			}
			block_name_offset = 0;
		}
		if( dump_count > internal_store->store_metadata_dump_count )
		{
			if( information_record_type == 0xc1fdf007 )
			{
				if( libcdata_array_append_entry(
				     internal_store->stream_descriptors_array,
				     &entry_index,
				     (intptr_t *) stream_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable append stream descriptor.",
					 function );

					goto on_error;
				}
				stream_descriptor = NULL;
			}
			else if( information_record_type == 0xc1fdf008 )
			{
				if( libcdata_array_append_entry(
				     internal_store->container_descriptors_array,
				     &entry_index,
				     (intptr_t *) container_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable append container descriptor.",
					 function );

					goto on_error;
				}
				container_descriptor = NULL;
			}
		}
		else
		{
			if( information_record_type == 0xc1fdf007 )
			{
				if( libfsclfs_stream_descriptor_free(
				     &stream_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable free stream descriptor.",
					 function );

					goto on_error;
				}
			}
			else if( information_record_type == 0xc1fdf008 )
			{
				if( libfsclfs_container_descriptor_free(
				     &container_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable free container descriptor.",
					 function );

					goto on_error;
				}
			}
		}
	}
	if( libfsclfs_block_free(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free block.",
		 function );

		return( -1 );
	}
	internal_store->store_metadata_dump_count = dump_count;

	return( 1 );

on_error:
	libcdata_array_resize(
	 internal_store->container_descriptors_array,
	 0,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_container_descriptor_free,
	 NULL );

	libcdata_array_resize(
	 internal_store->stream_descriptors_array,
	 0,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_stream_descriptor_free,
	 NULL );

	if( container_descriptor != NULL )
	{
		libfsclfs_container_descriptor_free(
		 &container_descriptor,
		 NULL );
	}
	if( stream_descriptor != NULL )
	{
		libfsclfs_stream_descriptor_free(
		 &stream_descriptor,
		 NULL );
	}
	if( block != NULL )
	{
		libfsclfs_block_free(
		 &block,
		 NULL );
	}
	return( -1 );
}


/* Reads the container owner page
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_read_container_owner_page(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *container_file_io_handle,
     libfsclfs_owner_page_t *owner_page,
     uint32_t offset,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_store_read_container_owner_page";
	int number_of_streams = 0;
	int result            = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_store->stream_descriptors_array,
	     &number_of_streams,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of stream descriptors.",
		 function );

		return( -1 );
	}
#ifdef TODO
	/* TODO determine when owner page should be valid */
	result = libfsclfs_owner_page_read(
	          owner_page,
	          internal_store->io_handle,
	          container_file_io_handle,
	          number_of_streams,
	          (off64_t) offset,
	          error );
#else
	result = libfsclfs_owner_page_read_scan_region(
	          owner_page,
	          internal_store->io_handle,
	          container_file_io_handle,
	          number_of_streams,
	          (off64_t) offset,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read owner page at offset: %" PRIu32 ".",
		 function,
		 offset );

		return( -1 );
	}
	return( 1 );
}

/* Reads the container block record values
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_block_read_record_values(
     libfsclfs_internal_store_t *internal_store,
     libbfio_handle_t *container_file_io_handle,
     uint32_t block_offset,
     libcdata_array_t *record_values_array,
     libcerror_error_t **error )
{
	libfsclfs_block_t *block               = NULL;
	libfsclfs_record_value_t *record_value = NULL;
	uint8_t *record_data                   = NULL;
	static char *function                  = "libfsclfs_block_read_record_values";
	size_t alignment_padding_size          = 0;
	size_t record_data_offset              = 0;
	size_t record_data_size                = 0;
        uint32_t container_logical_number      = 0;
	uint32_t record_type                   = 0;
	uint16_t record_number                 = 0;
	int entry_index                        = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( libfsclfs_block_initialize(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	do
	{
		if( libfsclfs_block_read(
		     block,
		     internal_store->io_handle,
		     container_file_io_handle,
		     block_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block at offset: %" PRIu32 ".",
			 function,
			 block_offset );

			goto on_error;
		}
		if( libfsclfs_block_get_record_data(
		     block,
		     &record_data,
		     &record_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable retrieve record data.",
			 function );

			goto on_error;
		}
		if( record_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing record data.",
			 function );

			goto on_error;
		}
		record_data_offset = block->record_data_offset;

		while( record_data_size > 0 )
		{
			if( libfsclfs_record_value_initialize(
			     &record_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create record value.",
				 function );

				goto on_error;
			}
			if( libfsclfs_record_value_read_data(
			     record_value,
			     record_data,
			     record_data_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read record.",
				 function );

				goto on_error;
			}
			record_type         = record_value->type;
			record_data        += record_value->size;
			record_data_size   -= record_value->size;
			record_data_offset += record_value->size;

			if( libcdata_array_append_entry(
			     record_values_array,
			     &entry_index,
			     (intptr_t *) record_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable append block record value.",
				 function );

				goto on_error;
			}
			record_value = NULL;

			if( ( record_data_offset % 8 ) != 0 )
			{
				alignment_padding_size = 8 - ( record_data_offset % 8 );

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: alignment padding:\n",
					 function );
					libcnotify_print_data(
					 record_data,
					 alignment_padding_size,
					 0 );
				}
#endif
				record_data        += alignment_padding_size;
				record_data_size   -= alignment_padding_size;
				record_data_offset += alignment_padding_size;
			}
			if( ( record_type & RECORD_TYPE_FLAG_IS_LAST ) != 0 )
			{
				break;
			}
		}
		if( ( record_type & RECORD_TYPE_FLAG_IS_LAST ) != 0 )
		{
			break;
		}
		block_offset             = (uint32_t) ( block->next_block_lsn & 0xfffffe00UL );
	        container_logical_number = (uint32_t) ( block->next_block_lsn >> 32 );
		record_number            = (uint16_t) ( block->next_block_lsn & 0x01ff );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: LSN: 0x%08" PRIx32 ", container logical number: %" PRIu32 ", record number: %" PRIu16 ", block offset: 0x%08" PRIx32 ", \n",
			 function,
			 block->next_block_lsn,
			 container_logical_number,
			 record_number,
			 block_offset );
		}
#endif
/* TODO what about block outside the container */
		if( block->next_block_lsn != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid next block LSN value out of bounds.",
			 function );

			goto on_error;
		}
	}
	while( block_offset != 0 );

	if( libfsclfs_block_free(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free block.",
		 function );

		return( -1 );
	}
	return( 1 );

on_error:
	libcdata_array_resize(
	 record_values_array,
	 0,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_record_value_free,
	 NULL );

	if( record_value != NULL )
	{
		libfsclfs_record_value_free(
		 &record_value,
		 NULL );
	}
	if( block != NULL )
	{
		libfsclfs_block_free(
		 &block,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the size of the basename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libfsclfs_store_get_basename_size(
     libfsclfs_internal_store_t *internal_store,
     size_t *basename_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_store_get_basename_size";

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( basename_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename size.",
		 function );

		return( -1 );
	}
	if( internal_store->basename == NULL )
	{
		return( 0 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#else
	*basename_size = internal_store->basename_size;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

/* Retrieves the basename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libfsclfs_store_get_basename(
     libfsclfs_internal_store_t *internal_store,
     char *basename,
     size_t basename_size,
     libcerror_error_t **error )
{
	static char *function       = "libfsclfs_store_get_basename";
	size_t narrow_basename_size = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                  = 0;
#endif

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( internal_store->basename == NULL )
	{
		return( 0 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          &narrow_basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          &narrow_basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          &narrow_basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          &narrow_basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow basename size.",
		 function );

		return( -1 );
	}
#else
	narrow_basename_size = internal_store->basename_size;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( basename_size < narrow_basename_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: basename too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) basename,
		          basename_size,
		          (libuna_utf32_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) basename,
		          basename_size,
		          (libuna_utf16_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) basename,
		          basename_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) basename,
		          basename_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set basename.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     basename,
	     internal_store->basename,
	     internal_store->basename_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set basename.",
		 function );

		return( -1 );
	}
	basename[ internal_store->basename_size - 1 ] = 0;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

/* Sets the basename
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_set_basename(
     libfsclfs_internal_store_t *internal_store,
     const char *basename,
     size_t basename_length,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_store_set_basename";

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( internal_store->basename != NULL )
	{
		memory_free(
		 internal_store->basename );

		internal_store->basename      = NULL;
		internal_store->basename_size = 0;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) basename,
		          basename_length + 1,
		          &( internal_store->basename_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) basename,
		          basename_length + 1,
		          &( internal_store->basename_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          &( internal_store->basename_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          &( internal_store->basename_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#else
	internal_store->basename_size = basename_length + 1;
#endif
	internal_store->basename = system_string_allocate(
	                            internal_store->basename_size );

	if( internal_store->basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create basename.",
		 function );

		internal_store->basename_size = 0;

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          (libuna_utf8_character_t *) basename,
		          basename_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          (libuna_utf8_character_t *) basename,
		          basename_length + 1,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          (uint8_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          (uint8_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set basename.",
		 function );

		memory_free(
		 internal_store->basename );

		internal_store->basename      = NULL;
		internal_store->basename_size = 0;

		return( -1 );
	}
#else
	if( system_string_copy(
	     internal_store->basename,
	     basename,
	     basename_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set basename.",
		 function );

		memory_free(
		 internal_store->basename );

		internal_store->basename      = NULL;
		internal_store->basename_size = 0;

		return( -1 );
	}
	internal_store->basename[ basename_length ] = 0;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves the size of the basename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libfsclfs_store_get_basename_size_wide(
     libfsclfs_internal_store_t *internal_store,
     size_t *basename_size,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_store_get_basename_size_wide";

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( basename_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename size.",
		 function );

		return( -1 );
	}
	if( internal_store->basename == NULL )
	{
		return( 0 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	*basename_size = internal_store->basename_size;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

/* Retrieves the basename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libfsclfs_store_get_basename_wide(
     libfsclfs_internal_store_t *internal_store,
     wchar_t *basename,
     size_t basename_size,
     libcerror_error_t **error )
{
	static char *function     = "libfsclfs_store_get_basename_wide";
	size_t wide_basename_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( internal_store->basename == NULL )
	{
		return( 0 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_basename_size = internal_store->basename_size;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          &wide_basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          &wide_basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          &wide_basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          &wide_basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	if( basename_size < wide_basename_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: basename too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     basename,
	     internal_store->basename,
	     internal_store->basename_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set basename.",
		 function );

		return( -1 );
	}
	basename[ internal_store->basename_size - 1 ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) basename,
		          basename_size,
		          (libuna_utf8_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) basename,
		          basename_size,
		          (libuna_utf8_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) basename,
		          basename_size,
		          (uint8_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) basename,
		          basename_size,
		          (uint8_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set basename.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

/* Sets the basename
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_set_basename_wide(
     libfsclfs_internal_store_t *internal_store,
     const wchar_t *basename,
     size_t basename_length,
     libcerror_error_t **error )
{
	static char *function = "libfsclfs_store_set_basename_wide";

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( internal_store->basename != NULL )
	{
		memory_free(
		 internal_store->basename );

		internal_store->basename      = NULL;
		internal_store->basename_size = 0;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	internal_store->basename_size = basename_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) basename,
		          basename_length + 1,
		          &( internal_store->basename_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) basename,
		          basename_length + 1,
		          &( internal_store->basename_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          &( internal_store->basename_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          &( internal_store->basename_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	internal_store->basename = system_string_allocate(
	                            internal_store->basename_size );

	if( internal_store->basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create basename.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     internal_store->basename,
	     basename,
	     basename_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set basename.",
		 function );

		memory_free(
		 internal_store->basename );

		internal_store->basename      = NULL;
		internal_store->basename_size = 0;

		return( -1 );
	}
	internal_store->basename[ basename_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          (libuna_utf32_character_t *) basename,
		          basename_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) internal_store->basename,
		          internal_store->basename_size,
		          (libuna_utf16_character_t *) basename,
		          basename_length + 1,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) basename,
		          basename_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) internal_store->basename,
		          internal_store->basename_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) basename,
		          basename_length + 1,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set basename.",
		 function );

		memory_free(
		 internal_store->basename );

		internal_store->basename      = NULL;
		internal_store->basename_size = 0;

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Retrieves the number of containers
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_get_number_of_containers(
     libfsclfs_store_t *store,
     int *number_of_containers,
     libcerror_error_t **error )
{
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_get_number_of_containers";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( libcdata_array_get_number_of_entries(
	     internal_store->container_descriptors_array,
	     number_of_containers,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of container descriptors.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific container
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_get_container(
     libfsclfs_store_t *store,
     int container_index,
     libfsclfs_container_t **container,
     libcerror_error_t **error )
{
	libfsclfs_container_descriptor_t *container_descriptor = NULL;
	libfsclfs_internal_store_t *internal_store             = NULL;
	static char *function                                  = "libfsclfs_store_get_container";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( container == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container.",
		 function );

		return( -1 );
	}
	if( *container != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid container value already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_store->container_descriptors_array,
	     container_index,
	     (intptr_t **) &container_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve container descriptor: %d.",
		 function,
		 container_index );

		return( -1 );
	}
	if( libfsclfs_container_initialize(
	     container,
	     internal_store,
	     container_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create container.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the physical container number for a specific logical container number
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsclfs_store_get_container_physical_number(
     libfsclfs_internal_store_t *internal_store,
     uint32_t container_logical_number,
     uint32_t *container_physical_number,
     libcerror_error_t **error )
{
	libfsclfs_container_descriptor_t *container_descriptor = NULL;
	static char *function                                  = "libfsclfs_store_set_basename_wide";
	int container_descriptor_index                         = 0;
	int number_of_container_descriptors                    = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( container_physical_number == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container physical number.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_store->container_descriptors_array,
	     &number_of_container_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of container descriptors.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_store->container_descriptors_array,
	     container_descriptor_index,
	     (intptr_t **) &container_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve container descriptor: %d.",
		 function,
		 container_descriptor_index );

		return( -1 );
	}
	if( container_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing container descriptor: %d.",
		 function,
		 container_descriptor_index );

		return( -1 );
	}
	if( container_descriptor->logical_number == container_logical_number )
	{
		*container_physical_number = container_descriptor->physical_number;

		return( 1 );
	}
/* TODO remove?
	else if( container_descriptor->physical_number == container_logical_number )
	{
		*container_physical_number = container_descriptor->physical_number;

		return( 1 );
	}
*/
	else if( container_descriptor->logical_number > container_logical_number )
	{
		for( container_descriptor_index = 1;
		     container_descriptor_index < number_of_container_descriptors;
		     container_descriptor_index++ )
		{
			if( libcdata_array_get_entry_by_index(
			     internal_store->container_descriptors_array,
			     container_descriptor_index,
			     (intptr_t **) &container_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve container descriptor: %d.",
				 function,
				 container_descriptor_index );

				return( -1 );
			}
			if( container_descriptor == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing container descriptor: %d.",
				 function,
				 container_descriptor_index );

				return( -1 );
			}
/* TODO determine what unknown2 contains */
			if( container_descriptor->unknown2 == 0 )
			{
				continue;
			}
			if( container_descriptor->logical_number == container_logical_number )
			{
				*container_physical_number = container_descriptor->physical_number;

				return( 1 );
			}
/* TODO remove?
			if( container_descriptor->physical_number == container_logical_number )
			{
				*container_physical_number = container_descriptor->physical_number;

				return( 1 );
			}
*/
		}
	}
	else
	{
		for( container_descriptor_index = number_of_container_descriptors - 1;
		     container_descriptor_index > 0;
		     container_descriptor_index-- )
		{
			if( libcdata_array_get_entry_by_index(
			     internal_store->container_descriptors_array,
			     container_descriptor_index,
			     (intptr_t **) &container_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve container descriptor: %d.",
				 function,
				 container_descriptor_index );

				return( -1 );
			}
			if( container_descriptor == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing container descriptor: %d.",
				 function,
				 container_descriptor_index );

				return( -1 );
			}
			if( container_descriptor->unknown2 == 0 )
			{
				continue;
			}
			if( container_descriptor->logical_number == container_logical_number )
			{
				*container_physical_number = container_descriptor->physical_number;

				return( 1 );
			}
/* TODO remove?
			if( container_descriptor->physical_number == container_logical_number )
			{
				*container_physical_number = container_descriptor->physical_number;

				return( 1 );
			}
*/
		}
	}
	return( 0 );
}

/* Retrieves the number of streams
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_get_number_of_streams(
     libfsclfs_store_t *store,
     int *number_of_streams,
     libcerror_error_t **error )
{
	libfsclfs_internal_store_t *internal_store = NULL;
	static char *function                      = "libfsclfs_store_get_number_of_streams";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( libcdata_array_get_number_of_entries(
	     internal_store->stream_descriptors_array,
	     number_of_streams,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of stream descriptors.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific stream
 * Returns 1 if successful or -1 on error
 */
int libfsclfs_store_get_stream(
     libfsclfs_store_t *store,
     int stream_index,
     libfsclfs_stream_t **stream,
     libcerror_error_t **error )
{
	libfsclfs_internal_store_t *internal_store       = NULL;
	libfsclfs_stream_descriptor_t *stream_descriptor = NULL;
	static char *function                            = "libfsclfs_store_get_stream";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfsclfs_internal_store_t *) store;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stream value already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_store->stream_descriptors_array,
	     stream_index,
	     (intptr_t **) &stream_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stream descriptor: %d.",
		 function,
		 stream_index );

		return( -1 );
	}
	if( libfsclfs_stream_initialize(
	     stream,
	     internal_store,
	     stream_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create stream.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific record value using a logical LSN
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsclfs_store_get_record_value_by_logical_lsn(
     libfsclfs_internal_store_t *internal_store,
     uint16_t stream_number,
     uint32_t container_logical_number,
     uint32_t block_offset,
     uint16_t record_number,
     libfsclfs_record_value_t **record_value,
     libcerror_error_t **error )
{
	libbfio_handle_t *container_file_io_handle = NULL;
	libcdata_array_t *record_values_array      = NULL;
	libfsclfs_owner_page_t *owner_page         = NULL;
	static char *function                      = "libfsclfs_store_get_record_value_by_logical_lsn";
	uint32_t container_physical_number         = 0;
	uint32_t owner_page_offset                 = 0;
	uint32_t physical_block_offset             = 0;
	uint32_t region_offset                     = 0;
	int result                                 = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal store.",
		 function );

		return( -1 );
	}
	if( internal_store->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing IO handle.",
		 function );

		return( -1 );
	}
	result = libfsclfs_store_get_container_physical_number(
	          internal_store,
	          container_logical_number,
	          &container_physical_number,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve container physical number.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
/* TODO use logical container number for index in file IO pool? */
		if( libbfio_pool_get_handle(
		     internal_store->container_file_io_pool,
		     (int) container_physical_number,
		     &container_file_io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve container file IO handle: %" PRIu32 " from pool.",
			 function,
			 container_physical_number );

			goto on_error;
		}
	}
	if( container_file_io_handle == 0 )
	{
		return( 0 );
	}
	if( stream_number == 0 )
	{
		physical_block_offset = block_offset;
		result                = 1;
	}
	else
	{
		region_offset = ( block_offset / internal_store->io_handle->region_size )
			      * internal_store->io_handle->region_size;

		owner_page_offset = region_offset
				  + internal_store->io_handle->region_owner_page_offset;

		if( libfsclfs_owner_page_initialize(
		     &owner_page,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create owner page.",
			 function );

			goto on_error;
		}
		if( libfsclfs_store_read_container_owner_page(
		     internal_store,
		     container_file_io_handle,
		     owner_page,
		     owner_page_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read container owner page.",
			 function );

			goto on_error;
		}
		result = libfsclfs_owner_page_get_physical_block_offset(
		          owner_page,
		          container_logical_number,
		          block_offset,
		          &physical_block_offset,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve physical block offset.",
			 function );

			goto on_error;
		}
/* TODO cache owner page */
		if( libfsclfs_owner_page_free(
		     &owner_page,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free owner page.",
			 function );

			return( -1 );
		}
		owner_page = NULL;
	}
	if( result != 0 )
	{
		if( libcdata_array_initialize(
		     &record_values_array,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create record values array.",
			 function );

			goto on_error;
		}
		if( libfsclfs_block_read_record_values(
		     internal_store,
		     container_file_io_handle,
		     physical_block_offset,
		     record_values_array,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block record values.",
			 function );

			goto on_error;
		}
		if( libcdata_array_get_entry_by_index(
		     record_values_array,
		     (int) record_number,
		     (intptr_t **) record_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve record value: %" PRIu16 ".",
			 function,
			 record_number );

			goto on_error;
		}
/* TODO for now unset the record value */
		if( libcdata_array_set_entry_by_index(
		     record_values_array,
		     (int) record_number,
		     (intptr_t *) NULL,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set record value: %" PRIu16 ".",
			 function,
			 record_number );

			goto on_error;
		}
		if( libcdata_array_free(
		     &record_values_array,
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_record_value_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free record values array.",
			 function );

			goto on_error;
		}
	}
	return( result );

on_error:
	if( record_values_array != NULL )
	{
		libcdata_array_free(
		 &record_values_array,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libfsclfs_record_value_free,
		 NULL );
	}
	if( owner_page != NULL )
	{
		libfsclfs_owner_page_free(
		 &owner_page,
		 NULL );
	}
	return( -1 );
}

