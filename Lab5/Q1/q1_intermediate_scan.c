/* Code to implement prefix scan using intermediate scan method */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<math.h>

void scan(int *A, int N, int threads)
{
	// intermediate scan array
	int partial[threads];
	
	
	long id, istart, iend, i; //private variables for loop
	long sum = 0;

//	double par_start = omp_get_wtime();
	# pragma omp parallel private(id,istart,iend,i,sum) \
	  shared(partial)
	{
		int num_threads = omp_get_num_threads();

		id = omp_get_thread_num();
		
		istart = (id * N) / num_threads;		
		iend = ((id+1) * N) / num_threads;
		
		// loop to perform prefix scan
		for (i = istart; i < iend; i++)
		{
			// two statements to remove loop dependency and make a register access
			A[i] = A[i] + sum;
			sum = A[i];			// temporary variable to avoid loop dependency by having to call A[i-1]
		}
		
		partial[id] = A[iend-1];
	
		#pragma omp barrier
		
		// Now we perform prefix scan on intermediate array with a single thread
		
		#pragma omp master
		for (i = 0; i < threads-1; i++)
		{
			partial[i+1] = partial[i+1] + partial[i];
		}
	
		// again with all the threads, add the appropriate elements of the intermediate array to original array to complete the prefix scan
		if(id != 0) 
		{ 
			for (i = istart; i < iend; i++)
			{
				A[i] += partial[id-1];
			}
		}
	}
	
//	double par_end = omp_get_wtime();
	
//	printf("MFLOPS = %f\n", (2*N+threads)/(1000000*(par_end-par_start)));

/* printing some elements to check correctness
	for(i = 0; i < 25; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
*/
}

int main(int argc, char* argv[])
{
	int N = atoi(argv[1]);		// size of array
	int threads = atoi(argv[2]);
	
	int i;
	
	// initialize array A
	int *A = (int *) malloc(sizeof(int) * N);

	for (i=0;i<N;i++)
	{
		A[i]=1;
	}

	double start=omp_get_wtime();
	scan(A, N, threads);
	double end= omp_get_wtime();

	printf("time: %f\n"/*last element = %d\n"*/, end-start/*, A[N-1]*/);

	return 0;
}


