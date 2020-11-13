#!/bin/bash

numberOfProcesses=31;

for ((i = 1; i <= $numberOfProcesses; i++));
do
  ./outputFile 1 $i 0.06 0.01
done

for ((i = 1; i <= $numberOfProcesses; i++));
do
  ./outputFile 2 $i 0.06 0.01 
done

for ((i = 1; i <= $numberOfProcesses; i++));
do
  ./outputFile 3 $i 0.06 0.01
done

for ((i = 1; i <= $numberOfProcesses; i++));
do
  ./outputFile 4 $i 0.06 0.01 
done
