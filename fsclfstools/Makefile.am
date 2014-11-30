AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFUSN_CPPFLAGS@ \
	@LIBFTXF_CPPFLAGS@ \
	@LIBFTXR_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFSCLFS_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	fsclfsinfo \
	fsclfstest

fsclfsinfo_SOURCES = \
	fsclfsinfo.c \
	fsclfsoutput.c fsclfsoutput.h \
	fsclfstools_libbfio.h \
	fsclfstools_libcerror.h \
	fsclfstools_libclocale.h \
	fsclfstools_libcnotify.h \
	fsclfstools_libcstring.h \
	fsclfstools_libcsystem.h \
	fsclfstools_libfdatetime.h \
	fsclfstools_libfguid.h \
	fsclfstools_libfsclfs.h \
	fsclfstools_libftxf.h \
	fsclfstools_libftxr.h \
	fsclfstools_libuna.h

fsclfsinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

fsclfstest_SOURCES = \
	fsclfstest.c \
	fsclfsoutput.c fsclfsoutput.h \
	fsclfstools_libbfio.h \
	fsclfstools_libcerror.h \
	fsclfstools_libclocale.h \
	fsclfstools_libcnotify.h \
	fsclfstools_libcstring.h \
	fsclfstools_libcsystem.h \
	fsclfstools_libfdatetime.h \
	fsclfstools_libfguid.h \
	fsclfstools_libfsclfs.h \
	fsclfstools_libftxf.h \
	fsclfstools_libftxr.h \
	fsclfstools_libuna.h

fsclfstest_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFTXR_LIBADD@ \
	@LIBFTXF_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on fsclfsinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(fsclfsinfo_SOURCES)

