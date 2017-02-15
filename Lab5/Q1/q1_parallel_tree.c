/* Code to implement prefix scan using tree method. First it uses Forward tree and then uses inverse tree */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<math.h>

void scan(int *A, int N)
{	
	int step,i;
	int steplimit = (float)log(N)/(float)log(2);
	int level;
	
	for (level = 1, step=2; level <= steplimit; step=step*2, level++)
	{	
		# pragma omp parallel for
		for (i=step-1;i<N;i=i+step)
		{
			A[i]= A[i] + A[i-step/2];
		}
	}

	step=step/2;
	for (; step>=1; step=step/2)
	{	
		# pragma omp parallel for private(i), shared(step, A)
		for (i=step-1;i<N;i=i+step)
		{
			/*if( (float)log(i+1)/(float)log(2) - (int)log(i+1)/log(2) == 0 )	// condition to check if it is power of 2
				continue;
			else */
			
			if((i+1)%(step*2) == 0)
				continue;
			else
			{
				A[i] = A[i] + A[i-step];			
			}
		}
	}

/*
	for(i = 0; i < 25; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");*/

}

int main(int argc, char* argv[])
{
	int N = atoi(argv[1]);		// size of array
	
	int i;
	
	// initialize array A
	int *A = (int *) malloc(sizeof(int) * N);

	for (i=0;i<N;i++)
	{
		A[i]=1;
	}

	double start=omp_get_wtime();
	scan(A, N);
	double end= omp_get_wtime();

	printf("time: %f\n"/*last element = %d\n"*/, end-start/*, A[N-1]*/);

	printf("\n");

	return 0;
}


