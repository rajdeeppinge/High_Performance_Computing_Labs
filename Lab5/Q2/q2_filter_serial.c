/* Code to filter and array using serial method */

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
			// generating random numbers in range [0,100)
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


// this function counts the number of elements greater than the threshold and accordingly gives the size for the output array
int *create_B(int *A, int N, int threshold)
{
	int i, count = 0;
	for(i = 0; i < N; i++) 
	{
		if(A[i] >= threshold)
			count++;
	}
	
	return (int *) malloc(sizeof(int) * count);
}


/* function to actually perform filtering */
void filter(int *A, int *B, int N, int threshold)
{
	int i, j = 0;
//	double start=omp_get_wtime();

	for (i=0;i<N;i++)
	{
		if(A[i] >= threshold)
			B[j++] = A[i];		// dependency of j
	}

//	double end= omp_get_wtime();
/*	
	for(i = 0; i < (j>10?10:j); i++)
	{
		printf("%d ", B[i]);
	}
	printf("\n");
*/
}


int main(int argc, char* argv[])
{
	int N = atoi(argv[1]);		// number of points to take
	int threshold = atoi(argv[2]);		// number of points to take
	
	int *A = (int *) malloc(sizeof(int) * N);
	//int *B = (int *) malloc(sizeof(int) * N);	//lot of storage space wasted
	double start,end;
	
	fill_arr(A, N);					//function to calculate pi using random numbers


	// actual execution code	
	start= omp_get_wtime();	
	int *B = create_B(A, N, threshold);
	filter(A, B, N, threshold);
	end= omp_get_wtime();

	//printf("time: %f, frac_parallelisable: %f\n",end-start,(double)par_time/(end-start));
	printf("time: %f\n",end-start);
	return 0;
}
