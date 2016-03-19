objects = Main.o \
		  Dispatcher.o DispatcherTestSuite.o \
		  ErrorHandler.o ErrorHandlerTestSuite.o \
		  NetworkWrappers.o NetworkWrappersTestSuite.o \
		  UnixWrappers.o UnixWrappersTestSuite.o \
		  Server.o ServerTestSuite.o

GTEST_DIR = ./googleTestRepo/googletest
GMOCK_DIR = ./googleTestRepo/googlemock

UnitTests : $(objects)
	g++ -std=c++14 -o UnitTests $(objects) \
		./libs/libgtest.a  ./libs/libgmock.a -pthread \
	   	-isystem $(GTEST_DIR)/include -isystem ${GMOCK_DIR}/include

Main.o : ./test_modules/Main.cpp
	g++ -c -std=c++14 -isystem $(GTEST_DIR)/include -pthread \
			-I ./mocks \
			./test_modules/Main.cpp

Dispatcher.o : ../source/Dispatcher.cpp ../include/Dispatcher.hpp
	g++ -c -std=c++14 -I ../include \
			../source/Dispatcher.cpp

DispatcherTestSuite.o : ./test_modules/DispatcherTestSuite.cpp ../include/Dispatcher.hpp
	g++ -c -std=c++14 -isystem $(GTEST_DIR)/include -pthread -isystem ${GMOCK_DIR}/include \
			-I ./mocks -I ../include/ \
			./test_modules/DispatcherTestSuite.cpp

ErrorHandler.o : ../source/ErrorHandler.cpp ../include/ErrorHandler.hpp
	g++ -c -std=c++14 -I ../include \
			../source/ErrorHandler.cpp

ErrorHandlerTestSuite.o : ./test_modules/ErrorHandlerTestSuite.cpp ../include/ErrorHandler.hpp
	g++ -c -std=c++14 -isystem $(GTEST_DIR)/include -pthread \
			-I ./mocks -I ../include/ \
			./test_modules/ErrorHandlerTestSuite.cpp

NetworkWrappers.o : ../source/NetworkWrappers.cpp ../include/NetworkWrappers.hpp
	g++ -c -std=c++14 -I ../include \
			../source/NetworkWrappers.cpp

NetworkWrappersTestSuite.o : ./test_modules/NetworkWrappersTestSuite.cpp ../include/NetworkWrappers.hpp
	g++ -c -std=c++14 -isystem $(GTEST_DIR)/include -pthread -isystem ${GMOCK_DIR}/include \
			-I ./mocks -I ../include/ \
			./test_modules/NetworkWrappersTestSuite.cpp

UnixWrappers.o : ../source/UnixWrappers.cpp ../include/UnixWrappers.hpp
	g++ -c -std=c++14 -I ../include \
			../source/UnixWrappers.cpp

UnixWrappersTestSuite.o : ./test_modules/UnixWrappersTestSuite.cpp ../include/UnixWrappers.hpp
	g++ -c -std=c++14 -isystem $(GTEST_DIR)/include -pthread -isystem ${GMOCK_DIR}/include \
			-I ./mocks -I ../include/ \
			./test_modules/UnixWrappersTestSuite.cpp

Server.o : ../source/Server.cpp ../include/Server.hpp
	g++ -c -std=c++14 -I ../include \
			../source/Server.cpp

ServerTestSuite.o : ./test_modules/ServerTestSuite.cpp ../include/Server.hpp
	g++ -c -std=c++14 -isystem $(GTEST_DIR)/include -pthread -isystem ${GMOCK_DIR}/include \
			-I ./mocks -I ../include/ \
			./test_modules/ServerTestSuite.cpp

ServerSendFileRequestHandler.o : ../source/ServerSendFileRequestHandler.cpp ../include/ServerSendFileRequestHandler.hpp
	g++ -c -std=c++14 -I ../include \
			../source/ServerSendFileRequestHandler.cpp

ServerSendFileRequestHandlerTestSuite.o : ./test_modules/ServerSendFileRequestHandlerTestSuite.cpp ../include/ServerSendFileRequestHandler.hpp
	g++ -c -std=c++14 -isystem $(GTEST_DIR)/include -pthread -isystem ${GMOCK_DIR}/include \
			-I ./mocks -I ../include/ \
			./test_modules/ServerSendFileRequestHandlerTestSuite.cpp

.PHONY : clean
clean:
	rm -f UnitTests $(objects)
