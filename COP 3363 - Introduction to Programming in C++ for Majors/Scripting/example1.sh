#!/bin/sh

echo This is a script that is running!
echo "ha ha ha ha ha ha ha ha ha"

echo "group environment variable =" $GROUP


echo "Now here's a calendar" > myfile1
cal -3 >> myfile1

echo "now here's the date" >> myfile1
date >> myfile1

name=Joe
age=35
occupation="Garbage Collector"

echo "name = $name"
echo "age = $age"
echo "occupation = $occupation"

echo '$1 =' $1
echo '$2 =' $2
echo '$3 =' $3
echo '$4 =' $4
echo '$5 =' $5

