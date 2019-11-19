proj5: proj5.o matrix.o matrix.h
	g++ -std=c++11 -o proj5 proj5.o matrix.o
proj5.o: proj5.cpp matrix.h
	g++ -std=c++11 -c proj5.cpp
matrix.o: matrix.cpp matrix.h
	g++ -std=c++11 -c matrix.cpp
clean: 
	rm *.o proj5

