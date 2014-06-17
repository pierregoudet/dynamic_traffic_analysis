#!/bin/bash


../bin/traffic measure.dat distrib.dat



gnuplot<<EOF
set terminal gif medium size 448,336
set output './Distrib.png'
set xlabel 'Traffic'
set ylabel 'Probality'
set grid
set nokey
set title 'Distribution of probability'
plot "distrib.dat" using 1:2 with lines smooth unique
set terminal gif medium size 448,336
set output './Traffic.png'
set xlabel 'Time'
set ylabel 'Traffic' 
set grid
set nokey
set title 'Sum of traffic'
plot "measure.dat" using 1:2 with lines smooth unique
EOF


display Traffic.png & display Distrib.png 

rm measure.dat
rm distrib.dat
