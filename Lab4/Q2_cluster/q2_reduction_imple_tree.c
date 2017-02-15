/*
divide work amongst threads.
*/

#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
#include <math.h>

void reduction(int *A,int* A2,int k); 
long partial_sum[4]= {0,0,0,0};

int main(int argc, char* argv[])
{
	int N = atoi(argv[1]),Nnew;
	int i;

//	Nnew =(int)pow(2,( log10(N)/log10(2) +1 ));

	Nnew = N + omp_get_num_threads() - (N % omp_get_num_threads());
	// allocate memory for two arrays which will be used alternately
	int *A = (int *) malloc(sizeof(int)*Nnew);
	int *A2 = (int *) malloc(sizeof(int)*Nnew);

	for(i=0;i<N;i++)
		A[i]=1; //fill the array

	for(i=N;i<Nnew;i++)
		A[i]=0;  //padding added to make it regular.

	double start=omp_get_wtime();
	reduction(A,A2,Nnew);
	double end=omp_get_wtime();

	/*Time using reduction: */
	printf("Time: %f\n",end-start);
	return 0;

}

void reduction(int *A,int * A2,int k) // put N as k in main
{
	//replace the code here 

	long id,i; //private variables for loop
	int t = omp_get_num_threads();
	int j, N = k;

	// step complexity log k
	for (j=0;j<(log10(k)/log10(2) + 1) ;j++, N = N / 2 + 1)
	{	
		# pragma omp parallel private(id,i) \
		shared(t,k)
		{
			id = omp_get_thread_num(); 
			if ((j%2) ==0) // even case
			{
				// sum elements pairwise
				for(i =0; i < N; i=i+(2*t)) // here 8 
				{
					if ( (i+2*id+1) <N)
					{
						A2[(i+2*id)/2] = A[i+2*id] + A[i + 2*id+ 1]; 
					}
					else if ((i+2*id) <N)
					{
						A2[(i+2*id)/2] = A[i+2*id]; // without rem --, carry forward
					}
				}
			}
			else // if odd
			{
				// sum elements pairwise
				for(i =0; i <N; i=i+(2*t)) // here 8 
				{
					if ( (i+2*id+1) <N)
					{
						A[(i+2*id)/2] = A2[i+2*id] + A2[i + 2*id+ 1];					 
					}
					else if ((i+2*id) <N)
					{
						A[(i+2*id)/2] = A2[i+2*id]; // without rem --, carry forward
					}
				}
			}
		}       
	} // 56 while
	  
	 
	if((int)(log(k)/log(2)) %2==0)  
		printf("ans:%d\n",A2[0]);

	else 
		printf("ans:%d\n",A[0]);

	printf("both\n");
	printf("ans:%d\n",A[0]);
	printf("ans:%d\n",A2[0]);
}
    
   
    

 
