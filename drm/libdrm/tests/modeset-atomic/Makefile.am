AM_CFLAGS = \
	$(WARN_CFLAGS)\
	-fvisibility=hidden \
	-I$(top_srcdir)/include/drm \
	-I$(top_srcdir)/libkms/ \
	-I$(top_srcdir)/tests/ \
	-I$(top_srcdir)

if HAVE_INSTALL_TESTS
bin_PROGRAMS = \
	modeset-atomic
else
noinst_PROGRAMS = \
	modeset-atomic
endif

modeset-atomic_SOURCES = \
	modeset-atomic.c

modeset-atomic_LDADD = \
	$(top_builddir)/tests/util/libutil.la \
	$(top_builddir)/libkms/libkms.la \
	$(top_builddir)/libdrm.la

run: modeset-atomic
	./modeset-atomic
