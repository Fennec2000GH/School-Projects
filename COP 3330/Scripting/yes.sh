#!/bin/sh

echo "yes or no?"
read answer

case $answer in
"yes")
  echo "exiting with status 0"
  exit 0;;
*)
  echo "exiting with status 1"
  exit 1;;
esac
