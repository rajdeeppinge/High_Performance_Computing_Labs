#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<math.h>

int N=100000000;

int *lastind; // = (int *) malloc(sizeof(int) * N); // get a lasting storage for each element, this uses more space.

void scan(int *A)
{
 	
	int step,i;
	int steplimit = (float)log10(N)/(float)log10(2);
	int level;
	//int index;
	// reduction pass 
	for (level = 1, step=2; level <= steplimit; step=step*2, level++)
	{	
    # pragma omp parallel for
		for (i=step-1;i<N;i=i+step)
		{
		 int index=i-step/2;
		    			A[i]= A[i] + A[index];
		    			lastind[i]=lastind[index];
			 // init as i-1 and then last index of i is lastindex of the item added from left
		                    // last index of element is the last index of the element to the left of it
		                    // provided last index is init properly.
		}
		
   }

 /*  printf("check last index\n");
   
     	for(i = 0; i < N; i++)
	{
		printf("%d ", lastind[i]);
	}
	
	printf("\n");*/

  // rest pass, race condi between even and odd 
    #pragma omp parallel for
    for (i=1;i<N;i++)
        {
            if (i%2==0) // if odd in 1 indexed
                A[i]= A[i] + A[i-1];
            else
                {
                    // is i+1 a pow of 2
                    if (((i+1)&(i))==0) // pow of 2
                        continue;
                        
                    // no need to check condi now, even not pow of 2
                         A[i]= A[i] + A[lastind[i]] ;  
                }                 
        }

	/*for(i = 0; i < N; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");*/
 
    	/*for(i = 0; i < N; i++)
	{
		printf("%d ", lastind[i]);
	}*/
	
	printf("\n");
}

int main()
{
	int i;
	int *A = (int *) malloc(sizeof(int) * N);
        lastind = (int *) malloc(sizeof(int) * N);
	for (i=0;i<N;i++)
	{
		A[i]=1;
		lastind[i]=i-1; //lastindex -1 in 0 but don't care for the 0th element, last index array initialized
	}

	double start=omp_get_wtime();
	scan(A);
	double end= omp_get_wtime();

	printf("Parallel time(lastindex):%f\nlast element = %d\n", end-start, A[N-1]);

	printf("\n");

	return 0;
}


