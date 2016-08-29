AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCPATH_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_path.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_path.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cpath_test_error \
	cpath_test_get_version \
	cpath_test_path

cpath_test_error_SOURCES = \
	cpath_test_error.c \
	cpath_test_libcpath.h \
	cpath_test_libcstring.h \
	cpath_test_macros.h \
	cpath_test_unused.h

cpath_test_error_LDADD = \
	../libcpath/libcpath.la \
	@LIBCSTRING_LIBADD@

cpath_test_get_version_SOURCES = \
	cpath_test_get_version.c \
	cpath_test_libcpath.h \
	cpath_test_libcstring.h \
	cpath_test_macros.h \
	cpath_test_unused.h

cpath_test_get_version_LDADD = \
	../libcpath/libcpath.la \
	@LIBCSTRING_LIBADD@

cpath_test_path_SOURCES = \
	cpath_test_libcerror.h \
	cpath_test_libcpath.h \
	cpath_test_libcstring.h \
	cpath_test_macros.h \
	cpath_test_memory.c cpath_test_memory.h \
	cpath_test_path.c \
	cpath_test_unused.h

cpath_test_path_LDADD = \
	../libcpath/libcpath.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

