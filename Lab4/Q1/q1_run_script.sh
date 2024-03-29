#!/bin/bash

gcc -Wall -fopenmp -o q1_pirand_serial q1_pirand_serial.c
gcc -Wall -fopenmp -o q1_parallel_seed q1_parallel_seed.c

echo changing number of threads, size = 1e7
echo	   

echo Threads_1
thread=1
export OMP_NUM_THREADS=1
serial_line="$(./q1_pirand_serial 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup ${thread} thread: ${speedup}
echo "$thread $speedup" > coresVsSpeedup_size1e7.txt
echo 

echo Threads_2
thread=2
export OMP_NUM_THREADS=2
#serial_line="$(./q1_pirand_serial 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup ${thread} thread: ${speedup}
echo "$thread $speedup" >> coresVsSpeedup_size1e7.txt
echo 

echo Threads_3
thread=3
export OMP_NUM_THREADS=3
#serial_line="$(./q1_pirand_serial 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup ${thread} thread: ${speedup}
echo "$thread $speedup" >> coresVsSpeedup_size1e7.txt
echo 

echo Threads_4
thread=4
export OMP_NUM_THREADS=4
#serial_line="$(./q1_pirand_serial 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup ${thread} thread: ${speedup}
echo "$thread $speedup" >> coresVsSpeedup_size1e7.txt
echo

echo changing number of threads, size = 1e8
echo	   

echo Threads_1
thread=1
export OMP_NUM_THREADS=1
serial_line="$(./q1_pirand_serial 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup ${thread} thread: ${speedup}
echo "$thread $speedup" > coresVsSpeedup_size1e8.txt
echo 

echo Threads_2
thread=2
export OMP_NUM_THREADS=2
#serial_line="$(./q1_pirand_serial 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup ${thread} thread: ${speedup}
echo "$thread $speedup" >> coresVsSpeedup_size1e8.txt
echo 

echo Threads_3
thread=3
export OMP_NUM_THREADS=3
#serial_line="$(./q1_pirand_serial 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup ${thread} thread: ${speedup}
echo "$thread $speedup" >> coresVsSpeedup_size1e8.txt
echo 

echo Threads_4
thread=4
export OMP_NUM_THREADS=4
#serial_line="$(./q1_pirand_serial 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup ${thread} thread: ${speedup}
echo "$thread $speedup" >> coresVsSpeedup_size1e8.txt
echo      

echo changing input size
echo

echo number of points = 1e3
size=3
serial_line="$(./q1_pirand_serial 1000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 1000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup 1e${size}: ${speedup}
echo "$size $stime $ptime" > problemSizeVsTime.txt
echo "$size $speedup" > problemSizeVsSpeedup.txt
echo 
	 
echo number of points = 1e4
size=4
serial_line="$(./q1_pirand_serial 10000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 10000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup 1e${size}: ${speedup}
echo "$size $stime $ptime" >> problemSizeVsTime.txt
echo "$size $speedup" >> problemSizeVsSpeedup.txt
echo

echo number of points = 1e5
size=5
serial_line="$(./q1_pirand_serial 100000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 100000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup 1e${size}: ${speedup}
echo "$size $stime $ptime" >> problemSizeVsTime.txt
echo "$size $speedup" >> problemSizeVsSpeedup.txt
echo

echo number of points = 1e6
size=6
serial_line="$(./q1_pirand_serial 1000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 1000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup 1e${size}: ${speedup}
echo "$size $stime $ptime" >> problemSizeVsTime.txt
echo "$size $speedup" >> problemSizeVsSpeedup.txt
echo

echo number of points = 1e7
size=7
serial_line="$(./q1_pirand_serial 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup 1e${size}: ${speedup}
echo "$size $stime $ptime" >> problemSizeVsTime.txt
echo "$size $speedup" >> problemSizeVsSpeedup.txt
echo

echo number of points = 1e8
size=8
serial_line="$(./q1_pirand_serial 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup 1e${size}: ${speedup}
echo "$size $stime $ptime" >> problemSizeVsTime.txt
echo "$size $speedup" >> problemSizeVsSpeedup.txt
echo

echo number of points = 1e9
size=9
serial_line="$(./q1_pirand_serial 1000000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q1_parallel_seed 1000000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"
speedup="$(echo "$stime/$ptime" | bc -l)"
echo speedup 1e${size}: ${speedup}
echo "$size $stime $ptime" >> problemSizeVsTime.txt
echo "$size $speedup" >> problemSizeVsSpeedup.txt
echo
