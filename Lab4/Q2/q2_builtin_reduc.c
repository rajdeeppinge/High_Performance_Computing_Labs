/*
	Programme to calculate sum of an array parallely using built-in reduction
*/

#include <stdio.h>
#include <omp.h>
#include<stdlib.h>

/* function to implement built_in reduction function */
void reduction_builtin(int *A, int N)
{
	//replace the code here 

	int i, final_sum = 0;

	// reducing the array to a single element
	# pragma omp parallel for reduction(+:final_sum)
	for(i = 0; i < N; i++)
	{
		final_sum += A[i];		// final_sum acts both as private and as shared due to reduction clause
	}
	
//	printf("final_sum = %d\n", final_sum);
} 


int main(int argc, char* argv[])
{
	int N = atoi(argv[1]);	//size of array
	int i;

	// allocating space for array
	int *A = (int *) malloc(sizeof(int)*N);

	for(i=0;i<N;i++)
		A[i]=1; //fill the array

	//execute builtin reduction
	double start=omp_get_wtime();
	reduction_builtin(A,N);
	double end=omp_get_wtime();

	/*Time using reduction: */
	printf("Time: %f ",end-start);

	return 0;
}


