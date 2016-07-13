#
#	Makefile for dcmseg/include
#



SHELL = /bin/sh
srcdir = .
top_srcdir = ..
configdir = ../../config

include $(configdir)/Makefile.def


all:

install:
	$(configdir)/mkinstalldirs $(DESTDIR)$(includedir)/dcmtk/dcmseg
	for file in dcmtk/dcmseg/*.h ; do \
		$(INSTALL_DATA) $$file $(DESTDIR)$(includedir)/dcmtk/dcmseg ;\
	done

clean:
	rm -f $(TRASH)

distclean:
	rm -f $(DISTTRASH)
