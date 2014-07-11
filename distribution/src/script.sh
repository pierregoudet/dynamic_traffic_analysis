#!/bin/bash

rm measure.dat

lim=$1
nb_sim=$2
rate=$3 
nb_vn='5'
capacity='1000'
admit_rate='0.99'
min_flow1='0.90'
min_flow2='0.80'

for ((i=0; i<$lim; i++))
do
    ../bin/main $nb_sim $rate $nb_vn $capacity $admit_rate $min_flow1 $min_flow2 $i
done


gnuplot<<EOF
set terminal png size 700,700
set output './Measure.png'
set ylabel 'Mean of data lost'
set xlabel 'Simulation number'
set grid
set nokey
set autoscale
set title 'Mean'
plot "measure.dat" using 1:2 with lines, "measure.dat" using 1:3 with lines
EOF

display Measure.png
