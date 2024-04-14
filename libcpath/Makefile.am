AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCPATH_DLL_EXPORT@

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
	libcpath_libuna.h \
	libcpath_support.c libcpath_support.h \
	libcpath_system_string.c libcpath_system_string.h \
	libcpath_unused.h

libcpath_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@

libcpath_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libcpath_definitions.h.in \
	libcpath.rc \
	libcpath.rc.in

DISTCLEANFILES = \
	libcpath_definitions.h \
	libcpath.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libcpath ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcpath_la_SOURCES)

