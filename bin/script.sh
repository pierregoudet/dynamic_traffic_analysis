#!/bin/bash

touch ../bin/measure.dat ../bin/distrib.dat
../bin/traffic measure.dat gnuplot/distrib.dat
 
cat measure.dat

gnuplot<<EOF
set terminal gif medium size 448,336
set output './Traffic.png'
set xlabel 'Time'
set ylabel 'Flow'
set grid
set nokey
set title 'Evolution of flow'
plot "measure.dat" using 1:8 with lines smooth unique, "measure.dat" using 1:7 with lines smooth unique, "measure.dat" using 1:6 with lines smooth unique,"measure.dat" using 1:5 with lines smooth unique
#
EOF


display Traffic.png


rm measure.dat
rm distrib.dat

