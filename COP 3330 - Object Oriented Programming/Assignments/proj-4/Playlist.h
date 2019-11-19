#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
#include "Song.h"
using namespace std;
class Song;

class Playlist
{
public:
    //CONSTRUCTORS
    Playlist():Playlist(""){}   //default constructor is delegated from the second constructor, but with blank listName
    Playlist(const char* a);

    //DESTRUCTORS
    ~Playlist();

    //ACCESSORS
    const char * getListName() const;
    Song getSong(int i) const;
    int getTotalDuration() const;
    int getUsedSize() const;
    int getTotalCapacity() const;

    //MUTATORS
    void addSong(const char* t, const char* a, Genre g, int d);
    int deleteSong(const char* t);
    void setListName(const char* a);

    //BONUS
    void sort(char criteria) const;


private:
    Song * list = new Song[5];
    char listName[21];
    int totalDuration, usedSize, totalCapacity;

};

#endif
