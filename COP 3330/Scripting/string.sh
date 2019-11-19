#!/bin/sh

# This example illustrates the difference between some of the quoting 
# rules (single quotes vs. double quotes), as well as the use of the 
# backslash to escape the meaning of special characters

age=21
balance=100.53

echo "Student age is $age"
echo 'Student age is $age'
echo 'Student age is' $age
echo "Student \"age\" is $age"
echo "Student '$age' is $age"

echo "Balance = $balance"
echo "Balance = \$balance"
echo "Balance = \$$balance"
echo 'Balance = \$$balance'
echo "Balance = \$\$$balance"

echo "Hi there ~/* "
echo "Hi there" ~/*
