// ---------- UTILITY.H ----------

// This file contains the definitions for
// a few functions that are useful for controlling the
// running of C++ programs.

#ifndef _UTILITY_H
#define _UTILITY_H

void terminateProgram();
// Freeze the screen until the user types a character,
// then print a concluding message.

int readyToQuit();
// Ask if the user is ready to quit the program.
// Return 1 if and only if the user enters 'y' or 'Y'.

void waitForUser(void);
// Freeze the screen until the user types a character.

void setNumeric(void);
// Set C++ format flags for numeric output.

void swap(int &, int &);
// Exchanges the values of two integers.

#endif

