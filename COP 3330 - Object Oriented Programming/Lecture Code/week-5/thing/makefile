appname := destruct

CXX := g++
#CXXFLAGS := -Wall -g -O3 
CXXFLAGS := -Wall -g -O3 -std=c++11
# LDLIBS := -L/usr/X11/lib -lglut -lGLU  -lGL -lXmu -lXext -lX11 -lm
LDLIBS := 

srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	    $(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	    rm -f ./.depend
		    $(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	    rm -f $(objects) $(appname)

dist-clean: clean
	   rm -f *~ .depend

include .depend
