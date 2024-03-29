/* simple parallel which gives speed down */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double par_time;
double n_fin;
void pi_rand()
{

int N=1000000,i,n=0; // number of
double x_cor,y_cor;

 //int ri[N], ry[N]; 

double par_start= omp_get_wtime();

#pragma omp parallel for reduction(+:n) \
	 private (x_cor,y_cor)
	for (i=0;i<N;i++)
	{
		x_cor = -1 + 2.0*(rand()/(double)RAND_MAX);
		y_cor= 	-1 + 2.0*(rand()/(double)RAND_MAX);

		if ((x_cor*x_cor + y_cor*y_cor) <1)
			
					
			n++;
	}
double par_end= omp_get_wtime();

par_time = par_end- par_start;
	printf("Approx value of p : %f\n",4*((double)n)/N); 
}

int main()
{
   double start,end;

start= omp_get_wtime();

    pi_rand();
end= omp_get_wtime();

printf("time:%f frac_parallelisable:%f\n",end-start,(double)par_time/(end-start));
	return 0;
}
