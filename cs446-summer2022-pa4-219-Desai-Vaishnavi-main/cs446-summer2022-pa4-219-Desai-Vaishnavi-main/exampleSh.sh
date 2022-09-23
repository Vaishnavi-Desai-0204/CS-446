#!/bin/bash

#use pwd to find the path of the cwd
dir=$(PWD)
#make a directory named example in cwd
mkdir -p example
#create an empty file called example.txt in the cwd
touch example.txt
#copy example.txt to example dir
cp example.txt ./example/example.txt

#create a loop that iterates 10 times
for var in {1..10}
do
  echo "HEY THERE"
done