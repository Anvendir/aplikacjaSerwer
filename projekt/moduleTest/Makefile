objects = ComponentTests.o \
		  ComponentTestsFunctions.o \
		  ErrorHandler.o \
		  NetworkWrappers.o \
		  UnixWrappers.o \
		  MessageConverter.o

ComponentTests : $(objects)
	g++ -std=c++14 -o ComponentTests $(objects) \
	   	-I ../include

ComponentTests.o : ./ComponentTests.cpp
	g++ -c -std=c++14 -I ../include ./ComponentTests.cpp

ComponentTestsFunctions.o : ./ComponentTestsFunctions.cpp
	g++ -c -std=c++14 -I ../include ./ComponentTestsFunctions.cpp

ErrorHandler.o : ../source/ErrorHandler.cpp ../include/ErrorHandler.hpp
	g++ -c -std=c++14 -I ../include \
    		../source/ErrorHandler.cpp

NetworkWrappers.o : ../source/NetworkWrappers.cpp ../include/NetworkWrappers.hpp
	g++ -c -std=c++14 -I ../include \
            ../source/NetworkWrappers.cpp

UnixWrappers.o : ../source/UnixWrappers.cpp ../include/UnixWrappers.hpp
	g++ -c -std=c++14 -I ../include \
            ../source/UnixWrappers.cpp

MessageConverter.o : ../source/MessageConverter.cpp ../include/MessageConverter.hpp
	g++ -c -std=c++14 -I ../include \
	   	../source/MessageConverter.cpp

.PHONY : clean
clean:
	rm -f ComponentTests odebrany.txt odebrany.jpg odebrany.dcm $(objects)
