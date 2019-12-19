#!/bin/sh

echo "USER = " $USER 
echo "PWD = " $PWD

firstname=Melina
lastname=Vastola
USER=Awesome_Sauce


echo "USER = "            $USER
echo $firstname $lastname "is user" $USER

echo Type a password:
read password
echo You typed in for your password: $password

echo Enter values for X and Y
read X
read Y
echo X = $X and Y = $Y

echo Please type your IQ and your shoe size
read IQ shoesize

echo Your IQ and shoe size are:  $IQ and $shoesize
echo "Which is which?"
