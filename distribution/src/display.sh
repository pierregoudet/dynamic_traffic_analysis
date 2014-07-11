#!/bin/bash


gnuplot<<EOF
set terminal png size 700,700
set output './out.png'
#set xlabel 'traffic'
#set ylabel 'Probality'
set grid
set nokey
set autoscale
set title 'Distribution of probability'
plot "$1" using 1:2 with lines, "$1" using 1:4 with lines
EOF

display out.png


