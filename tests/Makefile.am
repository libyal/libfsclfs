AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFSCLFS_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fsclfs_test_container \
	fsclfs_test_error \
	fsclfs_test_record \
	fsclfs_test_store \
	fsclfs_test_stream \
	fsclfs_test_support

fsclfs_test_container_SOURCES = \
	fsclfs_test_container.c \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_unused.h

fsclfs_test_container_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_error_SOURCES = \
	fsclfs_test_error.c \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_unused.h

fsclfs_test_error_LDADD = \
	../libfsclfs/libfsclfs.la

fsclfs_test_record_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_record.c \
	fsclfs_test_unused.h

fsclfs_test_record_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_store_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libclocale.h \
	fsclfs_test_libcsystem.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_libuna.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_store.c \
	fsclfs_test_unused.h

fsclfs_test_store_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_stream_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_stream.c \
	fsclfs_test_unused.h

fsclfs_test_stream_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_support_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_support.c \
	fsclfs_test_unused.h

fsclfs_test_support_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

