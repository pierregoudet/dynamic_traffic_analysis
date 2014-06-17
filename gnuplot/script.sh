#!/bin/bash


../bin/traffic distrib.dat dev.dat



gnuplot<<EOF
# set terminal gif medium size 448,336
# set output './Deviation_linear.png'
# set xlabel 'Deserved flow'
# set ylabel 'deviation'
# set grid
# set nokey
# set title 'Devitation by linear flow'
# plot "dev.dat" using 1:2 with lines smooth unique
set terminal gif medium size 448,336
set output './Distrib.png'
set xlabel 'Traffic'
set ylabel 'Probality'
set grid
set nokey
set title 'Distribution of probability'
plot "distrib.dat" using 1:2 with lines smooth unique
EOF


#display Deviation_linear.png
display Distrib.png 

