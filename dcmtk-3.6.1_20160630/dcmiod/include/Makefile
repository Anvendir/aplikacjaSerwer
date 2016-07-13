#
#	Makefile for dcmiod/include
#



SHELL = /bin/sh
srcdir = .
top_srcdir = ..
configdir = ../../config

include $(configdir)/Makefile.def


all:

install:
	$(configdir)/mkinstalldirs $(DESTDIR)$(includedir)/dcmtk/dcmiod
	for file in dcmtk/dcmiod/*.h ; do \
		$(INSTALL_DATA) $$file $(DESTDIR)$(includedir)/dcmtk/dcmiod ;\
	done

clean:
	rm -f $(TRASH)

distclean:
	rm -f $(DISTTRASH)
