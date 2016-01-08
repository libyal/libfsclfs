/*
 * Test reading records from a Common Log File System (CLFS) store
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

/*
#define TXF_TEST
#define TXR_TEST
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
#include "fsclfstools_libftxf.h"
#include "fsclfstools_libftxr.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use fsclfstest to read records from a Common Log File System (CLFS) store.\n\n" );

	fprintf( stream, "Usage: fsclfstest [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source CLFS base log file\n\n" );

	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Prints a record information
 * Returns 1 if successful or -1 on error
 */
int fsclfstest_store_record_fprint(
     FILE *stream,
     libfsclfs_store_t *log_store,
     libfsclfs_error_t **error )
{
	libfsclfs_record_t *log_record = NULL;
	libfsclfs_stream_t *log_stream = NULL;
	uint8_t *record_data           = NULL;
	static char *function          = "fsclfstest_store_record_fprint";
	size_t record_data_size        = 0;
	uint64_t record_lsn            = 0;
	int stream_index               = 0;

#if defined( TXF_TEST )
	libftxf_record_t *txf_record   = NULL;
#elif defined( TXR_TEST )
	libftxr_record_t *txr_record   = NULL;
#endif

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
	if( libfsclfs_store_get_stream(
	     log_store,
	     stream_index,
	     &log_stream,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stream: %d.",
		 function,
		 stream_index );

		goto on_error;
	}
	if( libfsclfs_stream_get_base_lsn(
	     log_stream,
	     &record_lsn,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stream base LSN.",
		 function );

		goto on_error;
	}
/*
	if( libfsclfs_stream_get_last_lsn(
	     log_stream,
	     &record_lsn,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stream last LSN.",
		 function );

		goto on_error;
	}
*/
#if defined( TXF_TEST )
	if( libftxf_record_initialize(
	     &txf_record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create TxF record.",
		 function );

		goto on_error;
	}
#elif defined( TXR_TEST )
	if( libftxr_record_initialize(
	     &txr_record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create TxR record.",
		 function );

		goto on_error;
	}
#endif
	while( record_lsn != 0xffffffff00000000ULL )
	{
		if( libfsclfs_stream_get_record_by_lsn(
		     log_stream,
		     record_lsn,
		     &log_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve record by LSN: 0x%08" PRIx64 ".",
			 function,
			 record_lsn );

			goto on_error;
		}
		if( libfsclfs_record_get_data(
		     log_record,
		     &record_data,
		     &record_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve record: 0x%08" PRIx64 " data.",
			 function,
			 record_lsn );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: record: 0x%08" PRIx64 " data:\n",
		 function,
		 record_lsn );

#if defined( TXF_TEST )
		if( libftxf_record_read(
		     txf_record,
		     record_data,
		     record_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read TxF record.",
			 function );

			goto on_error;
		}
#elif defined( TXR_TEST )
		if( libftxr_record_read(
		     txr_record,
		     record_data,
		     record_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read TxR record.",
			 function );

			goto on_error;
		}
#else
		libcnotify_print_data(
		 record_data,
		 record_data_size,
		 0 );
#endif
		if( libfsclfs_record_get_previous_lsn(
		     log_record,
		     &record_lsn,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve previous LSN.",
			 function,
			 record_lsn );

			goto on_error;
		}
		if( libfsclfs_record_free(
		     &log_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free record.",
			 function );

			goto on_error;
		}
/*
		record_lsn = 0xffffffff00000000ULL;
*/
	}
#if defined( TXF_TEST )
	if( libftxf_record_free(
	     &txf_record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free TxF record.",
		 function );

		goto on_error;
	}
#elif defined( TXR_TEST )
	if( libftxr_record_free(
	     &txr_record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free TxR record.",
		 function );

		goto on_error;
	}
#endif
	if( libfsclfs_stream_free(
	     &log_stream,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free stream.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( log_record != NULL )
	{
		libfsclfs_record_free(
		 &log_record,
		 NULL );
	}
	if( log_stream != NULL )
	{
		libfsclfs_stream_free(
		 &log_stream,
		 NULL );
	}
#if defined( TXF_TEST )
	if( txf_record != NULL )
	{
		libftxf_record_free(
		 &txf_record,
		 NULL );
	}
#elif defined( TXR_TEST )
	if( txr_record != NULL )
	{
		libftxr_record_free(
		 &txr_record,
		 NULL );
	}
#endif
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
	char *program                         = "fsclfstest";
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
				 argv[ optind ] );

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
	if( libfsclfs_store_open_containers(
	     log_store,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open store containers.\n" );

		goto on_error;
	}
	if( fsclfstest_store_record_fprint(
	     stdout,
	     log_store,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print store record.\n" );

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

