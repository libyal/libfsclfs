ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcerror \
	libcthreads \
	libcdata \
	libclocale \
	libcnotify \
	libcsplit \
	libuna \
	libcfile \
	libcpath \
	libbfio \
	libfcache \
	libfdata \
	libfdatetime \
	libfguid \
	libfwnt \
	libfsclfs \
	libfusn \
	libftxf \
	libftxr \
	fsclfstools \
	po \
	manuals \
	tests \
	ossfuzz \
	msvscpp

DPKG_FILES = \
	dpkg/changelog \
	dpkg/changelog.in \
	dpkg/compat \
	dpkg/control \
	dpkg/copyright \
	dpkg/rules \
	dpkg/libfsclfs-dev.install \
	dpkg/libfsclfs.install \
	dpkg/libfsclfs-tools.install \
	dpkg/source/format

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libfsclfs.pc.in

SPEC_FILES = \
	libfsclfs.spec \
	libfsclfs.spec.in

EXTRA_DIST = \
	$(DPKG_FILES) \
	$(GETTEXT_FILES) \
	$(PKGCONFIG_FILES) \
	$(SPEC_FILES)

DISTCLEANFILES = \
	config.status \
	config.cache \
	config.log \
	libfsclfs.pc \
	libfsclfs.spec \
	Makefile \
	Makefile.in \
	po/Makevars

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libfsclfs.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	(cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcerror && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcthreads && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcdata && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libclocale && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcnotify && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcsplit && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcfile && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcpath && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libbfio && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfcache && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfdata && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfdatetime && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfguid && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfwnt && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfsclfs && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/po && $(MAKE) $(AM_MAKEFLAGS))

