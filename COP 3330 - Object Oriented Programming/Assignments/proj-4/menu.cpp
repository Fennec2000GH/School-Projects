#include <iostream>
#include <cstring>
#include "Song.h"
#include "Song.cpp"
#include "Playlist.h"
#include "Playlist.cpp"
using namespace std;

int main()
{
    //upper-level menu variables
    char listName[21];
    bool validListName = false;
    char selection;                                                                 //menu option selected by user
    bool exitProg = false;                                                          //if true, stops the main do-while loop and exits the program

    //start of program that end user sees
    cout << "Please enter a name for the playlist. " << endl;
    cin.getline(listName, 21, '\n');
    cout << endl;

    for(int i = 0; i < strlen(listName); ++i)
        listName[i] = toupper(listName[i]);

    //checks for valid list name for the first time
    for(int i = 0; i < strlen(listName); ++i)
        if(listName[i] != ' ')
            validListName = true;

    //if invalid list name, the user must keep retrying to type valid list name
    while(validListName == false)
    {
        cout << "Invalid playlist name. Please re-enter: " << endl;
        cin.getline(listName, 21, '\n');
        cout << endl;

        for(int i = 0; i < strlen(listName); ++i)
            listName[i] = toupper(listName[i]);
        for(int i = 0; i < strlen(listName); ++i)
            if(listName[i] != ' ')
                validListName = true;
    }

    //creates a Playlist object only if there is a valid list name entered by user
    Playlist A(listName);

    do
    {
        //menu options loop
        cout << "A: Add a song to the playlist" << endl;
        cout << "F: Find a song in the playlist" << endl;
        cout << "R: Rename playlist" << endl;
        cout << "S: Remove a song" << endl;
        cout << "D: Display the playlist" << endl;
        cout << "G: Genre summary" << endl;
        cout << "M: Show this Menu" << endl;
        cout << "Q: Quit/exit the program" << endl;
        cout << endl;

        //starting point of user inputs
        cin >> selection;
        cin.ignore(10000, '\n');
        selection = toupper(selection);
        switch(selection)
        {
            case 'A':
                {
                    //variables to store user input
                    const char validGenres[5] = {'C', 'E', 'P', 'R', 'B'};      //char version of the enum Genre, aligned with the same indices
                    char title[41];
                    char artist[26];
                    char genre;
                    int duration;

                    //accepts and checks for valid names for the play list
                    cout << "Enter title:  ";
                    cin.getline(title, 41, '\n');
                    cout << "Enter author:  ";
                    cin.getline(artist, 26, '\n');

                    //accepts and checks for valid genre
                    bool genre_is_valid = false;
                    cout << "Enter genre - (C)ountry, (E)DM, (P)op, (R)ock, or (B)R&B:  ";
                    cin >> genre;
                    cin.ignore(10000, '\n');
                    genre = toupper(genre);   //always interpret user inputs of type char as uppercase

                    for(auto & item : validGenres)
                        if(genre == item)
                        {
                            genre_is_valid = true;
                            break;
                        }

                    while(genre_is_valid == false)
                    {
                        cout << "Invalid genre entry. Please re-enter: " << endl;
                        cin >> genre;
                        cin.ignore(10000, '\n');
                        genre = toupper(genre);

                        for(auto & item : validGenres)
                            if(genre == item)
                            {
                                genre_is_valid = true;
                                break;
                            }
                    }

                    cout << "Enter the duration of the song (in seconds):  ";
                    cin >> duration;
                    cin.ignore(10000, '\n');
                    while(duration <= 0)
                    {
                        cout << "Must enter a positive duration. Please re-enter: ";
                        cin >> duration;
                        cin.ignore(10000, '\n');
                    }

                    //sets data members of the Playlist object only after all inputs are valid
                    switch(genre)
                    {
                        case 'C': {A.addSong(title, artist, COUNTRY, duration); break;}
                        case 'E': {A.addSong(title, artist, EDM, duration); break;}
                        case 'P': {A.addSong(title, artist, POP, duration); break;}
                        case 'R': {A.addSong(title, artist, ROCK, duration); break;}
                        case 'B': {A.addSong(title, artist, RB, duration); break;}

                    }

                    break;
                }
            case 'F':
            {

                char search[41];
                int hits = 0; //the # of exact matches
                cout << "Enter title: ";
                cin.getline(search, 41, '\n');
                for(int i = 0; i < A.getUsedSize(); ++i)
                    if(strcmp(search, A.getSong(i).getTitle()) == 0 ||
                        strcmp(search, A.getSong(i).getArtist()) == 0)
                    {
                        A.getSong(i).display();
                        ++hits;
                    }
                if(hits == 0)
                    cout << "No songs found. " << endl << endl;

                break;
            }
            case 'R':
            {
                //accepts and checks for valid new name for the play list
                char new_name[21];
                bool name_is_valid = false;
                cout << "Enter title:  " << endl;
                cin.getline(new_name, 21, '\n');

                for(int i = 0; i < strlen(new_name); ++i)
                    if(new_name[i] != ' ')
                        name_is_valid = true;

                if(strlen(new_name) == 0 || name_is_valid == false)
                    cout << "Invalid playlist name. Playlist name was not updated. " << endl;
                else
                    A.setListName(new_name);

                break;
            }
            case 'S':
            {
                char title[41];
                cout << "Enter title:  ";
                cin.getline(title, 41, '\n');
                int deleteCount = A.deleteSong(title);

                //under the circumstance that no song matches
                if(deleteCount == 0)
                    cout << "No songs removed from PlaylistName. " << endl << endl;

                break;
            }

            case 'D':
            {
                for(int i = 0; i < A.getUsedSize(); ++i)
                    A.getSong(i).display();
                break;
            }
            case 'G':
            {
                const char validGenres[5] = {'C', 'E', 'P', 'R', 'B'};
                char genre;
                int genreValue = -1;
                int genreCount = 0;
                int genreDuration = 0;
                cout << "Enter genre - (C)ountry, (E)DM, (P)op, (R)ock, or (B)R&B:  ";
                cin >> genre;
                cin.ignore(10000, '\n');
                genre = toupper(genre);

                for(int i = 0; i < 5; ++i)
                    if(genre == validGenres[i])
                    {
                        genreValue = i;
                        break;
                    }
                if(genreValue >= 0 && genreValue <= 4)
                {
                    for(int i = 0; i < A.getUsedSize(); ++i)
                        if(int(A.getSong(i).getGenre()) == genreValue)
                        {
                            A.getSong(i).display();
                            ++genreCount;
                            genreDuration += A.getSong(i).getDuration();
                        }
                    cout << "Total duration:  " << genreDuration / 60 << ":" << genreDuration % 60 << endl;
                }
                if(genreCount == 0 || genreDuration == 0)
                    cout << "The playlist " << A.getListName() << " is empty. " << endl << endl;

                break;
            }
            case 'M':
            {
                //redisplays the menu
                cout << "A: Add a song to the playlist" << endl;
                cout << "F: Find a song in the playlist" << endl;
                cout << "R: Rename playlist" << endl;
                cout << "S: Remove a song" << endl;
                cout << "D: Display the playlist" << endl;
                cout << "G: Genre summary" << endl;
                cout << "M: Show this Menu" << endl;
                cout << "Q: Quit/exit the program" << endl;
                cout << endl;

                break;
            }
            case 'O':
            {
                char criteria;
                cout << "Sort by (T)itle or (A)rtist?  ";
                cin >> criteria;
                cin.ignore(10000, '\n');
                cout << endl << endl;
                A.sort(criteria);


                break;
            }
            case 'Q':
            {
                cout << "Exiting program. Your playlist was " << A.getTotalDuration() / 60;
                cout << ":" << A.getTotalDuration() % 60 << " long. " << endl;
                exitProg = true;

                break;
            }

        }
    } while(exitProg == false);

    return 0;
}
