AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = libcpath.la

libcpath_la_SOURCES = \
	libcpath.c \
	libcpath_definitions.h \
	libcpath_error.c libcpath_error.h \
	libcpath_extern.h \
	libcpath_path.c libcpath_path.h \
	libcpath_libcerror.h \
	libcpath_libclocale.h \
	libcpath_libcsplit.h \
	libcpath_libcstring.h \
	libcpath_libuna.h \
	libcpath_support.c libcpath_support.h \
	libcpath_unused.h

libcpath_la_LIBADD  = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@

libcpath_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libcpath_definitions.h.in \
	libcpath.rc \
	libcpath.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libcpath_definitions.h
	/bin/rm -f libcpath.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libcpath ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcpath_la_SOURCES) 

