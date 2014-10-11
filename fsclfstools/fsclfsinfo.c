/*
 * Shows information obtained from a Common Log File System (CLFS) store
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

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsclfsoutput.h"
#include "fsclfstools_libcerror.h"
#include "fsclfstools_libclocale.h"
#include "fsclfstools_libcnotify.h"
#include "fsclfstools_libcstring.h"
#include "fsclfstools_libcsystem.h"
#include "fsclfstools_libfsclfs.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use fsclfsinfo to determine information about a Common Log File System (CLFS) store.\n\n" );

	fprintf( stream, "Usage: fsclfsinfo [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source CLFS base log file\n\n" );

	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Prints store information
 * Returns 1 if successful or -1 on error
 */
int fsclfsinfo_store_info_fprint(
     FILE *stream,
     libfsclfs_store_t *log_store,
     libfsclfs_error_t **error )
{
	libcstring_system_character_t *value_string = NULL;
	libfsclfs_container_t *log_container        = NULL;
	libfsclfs_stream_t *log_stream              = NULL;
	static char *function                       = "fsclfsinfo_store_info_fprint";
	size64_t container_size                     = 0;
	size_t value_string_size                    = 0;
	int item_index                              = 0;
	int number_of_containers                    = 0;
	int number_of_streams                       = 0;
	int result                                  = 0;

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
	if( log_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	fprintf(
	 stream,
	 "Common Log File System (CLFS) store information:\n" );

	if( libfsclfs_store_get_number_of_containers(
	     log_store,
	     &number_of_containers,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of containers.",
		 function );

		goto on_error;
	}
	if( libfsclfs_store_get_number_of_streams(
	     log_store,
	     &number_of_streams,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of streams.",
		 function );

		goto on_error;
	}
	fprintf(
	 stream,
	 "\tNumber of containers:\t%d\n",
	 number_of_containers );

	fprintf(
	 stream,
	 "\tNumber of streams:\t%d\n",
	 number_of_streams );

	fprintf(
	 stream,
	 "\n" );

	for( item_index = 0;
	     item_index < number_of_containers;
	     item_index++ )
	{
		fprintf(
		 stream,
		 "Container: %d\n",
		 item_index + 1 );

		if( libfsclfs_store_get_container(
		     log_store,
		     item_index,
		     &log_container,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve container: %d.",
			 function,
			 item_index );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsclfs_container_get_utf16_name_size(
		          log_container,
		          &value_string_size,
		          error );
#else
		result = libfsclfs_container_get_utf8_name_size(
		          log_container,
		          &value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve container: %d name size.",
			 function,
			 item_index );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsclfs_container_get_utf16_name(
		          log_container,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libfsclfs_container_get_utf8_name(
		          log_container,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve container: %d name.",
			 function,
			 item_index );

			memory_free(
			 value_string );

			goto on_error;
		}
		fprintf(
		 stream,
		 "\tName:\t%" PRIs_LIBCSTRING_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		if( libfsclfs_container_get_size(
		     log_container,
		     &container_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve container: %d. size",
			 function,
			 item_index );

			goto on_error;
		}
		fprintf(
		 stream,
		 "\tSize:\t%" PRIu64 "\n",
		 container_size );

		if( libfsclfs_container_free(
		     &log_container,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free container: %d.",
			 function,
			 item_index );

			goto on_error;
		}
		fprintf(
		 stream,
		 "\n" );
	}
	for( item_index = 0;
	     item_index < number_of_streams;
	     item_index++ )
	{
		fprintf(
		 stream,
		 "Stream: %d\n",
		 item_index + 1 );

		if( libfsclfs_store_get_stream(
		     log_store,
		     item_index,
		     &log_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve stream: %d.",
			 function,
			 item_index );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsclfs_stream_get_utf16_name_size(
		          log_stream,
		          &value_string_size,
		          error );
#else
		result = libfsclfs_stream_get_utf8_name_size(
		          log_stream,
		          &value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve stream: %d name size.",
			 function,
			 item_index );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsclfs_stream_get_utf16_name(
		          log_stream,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libfsclfs_stream_get_utf8_name(
		          log_stream,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve stream: %d name.",
			 function,
			 item_index );

			memory_free(
			 value_string );

			goto on_error;
		}
		fprintf(
		 stream,
		 "\tName:\t%" PRIs_LIBCSTRING_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		if( libfsclfs_stream_free(
		     &log_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free stream: %d.",
			 function,
			 item_index );

			goto on_error;
		}
		fprintf(
		 stream,
		 "\n" );
	}
	return( 1 );

on_error:
	if( log_container != NULL )
	{
		libfsclfs_container_free(
		 &log_container,
		 NULL );
	}
	if( log_stream != NULL )
	{
		libfsclfs_stream_free(
		 &log_stream,
		 NULL );
	}
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libfsclfs_error_t *error              = NULL;
	libfsclfs_store_t *log_store          = NULL;
	libcstring_system_character_t *source = NULL;
	char *program                         = "fsclfsinfo";
	libcstring_system_integer_t option    = 0;
	int result                            = 0;
	int verbose                           = 0;

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
             "fsclfstools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
        if( libcsystem_initialize(
             _IONBF,
             &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize system values.\n" );

		goto on_error;
	}
	fsclfsoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "hvV" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (libcstring_system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (libcstring_system_integer_t) 'v':
				verbose = 1;

				break;

			case (libcstring_system_integer_t) 'V':
				fsclfsoutput_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libfsclfs_notify_set_stream(
	 stderr,
	 NULL );
	libfsclfs_notify_set_verbose(
	 verbose );

	if( libfsclfs_store_initialize(
	     &log_store,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize store.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsclfs_store_open_wide(
	          log_store,
	          source,
	          LIBFSCLFS_OPEN_READ,
	          &error );
#else
	result = libfsclfs_store_open(
	          log_store,
	          source,
	          LIBFSCLFS_OPEN_READ,
	          &error );
#endif
	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Error opening store using base log: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 argv[ optind ] );

		goto on_error;
	}
	if( fsclfsinfo_store_info_fprint(
	     stdout,
	     log_store,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print store information.\n" );

		goto on_error;
	}
	if( libfsclfs_store_close(
	     log_store,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Error closing store.\n" );

		goto on_error;
	}
	if( libfsclfs_store_free(
	     &log_store,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free store.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( log_store != NULL )
	{
		libfsclfs_store_free(
		 &log_store,
		 NULL );
	}
	return( EXIT_FAILURE );
}

