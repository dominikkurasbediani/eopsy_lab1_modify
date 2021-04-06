#!/bin/bash

# CREATING DIRECTORY WITH EXAMPLE FILES
echo "<----------------------------------->"
echo "Creating directory tree for testing"

mkdir "test"
cd "test"
mkdir "dir1"
mkdir "dir2"
mkdir "dir3"
mkdir "dir1/inside"
mkdir "dir1/inside/deeper"
mkdir "dir1/another"
mkdir "dir2/example1"
mkdir "dir2/example2"
echo hefllo > "dir1/file.txt";
echo hefllo > "dir1/file2.txt";
echo hefllo > "dir1/-file3.txt";
echo hello > "dir2/AbC.txt";
echo hello > "dir3/aab.txt";
echo helflo > "dir1/inside/space name example .txt";
echo helflo > "dir1/inside/deeper/spec&ial.txt";
echo helflo > "dir1/another/space is here example 2 .txt";
echo helflo > "dir2/example1/SPec??iaL.txt";
echo helflo > "dir2/example2/space is here .txt";
ls -R


 # CORRECT USAGE

 echo "<----------------------------------->"
 echo "Running modify -h"
 ../modify -h

 echo "<----------------------------------->"
 echo "Running modify -u file name"
 ../modify -u ./dir1/file.txt
 ls -R

 echo "<----------------------------------->"
 echo "Running modify -l file name"
 ../modify -l ./dir2/AbC.txt
 ls -R   

 echo "<----------------------------------->"
 echo "Running modify -r -u directory"
 ../modify -r -u ./dir1
 ls -R   

 echo "<----------------------------------->"
 echo "Running modify -r -l directory"
 ../modify -r -l ./dir1
 ls -R    

 echo "<----------------------------------->"
 echo "Running modify -r -u file name"
 ../modify -r -u ./dir3/aab.txt
 ls -R   

 echo "<----------------------------------->"
 echo "Running modify -r -l file name"
 ../modify -r -l ./dir2/example1/SPec??iaL.txt
 ls -R   

 echo "<----------------------------------->"
 echo "Running modify -r 's/e/EE/g' directory"
 ../modify -r 's/e/EE/g' ./dir2
 

 echo "<----------------------------------->"
 echo "Running modify 's/f/RR/g'"
 ../modify 's/f/RR/g' ./dir1

 echo "<----------------------------------->"
 echo "Running modify -r 's/EE/e/g' directory"
 ../modify -r 's/EE/e/g' ./dir2
 

 echo "<----------------------------------->"
 echo "Running modify 's/RR/r/g'"
 ../modify 's/RR/r/g' ./dir1
 

 # # INCORRECT USAGE

 echo "<----------------------------------->"
 echo "INCORRECT SCENARIO: Running modify -x -z dir"
 ../modify -x -z ./dir1
 

 echo "<----------------------------------->"
 echo "INCORRECT SCENARIO: Running modify -u file name"
 ../modify -u ./dir2/non existing file.txt


# CLEANING FULL DIR IF NEEDED

 echo "<----------------------------------->"
 echo "Cleaning up the test directory tree"
 cd ..
 rm -rf "test"