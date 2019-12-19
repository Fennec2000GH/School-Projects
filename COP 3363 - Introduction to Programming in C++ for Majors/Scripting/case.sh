#!/bin/sh

echo " do you want to remove file $1? (yes or no)" 
read ans

case $ans in 
"yes") rm $1
	echo "file removed" 
"no") echo "file not removed"
	;;	
*) echo "do not understand"
esac
exit
