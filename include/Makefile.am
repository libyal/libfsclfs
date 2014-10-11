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
	/bin/rm -f libfsclfs.h
	/bin/rm -f libfsclfs/definitions.h
	/bin/rm -f libfsclfs/features.h
	/bin/rm -f libfsclfs/types.h
	/bin/rm -f Makefile

