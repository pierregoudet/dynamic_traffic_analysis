#!/bin/bash


name=$1

gnuplot<<EOF
set terminal png size 700,700
set output './out.png'
#set xlabel 'traffic'
#set ylabel 'Probality'
set grid
set nokey
set autoscale
set title 'Distribution of probability'
plot name using 1:2 with lines
EOF


