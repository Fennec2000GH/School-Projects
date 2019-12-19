#!/bin/bash
#Test your cowsay program.

OUTPUTFILE="output.txt"

print_and_run()
{
  COMMAND=$1
  echo ">$COMMAND"
  $COMMAND
}

print_and_run "javac Cowsay.java" > $OUTPUTFILE
print_and_run "java Cowsay Hello World!" >> $OUTPUTFILE
print_and_run "java Cowsay -n kitteh Moew-Moew!" >> $OUTPUTFILE
print_and_run "java Cowsay -l" >> $OUTPUTFILE
print_and_run "java Cowsay -n ninja Hello world!" >> $OUTPUTFILE
print_and_run "java Cowsay -f tux Do you have any herring?" >> $OUTPUTFILE
print_and_run "java Cowsay -f alien Earth is ours!" >> $OUTPUTFILE
print_and_run "java Cowsay -f kitteh MEOW!!!" >> $OUTPUTFILE
print_and_run "java Cowsay -n tux How about tuna?" >> $OUTPUTFILE

less $OUTPUTFILE
