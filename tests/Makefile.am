AUTOMAKE_OPTIONS = subdir-objects

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
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFUSN_CPPFLAGS@ \
	@LIBFTXF_CPPFLAGS@ \
	@LIBFTXR_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFSCLFS_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

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
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

fsclfs_test_tools_signal_SOURCES = \
	../fsclfstools/fsclfstools_signal.c ../fsclfstools/fsclfstools_signal.h \
	fsclfs_test_libcerror.h \
	fsclfs_test_macros.h \
	fsclfs_test_tools_signal.c \
	fsclfs_test_unused.h

fsclfs_test_tools_signal_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCERROR_LIBADD@

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libfsclfs.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libfsclfs

test_inputs_fsclfsinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) fsclfsinfo

test_library: package.m4 test_inputs_libfsclfs.at test_library.at test_macros.at

test_manpages: package.m4 test_manpages.at

test_tools: package.m4 test_inputs_fsclfsinfo.at test_macros.at test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

