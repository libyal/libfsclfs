AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFSCLFS_DLL_IMPORT@

TESTS = \
	test_api_functions.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fsclfs_test_get_version

fsclfs_test_get_version_SOURCES = \
	fsclfs_test_libfsclfs.h \
	fsclfs_test_libcstring.h \
	fsclfs_test_get_version.c \
	fsclfs_test_unused.h

fsclfs_test_get_version_LDADD = \
	../libfsclfs/libfsclfs.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

