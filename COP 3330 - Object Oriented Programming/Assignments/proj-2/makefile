proj2: program.o date.o date.h
	g++ -std=c++11  -o proj2 program.o date.o

program.o: program.cpp date.h
	g++ -std=c++11 -c program.cpp

date.o: date.cpp date.h
	g++ -std=c++11 -c date.cpp

clean:
	rm *.0 proj2

	
