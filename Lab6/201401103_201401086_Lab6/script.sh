#!/bin/bash

gcc -Wall -fopenmp -o trapezoidal_serial trapezoidal_serial.c
gcc -Wall -fopenmp -o q3_trapezoidal_parallel_reduction q3_trapezoidal_parallel_reduction.c
mpicc -Wall -fopenmp -o trapezoidal_mpi trapezoidal_mpi.c
	

for inpsize in 1000 10000 100000 1000000 10000000 100000000 1000000000
do

input=$inpsize
fsize="$(echo "l($input)/l(10)" | bc -l)"
size=${fsize%.*}
echo number of points = 1e${size}
serial_line="$(./trapezoidal_serial $input)"
echo Serial: ${serial_line}
stime="$(echo "${serial_line}" | awk '{ print $2 }')"

sleep 2

	for i in 1 2 3 4 6 8 10 12 14 16
	do

	thread=$i
	echo Threads_${thread}
	export OMP_NUM_THREADS=${thread}
	
	parallel_line="$(./q3_trapezoidal_parallel_reduction $input)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $2 }')"

	speedup_omp="$(echo "$stime/$ptime" | bc -l)"
	eff_omp="$(echo "$speedup_omp/$thread" | bc -l)"

	sleep 2

	parallel_mpi="$(mpirun -np $thread ./trapezoidal_mpi $input)"
	echo Parallelmpi: ${parallel_mpi}
	pmpitime="$(echo "${parallel_mpi}" | awk '{ print $2 }')"

	speedup_mpi="$(echo "$stime/$pmpitime" | bc -l)"
	eff_mpi="$(echo "$speedup_mpi/$thread" | bc -l)"

	sleep 2
	
	echo speedup ${thread} thread: ${speedup_omp} ${speedup_mpi}
	echo "$thread $speedup_omp $speedup_mpi" >> q1_coresVsSpeedup_size1e${size}.txt
	echo "$thread $eff_omp $eff_mpi" >> q1_coresVsEfficiency_size1e${size}.txt
	echo 
	
	done
	
echo ${size} "$stime $ptime $pmpitime" >> q1_problemSizeVsTime.txt

done
