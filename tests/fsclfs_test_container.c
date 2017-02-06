/*
 * Library container type test program
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

#include "../libfsclfs/libfsclfs_container.h"

/* Tests the libfsclfs_container_free function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_container_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsclfs_container_free(
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

#if defined( __GNUC__ )

	/* TODO: add tests for libfsclfs_container_initialize */

#endif /* defined( __GNUC__ ) */

	FSCLFS_TEST_RUN(
	 "libfsclfs_container_free",
	 fsclfs_test_container_free );

#if defined( __GNUC__ )

	/* TODO: add tests for libfsclfs_container_get_size */

	/* TODO: add tests for libfsclfs_container_get_utf8_name_size */

	/* TODO: add tests for libfsclfs_container_get_utf8_name */

	/* TODO: add tests for libfsclfs_container_get_utf16_name_size */

	/* TODO: add tests for libfsclfs_container_get_utf16_name */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

