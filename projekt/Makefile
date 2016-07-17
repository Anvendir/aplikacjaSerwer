commonPart = -c -std=c++14 -I ./include

dicomIncludesPath = -I ./dcmtk/config/include \
			     	-I ./dcmtk/dcmdata/include \
					-I ./dcmtk/oflog/include \
					-I ./dcmtk/ofstd/include \
			   		-I ./dcmtk/dcmimgle/include \
					-I ./dcmtk/dcmimage/include

dicomLibrariesPath = -L ./dcmtk/dcmimgle/libsrc \
					 -L ./dcmtk/dcmdata/libsrc \
					 -L ./dcmtk/dcmimage/libsrc \
					 -L ./dcmtk/oflog/libsrc \
					 -L ./dcmtk/ofstd/libsrc

dicomLibraries = -ldcmimage \
				 -ldcmimgle \
				 -ldcmdata \
				 -loflog \
				 -lofstd

staticLibraries = -lz -lpng $(dicomLibraries)

objects = Main.o \
		  Dispatcher.o \
		  ErrorHandler.o \
		  NetworkWrappers.o \
		  UnixWrappers.o \
		  Server.o \
		  ServerSendFileRequestHandler.o \
		  ServerSendFileListRequestHandler.o \
		  MessageConverter.o \
		  ServerParseDicomFileRequestHandler.o \
		  DicomTextInformationExtractor.o \
		  DicomBinaryInformationExtractor.o

Program : $(objects)
	g++ -std=c++14 $(dicomLibrariesPath) -pthread -o Program $(objects) $(staticLibraries)

Main.o : ./source/Main.cpp
	g++ $(commonPart) ./source/Main.cpp

Dispatcher.o : ./source/Dispatcher.cpp
	g++ $(commonPart) ./source/Dispatcher.cpp

ErrorHandler.o : ./source/ErrorHandler.cpp
	g++ $(commonPart) ./source/ErrorHandler.cpp

NetworkWrappers.o : ./source/NetworkWrappers.cpp
	g++ $(commonPart) ./source/NetworkWrappers.cpp

UnixWrappers.o : ./source/UnixWrappers.cpp
	g++ $(commonPart) ./source/UnixWrappers.cpp

Server.o : ./source/Server.cpp
	g++ $(commonPart) $(dicomIncludesPath) ./source/Server.cpp

ServerSendFileRequestHandler.o : ./source/ServerSendFileRequestHandler.cpp
	g++ $(commonPart) ./source/ServerSendFileRequestHandler.cpp

ServerSendFileListRequestHandler.o : ./source/ServerSendFileListRequestHandler.cpp
	g++ $(commonPart) ./source/ServerSendFileListRequestHandler.cpp

MessageConverter.o : ./source/MessageConverter.cpp
	g++ $(commonPart) ./source/MessageConverter.cpp

ServerParseDicomFileRequestHandler.o : ./source/ServerParseDicomFileRequestHandler.cpp
	g++ $(commonPart) $(dicomIncludesPath) ./source/ServerParseDicomFileRequestHandler.cpp

DicomTextInformationExtractor.o : ./source/DicomTextInformationExtractor.cpp
	g++ $(commonPart) $(dicomIncludesPath) ./source/DicomTextInformationExtractor.cpp

DicomBinaryInformationExtractor.o : ./source/DicomBinaryInformationExtractor.cpp
	g++ $(commonPart) $(dicomIncludesPath) ./source/DicomBinaryInformationExtractor.cpp

.PHONY : clean
clean:
		rm -f Program $(objects)
