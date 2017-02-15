set terminal epslatex size 5,3 color colortext

set output "q1_problemSizeVsTime.tex" 
plot "q1_problemSizeVsTime.txt" using 1:2 with linespoints title 'Serial Code', \
"q1_problemSizeVsTime.txt" using 1:3 with linespoints title 'Parallel OpenMP Code', \
"q1_problemSizeVsTime.txt" using 1:3 with linespoints title 'Parallel MPI Code'

set output 'q1_problemSizeVsSpeedup.tex'
set title 'Graph to plot the variation in speedup compared to the problem size of in log scale'
set xlabel 'size[log base 10]'
set ylabel 'Speedup'
set xrange [0:10]
set yrange [0:5]
set xtics (0,1,2,3,4,5,6,7,8,9,10)
set ytics (0,1,2,3,4,5)
set key left
plot "q1_problemSizeVsSpeedup_cores1.txt" using 1:3 with linespoints title 'Threads = 1', \
"q1_problemSizeVsSpeedup_cores2.txt" using 1:3 with linespoints title 'Threads = 2', \
"q1_problemSizeVsSpeedup_cores3.txt" using 1:3 with linespoints title 'Threads = 3', \
"q1_problemSizeVsSpeedup_cores4.txt" using 1:3 with linespoints title 'Threads = 4'


set output 'q1_coresVsSpeedup.tex'
set title 'Graph to plot the variation in speedup compared to the number of cores'
set xlabel 'No. of Cores'
set ylabel 'Speedup'
set xrange [0:5]
set yrange [0:5]
set xtics (0,1,2,3,4,5)
set ytics (0,1,2,3,4,5)
set key left
plot "q1_coresVsSpeedup_size1e3.txt" using 1:3 with linespoints title 'Size 1e3', \
"q1_coresVsSpeedup_size1e4.txt" using 1:3 with linespoints title 'Size 1e4', \
"q1_coresVsSpeedup_size1e5.txt" using 1:3 with linespoints title 'Size 1e5', \
"q1_coresVsSpeedup_size1e6.txt" using 1:3 with linespoints title 'Size 1e6', \
"q1_coresVsSpeedup_size1e7.txt" using 1:3 with linespoints title 'Size 1e7', \
"q1_coresVsSpeedup_size1e8.txt" using 1:3 with linespoints title 'Size 1e8', \
"q1_coresVsSpeedup_size1e9.txt" using 1:3 with linespoints title 'Size 1e9'

set output 'q1_coresVsEfficiency.tex'
set title 'Graph to plot the variation in efficiency compared to the number of cores'
set xlabel 'No. of Cores'
set ylabel 'Efficieny'
set xrange [0:5]
set yrange [0:2]
set xtics (0,1,2,3,4,5)
set ytics (0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1,1.1,1.2,1.3)
set key left
plot "q1_coresVsEfficiency_size1e3.txt" using 1:3 with linespoints title 'Size 1e3', \
"q1_coresVsEfficiency_size1e4.txt" using 1:3 with linespoints title 'Size 1e4', \
"q1_coresVsEfficiency_size1e5.txt" using 1:3 with linespoints title 'Size 1e5', \
"q1_coresVsEfficiency_size1e6.txt" using 1:3 with linespoints title 'Size 1e6', \
"q1_coresVsEfficiency_size1e7.txt" using 1:3 with linespoints title 'Size 1e7', \
"q1_coresVsEfficiency_size1e8.txt" using 1:3 with linespoints title 'Size 1e8', \
"q1_coresVsEfficiency_size1e9.txt" using 1:3 with linespoints title 'Size 1e9'
