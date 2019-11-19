#include <iostream>
#include <cstring>
#include "Playlist.h"
using namespace std;

//CONSTRUCTORS
Playlist::Playlist(const char* a)       //intitializes the total duration, # of slots used up, and maximum number of allocated slots
{
    strcpy(listName, a);
    totalDuration = 0;
    usedSize = 0;
    totalCapacity = 5;
}

//DESTRUCTORS
Playlist::~Playlist(){delete [] list;} //deallocates memory of dynamic list of Song objects


//ACCESSORS
const char * Playlist::getListName() const    //retrieves the playlist name
{
    return listName;
}

Song Playlist::getSong(int i) const     //retrieves the Song object at index i of list
{
    return *(list + i);
}

int Playlist::getTotalDuration() const  //retrieves the sum of all elapsed time (in seconds) by the songs
{
    return totalDuration;
}

int Playlist::getUsedSize() const       //retrieves the current # of slots used by Song objects in list
{
    return usedSize;
}

int Playlist::getTotalCapacity() const  //retrieves the maximum # of Song objects list can hold without resizing
{
    return totalCapacity;
}

//MUTATORS
void Playlist::addSong(const char* t, const char* a, Genre g, int d)
{
    Song * newList;                    //potentially needed to point to longer array if the current dynamic array is full
    (*(list + usedSize)).set(t, a, g, d);
    totalDuration += d;
    ++usedSize;
    if(usedSize == totalCapacity)      //the actual size expansion process
    {
        totalCapacity += 5;
        newList = new Song[totalCapacity];
        for(int i = 0; i < usedSize; ++i)
            newList[i] = list[i];
        delete [] list;
        list = newList;
        cout << "** Array being resized to " << totalCapacity;
        cout << " allocated slots " << endl;
    }
    return;
}

int Playlist::deleteSong(const char* t) //resets the Song object using the default constructor and then removes it by shifting elements to the right
{
    int deleteCount = 0;
    Song * newList;
    for(int i = 0; i < usedSize; ++i)
        if(strcasecmp(t, getSong(i).getTitle()) == 0)
            {
                (*(list + i)).set("", "", RB, 0);
                totalDuration -= getSong(i).getDuration();
                ++deleteCount;
            }
    usedSize -= deleteCount;
    if(totalCapacity - usedSize <= 5 && deleteCount > 0)
    {
        newList = new Song[totalCapacity];
        int currentIndex = 0;           //current index of the newList dynamic array - indicates which slot to fill next with a non-deleted Song object
        for(int i = 0; i < usedSize; ++i)
            if(strlen(list[i].getTitle()) != 0)
            {
                newList[currentIndex] = list[i];
                ++currentIndex;
            }
    delete [] list;
    list = newList;
    }
    else if(totalCapacity - usedSize > 5 && deleteCount > 0)
    {
        totalCapacity -= 5;
        newList = new Song[totalCapacity];
        int currentIndex = 0;
        for(int i = 0; i < usedSize; ++i)
            if(strlen(list[i].getTitle()) != 0)
            {
                newList[currentIndex] = list[i];
                ++currentIndex;
            }
        delete [] list;
        list = newList;
        cout << "** Array being resized to " << totalCapacity;
        cout << " allocated slots " << endl;
    }
    return deleteCount;
}

void Playlist::setListName(const char* a)    //sets a new name for the list
{
    strcpy(listName, a);
    return;
}

//BONUS
void Playlist::sort(char criteria) const
{
    Song * newList = new Song[usedSize];
    int newListSize = 0;
    if(criteria == 'A' || criteria == 'a')
    {
        newList[0] = list[0];
        ++newListSize;
    for(int i = 1; i < usedSize; ++i)
        for(int f = newListSize - 1; f >= 0; --f)
            if(strcmp(list[i].getArtist(), newList[f].getArtist()) >= 0)
            {
                for(int c = newListSize - 1; c > f; --c)
                    newList[c + 1] = newList[c];
                newList[f + 1] = list[i];
            }

    }
    else if(criteria == 'T' || criteria == 't')
    {
        newList[0] = list[0];
        ++newListSize;
    for(int i = 1; i < usedSize; ++i)
        for(int f = newListSize - 1; f >= 0; --f)
            if(strcmp(list[i].getTitle(), newList[f].getTitle()) >= 0)
            {
                for(int c = newListSize - 1; c > f; --c)
                    newList[c + 1] = newList[c];
                newList[f + 1] = list[i];
            }
    }

    for(int i = 0; i < usedSize; ++i)
        newList[i].display(); 
    return;
}
