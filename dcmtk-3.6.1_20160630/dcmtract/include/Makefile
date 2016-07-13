#
#	Makefile for dcmtract/include
#



SHELL = /bin/sh
srcdir = .
top_srcdir = ..
configdir = ../../config

include $(configdir)/Makefile.def


all:

install:
	$(configdir)/mkinstalldirs $(DESTDIR)$(includedir)/dcmtk/dcmtract
	for file in dcmtk/dcmtract/*.h ; do \
		$(INSTALL_DATA) $$file $(DESTDIR)$(includedir)/dcmtk/dcmtract ;\
	done

clean:
	rm -f $(TRASH)

distclean:
	rm -f $(DISTTRASH)
