#!/bin/bash

./clean.sh



lim=$1
nb_sim=$2
rate=$3 
cnt=0

for ((i=1; i<=$lim; i++))
do
    ../bin/main $nb_sim $rate measure.dat $i
done


gnuplot<<EOF
set terminal png size 700,700
set output './Measure.png'
set ylabel 'Mean of data lost'qui
set xlabel 'Simulation number'
set grid
set nokey
set autoscale
set title 'Mean'
plot "measure.dat" using 1:2 with lines, "measure.dat" using 1:3 with lines
EOF

display Measure.png
