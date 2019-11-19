 // Song.h -- header file for the Song class
//
// An object of type Song stores information about a single song.
// The variable "category" stores the Genre of the song
// (one of the five items in the enumerated type Genre).

#ifndef COP3330_SONG_H
#define COP3330_SONG_H

enum Genre {COUNTRY, EDM, POP, ROCK, RB};

class Song
{
public:
    Song();           // Default constructor, sets up blank song object

    void set(const char* t, const char* a, Genre g, int d);

    // the set function should allow incoming data to be received through
    // parameters and loaded into the member data of the object (i.e., this
    // function "sets" the state of the object to the data passed in).
    // The parameters t, a, g, and d represent the title, artist, genre,
    // and duration of the song, respectively.

    const char* getTitle() const;		// returns the title stored in the object
    const char* getArtist() const;  	// returns the artist
    int getDuration() const;		    // returns the duration
    Genre getGenre() const;		        // returns the genre

    void display() const;	    		// described below

private:
    char title[41];	    // may assume title is 40 characters or less
    char artist[26];	// may assume artist name is 25 characters or less
    Genre type;
    int duration;       // Duration of a song in seconds.
                        // Must be a positive integer (larger or equal to zero)
};

// display() function
//
// The member function display() should print out one Song object on one line
// by printing its title, artist, genre, and duration. These should be printed such that
// when you print several songs one after the other (see examples below),
// their fields will align under each other. The duration should be printed as minutes
// and seconds notation (m:ss). Examples:
//
// Town Called Malice       The Jam            Rock                3:04
// One Dance                Drake              R&B                 3:25
// Girls Like You           Maroon 5           Pop                 4:30

#endif //COP3330_SONG_H
