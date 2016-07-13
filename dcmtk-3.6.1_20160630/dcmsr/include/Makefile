#
#	Makefile for dcmsr/include
#



SHELL = /bin/sh
srcdir = .
top_srcdir = ..
configdir = ../../config

include $(configdir)/Makefile.def


all:

install:
	for dir in dcmsr dcmsr/cmr dcmsr/codes ; do \
		$(configdir)/mkinstalldirs $(DESTDIR)$(includedir)/dcmtk/$$dir ;\
		for file in dcmtk/$$dir/*.h ; do \
			$(INSTALL_DATA) $$file $(DESTDIR)$(includedir)/dcmtk/$$dir ;\
		done \
	done

clean:
	rm -f $(TRASH)

distclean:
	rm -f $(DISTTRASH)
