/* Code to filter an array using prefix scan method */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* function to initialize original array
	input: number of points to take
	output: approx value of pi
*/
//Note here that in order to save total execution time, we have initialized the array wih parallel code
// We assume that we already have the array, hence this time is not counted as the time to perform filtering. 
void fill_arr(int *A, int N)
{
	int i;
	
	#pragma omp parallel
	{
		unsigned int seed = omp_get_thread_num();		// only one thread. Therefore it can have any seed

	//	double par_start= omp_get_wtime();
	
		#pragma omp for
		for (i=0;i<N;i++)
		{
			// generating random number
			A[i] = (rand_r(&seed)/(double)RAND_MAX)*100;
		}
	}
/*
	for(i = 0; i < 10; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
*/
//	double par_end= omp_get_wtime();

//	par_time = par_end- par_start;
//	printf("Approx value of pi : %f\n",4*((double)n)/N);
//	printf("MFLOPS = %f\n", 6 * N / (1000000*(par_end-par_start))); 
}


// this function counts the number of elements greater than the threshold and accordingly initializes the flag array
int *fill_B(int *A, int N, int threshold) 
{
	int *B = (int *) calloc(N, sizeof(int));
	
	long id, istart, iend, i; //private variables for loop
	# pragma omp parallel private(id,istart,iend,i)
	{
		int num_threads = omp_get_num_threads();

		id = omp_get_thread_num();
		
		istart = (id * N) / num_threads;		
		iend = ((id+1) * N) / num_threads;
		 
		for (i = istart; i < iend-1; i++)
		{
			if(A[i] >= threshold)		// if > threshold, flag is set to 1
			{
				B[i] = 1;
			}
/*			else 
			{
				B[i] = 0;
			}*/
		}
	}	
	
	return B;
}


/* Function to perform prefix scan on the flag array */
void scan(int *B, int N, int threads)
{
	int partial[threads];
	long id, istart, iend, i; //private variables for loop

//	double par_start = omp_get_wtime();

	// block to perform first step of scan and creting the intermediate array
	# pragma omp parallel private(id,istart,iend,i) \
	  shared(partial)
	{
		int num_threads = omp_get_num_threads();

		id = omp_get_thread_num();
		
		istart = (id * N) / num_threads;		
		iend = ((id+1) * N) / num_threads;
		 
		for (i = istart; i < iend-1; i++)
		{
			B[i+1] = B[i+1] + B[i];
		}
		
		partial[id] = B[iend-1];
	}
	
	// intermediate array prefix scan using 1 thread 
	for (i = 0; i < threads-1; i++)
	{
		partial[i+1] = partial[i+1] + partial[i];
	}
	
	// add the appropriate elements of the intermediate array to original array to complete the prefix scan
	# pragma omp parallel private(id,istart,iend,i) \
	  shared(partial)
	{
		int num_threads = omp_get_num_threads();

		id = omp_get_thread_num();
		
		istart = (id * N) / num_threads;		
		iend = ((id+1) * N) / num_threads;
		
		if(id != 0) 
		{ 
			for (i = istart; i < iend; i++)
			{
				B[i] += partial[id-1];
			}
		}
	}

/*
	for(i = 0; i < 25; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
*/
}

/* function to perform filtering 
	Due to dependency we can't parallelize this block nor we can remove the dependency
*/
void filter(int *A, int *B, int N, int threshold, int threads)
{
//	int j = 0;
//	double start=omp_get_wtime();
	
//	int threads = omp_get_num_threads();
	
	//scan the flag array
	scan(B, N, threads);
	
	// create final array
	int outsize = B[N-1];
	int *final = (int *) malloc(sizeof(int) * outsize);
	
	// filtering
	if(B[0] == 1)
		final[0] = A[0]; 	
	
	long id, istart, iend, i; //private variables for loop
	# pragma omp parallel private(id,istart,iend,i)
	{
		int num_threads = omp_get_num_threads();

		id = omp_get_thread_num();
		
		istart = (id * N) / num_threads;		
		iend = ((id+1) * N) / num_threads;
		  
		for (i = istart; i < iend-1; i++)	
		{
			if(B[i+1] > B[i])
				final[B[i+1]-1] = A[i+1];
		}
	}

//	double end= omp_get_wtime();

/*	printing for correctness
	for(j = 0; j < 25; j++)
	{
		printf("%d ", final[j]);
	}
	printf("\n");
*/
}


int main(int argc, char* argv[])
{
	int N = atoi(argv[1]);		// number of points to take
	int threshold = atoi(argv[2]);		// number of points to take
	int threads = atoi(argv[3]);		// number of points to take
	
	int *A = (int *) malloc(sizeof(int) * N);
//	int *B = (int *) malloc(sizeof(int) * N);
	double start,end;

	fill_arr(A, N);					//function to calculate pi using random numbers
	
	// actual execution code
	start= omp_get_wtime();		
	int *B = fill_B(A, N, threshold);
	filter(A, B, N, threshold, threads);
	end= omp_get_wtime();

	//printf("time: %f, frac_parallelisable: %f\n",end-start,(double)par_time/(end-start));
	printf("time: %f\n",end-start);
	return 0;
}
