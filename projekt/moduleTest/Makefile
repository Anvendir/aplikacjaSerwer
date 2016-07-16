commonPart = -c -std=c++14 -I ../include

objects = ComponentTests.o \
		  ComponentTestsFunctions.o \
		  ErrorHandler.o \
		  NetworkWrappers.o \
		  UnixWrappers.o \
		  MessageConverter.o

ComponentTests : $(objects)
	g++ -std=c++14 -I ../include -o ComponentTests $(objects)
ComponentTests.o : ./ComponentTests.cpp
	g++ $(commonPart) ./ComponentTests.cpp

ComponentTestsFunctions.o : ./ComponentTestsFunctions.cpp
	g++ $(commonPart) ./ComponentTestsFunctions.cpp

ErrorHandler.o : ../source/ErrorHandler.cpp
	g++ $(commonPart) ../source/ErrorHandler.cpp

NetworkWrappers.o : ../source/NetworkWrappers.cpp
	g++ $(commonPart) ../source/NetworkWrappers.cpp

UnixWrappers.o : ../source/UnixWrappers.cpp
	g++ $(commonPart) ../source/UnixWrappers.cpp

MessageConverter.o : ../source/MessageConverter.cpp
	g++ $(commonPart) ../source/MessageConverter.cpp

.PHONY : clean
clean:
	rm -f ComponentTests odebrany.txt odebrany.jpg odebrany.dcm odebranyRezultatParsowania.txt \
	   	./plikiPrzykladowe/CT0001.dcm.txt $(objects)
