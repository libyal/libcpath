AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCPATH_DLL_IMPORT@

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cpath_test_error \
	cpath_test_path \
	cpath_test_support \
	cpath_test_system_string

cpath_test_error_SOURCES = \
	cpath_test_error.c \
	cpath_test_libcpath.h \
	cpath_test_macros.h \
	cpath_test_unused.h

cpath_test_error_LDADD = \
	../libcpath/libcpath.la

cpath_test_path_SOURCES = \
	cpath_test_libcerror.h \
	cpath_test_libcpath.h \
	cpath_test_macros.h \
	cpath_test_memory.c cpath_test_memory.h \
	cpath_test_path.c \
	cpath_test_unused.h

cpath_test_path_LDADD = \
	../libcpath/libcpath.la \
	@LIBCERROR_LIBADD@

cpath_test_support_SOURCES = \
	cpath_test_libcerror.h \
	cpath_test_libcpath.h \
	cpath_test_macros.h \
	cpath_test_support.c \
	cpath_test_unused.h

cpath_test_support_LDADD = \
	../libcpath/libcpath.la \
	@LIBCERROR_LIBADD@

cpath_test_system_string_SOURCES = \
	cpath_test_libcerror.h \
	cpath_test_libcpath.h \
	cpath_test_macros.h \
	cpath_test_system_string.c \
	cpath_test_unused.h

cpath_test_system_string_LDADD = \
	../libcpath/libcpath.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

