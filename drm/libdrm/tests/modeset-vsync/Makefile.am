AM_CFLAGS = \
	$(WARN_CFLAGS)\
	-fvisibility=hidden \
	-I$(top_srcdir)/include/drm \
	-I$(top_srcdir)/libkms/ \
	-I$(top_srcdir)/tests/ \
	-I$(top_srcdir)

if HAVE_INSTALL_TESTS
bin_PROGRAMS = \
	modeset-vsync
else
noinst_PROGRAMS = \
	modeset-vsync
endif

modeset-vsync_SOURCES = \
	modeset-vsync.c

modeset-vsync_LDADD = \
	$(top_builddir)/tests/util/libutil.la \
	$(top_builddir)/libkms/libkms.la \
	$(top_builddir)/libdrm.la

run: modeset-vsync
	./modeset-vsync
