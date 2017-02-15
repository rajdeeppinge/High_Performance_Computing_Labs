#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int dotpro(short * ptrarr1, short *ptrarr2, int N);  //use malloc instead

int main()
{
	int N=1000000000; // this is the heap bound will have to inc heap size 

	short size_double= sizeof(short);
	
	short* ptrarr1 = (short *) malloc (N*size_double);
	short* ptrarr2 = (short *) malloc (N*size_double);
	short* curr1=ptrarr1;
	short* curr2=ptrarr2;
	
	//fill up the dynamic arrays

	// for now the filling is kept sequential for both

	int i; //dimesnison of the arrays
  
    for (i=0;i<N;i++)
	{ 
		*curr1=1;
		*curr2=1;

		curr1++; 
		curr2++;         
	}
 
	double start_time = omp_get_wtime(); //start time after array have set up don't incl setup time

    printf("Dot product is: %d\n",dotpro(ptrarr1,ptrarr2, N));
    
    double end_time = omp_get_wtime()-start_time;
    
    printf("time taken :%f\n",end_time);   
    
    return 0;
}
       


int dotpro(short * ptrarr1,short *ptrarr2, int N)
{
	// dot product, element wise multuple collect in 1 number
	int i;
	int dotpro=0;

	short* curr1=ptrarr1;
	short* curr2=ptrarr2;

	# pragma omp parallel for schedule(dynamic, 128) num_threads(4) \
		reduction(+: dotpro)
	for (i=0;i<N;i++)
	{
		dotpro += (curr1[i])*(curr2[i]);
	} 
	
	return dotpro;   
}
