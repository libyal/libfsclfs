AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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
	@PTHREAD_CPPFLAGS@ \
	@LIBFSCLFS_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	fsclfsinfo \
	fsclfstest

fsclfsinfo_SOURCES = \
	fsclfsinfo.c \
	fsclfstools_getopt.c fsclfstools_getopt.h \
	fsclfstools_i18n.h \
	fsclfstools_libbfio.h \
	fsclfstools_libcerror.h \
	fsclfstools_libclocale.h \
	fsclfstools_libcnotify.h \
	fsclfstools_libfdatetime.h \
	fsclfstools_libfguid.h \
	fsclfstools_libfsclfs.h \
	fsclfstools_libftxf.h \
	fsclfstools_libftxr.h \
	fsclfstools_libuna.h \
	fsclfstools_output.c fsclfstools_output.h \
	fsclfstools_signal.c fsclfstools_signal.h \
	fsclfstools_unused.h \
	info_handle.c info_handle.h

fsclfsinfo_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

fsclfstest_SOURCES = \
	fsclfstest.c \
	fsclfstools_getopt.c fsclfstools_getopt.h \
	fsclfstools_i18n.h \
	fsclfstools_libbfio.h \
	fsclfstools_libcerror.h \
	fsclfstools_libclocale.h \
	fsclfstools_libcnotify.h \
	fsclfstools_libfdatetime.h \
	fsclfstools_libfguid.h \
	fsclfstools_libfsclfs.h \
	fsclfstools_libftxf.h \
	fsclfstools_libftxr.h \
	fsclfstools_libuna.h \
	fsclfstools_output.c fsclfstools_output.h \
	fsclfstools_signal.c fsclfstools_signal.h \
	fsclfstools_unused.h

fsclfstest_LDADD = \
	@LIBFTXR_LIBADD@ \
	@LIBFTXF_LIBADD@ \
	@LIBFUSN_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on fsclfsinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(fsclfsinfo_SOURCES)

