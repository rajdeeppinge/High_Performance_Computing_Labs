/*
Complete tree structure implementation. Level wise execution. Not so effective since number of cores is less.
*/

#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
#include <math.h>

void reduction(int *A,int k); 
//long partial_sum[4]= {0,0,0,0};

int main(int argc, char* argv[])
{
	int N = atoi(argv[1]),Nnew;
	int i;

//	Nnew =(int)pow(2,( log10(N)/log10(2) +1 ));

	
	// allocate memory for two arrays which will be used alternately
	int *A = (int *) malloc(sizeof(int)*N);
	

	for(i=0;i<N;i++)
		A[i]=1; //fill the array

	
	double start=omp_get_wtime();
	reduction(A,N);
	double end=omp_get_wtime();

	/*Time using reduction: */
	printf("Time: %f\n",end-start);
	return 0;

}

void reduction(int *A,int k) // put N as k in main
{
	//replace the code here 

	int j, N = k,i;

    int add_from=1 , jump_to=2; 
	// step complexity log k
	for (j=0;j<(log10(k)/log10(2) + 1) ;jump_to=jump_to*2,add_from=add_from*2,j++) 
	{	
		# pragma omp parallel for 
		    for (i=0;i<k;i=i+jump_to)
		        {
		            if (i+add_from<k)
		                A[i]= A[i] + A[i+add_from];
		        } 
		      
	} // 56 while
	  
	 printf("ans:%d\n",A[0]);
  
		/*
		
		    for (i=0;i<k;i++)
		        {
		            printf("%d ",A[0]);
		                
		        } 
		printf("\n");*/
      
}
    
   
    

 
