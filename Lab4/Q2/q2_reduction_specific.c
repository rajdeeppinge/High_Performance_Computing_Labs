/*
divide work amongst threads.
*/

#include <stdio.h>
#include <omp.h>
#include<stdlib.h>

long reduction(int *A,int k); 


int main(int argc, char* argv[])
{
int N = atoi(argv[1]);
int i;

int *A = (int *) malloc(sizeof(int)*N);

for(i=0;i<N;i++)
	A[i]=1; //fill the array


double start=omp_get_wtime();
 printf("final sum: %ld \n",reduction(A,N));
double end=omp_get_wtime();

printf("Time using reduction: %f\n",end-start);
return 0;

}

long reduction(int *A,int k) // put N as k in main
{
   //replace the code here 

long partial_sum,id,istart,iend,i,final_sum=0; //private variables for loop
 
	# pragma omp parallel private(partial_sum,id,istart,iend,i) \
      shared(final_sum)

	{
		int num_threads = omp_get_num_threads();
		//printf("threads: %d\n",num_threads);
	
		 id = omp_get_thread_num();
		 istart = (id * k) / num_threads;
		 iend = ((id+1) * k) / num_threads;
		 

		//printf("id : %d, start : %d, end : %d\n", id, istart, iend);
		partial_sum = 0;
		
		for(i = istart; i < iend; i++)
		{
			partial_sum += A[i];	// function which gives alternate +ve or -ve 1 in the numerator
		}
		
	
		
		#pragma omp critical
		{
			final_sum += partial_sum;
		}
	
	}

return final_sum;
} 
