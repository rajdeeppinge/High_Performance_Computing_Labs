#!/usr/bin/gnuplot -persist
set title "Problem Size vs Time" font "16"
set xdata problem_size
set ydata time[sec]
set pointsize 1
set terminal wxt persist raise
plot "problemSizeVsTime.txt" using 1:2 with linespoints \
"problemSizeVsTime.txt" using 1:3 with linespoints
