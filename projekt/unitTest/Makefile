commonPartSrc = -c -std=c++14 -I ../include
gtestIncludes = -I ./googleTestRepo/googletest/include -I ./googleTestRepo/googlemock/include
commonPartUt = $(commonPartSrc) -pthread $(gtestIncludes) -I ./mocks

dicomIncludesPath = -I ../dcmtk/config/include \
			     	-I ../dcmtk/dcmdata/include \
					-I ../dcmtk/oflog/include \
					-I ../dcmtk/ofstd/include \
			   		-I ../dcmtk/dcmimgle/include

dicomLibrariesPath = -L ../dcmtk/dcmimgle/libsrc \
					 -L ../dcmtk/dcmdata/libsrc \
					 -L ../dcmtk/oflog/libsrc \
					 -L ../dcmtk/ofstd/libsrc

dicomLibraries = -ldcmimgle \
				 -ldcmdata \
				 -loflog \
				 -lofstd

gtestLibraries = -lgtest -lgmock

staticLibraries = -lz $(dicomLibraries) $(gtestLibraries)

staticLibriariesPath = -L ./libs $(dicomLibrariesPath)

objects = Main.o \
		  Dispatcher.o DispatcherTestSuite.o \
		  ErrorHandler.o ErrorHandlerTestSuite.o \
		  NetworkWrappers.o NetworkWrappersTestSuite.o \
		  UnixWrappers.o UnixWrappersTestSuite.o \
		  Server.o ServerTestSuite.o \
		  ServerSendFileRequestHandler.o ServerSendFileRequestHandlerTestSuite.o \
	      ServerSendFileListRequestHandler.o ServerSendFileListRequestHandlerTestSuite.o \
		  MessageConverter.o MessageConverterTestSuite.o \
		  ServerParseDicomFileRequestHandler.o ServerParseDicomFileRequestHandlerTestSuite.o \
		  DicomTextInformationExtractor.o DicomTextInformationExtractorTestSuite.o

UnitTests : $(objects)
	g++ -std=c++14 -pthread $(gtestIncludes) $(staticLibriariesPath) -o UnitTests $(objects) $(staticLibraries)

Main.o : ./test_modules/Main.cpp
	g++ $(commonPartUt) ./test_modules/Main.cpp

Dispatcher.o : ../source/Dispatcher.cpp
	g++ $(commonPartSrc) ../source/Dispatcher.cpp

DispatcherTestSuite.o : ./test_modules/DispatcherTestSuite.cpp
	g++ $(commonPartUt) ./test_modules/DispatcherTestSuite.cpp

ErrorHandler.o : ../source/ErrorHandler.cpp
	g++ $(commonPartSrc) ../source/ErrorHandler.cpp

ErrorHandlerTestSuite.o : ./test_modules/ErrorHandlerTestSuite.cpp
	g++ $(commonPartUt) ./test_modules/ErrorHandlerTestSuite.cpp

NetworkWrappers.o : ../source/NetworkWrappers.cpp
	g++ $(commonPartSrc) ../source/NetworkWrappers.cpp

NetworkWrappersTestSuite.o : ./test_modules/NetworkWrappersTestSuite.cpp
	g++ $(commonPartUt) ./test_modules/NetworkWrappersTestSuite.cpp

UnixWrappers.o : ../source/UnixWrappers.cpp
	g++ $(commonPartSrc) ../source/UnixWrappers.cpp

UnixWrappersTestSuite.o : ./test_modules/UnixWrappersTestSuite.cpp
	g++ $(commonPartUt) ./test_modules/UnixWrappersTestSuite.cpp

Server.o : ../source/Server.cpp
	g++ $(commonPartSrc) $(dicomIncludesPath) ../source/Server.cpp

ServerTestSuite.o : ./test_modules/ServerTestSuite.cpp
	g++ $(commonPartUt) ./test_modules/ServerTestSuite.cpp

ServerSendFileRequestHandler.o : ../source/ServerSendFileRequestHandler.cpp
	g++ $(commonPartSrc) ../source/ServerSendFileRequestHandler.cpp

ServerSendFileRequestHandlerTestSuite.o : ./test_modules/ServerSendFileRequestHandlerTestSuite.cpp
	g++ $(commonPartUt) ./test_modules/ServerSendFileRequestHandlerTestSuite.cpp

ServerSendFileListRequestHandler.o : ../source/ServerSendFileListRequestHandler.cpp
	g++ $(commonPartSrc) ../source/ServerSendFileListRequestHandler.cpp

ServerSendFileListRequestHandlerTestSuite.o : ./test_modules/ServerSendFileListRequestHandlerTestSuite.cpp
	g++ $(commonPartUt) ./test_modules/ServerSendFileListRequestHandlerTestSuite.cpp

MessageConverter.o : ../source/MessageConverter.cpp
	g++ $(commonPartSrc) ../source/MessageConverter.cpp

MessageConverterTestSuite.o : ./test_modules/MessageConverterTestSuite.cpp
	g++ $(commonPartUt) ./test_modules/MessageConverterTestSuite.cpp

ServerParseDicomFileRequestHandler.o : ../source/ServerParseDicomFileRequestHandler.cpp
	g++ $(commonPartSrc) $(dicomIncludesPath) ../source/ServerParseDicomFileRequestHandler.cpp

ServerParseDicomFileRequestHandlerTestSuite.o : ./test_modules/ServerParseDicomFileRequestHandlerTestSuite.cpp
	g++ $(commonPartUt) $(dicomIncludesPath) ./test_modules/ServerParseDicomFileRequestHandlerTestSuite.cpp

DicomTextInformationExtractor.o : ../source/DicomTextInformationExtractor.cpp
	g++ $(commonPartSrc) $(dicomIncludesPath) ../source/DicomTextInformationExtractor.cpp

DicomTextInformationExtractorTestSuite.o : ./test_modules/DicomTextInformationExtractorTestSuite.cpp
	g++ $(commonPartUt) $(dicomIncludesPath) ./test_modules/DicomTextInformationExtractorTestSuite.cpp

.PHONY : clean
clean:
	rm -f UnitTests $(objects)
