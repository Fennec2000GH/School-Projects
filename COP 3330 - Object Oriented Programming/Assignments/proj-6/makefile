proj6: main.o proj6.o proj6.h
	g++ -o proj6 main.o proj6.o 
main.o: main.cpp proj6.h 
	g++ -c main.cpp 
proj6.o: proj6.o proj6.h
	g++ -c proj6.cpp 
clean: 
	rm *.o proj6

