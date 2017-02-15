#!/bin/bash

	gcc -Wall -fopenmp -o q1_warping_serial q1_warping_serial.c -lm
	gcc -Wall -fopenmp -o q1_warping_parallel q1_warping_parallel.c -lm
	 
	echo changing number of threads
	echo	   

	echo Threads_1
	export OMP_NUM_THREADS=1
	serial_line="$(./q1_warping_serial lena_256x256.ppm)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q1_warping_parallel lena_256x256.ppm)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedupThread1: 
	echo " $stime/$ptime" | bc -l
	echo 

	echo Threads_2
	export OMP_NUM_THREADS=2
	serial_line="$(./q1_warping_serial lena_256x256.ppm)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q1_warping_parallel lena_256x256.ppm)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedupThread2: 
	echo " $stime/$ptime" | bc -l
	echo 

	echo Threads_3
	export OMP_NUM_THREADS=3
	serial_line="$(./q1_warping_serial lena_256x256.ppm)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q1_warping_parallel lena_256x256.ppm)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedupThread3: 
	echo " $stime/$ptime" | bc -l
	echo 

	echo Threads_4
	export OMP_NUM_THREADS=4
	serial_line="$(./q1_warping_serial lena_256x256.ppm)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q1_warping_parallel lena_256x256.ppm)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedupThread4: 
	echo " $stime/$ptime" | bc -l
	echo      
	
	echo changing input size
	echo

	echo image_size_256x256
	serial_line="$(./q1_warping_serial lena_256x256.ppm)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q1_warping_parallel lena_256x256.ppm)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedup256x256: 
	echo " $stime/$ptime" | bc -l
	echo 
	 
	echo image_size_512
	serial_line="$(./q1_warping_serial lena_512x512.ppm)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q1_warping_parallel lena_512x512.ppm)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedup512: 
	echo " $stime/$ptime" | bc -l
	echo

	echo image_size_1024
	serial_line="$(./q1_warping_serial lena_1024x1024.ppm)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q1_warping_parallel lena_1024x1024.ppm)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedup1024: 
	echo " $stime/$ptime" | bc -l
	echo

	echo image_size_2048
	serial_line="$(./q1_warping_serial lena_2048x2048.ppm)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q1_warping_parallel lena_2048x2048.ppm)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedup2048 
	echo " $stime/$ptime" | bc -l
	echo 
