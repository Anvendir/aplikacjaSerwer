objects = main.o Dispatcher.o ErrorHandler.o NetworkWrappers.o

program : $(objects)
	g++ -std=c++11 -o program $(objects)

main.o : ./source/main.cpp ./include/Dispatcher.hpp ./include/ErrorHandler.hpp
	g++ -c -std=c++11 -I ./include \
	   	./source/main.cpp

Dispatcher.o : ./source/Dispatcher.cpp ./include/Dispatcher.hpp
	g++ -c -std=c++11 -I ./include \
	   	./source/Dispatcher.cpp

ErrorHandler.o : ./source/ErrorHandler.cpp ./include/ErrorHandler.hpp
	g++ -c -std=c++11 -I ./include \
		./source/ErrorHandler.cpp

NetworkWrappers.o : ./source/NetworkWrappers.cpp ./include/NetworkWrappers.hpp
	g++ -c -std=c++11 -I ./include \
	   	./source/NetworkWrappers.cpp

.PHONY : clean
clean:
		rm program $(objects)
