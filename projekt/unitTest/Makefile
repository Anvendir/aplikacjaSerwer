objects = main.o \
		  Dispatcher.o DispatcherTestSuite.o \
		  ErrorHandler.o ErrorHandlerTestSuite.o \
		  NetworkWrappers.o NetworkWrappersTestSuite.o

GTEST_DIR = ./googleTestRepo/googletest/
GMOCK_DIR = ./googleTestRepo/googlemock/

unitTests : $(objects)
	g++ -std=c++11 -o unitTests $(objects) \
		./libs/libgtest.a  ./libs/libgmock.a -pthread \
	   	-isystem $(GTEST_DIR)/include -isystem ${GMOCK_DIR}/include

main.o : ./source/main.cpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread \
			-I ./include \
			./source/main.cpp

Dispatcher.o : ../source/Dispatcher.cpp ../include/Dispatcher.hpp
	g++ -c -std=c++11 -I ../include \
			../source/Dispatcher.cpp

DispatcherTestSuite.o : ./source/DispatcherTestSuite.cpp ../include/Dispatcher.hpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread \
			-I ./include -I ../include/ \
			./source/DispatcherTestSuite.cpp

ErrorHandler.o : ../source/ErrorHandler.cpp ../include/ErrorHandler.hpp
	g++ -c -std=c++11 -I ../include \
			../source/ErrorHandler.cpp

ErrorHandlerTestSuite.o : ./source/ErrorHandlerTestSuite.cpp ../include/ErrorHandler.hpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread \
			-I ./include -I ../include/ \
			./source/ErrorHandlerTestSuite.cpp

NetworkWrappers.o : ../source/NetworkWrappers.cpp ../include/NetworkWrappers.hpp
	g++ -c -std=c++11 -I ../include \
			../source/NetworkWrappers.cpp

NetworkWrappersTestSuite.o : ./source/NetworkWrappersTestSuite.cpp ../include/NetworkWrappers.hpp
	g++ -c -std=c++11 -isystem $(GTEST_DIR)/include -pthread -isystem ${GMOCK_DIR}/include \
			-I ./include -I ../include/ \
			./source/NetworkWrappersTestSuite.cpp

.PHONY : clean
clean:
	rm  $(objects)
