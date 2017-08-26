/*
 * Library owner_page type test program
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

#include "../libfsclfs/libfsclfs_owner_page.h"

#if defined( __GNUC__ ) && !defined( LIBFSCLFS_DLL_IMPORT )

/* Tests the libfsclfs_owner_page_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_owner_page_initialize(
     void )
{
	libcerror_error_t *error           = NULL;
	libfsclfs_owner_page_t *owner_page = NULL;
	int result                         = 0;

#if defined( HAVE_FSCLFS_TEST_MEMORY )
	int number_of_malloc_fail_tests    = 1;
	int number_of_memset_fail_tests    = 1;
	int test_number                    = 0;
#endif

	/* Test regular cases
	 */
	result = libfsclfs_owner_page_initialize(
	          &owner_page,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "owner_page",
         owner_page );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfsclfs_owner_page_free(
	          &owner_page,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "owner_page",
         owner_page );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfsclfs_owner_page_initialize(
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

	owner_page = (libfsclfs_owner_page_t *) 0x12345678UL;

	result = libfsclfs_owner_page_initialize(
	          &owner_page,
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

	owner_page = NULL;

#if defined( HAVE_FSCLFS_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfsclfs_owner_page_initialize with malloc failing
		 */
		fsclfs_test_malloc_attempts_before_fail = test_number;

		result = libfsclfs_owner_page_initialize(
		          &owner_page,
		          &error );

		if( fsclfs_test_malloc_attempts_before_fail != -1 )
		{
			fsclfs_test_malloc_attempts_before_fail = -1;

			if( owner_page != NULL )
			{
				libfsclfs_owner_page_free(
				 &owner_page,
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
			 "owner_page",
			 owner_page );

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
		/* Test libfsclfs_owner_page_initialize with memset failing
		 */
		fsclfs_test_memset_attempts_before_fail = test_number;

		result = libfsclfs_owner_page_initialize(
		          &owner_page,
		          &error );

		if( fsclfs_test_memset_attempts_before_fail != -1 )
		{
			fsclfs_test_memset_attempts_before_fail = -1;

			if( owner_page != NULL )
			{
				libfsclfs_owner_page_free(
				 &owner_page,
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
			 "owner_page",
			 owner_page );

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
	if( owner_page != NULL )
	{
		libfsclfs_owner_page_free(
		 &owner_page,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsclfs_owner_page_free function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_owner_page_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsclfs_owner_page_free(
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

/* Tests the libfsclfs_owner_page_read function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_owner_page_read(
     void )
{
	libcerror_error_t *error           = NULL;
	libfsclfs_owner_page_t *owner_page = NULL;
	int result                         = 0;

	/* Initialize test
	 */
	result = libfsclfs_owner_page_initialize(
	          &owner_page,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NOT_NULL(
         "owner_page",
         owner_page );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfsclfs_owner_page_read(
	          NULL,
	          NULL,
	          NULL,
	          0,
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

	result = libfsclfs_owner_page_read(
	          owner_page,
	          NULL,
	          NULL,
	          0,
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

	return( 1 );

	/* Clean up
	 */
	result = libfsclfs_owner_page_free(
	          &owner_page,
	          &error );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSCLFS_TEST_ASSERT_IS_NULL(
         "owner_page",
         owner_page );

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
	if( owner_page != NULL )
	{
		libfsclfs_owner_page_free(
		 &owner_page,
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
	 "libfsclfs_owner_page_initialize",
	 fsclfs_test_owner_page_initialize );

	FSCLFS_TEST_RUN(
	 "libfsclfs_owner_page_free",
	 fsclfs_test_owner_page_free );

	FSCLFS_TEST_RUN(
	 "libfsclfs_owner_page_read",
	 fsclfs_test_owner_page_read );

	/* TODO: add tests for libfsclfs_owner_page_read_virtual_log_range_array */

	/* TODO: add tests for libfsclfs_owner_page_read_sector_mapping_array */

	/* TODO: add tests for libfsclfs_owner_page_read_scan_region */

	/* TODO: add tests for libfsclfs_owner_page_get_physical_block_offset */

#endif /* defined( __GNUC__ ) && !defined( LIBFSCLFS_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

