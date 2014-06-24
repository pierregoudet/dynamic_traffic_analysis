#!/bin/bash

rm measure.dat

lim=$1
nb_sim=$2
rate=$3 
cnt=0
for ((i=1; i <=$lim; i++))
do
    ../bin/main $nb_sim $rate measure.dat distrib.dat $cnt
    cnt=$((cnt+1))
done



gnuplot<<EOF
set terminal png size 700,700
set output './Measure.png'
set ylabel 'Mean of data lost'
set xlabel 'Simulation number'
set grid
set nokey
set title 'Measure of flow'
set style line 1 lt 1 lc 1
set style line 2 lt 1 lc 2
#set yrange [0:30]
set autoscale
plot "measure.dat" using 1:2 with lines , "measure.dat" using 1:3 with lines
set terminal png size 700,700
set output './Distrib.png'
set xlabel 'traffic'
set ylabel 'Probality'
set grid
set nokey
set autoscale
set style line 1 lt 1 lc 1
set style line 2 lt 1 lc 2
set title 'Distribution of probability'
plot "distrib.dat" using 1:2 with lines, "distrib.dat" using 1:3 with lines
EOF

display Distrib.png & display Measure.png

