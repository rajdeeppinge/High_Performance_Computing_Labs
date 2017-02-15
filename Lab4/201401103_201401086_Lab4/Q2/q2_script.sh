#!/bin/bash

gcc -Wall -fopenmp -o q2_serial_bench q2_serial_bench.c
gcc -Wall -fopenmp -o q2_builtin_reduc q2_builtin_reduc.c
gcc -Wall -fopenmp -o q2_reduction_simpledivision q2_reduction_simpledivision.c
gcc -Wall -fopenmp -o q2_mixture q2_mixture.c

echo changing number of threads, size = 1e7
echo	   

echo Threads_1
thread=1
export OMP_NUM_THREADS=${thread}
serial_line="$(./q2_serial_bench 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" > q2_coresVsSpeedup_size1e7.txt
echo 

echo Threads_2
thread=2
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  

echo Threads_3
thread=3
export OMP_NUM_THREADS=${thread}3
#serial_line="$(./q2_serial_bench 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  


echo Threads_4
thread=4
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  


echo Threads_6
thread=6
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  


echo Threads_8
thread=8
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  


echo Threads_12
thread=12
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  


echo Threads_16
thread=16
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  

echo Threads_24
thread=24
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  

echo Threads_32
thread=32
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e7.txt
echo  

echo changing number of threads, size = 1e8
echo	   

echo Threads_1
thread=1
export OMP_NUM_THREADS=${thread}
serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" > q2_coresVsSpeedup_size1e8.txt
echo  
 

echo Threads_2
thread=2
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  
 

echo Threads_3
thread=3
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  


echo Threads_4
thread=4
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  


echo Threads_6
thread=6
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  


echo Threads_8
thread=8
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  


echo Threads_12
thread=12
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  


echo Threads_16
thread=16
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  

echo Threads_24
thread=24
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  

echo Threads_32
thread=32
export OMP_NUM_THREADS=${thread}
#serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)"

echo speedup ${thread} thread: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$thread $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_coresVsSpeedup_size1e8.txt
echo  
      

echo changing input size
echo

echo number of points = 1e3
size=3
serial_line="$(./q2_serial_bench 1000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 1000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 1000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 1000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)" 

echo speedup 1e${size}: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$size $stime $ptime $psimpledivtime $pmixtime" > q2_problemSizeVsTime.txt
echo "$size $speedup_builtin $speedup_simplediv $speedup_mix" > q2_problemSizeVsSpeedup.txt
echo 
	 
echo number of points = 1e4
size=4
serial_line="$(./q2_serial_bench 10000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)" 

echo speedup 1e${size}: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$size $stime $ptime $psimpledivtime $pmixtime" >> q2_problemSizeVsTime.txt
echo "$size $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_problemSizeVsSpeedup.txt
echo 

echo number of points = 1e5
size=5
serial_line="$(./q2_serial_bench 100000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 1000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)" 

echo speedup 1e${size}: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$size $stime $ptime $psimpledivtime $pmixtime" >> q2_problemSizeVsTime.txt
echo "$size $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_problemSizeVsSpeedup.txt
echo

echo number of points = 1e6
size=6
serial_line="$(./q2_serial_bench 1000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 1000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 1000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 1000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)" 

echo speedup 1e${size}: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$size $stime $ptime $psimpledivtime $pmixtime" >> q2_problemSizeVsTime.txt
echo "$size $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_problemSizeVsSpeedup.txt
echo

echo number of points = 1e7
size=7
serial_line="$(./q2_serial_bench 10000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 10000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 10000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 10000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)" 

echo speedup 1e${size}: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$size $stime $ptime $psimpledivtime $pmixtime" >> q2_problemSizeVsTime.txt
echo "$size $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_problemSizeVsSpeedup.txt
echo

echo number of points = 1e8
size=8
serial_line="$(./q2_serial_bench 100000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 100000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 100000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 100000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)" 

echo speedup 1e${size}: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$size $stime $ptime $psimpledivtime $pmixtime" >> q2_problemSizeVsTime.txt
echo "$size $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_problemSizeVsSpeedup.txt
echo

echo number of points = 1e9
size=9
serial_line="$(./q2_serial_bench 1000000000)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"
parallel_line="$(./q2_builtin_reduc 1000000000)"
echo Parallel: ${parallel_line}
ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

speedup_builtin="$(echo "$stime/$ptime" | bc -l)"

parallel_simple_div="$(./q2_reduction_simpledivision 1000000000)"
echo ParallelSimpleDiv: ${parallel_simple_div}
psimpledivtime="$(echo "${parallel_simple_div}" | awk '{ print $2 }')"

speedup_simplediv="$(echo "$stime/$psimpledivtime" | bc -l)"

parallel_mix="$(./q2_mixture 1000000000)"
echo ParallelMix: ${parallel_mix}
pmixtime="$(echo "${parallel_mix}" | awk '{ print $2 }')"

speedup_mix="$(echo "$stime/$pmixtime" | bc -l)" 

echo speedup 1e${size}: ${speedup_builtin} ${speedup_simplediv} ${speedup_mix}
echo "$size $stime $ptime $psimpledivtime $pmixtime" >> q2_problemSizeVsTime.txt
echo "$size $speedup_builtin $speedup_simplediv $speedup_mix" >> q2_problemSizeVsSpeedup.txt
echo
