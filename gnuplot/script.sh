#!/bin/bash

./trafic measure.dat distrib.dat
 
cat measure.dat
cat distrib.dat

gnuplot<<EOF
set terminal gif medium size 448,336
set output './graphics.png'
set xlabel 'Traffic'
set ylabel 'Probability'
set grid
set nokey
set title 'Probability of flow'
plot "data.dat" using 1:8 with lines smooth unique, "data.dat" using 1:7 with lines smooth unique, "data.dat" using 1:6 with lines smooth unique,"data.dat" using 1:5 with lines smooth unique
EOF


display graphics.png

rm measure.dat
