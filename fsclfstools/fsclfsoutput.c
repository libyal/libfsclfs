/*
 * Common output functions for the fsclfstools
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

#if defined( HAVE_LOCAL_LIBUNA )
#include <libuna_definitions.h>
#elif defined( HAVE_LIBUNA_H )
#include <libuna.h>
#endif

#if defined( HAVE_LOCAL_LIBBFIO )
#include <libbfio_definitions.h>
#elif defined( HAVE_LIBBFIO_H )
#include <libbfio.h>
#endif

#if defined( HAVE_LOCAL_LIBFDATETIME )
#include <libfdatetime_definitions.h>
#elif defined( HAVE_LIBFDATETIME_H )
#include <libfdatetime.h>
#endif

#if defined( HAVE_LOCAL_LIBFGUID )
#include <libfguid_definitions.h>
#elif defined( HAVE_LIBFGUID )
#include <libfguid.h>
#endif

#if defined( HAVE_LOCAL_LIBFTXF )
#include <libftxf_definitions.h>
#elif defined( HAVE_LIBFTXF )
#include <libftxf.h>
#endif

#include "fsclfsoutput.h"
#include "fsclfstools_libcerror.h"
#include "fsclfstools_libclocale.h"
#include "fsclfstools_libcnotify.h"
#include "fsclfstools_libcstring.h"
#include "fsclfstools_libcsystem.h"
#include "fsclfstools_libfsclfs.h"

/* Prints the copyright information
 */
void fsclfsoutput_copyright_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf(
	 stream,
	 "Copyright (c) 2010-2014, Joachim Metz <%s>.\n"
	 "This is free software; see the source for copying conditions. There is NO\n"
	 "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n",
	 PACKAGE_BUGREPORT );
}

/* Prints the version information
 */
void fsclfsoutput_version_fprint(
      FILE *stream,
      const char *program )
{
	if( stream == NULL )
	{
		return;
	}
	if( program == NULL )
	{
		return;
	}
        fprintf(
	 stream,
	 "%s %s\n\n",
         program,
	 LIBFSCLFS_VERSION_STRING );
}

/* Prints the detailed version information
 */
void fsclfsoutput_version_detailed_fprint(
      FILE *stream,
      const char *program )
{
	if( stream == NULL )
	{
		return;
	}
	if( program == NULL )
	{
		return;
	}
        fprintf(
	 stream,
	 "%s %s (libfsclfs %s",
         program,
	 LIBFSCLFS_VERSION_STRING,
	 LIBFSCLFS_VERSION_STRING );

	fprintf(
	 stream,
	 ", libuna %s",
	 LIBUNA_VERSION_STRING );

	fprintf(
	 stream,
	 ", libbfio %s",
	 LIBBFIO_VERSION_STRING );

	fprintf(
	 stream,
	 ", libfdatetime %s",
	 LIBFDATETIME_VERSION_STRING );

	fprintf(
	 stream,
	 ", libfguid %s",
	 LIBFGUID_VERSION_STRING );

	fprintf(
	 stream,
	 ", libftxf %s",
	 LIBFTXF_VERSION_STRING );

        fprintf(
	 stream,
	 ")\n\n" );
}

