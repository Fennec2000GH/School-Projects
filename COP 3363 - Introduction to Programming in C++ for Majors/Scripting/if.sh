#!/bin/sh

# Script that expects one command line parameter, and then checks to see
# if that item is a file or a directory, as well as whether it is 
# readable, writable, and/or executable

file=$1		# first command line argument is to be a filename

if [ -d $file ]
then
  echo "$file is a directory"
fi

if [ -f $file ]
then
  echo "$file is a file"
fi

if [ -r $file ]
then
  echo "$file is readable"
fi

if [ -w $file ]
then
  echo "$file is writable"
fi

if [ -x $file ]
then
  echo "$file is executable"
fi
