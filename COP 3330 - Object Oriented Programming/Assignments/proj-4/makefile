proj4: program.o Song.o Playlist.o
	g++ -std=c++11 -o proj4 program.o Song.o Playlist.o

program.o: program.cpp Song.h Playlist.h
	g++ -std=c++11 -c program.cpp

Song.o: Song.cpp Song.h
	g++ -std=c++11 -c Song.cpp

Playlist.o: Playlist.cpp Playlist.h
	g++ -std=c++11 -c Playlist.cpp

clean:
        rm *.o proj4

