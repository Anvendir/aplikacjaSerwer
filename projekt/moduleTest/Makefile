objects = pierwszyTest.o \
		  ErrorHandler.o \
		  NetworkWrappers.o \
		  UnixWrappers.o

pierwszyTest : $(objects)
	g++ -std=c++14 -o pierwszyTest $(objects) \
	   	-I ../include

pierwszyTest.o : ./pierwszyTest.cpp
	g++ -c -std=c++14 -I ../include pierwszyTest.cpp

ErrorHandler.o : ../source/ErrorHandler.cpp ../include/ErrorHandler.hpp
	g++ -c -std=c++14 -I ../include \
    		../source/ErrorHandler.cpp

NetworkWrappers.o : ../source/NetworkWrappers.cpp ../include/NetworkWrappers.hpp
	g++ -c -std=c++14 -I ../include \
            ../source/NetworkWrappers.cpp

UnixWrappers.o : ../source/UnixWrappers.cpp ../include/UnixWrappers.hpp
	g++ -c -std=c++14 -I ../include \
            ../source/UnixWrappers.cpp

.PHONY : clean
clean:
	rm program $(objects)
