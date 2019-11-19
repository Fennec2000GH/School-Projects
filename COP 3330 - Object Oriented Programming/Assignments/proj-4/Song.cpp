#include <iostream>
#include <iomanip>
#include <cstring>
#include "Song.h"
using namespace std;

//CONSTRUCTORS
Song::Song()                                                                            //sets the title and artist to a blank cstring
{
    strcpy(title, "");
    strcpy(artist, "");
}

//ACCESSORS
const char * Song::getTitle() const
{
    return title;
}

const char * Song::getArtist() const
{
    return artist;
}

int Song::getDuration() const
{
    return duration;
}

Genre Song::getGenre() const
{
    return type;
}

//OTHER NON-MUTATORS
void Song::display() const
{
    //string titleS(title);
    //string artistS(artist);
    cout << left << setw(42) << title;
    cout << left << setw(25) << artist;
    switch(type)
    {
        case COUNTRY: {cout << left << setw(20) << "Country"; break;}
        case EDM: {cout << left << setw(20) << "EDM"; break;}
        case POP: {cout << left << setw(20) << "Pop"; break;}
        case ROCK: {cout << left << setw(20) << "Rock"; break;}
        case RB: {cout << left << setw(20) << "R&B";}
    }
    cout << duration / 60 << ":" << duration % 60 << endl;
    return;
}

//MUTATORS
void Song::set(const char* t, const char* a, Genre g, int d)                            //sets all private data members of Song.h
{
    strcpy(title, t);
    strcpy(artist, a);
    type = g;
    duration = d;
    return;
}
