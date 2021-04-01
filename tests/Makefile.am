AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	@LIBFGUID_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFSCLFS_DLL_IMPORT@

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_fsclfsinfo.sh

check_SCRIPTS = \
	test_fsclfsinfo.sh \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh \
	test_tools.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fsclfs_test_block \
	fsclfs_test_block_descriptor \
	fsclfs_test_container \
	fsclfs_test_container_descriptor \
	fsclfs_test_error \
	fsclfs_test_io_handle \
	fsclfs_test_log_range \
	fsclfs_test_notify \
	fsclfs_test_owner_page \
	fsclfs_test_record \
	fsclfs_test_record_value \
	fsclfs_test_store \
	fsclfs_test_stream \
	fsclfs_test_stream_descriptor \
	fsclfs_test_support \
	fsclfs_test_tools_info_handle \
	fsclfs_test_tools_output \
	fsclfs_test_tools_signal

fsclfs_test_block_SOURCES = \
	fsclfs_test_block.c \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_unused.h

fsclfs_test_block_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_block_descriptor_SOURCES = \
	fsclfs_test_block_descriptor.c \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_unused.h

fsclfs_test_block_descriptor_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_container_SOURCES = \
	fsclfs_test_container.c \
	fsclfs_test_libcerror.h \
	fsclfs_test_libclocale.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_libuna.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_unused.h

fsclfs_test_container_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_container_descriptor_SOURCES = \
	fsclfs_test_container_descriptor.c \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_unused.h

fsclfs_test_container_descriptor_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_error_SOURCES = \
	fsclfs_test_error.c \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_unused.h

fsclfs_test_error_LDADD = \
	../libfsclfs/libfsclfs.la

fsclfs_test_io_handle_SOURCES = \
	fsclfs_test_io_handle.c \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_unused.h

fsclfs_test_io_handle_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_log_range_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_log_range.c \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_unused.h

fsclfs_test_log_range_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_notify_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_notify.c \
	fsclfs_test_unused.h

fsclfs_test_notify_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_owner_page_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_owner_page.c \
	fsclfs_test_unused.h

fsclfs_test_owner_page_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

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

fsclfs_test_record_value_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_record_value.c \
	fsclfs_test_unused.h

fsclfs_test_record_value_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_store_SOURCES = \
	fsclfs_test_getopt.c fsclfs_test_getopt.h \
	fsclfs_test_libcerror.h \
	fsclfs_test_libclocale.h \
	fsclfs_test_libcnotify.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_libuna.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_store.c

fsclfs_test_store_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

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

fsclfs_test_stream_descriptor_SOURCES = \
	fsclfs_test_libcerror.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_stream_descriptor.c \
	fsclfs_test_unused.h

fsclfs_test_stream_descriptor_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_support_SOURCES = \
	fsclfs_test_functions.c fsclfs_test_functions.h \
	fsclfs_test_getopt.c fsclfs_test_getopt.h \
	fsclfs_test_libbfio.h \
	fsclfs_test_libcerror.h \
	fsclfs_test_libclocale.h \
	fsclfs_test_libcnotify.h \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_libuna.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_support.c \
	fsclfs_test_unused.h

fsclfs_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_tools_info_handle_SOURCES = \
	../fsclfstools/info_handle.c ../fsclfstools/info_handle.h \
	fsclfs_test_libcerror.h \
	fsclfs_test_macros.h \
	fsclfs_test_memory.c fsclfs_test_memory.h \
	fsclfs_test_tools_info_handle.c \
	fsclfs_test_unused.h

fsclfs_test_tools_info_handle_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_tools_output_SOURCES = \
	../fsclfstools/fsclfstools_output.c ../fsclfstools/fsclfstools_output.h \
	fsclfs_test_libcerror.h \
	fsclfs_test_macros.h \
	fsclfs_test_tools_output.c \
	fsclfs_test_unused.h

fsclfs_test_tools_output_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

fsclfs_test_tools_signal_SOURCES = \
	../fsclfstools/fsclfstools_signal.c ../fsclfstools/fsclfstools_signal.h \
	fsclfs_test_libcerror.h \
	fsclfs_test_macros.h \
	fsclfs_test_tools_signal.c \
	fsclfs_test_unused.h

fsclfs_test_tools_signal_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

