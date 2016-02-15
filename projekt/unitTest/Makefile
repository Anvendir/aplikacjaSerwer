objects = main.o \
		  Dispatcher.o DispatcherTestSuite.o \
		  ErrorHandler.o ErrorHandlerTestSuite.o \
		  NetworkWrappers.o NetworkWrappersTestSuite.o \
		  UnixWrappers.o UnixWrappersTestSuite.o

GTEST_DIR = ./googleTestRepo/googletest
GMOCK_DIR = ./googleTestRepo/googlemock

unitTests : $(objects)
	g++ -std=c++11 -o unitTests $(objects) \
		./libs/libgtest.a  ./libs/libgmock.a -pthread \
	   	-isystem $(GTEST_DIR)/include -isystem ${GMOCK_DIR}/include

main.o : ./test_modules/main.cpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread \
			-I ./mocks \
			./test_modules/main.cpp

Dispatcher.o : ../source/Dispatcher.cpp ../include/Dispatcher.hpp
	g++ -c -std=c++11 -I ../include \
			../source/Dispatcher.cpp

DispatcherTestSuite.o : ./test_modules/DispatcherTestSuite.cpp ../include/Dispatcher.hpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread \
			-I ./mocks -I ../include/ \
			./test_modules/DispatcherTestSuite.cpp

ErrorHandler.o : ../source/ErrorHandler.cpp ../include/ErrorHandler.hpp
	g++ -c -std=c++11 -I ../include \
			../source/ErrorHandler.cpp

ErrorHandlerTestSuite.o : ./test_modules/ErrorHandlerTestSuite.cpp ../include/ErrorHandler.hpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread \
			-I ./mocks -I ../include/ \
			./test_modules/ErrorHandlerTestSuite.cpp

NetworkWrappers.o : ../source/NetworkWrappers.cpp ../include/NetworkWrappers.hpp
	g++ -c -std=c++11 -I ../include \
			../source/NetworkWrappers.cpp

NetworkWrappersTestSuite.o : ./test_modules/NetworkWrappersTestSuite.cpp ../include/NetworkWrappers.hpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread -isystem ${GMOCK_DIR}/include \
			-I ./mocks -I ../include/ \
			./test_modules/NetworkWrappersTestSuite.cpp

UnixWrappers.o : ../source/UnixWrappers.cpp ../include/UnixWrappers.hpp
	g++ -c -std=c++11 -I ../include \
			../source/UnixWrappers.cpp

UnixWrappersTestSuite.o : ./test_modules/UnixWrappersTestSuite.cpp ../include/UnixWrappers.hpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread -isystem ${GMOCK_DIR}/include \
			-I ./mocks -I ../include/ \
			./test_modules/UnixWrappersTestSuite.cpp

.PHONY : clean
clean:
	rm  $(objects)
