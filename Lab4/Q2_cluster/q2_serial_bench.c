/* simple princliple of reduction */

#include <stdio.h>
#include <omp.h>
#include<stdlib.h>

void reduction_serial(int *A, int N)
{
	int i, sum = 0;

//	double par_start = omp_get_wtime();
	//reducing the array to a single element
	for(i=0;i<N;i++)
	{
		sum += A[i];
	}
//	double par_end = omp_get_wtime();

//	printf("sum = %d\n", sum);
//	printf("MFLOPS = %f\n", N / (1000000*(par_end-par_start)));
}

int main(int argc, char* argv[])
{
	int N = atoi(argv[1]);		// size of array
	int i;

	// allocating space for array
	int *A = (int *) malloc(sizeof(int)*N);

	for(i=0;i<N;i++)
		A[i]=1; //fill the array

	double start=omp_get_wtime();   
	reduction_serial(A, N);
	double end=omp_get_wtime();

	printf("Time: %f\n",end-start);
	return 0;
}

