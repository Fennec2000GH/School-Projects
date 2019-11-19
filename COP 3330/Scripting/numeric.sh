#!/bin/sh

# Script that checks to see if the command line parameter is less than 5

num=$1		# first command line argument is to be a number

if [ $num -lt 5 ]
then
  echo "$num is less than 5"
elif [ $num -gt 5 ]
then
  echo "$num is more than 5"
else
  echo "$num is equal to 5"
fi

