/*
 * The libftxr header wrapper
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _FSCLFSTOOLS_LIBFTXR_H )
#define _FSCLFSTOOLS_LIBFTXR_H

#include <common.h>

/* Define HAVE_LOCAL_LIBFTXR for local use of libftxr
 */
#if defined( HAVE_LOCAL_LIBFTXR )

#include <libftxr_definitions.h>
#include <libftxr_record.h>
#include <libftxr_types.h>

#else

/* If libtool DLL support is enabled set LIBFTXR_DLL_IMPORT
 * before including libftxr.h
 */
#if defined( _WIN32 ) && defined( DLL_IMPORT )
#define LIBFTXR_DLL_IMPORT
#endif

#include <libftxr.h>

#endif

#endif

