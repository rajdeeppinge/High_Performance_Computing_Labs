set terminal epslatex size 5,3 color colortext

set output 'q1_problemSizeVsTime.tex'
set title 'Graph to plot the variation in time compared to the problem size in log scale'
set xlabel 'size[log base 10]'
set ylabel 'time[sec]'
set xrange [0:6]
set yrange [0:1000]
set xtics (0,1,2,3,4,5,6)
set ytics (0,200,400,600,800,1000)
set key left
plot "q1_problemSizeVsTime.txt" using 1:2 with linespoints title '$Serial Code$', \
"q1_problemSizeVsTime.txt" using 1:3 with linespoints title '$Parallel Code$'

set output 'q1_problemSizeVsSpeedup.tex'
set title 'Graph to plot the variation in speedup compared to the problem size of in log scale'
set xlabel 'size[log base 10]'
set ylabel 'Speedup'
set xrange [0:6]
set yrange [0:4]
set xtics (0,1,2,3,4,5,6)
set ytics (0,1,2,3,4)
set key left
plot "q1_problemSizeVsSpeedup.txt" using 1:2 with linespoints title '$Speedup$'

set output 'q1_coresVsSpeedup.tex'
set title 'Graph to plot the variation in speedup compared to the number of cores'
set xlabel 'No. of Cores'
set ylabel 'Speedup'
set xrange [0:15]
set yrange [0:5]
set xtics (0,1,2,3,4,5,6)
set ytics (0,1,2,3,4)
set key left
plot "q1_coresVsSpeedup_size1e7.txt" using 1:3 with linespoints title '$Size 1e7$', \
"q1_coresVsSpeedup_size1e8.txt" using 1:3 with linespoints title '$Size 1e8$'
