set terminal epslatex size 3.5,2.62 color colortext
set output 'q2_problemSizeVsTime.tex'
set title 'Graph to plot the variation in time compared to the number of points in log scale'
set xlabel 'size[log base 10]'
set ylabel 'time[sec]'
set xrange [0:10]
set yrange [0:3]
set xtics (0,1,2,3,4,5,6,7,8,9,10)
set ytics (0,.5,1,1.5,2,2.5,3,3.5,4)
set key left top
plot "q2_problemSizeVsTime.txt" using 1:2 with linespoints title '$Serial Code$', \
"q2_problemSizeVsTime.txt" using 1:3 with linespoints title '$Builtin Reduction$', \
"q2_problemSizeVsTime.txt" using 1:4 with linespoints title '$Simple Division$', \
"q2_problemSizeVsTime.txt" using 1:5 with linespoints title '$Divide , Tree Mix$'

set output 'q2_problemSizeVsSpeedup.tex'
set title 'Graph to plot the variation in speedup compared to the number of points in log scale'
set xlabel 'size[log base 10]'
set ylabel 'Speedup'
set xrange [0:10]
set yrange [0:10]
set xtics (0,1,2,3,4,5,6,7,8,9,10)
set ytics (0,1,2,3,4,5,6,7,8,9,10)
set key left top
plot "q2_problemSizeVsSpeedup.txt" using 1:2 with linespoints title '$speedup Reduction$', \
"q2_problemSizeVsSpeedup.txt" using 1:3 with linespoints title '$speedup Simple Division$', \
"q2_problemSizeVsSpeedup.txt" using 1:4 with linespoints title '$speedup Mix$'

set output 'q2_coresVsSpeedup.tex'
set title 'Graph to plot the variation speedup compared to the number of cores'
set xlabel 'No. of Cores'
set ylabel 'peedup'
set xrange [0:40]
set yrange [0:10]
set xtics (0,4,8,12,16,20,24,28,32,36,40)
set ytics (0,1,2,3,4,5,6,7,8,9,10)
set key left top
plot "q2_coresVsSpeedup_size1e8.txt" using 1:2 with linespoints title '$Reduction$', \
"q2_coresVsSpeedup_size1e8.txt" using 1:3 with linespoints title '$Simple Division$', \
"q2_coresVsSpeedup_size1e8.txt" using 1:4 with linespoints title '$Divide , Tree Mix$', \


