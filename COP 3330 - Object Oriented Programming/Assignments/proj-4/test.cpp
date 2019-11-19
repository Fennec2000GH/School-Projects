#include <iostream>
#include "Song.cpp"
#include "Playlist.cpp"
using namespace std;

int main()
{
    Song a;
    a.set("Write Sins Not Tradegies", "Panic! At the Disco", POP, 240);
    cout << a.getTitle() << endl;
    cout << a.getArtist() << endl;
    cout << a.getGenre() << endl;
    cout << a.getDuration() << endl;

    char rat[20];
    string pig = "Ima pig oink oink!";
    strcpy(rat, pig.c_str());

    for(char & item : rat)
        cout << item;
    cout << endl;

    char mouse[8] = {'N', 'O', 'O', 'B', 'I', 'E', 'S', '\0'};
    strcpy(rat, mouse);

    for(char & item : rat)
        cout << item;
    cout << endl;

    /*
    cin >> rat;

    for(char & item : rat)
        cout << item;
    cout << endl;
    */

    Song empty;
    cout << "The title of empty is:  " << empty.getTitle() << endl;
    cout << strlen(empty.getTitle()) << endl;

    cout << left << setw(20) << setfill('$') << "NubNun" << right << setw(20) << setfill('+') << " IInnII " << endl;

    const char * korean = "J-Hope 321";
    const char * kookie = "J-Hope 321";

    cout << strcmp(korean, kookie) << endl;

    return 0;
}
