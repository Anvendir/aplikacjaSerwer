objects = Main.o Dispatcher.o ErrorHandler.o NetworkWrappers.o UnixWrappers.o Server.o \
		  ServerSendFileRequestHandler.o

Program : $(objects)
	g++ -std=c++14 -o Program $(objects)

Main.o : ./source/Main.cpp ./include/Dispatcher.hpp ./include/ErrorHandler.hpp
	g++ -c -std=c++14 -I ./include \
	   	./source/Main.cpp

Dispatcher.o : ./source/Dispatcher.cpp ./include/Dispatcher.hpp
	g++ -c -std=c++14 -I ./include \
	   	./source/Dispatcher.cpp

ErrorHandler.o : ./source/ErrorHandler.cpp ./include/ErrorHandler.hpp
	g++ -c -std=c++14 -I ./include \
		./source/ErrorHandler.cpp

NetworkWrappers.o : ./source/NetworkWrappers.cpp ./include/NetworkWrappers.hpp
	g++ -c -std=c++14 -I ./include \
	   	./source/NetworkWrappers.cpp

UnixWrappers.o : ./source/UnixWrappers.cpp ./include/UnixWrappers.hpp
	g++ -c -std=c++14 -I ./include \
	   	./source/UnixWrappers.cpp

Server.o : ./source/Server.cpp ./include/Server.hpp
	g++ -c -std=c++14 -I ./include \
	   	./source/Server.cpp

ServerSendFileRequestHandler.o : ./source/ServerSendFileRequestHandler.cpp ./include/ServerSendFileRequestHandler.hpp
	g++ -c -std=c++14 -I ./include \
	   	./source/ServerSendFileRequestHandler.cpp

.PHONY : clean
clean:
		rm -f Program $(objects)
