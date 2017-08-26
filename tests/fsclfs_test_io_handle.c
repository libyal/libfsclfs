/*
 * Library io_handle type test program
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsclfs_test_libcerror.h"
#include "fsclfs_test_libfsclfs.h"
#include "fsclfs_test_macros.h"
#include "fsclfs_test_memory.h"
#include "fsclfs_test_unused.h"

#include "../libfsclfs/libfsclfs_io_handle.h"

#if defined( __GNUC__ ) && !defined( LIBFSCLFS_DLL_IMPORT )

/* Tests the libfsclfs_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_io_handle_initialize(
     void )
{
	libcerror_error_t *error         = NULL;
	libfsclfs_io_handle_t *io_handle = NULL;
	int result                       = 0;

#if defined( HAVE_FSCLFS_TEST_MEMORY )
	int number_of_malloc_fail_tests  = 1;
	int number_of_memset_fail_tests  = 1;
	int test_number                  = 0;
#endif

	/* Test regular cases
	 */
	result = libfsclfs_io_handle_initialize(
	          &io_handle,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "io_handle",
         io_handle );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfsclfs_io_handle_free(
	          &io_handle,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "io_handle",
         io_handle );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfsclfs_io_handle_initialize(
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

	io_handle = (libfsclfs_io_handle_t *) 0x12345678UL;

	result = libfsclfs_io_handle_initialize(
	          &io_handle,
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

	io_handle = NULL;

#if defined( HAVE_FSCLFS_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfsclfs_io_handle_initialize with malloc failing
		 */
		fsclfs_test_malloc_attempts_before_fail = test_number;

		result = libfsclfs_io_handle_initialize(
		          &io_handle,
		          &error );

		if( fsclfs_test_malloc_attempts_before_fail != -1 )
		{
			fsclfs_test_malloc_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libfsclfs_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
		/* Test libfsclfs_io_handle_initialize with memset failing
		 */
		fsclfs_test_memset_attempts_before_fail = test_number;

		result = libfsclfs_io_handle_initialize(
		          &io_handle,
		          &error );

		if( fsclfs_test_memset_attempts_before_fail != -1 )
		{
			fsclfs_test_memset_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libfsclfs_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
	if( io_handle != NULL )
	{
		libfsclfs_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsclfs_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsclfs_io_handle_free(
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

/* Tests the libfsclfs_io_handle_clear function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_io_handle_clear(
     void )
{
	libcerror_error_t *error         = NULL;
	libfsclfs_io_handle_t *io_handle = NULL;
	int result                       = 0;

	/* Initialize test
	 */
	result = libfsclfs_io_handle_initialize(
	          &io_handle,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "io_handle",
         io_handle );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test regular cases
	 */
	result = libfsclfs_io_handle_clear(
	          io_handle,
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
	result = libfsclfs_io_handle_clear(
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

	/* Clean up
	 */
	result = libfsclfs_io_handle_free(
	          &io_handle,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "io_handle",
         io_handle );

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
	if( io_handle != NULL )
	{
		libfsclfs_io_handle_free(
		 &io_handle,
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
	 "libfsclfs_io_handle_initialize",
	 fsclfs_test_io_handle_initialize );

	FSCLFS_TEST_RUN(
	 "libfsclfs_io_handle_free",
	 fsclfs_test_io_handle_free );

	FSCLFS_TEST_RUN(
	 "libfsclfs_io_handle_clear",
	 fsclfs_test_io_handle_clear );

#endif /* defined( __GNUC__ ) && !defined( LIBFSCLFS_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

