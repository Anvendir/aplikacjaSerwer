#
#	Makefile for dcmfg/include
#



SHELL = /bin/sh
srcdir = .
top_srcdir = ..
configdir = ../../config

include $(configdir)/Makefile.def


all:

install:
	$(configdir)/mkinstalldirs $(DESTDIR)$(includedir)/dcmtk/dcmfg
	for file in dcmtk/dcmfg/*.h ; do \
		$(INSTALL_DATA) $$file $(DESTDIR)$(includedir)/dcmtk/dcmfg ;\
	done

clean:
	rm -f $(TRASH)

distclean:
	rm -f $(DISTTRASH)
