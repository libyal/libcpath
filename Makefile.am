ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcerror \
	libclocale \
	libcsplit \
	libuna \
	libcpath \
	po \
	manuals \
	tests \
	msvscpp

DPKG_FILES = \
	dpkg/changelog \
	dpkg/changelog.in \
	dpkg/compat \
	dpkg/control \
	dpkg/copyright \
	dpkg/rules \
	dpkg/libcpath-dev.install \
	dpkg/libcpath.install \
	dpkg/source/format

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libcpath.pc.in

SPEC_FILES = \
	libcpath.spec \
	libcpath.spec.in

EXTRA_DIST = \
	$(DPKG_FILES) \
	$(GETTEXT_FILES) \
	$(PKGCONFIG_FILES) \
	$(SPEC_FILES)

DISTCLEANFILES = \
	config.status \
	config.cache \
	config.log \
	libcpath.pc \
	libcpath.spec \
	Makefile \
	Makefile.in \
	po/Makevars

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libcpath.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcerror && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libclocale && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcsplit && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcpath && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/po && $(MAKE) $(AM_MAKEFLAGS)

