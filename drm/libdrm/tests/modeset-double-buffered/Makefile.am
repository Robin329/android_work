AM_CFLAGS = \
	$(WARN_CFLAGS)\
	-fvisibility=hidden \
	-I$(top_srcdir)/include/drm \
	-I$(top_srcdir)/libkms/ \
	-I$(top_srcdir)/tests/ \
	-I$(top_srcdir)

if HAVE_INSTALL_TESTS
bin_PROGRAMS = \
	modeset-double-buffered
else
noinst_PROGRAMS = \
	modeset-double-buffered
endif

modeset-double-buffered_SOURCES = \
	modeset-double-buffered.c

modeset-double-buffered_LDADD = \
	$(top_builddir)/tests/util/libutil.la \
	$(top_builddir)/libkms/libkms.la \
	$(top_builddir)/libdrm.la

run: modeset-double-buffered
	./modeset-double-buffered
