appname := frac

CXX := g++
CXXFLAGS := -Wall -g -O3 -std=c++11 
LDLIBS :=

$(appname): frac.o main.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $(appname) frac.o main.o

frac.o: frac.cpp frac.h
		$(CXX) $(CXXFLAGS) $(LDLIBS) -c frac.cpp

main.o: main.cpp frac.h
		$(CXX) $(CXXFLAGS) $(LDLIBS) -c  main.cpp

clean:
		rm -f *.o frac
