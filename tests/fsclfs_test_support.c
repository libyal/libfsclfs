/*
 * Library support functions test program
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsclfs_test_libcerror.h"
#include "fsclfs_test_libfsclfs.h"
#include "fsclfs_test_macros.h"
#include "fsclfs_test_unused.h"

/* Tests the libfsclfs_get_version function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = libfsclfs_get_version();

	result = narrow_string_compare(
	          version_string,
	          LIBFSCLFS_VERSION_STRING,
	          9 );

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libfsclfs_get_access_flags_read function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_get_access_flags_read(
     void )
{
	int access_flags = 0;

	access_flags = libfsclfs_get_access_flags_read();

	FSCLFS_TEST_ASSERT_EQUAL_INT(
	 "access_flags",
	 access_flags,
	 LIBFSCLFS_ACCESS_FLAG_READ );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libfsclfs_get_codepage function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_get_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	result = libfsclfs_get_codepage(
	          &codepage,
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
	result = libfsclfs_get_codepage(
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

/* Tests the libfsclfs_set_codepage function
 * Returns 1 if successful or 0 if not
 */
int fsclfs_test_set_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libfsclfs_set_codepage(
	          0,
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
	result = libfsclfs_set_codepage(
	          -1,
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

	FSCLFS_TEST_RUN(
	 "libfsclfs_get_version",
	 fsclfs_test_get_version );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

