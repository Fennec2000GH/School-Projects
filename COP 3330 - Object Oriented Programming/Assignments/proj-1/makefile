prog1: program.o diamond.o 
	g++ -o prog1 program.o diamond.o 

program.o: program.cpp diamond.h 
	g++ -c program.cpp 

diamond.o: diamond.cpp diamond.h 
	g++ -c diamond.cpp 

clean: 
	rm *.o prog1 
