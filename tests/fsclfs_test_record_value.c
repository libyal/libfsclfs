/*
 * Library record_value type test program
 *
 * Copyright (C) 2010-2023, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsclfs_test_libcerror.h"
#include "fsclfs_test_libfsclfs.h"
#include "fsclfs_test_macros.h"
#include "fsclfs_test_memory.h"
#include "fsclfs_test_unused.h"

#include "../libfsclfs/libfsclfs_record_value.h"

#if defined( __GNUC__ ) && !defined( LIBFSCLFS_DLL_IMPORT )

/* Tests the libfsclfs_record_value_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_record_value_initialize(
     void )
{
	libcerror_error_t *error               = NULL;
	libfsclfs_record_value_t *record_value = NULL;
	int result                             = 0;

#if defined( HAVE_FSCLFS_TEST_MEMORY )
	int number_of_malloc_fail_tests        = 1;
	int number_of_memset_fail_tests        = 1;
	int test_number                        = 0;
#endif

	/* Test regular cases
	 */
	result = libfsclfs_record_value_initialize(
	          &record_value,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSCLFS_TEST_ASSERT_IS_NOT_NULL(
	 "record_value",
	 record_value );

	FSCLFS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsclfs_record_value_free(
	          &record_value,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSCLFS_TEST_ASSERT_IS_NULL(
	 "record_value",
	 record_value );

	FSCLFS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsclfs_record_value_initialize(
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

	record_value = (libfsclfs_record_value_t *) 0x12345678UL;

	result = libfsclfs_record_value_initialize(
	          &record_value,
	          &error );

	record_value = NULL;

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSCLFS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FSCLFS_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfsclfs_record_value_initialize with malloc failing
		 */
		fsclfs_test_malloc_attempts_before_fail = test_number;

		result = libfsclfs_record_value_initialize(
		          &record_value,
		          &error );

		if( fsclfs_test_malloc_attempts_before_fail != -1 )
		{
			fsclfs_test_malloc_attempts_before_fail = -1;

			if( record_value != NULL )
			{
				libfsclfs_record_value_free(
				 &record_value,
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
			 "record_value",
			 record_value );

			FSCLFS_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfsclfs_record_value_initialize with memset failing
		 */
		fsclfs_test_memset_attempts_before_fail = test_number;

		result = libfsclfs_record_value_initialize(
		          &record_value,
		          &error );

		if( fsclfs_test_memset_attempts_before_fail != -1 )
		{
			fsclfs_test_memset_attempts_before_fail = -1;

			if( record_value != NULL )
			{
				libfsclfs_record_value_free(
				 &record_value,
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
			 "record_value",
			 record_value );

			FSCLFS_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FSCLFS_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record_value != NULL )
	{
		libfsclfs_record_value_free(
		 &record_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsclfs_record_value_free function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_record_value_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsclfs_record_value_free(
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

/* Tests the libfsclfs_record_value_read_data function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_record_value_read_data(
     void )
{
	libcerror_error_t *error               = NULL;
	libfsclfs_record_value_t *record_value = NULL;
	int result                             = 0;

	/* Initialize test
	 */
	result = libfsclfs_record_value_initialize(
	          &record_value,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSCLFS_TEST_ASSERT_IS_NOT_NULL(
	 "record_value",
	 record_value );

	FSCLFS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsclfs_record_value_read_data(
	          NULL,
	          NULL,
	          0,
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

	result = libfsclfs_record_value_read_data(
	          record_value,
	          NULL,
	          0,
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

	/* Clean up
	 */
	result = libfsclfs_record_value_free(
	          &record_value,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSCLFS_TEST_ASSERT_IS_NULL(
	 "record_value",
	 record_value );

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
	if( record_value != NULL )
	{
		libfsclfs_record_value_free(
		 &record_value,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFSCLFS_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FSCLFS_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FSCLFS_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FSCLFS_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FSCLFS_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FSCLFS_TEST_UNREFERENCED_PARAMETER( argc )
	FSCLFS_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFSCLFS_DLL_IMPORT )

	FSCLFS_TEST_RUN(
	 "libfsclfs_record_value_initialize",
	 fsclfs_test_record_value_initialize );

	FSCLFS_TEST_RUN(
	 "libfsclfs_record_value_free",
	 fsclfs_test_record_value_free );

	FSCLFS_TEST_RUN(
	 "libfsclfs_record_value_read_data",
	 fsclfs_test_record_value_read_data );

	/* TODO: add tests for libfsclfs_record_value_get_data */

#endif /* defined( __GNUC__ ) && !defined( LIBFSCLFS_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

