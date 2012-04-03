include_HEADERS = \
	libcpath.h

pkginclude_HEADERS = \
	libcpath/codepage.h \
	libcpath/definitions.h \
	libcpath/error.h \
	libcpath/extern.h \
	libcpath/features.h \
	libcpath/types.h

EXTRA_DIST = \
	libcpath.h.in \
	libcpath/definitions.h.in \
	libcpath/features.h.in \
	libcpath/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libcpath.h
	/bin/rm -f libcpath/definitions.h
	/bin/rm -f libcpath/features.h
	/bin/rm -f libcpath/types.h
	/bin/rm -f Makefile

