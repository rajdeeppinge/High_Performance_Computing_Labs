/* Code to implement prefix scan using normal serial method */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	int N = atoi(argv[1]);		// size of array
	
	int i;
	
	// initialize array on which prefix scan is performed
	int *A = (int *) malloc(sizeof(int) * N);

	for (i=0;i<N;i++)
		A[i]=1;


	// block which performs prefix scan
	double start=omp_get_wtime();

	for (i=0; i<(N-1); i++)
	{
		A[i+1] = A[i+1] + A[i];
	}

	double end= omp_get_wtime();

	/* printing array to check the correctness
	for(i = 0; i < N; i++)
		{
			printf("%d ", A[i]);
		}
		printf("\n");
	*/

	printf("time: %f\n",end-start/*"MFLOP = %f", N/(1000000*(end-start))*/);

	return 0;
}
