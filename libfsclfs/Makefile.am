AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@

lib_LTLIBRARIES = libfsclfs.la

libfsclfs_la_SOURCES = \
	libfsclfs.c \
	libfsclfs_block.c libfsclfs_block.h \
	libfsclfs_block_descriptor.c libfsclfs_block_descriptor.h \
	libfsclfs_container.c libfsclfs_container.h \
	libfsclfs_container_descriptor.c libfsclfs_container_descriptor.h \
	libfsclfs_debug.c libfsclfs_debug.h \
	libfsclfs_definitions.h \
	libfsclfs_error.c libfsclfs_error.h \
	libfsclfs_extern.h \
	libfsclfs_io_handle.c libfsclfs_io_handle.h \
	libfsclfs_libbfio.h \
	libfsclfs_libcdata.h \
	libfsclfs_libcerror.h \
	libfsclfs_libclocale.h \
	libfsclfs_libcnotify.h \
	libfsclfs_libcstring.h \
	libfsclfs_libfguid.h \
	libfsclfs_libuna.h \
	libfsclfs_log_range.c libfsclfs_log_range.h \
	libfsclfs_notify.c libfsclfs_notify.h \
	libfsclfs_owner_page.c libfsclfs_owner_page.h \
	libfsclfs_record.c libfsclfs_record.h \
	libfsclfs_record_value.c libfsclfs_record_value.h \
	libfsclfs_store.c libfsclfs_store.h \
	libfsclfs_stream.c libfsclfs_stream.h \
	libfsclfs_stream_descriptor.c libfsclfs_stream_descriptor.h \
	libfsclfs_support.c libfsclfs_support.h \
	libfsclfs_types.h \
	libfsclfs_unused.h \
	fsclfs_base_log_record.h \
	fsclfs_block.h \
	fsclfs_record.h

libfsclfs_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

libfsclfs_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libfsclfs_definitions.h.in \
	libfsclfs.rc \
	libfsclfs.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libfsclfs_definitions.h
	/bin/rm -f libfsclfs.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libfsclfs ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libfsclfs_la_SOURCES)

