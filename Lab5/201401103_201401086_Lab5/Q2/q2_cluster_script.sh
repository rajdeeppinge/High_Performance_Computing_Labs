#!/bin/bash

gcc -Wall -fopenmp -o q2_filter_serial q2_filter_serial.c
gcc -Wall -fopenmp -o q2_filter_parallel q2_filter_parallel.c
gcc -Wall -fopenmp -o q2_filter_parallel_basic q2_filter_parallel_basic.c

threshold=10

echo changing number of threads, size = 1e7
echo

thread=1
echo Threads_${thread}
export OMP_NUM_THREADS=${thread}
serial_line="$(./q2_filter_serial 10000000 $threshold)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_filter_parallel 10000000 $threshold $thread)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_basic="$(echo "$stime/$ptime" | bc -l)"

parallel_filter_scan="$(./q2_filter_parallel_basic 10000000 $threshold)"
echo ParallelFilterScan: ${parallel_filter_scan}
pscanfiltertime="$(echo "${parallel_filter_scan}" | awk '{ print $2 }')"

speedup_scan_filter="$(echo "$stime/$pscanfiltertime" | bc -l)"

echo speedup ${thread} thread: ${speedup_basic} ${speedup_scan_filter}
echo "$thread $speedup_basic $speedup_scan_filter" > q2_coresVsSpeedup_size1e7.txt
echo 

for i in 2 3 4 6 8 10 12
do

thread=$i
echo Threads_${thread}
export OMP_NUM_THREADS=${thread}
serial_line="$(./q2_filter_serial 10000000 $threshold)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_filter_parallel 10000000 $threshold $thread)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_basic="$(echo "$stime/$ptime" | bc -l)"

parallel_filter_scan="$(./q2_filter_parallel_basic 10000000 $threshold)"
echo ParallelFilterScan: ${parallel_filter_scan}
pscanfiltertime="$(echo "${parallel_filter_scan}" | awk '{ print $2 }')"

speedup_scan_filter="$(echo "$stime/$pscanfiltertime" | bc -l)"

echo speedup ${thread} thread: ${speedup_basic} ${speedup_scan_filter}
echo "$thread $speedup_basic $speedup_scan_filter" >> q2_coresVsSpeedup_size1e7.txt
echo 

done

echo changing number of threads, size = 1e8
echo	   

thread=1
echo Threads_${thread}
export OMP_NUM_THREADS=${thread}
serial_line="$(./q2_filter_serial 100000000 $threshold)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_filter_parallel 100000000 $threshold $thread)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_basic="$(echo "$stime/$ptime" | bc -l)"

parallel_filter_scan="$(./q2_filter_parallel_basic 100000000 $threshold)"
echo ParallelFilterScan: ${parallel_filter_scan}
pscanfiltertime="$(echo "${parallel_filter_scan}" | awk '{ print $2 }')"

speedup_scan_filter="$(echo "$stime/$pscanfiltertime" | bc -l)"

echo speedup ${thread} thread: ${speedup_basic} ${speedup_scan_filter}
echo "$thread $speedup_basic $speedup_scan_filter" > q2_coresVsSpeedup_size1e8.txt
echo 

for i in 2 3 4 6 8 10 12
do

thread=$i
echo Threads_${thread}
export OMP_NUM_THREADS=${thread}
serial_line="$(./q2_filter_serial 100000000 $threshold)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_filter_parallel 100000000 $threshold $thread)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_basic="$(echo "$stime/$ptime" | bc -l)"

parallel_filter_scan="$(./q2_filter_parallel_basic 100000000 $threshold)"
echo ParallelFilterScan: ${parallel_filter_scan}
pscanfiltertime="$(echo "${parallel_filter_scan}" | awk '{ print $2 }')"

speedup_scan_filter="$(echo "$stime/$pscanfiltertime" | bc -l)"

echo speedup ${thread} thread: ${speedup_basic} ${speedup_scan_filter}
echo "$thread $speedup_basic $speedup_scan_filter" >> q2_coresVsSpeedup_size1e8.txt
echo 

done 
      
echo changing input size
echo

input=1000
size="$(echo "l($input)/l(10)" | bc -l)"
echo number of points = 1e${size%%.*}
serial_line="$(./q2_filter_serial $input $threshold)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_filter_parallel $input $threshold $thread)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_basic="$(echo "$stime/$ptime" | bc -l)"

parallel_filter_scan="$(./q2_filter_parallel_basic $input $threshold)"
echo ParallelFilterScan: ${parallel_filter_scan}
pscanfiltertime="$(echo "${parallel_filter_scan}" | awk '{ print $2 }')"

speedup_scan_filter="$(echo "$stime/$pscanfiltertime" | bc -l)"

echo speedup 1e$size: ${speedup_basic} ${speedup_scan_filter}
echo ${size%%.*} "$stime $ptime $pscanfiltertime" > q2_problemSizeVsTime.txt
echo ${size%%.*} "$speedup_basic $speedup_scan_filter" > q2_problemSizeVsSpeedup.txt
echo 

for inpsize in 10000 100000 1000000 10000000 100000000 1000000000
do

input=$inpsize
size="$(echo "l($input)/l(10)" | bc -l)"
echo number of points = 1e${size%%.*}
serial_line="$(./q2_filter_serial $input $threshold)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_filter_parallel $input $threshold $thread)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_basic="$(echo "$stime/$ptime" | bc -l)"

parallel_filter_scan="$(./q2_filter_parallel_basic $input $threshold)"
echo ParallelFilterScan: ${parallel_filter_scan}
pscanfiltertime="$(echo "${parallel_filter_scan}" | awk '{ print $2 }')"

speedup_scan_filter="$(echo "$stime/$pscanfiltertime" | bc -l)"

echo speedup 1e$size: ${speedup_basic} ${speedup_scan_filter}
echo ${size%%.*} "$stime $ptime $pscanfiltertime" >> q2_problemSizeVsTime.txt
echo ${size%%.*} "$speedup_basic $speedup_scan_filter" >> q2_problemSizeVsSpeedup.txt
echo 
	
done
