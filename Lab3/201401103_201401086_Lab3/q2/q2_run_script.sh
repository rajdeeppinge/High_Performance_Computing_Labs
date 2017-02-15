#!/bin/bash

# 256,512,1024,2048 are possible square image dimensions

	gcc -Wall -fopenmp -o q2_filter_serial q2_filter_serial.c -lm
	gcc -Wall -fopenmp -o q2_filter_parallel q2_filter_parallel.c -lm
	 
	echo WARNING: THIS CODE MIGHT TAKE APPROXIMATELY 60 SECONDS TO PROCESS FOR ALL THE IMAGE SIZES. ALSO THE SCRIPT GIVES THE SPEEDUP OF approximately 3 BUT WHEN RUN INDIVIDUALLY THE SPEEDUP IS \> 5
	echo
	
	echo changing number of threads problem size 256x256 and half-width 3
	echo	   

	echo Threads_1
	export OMP_NUM_THREADS=1
	serial_line="$(./q2_filter_serial lena_256x256.ppm 3)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q2_filter_parallel lena_256x256.ppm 3)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedupThread1: 
	echo " $stime/$ptime" | bc -l
	echo 

	echo Threads_2
	export OMP_NUM_THREADS=2
	serial_line="$(./q2_filter_serial lena_256x256.ppm 3)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q2_filter_parallel lena_256x256.ppm 3)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedupThread2: 
	echo " $stime/$ptime" | bc -l
	echo 

	echo Threads_3
	export OMP_NUM_THREADS=3
	serial_line="$(./q2_filter_serial lena_256x256.ppm 3)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q2_filter_parallel lena_256x256.ppm 3)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedupThread3: 
	echo " $stime/$ptime" | bc -l
	echo 

	echo Threads_4
	export OMP_NUM_THREADS=4
	serial_line="$(./q2_filter_serial lena_256x256.ppm 3)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q2_filter_parallel lena_256x256.ppm 3)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedupThread4: 
	echo " $stime/$ptime" | bc -l
	echo      
	
	echo changing input size half-width 2 threads 4
	echo

	echo image_size_256x256
	serial_line="$(./q2_filter_serial lena_256x256.ppm 2)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q2_filter_parallel lena_256x256.ppm 2)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedup256x256: 
	echo " $stime/$ptime" | bc -l
	echo 
	 
	echo image_size_512
	serial_line="$(./q2_filter_serial lena_512x512.ppm 2)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q2_filter_parallel lena_512x512.ppm 2)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedup512: 
	echo " $stime/$ptime" | bc -l
	echo

	echo image_size_1024
	serial_line="$(./q2_filter_serial lena_1024x1024.ppm 2)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q2_filter_parallel lena_1024x1024.ppm 2)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedup1024: 
	echo " $stime/$ptime" | bc -l
	echo

	echo image_size_2048
	serial_line="$(./q2_filter_serial lena_2048x2048.ppm 2)"
	echo Serial: ${serial_line}
	stime="$(echo "${serial_line}" | awk '{ print $3 }')"
	parallel_line="$(./q2_filter_parallel lena_2048x2048.ppm 2)"
	echo Parallel: ${parallel_line}
	ptime="$(echo "${parallel_line}" | awk '{ print $3 }')"
	echo speedup2048 
	echo " $stime/$ptime" | bc -l
	echo 
