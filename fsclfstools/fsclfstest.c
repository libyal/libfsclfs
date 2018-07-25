/*
 * Test reading records from a Common Log File System (CLFS) store
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <system_string.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "fsclfstools_getopt.h"
#include "fsclfstools_libcerror.h"
#include "fsclfstools_libclocale.h"
#include "fsclfstools_libcnotify.h"
#include "fsclfstools_libfsclfs.h"
#include "fsclfstools_libftxf.h"
#include "fsclfstools_libftxr.h"
#include "fsclfstools_output.h"
#include "fsclfstools_signal.h"
#include "fsclfstools_unused.h"

enum FSCLFS_RECORD_DATA_TYPES
{
	FSCLFS_RECORD_DATA_TYPE_UNKNOWN,
	FSCLFS_RECORD_DATA_TYPE_TM,
	FSCLFS_RECORD_DATA_TYPE_TXF,
	FSCLFS_RECORD_DATA_TYPE_TXR,
};

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
int fsclfstest_record_fprint(
     FILE *stream,
     int record_data_type,
     libfsclfs_record_t *log_record,
     libfsclfs_error_t **error )
{
	libftxf_record_t *txf_record = NULL;
	libftxr_record_t *txr_record = NULL;
	uint8_t *record_data         = NULL;
	static char *function        = "fsclfstest_store_record_fprint";
	size_t record_data_size      = 0;

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
	if( log_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
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
		 "%s: unable to retrieve record data.",
		 function );

		goto on_error;
	}
	switch( record_data_type )
	{
		case FSCLFS_RECORD_DATA_TYPE_TXF:
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
			if( libftxf_record_copy_from_byte_stream(
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
			break;

		case FSCLFS_RECORD_DATA_TYPE_TXR:
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
			if( libftxr_record_copy_from_byte_stream(
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
			break;

		default:
			libcnotify_print_data(
			 record_data,
			 record_data_size,
			 0 );
			break;
	}
	return( 1 );

on_error:
	if( txf_record != NULL )
	{
		libftxf_record_free(
		 &txf_record,
		 NULL );
	}
	if( txr_record != NULL )
	{
		libftxr_record_free(
		 &txr_record,
		 NULL );
	}
	return( -1 );
}

/* Prints the records in a stream
 * Returns 1 if successful or -1 on error
 */
int fsclfstest_stream_fprint(
     FILE *stream,
     libfsclfs_stream_t *log_stream,
     libfsclfs_error_t **error )
{
	uint8_t stream_name[ 256 ];

	libfsclfs_record_t *log_record = NULL;
	static char *function          = "fsclfstest_stream_fprint";
	uint64_t record_lsn            = 0;
	uint32_t record_type           = 0;
	int record_data_type           = 0;
	int result                     = 0;

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
	if( log_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( libfsclfs_stream_get_utf8_name(
	     log_stream,
	     stream_name,
	     256,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stream name.",
		 function );

		goto on_error;
	}
	/* Name of the TxF stream: TxfLog
	 */
	if( memory_compare(
	     stream_name,
	     "TxfLog",
	     7 ) == 0 )
	{
		record_data_type = FSCLFS_RECORD_DATA_TYPE_TXF;
	}
	/* Name of the TxR stream: \SystemRoot\System32\Config\TxR\{%GUID%}.TxR.blf
	 */
	else if( ( memory_compare(
	            stream_name,
	            "\\SystemRoot\\System32\\Config\\TxR\\{",
	            33 ) == 0 )
	      && ( memory_compare(
	            &( stream_name[ 70 ] ),
	            "}.TxR.blf",
	            10 ) == 0 ) )
	{
		record_data_type = FSCLFS_RECORD_DATA_TYPE_TXR;
	}
	/* Name of the TxR stream: \Device\HarddiskVolume#\$Extend\$RmMetadata\$TxfLog\$TxfLog.blf
	 */
	else if( ( memory_compare(
	            stream_name,
	            "\\Device\\HarddiskVolume",
	            22 ) == 0 )
	      && ( memory_compare(
	            &( stream_name[ 23 ] ),
	            "\\$Extend\\$RmMetadata\\$TxfLog\\$TxfLog.blf",
	            41 ) == 0 ) )
	{
		record_data_type = FSCLFS_RECORD_DATA_TYPE_TM;

/* 00000000: 00 00 00 00 00 00 00 00  04 01 00 00 ed e0 c2 43   ........ .......C
 * 00000010: 3d 9f e1 11 ad a0 80 6e  6f 6e 69 63 8c 6c d6 9a   =......n onic.l..
 *
 * 00000000: 00 00 00 00 00 00 00 00  04 01 00 00 ed e0 c2 43   ........ .......C
 * 00000010: 3d 9f e1 11 ad a0 80 6e  6f 6e 69 63 8c ec 7c 80   =......n onic..|.
 *
 *  0 -  8 Unknown empty
 *  8 -  4 Unknown
 * 12 - 16 Unknown (GUID?)
 * 28 -  4 Unknown (sequence number? similar to unknown2)
 *
 * libfsclfs_container_descriptor_read_data: unknown2                      : 0x8cd6a878
 */
	}
	else
	{
		record_data_type = FSCLFS_RECORD_DATA_TYPE_UNKNOWN;
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
	while( record_lsn != 0xffffffff00000000ULL )
	{
		result = libfsclfs_stream_get_record_by_lsn(
		          log_stream,
		          record_lsn,
		          &log_record,
		          error );

		if( result == -1 )
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
		else if( result == 0 )
		{
			break;
		}
		libcnotify_printf(
		 "%s: record: 0x%08" PRIx64 ":\n",
		 function,
		 record_lsn );

		if( fsclfstest_record_fprint(
		     stream,
		     record_data_type,
		     log_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print record.",
			 function );

			goto on_error;
		}
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
			 function );

			goto on_error;
		}
		if( libfsclfs_record_get_type(
		     log_record,
		     &record_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve record type.",
			 function );

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
	}
	return( 1 );

on_error:
	if( log_record != NULL )
	{
		libfsclfs_record_free(
		 &log_record,
		 NULL );
	}
	return( -1 );
}

/* Prints the records in a store
 * Returns 1 if successful or -1 on error
 */
int fsclfstest_store_fprint(
     FILE *stream,
     libfsclfs_store_t *log_store,
     libfsclfs_error_t **error )
{
	libfsclfs_stream_t *log_stream = NULL;
	static char *function          = "fsclfstest_store_fprint";
	int item_index                 = 0;
	int number_of_streams          = 0;

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
	for( item_index = 0;
	     item_index < number_of_streams;
	     item_index++ )
	{
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
		if( fsclfstest_stream_fprint(
		     stream,
		     log_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print records in stream: %d.",
			 function,
			 item_index );

			goto on_error;
		}
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
	}
	return( 1 );

on_error:
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libfsclfs_error_t *error     = NULL;
	libfsclfs_store_t *log_store = NULL;
	system_character_t *source   = NULL;
	char *program                = "fsclfstest";
	system_integer_t option      = 0;
	int result                   = 0;
	int verbose                  = 0;

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
        if( fsclfstools_output_initialize(
             _IONBF,
             &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	fsclfsoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = fsclfstools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "hvV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "Error opening store using base log: %" PRIs_SYSTEM ".\n",
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
	if( fsclfstest_store_fprint(
	     stdout,
	     log_store,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print records in store.\n" );

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

