include_HEADERS = \
	libfsclfs.h

pkginclude_HEADERS = \
	libfsclfs/codepage.h \
	libfsclfs/definitions.h \
	libfsclfs/error.h \
	libfsclfs/extern.h \
	libfsclfs/features.h \
	libfsclfs/types.h

EXTRA_DIST = \
	libfsclfs.h.in \
	libfsclfs/definitions.h.in \
	libfsclfs/features.h.in \
	libfsclfs/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libfsclfs.h
	-rm -f libfsclfs/definitions.h
	-rm -f libfsclfs/features.h
	-rm -f libfsclfs/types.h
	-rm -f Makefile

