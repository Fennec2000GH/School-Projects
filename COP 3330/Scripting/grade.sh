#!/bin/sh

# Example of if-statements in shell scripts.
# This example takes one command line argument, a test score, then 
# computes the letter grade based on that score

grade=$1

if [ $grade -ge 90 ]
then
  echo "You scored an A!"
elif [ $grade -ge 80 ]
then
  echo "You scored a B"
elif [ $grade -ge 70 ]
then
  echo "You scored a C"
elif [ $grade -ge 60 ]
then
  echo "You scored a D"
else
  if [ $grade -ge 55 ]
  then
    echo "You scored an F, but you came close.  Good luck next term"
  else
    echo "You scored an F, and a really bad one."
  fi
fi

echo "We are done!"
