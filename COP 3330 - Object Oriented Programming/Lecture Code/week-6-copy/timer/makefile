timer: main.o timer.o
	g++ -Wall -O3 -std=c++11 -o timer main.o timer.o

main.o: main.cpp timer.h
	g++ -Wall -O3 -std=c++11 -o main.o -c main.cpp

timer.o: timer.cpp timer.h
	g++ -Wall -O3 -std=c++11 -o timer.o -c timer.cpp

clean:
	rm -f *.o timer
