#include <stdio.h>
#include <omp.h>

double trap_area(double start, double end, int num_steps, double start_time);
double f(double x);

double global_approx;

int main()
{
	double start_time = omp_get_wtime();
	double start=0.0,end=1.0;
	int num_steps=100000;
	double approx_area= trap_area(start,end,num_steps, start_time);
	printf("Approx area is: %f, time_taken = %f\n",approx_area, omp_get_wtime()-start_time);
	return 0;
}

double f(double x)
{
	// return the req formula
	return 4.0/(1.0+x*x);
}

double trap_area(double start,double end, int num_steps, double start_time)
{		
	int i;
	
	global_approx = (f(start)+f(end))/2.0;

	#pragma omp parallel
	{	int id, Nthreads, istart, iend;
		id = omp_get_thread_num();
		Nthreads = omp_get_num_threads();
		istart = id * num_steps / Nthreads;
		iend = (id+1) * num_steps / Nthreads;
		if(id == Nthreads - 1)
			iend = num_steps;
		
		double h= ((double)iend-istart)/(double)num_steps;
		double approx = 0;
		for (i=istart;i<iend;i++)	
			approx += f(istart + i*h);
			
		printf("%d, %d\n",istart, iend);
		#pragma omp critical
		{
			global_approx += approx*h;
		}
		printf("%f\n",global_approx);	

	}

	return global_approx;
}
