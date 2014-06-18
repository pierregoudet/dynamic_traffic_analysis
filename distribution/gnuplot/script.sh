#!/bin/bash


../bin/main distrib.dat dev.dat



gnuplot<<EOF
# set terminal png size 448,336
# set output './Deviation_linear.png'
# set xlabel 'Deserved flow'
# set ylabel 'deviation'
# set grid
# set nokey
# set title 'Devitation by linear flow'
# plot "dev.dat" using 1:2 with lines smooth unique
set terminal png size 700,700
set output './Distrib.png'
set xlabel 'Traffic'
set ylabel 'Probality'
set grid
set nokey
set title 'Distribution of probability'
plot "distrib.dat" using 1:2 with lines, "distrib.dat" using 1:3 with lines
EOF


#display Deviation_linear.png
display Distrib.png 

