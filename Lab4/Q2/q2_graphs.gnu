set terminal epslatex size 3.5,2.62 color colortext
set output 'q1_problemSizeVsTime.tex'
set title 'Graph to plot the variation in time compared to the number of points in log scale'
set xlabel 'size[log base 10]'
set ylabel 'time[sec]'
set xrange [0:10]
set yrange [0:25]
set xtics (0,1,2,3,4,5,6,7,8,9,10)
set ytics (0,5,10,15,20,25)
set key left top
plot "q2_problemSizeVsTime.txt" using 1:2 with linespoints title '$Serial Code$', \
"q2_problemSizeVsTime.txt" using 1:3 with linespoints title '$Parallel Code$'

set output 'q1_problemSizeVsSpeedup.tex'
set title 'Graph to plot the variation in speedup compared to the number of points in log scale'
set xlabel 'size[log base 10]'
set ylabel 'Speedup'
set xrange [0:10]
set yrange [0:10]
set xtics (0,1,2,3,4,5,6,7,8,9,10)
set ytics (0,1,2,3,4,5,6,7,8,9,10)
set key left top
plot "q2_problemSizeVsSpeedup.txt" using 1:2 with linespoints title '$speedup curve$'

set output 'q1_coresVsSpeedup.tex'
set title 'Graph to plot the variation speedup compared to the number of cores'
set xlabel 'No. of Cores'
set ylabel 'Speedup'
set xrange [0:40]
set yrange [0:10]
set xtics (0,4,8,12,16,20,24,28,32,36,40)
set ytics (0,1,2,3,4,5,6,7,8,9,10)
set key left top
plot "q2_coresVsSpeedup_size1e7.txt" using 1:2 with linespoints title '$Size 1e7$', \
"q2_coresVsSpeedup_size1e8.txt" using 1:2 with linespoints title '$Size 1e8$'


