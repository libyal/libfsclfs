/*
 * Codepage definitions for libfsclfs
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSCLFS_CODEPAGE_H )
#define _LIBFSCLFS_CODEPAGE_H

#include <libfsclfs/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBFSCLFS_CODEPAGES
{
	LIBFSCLFS_CODEPAGE_ASCII			= 20127,

	LIBFSCLFS_CODEPAGE_ISO_8859_1			= 28591,
	LIBFSCLFS_CODEPAGE_ISO_8859_2			= 28592,
	LIBFSCLFS_CODEPAGE_ISO_8859_3			= 28593,
	LIBFSCLFS_CODEPAGE_ISO_8859_4			= 28594,
	LIBFSCLFS_CODEPAGE_ISO_8859_5			= 28595,
	LIBFSCLFS_CODEPAGE_ISO_8859_6			= 28596,
	LIBFSCLFS_CODEPAGE_ISO_8859_7			= 28597,
	LIBFSCLFS_CODEPAGE_ISO_8859_8			= 28598,
	LIBFSCLFS_CODEPAGE_ISO_8859_9			= 28599,
	LIBFSCLFS_CODEPAGE_ISO_8859_10			= 28600,
	LIBFSCLFS_CODEPAGE_ISO_8859_11			= 28601,
	LIBFSCLFS_CODEPAGE_ISO_8859_13			= 28603,
	LIBFSCLFS_CODEPAGE_ISO_8859_14			= 28604,
	LIBFSCLFS_CODEPAGE_ISO_8859_15			= 28605,
	LIBFSCLFS_CODEPAGE_ISO_8859_16			= 28606,

	LIBFSCLFS_CODEPAGE_KOI8_R			= 20866,
	LIBFSCLFS_CODEPAGE_KOI8_U			= 21866,

	LIBFSCLFS_CODEPAGE_WINDOWS_874			= 874,
	LIBFSCLFS_CODEPAGE_WINDOWS_932			= 932,
	LIBFSCLFS_CODEPAGE_WINDOWS_936			= 936,
	LIBFSCLFS_CODEPAGE_WINDOWS_949			= 949,
	LIBFSCLFS_CODEPAGE_WINDOWS_950			= 950,
	LIBFSCLFS_CODEPAGE_WINDOWS_1250			= 1250,
	LIBFSCLFS_CODEPAGE_WINDOWS_1251			= 1251,
	LIBFSCLFS_CODEPAGE_WINDOWS_1252			= 1252,
	LIBFSCLFS_CODEPAGE_WINDOWS_1253			= 1253,
	LIBFSCLFS_CODEPAGE_WINDOWS_1254			= 1254,
	LIBFSCLFS_CODEPAGE_WINDOWS_1255			= 1255,
	LIBFSCLFS_CODEPAGE_WINDOWS_1256			= 1256,
	LIBFSCLFS_CODEPAGE_WINDOWS_1257			= 1257,
	LIBFSCLFS_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBFSCLFS_CODEPAGE_US_ASCII			LIBFSCLFS_CODEPAGE_ASCII

#define LIBFSCLFS_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBFSCLFS_CODEPAGE_ISO_8859_1
#define LIBFSCLFS_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBFSCLFS_CODEPAGE_ISO_8859_2
#define LIBFSCLFS_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBFSCLFS_CODEPAGE_ISO_8859_3
#define LIBFSCLFS_CODEPAGE_ISO_NORTH_EUROPEAN		LIBFSCLFS_CODEPAGE_ISO_8859_4
#define LIBFSCLFS_CODEPAGE_ISO_CYRILLIC			LIBFSCLFS_CODEPAGE_ISO_8859_5
#define LIBFSCLFS_CODEPAGE_ISO_ARABIC			LIBFSCLFS_CODEPAGE_ISO_8859_6
#define LIBFSCLFS_CODEPAGE_ISO_GREEK			LIBFSCLFS_CODEPAGE_ISO_8859_7
#define LIBFSCLFS_CODEPAGE_ISO_HEBREW			LIBFSCLFS_CODEPAGE_ISO_8859_8
#define LIBFSCLFS_CODEPAGE_ISO_TURKISH			LIBFSCLFS_CODEPAGE_ISO_8859_9
#define LIBFSCLFS_CODEPAGE_ISO_NORDIC			LIBFSCLFS_CODEPAGE_ISO_8859_10
#define LIBFSCLFS_CODEPAGE_ISO_THAI			LIBFSCLFS_CODEPAGE_ISO_8859_11
#define LIBFSCLFS_CODEPAGE_ISO_BALTIC			LIBFSCLFS_CODEPAGE_ISO_8859_13
#define LIBFSCLFS_CODEPAGE_ISO_CELTIC			LIBFSCLFS_CODEPAGE_ISO_8859_14

#define LIBFSCLFS_CODEPAGE_ISO_LATIN_1			LIBFSCLFS_CODEPAGE_ISO_8859_1
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_2			LIBFSCLFS_CODEPAGE_ISO_8859_2
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_3			LIBFSCLFS_CODEPAGE_ISO_8859_3
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_4			LIBFSCLFS_CODEPAGE_ISO_8859_4
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_5			LIBFSCLFS_CODEPAGE_ISO_8859_9
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_6			LIBFSCLFS_CODEPAGE_ISO_8859_10
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_7			LIBFSCLFS_CODEPAGE_ISO_8859_13
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_8			LIBFSCLFS_CODEPAGE_ISO_8859_14
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_9			LIBFSCLFS_CODEPAGE_ISO_8859_15
#define LIBFSCLFS_CODEPAGE_ISO_LATIN_10			LIBFSCLFS_CODEPAGE_ISO_8859_16

#define LIBFSCLFS_CODEPAGE_KOI8_RUSSIAN			LIBFSCLFS_CODEPAGE_KOI8_R
#define LIBFSCLFS_CODEPAGE_KOI8_UKRAINIAN		LIBFSCLFS_CODEPAGE_KOI8_U

#define LIBFSCLFS_CODEPAGE_WINDOWS_THAI			LIBFSCLFS_CODEPAGE_WINDOWS_874
#define LIBFSCLFS_CODEPAGE_WINDOWS_JAPANESE		LIBFSCLFS_CODEPAGE_WINDOWS_932
#define LIBFSCLFS_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBFSCLFS_CODEPAGE_WINDOWS_936
#define LIBFSCLFS_CODEPAGE_WINDOWS_KOREAN		LIBFSCLFS_CODEPAGE_WINDOWS_949
#define LIBFSCLFS_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBFSCLFS_CODEPAGE_WINDOWS_950
#define LIBFSCLFS_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBFSCLFS_CODEPAGE_WINDOWS_1250
#define LIBFSCLFS_CODEPAGE_WINDOWS_CYRILLIC		LIBFSCLFS_CODEPAGE_WINDOWS_1251
#define LIBFSCLFS_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBFSCLFS_CODEPAGE_WINDOWS_1252
#define LIBFSCLFS_CODEPAGE_WINDOWS_GREEK		LIBFSCLFS_CODEPAGE_WINDOWS_1253
#define LIBFSCLFS_CODEPAGE_WINDOWS_TURKISH		LIBFSCLFS_CODEPAGE_WINDOWS_1254
#define LIBFSCLFS_CODEPAGE_WINDOWS_HEBREW		LIBFSCLFS_CODEPAGE_WINDOWS_1255
#define LIBFSCLFS_CODEPAGE_WINDOWS_ARABIC		LIBFSCLFS_CODEPAGE_WINDOWS_1256
#define LIBFSCLFS_CODEPAGE_WINDOWS_BALTIC		LIBFSCLFS_CODEPAGE_WINDOWS_1257
#define LIBFSCLFS_CODEPAGE_WINDOWS_VIETNAMESE		LIBFSCLFS_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSCLFS_CODEPAGE_H ) */

