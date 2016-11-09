/*
 * Library store type testing program
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

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsclfs_test_libcerror.h"
#include "fsclfs_test_libclocale.h"
#include "fsclfs_test_libcsystem.h"
#include "fsclfs_test_libfsclfs.h"
#include "fsclfs_test_libuna.h"
#include "fsclfs_test_macros.h"
#include "fsclfs_test_memory.h"

#if SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make fsclfs_test_store generate verbose output
#define FSCLFS_TEST_STORE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int fsclfs_test_store_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "fsclfs_test_store_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int fsclfs_test_store_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "fsclfs_test_store_get_wide_source";
	size_t wide_source_size = 0;
	size_t source_length    = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source store
 * Returns 1 if successful or -1 on error
 */
int fsclfs_test_store_open_source(
     libfsclfs_store_t **store,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "fsclfs_test_store_open_source";
	int result            = 0;

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
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libfsclfs_store_initialize(
	     store,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize store.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsclfs_store_open_wide(
	          *store,
	          source,
	          LIBFSCLFS_OPEN_READ,
	          error );
#else
	result = libfsclfs_store_open(
	          *store,
	          source,
	          LIBFSCLFS_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open store.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *store != NULL )
	{
		libfsclfs_store_free(
		 store,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source store
 * Returns 1 if successful or -1 on error
 */
int fsclfs_test_store_close_source(
     libfsclfs_store_t **store,
     libcerror_error_t **error )
{
	static char *function = "fsclfs_test_store_close_source";
	int result            = 0;

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
	if( libfsclfs_store_free(
	     store,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free store.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libfsclfs_store_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_store_initialize(
     void )
{
	libcerror_error_t *error = NULL;
	libfsclfs_store_t *store      = NULL;
	int result               = 0;

	/* Test libfsclfs_store_initialize
	 */
	result = libfsclfs_store_initialize(
	          &store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "store",
         store );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfsclfs_store_free(
	          &store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "store",
         store );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfsclfs_store_initialize(
	          NULL,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	store = (libfsclfs_store_t *) 0x12345678UL;

	result = libfsclfs_store_initialize(
	          &store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	store = NULL;

#if defined( HAVE_FSCLFS_TEST_MEMORY )

	/* Test libfsclfs_store_initialize with malloc failing
	 */
	fsclfs_test_malloc_attempts_before_fail = 0;

	result = libfsclfs_store_initialize(
	          &store,
	          &error );

	if( fsclfs_test_malloc_attempts_before_fail != -1 )
	{
		fsclfs_test_malloc_attempts_before_fail = -1;

		if( store != NULL )
		{
			libfsclfs_store_free(
			 &store,
			 NULL );
		}
	}
	else
	{
		FSCLFS_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FSCLFS_TEST_ASSERT_IS_NULL(
		 "store",
		 store );

		FSCLFS_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfsclfs_store_initialize with memset failing
	 */
	fsclfs_test_memset_attempts_before_fail = 0;

	result = libfsclfs_store_initialize(
	          &store,
	          &error );

	if( fsclfs_test_memset_attempts_before_fail != -1 )
	{
		fsclfs_test_memset_attempts_before_fail = -1;

		if( store != NULL )
		{
			libfsclfs_store_free(
			 &store,
			 NULL );
		}
	}
	else
	{
		FSCLFS_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FSCLFS_TEST_ASSERT_IS_NULL(
		 "store",
		 store );

		FSCLFS_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FSCLFS_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( store != NULL )
	{
		libfsclfs_store_free(
		 &store,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsclfs_store_free function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_store_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsclfs_store_free(
	          NULL,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsclfs_store_open functions
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_store_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libfsclfs_store_t *store      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = fsclfs_test_store_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfsclfs_store_initialize(
	          &store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "store",
         store );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libfsclfs_store_open(
	          store,
	          narrow_source,
	          LIBFSCLFS_OPEN_READ,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libfsclfs_store_close(
	          store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfsclfs_store_free(
	          &store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "store",
         store );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( store != NULL )
	{
		libfsclfs_store_free(
		 &store,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libfsclfs_store_open_wide functions
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_store_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libfsclfs_store_t *store      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = fsclfs_test_store_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfsclfs_store_initialize(
	          &store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "store",
         store );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libfsclfs_store_open_wide(
	          store,
	          wide_source,
	          LIBFSCLFS_OPEN_READ,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libfsclfs_store_close(
	          store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfsclfs_store_free(
	          &store,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "store",
         store );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( store != NULL )
	{
		libfsclfs_store_free(
		 &store,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libfsclfs_store_get_number_of_containers functions
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_store_get_number_of_containers(
     libfsclfs_store_t *store )
{
	libcerror_error_t *error = NULL;
	int number_of_containers    = 0;
	int result               = 0;

	result = libfsclfs_store_get_number_of_containers(
	          store,
	          &number_of_containers,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfsclfs_store_get_number_of_containers(
	          NULL,
	          &number_of_containers,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfsclfs_store_get_number_of_containers(
	          store,
	          NULL,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsclfs_store_get_number_of_streams functions
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_store_get_number_of_streams(
     libfsclfs_store_t *store )
{
	libcerror_error_t *error = NULL;
	int number_of_streams    = 0;
	int result               = 0;

	result = libfsclfs_store_get_number_of_streams(
	          store,
	          &number_of_streams,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfsclfs_store_get_number_of_streams(
	          NULL,
	          &number_of_streams,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfsclfs_store_get_number_of_streams(
	          store,
	          NULL,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;
	libfsclfs_store_t *store        = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( FSCLFS_TEST_STORE_VERBOSE )
	libfsclfs_notify_set_verbose(
	 1 );
	libfsclfs_notify_set_stream(
	 stderr,
	 NULL );
#endif

	FSCLFS_TEST_RUN(
	 "libfsclfs_store_initialize",
	 fsclfs_test_store_initialize );

	FSCLFS_TEST_RUN(
	 "libfsclfs_store_free",
	 fsclfs_test_store_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		FSCLFS_TEST_RUN_WITH_ARGS(
		 "libfsclfs_store_open",
		 fsclfs_test_store_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		FSCLFS_TEST_RUN_WITH_ARGS(
		 "libfsclfs_store_open_wide",
		 fsclfs_test_store_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBFSCLFS_HAVE_BFIO )

		/* TODO add test for libfsclfs_store_open_file_io_handle */

#endif /* defined( LIBFSCLFS_HAVE_BFIO ) */

		/* TODO add test for libfsclfs_store_close */

		/* Initialize test
		 */
		result = fsclfs_test_store_open_source(
		          &store,
		          source,
		          &error );

		FSCLFS_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
	         "store",
	         store );

	        FSCLFS_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		FSCLFS_TEST_RUN_WITH_ARGS(
		 "libfsclfs_store_open",
		 fsclfs_test_store_open,
		 store );

		FSCLFS_TEST_RUN_WITH_ARGS(
		 "libfsclfs_store_get_number_of_containers",
		 fsclfs_test_store_get_number_of_containers,
		 store );

		FSCLFS_TEST_RUN_WITH_ARGS(
		 "libfsclfs_store_get_number_of_streams",
		 fsclfs_test_store_get_number_of_streams,
		 store );

		/* Clean up
		 */
		result = fsclfs_test_store_close_source(
		          &store,
		          &error );

		FSCLFS_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		FSCLFS_TEST_ASSERT_IS_NULL(
	         "store",
	         store );

	        FSCLFS_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( store != NULL )
	{
		fsclfs_test_store_close_source(
		 &store,
		 NULL );
	}
	return( EXIT_FAILURE );
}

