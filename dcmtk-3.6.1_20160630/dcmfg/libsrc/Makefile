#
#	Makefile for dcmfg/libsrc
#



SHELL = /bin/sh
VPATH = ../include:../../config/include
srcdir = .
top_srcdir = ..
configdir = ../../config

include $(configdir)/Makefile.def

ofstddir = $(top_srcdir)/../ofstd
oflogdir = $(top_srcdir)/../oflog
dcmdatadir = $(top_srcdir)/../dcmdata
dcmioddir = $(top_srcdir)/../dcmiod

LOCALINCLUDES = -I$(ofstddir)/include -I$(oflogdir)/include \
	-I$(dcmdatadir)/include -I$(dcmioddir)/include

LOCALDEFS =

objs = fgderimg.o fgframevoilut.o fgpixmsr.o fgplanpo.o fgseg.o stackinterface.o \
	fgbase.o fgfact.o fgimagedatatype.o fgplanor.o fgplanposvol.o fgtypes.o \
	fg.o fgfracon.o fginterface.o fgplanorvol.o fgrealworldvaluemapping.o \
	fgusimagedescription.o stack.o


library = libdcmfg.$(LIBEXT)


all: $(library)

install: $(library)
	$(configdir)/mkinstalldirs $(DESTDIR)$(libdir)
	$(INSTALL_DATA) $(library) $(DESTDIR)$(libdir)/$(library)
	$(RANLIB) $(DESTDIR)$(libdir)/$(library)


$(library): $(objs)
	$(AR) $(ARFLAGS) $@ $(objs)
	$(RANLIB) $@


clean:
	rm -f $(objs) $(library) $(TRASH)

distclean:
	rm -f $(objs) $(library) $(DISTTRASH)


dependencies:
	$(CXX) -MM $(defines) $(includes) $(CPPFLAGS) $(CXXFLAGS) *.cc  > $(DEP)

include $(DEP)
